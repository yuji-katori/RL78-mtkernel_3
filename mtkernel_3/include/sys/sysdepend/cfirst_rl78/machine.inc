;/*
; *----------------------------------------------------------------------
; *    micro T-Kernel 3.00.00
; *
; *    Copyright (C) 2006-2019 by Ken Sakamura.
; *    This software is distributed under the T-License 2.1.
; *----------------------------------------------------------------------
; *
; *    Released by TRON Forum(http://www.tron.org) at 2019/12/11.
; *
; *----------------------------------------------------------------------
; */

;/*
; *	machine.inc
; *
; *	Machine type definition (C-First depended)
; */

$IFNDEF __SYS_SYSDEPEND_MACHINE_H__
__SYS_SYSDEPEND_MACHINE_H__	.EQU	(1)

;/*
; * [TYPE]_[CPU]	TARGET SYSTEM
; * CPU_xxxx		CPU type
; * CPU_CORE_xxx	CPU core type
; */

;/* ----- C-First RL78/G14 (CPU: R5F104LE) definition ----- */
;#undef _CFirst_RL78_

CFIRST_RL78	.EQU	(1)			;/* Target system : C-First RL78/G14 */
CPU_R5F104LE	.EQU	(1)			;/* Target CPU : RENESAS R5F104LE */
CPU_CORE_RL78S3	.EQU	(1)			;/* Target CPU-Core : RL78/S3 */

;#define TARGET_DIR		cfirst_rl78			/* Sysdepend-Directory name */

;/*
; **** CPU-depeneded profile (R5F104LE)
; */
;#include "../cpu/r5f104le/machine.h"


$ENDIF ; __SYS_SYSDEPEND_MACHINE_H__
