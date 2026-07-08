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

#include <sys/machine.h>
#if defined(EXT_SEC) && defined(NUCLEO_STM32N657)

#include <tk/tkernel.h>
#include <kernel.h>

/*
 *	power_save.c (Nucleo-STM32N657N)  **NON-SECURE**
 *	Secure Extension Power-Saving Function
 */

/*
 * Switch to power-saving mode
 */
EXPORT void low_pow( void )
{
}

/*
 * Move to suspend mode
 */
EXPORT void off_pow( void )
{
}


#endif /* defined(EXT_SEC) && defined(NUCLEO_STM32N657) */
