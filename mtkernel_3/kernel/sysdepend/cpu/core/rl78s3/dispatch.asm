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
$INCLUDE "sys/machine.inc"
$IFDEF CPU_CORE_RL78S3
;/*
; *	dispatch.asm (RL78/S3)
; *	Dispatcher
; */

$INCLUDE "sys/sysdef.inc"
$INCLUDE "sys/profile.inc"
$INCLUDE "sys/knldef.inc"

;/* ------------------------------------------------------------------------ */
;/*
; * Dispatcher
; *	dispatch_to_schedtsk:
; *		Throw away the current contexts and forcibly dispatch to 'schedtsk.'
; *		Called directly by jump (jmp) but do not return.
; *		Called on the undefined stack state (undefined 'ssp').
; *		Called on the interrupt disable state.
; *	dispatch_entry:
; *		Normal dispatch processing.
; *	_ret_int_dispatch:
; *		Called when dispatch is required by 'tk_ret_int().'
; *
; *	Contexts to save
; *	Save registers except for SP to a stack. Save SP to TCB.
; *
; *		   High Address	+---------------+
; *				| SPSW(8bit)	| Saved by interrupt entry
; *				| SPC(24bit)	| routines until here.
; *				+---------------+
; *				| AX(16bit)	|
; *				| BC(16bit)	|
; *				| DE(16bit)	|
; *	Saved to TCB  SP =>	| HL(16bit)	|
; *		    Low Address	+---------------+
; */

;/* Temporal stack used when 'dispatch_to_schedtsk' is called */

	.SECTION .text,TEXT
	.PUBLIC _knl_dispatch_to_schedtsk
	.PUBLIC _knl_dispatch_entry

_knl_dispatch_to_schedtsk:
	MOVW	SP, #LOWW(_knl_tmp_stack+TMP_STACK_SIZE); Set temporal stack
	ONEW	AX					; AX := 1
	MOVW	!LOWW(_knl_dispatch_disabled), AX	; Dispatch disable
	MOVW	DE, #LOWW(_knl_ctxtsk)			; DE := &ctxtsk
	CLRW	AX
	MOVW	[DE], AX				; ctxtsk = NULL
	MOV	PSW, #0x86				; Interrupt enable
	BR	$.L0_dispatch
_knl_dispatch_entry:
	MOV	A, PSW
	MOV	[SP+3], A				; SSR compensation (IE=1)
_ret_int_dispatch:
	PUSH	AX					; Context(AX) save
	ONEW	AX					; AX := 1
	MOVW	!LOWW(_knl_dispatch_disabled), AX	; Dispatch disable
	MOV	PSW, #0x86				; Interrupt enable
	PUSH	BC					; Context save
	PUSH	DE
	PUSH	HL
	MOVW	DE, #LOWW(_knl_ctxtsk)			; DE := &ctxtsk
	MOVW	AX, [DE]
	MOVW	HL, AX
	MOVW	AX, SP					; Save SSP to TCB
	MOVW	[HL+4], AX
.L0_dispatch:
	MOV	PSW, #MAX_INT_PRI_PSW			; set max interrupt level
	MOVW	HL, !LOWW(_knl_schedtsk)		; HL := schedtsk
	CLRW	AX					; Is there 'schedtsk'?
	CMPW	AX, HL
	BNZ	$.L1_dispatch
	MOVW	!_knl_ctxtsk, AX
	; Because there is no task that should be executed, move to the power-saving mode
$IF TK_SUPPORT_LOWPOWER == TRUE
	MOVW	HL, !LOWW(_knl_lowpow_discnt)		; Is 'low_pow' disabled?
	CMPW	AX, HL
	SKNZ
	CALL	!_low_pow				; call low_pow()
	MOV	PSW, #0x86				; Interrupt enable
$ELSE
	MOV	PSW, #0x86				; Interrupt enable
	HALT						; Stop CPU
$ENDIF
	BR	$.L0_dispatch
.L1_dispatch:						; Switch to 'schedtsk'
	MOVW	AX, HL					; AX := schedtsk
	MOVW	!LOWW(_knl_ctxtsk), AX			; ctxtsk = schedtsk
	MOVW	AX, [HL+4]				; Restore SSP from TCB
	MOVW	SP, AX
	CLRW	AX
	MOVW	!LOWW(_knl_dispatch_disabled), AX	; Dispatch enable 
	POP	HL					; Context restore
	POP	DE
	POP	BC
	POP	AX
	RETI

;/*
; * System-timer Interrupt handler
; */
	.PUBLIC	_knl_systim_inthdr
_knl_systim_inthdr:
	EI						; enable interrupt
	PUSH	AX					; Context save
	PUSH	BC
	PUSH	DE
	PUSH	HL
	MOV	PSW, #MAX_INT_PRI_PSW			; set max interrupt level
	MOVW	AX, !LOWW(_knl_taskindp)		; enter task independent mode
	CMPW	AX, #0x0000
	INCW	AX
	MOVW	!LOWW(_knl_taskindp), AX
	BNZ	$.L0_timerhdr				; multiple interrupt
	MOVW	AX, SP
	MOVW	SP, #LOWW(INTERNAL_RAM_END)		; change to SP
	PUSH	AX					; SSP save
