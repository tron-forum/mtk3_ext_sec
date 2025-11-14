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

#endif /* _EXTSEC_SYSDEP_CPU_CORE_SYSDEPEND_ */
