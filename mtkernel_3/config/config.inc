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
; *	config.inc
; *	User Configuration Definition
; */

$IFNDEF __TK_CONFIG__
__TK_CONFIG__	.EQU	(1)

;/*---------------------------------------------------------------------- */
;/* Stack size definition
; */
CFN_EXC_STACK_SIZE	.EQU	(256)	;/* Exception stack size */
CFN_TMP_STACK_SIZE	.EQU	(12)	;/* Temporary stack size */


;/*---------------------------------------------------------------------- */
;/* System function selection
; *   1: Use function.  0: No use function.
; */
USE_IMALLOC		.EQU	(1)	;/* Use dynamic memory allocation */

$ENDIF ; __TK_CONFIG__
