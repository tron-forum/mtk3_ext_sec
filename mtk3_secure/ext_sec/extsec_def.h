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
 *	extsec_def.h  **SECURE**
 *	micro T-kernel Secure Extension  definition
 */
#ifndef _EXTSEC_DEF_H_
#define _EXTSEC_DEF_H_

/*----------------------------------------------------------------------*/
/*
 * System definition form Configuration
 */

/* Task configuration */
#define MIN_TSKID	(1)
#define MAX_TSKID	(CNF_MAX_TSKID)
#define NUM_TSKID	(MAX_TSKID)
#define CHK_TSKID(id)	((MIN_TSKID) <= (id) && (id) <= (MAX_TSKID))
#define INDEX_TSK(id)	((id)-(MIN_TSKID))
#define ID_TSK(index)	((index)+(MIN_TSKID))

/*----------------------------------------------------------------------*/
/*
 *  Global variable definition
 */
/* Secure part status */
IMPORT _UW	extsec_status;
#define KNLSEC_STS_INITIALIZED	(1<<0)	// Secure part initialized
#define KNLSEC_STS_INAPI	(1<<1)	// API processing in progress

/* Management memory area */
IMPORT void* extsec_lowmem_top;
IMPORT void* extsec_lowmem_limit;

/*----------------------------------------------------------------------*/
/*
 * STCB (Secure Task Control Block) definition
 */
typedef struct {
	void	*ssp;		/* System stack pointer */

#if USE_SPMON
	void	*spsa;		/* Stack stat address */
	void	*spea;		/* Stack end address */
#endif

} SCTXB;

typedef struct {
	ID	tskid;
	ATR	tskatr;		/* Task attribute */ /* 初期化前は 0 */
	SCTXB	tztskctxb;	/* Task context block */
	W	tzstksz;	/* stack size */
	void*	itzstack;	/* stack pointer initial value */
} STCB;

IMPORT STCB stcb_table[];        /* Task control block */

/* Get STCB from task ID. */
#define get_stcb(id)             ( &stcb_table[INDEX_TSK(id)] )

/*----------------------------------------------------------------------*/
/* 
 * Secure internal functions
 */
IMPORT void* extsec_Imalloc(SZ size);
IMPORT void* extsec_Icalloc( SZ nmemb, SZ size );
IMPORT void* knlec_Irealloc( void *ptr, SZ size );
IMPORT void extsec_Ifree(void* ptr);
IMPORT ER extsec_init_Imalloc( void );

IMPORT ER extsec_task_initialize( void );

IMPORT SCTXB* extsec_get_context(ID tskid);

/*----------------------------------------------------------------------*/
/* 
 * Secure API processing functions
 */
IMPORT ER extsec_kernel_init(void);
IMPORT ER extsec_tcb_initialize(ID tskid, ATR tskatr, W tzstksz);
IMPORT ER extsec_tcb_cleanup(ID tskid);

#endif /* _EXTSEC_DEF_H_ */