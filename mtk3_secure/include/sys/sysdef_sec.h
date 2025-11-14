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
 *	sysdef_sec.h **SECURE**
 *
 *	System dependencies definition.
 *	Secure Extension Included also from assembler program.
 */

#ifndef _EXTSEC_SYS_SYSDEF_H_
#define _EXTSEC_SYS_SYSDEF_H_

/* System dependencies */
#define SYSDEF_PATH_(a)		#a
#define SYSDEF_PATH(a)		SYSDEF_PATH_(a)
#define SYSDEF_SYSDEP()		SYSDEF_PATH(sys/sysdepend/TARGET_DIR/sysdef_sec.h)
#include SYSDEF_SYSDEP()

#endif /* _EXTSEC_SYS_SYSDEF_H_ */
