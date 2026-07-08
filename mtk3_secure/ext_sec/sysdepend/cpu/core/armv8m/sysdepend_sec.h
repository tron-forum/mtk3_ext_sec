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
 *	sysdepend_sec.h (ARMv8-M)  **Secure**
 *	Secure Extension System-Dependent local defined
 */

#ifndef _EXTSEC_SYSDEP_CPU_CORE_SYSDEPEND_
#define _EXTSEC_SYSDEP_CPU_CORE_SYSDEPEND_

/*
 *	Stack register operation
 */
Inline void knl_set_psp(UW val)
{
	Asm("msr psp, %0"::"r"(val));
}

Inline void knl_set_psplim(UW val)
{
	Asm("msr psplim, %0"::"r"(val));
}

/*
 *	System memory definition
 */
#if USE_STATIC_SEC_SYSMEM

IMPORT UW knl_sysmem_sec[];

#define SECURE_LOWMEM_TOP	((void*)(&knl_sysmem_sec))
#define SECURE_LOWMEM_LIMIT	((void*)((uint32_t)&knl_sysmem_sec + CNF_SEC_SYSMEM_SIZE))

#endif

#endif /* _EXTSEC_SYSDEP_CPU_CORE_SYSDEPEND_ */
