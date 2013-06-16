/*
 * hw_hpi.h
 */

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */


#ifndef _HW_HPI_H_
#define _HW_HPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#define HPI_REVID		(0x0)
#define HPI_PWREMU_MGMT		(0x4)
#define HPI_GPIOEN		(0xC)
#define HPI_GPIODIR1		(0x10)
#define HPI_GPIODAT1		(0x14)
#define HPI_GPIODIR2		(0x18)
#define HPI_GPIODAT2		(0x1C)
#define HPI_HPIC		(0x30)
#define HPI_HPIAW		(0x34)
#define HPI_HPIAR		(0x38)

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* REVID */


#define HPI_REVID_REV         (0xFFFFFFFFu)
#define HPI_REVID_REV_SHIFT        (0x00000000u)


/* PWREMU_MGMT */


#define HPI_PWREMU_MGMT_SOFT (0x00000002u)
#define HPI_PWREMU_MGMT_SOFT_SHIFT (0x00000001u)

#define HPI_PWREMU_MGMT_FREE (0x00000001u)
#define HPI_PWREMU_MGMT_FREE_SHIFT (0x00000000u)


/* HPIC */


#define HPI_HPIC_HPIASEL (0x00000800u)
#define HPI_HPIC_HPIASEL_SHIFT (0x0000000Bu)


#define HPI_HPIC_DUALHPIA (0x00000200u)
#define HPI_HPIC_DUALHPIA_SHIFT (0x00000009u)

#define HPI_HPIC_HWOBSTAT (0x00000100u)
#define HPI_HPIC_HWOBSTAT_SHIFT (0x00000008u)



#define HPI_HPIC_FETCH (0x00000010u)
#define HPI_HPIC_FETCH_SHIFT (0x00000004u)


#define HPI_HPIC_HINT (0x00000004u)
#define HPI_HPIC_HINT_SHIFT (0x00000002u)

#define HPI_HPIC_DSPINT (0x00000002u)
#define HPI_HPIC_DSPINT_SHIFT (0x00000001u)

#define HPI_HPIC_HWOB (0x00000001u)
#define HPI_HPIC_HWOB_SHIFT (0x00000000u)


/* HPIAW */

#define HPI_HPIAW_HPIAW (0xFFFFFFFFu)
#define HPI_HPIAW_HPIAW_SHIFT (0x00000000u)


/* HPIAR */

#define HPI_HPIAR_HPIAR (0xFFFFFFFFu)
#define HPI_HPIAR_HPIAR_SHIFT (0x00000000u)


#ifdef __cplusplus
}
#endif

#endif

