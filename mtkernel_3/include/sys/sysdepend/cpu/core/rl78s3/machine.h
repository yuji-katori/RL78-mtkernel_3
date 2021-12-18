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
 *	Machine type definition (RL78/S3 core depended)
 */

#ifndef __SYS_MACHINE_CORE_H__
#define __SYS_MACHINE_CORE_H__

/*
 * CPU_xxxx		CPU type
 * ALLOW_MISALIGN	1 if access to misalignment data is allowed 
 * BIGENDIAN		1 if big endian 
 */

/* ----- C-First RL78/S3 definition ----- */

#define CPU_RL78_S3		1
#define ALLOW_MISALIGN		0
#define INT_BITWIDTH		16

/*
 * Endianness
 */
#define BIGENDIAN		0	/* Default (Little Endian) */

#endif /* __SYS_MACHINE_CORE_H__ */
