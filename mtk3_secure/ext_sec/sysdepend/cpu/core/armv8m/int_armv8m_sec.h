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

#ifndef _EXTSEC_SYSDEP_INT_CPU_CORE_ARMV8M_H_
#define _EXTSEC_SYSDEP_INT_CPU_CORE_ARMV8M_H_

/*
 *	int_armv8m_sec.h (ARMv8-M)  **Secure**
 *
 *	Secure Extension Interrupt controller
 */

IMPORT void set_basepri(UW intsts);	/* Set Base Priority register */
IMPORT UW get_basepri(void);		/* Get Base Priority register */
IMPORT UW disint(void);			/* Disable interrupt */

#define DI(intsts)		( (intsts) = disint() )
#define EI(intsts)		( set_basepri(intsts) )
#define isDI(intsts)		( (intsts) != 0 )

#define INTLEVEL_DI		(0)
#define INTLEVEL_EI		(255)

#endif	/* _EXTSEC_SYSDEP_INT_CPU_CORE_ARMV8M_H_ */