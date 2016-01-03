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
// pcan_timing.c - timing abstraction facilities
//
// $Id: pcan_timing.c 615 2011-02-10 22:38:55Z stephane $
//
//****************************************************************************

#undef DEBUG
//#define DEBUG

//****************************************************************************
// INCLUDES

#include <linux/kernel.h>
#include <linux/string.h>              // memset()
#include <src/pcan_common.h>
#include <src/pcan_timing.h>
#include <asm/div64.h>


#define PENALTY_INVALID                0x7fffffff

/* Info about an analysed baud rate */
struct pcan_timing_parameters
{
	// Preconditions
	uint32_t   sysclock;       // here a constant
	uint32_t   tBit_ns;        // requested duration of a CAN-Bits in nanosesc

	// Result values
	uint16_t    tseg1, tseg2;  // in tSCL_ps
	uint16_t    sjw;
	uint16_t    prescaler;

	// Auxilliary values
	uint32_t   tSCL_ps;        // Duration of a Time Quantums in picosecs

	// calculated values
	uint32_t   baudrate;
	uint32_t   tseg1_ns, tseg2_ns, sjw_ns; // Segments in nNanosecs

	uint32_t   penalty;        // "penalty points" for this baud rate, 
	                           // if it does not hit the optimum
};

/* Public timing capabilites */
const struct pcan_timing_capabilities sja1000_capabilities =
{
   .max_brp = 128,
   .min_brp = 1,
   .max_tseg1 = 16,
   .min_tseg1 = 2,	/* constant for v <= 7.13 */
   .max_tseg2 = 8,
   .min_tseg2 = 2,	/* constant for v <= 7.13 */
   .max_sjw = 4,
   .min_sjw = 1,
   .intern_prescaler = 2
};

#define DIV_ROUND(a,b)                 (((a)+(b)/2)/(b))

#ifdef CONFIG_64BIT
typedef uint64_t                       big_t;
#define pcan_timing_div_64(a,b)        (a/b)
#define DIV_ROUND64(a,b)               DIV_ROUND(a,b)

#else

/* Running 32-bits arch forces using do_div() *BUT* this enables only to */
/* divide uint64_t by uint32_t and, unfortunately, some division operations */
/* below need uint64_t / uint64_t... */
/* But, some dividend and/or divisor could be (very) smaller if we were using */
/* quartz frequencies in MHz value instead of Hz values */
/* Then, for the moment, PCAN_TIMING_DIV64_WORKAROUND *MUST* be defined */
/* The only limitation is that these quartz frequencies *MUST* be multiple of */
/* 1xMHz... */

#define PCAN_TIMING_DIV64_WORKAROUND

/*
 * uint32_t pcan_timing_div_64(uint64_t a, uint32_t b)
 */
static inline uint32_t pcan_timing_div_64(uint64_t a, uint32_t b)
{
	do_div(a, b);
	return a;
}

/*
 * inline uint32_t DIV_ROUND64(uint64_t a, uint32_t b)
 *
 * Use this *ONLY* when divisor is certain to be a 32-bits value...
 */
static inline uint32_t DIV_ROUND64(uint64_t a, uint32_t b)
{
	uint64_t x = a + (b >> 1);
	return pcan_timing_div_64(x, b);
}

#ifndef PCAN_TIMING_DIV64_WORKAROUND
typedef uint64_t                       big_t;
#else
typedef uint32_t                       big_t;
#endif

#endif

#ifdef DEBUG
static void debug_pcan_timing_parameters(char *prompt,
                                         struct pcan_timing_parameters *ptp)
{
	DPRINTK(KERN_DEBUG "%s: sysclock=%u tBit_ns=%u tseg1=%u tseg2=%u sjw=%u "
	                   "prescaler=%u tSCL_ps=%u baudrate=%u tseg1_ns=%u "
	                   "tseg2_ns=%u sjw_ns=%u penalty=%u\n",
	                   prompt, ptp->sysclock, ptp->tBit_ns, ptp->tseg1, 
	                   ptp->tseg2, ptp->sjw, ptp->prescaler, ptp->tSCL_ps, 
	                   ptp->baudrate, ptp->tseg1_ns, ptp->tseg2_ns, ptp->sjw_ns,
	                   ptp->penalty);
}

