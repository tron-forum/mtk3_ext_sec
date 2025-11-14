/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 Secure Extension 1.00.B0
 *
 *    Copyright (C) 2025 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2025/11.
 *
 *----------------------------------------------------------------------
 */

#include <sys/machine.h>
#if defined(EXT_SEC) && defined(CPU_CORE_ARMV8M)
/*
 *	task_sysdep.c (ARMv8-M)  **NON-SECURE**
 *	Secure Extension Task System Dependent definition
 */
#include <tk/tkernel.h>
#include <kernel.h>

#if DEFINE_TSK_SYSDEPEND

EXPORT ER knl_tcb_sysdep_cre(TCB *tcb, CONST T_CTSK *pk_ctsk)
{
	ER	ercd = E_OK;

	if ( (tcb->tskatr & TA_TZCALL) != 0 ) {
		if( knl_isTaskIndependent() || (knl_ctxtsk != NULL && ((knl_ctxtsk->tskatr & TA_TZCALL) == 0))) {
			return E_CTX;
		}
		tcb->tzstksz = pk_ctsk->tzstksz;
		ercd = SECURE_extsec_tcbinit(tcb->tskid, tcb->tskatr, tcb->tzstksz);
	}
	return ercd;
}

EXPORT ER knl_tcb_sysdep_del(TCB *tcb)
{
	ER	ercd = E_OK;

	if ( (tcb->tskatr & TA_TZCALL) != 0 ) {
		if( knl_isTaskIndependent() || (knl_ctxtsk != NULL && ((knl_ctxtsk->tskatr & TA_TZCALL) == 0))) {
			return E_CTX;
		}
		ercd = SECURE_extsec_tcbclnup(tcb->tskid);
	}
	return ercd;
}

#endif	/* DEFINE_TSK_SYSDEPEND */
#endif	/* defined(EXT_SEC) && defined(CPU_CORE_ARMV8M) */