//****************************************************************************
// Copyright (C) 2001-2006  PEAK System-Technik GmbH
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
//****************************************************************************

//****************************************************************************
//
// parser.cpp - parses the input file and put the messages into a list
//
// $Id: parser.cpp 840 2015-03-13 10:45:33Z stephane $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <string>

#include <iostream>
#include <fstream>

#include <ctype.h>
#include <libpcan.h>
#include <src/parser.h>

//****************************************************************************
// DEFINES

//****************************************************************************
// GLOBALS

//****************************************************************************
// LOCALS

//****************************************************************************
// CODE

//----------------------------------------------------------------------------
// construct and destruct
parser::parser(void)
{
	m_szFileName = NULL;
	m_nLastError = 0;
}

parser::parser(const char *filename)
{
	m_szFileName = filename;
	m_nLastError = 0;
}

parser::~parser(void)
{
}

//----------------------------------------------------------------------------
// skip blanks and tabs
void parser::skip_blanks(char **ptr)
{
	// remove blanks or tabs
	while ((**ptr == ' ') || (**ptr == '\t'))
		(*ptr)++;
}

//----------------------------------------------------------------------------
// skip blanks, return 0 if the 1st non-blank char is not '\n'
int parser::skip_blanks_and_test_for_CR(char **ptr)
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
int parser::scan_unsigned_number(char **ptr, __u32 *dwResult)
{
	char *p = *ptr;

	*dwResult = strtoul(p, ptr, 0);

	if (p != *ptr)
		return 0;

	return ERANGE;
}

//----------------------------------------------------------------------------
// extract a char from a string
char parser::scan_char(char **ptr)
{
	return *(*ptr)++;
}

//----------------------------------------------------------------------------
// parses a message command
int parser::parse_input_message(char *buffer, TPCANMsg *Message)
{
	char *ptr = buffer;
	__u32 dwLen;
	__u32 dwDat;
	uint i;
	int err = EINVAL;

	// remove leading blanks
	skip_blanks(&ptr);

	// search for 'm' or 'r' to distinguish between message or remote transmit requests
	Message->MSGTYPE  = 0;
	switch (scan_char(&ptr)) {
	case 'M':  Message->MSGTYPE |= MSGTYPE_SELFRECEIVE;
	case 'm':  break; // normal message
	case 'R':  Message->MSGTYPE |= MSGTYPE_SELFRECEIVE;
	case 'r':  Message->MSGTYPE |= MSGTYPE_RTR; break; // rtr message

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
	Message->LEN = (__u8)dwLen;

	// read data elements up to message len
	i = 0;
	while (i < dwLen) {
		if (skip_blanks_and_test_for_CR(&ptr))
		goto reject;

		if ((err = scan_unsigned_number(&ptr, &dwDat)))
		  goto reject;
		if (dwDat > 255)
		  goto reject;
		Message->DATA[i] = (__u8)dwDat;

		i++;
	}
	return 0;

reject:
	return err;
}

//----------------------------------------------------------------------------
// returns the last error
int parser::nGetLastError(void)
{
	int error = m_nLastError;

	m_nLastError = 0;
	return error;
}

//----------------------------------------------------------------------------
// set the filename
void parser::setFileName(const char *filename)
{
	m_szFileName = filename;
}

//----------------------------------------------------------------------------
// returns the list of messages
std::list<TPCANMsg> *parser::Messages(void)
{
	std::list<TPCANMsg> *_local = &m_List;
	std::string    str;
	std::ifstream  input(m_szFileName);
	TPCANMsg       Message;

	if (!input) {
		m_nLastError = errno;
		return NULL;
	}

	while (!input.eof() && !input.fail()) {
		getline(input, str);

		if (!parse_input_message(const_cast<char *>(str.c_str()), &Message))
		  m_List.push_back(Message);
	}

	if (!input.eof() && input.fail()) {
		m_nLastError = errno;
		_local = NULL;
	}

	input.close();

#if 0 //------------- print out message, begin ----------------
	{
		list<TPCANMsg>::iterator iter;
		int i;

		for (iter = m_List.begin(); iter != m_List.end(); iter++) {
		  i = 0;

		  printf("%s: 0x%08x 0x%02x %d . ",
		    "transmitest", iter->ID, iter->MSGTYPE, iter->LEN);

		  while (i++ < iter->LEN)
		    printf("0x%02x ", iter->DATA[i]);

		  printf("\n");
		}
	}
#endif //------------- print out message, end -----------------

	return _local;
}
