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
$IFDEF CPU_R5F104LE

;/*
; *	vector.asm (R5F104LE)
; *	Exception/Interrupt Vector Table
; */

knl_inthdr_entry2	.VECTOR	0x04		;  INTWDTI
knl_inthdr_entry3	.VECTOR	0x06		;  INTLVI
knl_inthdr_entry4	.VECTOR	0x08		;  INTP0
knl_inthdr_entry5	.VECTOR	0x0A		;  INTP1
knl_inthdr_entry6	.VECTOR	0x0C		;  INTP2
knl_inthdr_entry7	.VECTOR	0x0E		;  INTP3
knl_inthdr_entry8	.VECTOR	0x10		;  INTP4
knl_inthdr_entry9	.VECTOR	0x12		;  INTP5
knl_inthdr_entry10	.VECTOR	0x14		;  INTST2/INTCSI20/INTIIC20
knl_inthdr_entry11	.VECTOR	0x16		;  INTSR2/INTCSI21/INTIIC21
knl_inthdr_entry12	.VECTOR	0x18		;  INTSRE2/INTTM11H
						;
						;
knl_inthdr_entry15	.VECTOR	0x1E		;  INTST0/INTCSI00/INTIIC00
knl_inthdr_entry16	.VECTOR	0x20		;  INTSR0/INTCSI01/INTIIC01
knl_inthdr_entry17	.VECTOR	0x22		;  INTSRE0/INTTM01H
knl_inthdr_entry18	.VECTOR	0x24		;  INTST1/INTCSI10/INTIIC10
knl_inthdr_entry19	.VECTOR	0x26		;  INTSR1/INTCSI11/INTIIC11
knl_inthdr_entry20	.VECTOR	0x28		;  INTSRE1/INTTM03H
knl_inthdr_entry21	.VECTOR	0x2A		;  INTIICA0
knl_inthdr_entry22	.VECTOR	0x2C		;  INTTM00
knl_inthdr_entry23	.VECTOR	0x2E		;  INTTM01
knl_inthdr_entry24	.VECTOR	0x30		;  INTTM02
knl_inthdr_entry25	.VECTOR	0x32		;  INTTM03
knl_inthdr_entry26	.VECTOR	0x34		;  INTAD
knl_inthdr_entry27	.VECTOR	0x36		;  INTRTC
_knl_systim_inthdr	.VECTOR	0x38		;  INTIT
knl_inthdr_entry29	.VECTOR	0x3A		;  INTKR
knl_inthdr_entry30	.VECTOR	0x3C		;  INTST3/INTCSI30/INTIIC30
knl_inthdr_entry31	.VECTOR	0x3E		;  INTSR3/INTCSI31/INTIIC31
knl_inthdr_entry32	.VECTOR	0x40		;  INTTRJ0
knl_inthdr_entry33	.VECTOR	0x42		;  INTTM10
knl_inthdr_entry34	.VECTOR	0x44		;  INTTM11
knl_inthdr_entry35	.VECTOR	0x46		;  INTTM12
knl_inthdr_entry36	.VECTOR	0x48		;  INTTM13
knl_inthdr_entry37	.VECTOR	0x4A		;  INTP6
knl_inthdr_entry38	.VECTOR	0x4C		;  INTP7
knl_inthdr_entry39	.VECTOR	0x4E		;  INTP8
knl_inthdr_entry40	.VECTOR	0x50		;  INTP9
knl_inthdr_entry41	.VECTOR	0x52		;  INTP10/INTCMP0
knl_inthdr_entry42	.VECTOR	0x54		;  INTP11/INTCMP1
knl_inthdr_entry43	.VECTOR	0x56		;  INTTRD0
knl_inthdr_entry44	.VECTOR	0x58		;  INTTRD1
knl_inthdr_entry45	.VECTOR	0x5A		;  INTTRG
knl_inthdr_entry46	.VECTOR	0x5C		;  INTSRE3/INTTM13H
						;
