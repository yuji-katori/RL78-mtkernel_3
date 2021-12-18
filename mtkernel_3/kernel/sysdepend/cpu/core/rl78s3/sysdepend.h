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
 *	sysdepend.h (RL78/S3)
 *	System-Dependent local defined
 */

#ifndef _SYSDEPEND_CPU_CORE_SYSDEPEND_
#define _SYSDEPEND_CPU_CORE_SYSDEPEND_

/*
 *    System data (sys_dat.c)
 */
IMPORT	INT	knl_taskindp;			/* Task independent status */

/*
 *    Reset Handler (vector_tbl.c/reset_hdl.c)
 */
IMPORT void Reset_Handler(void);		/* Reset Handler */

/*
 *    Exception Handler (vector_tbl.c/interrupt.c)
 */
IMPORT void Default_Handler(UINT intno);	/* Default Handler (Undefine Interrupt) */

/*
 * Dispatcher (dispatch.asm)
 */
IMPORT void knl_dispatch_entry(void);		/* dispatch entry */
IMPORT void knl_dispatch_to_schedtsk(void);	/* force dispatch */

/*
 * Interrupt Control (dispatch.asm)
 */
IMPORT void knl_systim_inthdr(void);		/* System-timer Interrupt handler */


#endif /* _SYSDEPEND_CPU_CORE_SYSDEPEND_ */
