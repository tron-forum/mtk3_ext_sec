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
 *	sysdef_sec.h  **Secure**
 *
 *	Secure Extension System dependencies definition (ARMv8-M)
 *	Included also from assembler program.
 */

#ifndef _EXTSEC_SYS_SYSDEF_DEPEND_CORE_H_
#define _EXTSEC_SYS_SYSDEF_DEPEND_CORE_H_

/*
 * The number of the implemented bit width for priority value fields.
 * The LSB of (8-INTPRI_BITWIDTH) bits priority value is ignored, 
 * Bacause each priory bits is INTPRI_BITWIDTH bits.
 */
#define INTPRI_VAL(x)	((x) << (8-INTPRI_BITWIDTH))

/*
 *    TrustZone Stack Seal definition
 */
#define TZ_STACK_SEAL_SIZE	8U
#define TZ_STACK_SEAL_VALUE	0xFEF5EDA5FEF5EDA5ULL

#endif /* _EXTSEC_SYS_SYSDEF_DEPEND_CORE_H_ */