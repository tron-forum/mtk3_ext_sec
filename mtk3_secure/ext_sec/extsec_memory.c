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

#include <sys/machine_sec.h>
#ifdef EXT_SEC

/*
 *	extsec_memory.c  **SECURE**
 *	Secure Extension In-kernel dynamic memory management
 */

#include <string.h>

#include <tk/tkernel_sec.h>
#include <sys/queue_sec.h>

#include "sysdepend/int_sec.h"
#include "extsec_def.h"
#include "extsec_memory.h"

/*
 * FreeQue search
 *	Search the free area whose size is equal to 'blksz',
 *	or larger than
 *      'blksz' but closest.
 *	If it does not exist, return '&imacb->freeque'.
 */
LOCAL QUEUE* extsec_searchFreeArea( IMACB *imacb, W blksz )
{
	QUEUE	*q = &imacb->freeque;

	/* For area whose memory pool size is less than 1/4,
	   search from smaller size.
	   Otherwise, search from larger size. */
	if ( blksz > imacb->memsz / 4 ) {
		/* Search from larger size. */
		W fsz = 0;
		while ( (q = q->prev) != &imacb->freeque ) {
			fsz = FreeSize(q);
			if ( fsz <= blksz ) {
				return ( fsz < blksz )? q->next: q;
			}
		}
		return ( fsz >= blksz )? q->next: q;
	} else {
		/* Search from smaller size. */
		while ( (q = q->next) != &imacb->freeque ) {
			if ( FreeSize(q) >= blksz ) {
				break;
			}
		}
		return q;
	}
}


/*
 * Registration of free area on FreeQue
 *	FreeQue is composed of 2 types: Queue that links the
 *	different size of areas by size and queue that links the
 *	same size of areas.
 *
 *	freeque
 *	|
 *	|   +-----------------------+	    +-----------------------+
 *	|   | AreaQue		    |	    | AreaQue		    |
 *	|   +-----------------------+	    +-----------------------+
 *	*---> FreeQue Size order    |	    | EmptyQue		    |
 *	|   | FreeQue Same size   --------->| FreeQue Same size   ----->
 *	|   |			    |	    |			    |
 *	|   |			    |	    |			    |
 *	|   +-----------------------+	    +-----------------------+
 *	|   | AreaQue		    |	    | AreaQue		    |
 *	v   +-----------------------+	    +-----------------------+
 */
LOCAL void extsec_appendFreeArea( IMACB *imacb, QUEUE *aq )
{
	QUEUE	*fq;
	W	size = AreaSize(aq);

	/* Registration position search */
	/*  Search the free area whose size is equal to 'blksz',
	 *  or larger than 'blksz' but closest.
	 *  If it does not exist, return '&imacb->freeque'.
	 */
	fq = extsec_searchFreeArea(imacb, size);

	/* Register */
	clrAreaFlag(aq, AREA_USE);
	if ( fq != &imacb->freeque && FreeSize(fq) == size ) {
		/* FreeQue Same size */
		(aq + 2)->next = (fq + 1)->next;
		(fq + 1)->next = aq + 2;
		(aq + 2)->prev = fq + 1;
		if( (aq + 2)->next != NULL ) {
			(aq + 2)->next->prev = aq + 2;
		}
		(aq + 1)->next = NULL;
	} else {
		/* FreeQue Size order */
		QueInsert(aq + 1, fq);
		(aq + 2)->next = NULL;
		(aq + 2)->prev = (QUEUE*)size;
	}
}

/*
 * Delete from FreeQue
 */
LOCAL void extsec_removeFreeQue( QUEUE *fq )
{
	if ( fq->next == NULL ) {	/* FreeQue Same size */
		(fq + 1)->prev->next = (fq + 1)->next;
		if ( (fq + 1)->next != NULL ) {
			(fq + 1)->next->prev = (fq + 1)->prev;
		}
	} else {			/* FreeQue Size order */
		if ( (fq + 1)->next != NULL ) {		/* having FreeQue Same size */
			QueInsert((fq + 1)->next - 1, fq);
			(fq + 1)->next->prev = (fq + 1)->prev;
		}
		QueRemove(fq);
	}
}

/*
 * Register area
 *	Insert 'ent' just after 'que.'
 */
LOCAL void extsec_insertAreaQue( QUEUE *que, QUEUE *ent )
{
	ent->prev = que;
	ent->next = que->next;
	Assign(que->next->prev, ent);
	que->next = ent;
}

/*
 * Delete area
 */
LOCAL void secure_removeAreaQue( QUEUE *aq )
{
	Mask(aq->prev)->next = aq->next;
	Assign(aq->next->prev, Mask(aq->prev));
}

/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */

Noinit(EXPORT IMACB *secure_imacb);

/* ------------------------------------------------------------------------ */

/*
 * Memory allocate
 */
