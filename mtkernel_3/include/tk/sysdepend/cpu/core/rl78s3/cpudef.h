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
 *	cpudef.h
 *
 *	CPU dependent definition  (RL78/S3 core depended)
 */

#ifndef __TK_CPUDEF_CORE_H__
#define __TK_CPUDEF_CORE_H__

#include <config.h>

/*
 * Using FPU (depend on CPU)
 *   0: not using FPU
 *   TA_COPn(n = 0-3): using FPU
 */
#define TA_FPU		0

/*
 * General purpose register		tk_get_reg tk_set_reg
 */
typedef struct t_regs {
	UH	rp[4];		/* General purpose register RP0-RP3 */
} T_REGS;

/*
 * Exception-related register		tk_get_reg tk_set_reg
 */
typedef struct t_eit {
	UH	pc;		/* Program counter */
	UB	psw;		/* Status register */
} T_EIT;

/*
 * Control register			tk_get_reg tk_set_reg
 */
typedef struct t_cregs {
	void	*sp;		/* System stack pointer SP */
} T_CREGS;

#endif /* __TK_CPUDEF_CORE_H__ */
