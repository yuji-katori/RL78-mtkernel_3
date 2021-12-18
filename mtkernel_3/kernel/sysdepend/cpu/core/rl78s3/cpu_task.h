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
 *	cpu_task.h (RL78/S3)
 *	CPU-Dependent Task Start Processing
 */

#ifndef _SYSDEPEND_CPU_CORE_CPUTASK_
#define _SYSDEPEND_CPU_CORE_CPUTASK_

/*
 * System stack configuration at task startup
 */
typedef struct {
//	UB	es,cs;	/* ES,CS   */
	UH	rp[4];	/* RP0-RP3 */
	UW	pc_psw;	/* PC,PSW  */
} SStackFrame;

/*
 * Size of system stack area destroyed by 'make_dormant()'
 * In other words, the size of area required to write by 'setup_context().'
 */
//#define DORMANT_STACK_SIZE	( sizeof(VW) * 1 )	/* To 'spc_spsw' position */

/*
 * Initial value for task startup
 */
#define INIT_PSW	( 0x86 )


/*
 * Create stack frame for task startup
 *	Call from 'make_dormant()'
 */
Inline void knl_setup_context( TCB *tcb )
{
	SStackFrame	*ssp;

	ssp = tcb->isstack;
	ssp--;

	/* CPU context initialization */
		  /* Initial PSW */ /* Task startup address */
	ssp->pc_psw = ((UW)INIT_PSW << 24) + (UH)tcb->task;
	tcb->tskctxb.ssp = ssp;		/* System stack */
}

/*
 * Set task startup code
 *	Called by 'tk_sta_tsk()' processing.
 */
Inline void knl_setup_stacd( TCB *tcb, INT stacd )
{
	SStackFrame	*ssp = tcb->tskctxb.ssp;

	ssp->rp[3] = stacd;			/* rp3(AX) */
	ssp->rp[2] = (UH)tcb->exinf;		/* rp2(BC) */
}

/*
 * Delete task contexts
 */
Inline void knl_cleanup_context( TCB *tcb )
{
}

#endif /* _SYSDEPEND_CPU_CORE_CPUTASK_ */
