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

#include <sys/machine_sec.h>
#if defined(EXT_SEC) && defined(CPU_CORE_ARMV8M)

 /*
 *	sysmem.c (ARMv8-M)  **Secure**
 *	Secure Extension System memory
 */
#include <tk/tkernel_sec.h>

#if USE_STATIC_SEC_SYSMEM
EXPORT UW knl_sysmem_sec[CNF_SEC_SYSMEM_SIZE/sizeof(UW)];
#endif

#endif	// #if defined(EXT_SEC) && defined(CPU_CORE_ARMV8M)
