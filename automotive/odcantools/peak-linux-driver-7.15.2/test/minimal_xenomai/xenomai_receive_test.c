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
// xeno_receive_test.c - minimalist xenomai receive test example (receive 5 messages and quit) 
//
// $Id: bitratetest.c 517 2007-07-09 09:40:42Z edouard $
//
//****************************************************************************

#include <stdlib.h>
#include <signal.h>
#include <sys/mman.h>
#include <native/task.h>
#include <libpcan.h>

RT_TASK test_task;
HANDLE can_handle = NULL;
TPCANRdMsg can_msg[5];

void test(void * arg)
{
	
	int i;
	for (i = 0; i < 5; i++) {
		LINUX_CAN_Read(can_handle, &can_msg[i]);
	}
}

void signal_handler(int status)
{
	rt_task_delete(&test_task);
	CAN_Close(can_handle);
	exit(0);
}

int main(int argc, char *argv[])
{
	int i, err;

	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);

	mlockall(MCL_CURRENT | MCL_FUTURE);

	can_handle = CAN_Open(HW_PCI, 1);
	CAN_Init(can_handle, CAN_BAUD_1M, CAN_INIT_TYPE_EX);
	printf("Status = %i\n", CAN_Status(can_handle));

	err = rt_task_create(&test_task, "test", 0, 99, T_JOINABLE);
	if (err) {
		printf("receivetest: Failed to create rt task, code %d\n",
			errno);
		return err;
	}
 	rt_task_start(&test_task, test, NULL);
	if (err) {
		printf("receivetest: Failed to start rt task, code %d\n",
			errno);
		return errno;
    	}
	rt_task_join(&test_task);

	for (i = 0; i < 5; i++) {
		printf("Frame = %08lx %02x %02x %02x %02x %02x %02x %02x %02x, "
			"Time diff = %llu ns\n",
			(unsigned long) can_msg[i].Msg.ID,
			can_msg[i].Msg.DATA[0],
			can_msg[i].Msg.DATA[1],
			can_msg[i].Msg.DATA[2],
			can_msg[i].Msg.DATA[3],
			can_msg[i].Msg.DATA[4],
			can_msg[i].Msg.DATA[5],
			can_msg[i].Msg.DATA[6],
			can_msg[i].Msg.DATA[7],
			(i == 0) ? 0 :
				(can_msg[i].dwTime*(unsigned long long)1000+can_msg[i].wUsec)*1000-
				(can_msg[i-1].dwTime*(unsigned long long)1000+can_msg[i-1].wUsec)*1000
		);
	}

	CAN_Close(can_handle);
	return 0;
}
