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
 *	cpu_cntl.c (RL78/S3)
 *	CPU-Dependent Control
 */
#include "kernel.h"
#include "../../../sysdepend.h"

#include "cpu_task.h"

/* ------------------------------------------------------------------------ */
/*
 * Set task register contents (Used in tk_set_reg())
 */
EXPORT void knl_set_reg( CTXB *ctxb, CONST T_REGS *regs, CONST T_EIT *eit, CONST T_CREGS *cregs )
{
	SStackFrame	*ssp;
	INT	i;

	ssp = ctxb->ssp;

	if ( cregs != NULL ) {
		ssp = cregs->sp;
	}

	if ( regs != NULL ) {
		for ( i = 0; i < 4; ++i ) {
			ssp->rp[i] = regs->rp[i];
		}
	}

	if ( eit != NULL ) {
		ssp->pc_psw = ((UW)eit->psw << 24) + eit->pc;
	}

	if ( cregs != NULL ) {
		ctxb->ssp = cregs->sp;
	}
}


/* ------------------------------------------------------------------------ */
/*
 * Get task register contents (Used in tk_get_reg())
 */
EXPORT void knl_get_reg( CTXB *ctxb, T_REGS *regs, T_EIT *eit, T_CREGS *cregs )
{
	SStackFrame	*ssp;
	INT		i;

	ssp = ctxb->ssp;

	if ( regs != NULL ) {
		for ( i = 0; i < 3; ++i ) {
			regs->rp[i] = ssp->rp[i];
		}
	}

	if ( eit != NULL ) {
		eit->pc  = ssp->pc_psw;
		eit->psw = ssp->pc_psw >> 24;
	}

	if ( cregs != NULL ) {
		cregs->sp = ctxb->ssp;
	}
}

#endif /* CPU_CORE_RL78S3 */
