//****************************************************************************
// Copyright (C) 2001-2009  PEAK System-Technik GmbH
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
// common part between no-realtime and realtime
// receivetest_common.c - a small program to test the receive features of pcan driver 
//                 and the supporting shared library
//
// $Id: receivetest.c 539 2008-02-15 18:16:12Z edouard $
//
//****************************************************************************

// set here current release for this program
#define CURRENT_RELEASE "Release_20141203_r"

//****************************************************************************
// INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   // exit
#include <signal.h>
#include <string.h>
#include <stdlib.h>   // strtoul
#include <fcntl.h>    // O_RDWR
#include <libpcan.h>
#include <src/common.h>
#include <ctype.h>

//****************************************************************************
// DEFINES

#define DEFAULT_NODE "/dev/pcan0"
#ifndef bool
	#define bool  int
	#define true  1
	#define false 0
#endif

//****************************************************************************
// CODE

#include <sys/mman.h>

#ifdef XENOMAI
#include <native/task.h>
#include <native/timer.h>
#endif

#ifdef RTAI
#include <sys/poll.h>
#include <rtai_lxrt.h>
#endif

//****************************************************************************
// DEFINES

#define STATE_FILE_OPENED         1
#define STATE_TASK_CREATED        2
#define SET_INIT_STATE(new_state) current_state |= new_state
#define RESET_INIT_STATE(new_state) current_state &= ~new_state
//****************************************************************************
// GLOBALS
HANDLE h;
const char *current_release;
unsigned int current_state = 0;
int shutdownnow = 0;

#ifdef XENOMAI
RT_TASK reading_task;
#endif

#ifdef RTAI
RT_TASK *reading_task;
RT_TASK *mainr;
static pthread_t reading_thr;
#endif

void install_signal(void);

//****************************************************************************
// CODE

void do_exit(int error)
{
	if (current_state & STATE_FILE_OPENED) {
		print_diag("receivetest");
		CAN_Close(h);
		RESET_INIT_STATE(STATE_FILE_OPENED);
	}

#ifdef XENOMAI
	if (current_state & STATE_TASK_CREATED) {
		rt_task_delete(&reading_task);
		RESET_INIT_STATE(STATE_TASK_CREATED);
	}
#endif

#ifdef RTAI
	pthread_join(reading_thr, NULL);
	if (current_state & STATE_TASK_CREATED) {
		RESET_INIT_STATE(STATE_TASK_CREATED);
	}
	rt_task_delete(mainr);
#endif
}

void signal_handler(int unused)
{
	/* re-install signal handler */
	/* let main() executes after pause() */
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
}

//----------------------------------------------------------------------------
// real time task
void reading_task_proc(void *arg)
{
	TPCANMsg m;
	__u32 status;
	
#ifdef RTAI
	reading_task = rt_task_init_schmod(nam2num("RDTSK"), 1, 0, 0, SCHED_FIFO, 0xF);
	rt_make_hard_real_time();
#endif
	
	while (1) {
		if ((errno = CAN_Read(h, &m))) {
			shutdownnow = 1;
		} else {
			// check if a CAN status is pending
			if (m.MSGTYPE & MSGTYPE_STATUS) {
				status = CAN_Status(h);
				if ((int)status < 0) {
					shutdownnow = 1;
				}
			}
		}
		if (shutdownnow == 1)
			break;
	}
#ifdef RTAI
	rt_make_soft_real_time();
	rt_task_delete(reading_task);
#endif
}

int init()
{
	mlockall(MCL_CURRENT | MCL_FUTURE);
	/* Initialize LXRT */
#ifdef RTAI
	mainr = rt_task_init_schmod(nam2num("MAINR"), 3, 0, 0, SCHED_FIFO, 0xF);
#endif 
}

// start reading task
int read_loop(void)
{
#ifdef XENOMAI
	errno = rt_task_create(&reading_task,NULL,0,50,0);
	if (errno) {
		printf("receivetest: Failed to create rt task, code %d\n",errno);
		return errno;
	}
	errno = rt_task_start(&reading_task,&reading_task_proc,NULL);
	if (errno) {
		printf("receivetest: Failed to start rt task, code %d\n",errno);
		return errno;
	}
#endif

#ifdef RTAI
	errno = pthread_create(&reading_thr, NULL, (void *)reading_task_proc, NULL);
	if (errno) {
		printf("receivetest: Failed to create and start rt task, code %d\n",errno);
		return errno;
	}
#endif

	SET_INIT_STATE(STATE_TASK_CREATED);
	printf("receivetest: reading data from CAN ... (press Ctrl-C to exit)\n");

	pause();
	
	printf("transmitest: finishing\n");
	do_exit(0);
	
	return 0;
}

