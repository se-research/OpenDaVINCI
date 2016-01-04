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
// bitratetest.c - a small program to test the calculation of the bitrates
//
// $Id: bitratetest.c 879 2015-07-20 08:37:44Z stephane $
//
//****************************************************************************

//----------------------------------------------------------------------------
// set here current release for this program
#define CURRENT_RELEASE "Release_20060501_a"

//****************************************************************************
// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h> 
#include <unistd.h>   // exit
#include <signal.h>
#include <string.h>
#include <stdlib.h>   // strtoul
#include <libpcan.h>
#include <src/common.h>
#include <ctype.h>

#ifdef XENOMAI
#include <native/task.h>
#include <native/timer.h>
#endif

//****************************************************************************
// DEFINES
#define DEFAULT_NODE "/dev/pcan0"

//****************************************************************************
// GLOBALS
HANDLE h = NULL;
const char *current_release;

//****************************************************************************
// LOCALS

//****************************************************************************
// CODE 
static void hlpMsg(void)
{
  printf("bitratetest - a small test the calculation of BTR0BTR1 data from pcan.\n");
  printf("usage:   bitratetest [-f=devicenode] [-?]\n");
  printf("         -f=devicenode - path to devicefile, default=%s\n", DEFAULT_NODE);
  printf("         -? or --help  - this help\n");
  printf("\n");
}

// centralized entry point for all exits
static void my_private_exit(int error)
{
  if (h)
  {
    print_diag("bitratetest");
    CAN_Close(h);
  }
  printf("bitratetest: finished (%d).\n\n", error);
  exit(error);
}

// here all is done
int main(int argc, char *argv[])
{
  char *ptr;
  int i;
  const char *szDeviceNode = DEFAULT_NODE;
  
  errno = 0;

  current_release = CURRENT_RELEASE;
  disclaimer("bitratetest");

  // decode command line arguments
  for (i = 1; i < argc; i++)
  {
    char c;

    ptr = argv[i];

    while (*ptr == '-')
      ptr++;
      
    c = *ptr;
    ptr++;

    if (*ptr == '=')
      ptr++;
      
    switch(tolower(c))
    {
    	case 'f':
				szDeviceNode = ptr;
				break;
			case '?':
      case 'h':
        hlpMsg();
	      my_private_exit(0);
	      break;
	      
	    default:
	      errno = EINVAL;
	      perror("bitratetest: unknown command line argument");
	      my_private_exit(errno);
	      break;
	   }
  }
  
  // open the CAN port
  // please use what is appropriate
  // HW_DONGLE_SJA 
  // HW_DONGLE_SJA_EPP
  // HW_ISA_SJA 
  // HW_PCI
  h = LINUX_CAN_Open(szDeviceNode, O_RDWR);

  if (h)
  {
    char txt[VERSIONSTRING_LEN];

    // get version info
    errno = CAN_VersionInfo(h, txt);
    if (!errno)
      printf("bitratetest: driver version = %s\n", txt);
    else
    {
      perror("bitratetest: CAN_VersionInfo()");
      my_private_exit(errno);
    }

    printf("\n");
    
    // calculate BTR0BTR1 from bitrates
    for (i = 1000000; i > 2500; i /= 2)
    {
    	if (i == 62500)
				i = 100000;
			if (i == 6250)
				i = 10000;
				
    	printf("bitratetest: %d bits/sec \t->BTR0BTR1=0x%04x\n", i + 1,  LINUX_CAN_BTR0BTR1(h, i + 1));
    	printf("             %d bits/sec \t->BTR0BTR1=0x%04x\n", i    ,  LINUX_CAN_BTR0BTR1(h, i));
    	printf("             %d bits/sec \t->BTR0BTR1=0x%04x\n", i - 1,  LINUX_CAN_BTR0BTR1(h, i - 1));
    };
    printf("\n");
  }
  else
  {
    errno = nGetLastError();
    perror("bitratetest: CAN_Open()");
  }
    
  my_private_exit(errno);
  
  return errno;
}
