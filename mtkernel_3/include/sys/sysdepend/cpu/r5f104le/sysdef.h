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
 *	sysdef.h
 *
 *	System dependencies definition (R5F104LE depended)
 *	Included also from assembler program.
 */

#ifndef __TK_SYSDEF_DEPEND_CPU_H__
#define __TK_SYSDEF_DEPEND_CPU_H__


/* CPU Core-dependent definition (RL78/S3) */
#include "../core/rl78s3/sysdef.h"

/* ------------------------------------------------------------------------ */
/*
 * Internal Memorie (Main RAM without saddr)  0xFE900 - 0xFFE1F
 */
#define INTERNAL_RAM_TOP	0xE900
#define INTERNAL_RAM_END	0xFE20


/*
 * Settable interval range (millisecond)
 */
#define MIN_TIMER_PERIOD	1
#define MAX_TIMER_PERIOD	270


/* ------------------------------------------------------------------------ */
/*
 * Number of Interrupt vectors
 */
#define N_INTVEC		0x64	/* Number of Interrupt vectors */

/*
 * The number of the implemented bit width for priority value fields.
 */
#define INTPRI_BITWIDTH		2


/* ------------------------------------------------------------------------ */
/*
 * Interrupt Priority Levels
 */
#define MAX_INT_PRI		(1)		/* Highest Ext. interrupt level */
#define TIM_INT_PRI		(1)
#define	MAX_INT_PRI_PSW		((MAX_INT_PRI-1)*2+0x80)
#define	TIM_INT_PRI_PSW		((TIM_INT_PRI-1)*2+0x80)

/*
 * Time-event handler interrupt level
 */
#define TIMER_INTLEVEL		(TIM_INT_PRI_PSW^0xFF)


#endif /* __TK_SYSDEF_DEPEND_CPU_H__ */
