/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.00.00
 *
 *    Copyright (C) 2006-2019 by Ken Sakamura.
 *    This software is distributed under the T-License 2.1.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2019/12/11.
 *
 *----------------------------------------------------------------------
 */

/*
 *	sys_timer.h (RL78/S3)
 *	Hardware-Dependent System Timer (SysTick) Processing
 */

#ifndef _SYSDEPEND_CPU_CORE_SYSTIMER_
#define _SYSDEPEND_CPU_CORE_SYSTIMER_

#include "iodefine.h"

/*
 * Set timer
 */
Inline void knl_init_hw_timer( void )
{
	UINT	imask;

	DI(imask);

	OSMC |= 0x10;			// Clock uses fIL
	RTCEN = 1;			// Interval timer enable
	ITMK = 0;			// INTIT enable
	ITPR0 = TIM_INT_PRI/2;		// Set interval count and start timer
	ITPR1 = TIM_INT_PRI;

	ITMC = 0x8000 + 15 * TIMER_PERIOD -1;

	EI(imask);
}

/*
 * Timer start processing
 *	Initialize the timer and start the periodical timer interrupt.
 */
Inline void knl_start_hw_timer( void )
{
	/* Set timer */
	knl_init_hw_timer();
}

/*
 * Clear timer interrupt
 *	Clear the timer interrupt request. Depending on the type of
 *	hardware, there are two timings for clearing: at the beginning
 *	and the end of the interrupt handler.
 *	'clear_hw_timer_interrupt()' is called at the beginning of the
 *	timer interrupt handler.
 *	'end_of_hw_timer_interrupt()' is called at the end of the timer
 *	interrupt handler.
 *	Use either or both according to hardware.
 */
Inline void knl_clear_hw_timer_interrupt( void )
{
	/* Nothing required to do at this point */
}

Inline void knl_end_of_hw_timer_interrupt( void )
{
	/* Nothing required to do at this point */
}

/*
 * Timer stop processing
 *	Stop the timer operation.
 *	Called when system stops.
 */
Inline void knl_terminate_hw_timer( void )
{
	ITMC = 0;			// Stop interval timer
}

/*
 * Get processing time from the previous timer interrupt to the
 * current (nanosecond)
 *	Consider the possibility that the timer interrupt occurred
 *	during the interrupt disable and calculate the processing time
 *	within the following
 *	range: 0 <= Processing time < TIMER_PERIOD * 2
 */
Inline UW knl_get_hw_timer_nsec( void )
{
	/* Nothing required to do at this point */
	return 0;
}

#endif /* _SYSDEPEND_CPU_CORE_SYSTIMER_ */
