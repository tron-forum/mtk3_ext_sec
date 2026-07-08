/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 Secure Extension 1.00
 *
 *    Copyright (C) 2026 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2026/07.
 *
 *----------------------------------------------------------------------
 */

 /*
 *	sysdepend_sec.h (EK-RA8M1 depended)  **Secure**
 *	Secure Extension System-Dependent local defined
 */

#ifndef _EXTSEC_SYSDEP_EK_RA8M1_
#define _EXTSEC_SYSDEP_EK_RA8M1_

#include "../cpu/core/armv8m/sysdepend_sec.h"

#if !USE_STATIC_SEC_SYSMEM
/* Management memory area (Symbol defined in the linker script) */
extern uint8_t	__sec_os_mem$$Base;
extern uint8_t	__sec_os_mem$$Limit;

#define SECURE_LOWMEM_TOP	(&__sec_os_mem$$Base)
#define SECURE_LOWMEM_LIMIT	(&__sec_os_mem$$Limit)

#endif /* !USE_STATIC_SEC_SYSMEM */
#endif /* _EXTSEC_SYSDEP_EK_RA8M1_ */