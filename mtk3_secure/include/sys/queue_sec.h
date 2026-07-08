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

/*
 *	queue_sec.h  **Secure**
 *	Secure Extension Queuing operation
 */

#ifndef	_EXTSEC_SYS_QUEUE_H_
#define _EXTSEC_SYS_QUEUE_H_

/*
 * Double-link queue (ring)
 */
typedef struct queue {
	struct queue	*next;
	struct queue	*prev;
} QUEUE;

/*
 * Queue initialization 
 */
Inline void QueInit( QUEUE *que )
{
	que->next = (struct queue *)que;
	que->prev = (struct queue *)que;
}

/*
 * TRUE if the queue is empty 
 */
Inline BOOL isQueEmpty( QUEUE *que )
{
	return ( que->next == que )? TRUE: FALSE;
}

/*
 * Insert in queue 
 *	Inserts entry directly prior to que 
 */
Inline void QueInsert( QUEUE *entry, QUEUE *que )
{
	entry->prev = (struct queue*) que->prev;
	entry->next = que;
	que->prev->next = entry;
	que->prev = entry;
}

/*
 * Delete from queue 
 *	Deletes entry from queue 
 *	No action is performed if entry is empty. 
 */
Inline void QueRemove( QUEUE *entry )
{
	if ( entry->next != entry ) {
		entry->prev->next = (struct queue*) entry->next;
		entry->next->prev = (struct queue*) entry->prev;
	}
}

/*
 * Remove top entry 
 *	Deletes the entry directly after que from the queue,
 *	and returns the deleted entry.
 *	Returns NULL if que is empty.
 */
Inline QUEUE* QueRemoveNext( QUEUE *que )
{
	QUEUE	*entry;

	if ( que->next == que ) {
		return NULL;
	}

	entry = que->next;
	que->next = (struct queue*)entry->next;
	entry->next->prev = que;

	return entry;
}

#endif /* _EXTSEC_SYS_QUEUE_H_ */
