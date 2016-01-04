/*****************************************************************************
 * Copyright (C) 2010  PEAK System-Technik GmbH
 *
 * linux@peak-system.com
 * www.peak-system.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Maintainer(s): Klaus Hitschler (klaus.hitschler@gmx.de)
 *****************************************************************************/

/*****************************************************************************
 * pcan-settings.c - a small program to get and set various parameters of
 * PCAN interfaces
 *
 * $Id: pcan-settings.c 809 2014-12-09 15:36:04Z stephane $
 *
 *****************************************************************************/

/* set here current release for this program */
#define CURRENT_RELEASE	"Release_20140822_n"
#define PRGNAME		"pcan-settings"

#define USES_32BITS_DEVICENO

/*
 * INCLUDE
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>	/* exit */
#include <signal.h>
#include <string.h>
#include <stdlib.h>	/* strtoul */
#include <fcntl.h>	/* O_RDWR */
#include <pcan.h>	/* this program does not use libpcan */
#include <src/common.h>
#include <ctype.h>
#include <popt.h>
#include <err.h>

/*
 * DEFINES
 */
#define DEFAULT_NODE	"/dev/pcan32"  /* currently only USB settings */
#ifndef bool
#define bool		int
#define true		1
#define false		0
#endif

/* a help to get command line interpretation separated from control */
#define SERIALNO	1
#define DEVICENO	2
#define VERBOSE		4

/*
 * GLOBALS
 */
int getSerialNumber(int nFileNo, int *pserialNo)
{
	int err;
	TPEXTRAPARAMS params;

	params.nSubFunction = SF_GET_SERIALNUMBER;

	err = ioctl(nFileNo, PCAN_EXTRA_PARAMS, &params);

	if (!err)
		*pserialNo = params.func.dwSerialNumber;

	return err;
}

int getDeviceNumber(int nFileNo, __uint32_t *pdeviceNo)
{
	int err;
	TPEXTRAPARAMS params;

	params.nSubFunction = SF_GET_HCDEVICENO;

	err = ioctl(nFileNo, PCAN_EXTRA_PARAMS, &params);

	if (!err)
#ifndef USES_32BITS_DEVICENO
		*pdeviceNo = (__uint32_t )params.func.ucHCDeviceNo;
#else
		*pdeviceNo = (__uint32_t )params.func.dwSerialNumber;
#endif
	return err;
}

int setDeviceNumber(int nFileNo, __uint32_t deviceNo)
{
	TPEXTRAPARAMS params;

	params.nSubFunction = SF_SET_HCDEVICENO;
#ifndef USES_32BITS_DEVICENO
	params.func.ucHCDeviceNo = (BYTE) deviceNo;
#else
	params.func.dwSerialNumber = (DWORD )deviceNo;
#endif
	return ioctl(nFileNo, PCAN_EXTRA_PARAMS, &params);
}

/* start here */
int main(int argc, char *argv[])
{
	int ret = 0;
	char *szDevNode = DEFAULT_NODE;
	char *szSerialNo = "";
	unsigned int serialNo = 0;
	__uint32_t deviceNo = 0;
	poptContext context;
	int result = 0;
	int verbose = false;
	int deviceArgSet;

	errno = 0;

	/* interpret command line */
	struct poptOption cmdLineOpts[] = {
		{ "deviceNode", 'f',
			POPT_ARG_STRING | POPT_ARGFLAG_SHOW_DEFAULT,
			&szDevNode, 0,
			"set path to PCAN device",
			"'device file path'"
		},
		{ "SerialNo", 's',
			POPT_ARG_NONE,
			NULL, SERIALNO,
			"get serial No",
			"'non-volatile serial number'"
		},
		{ "DeviceNo", 'd',
			POPT_ARG_INT | POPT_ARGFLAG_OPTIONAL,
			&deviceNo, DEVICENO,
			"get or set device No",
			"'non-volatile device number'"
		},
		{ "verbose", 'v',
			POPT_ARG_NONE,
			NULL, VERBOSE,
			"make it verbose",
			"verbose"
		},
		POPT_AUTOHELP
		POPT_TABLEEND
	};

	context = poptGetContext(PRGNAME, argc, (const char ** )argv,
								cmdLineOpts, 0);
	while ((ret = poptGetNextOpt(context)) >= 0) {
		result |= ret;
		switch (ret) {
		case SERIALNO:
			break;
		case DEVICENO:
			deviceArgSet = (poptGetOptArg(context)) ? true : false;
			break;
		case VERBOSE:
			verbose = true;
			break;
		}
	}

	errno = EINVAL;
	result &= ~VERBOSE; /* remove possible VERBOSE from result */

	/* some sanity checks */
	/* 1st illegal command line switches */
	if (ret < -1)
		err(errno, "illegal command line switches %s",
			poptBadOption(context, POPT_BADOPTION_NOALIAS));

	/* 2nd: only a device node given */
	if (!result) {
		poptPrintUsage(context, stderr, 0);
		err(errno, "more than a device node required");
	}

	/* do what was intended to do */
	ret = 0;
	if (result) {
		int nFileNo;

		/* open path to device */
		if ((nFileNo = open(szDevNode, O_RDWR)) == -1)
			err(errno, "%s", szDevNode);

		/* get serial number */
		if ((result & SERIALNO) && !ret) {
			ret = getSerialNumber(nFileNo, &serialNo);
			if (!ret) {
				if (verbose)
					printf("%s: SerialNumber is 0x%08x\n",
						PRGNAME, serialNo);
				else
					printf("0x%08x\n", serialNo);
			}
		}

		/* set or get device number */
		if ((result & DEVICENO) && !ret) {
			/* argument given, set value */
			if (deviceArgSet) {
				ret = setDeviceNumber(nFileNo, deviceNo);
				if ((verbose) && !ret)
					printf("%s: DeviceNumber set to %u\n",
						PRGNAME, deviceNo);
			} else {
				ret = getDeviceNumber(nFileNo, &deviceNo);
				if (!ret)
					if (verbose)
						printf("%s: DeviceNumber is %u\n",
							PRGNAME, deviceNo);
					else
						printf("%u\n", deviceNo);
			}
		}

		/* close path to device */
		close(nFileNo);
	}

	if (ret < 0)
		err(errno, "configuration @ set or get");

	poptFreeContext(context);
	return errno;
}
