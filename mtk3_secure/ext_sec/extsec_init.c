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

#include <sys/machine_sec.h>
#ifdef EXT_SEC

/*
 *	extsec_init.c  **SECURE**
 *	Secure Extension Kernel secure part initialization
 */
#include <tk/tkernel_sec.h>

#include "extsec_def.h"
#include "extsec_memory.h"
#include "sysdepend/sysdepend_sec.h"

void* extsec_lowmem_top;
void* extsec_lowmem_limit;

/* 
 * Kernel secure part initialization
 */
EXPORT ER extsec_kernel_init(void)
{
	ER	ercd;


	knl_set_psplim(0xFFFFFFFF);
	knl_set_psp(0);

	/* Set System memory area */
	if(CNF_SYSTEMAREA_TOP == 0) {
		extsec_lowmem_top = SECURE_LOWMEM_TOP;
	} else {
		extsec_lowmem_top = (void*)CNF_SYSTEMAREA_TOP;
	}

	if(CNF_SYSTEMAREA_END == 0) {
		extsec_lowmem_limit = SECURE_LOWMEM_LIMIT;
	} else{
		extsec_lowmem_limit = (void*)CNF_SYSTEMAREA_END;
	}

	ercd = extsec_init_Imalloc();		// Secure Imalloc initial setting
	if(ercd < E_OK) return ercd;

	ercd = extsec_task_initialize();	// Secure TCB Initialization

	return ercd;
}

#endif /* EXT_SEC */