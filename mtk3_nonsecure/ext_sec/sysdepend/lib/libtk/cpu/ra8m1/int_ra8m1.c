/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 Secure Extension 1.00
 *
 *    Copyright (C) 2026 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2026/07.
 *
 *----------------------------------------------------------------------
 */
#include <sys/machine.h>
#if defined(EXT_SEC) && defined(CPU_RA8M1)

/*
 *	int_ra8m1.c (RA8M1)
 *	Secure Extension Interrupt controller
 */
#include <tk/tkernel.h>
#include <tk/syslib.h>

#include <lib/libtk/sysdepend/cpu/core/armv8m/int_armv8m.h>

/*----------------------------------------------------------------------*/
/*
 * Interrupt control API
 * 
 */
/*
 * Enable interrupt 
 */
EXPORT void EnableInt( UINT intno, INT level )
{
	if( intno <= MAX_NVIC_INTNO ) {
		EnableInt_nvic( intno, level);
	}
}

/*
 * Disable interrupt 
 */
EXPORT void DisableInt( UINT intno )
{
	if( intno <= MAX_NVIC_INTNO ) {
		DisableInt_nvic( intno);
	}
}

/*
 * Clear interrupt
 */
EXPORT void ClearInt( UINT intno )
{
	if( intno <= MAX_NVIC_INTNO ) {
		/* Clear IR bit of the ICU.IELSR register */
		out_w(ICU_IELSR(intno), in_w(ICU_IELSR(intno)) & ~ICU_IELSR_IR);
		in_w(ICU_IELSR(intno));
		
		ClearInt_nvic( intno );
	}
}

/*
 * Issue EOI to interrupt controller
 */
EXPORT void EndOfInt( UINT intno )
{
	/* No opetarion. */
}

/*
 * Check active state
 */
EXPORT BOOL CheckInt( UINT intno )
{
	BOOL rtncd;
	
	if( intno <= MAX_NVIC_INTNO ) {
		rtncd = CheckInt_nvic( intno );
	} else {
		rtncd = FALSE;
	}
	return rtncd;
}

/*
 * Set interrupt mode
 */
EXPORT void SetIntMode(UINT intno, UINT mode)
{
	/* No opetarion. */
}

#endif /* defined(EXT_SEC) && defined(CPU_RA8M1) */
