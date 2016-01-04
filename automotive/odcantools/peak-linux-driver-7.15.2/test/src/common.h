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
// common.h - the header for common parts for transmittest and receivetest
//
// $Id: common.h 538 2008-02-15 16:06:45Z edouard $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <libpcan.h> 

//****************************************************************************
// DEFINES

//****************************************************************************
// GLOBALS
extern HANDLE h;
extern const char *current_release;

//****************************************************************************
// LOCALS

//****************************************************************************
// PROTOTYPES
#ifdef __cplusplus
extern "C" 
{
#endif

// print out GPL disclaimer
void disclaimer(const char *prgName);

// print out the contents of a CAN message  
void print_message(TPCANMsg *m);

// lookup for HW_... constant out of device type string
int getTypeOfInterface(char *szTypeName);

// the opposite: lookup for device string out of HW_.. constant
char *getNameOfInterface(int nType);

// print out device and channel diagnostics
void print_diag(const char *prgName);

#ifdef __cplusplus
}
#endif