.L0_timerhdr:
	MOV	PSW, #TIM_INT_PRI_PSW			; set timer interrupt level
	CALL	!_knl_timer_handler			; call timer_handler()
	MOV	PSW, #MAX_INT_PRI_PSW			; set max interrupt level
	MOVW	AX, !LOWW(_knl_taskindp)		; enter task independent mode
	DECW	AX
	CMPW	AX, #0x0000
	MOVW	!LOWW(_knl_taskindp), AX
	BNZ	$.L1_timerhdr				; multiple interrupt
	POP	AX					; AX = SSP
	MOVW	SP, AX
.L1_timerhdr:
	BR	!_tk_ret_int_impl

;/* ------------------------------------------------------------------------ */
;/*
; * Interrupt entry routine on the state saved in the interrupt 
; *	stack as shown below.
; *	   High Address	+---------------+
; *			| SPSW(8bit)	| <-- PSW of Before Interrupt
; *			| SPC(24bit)	| <-- PC  of Before Interrupt
; *			| SPSW(8bit)	| <-- PSW(Interrupt Mask Level)
; *			| SPC(24bit)	| <-- PC (Vector Address Data)
; *	    Low Address	+---------------+
; *
; */
	.PUBLIC _knl_hll_inthdr
_knl_hll_inthdr:
	MOV	PSW, #MAX_INT_PRI_PSW			; set max interrupt level
	PUSH	DE					; save DE
	XCHW	AX, HL					; AX <==> HL
	PUSH	AX					; save HL
	MOVW	AX, [SP+4]				; return address ==> AX
	SUBW	AX, #LOWW(call_table)			; vector table address ==> AX
	XCHW	AX, BC					; vector table address ==> BC
	MOVW	[SP+4], AX				; save BC
	MOVW	AX, [SP+6]				; old PSW ==> AX
	XCHW	AX, HL					; AX <==> HL
	MOVW	[SP+6], AX				; save HL
;/* ------------------------------------------------------------------------ */
;/*
; * High level programming language routine for interrupt handler
; *	Called by interrupt entry routine on the state saved in the interrupt 
; *	stack as shown below.
; *	   High Address	+---------------+
; *			| SPSW(8bit)	|
; *			| SPC(24bit)	|
; *			| AX(16bit)	|
; *			| BC(16bit)	|
; *			| DE(16bit)	|
; *			| HL(16bit)	|
; *	    Low Address	+---------------+
; *
; *	BC = intno (vector table address)
; *	H  = PSW (after interrupt handling)
; */
	MOVW	AX, !LOWW(_knl_taskindp)		; enter task independent mode
	CMPW	AX, #0x0000
	INCW	AX
	MOVW	!LOWW(_knl_taskindp), AX
	BNZ	$.L0_no_change_sp			; multiple interrupt
	MOVW	AX, SP
	MOVW	SP, #LOWW(INTERNAL_RAM_END)		; change to SP
	PUSH	AX					; SSP save
.L0_no_change_sp:
	MOV	A, H					; AX = PSW
	OR	A, #0x80				; set IE
	MOV	PSW, A					; set real interrupt level
	MOVW	AX, _knl_inthdr_tbl[BC]			; call hll_inthdr[n](dintno)
	XCHW	AX, BC
	CALL	BC
	MOV	PSW, #MAX_INT_PRI_PSW			; set max interrupt level
	MOVW	AX, !LOWW(_knl_taskindp)		; enter task independent mode
	DECW	AX
	CMPW	AX, #0000
	MOVW	!LOWW(_knl_taskindp), AX
	BNZ	$.L1_no_change_sp			; multiple interrupt
	POP	AX					; AX = SSP
	MOVW	SP, AX
.L1_no_change_sp:
;	BR	!LOWW(_tk_ret_int_impl)

;/*
; * _tk_ret_int()
; *
; * tk_ret_int() processing
; *	When called, the interrupt stack is configured as shown below.
; *	   High Address	+---------------+
; *			| SPSW(8bit)	| Saved when interrupt occur
; *			| SPC(24bit)	|
; *			| AX(16bit)	|
; *			| BC(16bit)	|
; *			| DE(16bit)	|
; *		SSP =>	| HL(16bit)	|
; *	    Low Address	+---------------+
; */
	.PUBLIC _tk_ret_int_impl
_tk_ret_int_impl:
	POP	HL					; Context restore
	POP	DE
	CLRW	AX
	CMPW	AX, !LOWW(_knl_taskindp)		; enter task independent mode
	BNZ	$.L0_tk_ret_int
	CMPW	AX, !LOWW(_knl_dispatch_disabled)	; Is it during dispatch disable?
	BNZ	$.L0_tk_ret_int
	MOVW	AX, !LOWW(_knl_ctxtsk)			; Is dispatch required?
	MOVW	BC, !LOWW(_knl_schedtsk)
	CMPW	AX, BC
	BZ	$.L0_tk_ret_int
	POP	BC					; Context restore
	POP	AX
	BR	!_ret_int_dispatch			; To dispatch processing
.L0_tk_ret_int:						; Dispatch not required
	POP	BC
	POP	AX
	RETI

$ENDIF ; CPU_CORE_RL78S3
