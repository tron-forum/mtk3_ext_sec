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

#include <sys/machine.h>
#if defined(EXT_SEC) && defined(CPU_RA8M1)
/*
 *	vector_tbl.h (RA8M1)  **NON-SECURE**
 *	Secure Extension Exception/Interrupt Vector Table
 */
#include "kernel.h"
#include "../../ek_ra8m1/sysdepend.h"

#if USE_KNL_VECTBL
/* ------------------------------------------------------------------------ */
/*
 * Exception/Interrupt Vector Table
 * 
 */
void (* const vector_tbl[])() = {
	(void(*)()) (INITIAL_SP),		/* 0: Top of Stack */
	Reset_Handler,				/* 1: Reset Handler */
	knl_nmi_handler,			/* 2: NMI Handler */
	knl_hardfault_handler,			/* 3: Hard Fault Handler */
	knl_memmanage_handler,			/* 4: MPU Fault Handler */
	knl_busfault_handler,			/* 5: Bus Fault Handler */
	knl_usagefault_handler,			/* 6: Usage Fault Handler */
	knl_securefault_handler,		/* 7: Secure Fault Handler */
	0,					/* 8: Reserved */
	0,					/* 9: Reserved */
	0,					/* 10: Reserved */
	knl_svcall_handler,			/* 11: Svcall */
	knl_debugmon_handler,			/* 12: Debug Monitor Handler */
	0,					/* 13: Reserved */
	knl_dispatch_entry,			/* 14: Pend SV */
	knl_systim_inthdr,			/* 15: Systick */

	/* External Interrupts */
	knl_default_handler,			/* IRQ 0 */
	knl_default_handler,			/* IRQ 1 */
	knl_default_handler,			/* IRQ 2 */
	knl_default_handler,			/* IRQ 3 */
	knl_default_handler,			/* IRQ 4 */
	knl_default_handler,			/* IRQ 5 */
	knl_default_handler,			/* IRQ 6 */
	knl_default_handler,			/* IRQ 7 */
	knl_default_handler,			/* IRQ 8 */
	knl_default_handler,			/* IRQ 9 */
	knl_default_handler,			/* IRQ 10 */
	knl_default_handler,			/* IRQ 11 */
	knl_default_handler,			/* IRQ 12 */
	knl_default_handler,			/* IRQ 13 */
	knl_default_handler,			/* IRQ 14 */
	knl_default_handler,			/* IRQ 15 */
	knl_default_handler,			/* IRQ 16 */
	knl_default_handler,			/* IRQ 17 */
	knl_default_handler,			/* IRQ 18 */
	knl_default_handler,			/* IRQ 19 */
	knl_default_handler,			/* IRQ 20 */
	knl_default_handler,			/* IRQ 21 */
	knl_default_handler,			/* IRQ 22 */
	knl_default_handler,			/* IRQ 23 */
	knl_default_handler,			/* IRQ 24 */
	knl_default_handler,			/* IRQ 25 */
	knl_default_handler,			/* IRQ 26 */
	knl_default_handler,			/* IRQ 27 */
	knl_default_handler,			/* IRQ 28 */
	knl_default_handler,			/* IRQ 29 */
	knl_default_handler,			/* IRQ 30 */
	knl_default_handler,			/* IRQ 31 */
	knl_default_handler,			/* IRQ 32 */
	knl_default_handler,			/* IRQ 33 */
	knl_default_handler,			/* IRQ 34 */
	knl_default_handler,			/* IRQ 35 */
	knl_default_handler,			/* IRQ 36 */
	knl_default_handler,			/* IRQ 37 */
	knl_default_handler,			/* IRQ 38 */
	knl_default_handler,			/* IRQ 39 */
	knl_default_handler,			/* IRQ 40 */
	knl_default_handler,			/* IRQ 41 */
	knl_default_handler,			/* IRQ 42 */
	knl_default_handler,			/* IRQ 43 */
	knl_default_handler,			/* IRQ 44 */
	knl_default_handler,			/* IRQ 45 */
	knl_default_handler,			/* IRQ 46 */
	knl_default_handler,			/* IRQ 47 */
	knl_default_handler,			/* IRQ 48 */
	knl_default_handler,			/* IRQ 49 */
	knl_default_handler,			/* IRQ 50 */
	knl_default_handler,			/* IRQ 51 */
	knl_default_handler,			/* IRQ 52 */
	knl_default_handler,			/* IRQ 53 */
	knl_default_handler,			/* IRQ 54 */
	knl_default_handler,			/* IRQ 55 */
	knl_default_handler,			/* IRQ 56 */
	knl_default_handler,			/* IRQ 57 */
	knl_default_handler,			/* IRQ 58 */
	knl_default_handler,			/* IRQ 59 */
	knl_default_handler,			/* IRQ 60 */
	knl_default_handler,			/* IRQ 61 */
	knl_default_handler,			/* IRQ 62 */
	knl_default_handler,			/* IRQ 63 */
	knl_default_handler,			/* IRQ 64 */
	knl_default_handler,			/* IRQ 65 */
	knl_default_handler,			/* IRQ 66 */
	knl_default_handler,			/* IRQ 67 */
	knl_default_handler,			/* IRQ 68 */
	knl_default_handler,			/* IRQ 69 */
	knl_default_handler,			/* IRQ 70 */
	knl_default_handler,			/* IRQ 71 */
	knl_default_handler,			/* IRQ 72 */
	knl_default_handler,			/* IRQ 73 */
	knl_default_handler,			/* IRQ 74 */
	knl_default_handler,			/* IRQ 75 */
	knl_default_handler,			/* IRQ 76 */
	knl_default_handler,			/* IRQ 77 */
	knl_default_handler,			/* IRQ 78 */
	knl_default_handler,			/* IRQ 79 */
	knl_default_handler,			/* IRQ 80 */
	knl_default_handler,			/* IRQ 81 */
	knl_default_handler,			/* IRQ 82 */
	knl_default_handler,			/* IRQ 83 */
	knl_default_handler,			/* IRQ 84 */
	knl_default_handler,			/* IRQ 85 */
	knl_default_handler,			/* IRQ 86 */
	knl_default_handler,			/* IRQ 87 */
	knl_default_handler,			/* IRQ 88 */
	knl_default_handler,			/* IRQ 89 */
	knl_default_handler,			/* IRQ 90 */
	knl_default_handler,			/* IRQ 91 */
	knl_default_handler,			/* IRQ 92 */
	knl_default_handler,			/* IRQ 93 */
	knl_default_handler,			/* IRQ 94 */
	knl_default_handler,			/* IRQ 95 */
};

#endif	/* USE_KNL_VECTBL */
#endif /* defined(EXT_SEC) && defined(CPU_RA8M1) */
