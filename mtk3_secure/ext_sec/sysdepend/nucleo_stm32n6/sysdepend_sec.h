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
 *    Modifications: Porting toKeil MDK
 *    Modified by UC Technology at 2025/11.
 */

 /*
 *	sysdepend_sec.h (NUCLEO-N657 depended)  **Secure**
 *	Secure Extension System-Dependent local defined
 */

#ifndef _EXTSEC_SYSDEP_NUCLEO_N657_
#define _EXTSEC_SYSDEP_NUCLEO_N657_

#include "../cpu/core/armv8m/sysdepend_sec.h"

/* Management memory area (Symbol defined in the linker script) */
#if defined(__ARMCC_VERSION)		// Keil MDK
extern int Image$$ARM_LIB_HEAP$$Limit;
extern int Image$$ARM_LIB_STACK$$Base;

#define SECURE_LOWMEM_TOP	(&Image$$ARM_LIB_HEAP$$Limit)	
#define SECURE_LOWMEM_LIMIT	(&Image$$ARM_LIB_STACK$$Base)

#elif defined(__GNUC__)			// GCC
extern uint8_t	_end;
extern uint8_t	_estack;
extern uint32_t	_Min_Stack_Size;

#define SECURE_LOWMEM_TOP	(&_end)
#define SECURE_LOWMEM_LIMIT	((void*)((uint32_t)&_estack - (uint32_t)&_Min_Stack_Size))
#endif

#endif /* _EXTSEC_SYSDEP_NUCLEO_N657_ */