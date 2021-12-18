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
; *	System dependencies definition (C-First depended)
; *	Included also from assembler program.
; */

$IFNDEF __SYS_SYSDEF_DEPEND_H__
__SYS_SYSDEF_DEPEND_H__		.EQU	(1)


;/* CPU-dependent definition (R5F104LE) */
$INCLUDE "../cpu/r5f104le/sysdef.inc"

;/* ------------------------------------------------------------------------ */
;/*
; * Maximum value of Power-saving mode switching prohibition request.
; * Use in tk_set_pow API.
; */
;#define LOWPOW_LIMIT	0x7fff		/* Maximum number for disabling */

;/* ------------------------------------------------------------------------ */
;/*
; * size_t, prtdiff_t
; *
; */
;#include <stddef.h>

$ENDIF ; __TK_SYSDEF_DEPEND_H__ */
