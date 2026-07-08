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
 *	ptimer_ra8m1.c (RA8M1) **NON-SECURE**
 *	Secure Extension Physical timer
 */
#include <tk/tkernel.h>
#include <tk/syslib.h>
#include "kernel.h"
#include "../../../../kernel/ek_ra8m1/halif.h"

#if USE_PTMR

typedef struct {
	UW	baddr;		// Register Base Address
	UINT	mode;		// Timer mode
	UW	limit;		// Counter Limit
	FP	ptmrhdr;	// Timer Hnadler
	PRI	intpri;		// Interrupt priority
	UW	clksrc;		// Clock source
	BOOL	tim32;		// 32-bit timer?
	void	*exinf;		// Extended information
} T_PTMRCB;

T_PTMRCB ptmrcb[TK_MAX_PTIMER] = {
	{ AGT0_BASE, -1, 0, (FP)NULL, INTPRI_AGT0, AGT0_TCK_PCLKB, FALSE, 0 },// No.1
	{ AGT1_BASE, -1, 0, (FP)NULL, INTPRI_AGT1, AGT1_TCK_PCLKB, FALSE, 0 },// No.2
};

#define AGT_AGT(n)	(ptmrcb[n].baddr + AGTxAGT)
#define AGT_CMA(n)	(ptmrcb[n].baddr + AGTxCMA)
#define AGT_CMB(n)	(ptmrcb[n].baddr + AGTxCMB)
#define AGT_CR(n)	(ptmrcb[n].baddr + AGTxCR)
#define AGT_MR1(n)	(ptmrcb[n].baddr + AGTxMR1)
#define AGT_MR2(n)	(ptmrcb[n].baddr + AGTxMR2)
#define AGT_IOC(n)	(ptmrcb[n].baddr + AGTxIOC)
#define AGT_ISR(n)	(ptmrcb[n].baddr + AGTxISR)
#define AGT_CMSR(n)	(ptmrcb[n].baddr + AGTxCMSR)
#define AGT_IOSEL(n)	(ptmrcb[n].baddr + AGTxIOSEL)

/*
 * Physical timer interrupt handler
 */
LOCAL void ptmr_int_main( UINT intno, T_PTMRCB *p_cb)
{
	out_b(p_cb->baddr + AGTxCR, in_b(p_cb->baddr + AGTxCR) & ((UB)(~AGTxCR_TUND)));			// Clear interrupt flag
	while((in_b(p_cb->baddr + AGTxCR) & AGTxCR_TUND) != 0) ;
	ClearInt( intno);

	if( p_cb->ptmrhdr != NULL) {
		(*p_cb->ptmrhdr)( p_cb->exinf);		// Execute user handler.
	}

	if( p_cb->mode == TA_ALM_PTMR)  {
		out_b( p_cb->baddr + AGTxCR, AGTxCR_TSTOP );       // Stop Physical timer.
		while((in_b(p_cb->baddr + AGTxCR) & AGTxCR_TCSTF) != 0) {};    // Wait for AGT stop.

		DisableInt( intno);			// Disable interrupt.
	}
}

LOCAL void ptmr1_inthdr( UINT intno ) { ptmr_int_main( intno, &ptmrcb[0]); }
LOCAL void ptmr2_inthdr( UINT intno ) { ptmr_int_main( intno, &ptmrcb[1]); }

LOCAL void (* const inthdr_tbl[])() = {
	ptmr1_inthdr, ptmr2_inthdr
};

LOCAL const UINT intno_tbl[] = {
	INTNO_AGT0, INTNO_AGT1
};

/*
 * Initialize physical timer
 */
EXPORT void knl_init_ptmr(void)
{
	out_w(MSTP_CRD, in_w(MSTP_CRD)&0xFFFFFFCF);	// Enable AGT0-AGT1
	while((in_w(MSTP_CRD)&0x00000030)!=0x00000000);
}

/*
 * physical timer API
 */