EXPORT void* extsec_Imalloc( SZ size )
{
	QUEUE	*q, *aq, *aq2;
	UINT	imask;

	/* If it is smaller than the minimum fragment size,
	   allocate the minimum size to it. */
	if( size <= 0 ) {
		return (void *)NULL;
	} else 	if ( size < (W)MIN_FRAGMENT ) {
		size = (W)MIN_FRAGMENT;
	} else {
		size = ROUND(size);
	}

	DI(imask);  /* Exclusive control by interrupt disable */

	/* Search FreeQue */
	q = extsec_searchFreeArea(secure_imacb, size);
	if ( q == &(secure_imacb->freeque) ) {
		q = NULL; /* Insufficient memory */
		goto err_ret;
	}

	/* There is free area: Split from FreeQue once */
	extsec_removeFreeQue(q);

	aq = q - 1;

	/* If there are fragments smaller than the minimum fragment size,
	   allocate them also */
	if ( FreeSize(q) - size >= (W)(MIN_FRAGMENT + sizeof(QUEUE)) ) {

		/* Divide area into 2 */
		aq2 = (QUEUE*)((VB*)(aq + 1) + size);
		extsec_insertAreaQue(aq, aq2);

		/* Register remaining area to FreeQue */
		extsec_appendFreeArea(secure_imacb, aq2);
	}
	setAreaFlag(aq, AREA_USE);

err_ret:
	EI(imask);

	return (void *)q;
}

/*
 * Memory allocate  and clear
 */
EXPORT void* extsec_Icalloc( SZ nmemb, SZ size )
{
	SZ	sz = nmemb * size;
	void	*mem;

	mem = extsec_Imalloc(sz);
	if ( mem == NULL ) {
		return NULL;
	}

	memset(mem, 0, sz);

	return mem;
}


/*
 * Memory allocation size change
 */
EXPORT void* knlec_Irealloc( void *ptr, SZ size )
{
	void	*newptr;
	QUEUE	*aq;
	SZ	oldsz;

	if(size != 0) {
		newptr = extsec_Imalloc(size);
		if(newptr == NULL) {
			return NULL;
		}
	} else {
		newptr = NULL;
	}

	if(ptr != NULL) {
		if(newptr != NULL) {
			aq = (QUEUE*)ptr - 1;
			oldsz = (SZ)AreaSize(aq);
			memcpy(newptr, ptr, (size > oldsz)?oldsz:size);
		}
		extsec_Ifree(ptr);
	}

	return newptr;
}


/*
 * Free memory
 */
EXPORT void  extsec_Ifree( void *ptr )
{
	QUEUE	*aq;
	UINT	imask;

	DI(imask);  /* Exclusive control by interrupt disable */

	aq = (QUEUE*)ptr - 1;
	clrAreaFlag(aq, AREA_USE);

	if ( !chkAreaFlag(aq->next, AREA_USE) ) {
		/* Merge with free area in after location */
		extsec_removeFreeQue(aq->next + 1);
		secure_removeAreaQue(aq->next);
	}

	if ( !chkAreaFlag(aq->prev, AREA_USE) ) {
		/* Merge with free area in front location */
		aq = aq->prev;
		extsec_removeFreeQue(aq + 1);
		secure_removeAreaQue(aq->next);
	}

	extsec_appendFreeArea(secure_imacb, aq);

	EI(imask);
}


/* ------------------------------------------------------------------------ */

/*
 * IMACB Initialization
 */
LOCAL void extsec_initIMACB( void )
{
	QueInit(&(secure_imacb->areaque));
	QueInit(&(secure_imacb->freeque));
}

/*
 * Imalloc initial setting
 */
EXPORT ER extsec_init_Imalloc( void )
{
	QUEUE	*top, *end;

	/* Align top with 4 byte unit alignment for IMACB */
	extsec_lowmem_top = (void *)(((UW)extsec_lowmem_top + 3) & ~0x00000003UL);
	secure_imacb = (IMACB*)extsec_lowmem_top;
	extsec_lowmem_top = (void *)((UW)extsec_lowmem_top + sizeof(IMACB));

	/* Align top with 8 byte unit alignment */
	extsec_lowmem_top = (void *)(((UW)extsec_lowmem_top + 7) & ~0x00000007UL);
	top = (QUEUE*)extsec_lowmem_top;
	secure_imacb->memsz = (W)((UW)extsec_lowmem_limit - (UW)extsec_lowmem_top - sizeof(QUEUE)*2);

	extsec_lowmem_top = extsec_lowmem_limit;  /* Update memory free space */

	extsec_initIMACB();

	/* Register on AreaQue */
	end = (QUEUE*)((VB*)top + secure_imacb->memsz) + 1;
	extsec_insertAreaQue(&secure_imacb->areaque, end);
	extsec_insertAreaQue(&secure_imacb->areaque, top);
	setAreaFlag(end, AREA_USE);
	setAreaFlag(&secure_imacb->areaque, AREA_USE);

	extsec_appendFreeArea(secure_imacb, top);

	return E_OK;
}

#endif /* EXT_SEC */