static void debug_pcan_timing_abstract(char *prompt,
                                       struct pcan_timing_abstract *pta)
{
	DPRINTK(KERN_DEBUG "%s: prescaler=%u sync_seg_ns=%u tseg1_ns=%u "
	                   "tseg2_ns=%u sjw_ns=%u info_baudrate=%u "
	                   "info_delta_baudrate=%u sample3=%u\n",
	                   prompt, pta->prescaler, pta->sync_seg_ns, pta->tseg1_ns, 
	                   pta->tseg2_ns, pta->sjw_ns, pta->info_baudrate,
	                   pta->info_delta_baudrate, pta->sample3);
}

static void debug_pcan_timing_baudrate(char *prompt,
                                       struct pcan_timing_baudrate *ptb)
{
	DPRINTK(KERN_DEBUG "%s: SJW=%u TSEG1=%u TSEG2=%u BRP=%u SAM=%u "
	                   "can_systemclock=%u\n", 
	                   prompt, ptb->SJW, ptb->TSEG1, ptb->TSEG2, 
	                   ptb->BRP, ptb->SAM, ptb->can_systemclock);
}

#define __debug_pcan_timing_parameters(a) debug_pcan_timing_parameters(#a,&a)
#define __debug_pcan_timing_abstract(a)   debug_pcan_timing_abstract(#a,&a)
#define __debug_pcan_timing_baudrate(a)   debug_pcan_timing_baudrate(#a,&a)
#else
#define __debug_pcan_timing_parameters(a)
#define __debug_pcan_timing_abstract(a)
#define __debug_pcan_timing_baudrate(a)
#endif


/*
 * void pcan_timing_decode_baudrate(uint32_t fquartz,
 *                                  uint16_t btr0btr1,
 *                                  struct pcan_timing_baudrate *sja1000bt)
 *
 *      Decodes BTR0BTR1-value of a SJA1000 with given base clock
 *      "Register value -> TCANControllerChip_SJA1000__BaudrateTiming"
 */
static
void pcan_timing_decode_baudrate(uint32_t fquartz,
                                 uint16_t btr0btr1,
                                 struct pcan_timing_baudrate *sja1000bt)
{
	uint8_t btr0, btr1;

	btr0 = btr0btr1 >> 8;
	btr1 = btr0btr1 & 0xFF;

	sja1000bt->SJW = ((btr0 >> 6) & 0x03) + 1;
	sja1000bt->TSEG1 = (btr1 & 0x0f) + 1;
	sja1000bt->TSEG2 = ((btr1 >> 4) & 0x07) + 1;
	sja1000bt->BRP = (btr0 & 0x3f) + 1;
	sja1000bt->SAM = btr1 >> 7;
	sja1000bt->can_systemclock = fquartz;       // "division by 2" is used on 
	                                            // all references to BRP
	__debug_pcan_timing_baudrate(*sja1000bt);	
}

/*
 * void pcan_timing_sja_to_abstract(const struct pcan_timing_capabilities *cap,
 *                                  struct pcan_timing_baudrate *sja1000bt,
 * 	                              struct pcan_timing_abstract *abt)
 *
 * Convert a SJA1000 baud rate to abstract baudrate
 */
static 
void pcan_timing_sja_to_abstract(const struct pcan_timing_capabilities *cap,
                                 struct pcan_timing_baudrate *sja1000bt,
                                 struct pcan_timing_abstract *abt)
{
	const uint32_t sysclock_MHz = sja1000bt->can_systemclock / MHz;

