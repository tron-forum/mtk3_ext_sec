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

 /*
  *	config_sec.h  **NON-SECURE**
  *	Secure Extension Configuration Definition
  */

#ifndef	_EXTSEC_CONFIG_H_
#define	_EXTSEC_CONFIG_H_

/* ------------------------------------------------------------------------ *
 * 	TrustZone definition
 */
#define	CNF_TZ_ENABLE		1	/* TrustZone Support (1:Valid  0:invalid) */
#define	CNF_TZ_STATE		0	/* OS execution state (1:Secure  0:Non-Secure) */
#define CNF_TZ_SCALL		1	/* Secure Calls from Tasks (1:Valid  0:invalid) */

/* ------------------------------------------------------------------------ *
 * 	Exception/Interrupt Vector Table
 */
#define USE_KNL_VECTBL		0	/* Use the vector table defined in the kernel (1:Valid  0:invalid) */

#endif  /* _EXTSEC_CONFIG_H_ */
