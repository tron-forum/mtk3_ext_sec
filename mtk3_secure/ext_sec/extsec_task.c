/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 Secure Extension 1.00
 *
 *    Copyright (C) 2025 - 2026 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2026/07.
 *
 *----------------------------------------------------------------------
 */

#include <sys/machine_sec.h>
#ifdef EXT_SEC

/*
 *	extsec_task.c  **SECURE**
 *	Secure Extension Task Secure Control
 */

 #include <tk/tkernel_sec.h>

#include "extsec_def.h"
#include "extsec_memory.h"

/*
 * Task control information
 */
Noinit(EXPORT STCB stcb_table[NUM_TSKID]);	/* Task control block */

/*
 * TCB Initialization
 */
EXPORT ER extsec_task_initialize( void )
{
	INT		i;
	STCB	*tcb;
	ID		tskid;

	/* Register all TCBs onto FreeQue */
	for ( tcb = stcb_table, i = 0; i < NUM_TSKID; tcb++, i++ ) {
		tskid = ID_TSK(i);
		tcb->tskid = tskid;
		tcb->tskatr = 0;	/* uninitialized */
	}
	return E_OK;
}

// Called from dispatch_sec.S
EXPORT SCTXB* extsec_get_context(ID tskid)
{
	STCB* tcb;

	if (!CHK_TSKID(tskid)) {
		return NULL;
	}

	tcb = get_stcb(tskid);

	if (!(tcb->tskatr & TA_TZCALL)) {
		return NULL;
	}

	return &tcb->tztskctxb;
}

Inline void secure_setup_context( STCB *tcb )
{
	VB* ssp = (VB*)tcb->itzstack;

	/* Countermeasures for Stack Sealing Vulnerability */
	ssp -= TZ_STACK_SEAL_SIZE;
	out_d((UW)ssp, TZ_STACK_SEAL_VALUE);

	tcb->tztskctxb.ssp = ssp;		/* System stack pointer */

#if USE_SPMON
	tcb->tztskctxb.spsa = tcb->itzstack - tcb->tzstksz;
	tcb->tztskctxb.spea = tcb->itzstack + sizeof(UW) - 1;
#endif

#if USE_FPU && ALWAYS_FPU_ATR
	tcb->tskatr |= TA_FPU;		/* Always set the TA_FPU attribute on all tasks */
#endif
}

EXPORT ER extsec_tcb_initialize(ID tskid, ATR tskatr, W tzstksz)
{
	STCB* tcb;
	void* stack;
	ER er;

	if (!CHK_TSKID(tskid) || !(tskatr & TA_TZCALL) || tzstksz < MIN_TZ_STACK_SIZE) {
		er = E_PAR;
		goto err_ret0;
	}

	tcb = get_stcb(tskid);

	if (tcb->tskatr & TA_TZCALL) {
		er = E_OBJ;
		goto err_ret0;
	}

	stack = extsec_Imalloc(tzstksz);
	if (!stack) {
		er = E_NOMEM;
		goto err_ret0;
	}

	tcb->tskatr = tskatr;
	tcb->itzstack = (VB*)stack + tzstksz;
	tcb->tzstksz = tzstksz;

	secure_setup_context(tcb);

	return E_OK;

err_ret0:
	return er;
}

// CMSE_NS_ENTRY ER secure_tcb_cleanup(ID tskid)
EXPORT ER extsec_tcb_cleanup(ID tskid)
{
	STCB* tcb;
	ER er;

	if (!CHK_TSKID(tskid)) {
		er = E_PAR;
		goto err_ret0;
	}

	tcb = get_stcb(tskid);

	if (!(tcb->tskatr & TA_TZCALL)) {
		er = E_NOEXS;
		goto err_ret0;
	}

	tcb->tskatr = 0;
	extsec_Ifree((VB*)tcb->itzstack - tcb->tzstksz);

	return E_OK;

err_ret0:
	return er;
}

#endif	/* EXT_SEC */