; Copyright (C) 2014, 2018 Renesas Electronics Corporation
; RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY.
; This program must be used solely for the purpose for which
; it was furnished by Renesas Electronics Corporation. No part of this
; program may be reproduced or disclosed to others, in any
; form, without the prior written permission of Renesas Electronics
; Corporation.

;   NOTE       : THIS IS A TYPICAL EXAMPLE.
$INCLUDE "config.inc"
$INCLUDE "sys/machine.inc"
$INCLUDE "sys/sysdef.inc"
$INCLUDE "sys/knldef.inc"
$IFDEF CPU_CORE_RL78S3

$IFNDEF __RENESAS_VERSION__
__RENESAS_VERSION__	.EQU	0x01000000
$ENDIF

	.public	_start

;-----------------------------------------------------------------------------
;	RAM section
;-----------------------------------------------------------------------------
.SECTION .dataR, DATA
.SECTION .sdataR, DATA

;-----------------------------------------------------------------------------
;	RESET vector
;-----------------------------------------------------------------------------
_start	.VECTOR	0

;-----------------------------------------------------------------------------
;	startup
;-----------------------------------------------------------------------------
.SECTION .text, TEXT
_start:
	;--------------------------------------------------
	; setting the stack pointer
	;--------------------------------------------------
	MOVW	SP,#LOWW(INTERNAL_RAM_END)

	;--------------------------------------------------
	; initializing BSS
	;--------------------------------------------------
	; clear external variables which doesn't have initial value (near)
	MOVW	HL,#LOWW(STARTOF(.bss))
$IF USE_IMALLOC
	MOVW	AX,#LOWW(INTERNAL_RAM_END - EXC_STACK_SIZE)
$ELSE
	MOVW	AX,#LOWW(STARTOF(.bss) + SIZEOF(.bss))
$ENDIF
	BR	$.L2_BSS
.L1_BSS:
	MOV	[HL+0],#0
	INCW	HL
.L2_BSS:
	CMPW	AX,HL
	BNZ	$.L1_BSS

	; clear saddr variables which doesn't have initial value
	MOVW	HL,#LOWW(STARTOF(.sbss))
	MOVW	AX,#LOWW(STARTOF(.sbss) + SIZEOF(.sbss))
	BR	$.L2_SBSS
.L1_SBSS:
	MOV	[HL+0],#0
	INCW	HL
.L2_SBSS:
	CMPW	AX,HL
	BNZ	$.L1_SBSS

	;--------------------------------------------------
	; ROM data copy
	;--------------------------------------------------
	; copy external variables having initial value (near)
	MOV	ES,#HIGHW(STARTOF(.data))
	MOVW	BC,#LOWW(SIZEOF(.data))
	BR	$.L2_DATA
.L1_DATA:
	DECW	BC
	MOV	A,ES:LOWW(STARTOF(.data))[BC]
	MOV	LOWW(STARTOF(.dataR))[BC],A
.L2_DATA:
	CLRW	AX
	CMPW	AX,BC
	BNZ	$.L1_DATA

	; copy saddr variables having initial value
	MOV	ES,#HIGHW(STARTOF(.sdata))
	MOVW	BC,#LOWW(SIZEOF(.sdata))
	BR	$.L2_SDATA
.L1_SDATA:
	DECW	BC
	MOV	A,ES:LOWW(STARTOF(.sdata))[BC]
	MOV	LOWW(STARTOF(.sdataR))[BC],A
.L2_SDATA:
	CLRW	AX
	CMPW	AX,BC
	BNZ	$.L1_SDATA
	MOV	ES,#HIGHW(STARTOF(.dataR))

	;--------------------------------------------------
	; call main function
	;--------------------------------------------------
	BR	!!_Reset_Handler	; Reset_Handler();

;-----------------------------------------------------------------------------
;	section
;-----------------------------------------------------------------------------
.SECTION .RLIB, TEXTF
.L_section_RLIB:
.SECTION .SLIB, TEXTF
.L_section_SLIB:
.SECTION .textf, TEXTF
.L_section_textf:
.SECTION .const, CONST
.L_section_const:
.SECTION .constf, CONSTF
.L_section_constf:
.SECTION .data, DATA
.L_section_data:
.SECTION .sdata, SDATA
.L_section_sdata:
.SECTION .bss, BSS
.L_section_bss:
.SECTION .sbss, SBSS
.L_section_sbss:

$ENDIF ; CPU_CORE_RL78S3
