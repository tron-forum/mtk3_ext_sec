/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 Secure Extension 1.00
 *
 *    Copyright (C) 2025 -2026 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2026/07.
 *
 *----------------------------------------------------------------------
 */

#include <sys/machine.h>
#if defined(EXT_SEC) && defined(CPU_STM32N6)
/*
 *	vector_tbl.h (STM32N6)  **NON-SECURE**
 *	Secure Extension Exception/Interrupt Vector Table
 */
#include "kernel.h"
#include "../../nucleo_stm32n6/sysdepend.h"

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
	0,					/* 7: Reserved */
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
	knl_default_handler,			/* IRQ 96 */
	knl_default_handler,			/* IRQ 97 */
	knl_default_handler,			/* IRQ 98 */
	knl_default_handler,			/* IRQ 99 */
	knl_default_handler,			/* IRQ 100 */
	knl_default_handler,			/* IRQ 101 */
	knl_default_handler,			/* IRQ 102 */
	knl_default_handler,			/* IRQ 103 */
	knl_default_handler,			/* IRQ 104 */
	knl_default_handler,			/* IRQ 105 */
	knl_default_handler,			/* IRQ 106 */
	knl_default_handler,			/* IRQ 107 */
	knl_default_handler,			/* IRQ 108 */
	knl_default_handler,			/* IRQ 109 */
	knl_default_handler,			/* IRQ 110 */
	knl_default_handler,			/* IRQ 111 */
	knl_default_handler,			/* IRQ 112 */
	knl_default_handler,			/* IRQ 113 */
	knl_default_handler,			/* IRQ 114 */
	knl_default_handler,			/* IRQ 115 */
	knl_default_handler,			/* IRQ 116 */
	knl_default_handler,			/* IRQ 117 */
	knl_default_handler,			/* IRQ 118 */
	knl_default_handler,			/* IRQ 119 */
	knl_default_handler,			/* IRQ 120 */
	knl_default_handler,			/* IRQ 121 */
	knl_default_handler,			/* IRQ 122 */
	knl_default_handler,			/* IRQ 123 */
	knl_default_handler,			/* IRQ 124 */
	knl_default_handler,			/* IRQ 125 */
	knl_default_handler,			/* IRQ 126 */
	knl_default_handler,			/* IRQ 127 */
	knl_default_handler,			/* IRQ 128 */
	knl_default_handler,			/* IRQ 129 */
	knl_default_handler,			/* IRQ 130 */
	knl_default_handler,			/* IRQ 131 */
	knl_default_handler,			/* IRQ 132 */
	knl_default_handler,			/* IRQ 133 */
	knl_default_handler,			/* IRQ 134 */
	knl_default_handler,			/* IRQ 135 */
	knl_default_handler,			/* IRQ 136 */
	knl_default_handler,			/* IRQ 137 */
	knl_default_handler,			/* IRQ 138 */
	knl_default_handler,			/* IRQ 139 */
	knl_default_handler,			/* IRQ 140 */
	knl_default_handler,			/* IRQ 141 */
	knl_default_handler,			/* IRQ 142 */
	knl_default_handler,			/* IRQ 143 */
	knl_default_handler,			/* IRQ 144 */
	knl_default_handler,			/* IRQ 145 */
	knl_default_handler,			/* IRQ 146 */
	knl_default_handler,			/* IRQ 147 */
	knl_default_handler,			/* IRQ 148 */
	knl_default_handler,			/* IRQ 149 */
	knl_default_handler,			/* IRQ 150 */
	knl_default_handler,			/* IRQ 151 */
	knl_default_handler,			/* IRQ 152 */
	knl_default_handler,			/* IRQ 153 */
	knl_default_handler,			/* IRQ 154 */
	knl_default_handler,			/* IRQ 155 */
	knl_default_handler,			/* IRQ 156 */
	knl_default_handler,			/* IRQ 157 */
	knl_default_handler,			/* IRQ 158 */
	knl_default_handler,			/* IRQ 159 */
	knl_default_handler,			/* IRQ 160 */
	knl_default_handler,			/* IRQ 161 */
	knl_default_handler,			/* IRQ 162 */
	knl_default_handler,			/* IRQ 163 */
	knl_default_handler,			/* IRQ 164 */
	knl_default_handler,			/* IRQ 165 */
	knl_default_handler,			/* IRQ 166 */
	knl_default_handler,			/* IRQ 167 */
	knl_default_handler,			/* IRQ 168 */
	knl_default_handler,			/* IRQ 169 */
	knl_default_handler,			/* IRQ 170 */
	knl_default_handler,			/* IRQ 171 */
	knl_default_handler,			/* IRQ 172 */
	knl_default_handler,			/* IRQ 173 */
	knl_default_handler,			/* IRQ 174 */
	knl_default_handler,			/* IRQ 175 */
	knl_default_handler,			/* IRQ 176 */
	knl_default_handler,			/* IRQ 177 */
	knl_default_handler,			/* IRQ 178 */
	knl_default_handler,			/* IRQ 179 */
	knl_default_handler,			/* IRQ 180 */
	knl_default_handler,			/* IRQ 181 */
	knl_default_handler,			/* IRQ 182 */
	knl_default_handler,			/* IRQ 183 */
	knl_default_handler,			/* IRQ 184 */
	knl_default_handler,			/* IRQ 185 */
	knl_default_handler,			/* IRQ 186 */
	knl_default_handler,			/* IRQ 187 */
	knl_default_handler,			/* IRQ 188 */
	knl_default_handler,			/* IRQ 189 */
	knl_default_handler,			/* IRQ 190 */
	knl_default_handler,			/* IRQ 191 */
	knl_default_handler,			/* IRQ 192 */
	knl_default_handler,			/* IRQ 193 */
	knl_default_handler,			/* IRQ 194 */
	knl_default_handler,			/* IRQ 195 */
};

#endif	/* USE_KNL_VECTBL */
#endif /* defined(EXT_SEC) && defined(CPU_STM32N6) */
