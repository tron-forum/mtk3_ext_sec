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
 *	Sysdepend.h (Nucleo-STM32N657N)  **NON-SECURE**
 *	Secure Extension System-Dependent local defined
 */

#ifndef _EXTSEC_SYSDEPEND_SYSDEPEND_
#define _EXTSEC_SYSDEPEND_SYSDEPEND_

#include <kernel/sysdepend/cpu/core/armv8m/sysdepend.h>
#include "../cpu/core/armv8m/sysdepend.h"

IMPORT void knl_init_ptmr(void);

#endif /* _EXTSEC_SYSDEPEND_SYSDEPEND_ */