EXPORT ER StartPhysicalTimer( UINT ptmrno, UW limit, UINT mode)
{
	T_DINT		dint;
	UINT		intno;
	UW		limit_max;
	ER		err;

	/* parameter check */
	if(( ptmrno == 0 || ptmrno > TK_MAX_PTIMER )
		|| ( limit == 0 ) || ( mode > TA_CYC_PTMR ))	return E_PAR;

	ptmrno--;
	if(ptmrcb[ptmrno].baddr == (UW)NULL) return E_PAR;

	if(ptmrcb[ptmrno].tim32) {
		limit_max = PTMR_MAX_CNT32;
	} else {
		limit_max = PTMR_MAX_CNT16;
	}
	if( limit > limit_max) {
		return E_PAR;
	}

	ptmrcb[ptmrno].limit	= limit;
	ptmrcb[ptmrno].mode	= mode;

	/* Timer initialization */
	out_b( AGT_CR(ptmrno), AGTxCR_TSTOP);		// Stop timer.
	while((in_b(AGT_CR(ptmrno)) & AGTxCR_TCSTF) != 0) {};    // Wait for AGT stop.

	out_b( AGT_MR2(ptmrno), 0);
	out_b( AGT_MR1(ptmrno), AGTxMR1_TMOD_TIMER | AGTxMR1_TCK((UB) ptmrcb[ptmrno].clksrc));	// Select Clock Source and set mode.
	out_h( AGT_AGT(ptmrno), (UH) limit);		// Set the counter upper limit.
	out_h( AGT_CMA(ptmrno), 0xFFFF);		// Set compare timer A to 0xFFFF.
	out_h( AGT_CMB(ptmrno), 0xFFFF);		// Set compare timer B to 0xFFFF.

	/* Register interrupt handler */
	intno		= intno_tbl[ptmrno];
	dint.intatr	= TA_HLNG;
	dint.inthdr	= inthdr_tbl[ptmrno];
	err = tk_def_int( intno, &dint);
	if(err != E_OK) {
		return err;
	}

	ClearInt(intno);
	EnableInt( intno, ptmrcb[ptmrno].intpri);

	/* Start Physical Timer */
	out_b( AGT_CR(ptmrno) , AGTxCR_TSTART);	// Start Timer.
	while((in_b(AGT_CR(ptmrno)) & AGTxCR_TCSTF) == 0) {};    // Wait for AGT start.

	return E_OK;
}

EXPORT ER StopPhysicalTimer( UINT ptmrno )
{
	/* parameter check */
	if( ptmrno == 0 || ptmrno > TK_MAX_PTIMER ) return E_PAR;

	ptmrno--;
	if(ptmrcb[ptmrno].baddr == (UW)NULL) return E_PAR;

	/* Stop Physical Timer */
	DisableInt( intno_tbl[ptmrno]);
	out_b( AGT_CR(ptmrno), AGTxCR_TSTOP);		// Stop timer.
	while((in_b(AGT_CR(ptmrno)) & AGTxCR_TCSTF) != 0) {};    // Wait for AGT stop.

	return E_OK;
}


IMPORT ER GetPhysicalTimerCount( UINT ptmrno, UW *p_count )
{
	/* parameter check */
	if( ptmrno == 0 || ptmrno > TK_MAX_PTIMER ) return E_PAR;

	ptmrno--;
	if(ptmrcb[ptmrno].baddr == (UW)NULL) return E_PAR;

	/* Get Physical timer counter */
	if(ptmrcb[ptmrno].tim32) {	/* 32bit timer */
		// Skeleton for 32 bits timer				// Read counter.
	} else {			/* 16bit timer */
		*p_count = in_h( AGT_AGT(ptmrno)) & PTMR_MAX_CNT16;	// Read counter.
	}

	return E_OK;
}


EXPORT ER DefinePhysicalTimerHandler( UINT ptmrno, CONST T_DPTMR *pk_dptmr )
{
	/* parameter check */
	if( ptmrno == 0 || ptmrno > TK_MAX_PTIMER ) return E_PAR;

	ptmrno--;
	if(ptmrcb[ptmrno].baddr == (UW)NULL) return E_PAR;

	/* Set user Handler */
	if(pk_dptmr != NULL) {
		ptmrcb[ptmrno].ptmrhdr	= pk_dptmr->ptmrhdr;
		ptmrcb[ptmrno].exinf	= pk_dptmr->exinf;
	} else {
		ptmrcb[ptmrno].ptmrhdr	= NULL;
	}

	return E_OK;
}

EXPORT ER GetPhysicalTimerConfig(UINT ptmrno, T_RPTMR *pk_rptmr)
{
	UW		ptmrclk;

	/* parameter check */
	if( ptmrno == 0 || ptmrno > TK_MAX_PTIMER ) return E_PAR;

	ptmrno--;
	if(ptmrcb[ptmrno].baddr == (UW)NULL) return E_PAR;
	
	/* AGT uses PCLKB */
	ptmrclk = halif_get_pclkb();

	pk_rptmr->ptmrclk	= ptmrclk;
	pk_rptmr->maxcount	= (ptmrcb[ptmrno].tim32)?PTMR_MAX_CNT32:PTMR_MAX_CNT16;
	pk_rptmr->defhdr	= TRUE;

	return E_OK;
}

#endif	/* USE_PTMR */
#endif	/* defined(EXT_SEC) && defined(CPU_RA6M5) */
