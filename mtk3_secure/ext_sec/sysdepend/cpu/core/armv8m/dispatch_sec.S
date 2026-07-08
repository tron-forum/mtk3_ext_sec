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
 *	dispatch_sec.S (ARMv8-M)  **Secure**
 *	Secure Extension Dispatch secure API (Called by Non-secure dispatcher)
 */

#define	_in_asm_source_

/*----------------------------------------------------------------------*/
/*
 *      offset data in CTXB
 */
#define CTXB_ssp        0
#define CTXB_spsa       4
#define CTXB_spea       8

	.code 16
	.syntax unified
	.thumb

// ----

	.text
	.align 2
	.thumb
	.thumb_func
	.globl Csym(__acle_se_secure_save_context)
	.globl Csym(secure_save_context)
	.type  Csym(__acle_se_secure_save_context),%function
	.type  Csym(secure_save_context),%function

/* void secure_save_context(tskid); */
Csym(__acle_se_secure_save_context):
Csym(secure_save_context):
	push	{lr}
	bl		Csym(extsec_get_context)	// r0: SECURE_CTXB
	pop		{lr}
	cmp		r0, #0
	beq		skip_save
	str		sp, [r0, #CTXB_ssp]
skip_save:
	bxns	lr
	.size	secure_save_context, .-secure_save_context

// ----

	.text
	.align 2
	.thumb
	.thumb_func
	.globl Csym(__acle_se_secure_restore_context)
	.globl Csym(secure_restore_context)
	.type  Csym(__acle_se_secure_restore_context),%function
	.type  Csym(secure_restore_context),%function

// void secure_restore_context(tskid); */
Csym(__acle_se_secure_restore_context):
Csym(secure_restore_context):
	push	{lr}
	bl		Csym(extsec_get_context)
	pop		{lr}
	cmp		r0, #0
	beq		skip_restore
	mov		r1, #0
	msr		msplim, r1
	ldr		sp, [r0, #CTXB_ssp]
	ldr		r1, [r0, #CTXB_spsa]
	msr		msplim, r1
skip_restore:
	bxns	lr
	.size	secure_restore_context, .-secure_restore_context

#endif	/* defined(EXT_SEC) && defined(CPU_CORE_ARMV8M) */
