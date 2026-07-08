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

#include <sys/machine_sec.h>
#if defined(EXT_SEC) && defined(CPU_CORE_ARMV8M)

/*
 *	int_armv8m_sec.c (ARMv8-M)  **Secure**
 *
 *	Secure Extension Interrupt controller
 */

#include <tk/tkernel_sec.h>
#include "int_armv8m_sec.h"

/*----------------------------------------------------------------------*/
/*
 * CPU Interrupt Control for ARMv8-M
 *
 */

/*
 * Set Base Priority register
 */
EXPORT void set_basepri(UW intsts)
{
	Asm("msr basepri, %0":: "r"(intsts));
	Asm("isb");
}

/*
 * Get Base Priority register
 */
EXPORT UW get_basepri(void)
{
	UW	basepri;

	Asm("mrs %0, basepri": "=r"(basepri));
	return basepri;
}

/*
 * Disable interrupt
 */
EXPORT UW disint(void)
{
	UW	intsts, maxint;

	maxint = INTPRI_VAL(INTPRI_MAX_EXTINT_PRI);
	Asm("mrs %0, basepri": "=r"(intsts));
	Asm("msr basepri, %0":: "r"(maxint));

	return intsts;
}

#endif /* defined(EXT_SEC) && defined(CPU_CORE_ARMV8M) */
