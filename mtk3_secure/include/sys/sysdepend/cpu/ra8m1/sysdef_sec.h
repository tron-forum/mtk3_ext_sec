/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 Secure Extension 1.00.B2
 *
 *    Copyright (C) 2026 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2026/03.
 *
 *----------------------------------------------------------------------
 */

/*
 *	sysdef_sec.h  **SECURE**
 *	Secure Extension System dependencies definition (RA8M1 depended)
 *	Included also from assembler program.
 */

#ifndef _EXTSEC_SYS_SYSDEF_DEPEND_CPU_H_
#define _EXTSEC_SYS_SYSDEF_DEPEND_CPU_H_

#include <sys/machine_sec.h>

/* CPU Core-dependent definition */
#include <sys/sysdepend/cpu/core/armv8m/sysdef_sec.h>

/*
 * The number of the implemented bit width for priority value fields.
 */
#define INTPRI_BITWIDTH		4

/* ------------------------------------------------------------------------ */
/*
 * Interrupt Priority Levels
 */
#define INTPRI_MAX_EXTINT_PRI	1	/* Highest Ext. interrupt level */


#endif /* _EXTSEC_SYS_SYSDEF_DEPEND_CPU_H_ */
