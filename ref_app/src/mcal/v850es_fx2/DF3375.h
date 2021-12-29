/************************************************************************/
/*                          DF3375.h                                    */
/*                                                                      */
/*  NEC V850 microcontroller device uPD70F3375                          */
/*                                                                      */
/*  Declarations of I/O Registers                                       */
/*                                                                      */
/*                                                                      */
/*  Copyright (C) NEC Corporation 2006                                  */
/*  This file was created from device file DF3375.800       [V1.00 ]    */
/*  by DeFiX V1.23                                                      */
/*                                                                      */
/*  This file is only intended as a sample supplement to NEC tools.     */
/*  Feel free to adapt it to your own needs.                            */
/*  This File is provided 'as is' without warranty of any kind.         */
/*  Neither NEC nor their sales representatives can be held liable      */
/*  of any inconvenience or problem caused by its contents.             */
/************************************************************************/

#ifndef __uPD70F3375_H
#define __uPD70F3375_H

/* CAN register */
#define C0GMCTRL         CAST_US(0x03FEC000)
#define C0GMCS           CAST_UC(0x03FEC002)
#define C0MASK1L         CAST_US(0x03FEC040)
#define C0MASK1H         CAST_US(0x03FEC042)
#define C0CTRL           CAST_US(0x03FEC050)
#define C0IE             CAST_US(0x03FEC056)
#define C0INTS           CAST_US(0x03FEC058)
#define C0BRP            CAST_UC(0x03FEC05A)
#define C0BTR            CAST_US(0x03FEC05C)
#define C0LIPT           CAST_UC(0x03FEC05E)
#define C0RGPT           CAST_US(0x03FEC060)
#define C0TGPT           CAST_US(0x03FEC064)

#define C0MDATA000_ADDR  (0x03FEC100)
#define C0MDATA00        CAST_UC(0x03FEC100)
#define C0MDATA10        CAST_UC(0x03FEC101)
#define C0MDATA20        CAST_UC(0x03FEC102)
#define C0MDATA30        CAST_UC(0x03FEC103)
#define C0MDATA40        CAST_UC(0x03FEC104)
#define C0MDATA50        CAST_UC(0x03FEC105)
#define C0MDATA60        CAST_UC(0x03FEC106)
#define C0MDATA70        CAST_UC(0x03FEC107)

#define C0MDLC0          CAST_UC(0x03FEC108)
#define C0MCONF0         CAST_UC(0x03FEC109)
#define C0MCONF0_ADDR    (0x03FEC109)
#define C0MIDL0          CAST_US(0x03FEC10A)
#define C0MIDH0          CAST_US(0x03FEC10C)
#define C0MCTRL0         CAST_US(0x03FEC10E)
#define C0MCTRL0_ADDR    (0x03FEC10E)


#define C0MDATA001_ADDR  (0x03FEC120)
#define C0MDLC1          CAST_UC(0x03FEC128)
#define C0MCONF1         CAST_UC(0x03FEC129)
#define C0MIDL1          CAST_US(0x03FEC12A)
#define C0MIDH1          CAST_US(0x03FEC12C)
#define C0MCTRL1         CAST_US(0x03FEC12E)


#ifdef __LANGUAGE_ASM__
#else
   
  #define _C0INTS0          ((volatile struct bitf *)0x03FEC059)->bit00
  #define _C0INTS1          ((volatile struct bitf *)0x03FEC059)->bit01
   
  #define _C0RHPM           ((volatile struct bitf *)0x03FEC060)->bit01
   
  #define _C0THPM           ((volatile struct bitf *)0x03FEC064)->bit01

  #define _C0MCONF00        ((volatile struct bitf *)0x03FEC109)->bit00
   
  #define _C0MCONF10        ((volatile struct bitf *)0x03FEC129)->bit00
 //  #define _C0MCONF13        ((volatile struct bitf *)0x03FEC129)->bit03
  #define _C0MCONF14        ((volatile struct bitf *)0x03FEC129)->bit04

#endif

#define C1GMCTRL         CAST_US(0x03FEC600)
#define C1GMCS           CAST_UC(0x03FEC602)
#define C1MASK1L         CAST_US(0x03FEC640)
#define C1MASK1H         CAST_US(0x03FEC642)
#define C1CTRL           CAST_US(0x03FEC650)
#define C1IE             CAST_US(0x03FEC656)
#define C1INTS           CAST_US(0x03FEC658)
#define C1BRP            CAST_UC(0x03FEC65A)
#define C1BTR            CAST_US(0x03FEC65C)
#define C1LIPT           CAST_UC(0x03FEC65E)
#define C1RGPT           CAST_US(0x03FEC660)
#define C1TGPT           CAST_US(0x03FEC664)

#define C1MDATA000_ADDR  (0x03FEC700)
#define C1MDLC0          CAST_UC(0x03FEC708)
#define C1MCONF0         CAST_UC(0x03FEC709)
#define C1MCONF0_ADDR    (0x03FEC709)
#define C1MIDL0          CAST_US(0x03FEC70A)
#define C1MIDH0          CAST_US(0x03FEC70C)
#define C1MCTRL0         CAST_US(0x03FEC70E)
#define C1MCTRL0_ADDR    (0x03FEC70E)

#define C1MDATA001_ADDR  (0x03FEC720)
#define C1MDLC1          CAST_UC(0x03FEC728)
#define C1MCONF1         CAST_UC(0x03FEC729)
#define C1MIDL1          CAST_US(0x03FEC72A)
#define C1MIDH1          CAST_US(0x03FEC72C)
#define C1MCTRL1         CAST_US(0x03FEC72E)

#define C1MDATA002_ADDR  (0x03FEC740)
#define C1MDLC2          CAST_UC(0x03FEC748)
#define C1MCONF2         CAST_UC(0x03FEC749)
#define C1MIDL2          CAST_US(0x03FEC74A)
#define C1MIDH2          CAST_US(0x03FEC74C)
#define C1MCTRL2         CAST_US(0x03FEC74E)
         
#ifdef __LANGUAGE_ASM__
#else
   
  #define _C1INTS0          ((volatile struct bitf *)0x03FEC659)->bit00
  #define _C1INTS1          ((volatile struct bitf *)0x03FEC659)->bit01
   
  #define _C1RHPM           ((volatile struct bitf *)0x03FEC660)->bit01
   
  #define _C1THPM           ((volatile struct bitf *)0x03FEC664)->bit01

  #define _C1MCONF00        ((volatile struct bitf *)0x03FEC709)->bit00
   
  #define _C1MCONF10        ((volatile struct bitf *)0x03FEC729)->bit00
  // #define _C1MCONF13        ((volatile struct bitf *)0x03FEC729)->bit03
  #define _C1MCONF14        ((volatile struct bitf *)0x03FEC729)->bit04

  #define _C1MCONF20        ((volatile struct bitf *)0x03FEC749)->bit00
  // #define _C1MCONF23        ((volatile struct bitf *)0x03FEC749)->bit03
  #define _C1MCONF24        ((volatile struct bitf *)0x03FEC749)->bit04

#endif