	abt->prescaler = sja1000bt->BRP * cap->intern_prescaler;

	abt->sync_seg_ns = \
	   DIV_ROUND( abt->prescaler*kHz, sysclock_MHz);

	abt->tseg1_ns = \
	   DIV_ROUND((abt->prescaler * sja1000bt->TSEG1)*kHz, sysclock_MHz);

	abt->tseg2_ns = \
	   DIV_ROUND((abt->prescaler * sja1000bt->TSEG2)*kHz, sysclock_MHz);

	abt->sjw_ns = \
	   DIV_ROUND((abt->prescaler * sja1000bt->SJW)*kHz, sysclock_MHz);

	abt->info_baudrate = \
	   DIV_ROUND(sja1000bt->can_systemclock,
	             abt->prescaler * (1 + sja1000bt->TSEG1 + sja1000bt->TSEG2));

	abt->info_delta_baudrate = \
	   abs(  abt->info_baudrate 
	       - DIV_ROUND(sja1000bt->can_systemclock,
	                   abt->prescaler * (1 + sja1000bt->TSEG1
	                                       + sja1000bt->TSEG2
	                                       + sja1000bt->SJW)));
	abt->sample3 = sja1000bt->SAM;

	__debug_pcan_timing_abstract(*abt);
}

/*
 * int pcan_timing_convert_br_settings()
 *
 *  Calculates from requested baudrate, base clock and SJW
 *  values for prescaler, sjw, tseg1 und tseg2.
 *  Position of smapling point is given in percent (%), 
 *  0% = earliest possible point.
 *  100% = latestest possible point in time.
 *  Return:
 *      1 = good values for prescale, tseg1, tseg2 could be calculated
 *      0 = requested baudrate not possible
 *
 *  Ref: "Applicatiuon Note AN97046: Determination of Bit Timing Parameters 
 *       for the CAN Controller SJA1000", Philips Semiconductors.
 */
int pcan_timing_convert_br_settings(const struct pcan_timing_capabilities *cap,
                                    struct pcan_timing_abstract *abt_org,
                                    uint32_t sysclock,
                                    struct pcan_timing_abstract *abt_result)
{
	// Calculate baud rate values. baudrate = bits per second 
	// (e.g. "500000" for 500kBaud).
	uint16_t NBT;        // Count of timequanta = tSCL per tBit
	struct pcan_timing_parameters cur_baudrate;     // Calculation sheet for 
	                                                // current calculation
	struct pcan_timing_parameters best_baudrate;    // Calculation sheet with 
	                                                // best result so far.

	// Simply to remove "may be used uninitialized" warnings...
	memset(&best_baudrate, '\0', sizeof(best_baudrate));

	best_baudrate.penalty = PENALTY_INVALID;    // mark as invalid
	cur_baudrate.sysclock = sysclock;           // nominal clock

#ifdef PCAN_TIMING_DIV64_WORKAROUND
	/* to avoid div64 arithmetic: do_div() only does u64/u32 */
	sysclock /= MHz;
#endif

	__debug_pcan_timing_abstract(*abt_org);

	// = 2000 ns for 500kBaud , 80000 ns for 125 kBaud
	/* note: 1xGHz < 2^32 < 5xGHz */
	cur_baudrate.tBit_ns = DIV_ROUND(1*GHz, abt_org->info_baudrate);

