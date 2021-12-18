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

#include <sys/machine.h>
#ifdef CPU_CORE_RL78S3

/*
 *	int.c
 *
 *	Interrupt controller (RL78/S3)
 */

#include <tk/tkernel.h>

/*----------------------------------------------------------------------*/
/*
 * CPU Interrupt Control for RL78/S3.
 *
 */

/* 
 * Disable interrupt 
 */
EXPORT UINT disint(void)
{
UB ret;
	ret = __get_psw( ) ^ 0xFF;
	__set_psw( MAX_INT_PRI_PSW );
	return ret;
}


/*
 * Enable interrupt
 */
UINT enaint( UINT intsts )
{
UB ret;
	ret = __get_psw( ) ^ 0xFF;
	__set_psw(  ( intsts ^ 0xFF ) & 0x86 );
	return ret;
}


#endif /* CPU_CORE_RL78S3 */
