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

/*
 *	config.h
 *	User Configuration Definition
 */

#ifndef __TK_CONFIG__
#define __TK_CONFIG__

/*---------------------------------------------------------------------- */
/* SYSCONF : micro T-Kernel system configuration
 */

#define	CFN_MAX_TSKPRI		16	/* Task Max priority */

#define CFN_TIMER_PERIOD	1	/* System timer period */

/* Maximum number of kernel objects */
#define CFN_MAX_TSKID		4	/* Task */
#define CFN_MAX_SEMID		2	/* Semaphore */
#define CFN_MAX_FLGID		2	/* Event flag */
#define CFN_MAX_MBXID		2	/* Mailbox */
#define CFN_MAX_MTXID		2	/* Mutex */
#define CFN_MAX_MBFID		2	/* Message buffer */
#define CFN_MAX_MPFID		2	/* Fixed size memory pool */
#define CFN_MAX_MPLID		2	/* Memory pool */
#define CFN_MAX_CYCID		2	/* Cyclic handler */
#define CFN_MAX_ALMID		2	/* Alarm handler */
#define CFN_MAX_SSYID		2	/* Subsystem */
#define CFN_MAX_SSYPRI		1	/* Subsystem Priority */

/* Device configuration */
#define CFN_MAX_REGDEV		(2)	/* Max registered device */
#define CFN_MAX_OPNDEV		(4)	/* Max open device */
#define CFN_MAX_REQDEV		(4)	/* Max request device */
#define CFN_DEVT_MBFSZ0		(-1)	/* message buffer size for event notification */
#define CFN_DEVT_MBFSZ1		(-1)	/* message max size for event notification */

/* Version Number */
#define CFN_VER_MAKER		0x0008
#define CFN_VER_PRID		0x0002
#define CFN_VER_PRVER		0x0001
#define CFN_VER_PRNO1		0x524C
#define CFN_VER_PRNO2		0x3738
#define CFN_VER_PRNO3		0x4343
#define CFN_VER_PRNO4		0x524C


/*---------------------------------------------------------------------- */
/* Stack size definition
 */
#define CFN_EXC_STACK_SIZE	(256)	/* Exception stack size */
#define	CFN_TMP_STACK_SIZE	(12)	/* Temporary stack size */


/*---------------------------------------------------------------------- */
/* System function selection
 *   1: Use function.  0: No use function.
 */
#define USE_IMALLOC		(1)	/* Use dynamic memory allocation */
#define USE_SHUTDOWN		(1)	/* Use System shutdown */


/*---------------------------------------------------------------------- */
/* Check API parameter
 *   1: Check parameter  0: Do not check parameter
 */
#define CHK_NOSPT		(1)	/* Check unsupported function (E_NOSPT) */
#define CHK_RSATR		(1)	/* Check reservation attribute error (E_RSATR) */
#define CHK_PAR			(1)	/* Check parameter (E_PAR) */
#define CHK_ID			(1)	/* Check object ID range (E_ID) */
#define CHK_OACV		(1)	/* Check Object Access Violation (E_OACV) */
#define CHK_CTX			(1)	/* Check whether task-independent part is running (E_CTX) */
#define CHK_CTX1		(1)	/* Check dispatch disable part */
#define CHK_CTX2		(1)	/* Check task independent part */
#define CHK_SELF		(1)	/* Check if its own task is specified (E_OBJ) */

#define	CHK_TKERNEL_CONST	(1)	/* Check const-type parameter */

/*---------------------------------------------------------------------- */
/* User initialization program (UserInit)
 *
 */
#define	USE_USERINIT		(0)	/* 1: Use UserInit  0: Do not use UserInit */
#define RI_USERINIT		(0)	/* UserInit start address */


/*---------------------------------------------------------------------- */
/* Debugger support function
 *   1: Valid  0: Invalid
 */
#define USE_DBGSPT		(0)	/* Use mT-Kernel/DS */
#define USE_OBJECT_NAME		(1)	/* Use DS object name */

#define OBJECT_NAME_LENGTH	(8)	/* DS Object name length */

/*---------------------------------------------------------------------- */
/* Use T-Monitor Compatible API Library  & Message to terminal.
 *   1: Valid  0: Invalid
 */
#define	USE_TMONITOR		(1)	/* T-Monitor API */
#define USE_SYSTEM_MESSAGE	(1)	/* System Message */
#define USE_EXCEPTION_DBG_MSG	(1)	/* Excepttion debug message */

/*
 *	Use function Definition
 */
#include "config_func.h"

#endif /* __TK_CONFIG__ */
