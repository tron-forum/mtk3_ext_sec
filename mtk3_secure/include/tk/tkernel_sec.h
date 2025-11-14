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
 *	tkernel_sec.h  **Secure**
 *	Secure Extension T-Kernel Definition
 */

#ifndef _EXTSEC_TK_TKERNEL_H_
#define _EXTSEC_TK_TKERNEL_H_

#include <sys/machine_sec.h>
#include <config_sec.h>

#if USE_STDINC_STDDEF
#include <stddef.h>
#define PROHIBIT_DEF_SIZE_T
#endif

#if USE_STDINC_STDINT
#include <stdint.h>
#endif

#include <tk/typedef_sec.h>
#include <tk/errno_sec.h>
#include <tk/syslib_sec.h>
#include <sys/sysdef_sec.h>

/* ------------------------------------------------------------------------ */
/* 
 * Task attributes
 */
#define TA_FPU		0x00001000U
#define TA_TZCALL	0x00010000U	/* Use TrustZone secure functions */


#endif /* _EXTSEC_TK_TKERNEL_H_ */
