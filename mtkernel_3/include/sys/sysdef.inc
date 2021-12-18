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
; *	System dependencies definition.
; *	Included also from assembler program.
; */

$IFNDEF __SYS_SYSDEF_H__
__SYS_SYSDEF_H__	.EQU	(1)

;/* System dependencies */
;#define SYSDEF_PATH_(a)		#a
;#define SYSDEF_PATH(a)		SYSDEF_PATH_(a)
;#define SYSDEF_SYSDEP()		SYSDEF_PATH(sysdepend/TARGET_DIR/sysdef.h)
;#include SYSDEF_SYSDEP()

$IFDEF _CFirst_RL78_
$INCLUDE "sysdepend/cfirst_rl78/sysdef.inc"
$ENDIF

$ENDIF ; __SYS_SYSDEF_H__
