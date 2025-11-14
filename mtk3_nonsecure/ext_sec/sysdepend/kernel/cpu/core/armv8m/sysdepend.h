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

/*
 *	sysdepend.h (ARMv8-M)  **NON-SECURE**
 *	Secure Extension System-Dependent local defined
 */

#ifndef _EXTSEC_SYSDEPEND_CPU_CORE_SYSDEPEND_
#define _EXTSEC_SYSDEPEND_CPU_CORE_SYSDEPEND_

/* --------------------------------------------------------------------- */
/*
 * TrustZone Support
*/
#if TRUSTZONE_SCALL	// Enable Secure Call

/*
 * Task System Dependent definition
 */
#undef DEFINE_TSK_SYSDEPEND
#define DEFINE_TSK_SYSDEPEND	1

#undef TCB_SYSDEPEND_INFO
#define TCB_SYSDEPEND_INFO	W tzstksz;	/* TrustZone secure stack size */

/* 
 * OS Secure Call
 */
IMPORT ER SECURE_extsec_knlinit(void);

IMPORT ER SECURE_extsec_tcbinit(ID tskid, ATR tskatr, SZ tzstksz);
IMPORT ER SECURE_extsec_tcbclnup(ID tskid);

/* form Dispatcher */
IMPORT void secure_save_context(ID tskid);
IMPORT void secure_restore_context(ID tskid);

#endif /* TRUSTZONE_SCALL */


/* --------------------------------------------------------------------- */
/*
 * Exception/Interrupt Vector Table
*/
#if USE_KNL_VECTBL

IMPORT void (* const vector_tbl[])();

#endif	/* USE_KNL_VECTBL */

#endif /* _EXTSEC_SYSDEPEND_CPU_CORE_SYSDEPEND_ */