/* I/O register */
#define	PDL              CAST_US(0xfffff004)
#define	PDLL             CAST_UC(0xfffff004)
#define	PDLH             CAST_UC(0xfffff005)
#define	PCS              CAST_UC(0xfffff008)
#define	PCT              CAST_UC(0xfffff00a)
#define	PCM              CAST_UC(0xfffff00c)
#define	PMDL             CAST_US(0xfffff024)
#define	PMDLL            CAST_UC(0xfffff024)
#define	PMDLH            CAST_UC(0xfffff025)
#define	PMCS             CAST_UC(0xfffff028)
#define	PMCT             CAST_UC(0xfffff02a)
#define	PMCM             CAST_UC(0xfffff02c)
#define	PMCCM            CAST_UC(0xfffff04c)
#define	BPC              CAST_US(0xfffff064)
#define	BSC              CAST_US(0xfffff066)
#define	VSWC             CAST_UC(0xfffff06e)
#define	DSA0L            CAST_US(0xfffff080)
#define	DSA0H            CAST_US(0xfffff082)
#define	DDA0L            CAST_US(0xfffff084)
#define	DDA0H            CAST_US(0xfffff086)
#define	DSA1L            CAST_US(0xfffff088)
#define	DSA1H            CAST_US(0xfffff08a)
#define	DDA1L            CAST_US(0xfffff08c)
#define	DDA1H            CAST_US(0xfffff08e)
#define	DSA2L            CAST_US(0xfffff090)
#define	DSA2H            CAST_US(0xfffff092)
#define	DDA2L            CAST_US(0xfffff094)
#define	DDA2H            CAST_US(0xfffff096)
#define	DSA3L            CAST_US(0xfffff098)
#define	DSA3H            CAST_US(0xfffff09a)
#define	DDA3L            CAST_US(0xfffff09c)
#define	DDA3H            CAST_US(0xfffff09e)
#define	DBC0             CAST_US(0xfffff0c0)
#define	DBC1             CAST_US(0xfffff0c2)
#define	DBC2             CAST_US(0xfffff0c4)
#define	DBC3             CAST_US(0xfffff0c6)
#define	DADC0            CAST_US(0xfffff0d0)
#define	DADC1            CAST_US(0xfffff0d2)
#define	DADC2            CAST_US(0xfffff0d4)
#define	DADC3            CAST_US(0xfffff0d6)
#define	DCHC0            CAST_UC(0xfffff0e0)
#define	DCHC1            CAST_UC(0xfffff0e2)
#define	DCHC2            CAST_UC(0xfffff0e4)
#define	DCHC3            CAST_UC(0xfffff0e6)
#define	IMR0             CAST_US(0xfffff100)
#define	IMR0L            CAST_UC(0xfffff100)
#define	IMR0H            CAST_UC(0xfffff101)
#define	IMR1             CAST_US(0xfffff102)
#define	IMR1L            CAST_UC(0xfffff102)
#define	IMR1H            CAST_UC(0xfffff103)
#define	IMR2             CAST_US(0xfffff104)
#define	IMR2L            CAST_UC(0xfffff104)
#define	IMR2H            CAST_UC(0xfffff105)
#define	IMR3             CAST_US(0xfffff106)
#define	IMR3L            CAST_UC(0xfffff106)
#define	IMR3H            CAST_UC(0xfffff107)
#define	IMR4             CAST_US(0xfffff108)
#define	IMR4L            CAST_UC(0xfffff108)
#define	LVILIC           CAST_UC(0xfffff110)
#define	LVIHIC           CAST_UC(0xfffff112)
#define	PIC0             CAST_UC(0xfffff114)
#define	PIC1             CAST_UC(0xfffff116)
#define	PIC2             CAST_UC(0xfffff118)
#define	PIC3             CAST_UC(0xfffff11a)
#define	PIC4             CAST_UC(0xfffff11c)
#define	PIC5             CAST_UC(0xfffff11e)
#define	PIC6             CAST_UC(0xfffff120)
#define	TQ0OVIC          CAST_UC(0xfffff122)
#define	TAB0OVIC         CAST_UC(0xfffff124)
#define	TAB0CCIC0        CAST_UC(0xfffff126)
#define	TAB0CCIC1        CAST_UC(0xfffff128)
#define	TAB0CCIC2        CAST_UC(0xfffff12a)
#define	TAB0CCIC3        CAST_UC(0xfffff12c)
#define	TAA0OVIC         CAST_UC(0xfffff12e)
#define	TAA0CCIC0        CAST_UC(0xfffff130)
#define	TAA0CCIC1        CAST_UC(0xfffff132)
#define	TAA1OVIC         CAST_UC(0xfffff134)
#define	TAA1CCIC0        CAST_UC(0xfffff136)
#define	TAA1CCIC1        CAST_UC(0xfffff138)
#define	TAA2OVIC         CAST_UC(0xfffff13a)
#define	TAA2CCIC0        CAST_UC(0xfffff13c)
#define	TAA2CCIC1        CAST_UC(0xfffff13e)
#define	TAA3OVIC         CAST_UC(0xfffff140)
#define	TAA3CCIC0        CAST_UC(0xfffff142)
#define	TAA3CCIC1        CAST_UC(0xfffff144)
#define	TAA4OVIC         CAST_UC(0xfffff146)
#define	TAA4CCIC0        CAST_UC(0xfffff148)
#define	TAA4CCIC1        CAST_UC(0xfffff14a)
#define	TM0EQIC0         CAST_UC(0xfffff14c)
#define	CB0RIC           CAST_UC(0xfffff14e)
#define	CB0TIC           CAST_UC(0xfffff150)
#define	CB1RIC           CAST_UC(0xfffff152)
#define	CB1TIC           CAST_UC(0xfffff154)
#define	UD0SIC           CAST_UC(0xfffff156)
#define	UD0RIC           CAST_UC(0xfffff158)
#define	UD0TIC           CAST_UC(0xfffff15a)
#define	UD1SIC           CAST_UC(0xfffff15c)
#define	UD1RIC           CAST_UC(0xfffff15e)
#define	UD1TIC           CAST_UC(0xfffff160)
#define	IIC0IC           CAST_UC(0xfffff162)
#define	ADIC             CAST_UC(0xfffff164)
#define	C0ERRIC          CAST_UC(0xfffff166)
#define	C0WUPIC          CAST_UC(0xfffff168)
#define	C0RECIC          CAST_UC(0xfffff16a)
#define	C0TRXIC          CAST_UC(0xfffff16c)
#define	DMAIC0           CAST_UC(0xfffff16e)
#define	DMAIC1           CAST_UC(0xfffff170)
#define	DMAIC2           CAST_UC(0xfffff172)
#define	DMAIC3           CAST_UC(0xfffff174)
#define	KRIC             CAST_UC(0xfffff176)
#define	WTIIC            CAST_UC(0xfffff178)
#define	WTIC             CAST_UC(0xfffff17a)
#define	ECCDIC           CAST_UC(0xfffff17c)
#define	FLIC             CAST_UC(0xfffff17e)
#define	PIC8             CAST_UC(0xfffff180)
#define	PIC9             CAST_UC(0xfffff182)
#define	PIC10            CAST_UC(0xfffff184)
#define	TAB1OVIC         CAST_UC(0xfffff186)
#define	TAB1CCIC0        CAST_UC(0xfffff188)
#define	TAB1CCIC1        CAST_UC(0xfffff18a)
#define	TAB1CCIC2        CAST_UC(0xfffff18c)
#define	TAB1CCIC3        CAST_UC(0xfffff18e)
#define	UD2SIC           CAST_UC(0xfffff190)
#define	UD2RIC           CAST_UC(0xfffff192)
#define	UD2TIC           CAST_UC(0xfffff194)
#define	C1ERRIC          CAST_UC(0xfffff196)
#define	C1WUPIC          CAST_UC(0xfffff198)
#define	C1RECIC          CAST_UC(0xfffff19a)
#define	C1TRXIC          CAST_UC(0xfffff19c)
#define	ISPR             CAST_UC(0xfffff1fa)
#define	PRCMD            CAST_UC(0xfffff1fc)
#define	PSC              CAST_UC(0xfffff1fe)
#define	ADA0M0           CAST_UC(0xfffff200)
#define	ADA0M1           CAST_UC(0xfffff201)
#define	ADA0S            CAST_UC(0xfffff202)
#define	ADA0M2           CAST_UC(0xfffff203)
#define	ADA0PFM          CAST_UC(0xfffff204)
#define	ADA0PFT          CAST_UC(0xfffff205)
#define	ADA0CRDD         CAST_US(0xfffff20c)
#define	ADA0CRDDH        CAST_UC(0xfffff20d)
#define	ADA0CRSS         CAST_US(0xfffff20e)
#define	ADA0CRSSH        CAST_UC(0xfffff20f)
#define	ADA0CR0          CAST_US(0xfffff210)
#define	ADA0CR0H         CAST_UC(0xfffff211)
#define	ADA0CR1          CAST_US(0xfffff212)
#define	ADA0CR1H         CAST_UC(0xfffff213)
#define	ADA0CR2          CAST_US(0xfffff214)
#define	ADA0CR2H         CAST_UC(0xfffff215)
#define	ADA0CR3          CAST_US(0xfffff216)
#define	ADA0CR3H         CAST_UC(0xfffff217)
#define	ADA0CR4          CAST_US(0xfffff218)
#define	ADA0CR4H         CAST_UC(0xfffff219)
#define	ADA0CR5          CAST_US(0xfffff21a)
#define	ADA0CR5H         CAST_UC(0xfffff21b)
#define	ADA0CR6          CAST_US(0xfffff21c)
#define	ADA0CR6H         CAST_UC(0xfffff21d)
#define	ADA0CR7          CAST_US(0xfffff21e)
#define	ADA0CR7H         CAST_UC(0xfffff21f)
#define	ADA0CR8          CAST_US(0xfffff220)
#define	ADA0CR8H         CAST_UC(0xfffff221)
#define	ADA0CR9          CAST_US(0xfffff222)
#define	ADA0CR9H         CAST_UC(0xfffff223)
#define	ADA0CR10         CAST_US(0xfffff224)
#define	ADA0CR10H        CAST_UC(0xfffff225)
#define	ADA0CR11         CAST_US(0xfffff226)
#define	ADA0CR11H        CAST_UC(0xfffff227)
#define	ADA0CR12         CAST_US(0xfffff228)
#define	ADA0CR12H        CAST_UC(0xfffff229)
#define	ADA0CR13         CAST_US(0xfffff22a)
#define	ADA0CR13H        CAST_UC(0xfffff22b)
#define	ADA0CR14         CAST_US(0xfffff22c)
#define	ADA0CR14H        CAST_UC(0xfffff22d)
#define	ADA0CR15         CAST_US(0xfffff22e)
#define	ADA0CR15H        CAST_UC(0xfffff22f)
#define	KRM              CAST_UC(0xfffff300)
#define	SELCNT0          CAST_UC(0xfffff308)
#define	SELCNT2          CAST_UC(0xfffff30c)
#define	SELCNT3          CAST_UC(0xfffff30e)
#define	NFC              CAST_UC(0xfffff318)
#define	OCKS0            CAST_UC(0xfffff340)
#define	SSCGCTL          CAST_UC(0xfffff3f0)
#define	SFC0             CAST_UC(0xfffff3f1)
#define	SFC1             CAST_UC(0xfffff3f2)
#define	SELCNT4          CAST_UC(0xfffff3f8)
#define	P0               CAST_UC(0xfffff400)
#define	P1               CAST_UC(0xfffff402)
#define	P3               CAST_US(0xfffff406)
#define	P3L              CAST_UC(0xfffff406)
#define	P3H              CAST_UC(0xfffff407)
#define	P4               CAST_UC(0xfffff408)
#define	P5               CAST_UC(0xfffff40a)
#define	P7L              CAST_UC(0xfffff40e)
#define	P7H              CAST_UC(0xfffff40f)
#define	P9               CAST_US(0xfffff412)
#define	P9L              CAST_UC(0xfffff412)
#define	P9H              CAST_UC(0xfffff413)
#define	PM0              CAST_UC(0xfffff420)
#define	PM1              CAST_UC(0xfffff422)
#define	PM3              CAST_US(0xfffff426)
#define	PM3L             CAST_UC(0xfffff426)
#define	PM3H             CAST_UC(0xfffff427)
#define	PM4              CAST_UC(0xfffff428)
#define	PM5              CAST_UC(0xfffff42a)
#define	PM7L             CAST_UC(0xfffff42e)
#define	PM7H             CAST_UC(0xfffff42f)
#define	PM9              CAST_US(0xfffff432)
#define	PM9L             CAST_UC(0xfffff432)
#define	PM9H             CAST_UC(0xfffff433)
#define	PMC0             CAST_UC(0xfffff440)
#define	PMC1             CAST_UC(0xfffff442)
#define	PMC3             CAST_US(0xfffff446)
#define	PMC3L            CAST_UC(0xfffff446)
#define	PMC3H            CAST_UC(0xfffff447)
#define	PMC4             CAST_UC(0xfffff448)
#define	PMC5             CAST_UC(0xfffff44a)
#define	PMC7L            CAST_UC(0xfffff44e)
#define	PMC7H            CAST_UC(0xfffff44f)
#define	PMC9             CAST_US(0xfffff452)
#define	PMC9L            CAST_UC(0xfffff452)
#define	PMC9H            CAST_UC(0xfffff453)
#define	PFC0             CAST_UC(0xfffff460)
#define	PFC3L            CAST_UC(0xfffff466)
#define	PFC4             CAST_UC(0xfffff468)
#define	PFC5             CAST_UC(0xfffff46a)
#define	PFC9             CAST_US(0xfffff472)
#define	PFC9L            CAST_UC(0xfffff472)
#define	PFC9H            CAST_UC(0xfffff473)
#define	DWC0             CAST_US(0xfffff484)
#define	AWC              CAST_US(0xfffff488)
#define	BCC              CAST_US(0xfffff48a)
#define	TQ0CTL0          CAST_UC(0xfffff540)
#define	TQ0CTL1          CAST_UC(0xfffff541)
#define	TAB0IOC0         CAST_UC(0xfffff542)
#define	TAB0IOC1         CAST_UC(0xfffff543)
#define	TAB0IOC2         CAST_UC(0xfffff544)
#define	TAB0OPT0         CAST_UC(0xfffff545)
#define	TAB0CCR0         CAST_US(0xfffff546)
#define	TAB0CCR1         CAST_US(0xfffff548)
#define	TAB0CCR2         CAST_US(0xfffff54a)
#define	TAB0CCR3         CAST_US(0xfffff54c)
#define	TQ0CNT           CAST_US(0xfffff54e)
#define	TAB0IOC4         CAST_UC(0xfffff550)
#define	TAB0OPT1         CAST_UC(0xfffff560)
#define	TAB0OPT2         CAST_UC(0xfffff561)
#define	TAB0IOC3         CAST_UC(0xfffff562)
#define	TAB0DTC          CAST_US(0xfffff564)
#define	HZA0CTL0         CAST_UC(0xfffff570)
#define	HZA0CTL1         CAST_UC(0xfffff571)
#define	TAA0CTL0         CAST_UC(0xfffff590)
#define	TAA0CTL1         CAST_UC(0xfffff591)
#define	TAA0IOC0         CAST_UC(0xfffff592)
#define	TAA0IOC1         CAST_UC(0xfffff593)
#define	TAA0IOC2         CAST_UC(0xfffff594)
#define	TAA0OPT0         CAST_UC(0xfffff595)
#define	TAA0CCR0         CAST_US(0xfffff596)
#define	TAA0CCR1         CAST_US(0xfffff598)
#define	TAA0CNT          CAST_US(0xfffff59a)
#define	TAA0IOC4         CAST_UC(0xfffff59c)
#define	TAA1CTL0         CAST_UC(0xfffff5a0)
#define	TAA1CTL1         CAST_UC(0xfffff5a1)
#define	TAA1IOC0         CAST_UC(0xfffff5a2)
#define	TAA1IOC1         CAST_UC(0xfffff5a3)
#define	TAA1IOC2         CAST_UC(0xfffff5a4)
#define	TAA1OPT0         CAST_UC(0xfffff5a5)
#define	TAA1CCR0         CAST_US(0xfffff5a6)
#define	TAA1CCR1         CAST_US(0xfffff5a8)
#define	TAA1CNT          CAST_US(0xfffff5aa)
#define	TAA1IOC4         CAST_UC(0xfffff5ac)
#define	TAA1OPT1         CAST_UC(0xfffff5ad)
#define	TAA2CTL0         CAST_UC(0xfffff5b0)
#define	TAA2CTL1         CAST_UC(0xfffff5b1)
#define	TAA2IOC0         CAST_UC(0xfffff5b2)
#define	TAA2IOC1         CAST_UC(0xfffff5b3)
#define	TAA2IOC2         CAST_UC(0xfffff5b4)
#define	TAA2OPT0         CAST_UC(0xfffff5b5)
#define	TAA2CCR0         CAST_US(0xfffff5b6)
#define	TAA2CCR1         CAST_US(0xfffff5b8)
#define	TAA2CNT          CAST_US(0xfffff5ba)
#define	TAA2IOC4         CAST_UC(0xfffff5bc)
#define	TAA3CTL0         CAST_UC(0xfffff5c0)
#define	TAA3CTL1         CAST_UC(0xfffff5c1)
#define	TAA3IOC0         CAST_UC(0xfffff5c2)
#define	TAA3IOC1         CAST_UC(0xfffff5c3)
#define	TAA3IOC2         CAST_UC(0xfffff5c4)
#define	TAA3OPT0         CAST_UC(0xfffff5c5)
#define	TAA3CCR0         CAST_US(0xfffff5c6)
#define	TAA3CCR1         CAST_US(0xfffff5c8)
#define	TAA3CNT          CAST_US(0xfffff5ca)
#define	TAA3IOC4         CAST_UC(0xfffff5cc)
#define	TAA3OPT1         CAST_UC(0xfffff5cd)
#define	TAA4CTL0         CAST_UC(0xfffff5d0)
#define	TAA4CTL1         CAST_UC(0xfffff5d1)
#define	TAA4IOC0         CAST_UC(0xfffff5d2)
#define	TAA4IOC1         CAST_UC(0xfffff5d3)
#define	TAA4IOC2         CAST_UC(0xfffff5d4)
#define	TAA4OPT0         CAST_UC(0xfffff5d5)
#define	TAA4CCR0         CAST_US(0xfffff5d6)
#define	TAA4CCR1         CAST_US(0xfffff5d8)
#define	TAA4CNT          CAST_US(0xfffff5da)
#define	TAA4IOC4         CAST_UC(0xfffff5dc)
#define	TAB1CTL0         CAST_UC(0xfffff610)
#define	TAB1CTL1         CAST_UC(0xfffff611)
#define	TAB1IOC0         CAST_UC(0xfffff612)
#define	TAB1IOC1         CAST_UC(0xfffff613)
#define	TAB1IOC2         CAST_UC(0xfffff614)
#define	TAB1OPT0         CAST_UC(0xfffff615)
#define	TAB1CCR0         CAST_US(0xfffff616)
#define	TAB1CCR1         CAST_US(0xfffff618)
#define	TAB1CCR2         CAST_US(0xfffff61a)
#define	TAB1CCR3         CAST_US(0xfffff61c)
#define	TAB1CNT          CAST_US(0xfffff61e)
#define	TAB1IOC4         CAST_UC(0xfffff660)
#define	WTM              CAST_UC(0xfffff680)
#define	TM0CTL0          CAST_UC(0xfffff690)
#define	TM0CMP0          CAST_US(0xfffff694)
#define	OSTS             CAST_UC(0xfffff6c0)
#define	PLLS             CAST_UC(0xfffff6c1)
#define	OSTC             CAST_UC(0xfffff6c2)
#define	WDTM2            CAST_UC(0xfffff6d0)
#define	WDTE             CAST_UC(0xfffff6d1)
#define	PFCE0            CAST_UC(0xfffff700)
#define	PFCE3L           CAST_UC(0xfffff706)
#define	PFCE5            CAST_UC(0xfffff70a)
#define	PFCE9            CAST_US(0xfffff712)
#define	PFCE9L           CAST_UC(0xfffff712)
#define	PFCE9H           CAST_UC(0xfffff713)
#define	SYS              CAST_UC(0xfffff802)
#define	RCM              CAST_UC(0xfffff80c)
#define	DTFR0            CAST_UC(0xfffff810)
#define	DTFR1            CAST_UC(0xfffff812)
#define	DTFR2            CAST_UC(0xfffff814)
#define	DTFR3            CAST_UC(0xfffff816)
#define	PSMR             CAST_UC(0xfffff820)
#define	LOCKR            CAST_UC(0xfffff824)
#define	PCC              CAST_UC(0xfffff828)
#define	PLLCTL           CAST_UC(0xfffff82c)
#define	CCLS             CAST_UC(0xfffff82e)
#define	PCLM             CAST_UC(0xfffff82f)
#define	MCM              CAST_UC(0xfffff860)
#define	CLM              CAST_UC(0xfffff870)
#define	RESF             CAST_UC(0xfffff888)
#define	LVIM             CAST_UC(0xfffff890)
#define	LVIS             CAST_UC(0xfffff891)
#define	RAMS             CAST_UC(0xfffff892)
#define	PRSM0            CAST_UC(0xfffff8b0)
#define	PRSCM0           CAST_UC(0xfffff8b1)
#define	OCDM             CAST_UC(0xfffff9fc)
#define	PEMU1            CAST_UC(0xfffff9fe)
#define	UD0CTL0          CAST_UC(0xfffffa00)
#define	UD0CTL1          CAST_UC(0xfffffa01)
#define	UD0CTL2          CAST_UC(0xfffffa02)
#define	UD0OPT0          CAST_UC(0xfffffa03)
#define	UD0STR           CAST_UC(0xfffffa04)
#define	UD0OPT1          CAST_UC(0xfffffa05)
#define	UD0RX            CAST_UC(0xfffffa06)
#define	UD0TX            CAST_UC(0xfffffa07)
#define	UD1CTL0          CAST_UC(0xfffffa10)
#define	UD1CTL1          CAST_UC(0xfffffa11)
#define	UD1CTL2          CAST_UC(0xfffffa12)
#define	UD1OPT0          CAST_UC(0xfffffa13)
#define	UD1STR           CAST_UC(0xfffffa14)
#define	UD1OPT1          CAST_UC(0xfffffa15)
#define	UD1RX            CAST_UC(0xfffffa16)
#define	UD1TX            CAST_UC(0xfffffa17)
#define	UD2CTL0          CAST_UC(0xfffffa20)
#define	UD2CTL1          CAST_UC(0xfffffa21)
#define	UD2CTL2          CAST_UC(0xfffffa22)
#define	UD2OPT0          CAST_UC(0xfffffa23)
#define	UD2STR           CAST_UC(0xfffffa24)
#define	UD2OPT1          CAST_UC(0xfffffa25)
#define	UD2RX            CAST_UC(0xfffffa26)
#define	UD2TX            CAST_UC(0xfffffa27)
#define	INTF0            CAST_UC(0xfffffc00)
#define	INTF1            CAST_UC(0xfffffc02)
#define	INTF3            CAST_US(0xfffffc06)
#define	INTF3L           CAST_UC(0xfffffc06)
#define	INTF3H           CAST_UC(0xfffffc07)
#define	INTF9H           CAST_UC(0xfffffc13)
#define	INTR0            CAST_UC(0xfffffc20)
#define	INTR1            CAST_UC(0xfffffc22)
#define	INTR3            CAST_US(0xfffffc26)
#define	INTR3L           CAST_UC(0xfffffc26)
#define	INTR3H           CAST_UC(0xfffffc27)
#define	INTR9H           CAST_UC(0xfffffc33)
#define	PU0              CAST_UC(0xfffffc40)
#define	PU1              CAST_UC(0xfffffc42)
#define	PU3              CAST_US(0xfffffc46)
#define	PU3L             CAST_UC(0xfffffc46)
#define	PU3H             CAST_UC(0xfffffc47)
#define	PU4              CAST_UC(0xfffffc48)
#define	PU5              CAST_UC(0xfffffc4a)
#define	PU9              CAST_US(0xfffffc52)
#define	PU9L             CAST_UC(0xfffffc52)
#define	PU9H             CAST_UC(0xfffffc53)
#define	PF9H             CAST_UC(0xfffffc73)
#define PRDSELH          CAST_US(0xfffffcca)
#define	DFLCTL           CAST_UC(0xfffffcf8)
#define	CB0CTL0          CAST_UC(0xfffffd00)
#define	CB0CTL1          CAST_UC(0xfffffd01)
#define	CB0CTL2          CAST_UC(0xfffffd02)
#define	CB0STR           CAST_UC(0xfffffd03)
#define	CB0RX            CAST_US(0xfffffd04)
#define	CB0RXL           CAST_UC(0xfffffd04)
#define	CB0TX            CAST_US(0xfffffd06)
#define	CB0TXL           CAST_UC(0xfffffd06)
#define	CB1CTL0          CAST_UC(0xfffffd10)
#define	CB1CTL1          CAST_UC(0xfffffd11)
#define	CB1CTL2          CAST_UC(0xfffffd12)
#define	CB1STR           CAST_UC(0xfffffd13)
#define	CB1RX            CAST_US(0xfffffd14)
#define	CB1RXL           CAST_UC(0xfffffd14)
#define	CB1TX            CAST_US(0xfffffd16)
#define	CB1TXL           CAST_UC(0xfffffd16)
#define	IIC0             CAST_UC(0xfffffd80)
#define	IICC0            CAST_UC(0xfffffd82)
#define	SVA0             CAST_UC(0xfffffd83)
#define	IICCL0           CAST_UC(0xfffffd84)
#define	IICX0            CAST_UC(0xfffffd85)
#define	IICS0            CAST_UC(0xfffffd86)
#define	IICF0            CAST_UC(0xfffffd8a)


