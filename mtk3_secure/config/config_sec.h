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
  *	config_sec.h  **SECURE**
  *	Secure Extension Configuration Definition
  */

#ifndef	_EXTSEC_SEC_CONFIG_H_
#define	_EXTSEC_SEC_CONFIG_H_

/*---------------------------------------------------------------------- */
/*
 * System memory definition
 */
#define	CNF_SYSTEMAREA_TOP	0	/* 0: Use system default address */
#define	CNF_SYSTEMAREA_END	0	/* 0: Use system default address */

/*---------------------------------------------------------------------- */
/*
 * Task definition
 */
#define	MIN_TZ_STACK_SIZE	128	// Minimum size of a task's secure stack
#define	CNF_MAX_TSKID		32	// Maximum number of tasks

/*---------------------------------------------------------------------- */
/* Use Co-Processor.
 *  1: Valid  0: Invalid
 */
#define	USE_FPU			(1)	/* Use FPU */
#define	USE_DSP			(0)	/* Use DSP */

#define	ALWAYS_FPU_ATR		(1)	/* Always set the TA_FPU attribute on all tasks */

/*---------------------------------------------------------------------- */
/*
 *	Use Standard C include file
 */
#define USE_STDINC_STDDEF	(1)	/* Use <stddef.h> */
#define USE_STDINC_STDINT	(1)	/* Use <stdint.h> */

/* ------------------------------------------------------------------------ */
/*
 *  Stack pointer monitoring function
 */
#define USE_SPMON		(1)		// 1:Valid   0:invalid

#endif  /* _EXTSEC_SEC_CONFIG_H_ */
