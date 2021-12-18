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
 *	sys_dat.c (RL78/S3)
 *	System data
 */
#include "kernel.h"

EXPORT	INT	knl_taskindp;	/* Task independent status */

/* Temporal stack used when 'dispatch_to_schedtsk' is called */
Noinit(EXPORT UB knl_tmp_stack[TMP_STACK_SIZE]);


#endif /* CPU_CORE_RL78S3 */