/* I/O register bit */

#ifdef __LANGUAGE_ASM__
#else

   #define  _MPCCMPIN1         ((volatile struct bitf *)0xfffff04c)->bit01

   #define	_E00              ((volatile struct bitf *)0xfffff0e0)->bit00
   #define	_STG0             ((volatile struct bitf *)0xfffff0e0)->bit01
   #define	_INIT0            ((volatile struct bitf *)0xfffff0e0)->bit02
   #define	_TC0              ((volatile struct bitf *)0xfffff0e0)->bit07

   #define	_E11              ((volatile struct bitf *)0xfffff0e2)->bit00
   #define	_STG1             ((volatile struct bitf *)0xfffff0e2)->bit01
   #define	_INIT1            ((volatile struct bitf *)0xfffff0e2)->bit02
   #define	_TC1              ((volatile struct bitf *)0xfffff0e2)->bit07

   #define	_E22              ((volatile struct bitf *)0xfffff0e4)->bit00
   #define	_STG2             ((volatile struct bitf *)0xfffff0e4)->bit01
   #define	_INIT2            ((volatile struct bitf *)0xfffff0e4)->bit02
   #define	_TC2              ((volatile struct bitf *)0xfffff0e4)->bit07

   #define	_E33              ((volatile struct bitf *)0xfffff0e6)->bit00
   #define	_STG3             ((volatile struct bitf *)0xfffff0e6)->bit01
   #define	_INIT3            ((volatile struct bitf *)0xfffff0e6)->bit02
   #define	_TC3              ((volatile struct bitf *)0xfffff0e6)->bit07

   #define	_LVILMK           ((volatile struct bitf *)0xfffff110)->bit06
   #define	_LVILIF           ((volatile struct bitf *)0xfffff110)->bit07

   #define	_LVIHMK           ((volatile struct bitf *)0xfffff112)->bit06
   #define	_LVIHIF           ((volatile struct bitf *)0xfffff112)->bit07

   #define	_PMK0             ((volatile struct bitf *)0xfffff114)->bit06
   #define	_PIF0             ((volatile struct bitf *)0xfffff114)->bit07

   #define	_PMK1             ((volatile struct bitf *)0xfffff116)->bit06
   #define	_PIF1             ((volatile struct bitf *)0xfffff116)->bit07

   #define	_PMK2             ((volatile struct bitf *)0xfffff118)->bit06
   #define	_PIF2             ((volatile struct bitf *)0xfffff118)->bit07

   #define	_PMK3             ((volatile struct bitf *)0xfffff11a)->bit06
   #define	_PIF3             ((volatile struct bitf *)0xfffff11a)->bit07

   #define	_PMK4             ((volatile struct bitf *)0xfffff11c)->bit06
   #define	_PIF4             ((volatile struct bitf *)0xfffff11c)->bit07

   #define	_PMK5             ((volatile struct bitf *)0xfffff11e)->bit06
   #define	_PIF5             ((volatile struct bitf *)0xfffff11e)->bit07

   #define	_PMK6             ((volatile struct bitf *)0xfffff120)->bit06
   #define	_PIF6             ((volatile struct bitf *)0xfffff120)->bit07

   #define	_PMK7             ((volatile struct bitf *)0xfffff122)->bit06
   #define	_PIF7             ((volatile struct bitf *)0xfffff122)->bit07

   #define	_TAB0OVMK         ((volatile struct bitf *)0xfffff124)->bit06
   #define	_TAB0OVIF         ((volatile struct bitf *)0xfffff124)->bit07

   #define	_TAB0CCMK0        ((volatile struct bitf *)0xfffff126)->bit06
   #define	_TAB0CCIF0        ((volatile struct bitf *)0xfffff126)->bit07

   #define	_TAB0CCMK1        ((volatile struct bitf *)0xfffff128)->bit06
   #define	_TAB0CCIF1        ((volatile struct bitf *)0xfffff128)->bit07

   #define	_TAB0CCMK2        ((volatile struct bitf *)0xfffff12a)->bit06
   #define	_TAB0CCIF2        ((volatile struct bitf *)0xfffff12a)->bit07

   #define	_TAB0CCMK3        ((volatile struct bitf *)0xfffff12c)->bit06
   #define	_TAB0CCIF3        ((volatile struct bitf *)0xfffff12c)->bit07

   #define	_TAA0OVMK         ((volatile struct bitf *)0xfffff12e)->bit06
   #define	_TAA0OVIF         ((volatile struct bitf *)0xfffff12e)->bit07

   #define	_TAA0CCMK0        ((volatile struct bitf *)0xfffff130)->bit06
   #define	_TAA0CCIF0        ((volatile struct bitf *)0xfffff130)->bit07

   #define	_TAA0CCMK1        ((volatile struct bitf *)0xfffff132)->bit06
   #define	_TAA0CCIF1        ((volatile struct bitf *)0xfffff132)->bit07

   #define	_TAA1OVMK         ((volatile struct bitf *)0xfffff134)->bit06
   #define	_TAA1OVIF         ((volatile struct bitf *)0xfffff134)->bit07

   #define	_TAA1CCMK0        ((volatile struct bitf *)0xfffff136)->bit06
   #define	_TAA1CCIF0        ((volatile struct bitf *)0xfffff136)->bit07

   #define	_TAA1CCMK1        ((volatile struct bitf *)0xfffff138)->bit06
   #define	_TAA1CCIF1        ((volatile struct bitf *)0xfffff138)->bit07

   #define	_TAA2OVMK         ((volatile struct bitf *)0xfffff13a)->bit06
   #define	_TAA2OVIF         ((volatile struct bitf *)0xfffff13a)->bit07

   #define	_TAA2CCMK0        ((volatile struct bitf *)0xfffff13c)->bit06
   #define	_TAA2CCIF0        ((volatile struct bitf *)0xfffff13c)->bit07

   #define	_TAA2CCMK1        ((volatile struct bitf *)0xfffff13e)->bit06
   #define	_TAA2CCIF1        ((volatile struct bitf *)0xfffff13e)->bit07

   #define	_TAA3OVMK         ((volatile struct bitf *)0xfffff140)->bit06
   #define	_TAA3OVIF         ((volatile struct bitf *)0xfffff140)->bit07

   #define	_TAA3CCMK0        ((volatile struct bitf *)0xfffff142)->bit06
   #define	_TAA3CCIF0        ((volatile struct bitf *)0xfffff142)->bit07

   #define	_TAA3CCMK1        ((volatile struct bitf *)0xfffff144)->bit06
   #define	_TAA3CCIF1        ((volatile struct bitf *)0xfffff144)->bit07

   #define	_TAA4OVMK         ((volatile struct bitf *)0xfffff146)->bit06
   #define	_TAA4OVIF         ((volatile struct bitf *)0xfffff146)->bit07

   #define	_TAA4CCMK0        ((volatile struct bitf *)0xfffff148)->bit06
   #define	_TAA4CCIF0        ((volatile struct bitf *)0xfffff148)->bit07

   #define	_TAA4CCMK1        ((volatile struct bitf *)0xfffff14a)->bit06
   #define	_TAA4CCIF1        ((volatile struct bitf *)0xfffff14a)->bit07

   #define	_TM0EQMK0         ((volatile struct bitf *)0xfffff14c)->bit06
   #define	_TM0EQIF0         ((volatile struct bitf *)0xfffff14c)->bit07

   #define	_CB0RMK           ((volatile struct bitf *)0xfffff14e)->bit06
   #define	_CB0RIF           ((volatile struct bitf *)0xfffff14e)->bit07

   #define	_CB0TMK           ((volatile struct bitf *)0xfffff150)->bit06
   #define	_CB0TIF           ((volatile struct bitf *)0xfffff150)->bit07

   #define	_CB1RMK           ((volatile struct bitf *)0xfffff152)->bit06
   #define	_CB1RIF           ((volatile struct bitf *)0xfffff152)->bit07

   #define	_CB1TMK           ((volatile struct bitf *)0xfffff154)->bit06
   #define	_CB1TIF           ((volatile struct bitf *)0xfffff154)->bit07

   #define	_UD0SMK           ((volatile struct bitf *)0xfffff156)->bit06
   #define	_UD0SIF           ((volatile struct bitf *)0xfffff156)->bit07

   #define	_UD0RMK           ((volatile struct bitf *)0xfffff158)->bit06
   #define	_UD0RIF           ((volatile struct bitf *)0xfffff158)->bit07

   #define	_UD0TMK           ((volatile struct bitf *)0xfffff15a)->bit06
   #define	_UD0TIF           ((volatile struct bitf *)0xfffff15a)->bit07

   #define	_UD1SMK           ((volatile struct bitf *)0xfffff15c)->bit06
   #define	_UD1SIF           ((volatile struct bitf *)0xfffff15c)->bit07

   #define	_UD1RMK           ((volatile struct bitf *)0xfffff15e)->bit06
   #define	_UD1RIF           ((volatile struct bitf *)0xfffff15e)->bit07

   #define	_UD1TMK           ((volatile struct bitf *)0xfffff160)->bit06
   #define	_UD1TIF           ((volatile struct bitf *)0xfffff160)->bit07

   #define	_IIC0MK           ((volatile struct bitf *)0xfffff162)->bit06
   #define	_IIC0IF           ((volatile struct bitf *)0xfffff162)->bit07

   #define	_ADMK             ((volatile struct bitf *)0xfffff164)->bit06
   #define	_ADIF             ((volatile struct bitf *)0xfffff164)->bit07

   #define	_C0ERRMK          ((volatile struct bitf *)0xfffff166)->bit06
   #define	_C0ERRIF          ((volatile struct bitf *)0xfffff166)->bit07

   #define	_C0WUPMK          ((volatile struct bitf *)0xfffff168)->bit06
   #define	_C0WUPIF          ((volatile struct bitf *)0xfffff168)->bit07

   #define	_C0RECMK          ((volatile struct bitf *)0xfffff16a)->bit06
   #define	_C0RECIF          ((volatile struct bitf *)0xfffff16a)->bit07

   #define	_C0TRXMK          ((volatile struct bitf *)0xfffff16c)->bit06
   #define	_C0TRXIF          ((volatile struct bitf *)0xfffff16c)->bit07

   #define	_DMAMK0           ((volatile struct bitf *)0xfffff16e)->bit06
   #define	_DMAIF0           ((volatile struct bitf *)0xfffff16e)->bit07

   #define	_DMAMK1           ((volatile struct bitf *)0xfffff170)->bit06
   #define	_DMAIF1           ((volatile struct bitf *)0xfffff170)->bit07

   #define	_DMAMK2           ((volatile struct bitf *)0xfffff172)->bit06
   #define	_DMAIF2           ((volatile struct bitf *)0xfffff172)->bit07

   #define	_DMAMK3           ((volatile struct bitf *)0xfffff174)->bit06
   #define	_DMAIF3           ((volatile struct bitf *)0xfffff174)->bit07

   #define	_KRMK             ((volatile struct bitf *)0xfffff176)->bit06
   #define	_KRIF             ((volatile struct bitf *)0xfffff176)->bit07

   #define	_WTIMK            ((volatile struct bitf *)0xfffff178)->bit06
   #define	_WTIIF            ((volatile struct bitf *)0xfffff178)->bit07

   #define	_WTMK             ((volatile struct bitf *)0xfffff17a)->bit06
   #define	_WTIF             ((volatile struct bitf *)0xfffff17a)->bit07

   #define	_ECCDMK           ((volatile struct bitf *)0xfffff17c)->bit06
   #define	_ECCDIF           ((volatile struct bitf *)0xfffff17c)->bit07

   #define	_FLMK             ((volatile struct bitf *)0xfffff17e)->bit06
   #define	_FLIF             ((volatile struct bitf *)0xfffff17e)->bit07

   #define	_PMK8             ((volatile struct bitf *)0xfffff180)->bit06
   #define	_PIF8             ((volatile struct bitf *)0xfffff180)->bit07

   #define	_PMK9             ((volatile struct bitf *)0xfffff182)->bit06
   #define	_PIF9             ((volatile struct bitf *)0xfffff182)->bit07

   #define	_PMK10            ((volatile struct bitf *)0xfffff184)->bit06
   #define	_PIF10            ((volatile struct bitf *)0xfffff184)->bit07

   #define	_TAB1OVMK         ((volatile struct bitf *)0xfffff186)->bit06
   #define	_TAB1OVIF         ((volatile struct bitf *)0xfffff186)->bit07

   #define	_TAB1CCMK0        ((volatile struct bitf *)0xfffff188)->bit06
   #define	_TAB1CCIF0        ((volatile struct bitf *)0xfffff188)->bit07

   #define	_TAB1CCMK1        ((volatile struct bitf *)0xfffff18a)->bit06
   #define	_TAB1CCIF1        ((volatile struct bitf *)0xfffff18a)->bit07

   #define	_TAB1CCMK2        ((volatile struct bitf *)0xfffff18c)->bit06
   #define	_TAB1CCIF2        ((volatile struct bitf *)0xfffff18c)->bit07

   #define	_TAB1CCMK3        ((volatile struct bitf *)0xfffff18e)->bit06
   #define	_TAB1CCIF3        ((volatile struct bitf *)0xfffff18e)->bit07

   #define	_UD2SMK           ((volatile struct bitf *)0xfffff190)->bit06
   #define	_UD2SIF           ((volatile struct bitf *)0xfffff190)->bit07

   #define	_UD2RMK           ((volatile struct bitf *)0xfffff192)->bit06
   #define	_UD2RIF           ((volatile struct bitf *)0xfffff192)->bit07

   #define	_UD2TMK           ((volatile struct bitf *)0xfffff194)->bit06
   #define	_UD2TIF           ((volatile struct bitf *)0xfffff194)->bit07

   #define	_C1ERRMK          ((volatile struct bitf *)0xfffff196)->bit06
   #define	_C1ERRIF          ((volatile struct bitf *)0xfffff196)->bit07

   #define	_C1WUPMK          ((volatile struct bitf *)0xfffff198)->bit06
   #define	_C1WUPIF          ((volatile struct bitf *)0xfffff198)->bit07

   #define	_C1RECMK          ((volatile struct bitf *)0xfffff19a)->bit06
   #define	_C1RECIF          ((volatile struct bitf *)0xfffff19a)->bit07

   #define	_C1TRXMK          ((volatile struct bitf *)0xfffff19c)->bit06
   #define	_C1TRXIF          ((volatile struct bitf *)0xfffff19c)->bit07

   #define	_ISPR0            ((volatile struct bitf *)0xfffff1fa)->bit00
   #define	_ISPR1            ((volatile struct bitf *)0xfffff1fa)->bit01
   #define	_ISPR2            ((volatile struct bitf *)0xfffff1fa)->bit02
   #define	_ISPR3            ((volatile struct bitf *)0xfffff1fa)->bit03
   #define	_ISPR4            ((volatile struct bitf *)0xfffff1fa)->bit04
   #define	_ISPR5            ((volatile struct bitf *)0xfffff1fa)->bit05
   #define	_ISPR6            ((volatile struct bitf *)0xfffff1fa)->bit06
   #define	_ISPR7            ((volatile struct bitf *)0xfffff1fa)->bit07

   #define	_STP              ((volatile struct bitf *)0xfffff1fe)->bit01
   #define	_INTM             ((volatile struct bitf *)0xfffff1fe)->bit04
   #define	_NMI0M            ((volatile struct bitf *)0xfffff1fe)->bit05
   #define	_NMI1M            ((volatile struct bitf *)0xfffff1fe)->bit06

   #define	_ADA0EF           ((volatile struct bitf *)0xfffff200)->bit00
   #define	_ADA0PS           ((volatile struct bitf *)0xfffff200)->bit06
   #define	_ADA0CE           ((volatile struct bitf *)0xfffff200)->bit07

   #define	_ADA0DISC         ((volatile struct bitf *)0xfffff203)->bit04
   #define	_ADA0DIAG         ((volatile struct bitf *)0xfffff203)->bit05

   #define	_ADA0PFC          ((volatile struct bitf *)0xfffff204)->bit06
   #define	_ADA0PFE          ((volatile struct bitf *)0xfffff204)->bit07

   #define	_ADA0PFT0         ((volatile struct bitf *)0xfffff205)->bit00
   #define	_ADA0PFT1         ((volatile struct bitf *)0xfffff205)->bit01
   #define	_ADA0PFT2         ((volatile struct bitf *)0xfffff205)->bit02
   #define	_ADA0PFT3         ((volatile struct bitf *)0xfffff205)->bit03
   #define	_ADA0PFT4         ((volatile struct bitf *)0xfffff205)->bit04
   #define	_ADA0PFT5         ((volatile struct bitf *)0xfffff205)->bit05
   #define	_ADA0PFT6         ((volatile struct bitf *)0xfffff205)->bit06
   #define	_ADA0PFT7         ((volatile struct bitf *)0xfffff205)->bit07

   #define	_ISEL00           ((volatile struct bitf *)0xfffff308)->bit00
   #define	_ISEL01           ((volatile struct bitf *)0xfffff308)->bit01
   #define	_ISEL02           ((volatile struct bitf *)0xfffff308)->bit02
   #define	_ISEL03           ((volatile struct bitf *)0xfffff308)->bit03
   #define	_ISEL04           ((volatile struct bitf *)0xfffff308)->bit04
   #define	_ISEL05           ((volatile struct bitf *)0xfffff308)->bit05
   #define	_ISEL07           ((volatile struct bitf *)0xfffff308)->bit07

   #define	_ISEL20           ((volatile struct bitf *)0xfffff30c)->bit00
   #define	_ISEL21           ((volatile struct bitf *)0xfffff30c)->bit01
   #define	_ISEL22           ((volatile struct bitf *)0xfffff30c)->bit02
   #define	_ISEL23           ((volatile struct bitf *)0xfffff30c)->bit03
   #define	_ISEL24           ((volatile struct bitf *)0xfffff30c)->bit04
   #define	_ISEL25           ((volatile struct bitf *)0xfffff30c)->bit05
   #define	_ISEL26           ((volatile struct bitf *)0xfffff30c)->bit06
   #define	_ISEL27           ((volatile struct bitf *)0xfffff30c)->bit07

   #define	_ISEL31           ((volatile struct bitf *)0xfffff30e)->bit01
   #define	_ISEL32           ((volatile struct bitf *)0xfffff30e)->bit02

   #define	_SSCGON           ((volatile struct bitf *)0xfffff3f0)->bit00
   #define	_SELSSCG          ((volatile struct bitf *)0xfffff3f0)->bit01

   #define	_ISEL40           ((volatile struct bitf *)0xfffff3f8)->bit00

   #define	_PMC3L0           ((volatile struct bitf *)0xfffff446)->bit00
   #define	_PMC3L1           ((volatile struct bitf *)0xfffff446)->bit01
   #define	_PMC3L2           ((volatile struct bitf *)0xfffff446)->bit02
   #define	_PMC3L3           ((volatile struct bitf *)0xfffff446)->bit03
   #define	_PMC3L4           ((volatile struct bitf *)0xfffff446)->bit04
   #define  _PMC3L6           ((volatile struct bitf *)0xfffff446)->bit06
   #define  _PMC3L7           ((volatile struct bitf *)0xfffff446)->bit07
   
   #define	_PMC3H0           ((volatile struct bitf *)0xfffff447)->bit00
   #define	_PMC3H1           ((volatile struct bitf *)0xfffff447)->bit01

   
   #define	_PMC9L0           ((volatile struct bitf *)0xfffff452)->bit00
   #define	_PMC9L1           ((volatile struct bitf *)0xfffff452)->bit01

   #define	_TAB0CE           ((volatile struct bitf *)0xfffff540)->bit07

   #define	_TAB0EEE          ((volatile struct bitf *)0xfffff541)->bit05
   #define	_TAB0EST          ((volatile struct bitf *)0xfffff541)->bit06

   #define	_TAB0OE0          ((volatile struct bitf *)0xfffff542)->bit00
   #define	_TAB0OE1          ((volatile struct bitf *)0xfffff542)->bit02
   #define	_TAB0OE2          ((volatile struct bitf *)0xfffff542)->bit04
   #define	_TAB0OE3          ((volatile struct bitf *)0xfffff542)->bit06

   #define	_TAB0OVF          ((volatile struct bitf *)0xfffff545)->bit00

   #define	_TAB0IOE          ((volatile struct bitf *)0xfffff560)->bit06
   #define	_TAB0ICE          ((volatile struct bitf *)0xfffff560)->bit07

   #define	_TAB0AT0          ((volatile struct bitf *)0xfffff561)->bit00
   #define	_TAB0AT1          ((volatile struct bitf *)0xfffff561)->bit01
   #define	_TAB0AT2          ((volatile struct bitf *)0xfffff561)->bit02
   #define	_TAB0AT3          ((volatile struct bitf *)0xfffff561)->bit03
   #define	_TAB0ATM2         ((volatile struct bitf *)0xfffff561)->bit04
   #define	_TAB0ATM3         ((volatile struct bitf *)0xfffff561)->bit05
   #define	_TAB0DTM          ((volatile struct bitf *)0xfffff561)->bit06
   #define	_TAB0RDE          ((volatile struct bitf *)0xfffff561)->bit07

   #define	_TAB0OEB1         ((volatile struct bitf *)0xfffff562)->bit02
   #define	_TAB0OLB1         ((volatile struct bitf *)0xfffff562)->bit03
   #define	_TAB0OEB2         ((volatile struct bitf *)0xfffff562)->bit04
   #define	_TAB0OLB2         ((volatile struct bitf *)0xfffff562)->bit05
   #define	_TAB0OEB3         ((volatile struct bitf *)0xfffff562)->bit06
   #define	_TAB0OLB3         ((volatile struct bitf *)0xfffff562)->bit07

   #define	_HZA0DCF0         ((volatile struct bitf *)0xfffff570)->bit00
   #define	_HZA0DCC0         ((volatile struct bitf *)0xfffff570)->bit02
   #define	_HZA0DCT0         ((volatile struct bitf *)0xfffff570)->bit03
   #define	_HZA0DCM0         ((volatile struct bitf *)0xfffff570)->bit06
   #define	_HZA0DCE0         ((volatile struct bitf *)0xfffff570)->bit07

   #define	_HZA0DCF1         ((volatile struct bitf *)0xfffff571)->bit00
   #define	_HZA0DCC1         ((volatile struct bitf *)0xfffff571)->bit02
   #define	_HZA0DCT1         ((volatile struct bitf *)0xfffff571)->bit03
   #define	_HZA0DCM1         ((volatile struct bitf *)0xfffff571)->bit06
   #define	_HZA0DCE1         ((volatile struct bitf *)0xfffff571)->bit07

   #define	_TAA0CE           ((volatile struct bitf *)0xfffff590)->bit07

   #define	_TAA0EEE          ((volatile struct bitf *)0xfffff591)->bit05
   #define	_TAA0EST          ((volatile struct bitf *)0xfffff591)->bit06

   #define	_TAA0OE0          ((volatile struct bitf *)0xfffff592)->bit00
   #define	_TAA0OE1          ((volatile struct bitf *)0xfffff592)->bit02

   #define	_TAA0OVF          ((volatile struct bitf *)0xfffff595)->bit00

   #define	_TAA1CE           ((volatile struct bitf *)0xfffff5a0)->bit07

   #define	_TAA1EEE          ((volatile struct bitf *)0xfffff5a1)->bit05
   #define	_TAA1EST          ((volatile struct bitf *)0xfffff5a1)->bit06
   #define	_TAA1SYE          ((volatile struct bitf *)0xfffff5a1)->bit07

   #define	_TAA1OE0          ((volatile struct bitf *)0xfffff5a2)->bit00
   #define	_TAA1OE1          ((volatile struct bitf *)0xfffff5a2)->bit02

   #define	_TAA1OVF          ((volatile struct bitf *)0xfffff5a5)->bit00

   #define	_TAA1CSE          ((volatile struct bitf *)0xfffff5ad)->bit07

   #define	_TAA2CE           ((volatile struct bitf *)0xfffff5b0)->bit07

   #define	_TAA2EEE          ((volatile struct bitf *)0xfffff5b1)->bit05
   #define	_TAA2EST          ((volatile struct bitf *)0xfffff5b1)->bit06

   #define	_TAA2OE0          ((volatile struct bitf *)0xfffff5b2)->bit00
   #define	_TAA2OE1          ((volatile struct bitf *)0xfffff5b2)->bit02

   #define	_TAA2OVF          ((volatile struct bitf *)0xfffff5b5)->bit00

   #define	_TAA3CE           ((volatile struct bitf *)0xfffff5c0)->bit07

   #define	_TAA3EEE          ((volatile struct bitf *)0xfffff5c1)->bit05
   #define	_TAA3EST          ((volatile struct bitf *)0xfffff5c1)->bit06
   #define	_TAA3SYE          ((volatile struct bitf *)0xfffff5c1)->bit07

   #define	_TAA3OE0          ((volatile struct bitf *)0xfffff5c2)->bit00
   #define	_TAA3OE1          ((volatile struct bitf *)0xfffff5c2)->bit02

   #define	_TAA3OVF          ((volatile struct bitf *)0xfffff5c5)->bit00

   #define	_TAA3CSE          ((volatile struct bitf *)0xfffff5cd)->bit07

   #define	_TAA4CE           ((volatile struct bitf *)0xfffff5d0)->bit07

   #define	_TAA4EEE          ((volatile struct bitf *)0xfffff5d1)->bit05
   #define	_TAA4EST          ((volatile struct bitf *)0xfffff5d1)->bit06
   #define	_TAA4SYE          ((volatile struct bitf *)0xfffff5d1)->bit07

   #define	_TAA4OE0          ((volatile struct bitf *)0xfffff5d2)->bit00
   #define	_TAA4OE1          ((volatile struct bitf *)0xfffff5d2)->bit02

   #define	_TAA4OVF          ((volatile struct bitf *)0xfffff5d5)->bit00

   #define	_TAB1CE           ((volatile struct bitf *)0xfffff610)->bit07

   #define	_TAB1EEE          ((volatile struct bitf *)0xfffff611)->bit05
   #define	_TAB1EST          ((volatile struct bitf *)0xfffff611)->bit06

   #define	_TAB1OE0          ((volatile struct bitf *)0xfffff612)->bit00
   #define	_TAB1OE1          ((volatile struct bitf *)0xfffff612)->bit02
   #define	_TAB1OE2          ((volatile struct bitf *)0xfffff612)->bit04
   #define	_TAB1OE3          ((volatile struct bitf *)0xfffff612)->bit06

   #define	_TAB1OVF          ((volatile struct bitf *)0xfffff615)->bit00

   #define	_WTM0             ((volatile struct bitf *)0xfffff680)->bit00
   #define	_WTM1             ((volatile struct bitf *)0xfffff680)->bit00

   
   #define	_TM0CE            ((volatile struct bitf *)0xfffff690)->bit07
   
   #define  _PFCE3L3          ((volatile struct bitf *)0xfffff706)->bit03
   #define  _PFCE3L4          ((volatile struct bitf *)0xfffff706)->bit04
   
   #define	_PFCE90           ((volatile struct bitf *)0xfffff712)->bit00
   #define	_PFCE91           ((volatile struct bitf *)0xfffff712)->bit01

   #define	_PRERR            ((volatile struct bitf *)0xfffff802)->bit00

   #define	_RSTOP            ((volatile struct bitf *)0xfffff80c)->bit00
   #define	_HRSTOP           ((volatile struct bitf *)0xfffff80c)->bit01

   #define	_DF0              ((volatile struct bitf *)0xfffff810)->bit07

   #define	_DF1              ((volatile struct bitf *)0xfffff812)->bit07

   #define	_DF2              ((volatile struct bitf *)0xfffff814)->bit07

   #define	_DF3              ((volatile struct bitf *)0xfffff816)->bit07

   #define	_PSM0             ((volatile struct bitf *)0xfffff820)->bit00
   #define	_PSM1             ((volatile struct bitf *)0xfffff820)->bit01

   #define	_LOCK             ((volatile struct bitf *)0xfffff824)->bit00

   #define	_CK3              ((volatile struct bitf *)0xfffff828)->bit03
   #define	_CLS              ((volatile struct bitf *)0xfffff828)->bit04
   #define	_MCK              ((volatile struct bitf *)0xfffff828)->bit06

   #define	_PLLON            ((volatile struct bitf *)0xfffff82c)->bit00
   #define	_SELPLL           ((volatile struct bitf *)0xfffff82c)->bit01

   #define	_PCLE             ((volatile struct bitf *)0xfffff82f)->bit04

   #define	_MCM0             ((volatile struct bitf *)0xfffff860)->bit00
   #define	_MCS              ((volatile struct bitf *)0xfffff860)->bit01

   #define	_CLME             ((volatile struct bitf *)0xfffff870)->bit00

   #define	_LVIF             ((volatile struct bitf *)0xfffff890)->bit00
   #define	_LVIMD            ((volatile struct bitf *)0xfffff890)->bit01
   #define	_LVION            ((volatile struct bitf *)0xfffff890)->bit07

   #define	_RAMF             ((volatile struct bitf *)0xfffff892)->bit00

   #define	_BGCE0            ((volatile struct bitf *)0xfffff8b0)->bit04

   #define	_OCDM0            ((volatile struct bitf *)0xfffff9fc)->bit00

   #define  _UD0SL            ((volatile struct bitf *)0xfffffa00)->bit00
   #define  _UD0CL            ((volatile struct bitf *)0xfffffa00)->bit01
   #define  _UD0PS0           ((volatile struct bitf *)0xfffffa00)->bit02
   #define  _UD0PS1           ((volatile struct bitf *)0xfffffa00)->bit03
   #define	_UD0DIR           ((volatile struct bitf *)0xfffffa00)->bit04
   #define	_UD0RXE           ((volatile struct bitf *)0xfffffa00)->bit05
   #define	_UD0TXE           ((volatile struct bitf *)0xfffffa00)->bit06
   #define	_UD0PWR           ((volatile struct bitf *)0xfffffa00)->bit07

   #define	_UD0SRF           ((volatile struct bitf *)0xfffffa03)->bit07

   #define	_UD0OVE           ((volatile struct bitf *)0xfffffa04)->bit00
   #define	_UD0FE            ((volatile struct bitf *)0xfffffa04)->bit01
   #define	_UD0PE            ((volatile struct bitf *)0xfffffa04)->bit02
   #define	_UD0TSF           ((volatile struct bitf *)0xfffffa04)->bit07

   #define  _UD1SL            ((volatile struct bitf *)0xfffffa10)->bit00
   #define  _UD1CL            ((volatile struct bitf *)0xfffffa10)->bit01
   #define  _UD1PS0           ((volatile struct bitf *)0xfffffa10)->bit02
   #define  _UD1PS1           ((volatile struct bitf *)0xfffffa10)->bit03
   #define	_UD1DIR           ((volatile struct bitf *)0xfffffa10)->bit04
   #define	_UD1RXE           ((volatile struct bitf *)0xfffffa10)->bit05
   #define	_UD1TXE           ((volatile struct bitf *)0xfffffa10)->bit06
   #define	_UD1PWR           ((volatile struct bitf *)0xfffffa10)->bit07

   #define	_UD1SRF           ((volatile struct bitf *)0xfffffa13)->bit07

   #define	_UD1OVE           ((volatile struct bitf *)0xfffffa14)->bit00
   #define	_UD1FE            ((volatile struct bitf *)0xfffffa14)->bit01
   #define	_UD1PE            ((volatile struct bitf *)0xfffffa14)->bit02
   #define	_UD1TSF           ((volatile struct bitf *)0xfffffa14)->bit07

   #define  _UD2CL            ((volatile struct bitf *)0xfffffa20)->bit01
   #define	_UD2DIR           ((volatile struct bitf *)0xfffffa20)->bit04
   #define	_UD2RXE           ((volatile struct bitf *)0xfffffa20)->bit05
   #define	_UD2TXE           ((volatile struct bitf *)0xfffffa20)->bit06
   #define	_UD2PWR           ((volatile struct bitf *)0xfffffa20)->bit07

   #define	_UD2SRF           ((volatile struct bitf *)0xfffffa23)->bit07

   #define	_UD2OVE           ((volatile struct bitf *)0xfffffa24)->bit00
   #define	_UD2FE            ((volatile struct bitf *)0xfffffa24)->bit01
   #define	_UD2PE            ((volatile struct bitf *)0xfffffa24)->bit02
   #define	_UD2TSF           ((volatile struct bitf *)0xfffffa24)->bit07

   #define	_DFLEN            ((volatile struct bitf *)0xfffffcf8)->bit07

   #define	_CB0SCE           ((volatile struct bitf *)0xfffffd00)->bit00
   #define	_CB0DIR           ((volatile struct bitf *)0xfffffd00)->bit04
   #define	_CB0RXE           ((volatile struct bitf *)0xfffffd00)->bit05
   #define	_CB0TXE           ((volatile struct bitf *)0xfffffd00)->bit06
   #define	_CB0PWR           ((volatile struct bitf *)0xfffffd00)->bit07

   #define	_CB0OVE           ((volatile struct bitf *)0xfffffd03)->bit00
   #define	_CB0TSF           ((volatile struct bitf *)0xfffffd03)->bit07

   #define	_CB1SCE           ((volatile struct bitf *)0xfffffd10)->bit00
   #define	_CB1DIR           ((volatile struct bitf *)0xfffffd10)->bit04
   #define	_CB1RXE           ((volatile struct bitf *)0xfffffd10)->bit05
   #define	_CB1TXE           ((volatile struct bitf *)0xfffffd10)->bit06
   #define	_CB1PWR           ((volatile struct bitf *)0xfffffd10)->bit07

   #define	_CB1OVE           ((volatile struct bitf *)0xfffffd13)->bit00
   #define	_CB1TSF           ((volatile struct bitf *)0xfffffd13)->bit07

   #define	_SPT0             ((volatile struct bitf *)0xfffffd82)->bit00
   #define	_STT0             ((volatile struct bitf *)0xfffffd82)->bit01
   #define	_ACKE0            ((volatile struct bitf *)0xfffffd82)->bit02
   #define	_WTIM0            ((volatile struct bitf *)0xfffffd82)->bit03
   #define	_SPIE0            ((volatile struct bitf *)0xfffffd82)->bit04
   #define	_WREL0            ((volatile struct bitf *)0xfffffd82)->bit05
   #define	_LREL0            ((volatile struct bitf *)0xfffffd82)->bit06
   #define	_IICE0            ((volatile struct bitf *)0xfffffd82)->bit07

   #define	_DAD0             ((volatile struct bitf *)0xfffffd84)->bit04
   #define	_CLD0             ((volatile struct bitf *)0xfffffd84)->bit05

   #define	_CLX0             ((volatile struct bitf *)0xfffffd85)->bit00

   #define	_SPD0             ((volatile struct bitf *)0xfffffd86)->bit00
   #define	_STD0             ((volatile struct bitf *)0xfffffd86)->bit01
   #define	_ACKD0            ((volatile struct bitf *)0xfffffd86)->bit02
   #define	_TRC0             ((volatile struct bitf *)0xfffffd86)->bit03
   #define	_COI0             ((volatile struct bitf *)0xfffffd86)->bit04
   #define	_EXC0             ((volatile struct bitf *)0xfffffd86)->bit05
   #define	_ALD0             ((volatile struct bitf *)0xfffffd86)->bit06
   #define	_MSTS0            ((volatile struct bitf *)0xfffffd86)->bit07

   #define	_IICRSV0          ((volatile struct bitf *)0xfffffd8a)->bit00
   #define	_STCEN0           ((volatile struct bitf *)0xfffffd8a)->bit01
   #define	_IICBSY0          ((volatile struct bitf *)0xfffffd8a)->bit06
   #define	_STCF0            ((volatile struct bitf *)0xfffffd8a)->bit07
#endif /* __LANGUAGE_ASM__ */


#endif /* __uPD70F3375_H */
