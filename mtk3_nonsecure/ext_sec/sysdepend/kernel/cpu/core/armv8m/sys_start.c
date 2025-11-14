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


#include <sys/machine.h>
#if defined(EXT_SEC) && defined(CPU_CORE_ARMV8M)

/*
 *	sys_start.c (ARMv8-M)  **NON-SECURE**
 *	Secure Extension Kernel start routine 
 */
#include <tk/tkernel.h>
#include <kernel.h>
#include "sysdepend.h"

/* Exception handler table (RAM) */
EXPORT UW knl_exctbl[sizeof(UW)*(N_SYSVEC + N_INTVEC)]
	__attribute__((section(".mtk_exctbl"))) __attribute__ ((aligned(EXCTBL_ALIGN)));


EXPORT UW *knl_exctbl_o;	// Exception handler table (Origin)

EXPORT void		*knl_lowmem_top;	// Head of area (Low address)
EXPORT void		*knl_lowmem_limit;	// End of area (High address)

#if USE_STATIC_SYS_MEM
EXPORT UW knl_system_mem[SYSTEM_MEM_SIZE/sizeof(UW)] __attribute__((section(".mtk_sysmem")));
#endif

#if USE_DEBUG_SYSMEMINFO
EXPORT void		*knl_sysmem_top	= 0;
EXPORT void		*knl_sysmem_end	= 0;
#endif

EXPORT void knl_start_mtkernel(void)
{
	UW	*src, *top;
	UW	reg;
	INT	i;

	disint();		// Disable Interrupt

	knl_startup_hw();

	/* Copy exception handler (ROM -> RAM) */
#if USE_KNL_VECTBL
	src = knl_exctbl_o = (UW*)vector_tbl;
#else
	src = knl_exctbl_o = (UW*)in_w(SCB_VTOR);
#endif
	top = (UW*)knl_exctbl;
	for(i=0; i < (N_SYSVEC + N_INTVEC); i++) {
		*top++ = *src++;
	}
	out_w(SCB_VTOR, (UW)knl_exctbl);

#if USE_CACHE
	if(knl_check_dcache()) {	// Clear D-cache if it is valid
		knl_clean_dcache_adr(knl_exctbl, sizeof(knl_exctbl));
	}
	if(knl_check_icache()) {	// Clear I-cache if it is valid
		knl_dsb();
		knl_invalidate_icache();
		knl_isb();
	}
#endif	/* USE_CACHE */

	/* Configure exception priorities */
	reg = *(_UW*)SCB_AIRCR;
	reg = (reg & (~AIRCR_PRIGROUP7)) | AIRCR_PRIGROUP3;	// PRIGRP:SUBPRI = 4 : 4
	*(_UW*)SCB_AIRCR = (reg & 0x0000FFFF) | AIRCR_VECTKEY;

	/* Enable UsageFault & BusFault & MemFault */
	out_w(SCB_SHCSR, SHCSR_USGFAULTENA | SHCSR_BUSFAULTENA | SHCSR_MEMFAULTENA);

	out_w(SCB_SHPR2, SCB_SHPR2_VAL);		// SVC pri = 0
	out_w(SCB_SHPR3, SCB_SHPR3_VAL);		// SysTick = 1 , PendSV = 15

#if USE_IMALLOC
#if USE_STATIC_SYS_MEM
	knl_lowmem_top = knl_system_mem;
	knl_lowmem_limit = &knl_system_mem[SYSTEM_MEM_SIZE/sizeof(UW)];
#else
	/* Set System memory area */
	if(INTERNAL_RAM_START > SYSTEMAREA_TOP) {
		knl_lowmem_top = (UW*)INTERNAL_RAM_START;
	} else {
		knl_lowmem_top = (UW*)SYSTEMAREA_TOP;
	}
	if((UW)knl_lowmem_top < UNUSED_RAM_TOP) {
		knl_lowmem_top = (UW*)UNUSED_RAM_TOP;
	}

	if((SYSTEMAREA_END != 0) && (INTERNAL_RAM_END > CNF_SYSTEMAREA_END)) {
		knl_lowmem_limit = (UW*)(SYSTEMAREA_END - EXC_STACK_SIZE);
	} else {
		knl_lowmem_limit = (UW*)(INTERNAL_RAM_END - EXC_STACK_SIZE);
	}
#endif

#if TRUSTZONE_SCALL
	SECURE_extsec_knlinit();	// Kernel secure part initialization
#endif

#if USE_DEBUG_SYSMEMINFO
	knl_sysmem_top	= knl_lowmem_top;
	knl_sysmem_end	= knl_lowmem_limit;
#endif	// USE_DEBUG_MEMINFO
#endif	// USE_IMALLOC

	/* Temporarily disable stack pointer protection */
	Asm ("msr msplim, %0" : : "r" ((uint32_t)INTERNAL_RAM_START));

	/* Startup Kernel */
	knl_main();		// *** No return ****/
	while(1);		// guard - infinite loops
}

#endif	/* defined(EXT_SEC) && defined(CPU_CORE_ARMV8M) */
