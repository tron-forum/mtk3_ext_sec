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

#ifndef _EXTSEC_SYSDEP_INT_H_
#define _EXTSEC_SYSDEP_INT_H_

/*
 *	int_sec.h  **Secure**
 *
 *	Secure Extension Interrupt controller
 */

#define INTSEC_PATH_(a)		#a
#define INTSEC_PATH(a)		INTSEC_PATH_(a)
#define INTSEC_SYSDEP()		INTSEC_PATH(../sysdepend/TARGET_DIR/int_sec.h)
#include INTSEC_SYSDEP()

#endif	/* _EXTSEC_SYSDEP_INT_H_ */