static void hlpMsg(void)
{
	printf("receivetest - a small test program which receives and prints CAN messages.\n");
	printf("usage:   receivetest {[-f=devicenode] | {[-t=type] [-p=port [-i=irq]]}} [-b=BTR0BTR1] [-e] [-?]\n");
	printf("options: -f - devicenode - path to devicefile, default=%s\n", DEFAULT_NODE);
	printf("         -t - type of interface, e.g. 'pci', 'sp', 'epp', 'isa', 'pccard' or 'usb' (default: pci).\n");
	printf("         -p - port in hex notation if applicable, e.g. 0x378 (default: 1st port of type).\n");
	printf("         -i - irq in dec notation if applicable, e.g. 7 (default: irq of 1st port).\n");
	printf("         -b - BTR0BTR1 code in hex, e.g. 0x001C (default: 500 kbit).\n");
	printf("         -e - accept extended frames. (default: standard frames)\n");
	printf("         -? or --help - this help\n");
	printf("\n");
}

// here all is done
int main(int argc, char *argv[])
{
	char *ptr;
	int i;
	int nType = HW_PCI;
	__u32 dwPort = 0;
	__u16 wIrq = 0;
	__u16 wBTR0BTR1 = 0;
	int nExtended = CAN_INIT_TYPE_ST;
	const char  *szDevNode = DEFAULT_NODE;
	bool bDevNodeGiven = false;
	bool bTypeGiven = false;
	char txt[VERSIONSTRING_LEN];

	errno = 0;

	current_release = CURRENT_RELEASE;
	disclaimer("receivetest");

	init();

	// decode command line arguments
	for (i = 1; i < argc; i++) {
		char c;

		ptr = argv[i];

		while (*ptr == '-')
			ptr++;

		c = *ptr;
		ptr++;

		if (*ptr == '=')
			ptr++;

		switch(tolower(c)) {
		case 'f':
			szDevNode = ptr;
			bDevNodeGiven = true;
			break;
		case 't':
			nType = getTypeOfInterface(ptr);
			if (!nType){
				errno = EINVAL;
				printf("receivetest: unknown type of interface!\n");
				goto error;
			}
			bTypeGiven = true;
			break;
		case 'p':
			dwPort = strtoul(ptr, NULL, 16);
			break;
		case 'i':
			wIrq = (__u16)strtoul(ptr, NULL, 10);
			break;
		case 'e':
			nExtended = CAN_INIT_TYPE_EX;
			break;
		case '?':
		case 'h':
			hlpMsg();
			goto error;
			break;
		case 'b':
			wBTR0BTR1 = (__u16)strtoul(ptr, NULL, 16);
			break;
		default:
			errno = EINVAL;
			perror("receivetest: unknown command line argument!\n");
			goto error;
			break;
		}
	}

	// simple command input check
	if (bDevNodeGiven && bTypeGiven){
		errno = EINVAL;
		perror("receivetest: device node and type together is useless");
		goto error;
	}

	// give some information back
	if (!bTypeGiven){
		printf("receivetest: device node=\"%s\"\n", szDevNode);
	} else {
		printf("receivetest: type=%s", getNameOfInterface(nType));
		switch (nType) {
		case HW_USB:
		case HW_USB_PRO:
		case HW_USB_FD:
		case HW_USB_PRO_FD:
			if (dwPort)
				printf(", %d. device\n", dwPort);
			else
				printf(", standard device\n");
			break;
		default:
			if (dwPort) {
				if (nType == HW_PCI)
					printf(", %d. PCI device", dwPort);
				else
					printf(", port=0x%08x", dwPort);
			} else
				printf(", port=default");

			if ((wIrq) && !(nType == HW_PCI))
				printf(" irq=0x%04x\n", wIrq);
			else
				printf(", irq=default\n");
			break;
		}
	}

	if (nExtended == CAN_INIT_TYPE_EX)
		printf("             Extended frames are accepted");
	else
		printf("             Only standard frames are accepted");
	if (wBTR0BTR1)
		printf(", init with BTR0BTR1=0x%04x\n", wBTR0BTR1);
	else
		printf(", init with 500 kbit/sec.\n");

	/* install signal handlers */
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);

	/* open CAN port */
	if ((bDevNodeGiven) || (!bDevNodeGiven && !bTypeGiven)) {
		h = LINUX_CAN_Open(szDevNode, O_RDWR);
		if (h)
			SET_INIT_STATE(STATE_FILE_OPENED);
		else {
			printf("receivetest: can't open %s\n", szDevNode);
			goto error;
		}
	} else {
		// please use what is appropriate  
		// HW_DONGLE_SJA 
		// HW_DONGLE_SJA_EPP 
		// HW_ISA_SJA 
		// HW_PCI 
		h = CAN_Open(nType, dwPort, wIrq);
		if (h)
			SET_INIT_STATE(STATE_FILE_OPENED);
		else {
			printf("receivetest: can't open %s device.\n",
				getNameOfInterface(nType));
			goto error;
		}
	}

	/* clear status */
	//  CAN_Status(h);

	 // get version info
	errno = CAN_VersionInfo(h, txt);
	if (!errno)
		printf("receivetest: driver version = %s\n", txt);
	else {
		perror("receivetest: CAN_VersionInfo()");
		goto error;
	}

	// init to a user defined bit rate
	if (wBTR0BTR1) {
		errno = CAN_Init(h, wBTR0BTR1, nExtended);
		if (errno) {
			perror("receivetest: CAN_Init()");
			goto error;
		}
	}
	errno = read_loop();
	if (!errno)
		return 0;

error:
	do_exit(errno);
	return errno;
}