	// Iterate over all combination of "time quanta" und "sjw".
	// Find optimal combination of neu.tseg1, neu.tseg2 and neu.sjw
	// with minimal difference of tseg1, tseg2 and sjw to nominal value.
	for (NBT=(cap->max_tseg1+cap->max_tseg2+1); NBT >= 4; NBT--)
	{
		// prescale = tSCL_ns[ns] / tClk [ns] =  tSCL_ns[ns] * fClk / 10e9
		// = tSCL_ns[] * fClk[MHz] / 1000
		//        *prescale = (uint16_t) (tSCL_ns * fClkMHz / 1000) ;      
		// Bsp: prescale = 125*8/1000 = 1
		// timequanta as bittime/NBT, because of integer rounding errors
#ifdef PCAN_TIMING_DIV64_WORKAROUND
		cur_baudrate.prescaler = DIV_ROUND(cur_baudrate.tBit_ns * sysclock,
				                             NBT*kHz);
		DPRINTK(KERN_DEBUG "prescaler=%u/%u=%u\n",
		        cur_baudrate.tBit_ns * sysclock, NBT*kHz,
		        cur_baudrate.prescaler);
#else
		cur_baudrate.prescaler = DIV_ROUND((big_t)cur_baudrate.tBit_ns * sysclock,
				                             (big_t)NBT*GHz);
		DPRINTK(KERN_DEBUG "prescaler=%llu/%llu=%u NBT=%u GHz=%u\n",
		        (big_t )cur_baudrate.tBit_ns * sysclock, (big_t )NBT*GHz,
		        cur_baudrate.prescaler,
		        NBT, GHz);
#endif

		// prescale==0: baud rate can not be constructed.
		if (  (cur_baudrate.prescaler < cap->min_brp)
		   || (cur_baudrate.prescaler > cap->max_brp)
		   )
		{
			DPRINTK(KERN_DEBUG "%s: %s(): loop1: cap->max_brp=%u\n", 
			        DEVICE_NAME, __FUNCTION__, cap->max_brp);
			__debug_pcan_timing_parameters(cur_baudrate);
			continue;
		}

		// prescaler must be an integer multiple of the internal  pre-rpescaler
		if ((cur_baudrate.prescaler % cap->intern_prescaler) != 0)
		{
			// prescaler can not be set correctly
			DPRINTK(KERN_DEBUG "%s: %s(): loop2: cap->intern_prescaler=%u\n", 
			        DEVICE_NAME, __FUNCTION__, cap->intern_prescaler);
			__debug_pcan_timing_parameters(cur_baudrate);
			continue;
		}

		// now base clock is defined, calculate time quantum for this baudrate
#ifdef PCAN_TIMING_DIV64_WORKAROUND
		cur_baudrate.tSCL_ps = DIV_ROUND(cur_baudrate.prescaler*MHz, 
				                           sysclock);
		DPRINTK(KERN_DEBUG "tSCL_ps:%u/%u=%u\n",
		        cur_baudrate.prescaler*MHz, sysclock, 
		        cur_baudrate.tSCL_ps);
#else
		cur_baudrate.tSCL_ps = DIV_ROUND((big_t )cur_baudrate.prescaler*1000*GHz, 
				                           sysclock);
		DPRINTK(KERN_DEBUG "tSCL_ps:%llu/%u=%u\n",
		        (big_t )cur_baudrate.prescaler*1000*GHz, sysclock, 
		        cur_baudrate.tSCL_ps);
#endif

		if (cur_baudrate.tSCL_ps == 0)
		{
			// prescaler to small => NBT too big
			DPRINTK(KERN_DEBUG "%s: %s(): loop3:\n", DEVICE_NAME, __FUNCTION__);
			__debug_pcan_timing_parameters(cur_baudrate);
			continue;
		}

		cur_baudrate.tseg1 = DIV_ROUND(1000*abt_org->tseg1_ns, 
		                               cur_baudrate.tSCL_ps);
		cur_baudrate.tseg2 = DIV_ROUND(1000*abt_org->tseg2_ns, 
		                               cur_baudrate.tSCL_ps);

		if ((cur_baudrate.tseg1 + cur_baudrate.tseg2 + 1) != NBT)
		{
			//  is rounding error of tSCL_ns too big?
			DPRINTK(KERN_DEBUG "%s: %s(): loop4: NBT=%u\n", 
			        DEVICE_NAME, __FUNCTION__, NBT);
			__debug_pcan_timing_parameters(cur_baudrate);
			continue;
		}

		/* if (  (cur_baudrate.tseg1 < 2) */
		if (  (cur_baudrate.tseg1 < cap->min_tseg1)
		   || (cur_baudrate.tseg1 > cap->max_tseg1)
		   )
		{
			DPRINTK(KERN_DEBUG "%s: %s(): loop5: cap->max_tseg1=%u\n", 
			        DEVICE_NAME, __FUNCTION__, cap->max_tseg1);
			__debug_pcan_timing_parameters(cur_baudrate);
			continue;
		}

		/* if (  (cur_baudrate.tseg2 < 2) */
		if (  (cur_baudrate.tseg2 < cap->min_tseg2)
		   || (cur_baudrate.tseg2 > cap->max_tseg2)
		   )
		{
			DPRINTK(KERN_DEBUG "%s: %s(): loop6: cap->max_tseg2=%u\n", 
			        DEVICE_NAME, __FUNCTION__, cap->max_tseg2);
			__debug_pcan_timing_parameters(cur_baudrate);
			continue;
		}

		cur_baudrate.tseg1_ns = (big_t )cur_baudrate.tseg1 
		                              * cur_baudrate.tSCL_ps / 1000;
		cur_baudrate.tseg2_ns = (big_t )cur_baudrate.tseg2 
		                              * cur_baudrate.tSCL_ps / 1000;

		for (cur_baudrate.sjw=1; cur_baudrate.sjw <= cap->max_sjw; 
				                                               cur_baudrate.sjw++)
		{
			// try all SJW
			cur_baudrate.sjw_ns = (big_t )cur_baudrate.sjw 
			                            * cur_baudrate.tSCL_ps / 1000;

#ifndef CONFIG_64BIT
			/* this only dividion needs 64-bits do_div(). the divisor normally */
			/* won't be > 2^32. Anyway, this ".baudrate" member seems not be */
			/* used next and seems only an info field. */
#endif
			cur_baudrate.baudrate = \
			   DIV_ROUND64(1000ULL*GHz, (  cur_baudrate.tSCL_ps 
				                          + cur_baudrate.tseg1_ns*1000
				                          + cur_baudrate.tseg2_ns*1000));

			// Calculate deviation of timing to original

#if 1
			// Model for "goodness": baud rate and SJW are equally important
			cur_baudrate.penalty =   abs( ( cur_baudrate.tseg1_ns \
				                           + cur_baudrate.tseg2_ns \
				                           + cur_baudrate.tSCL_ps / 1000) \
				                         - ( abt_org->tseg1_ns \
				                           + abt_org->tseg2_ns \
				                           + abt_org->sync_seg_ns) ) 
				                    + abs(cur_baudrate.sjw_ns - abt_org->sjw_ns);
#endif

#if 0
			// Model for "goodness": all timesegs are equally important
			// But this is a mental error! TSCL is different for both baud rates...
			// so must include the "1 timequanta Gap"!
			cur_baudrate.penalty = abs(cur_baudrate.tseg1_ns - abt_org->tseg1_ns)
				                  + abs(cur_baudrate.tseg2_ns - abt_org->tseg2_ns)
				                  + abs(cur_baudrate.sjw_ns - abt_org->sjw_ns);
#endif
			if (cur_baudrate.penalty < best_baudrate.penalty) 
			{
				best_baudrate = cur_baudrate;
			}
		}
	}

