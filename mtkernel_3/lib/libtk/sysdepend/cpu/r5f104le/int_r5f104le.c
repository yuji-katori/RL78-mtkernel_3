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

#include <tk/tkernel.h>
#include <tk/syslib.h>
#include <sys/machine.h>
#include <sys/profile.h>

#ifdef CPU_R5F104LE

#include "iodefine.h"

#if TK_SUPPORT_INTCTRL == TRUE

#if TK_HAS_ENAINTLEVEL == TRUE
/*
 * Enable interrupt 
 *	Enables the interrupt specified in intno.
 *	External Interrupt can be specified. 
 */
EXPORT void EnableInt( UINT intno, INT level )
{
UINT imask;
INT index;
UB maskptn;

	intno >>= 1;
	if( intno < 0x44>>1 )
		intno += 16*8 -2;
	else
		intno -= 0x44>>1;
	index = intno>>3;
	maskptn = 1<<(intno&7);

	DI(imask);
	(&MK2L)[index] |= maskptn;
	if( level & 1 )
		(&PR02L)[index] |= maskptn;
	else
		(&PR02L)[index] &= ~maskptn;
	if( level & 2 )
		(&PR12L)[index] |= maskptn;
	else
		(&PR12L)[index] &= ~maskptn;
	(&MK2L)[index] &= ~maskptn;
	EI(imask);
}
#endif /* #if TK_HAS_ENAINTLEVEL */

/*
 * Disable interrupt 
 *	Disables the interrupt specified in intno.
 *	External Interrupt can be specified. 
 */
EXPORT void DisableInt( UINT intno )
{
UINT imask;

	intno >>= 1;
	if( intno < 0x44>>1 )
		intno += 16*8 -2;
	else
		intno -= 0x44>>1;

	DI(imask);
	(&MK2L)[intno>>3] |= 1<<(intno&7);
	EI(imask);
}

/*
 * Issue EOI to interrupt controller
 */
EXPORT void EndOfInt( UINT intno )
{
	/* No opetarion. */
}

/*
 * Clear interrupt request 
 *	Clears the intno interrupt request.
 *	Valid only for edge trigger.
 *	For edge trigger, the interrupt must be cleared with an
 *	interrupt handler.
 */
EXPORT void ClearInt( UINT intno )
{
UINT imask;

	intno >>= 1;
	if( intno < 0x44>>1 )
		intno += 16*8 -2;
	else
		intno -= 0x44>>1;

	DI(imask);
	(&IF2L)[intno>>3] &= ~(1<<(intno&7));
	EI(imask);
}

/*
 * Check for interrupt requests 
 *	Checks for intvec interrupt  requests.
 *	If an interrupt request is found, returns TRUE (other than 0).
 */
EXPORT BOOL CheckInt( UINT intno )
{
	intno >>= 1;
	if( intno < 0x44>>1 )
		intno += 16*8 -2;
	else
		intno -= 0x44>>1;

	return (&IF2L)[intno>>3] & 1<<(intno&7) ? TRUE : FALSE;
}

#endif /* TK_SUPPORT_INTCTRL */

#if TK_SUPPORT_CPUINTLEVEL

/*
 * Set Interrupt Mask Level in CPU
 */
IMPORT void SetCpuIntLevel( INT level )
{
	__set_psw( __get_psw( ) & 0xF9 | level << 1 & 0x06 );
}

/*
 * Get Interrupt Mask Level in CPU
 */
IMPORT INT GetCpuIntLevel( void )
{
	return __get_psw( ) >> 1 & 0x03;
}

#endif /* TK_SUPPORT_CPUINTLEVEL */

#endif /* CPU_R5F104LE */