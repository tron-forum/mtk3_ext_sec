/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 Secure Extension 1.00.B2
 *
 *    Copyright (C) 2025 - 2026 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2026/03.
 *
 *----------------------------------------------------------------------
 */
 /*
 *	sysdepend_sec.h (NUCLEO-N657 depended)  **Secure**
 *	Secure Extension System-Dependent local defined
 */

#ifndef _EXTSEC_SYSDEP_NUCLEO_N657_
#define _EXTSEC_SYSDEP_NUCLEO_N657_

#include "../cpu/core/armv8m/sysdepend_sec.h"

#if !USE_STATIC_SEC_SYSMEM
/* Management memory area (Symbol defined in the linker script) */
extern uint8_t	_end;
extern uint8_t	_estack;
extern uint32_t	_Min_Stack_Size;

#define SECURE_LOWMEM_TOP	(&_end)
#define SECURE_LOWMEM_LIMIT	((void*)((uint32_t)&_estack - (uint32_t)&_Min_Stack_Size))

#endif /* !USE_STATIC_SEC_SYSMEM */
#endif /* _EXTSEC_SYSDEP_NUCLEO_N657_ */