	// no baud rate found at all
	if (best_baudrate.penalty == PENALTY_INVALID) 
	{
		DPRINTK(KERN_DEBUG "%s: %s(): penalty!\n", DEVICE_NAME, __FUNCTION__);

		return 0;
	}

	DPRINTK(KERN_DEBUG "%s: %s(): best_baudrate["
	        "penalty=%u]\n",
	        DEVICE_NAME, __FUNCTION__,
	        best_baudrate.penalty);

	abt_result->prescaler = best_baudrate.prescaler;
	abt_result->tseg1_ns = best_baudrate.tseg1_ns;
	abt_result->tseg2_ns = best_baudrate.tseg2_ns;
	abt_result->sjw_ns = best_baudrate.sjw_ns;
	abt_result->info_baudrate = best_baudrate.baudrate;
	abt_result->sample3 = abt_org->sample3;

	DPRINTK(KERN_DEBUG "%s: %s(): abt_result["
	        "prescaler=%u tseg1_ns=%u tseg2_ns=%u sjw_ns=%u "
	        "info_baudrate=%u info_delta_baudrate=%u sample3=%u]\n",
	        DEVICE_NAME, __FUNCTION__,
	        abt_result->prescaler, abt_result->tseg1_ns, abt_result->tseg2_ns,
	        abt_result->sjw_ns, abt_result->info_baudrate, 
	        abt_result->info_delta_baudrate,
	        abt_result->sample3);