knl_inthdr_entry48	.VECTOR	0x60		;  INTIICA1
knl_inthdr_entry49	.VECTOR	0x62		;  INTFL

_knl_hll_inthdr		.VECTOR	0x7E		;  BRK

	.PUBLIC	call_table
	.SECTION .text,TEXT
call_table:		BRK			; 01
knl_inthdr_entry2:	BRK			; 02 INTWDTI
knl_inthdr_entry3:	BRK			; 03 INTLVI
knl_inthdr_entry4:	BRK			; 04 INTP0
knl_inthdr_entry5:	BRK			; 05 INTP1
knl_inthdr_entry6:	BRK			; 06 INTP2
knl_inthdr_entry7:	BRK			; 07 INTP3
knl_inthdr_entry8:	BRK			; 08 INTP4
knl_inthdr_entry9:	BRK			; 09 INTP5
knl_inthdr_entry10:	BRK			; 10 INTST2/INTCSI20/INTIIC20
knl_inthdr_entry11:	BRK			; 11 INTSR2/INTCSI21/INTIIC21
knl_inthdr_entry12:	BRK			; 12 INTSRE2/INTTM11H
			BRK			; 13
			BRK			; 14
knl_inthdr_entry15:	BRK			; 15 INTST0/INTCSI00/INTIIC00
knl_inthdr_entry16:	BRK			; 16 INTSR0/INTCSI01/INTIIC01
knl_inthdr_entry17:	BRK			; 17 INTSRE0/INTTM01H
knl_inthdr_entry18:	BRK			; 18 INTST1/INTCSI10/INTIIC10
knl_inthdr_entry19:	BRK			; 19 INTSR1/INTCSI11/INTIIC11
knl_inthdr_entry20:	BRK			; 20 INTSRE1/INTTM03H
knl_inthdr_entry21:	BRK			; 21 INTIICA0
knl_inthdr_entry22:	BRK			; 22 INTTM00
knl_inthdr_entry23:	BRK			; 23 INTTM01
knl_inthdr_entry24:	BRK			; 24 INTTM02
knl_inthdr_entry25:	BRK			; 25 INTTM03
knl_inthdr_entry26:	BRK			; 26 INTAD
knl_inthdr_entry27:	BRK			; 27 INTRTC
			BRK			; 28 INTIT
knl_inthdr_entry29:	BRK			; 29 INTKR
knl_inthdr_entry30:	BRK			; 30 INTST3/INTCSI30/INTIIC30
knl_inthdr_entry31:	BRK			; 31 INTSR3/INTCSI31/INTIIC31
knl_inthdr_entry32:	BRK			; 32 INTTRJ0
knl_inthdr_entry33:	BRK			; 33 INTTM10
knl_inthdr_entry34:	BRK			; 34 INTTM11
knl_inthdr_entry35:	BRK			; 35 INTTM12
knl_inthdr_entry36:	BRK			; 36 INTTM13
knl_inthdr_entry37:	BRK			; 37 INTP6
knl_inthdr_entry38:	BRK			; 38 INTP7
knl_inthdr_entry39:	BRK			; 39 INTP8
knl_inthdr_entry40:	BRK			; 40 INTP9
knl_inthdr_entry41:	BRK			; 41 INTP10/INTCMP0
knl_inthdr_entry42:	BRK			; 42 INTP11/INTCMP1
knl_inthdr_entry43:	BRK			; 43 INTTRD0
knl_inthdr_entry44:	BRK			; 44 INTTRD1
knl_inthdr_entry45:	BRK			; 45 INTTRG
knl_inthdr_entry46:	BRK			; 46 INTSRE3/INTTM13H
			BRK			; 47
knl_inthdr_entry48:	BRK			; 48 INTIICA1
knl_inthdr_entry49:	BRK			; 49 INTFL

$ENDIF ; CPU_R5F104LE
