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
; *	sysdef.inc
; *
; *	System dependencies definition (R5F104LE depended)
; *	Included also from assembler program.
; */

$IFNDEF __TK_SYSDEF_DEPEND_CPU_H__
__TK_SYSDEF_DEPEND_CPU_H__	.EQU	(1)


;/* CPU Core-dependent definition (RL78/S3) */
;#include "../core/rl78s3/sysdef.h"

;/* ------------------------------------------------------------------------ */
;/*
; * Internal Memorie (Main RAM without saddr)  0xFE900 - 0xFFE1F
; */
;#define INTERNAL_RAM_TOP	0xE900
INTERNAL_RAM_END	.EQU	0xFE20


;/*
; * Settable interval range (millisecond)
; */
;#define MIN_TIMER_PERIOD	1
;#define MAX_TIMER_PERIOD	270


;/* ------------------------------------------------------------------------ */
;/*
; * Number of Interrupt vectors
; */
;#define N_INTVEC		0x64	/* Number of Interrupt vectors */

;/*
; * The number of the implemented bit width for priority value fields.
; */
;#define INTPRI_BITWIDTH	2


;/* ------------------------------------------------------------------------ */
;/*
; * Interrupt Priority Levels
; */
MAX_INT_PRI		.EQU	(1)		;/* Highest Ext. interrupt level */
TIM_INT_PRI		.EQU	(1)
MAX_INT_PRI_PSW		.EQU	((MAX_INT_PRI-1)*2+0x80)
TIM_INT_PRI_PSW		.EQU	((TIM_INT_PRI-1)*2+0x80)

;/*
; * Time-event handler interrupt level
; */
;TIMER_INTLEVEL		.EQU	(TIM_INT_PRI_PSW^0xFF)


$ENDIF ; __TK_SYSDEF_DEPEND_CPU_H__