	return 1;
}

/*
 * void pcan_BTR0BTR1_to_abstract(uint16_t btr0btr1, 
 *                                struct pcan_timing_abstract *abt)
 */
void pcan_BTR0BTR1_to_abstract(uint16_t btr0btr1, 
                               struct pcan_timing_abstract *abt)
{
	struct pcan_timing_baudrate sja1000bt;

	//  1)  decode original timing. CANAPI uses BTR0BTR1 for SJA1000@16MHz.
	//      Postcondition: sja100bt contains timing values @16MHz
	pcan_timing_decode_baudrate(16*MHz, btr0btr1, &sja1000bt);

	//  2) calculate original abstract baud rate
	//     Postcondition: "abt" valid
	pcan_timing_sja_to_abstract(&sja1000_capabilities, &sja1000bt, abt);
}

/*
 * int pcan_abstract_to_sja(const struct pcan_timing_capabilities *cap,
 *                          struct pcan_timing_abstract *abt,
 *                          uint32_t sysclock,
 *                          struct pcan_timing_baudrate *sja1000bt)
 */
int pcan_abstract_to_sja(const struct pcan_timing_capabilities *cap,
                         struct pcan_timing_abstract *abt,
                         uint32_t sysclock,
                         struct pcan_timing_baudrate *sja1000bt)
{
	const uint32_t sysclock_MHz = sysclock / MHz;
	uint32_t tSCL_ns = DIV_ROUND(abt->prescaler*kHz, sysclock_MHz);

	if (tSCL_ns != 0)
	{
		// Base clock for assembly of bit time intervals
		sja1000bt->can_systemclock = sysclock;

		sja1000bt->SJW = DIV_ROUND(abt->sjw_ns, tSCL_ns);
		sja1000bt->TSEG1 = DIV_ROUND(abt->tseg1_ns, tSCL_ns);
		sja1000bt->TSEG2 = DIV_ROUND(abt->tseg2_ns, tSCL_ns);
		// sja works with clock/2
		sja1000bt->BRP = DIV_ROUND(abt->prescaler, cap->intern_prescaler);
		sja1000bt->SAM = abt->sample3;

		DPRINTK(KERN_DEBUG "%s: %s(sysclock=%u): tSCL_ns=%u "
		        "sja1000bt[SJW=%u TSEG1=%u TSEG2=%u BRP=%u SAM=%u]\n", 
		        DEVICE_NAME, __FUNCTION__, sysclock, tSCL_ns,
		        sja1000bt->SJW, sja1000bt->TSEG1, sja1000bt->TSEG2, 
		        sja1000bt->BRP, sja1000bt->SAM);

		return 1;
	}

	DPRINTK(KERN_DEBUG "%s: %s() tSCL_ns=%uGHz/%u=0!!!\n",
	        DEVICE_NAME, __FUNCTION__, abt->prescaler, sysclock);
	return 0;
}
