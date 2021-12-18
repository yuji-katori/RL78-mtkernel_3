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
#include <sys/machine.h>
#ifdef CPU_CORE_RL78S3
/*
 *	interrupt.c (RL78/S3)
 *	Interrupt control
 */

#include "kernel.h"
#include "../../../sysdepend.h"

#ifdef CLANGSPEC
INTFP knl_inthdr_tbl[N_INTVEC>>1];	/* HLL Interrupt Handler Table */
#else
FP knl_inthdr_tbl[N_INTVEC>>1];		/* HLL Interrupt Handler Table */
#endif /* CLANGSPEC */

/* ----------------------------------------------------------------------- */
/*
 * Set interrupt handler (Used in tk_def_int())
 */
#ifdef CLANGSPEC
EXPORT ER knl_define_inthdr( INT intno, ATR intatr, INTFP inthdr )
#else
EXPORT ER knl_define_inthdr( INT intno, ATR intatr, FP inthdr )
#endif /* CLANGSPEC */
{
	if(inthdr != NULL) {
		if ( (intatr & TA_HLNG) != 0 ) {
			knl_inthdr_tbl[intno>>1] = inthdr;
		}		
	} else 	{	/* Clear interrupt handler */
		knl_inthdr_tbl[intno>>1] = Default_Handler;
	}

	return E_OK;
}

/* ----------------------------------------------------------------------- */
/*
 * Return interrupt handler (Used in tk_ret_int())
 */
EXPORT void knl_return_inthdr(void)
{
	/* No processing in RL78. */
	return;
}

/* ------------------------------------------------------------------------ */
/*
 * Interrupt initialize
 */
EXPORT ER knl_init_interrupt( void )
{
	INT i;
	
	for( i=0 ; i<N_INTVEC>>1 ; i++ )
		knl_inthdr_tbl[i] = Default_Handler;
	/* No processing in RL78. */
	return E_OK;
}

/*
 * Default Handler
 */
EXPORT void Default_Handler(UINT intno)
{
#if USE_EXCEPTION_DBG_MSG
#ifdef CLANGSPEC
	tm_printf("Undefine Exception!! Vector Address is 0x%04X.\n", intno);
#else
	tm_printf((UB*)"Undefine Exception!! Vector Address is 0x%04X.\n", intno);
#endif /* CLANGSPEC */
#endif
	while(1);
}


#endif	/* CPU_CORE_RL78S3 */