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
 *	extsec_api.c  **SECURE**
 *	Secure Extension Kernel Secure API (Only used in the kernel)
 */
#include <tk/tkernel_sec.h>
#include "extsec_def.h"
#include "sysdepend/int_sec.h"

EXPORT _UW	extsec_status = 0;	/* Secure part status */

CMSE_NS_ENTRY ER SECURE_extsec_knlinit(void)
{
	UINT	imask;
	ER	ercd;

	DI(imask);
	if(extsec_status != 0) {
		EI(imask);
		return E_SYS;
	}

	ercd = extsec_kernel_init();
	if(ercd == E_OK) {
		extsec_status |= KNLSEC_STS_INITIALIZED;
	}

	EI(imask);

	return ercd;
}

CMSE_NS_ENTRY ER SECURE_extsec_tcbinit(ID tskid, ATR tskatr, SZ tzstksz)
{
	UINT	imask;
	ER	ercd;

	DI(imask);
	if(extsec_status != KNLSEC_STS_INITIALIZED) {
		EI(imask);
		return E_SYS;
	}
	extsec_status |= KNLSEC_STS_INAPI;
	EI(imask);

	ercd = extsec_tcb_initialize(tskid, tskatr, tzstksz);

	DI(imask);
	extsec_status &= ~KNLSEC_STS_INAPI;
	EI(imask);

	return ercd;
}

CMSE_NS_ENTRY ER SECURE_extsec_tcbclnup(ID tskid)
{
	UINT	imask;
	ER	ercd;

	DI(imask);
	if(extsec_status != KNLSEC_STS_INITIALIZED) {
		EI(imask);
		return E_SYS;
	}
	extsec_status |= KNLSEC_STS_INAPI;
	EI(imask);

	ercd = extsec_tcb_cleanup(tskid);

	DI(imask);
	extsec_status &= ~KNLSEC_STS_INAPI;
	EI(imask);

	return ercd;
}

#endif	/* EXT_SEC */