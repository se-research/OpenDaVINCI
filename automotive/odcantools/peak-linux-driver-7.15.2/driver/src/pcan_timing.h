//****************************************************************************
// Copyright (C) 2003-2011  PEAK System-Technik GmbH
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
// Maintainer(s): Stephane Grosjean (s.grosjean@peak-system.com)
//
//****************************************************************************

//****************************************************************************
//
// pcan_timing.h - timing/baudrate conversion facilities
//
// $Id: pcan_timing.h 615 2010-02-14 22:38:55Z khitschler $
//
//****************************************************************************

#ifndef __pcan_timing_h__
#define __pcan_timing_h__

#include <linux/types.h>

#define kHz                            1000
#define MHz                            (1000*kHz)
#define GHz                            (1000*MHz)

/* Hardware-independent description of a baud rate */
struct pcan_timing_abstract
{
	uint32_t   prescaler;  // the following values are for this prescaler

	uint32_t   sync_seg_ns;// Duration of sync segment
	uint32_t   tseg1_ns;   // Duration sync to sample point
	uint32_t   tseg2_ns;   // Duration sample point to end-of-bit
	uint32_t   sjw_ns;     // tollerance for timing. 
	                       // either tseg is extended by max. sjw,
	                       // or tseg2 is reduced by max sjw.
	// Info only
	uint32_t   info_baudrate;
	uint32_t   info_delta_baudrate; // calcualted from sjw
	//uint32_t   sjw_ns;              // in Nanosecs
	uint8_t    sample3;             // similar to SAM: 1=3 samples. 0=1 sample
	//uint8_t    samplingpoint;      // in %, 1..100
};

/* Parameter limits for baud rate timing on a given CAN-controller */
struct pcan_timing_capabilities
{
	uint32_t   max_tseg1;
	uint32_t   min_tseg1;
	uint32_t   max_tseg2;
	uint32_t   min_tseg2;
	uint32_t   max_sjw;
	uint32_t   min_sjw;
	/* uint32_t   max_prescaler; */
	uint32_t   max_brp;
	uint32_t   min_brp;

	uint32_t   intern_prescaler; // if sysclock is divided before reaching 
	                             // the prescaler.
};

/* Baud rate parameter for a SJA1000 */
struct pcan_timing_baudrate
{
	// coded regsiter values
	uint16_t    SJW;        // syncronization jump width. 1..4
	// Unit: Periods starting with CAN-Systemclock
	uint16_t    BRP;        // Baudrate-prescaler 1..64.
	// CAN-SystemClock  = 2 * Prescale / quartz_frequency
	uint8_t     SAM;        // Sampling (1 = 3x, 0= 1x)
	uint16_t    TSEG1;      // 1..16
	uint16_t    TSEG2;      // 1..8

	uint32_t   can_systemclock;    // ABse clock for assembly of bit timings
};

/* Controller timing capabilities */
extern const struct pcan_timing_capabilities sja1000_capabilities;

void pcan_BTR0BTR1_to_abstract(uint16_t, struct pcan_timing_abstract *);
int pcan_abstract_to_sja(const struct pcan_timing_capabilities *,
                          struct pcan_timing_abstract *,
                          uint32_t,
                          struct pcan_timing_baudrate *);
int pcan_timing_convert_br_settings(const struct pcan_timing_capabilities *,
                                    struct pcan_timing_abstract *,
                                    uint32_t,
                                    struct pcan_timing_abstract *);

#endif // __pcan_timing_h__
