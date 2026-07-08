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
 *	syslib_sec.h  **Secure**
 *	Secure Extensionmicro T-Kernel System Library
 */

#ifndef _EXTSEC_TK_SYSLIB_H_
#define _EXTSEC_TK_SYSLIB_H_

#include <tk/typedef_sec.h>

/* ------------------------------------------------------------------------ */
/*
 * I/O port access
 *	for memory mapped I/O
 */
Inline void out_d( UW port, UD data )
{
	*(_UD*)port = data;
}
Inline void out_w( UW port, UW data )
{
	*(_UW*)port = data;
}
Inline void out_h( UW port, UH data )
{
	*(_UH*)port = data;
}
Inline void out_b( UW port, UB data )
{
	*(_UB*)port = data;
}

Inline UD in_d( UW port )
{
	return *(_UD*)port;
}
Inline UW in_w( UW port )
{
	return *(_UW*)port;
}
Inline UH in_h( UW port )
{
	return *(_UH*)port;
}
Inline UB in_b( UW port )
{
	return *(_UB*)port;
}

#endif /* _EXTSEC_TK_SYSLIB_H_ */
