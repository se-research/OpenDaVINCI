//****************************************************************************
// Copyright (C) 2001-2007  PEAK System-Technik GmbH
//
// linux@peak-system.com
// www.peak-system.com
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// Maintainer(s): Klaus Hitschler (klaus.hitschler@gmx.de)
//
//****************************************************************************

//****************************************************************************
//
// pcan_parse.c - read input parser and write output formatter
//
// $Id: pcan_parse.c 839 2015-03-13 10:44:53Z stephane $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <src/pcan_common.h>   // must always be the 1st include
#include <linux/errno.h>       // error codes
#include <linux/kernel.h>      // DPRINTK()
#include <src/pcan_parse.h>

//****************************************************************************
// DEFINES

//****************************************************************************
// GLOBALS

//****************************************************************************
// LOCALS

//****************************************************************************
// CODE

//----------------------------------------------------------------------------
// helper for use in read..., makes a line of formatted output
int pcan_make_output(char *buffer, TPCANRdMsg *m)
{
	u32 rest  = 8;
	char *ptr = buffer;
	int i;
	char r_or_m, s_or_e;

	*buffer = 0;

	if (m->Msg.MSGTYPE & MSGTYPE_STATUS) {
		// any status frames are x-ed
		r_or_m = 'x';
		s_or_e = 'x';
	} else {
		r_or_m = (m->Msg.MSGTYPE & MSGTYPE_RTR)      ? 'r' : 'm';
#ifdef MSGTYPE_SELFRECEIVE
		if (m->Msg.MSGTYPE & MSGTYPE_SELFRECEIVE)
			r_or_m -= 0x20;
#endif
		s_or_e = (m->Msg.MSGTYPE & MSGTYPE_EXTENDED) ? 'e' : 's';
	}

	// print RTR, 11 or 29, CAN-Id and datalength
	sprintf(ptr, "%c %c 0x%08x %1d  ", r_or_m, s_or_e,
						m->Msg.ID, m->Msg.LEN);

	// search the end
	while (*ptr)
		ptr++;

	// "Vorsicht ist die Mutter der Porzellankiste!"
	// or "Better safe than sorry"
	if (m->Msg.LEN > 8) {
		for (i = 0; i < 8; i++) {
			sprintf(ptr, "---- ");
			rest--;
			ptr += 3;
		}
	} else {
		u8 ucLen;

		// don't print any data if it is a RTR message
		if (m->Msg.MSGTYPE & MSGTYPE_RTR)
			ucLen = 0;
		else
			ucLen =  m->Msg.LEN;

		for (i = 0; i < ucLen; i++) {
			sprintf(ptr, "0x%02x ", m->Msg.DATA[i]);
			rest--;
			ptr += 5;
		}
	}

	// else print 5 blanks for each not typed data
	rest *= 5;
	for (i = 0; i < rest; i++)
		*ptr++ = ' ';

	// print timestamp
	sprintf(ptr, " %11u %03u\n", m->dwTime, m->wUsec);

	// search the end
	while (*ptr)
		ptr++;

	return (int)(ptr - buffer);
}

//----------------------------------------------------------------------------
// skip blanks and tabs
static inline void skip_blanks(char **ptr)
{
	// remove blanks or tabs
	while ((**ptr == ' ') || (**ptr == '\t'))
		(*ptr)++;
}

//----------------------------------------------------------------------------
// skip blanks, return 0 if the 1st non-blank char is not '\n'
static int skip_blanks_and_test_for_CR(char **ptr)
{
	// remove blanks or tabs
	skip_blanks(ptr);

	if (**ptr == '\n')
		return -1;
	else
		return 0;
}

//----------------------------------------------------------------------------
// extract a number, either hex or decimal from a string
static int scan_unsigned_number(char **ptr, u32 *dwResult)
{
	char *p = *ptr;

	*dwResult = simple_strtoul(p, ptr, 0);

	if (p != *ptr)
		return 0;

	return -ERANGE;
}

//----------------------------------------------------------------------------
// extract a char from a string
static inline char scan_char(char **ptr)
{
	return *(*ptr)++;
}

//----------------------------------------------------------------------------
// lengthy helper for use in write..., reject empty and comment lines
int pcan_parse_input_idle(char *buffer)
{
	char *ptr = buffer;

	// DPRINTK(KERN_DEBUG "%s: pcan_parse_input_idle()\n", DEVICE_NAME);

	// remove leading blanks
	skip_blanks(&ptr);

	// search for 'm' or 'r' to distinguish between message or init strings
	switch (scan_char(&ptr)) {
	case '#':  // comment
	case '\n': return 0;

	default:   return -EINVAL;
	}
}

