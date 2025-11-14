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

/*
 *	halif.h (Nucleo-STM32N657N)  **NON-SECURE**
 *	Secure Extension HAL I/F
 */
#ifndef _EXTSEC_SYSDEPEND_HALIF_
#define _EXTSEC_SYSDEPEND_HALIF_
#include <stdint.h>

/* Get clock frequency (CMSIS wrapper function)*/
IMPORT UW SystemCoreClock;

uint32_t HAL_RCC_GetCpuClockFreq(void);
uint32_t HAL_RCC_GetSysClockFreq(void);
uint32_t HAL_RCC_GetHCLKFreq(void);
uint32_t HAL_RCC_GetPCLK1Freq(void);
uint32_t HAL_RCC_GetPCLK2Freq(void);

Inline uint32_t halif_get_cpuclk(void)
{
	return HAL_RCC_GetCpuClockFreq();
}

Inline uint32_t halif_get_sysclk(void)
{
	return HAL_RCC_GetSysClockFreq();
}

Inline uint32_t halif_get_hclk(void)
{
	return HAL_RCC_GetHCLKFreq();
}

Inline uint32_t halif_get_pclk1(void)
{
	return HAL_RCC_GetPCLK1Freq();
}

Inline uint32_t halif_get_pclk2(void)
{
	return HAL_RCC_GetPCLK2Freq();
}

#endif	/* _EXTSEC_SYSDEPEND_HALIF_ */