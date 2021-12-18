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
; *	profile.h
; *
; *	Service Profile (C-First depended)
; */

$IFNDEF __SYS_DEPEND_PROFILE_H__
__SYS_DEPEND_PROFILE_H__	.EQU	(1)

TRUE		.EQU		(1)		;/* True */
FALSE		.EQU		(0)		;/* False */

;/*
; **** CPU-depeneded profile (R5F104LE)
; */
;#include "../cpu/r5f104le/profile.h"

;/*
; **** Target-depeneded profile (C-First)
; */

;/*
; * Power management
; */
TK_SUPPORT_LOWPOWER		.EQU	FALSE		;/* Support of power management */



$ENDIF ;/* __SYS_DEPEND_PROFILE_H__ */
