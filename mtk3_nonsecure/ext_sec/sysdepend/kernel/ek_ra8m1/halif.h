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
 *	halif.h (EK-RA8M1)  **NON-SECURE**
 *	Secure Extension HAL I/F
 */
#ifndef _EXTSEC_SYSDEPEND_HALIF_
#define _EXTSEC_SYSDEPEND_HALIF_
#include <stdint.h>
#include <bsp_api.h>

/* Get clock frequency (FSP wrapper function)*/
IMPORT UW SystemCoreClock;

Inline uint32_t halif_get_cpuclk(void)
{
	return R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_CPUCLK);
}

Inline uint32_t halif_get_iclk(void)
{
	return R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_ICLK);
}

Inline uint32_t halif_get_fclk(void)
{
	return R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_FCLK);
}

Inline uint32_t halif_get_bclk(void)
{
	return R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_BCLK);
}

Inline uint32_t halif_get_pclka(void)
{
	return R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKA);
}

Inline uint32_t halif_get_pclkb(void)
{
	return R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKB);
}

Inline uint32_t halif_get_pclkc(void)
{
	return R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKC);
}

Inline uint32_t halif_get_pclkd(void)
{
	return R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKD);
}

Inline uint32_t halif_get_pclke(void)
{
	return R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_PCLKE);
}

#endif	/* _EXTSEC_SYSDEPEND_HALIF_ */