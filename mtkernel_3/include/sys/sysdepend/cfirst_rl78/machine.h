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
 *	machine.h
 *
 *	Machine type definition (C-First depended)
 */

#ifndef __SYS_SYSDEPEND_MACHINE_H__
#define __SYS_SYSDEPEND_MACHINE_H__

/*
 * [TYPE]_[CPU]		TARGET SYSTEM
 * CPU_xxxx		CPU type
 * CPU_CORE_xxx		CPU core type
 */

/* ----- C-First RL78/G14 (CPU: R5F104LE) definition ----- */
#undef _CFirst_RL78_

#define CFIRST_RL78		1				/* Target system : C-First RL78/G14 */
#define CPU_R5F104LE		1				/* Target CPU : RENESAS R5F104LE */
#define CPU_CORE_RL78S3		1				/* Target CPU-Core : RL78/S3 */

#define TARGET_DIR		cfirst_rl78			/* Sysdepend-Directory name */

/*
 **** CPU-depeneded profile (R5F104LE)
 */
#include "../cpu/r5f104le/machine.h"


#endif /* __SYS_SYSDEPEND_MACHINE_H__ */
