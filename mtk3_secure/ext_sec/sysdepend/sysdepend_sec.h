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

 /*
 *	sysdepend_sec.h  **Secure**
 *	Secure Extension System-Dependent local defined
 */

#ifndef _EXTSEC_SYSDEP_
#define _EXTSEC_SYSDEP_

#define SYSDEPSEC_PATH_(a)	#a
#define SYSDEPSEC_PATH(a)	SYSDEPSEC_PATH_(a)
#define SYSDEPSEC_SYSDEP()	SYSDEPSEC_PATH(../sysdepend/TARGET_DIR/sysdepend_sec.h)
#include SYSDEPSEC_SYSDEP()

#endif /* _EXTSEC_SYSDEP_ */