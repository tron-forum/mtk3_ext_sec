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
 *	machine_sec.h  **Secure**
 *	Secure Extension Machine type definition (EK-RA8M1)
 */

#ifndef _EXTSEC_SYS_SYSDEPEND_MACHINE_H_
#define _EXTSEC_SYS_SYSDEPEND_MACHINE_H_

/*
 * [TYPE]_[CPU]		TARGET SYSTEM
 * CPU_xxxx		CPU type
 * CPU_CORE_xxx		CPU core type
 */

/* ----- EK-RA8M1 (CPU: R7FA8M1AHECBD) definition ----- */
#define EK_RA8M1		1	/* Target Board    : EK-RA8M1 */

#define CPU_RA8			1	/* Target CPU type : RA8 series */
#define CPU_RA8M1		1	/* Target CPU      : RA8M1 */

#define CPU_CORE_ARMV8M		1	/* Target CPU-Core type : ARMv8-M */
#define CPU_CORE_ACM85		1	/* Target CPU-Core      : ARM Cortex-M85 */

#define TARGET_DIR		ek_ra8m1	/* Sysdepend-Directory name */
#define	TARGET_CPU_DIR		ra8m1		/* Sysdepend-CPU-Directory name */

#define KNL_SYSDEP_PATH		ek_ra8m1	/* Kernel sysdepend path */

/* ----- Extension definition ----*/
#define EXT_SEC			1	/* Secure Extension for Arm (TrustZone) */

#endif /* _EXTSEC_SYS_SYSDEPEND_MACHINE_H_ */