//----------------------------------------------------------------------------
// lengthy helper for use in write..., parses a message command
int pcan_parse_input_message(char *buffer, TPCANMsg *Message)
{
	char *ptr = buffer;
	u32 dwLen;
	u32 dwDat;
	int i;
	int err = -EINVAL;

	// DPRINTK(KERN_DEBUG "%s: pcan_parse_input_message()\n", DEVICE_NAME);

	// remove leading blanks
	skip_blanks(&ptr);

	// search for 'm' or 'r' to distinguish between message or init strings
	Message->MSGTYPE  = 0;
	switch (scan_char(&ptr)) {
#ifdef MSGTYPE_SELFRECEIVE
	case 'M':
		Message->MSGTYPE |= MSGTYPE_SELFRECEIVE;
#endif
	case 'm':
		break; // normal message
#ifdef MSGTYPE_SELFRECEIVE
	case 'R':
		Message->MSGTYPE |= MSGTYPE_SELFRECEIVE;
#endif
	case 'r':
		Message->MSGTYPE |= MSGTYPE_RTR;
		break; // rtr message

	default:   goto reject;
	}
	if (skip_blanks_and_test_for_CR(&ptr)) // no CR allowed here
		goto reject;

	// read message type
	switch (scan_char(&ptr)) {
	case 's': break;
	case 'e': Message->MSGTYPE |= MSGTYPE_EXTENDED; break;

	default:  goto reject;
	}
	if (skip_blanks_and_test_for_CR(&ptr))
		goto reject;

	// read CAN-ID
	if ((err = scan_unsigned_number(&ptr, &Message->ID)))
		goto reject;
	if (Message->MSGTYPE & MSGTYPE_EXTENDED) {
		if (Message->ID > 0x3fffffff)
			goto reject;
	} else {
		if (Message->ID > 2047)
			goto reject;
	}
	if (skip_blanks_and_test_for_CR(&ptr))
		goto reject;

	//read datalength
	if ((err = scan_unsigned_number(&ptr, &dwLen)))
		goto reject;
	if (dwLen > 8)
		goto reject;
	Message->LEN = (u8)dwLen;

	// read data elements up to message len
	i = 0;
	while (i < dwLen) {
		if (skip_blanks_and_test_for_CR(&ptr))
		goto reject;

		if ((err = scan_unsigned_number(&ptr, &dwDat)))
			goto reject;
		if (dwDat > 255)
			goto reject;
		Message->DATA[i] = (u8)dwDat;

		i++;
	}

	// DPRINTK(KERN_DEBUG "%s: pcan_parse_input_message() is OK\n", DEVICE_NAME);
	return 0;

reject:
	// DPRINTK(KERN_DEBUG "%s: reject in pcan_parse_input_message()\n", DEVICE_NAME);
	return err;
}

//----------------------------------------------------------------------------
// lengthy helper for use in write..., parses a init command
int pcan_parse_input_init(char *buffer, TPCANInit *Init)
{
	char *ptr = buffer;
	int i    = 0;
	u32 dwDummy;
	int err = -EINVAL;

	// DPRINTK(KERN_DEBUG "%s: pcan_parse_input_init()\n", DEVICE_NAME);

	// remove leading blanks
	skip_blanks(&ptr);

	// is it really a init string
	if (scan_char(&ptr) != 'i')
		goto reject;

	// parse init string, a CR is not allowed here
	if (skip_blanks_and_test_for_CR(&ptr))
		goto reject;

	// get BTR0BTR1
	if ((err = scan_unsigned_number(&ptr, &dwDummy)))
		goto reject;
	if (dwDummy > 0xFFFF)
		goto reject;

	Init->wBTR0BTR1 = (u16)dwDummy;
	Init->ucCANMsgType = 0;
	Init->ucListenOnly = 0;

	// optional rest, only 2 switches are possible
	for (i = 0; i < 2; i++) {
		if (skip_blanks_and_test_for_CR(&ptr))
			break;

		switch(scan_char(&ptr)) {
		case 's': break;
		case 'e': Init->ucCANMsgType |= MSGTYPE_EXTENDED; break;
		case 'l': Init->ucListenOnly |= 1; break;
		default:  break;
		}
	}

	// DPRINTK(KERN_DEBUG "%s: pcan_parse_input_init() is OK\n", DEVICE_NAME);
	return 0;

reject:
	// DPRINTK(KERN_DEBUG "%s: reject in pcan_parse_input_init()\n", DEVICE_NAME);
	return err;
}
