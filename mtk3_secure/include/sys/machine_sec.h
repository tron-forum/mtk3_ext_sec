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
 *	machine_sec.h  **Secure**
 *
 *	Secure Extension Machine type definition 
 */

#ifndef _EXTSEC_SYS_MACHINE_H_
#define _EXTSEC_SYS_MACHINE_H_

#define Csym(sym) sym

/* ===== System dependencies definitions ================================ */

#if defined(_STM32_NUCLEO_N657_EXTSEC_)
#include <sys/sysdepend/nucleo_stm32n6/machine_sec.h>
#endif

/* ===== C compiler dependencies definitions ============================= */

#ifdef __GNUC__

#define Inline static __inline__
#define Asm __asm__ volatile
#define Noinit(decl) decl __attribute__((section(".noinit")))
#define	Section(decl,name) decl __attribute__((section(#name)))
#define WEAK_FUNC __attribute__((weak))

#define _VECTOR_ENTRY(name) .word name
#define _WEAK_ENTRY(name) .weak name

#define CMSE_NS_CALL  __attribute((cmse_nonsecure_call))
#define CMSE_NS_ENTRY __attribute((cmse_nonsecure_entry))

#endif /* __GNUC__ */

#endif /* _EXTSEC_SYS_MACHINE_H_ */
