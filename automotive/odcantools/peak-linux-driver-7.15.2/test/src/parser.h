#ifndef __PARSER_H__
#define __PARSER_H__

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
// parser.h - header of parser which parses the input file and put the messages 
//            into a list
//
// $Id: parser.h 360 2006-02-05 10:49:18Z klaus $
//
//****************************************************************************

//****************************************************************************
// INCLUDES
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <ctype.h>
#include <libpcan.h>
#include <list>

//****************************************************************************
// DEFINES

//****************************************************************************
// GLOBALS

//****************************************************************************
// LOCALS

//****************************************************************************
// CODE 

class parser
{
  public:
  parser(void);
  parser(const char *filename);
  ~parser(void);

  int nGetLastError(void);
  void setFileName(const char *filename);
  std::list<TPCANMsg> *Messages(void);
  
  private:
  void skip_blanks(char **ptr);
  int  skip_blanks_and_test_for_CR(char **ptr);
  int  scan_unsigned_number(char **ptr, __u32 *dwResult);
  char scan_char(char **ptr);
  int  parse_input_message(char *buffer, TPCANMsg *Message);
  
  const char *m_szFileName;
  int  m_nLastError;
  std::list<TPCANMsg> m_List;
};

#endif // __PARSER_H__

