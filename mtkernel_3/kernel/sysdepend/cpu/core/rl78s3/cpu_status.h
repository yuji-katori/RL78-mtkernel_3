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
 *	cpu_status.h (RL78/S3)
 *	CPU Dependent Definition
 */

#ifndef _SYSDEPEND_CPU_CORE_STATUS_
#define _SYSDEPEND_CPU_CORE_STATUS_

#include <tk/syslib.h>
#include <sys/sysdef.h>

/*
 * Start/End critical section
 */
#define BEGIN_CRITICAL_SECTION	{ UINT _sr_ = disint();
#define END_CRITICAL_SECTION	if ( !isDI(_sr_)			\
				  && knl_ctxtsk != knl_schedtsk		\
				  && !knl_dispatch_disabled ) {		\
					knl_dispatch();			\
				}					\
				enaint(_sr_); }

/*
 * Start/End interrupt disable section
 */
#define BEGIN_DISABLE_INTERRUPT	{ UINT _sr_ = disint();
#define END_DISABLE_INTERRUPT	enaint(_sr_); }

/*
 * Interrupt enable/disable
 */
#define ENABLE_INTERRUPT	{ enaint(0); }
#define DISABLE_INTERRUPT	{ disint(); }

/*
 * Enable interrupt nesting
 *	Enable the interrupt that has a higher priority than 'level.'
 */
#define ENABLE_INTERRUPT_UPTO(level)	{ enaint(level); }

/*
 *  Task-independent control
 */
IMPORT	INT	knl_taskindp;		/* Task independent status */

/*
 * If it is the task-independent part, TRUE
 */
Inline BOOL knl_isTaskIndependent( void )
{
	return knl_taskindp > 0 ? TRUE : FALSE;
}
/*
 * Move to/Restore task independent part
 */
Inline void knl_EnterTaskIndependent( void )
{
	knl_taskindp++;
}
Inline void knl_LeaveTaskIndependent( void )
{
	knl_taskindp--;
}

/*
 * Move to/Restore task independent part
 */
#define ENTER_TASK_INDEPENDENT	{ knl_EnterTaskIndependent(); }
#define LEAVE_TASK_INDEPENDENT	{ knl_LeaveTaskIndependent(); }

/* ----------------------------------------------------------------------- */
/*
 *	Check system state
 */

/*
 * When a system call is called from the task independent part, TRUE
 */
#define in_indp()	( knl_isTaskIndependent() || knl_ctxtsk == NULL )

/*
 * When a system call is called during dispatch disable, TRUE
 * Also include the task independent part as during dispatch disable.
 */
#define in_ddsp()	( knl_dispatch_disabled	\
			|| in_indp()		\
			|| isDI(__get_psw()^0xFF) )

/*
 * When a system call is called during CPU lock (interrupt disable), TRUE
 * Also include the task independent part as during CPU lock.
 */
#define in_loc()	( in_indp()		\
			|| isDI(__get_psw()^0xFF) )

/*
 * When a system call is called during executing the quasi task part, TRUE
 * Valid only when in_indp() == FALSE because it is not discriminated from 
 * the task independent part. 
 */
#define in_qtsk()	( knl_ctxtsk->sysmode > knl_ctxtsk->isysmode )

/* ----------------------------------------------------------------------- */
/*
 *	Task dispatcher startup
 */

 /*
 * Throw away the current task context. 
 * and forcibly dispatch to the task that should be performed next.
 *	Use at system startup and 'tk_ext_tsk, tk_exd_tsk.'
 */
Inline  void knl_force_dispatch( void )
{
IMPORT void knl_dispatch_to_schedtsk( void );
	knl_dispatch_to_schedtsk( );		/* Dispatcher call */
}

/*
 * Start task dispatcher
 */
Inline void knl_dispatch( void )
{
IMPORT void knl_dispatch_entry( void );		/* Dispatcher call */
	knl_dispatch_entry( );
}

/* ----------------------------------------------------------------------- */
/*
 * Task context block
 */
typedef struct {
	void	*ssp;		/* System stack pointer */
} CTXB;


#endif /* _SYSDEPEND_CPU_CORE_STATUS_ */
