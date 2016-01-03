//****************************************************************************
// Copyright (C) 2007  PEAK System-Technik GmbH
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
// filtertest.cpp - a simple program to test CAN filter settings
//
// $Id: filtertest.cpp 538 2008-02-15 16:06:45Z edouard $
//
//****************************************************************************

//----------------------------------------------------------------------------
// set here current release for this program
#define CURRENT_RELEASE "Release_20070211_a"  

//****************************************************************************
// INCLUDES
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <ctype.h>
#include <unistd.h>   // exit
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>    // O_RDWR

#include <src/common.h>
#include <libpcan.h>

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
  printf("filtertest - a small test program to test CAN filter settings together with PCAN chardev driver.\n");
  printf("usage:   filtertest [-f=devicenode] {{[-l=low_CAN_ID] [-h=highest_CAN_ID] [-m=MSGTYPE]} | {[-c]}} [-?]\n");
  printf("options: -f - devicenode - path to devicefile, default=%s\n", DEFAULT_NODE);
  printf("         -l - lowest CAN ID to pass, e.g, '-l=0x200' (default: 0).\n");
  printf("         -u - most upper CAN ID to pass, e.g. '-u=0x201' (default: 0x7FFFFFFF).\n");
  printf("         -m - message type to pass, see pcan.h, e.g. '-m=0x02' (default: 0x02 - MSGTYPE_EXTENDED).\n");
  printf("         -c - clear all filters.\n");
  printf("         -v - set verbose mode.\n");
  printf("         -? or --help - this help\n");
  printf("\n");
}

int main(int argc, char *argv[])
{
  char *ptr;
  int  i;
  int  err;
  
  const char  *szDevNode = DEFAULT_NODE;
  __u32 lower_ID = 0;
  __u32 upper_ID = CAN_MAX_EXTENDED_ID;
  __u8  msgtype  = MSGTYPE_EXTENDED;
  bool  verbose  = false;
  bool  clear    = false;

  errno = 0;

  current_release = CURRENT_RELEASE;
  disclaimer("filtertest");

  // decode command line arguments
  for (i = 1; i < argc; i++)
  {
    char c;

    ptr = argv[i];

    if (*ptr == '-')
    {
      while (*ptr == '-')
        ptr++;

      c = *ptr;
      ptr++;

      if (*ptr == '=')
        ptr++;

      switch(tolower(c))
      {
        case 'f':
          szDevNode = ptr;
          break;
        case 'l':
          lower_ID = strtoul(ptr, NULL, 16);
          break;
        case 'u':
          upper_ID = strtoul(ptr, NULL, 16);
          break;
        case 'm':
          msgtype = (__u8)strtoul(ptr, NULL, 16);
          break;
        case 'v':
          verbose = true;
          break;
        case 'c':
          clear = true;
          break;
        case '?': 
        case 'h':
          hlpMsg();
          errno = 0;
          goto error;
          break;
        default:
          errno = EINVAL;
          printf("filtertest: unknown command line argument (%s)\n", ptr);
          errno = -1;
          goto error;
          break;
      }
    }
    else
    {
      printf("filtertest: unknown command line argument (%s)\n", ptr);
      errno = -1;
      goto error;
    }
  }
  
  if (verbose)
  {
    printf("filtertest: device-node = %s\n", szDevNode);
    if (clear)
      printf("filtertest: clear the filter chain.\n");
    else
    {
      printf("filtertest: lowest CAN ID to pass      = 0x%08x\n", lower_ID);
      printf("filtertest: highest CAN ID to pass     = 0x%08x\n", upper_ID);
      printf("filtertest: message type flags to pass = 0x%02x\n", msgtype);
    }    
  }
  
  // open path to device
  h = LINUX_CAN_Open(szDevNode, O_RDWR);
  
  // get driver version info
  if ((!h) && (verbose))
  {
    perror("filtertest: LINUX_CAN_Open()");
    goto error;
  }
  else
  {
    char txt[VERSIONSTRING_LEN];
    
    // clear status
    CAN_Status(h);
   
    // get version info
    errno = CAN_VersionInfo(h, txt);
    if (!errno)
      printf("filtertest: driver version = %s\n", txt);
    else
    {
      perror("filtertest: CAN_VersionInfo()");
      goto error;
    }
  }
  
  // clear or set filter criteria
  if (clear)
  {
    err = CAN_ResetFilter(h);
    if (err)
    {
      errno = err;
      perror("filtertest: CAN_ResetFilter()");
      goto error;
    }
  }
  else
  {
    err = CAN_MsgFilter(h, lower_ID, upper_ID, msgtype);
    if (err)
    {
      errno = err;
      perror("filtertest: CAN_MsgFilter()");
      goto error;
    }
  }
  
  error:
    if (h)
      CAN_Close(h);
      return errno;
}
