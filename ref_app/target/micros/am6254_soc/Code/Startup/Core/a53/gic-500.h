#ifndef __GIC_500_H__
#define __GIC_500_H__

#include <stdint.h>

#define GIC_TRANSLATER_BASE  (0x1000000UL)
#define GIC_BASE             (0x1800000UL)
#define GICD_BASE            (GIC_BASE + 0x00000UL)
#define GICR_BASE            (GIC_BASE + 0x80000UL)
#define GICS_BASE            (GIC_BASE + 0x90000UL)

typedef struct {
   volatile uint32_t                         LOWER;
   volatile uint32_t                         UPPER;
} gic500_gicdRegs_irouter;

typedef struct {
   volatile uint32_t                         CTLR;
   volatile uint32_t                         TYPER;
   volatile uint32_t                         IIDR;
   volatile uint8_t                          Rsvd0[4];
   volatile uint32_t                         STATUSR;
   volatile uint8_t                          Rsvd1[44];
   volatile uint32_t                         SETSPI_NSR;
   volatile uint8_t                          Rsvd2[4];
   volatile uint32_t                         CLRSPI_NSR;
   volatile uint8_t                          Rsvd3[4];
   volatile uint32_t                         SETSPI_SR;
   volatile uint8_t                          Rsvd4[4];
   volatile uint32_t                         CLRSPI_SR;
   volatile uint8_t                          Rsvd5[36];
   volatile uint32_t                         IGROUPR_SGI_PPI;
   volatile uint32_t                         IGROUPR_SPI[30];
   volatile uint8_t                          Rsvd6[4];
   volatile uint32_t                         ISENABLER_SGI_PPI;
   volatile uint32_t                         ISENABLER_SPI[30];
   volatile uint8_t                          Rsvd7[4];
   volatile uint32_t                         ICENABLER_SGI_PPI;
   volatile uint32_t                         ICENABLER_SPI[30];
   volatile uint8_t                          Rsvd8[4];
   volatile uint32_t                         ISPENDR_SGI_PPI;
   volatile uint32_t                         ISPENDR_SPI[30];
   volatile uint8_t                          Rsvd9[4];
   volatile uint32_t                         ICPENDR_SGI_PPI;
   volatile uint32_t                         ICPENDR_SPI[30];
   volatile uint8_t                          Rsvd10[4];
   volatile uint32_t                         ISACTIVER_SGI_PPI;
   volatile uint32_t                         ISACTIVER_SPI[30];
   volatile uint8_t                          Rsvd11[4];
   volatile uint32_t                         ICACTIVER_SGI_PPI;
   volatile uint32_t                         ICACTIVER_SPI[30];
   volatile uint8_t                          Rsvd12[4];
   volatile uint32_t                         IPRIORITYR_SGI_PPI[8];
   volatile uint32_t                         IPRIORITYR_SPI[240];
   volatile uint8_t                          Rsvd13[32];
   volatile uint32_t                         ITARGETSR_SGI_PPI[8];
   volatile uint32_t                         ITARGETSR_SPI[240];
   volatile uint8_t                          Rsvd14[32];
   volatile uint32_t                         ICFGR_SGI_PPI[2];
   volatile uint32_t                         ICFGR_SPI[60];
   volatile uint8_t                          Rsvd15[8];
   volatile uint32_t                         IGRPMODR_SGI_PPI;
   volatile uint32_t                         IGRPMODR_SPI[30];
   volatile uint8_t                          Rsvd16[132];
   volatile uint32_t                         NSACR[62];
   volatile uint8_t                          Rsvd17[8];
   volatile uint32_t                         SGIR;
   volatile uint8_t                          Rsvd18[12];
   volatile uint32_t                         CPENDSGIR[4];
   volatile uint32_t                         SPENDSGIR[4];
   volatile uint8_t                          Rsvd19[20944];
   gic500_gicdRegs_irouter                   IROUTER[960];
   volatile uint8_t                          Rsvd20[16640];
   volatile uint32_t                         ESTATUSR;
   volatile uint32_t                         ERRTESTR;
   volatile uint8_t                          Rsvd21[124];
   volatile uint32_t                         SPISR[30];
   volatile uint8_t                          Rsvd22[16084];
   volatile uint32_t                         PIDR4;
   volatile uint32_t                         PIDR5;
   volatile uint32_t                         PIDR6;
   volatile uint32_t                         PIDR7;
   volatile uint32_t                         PIDR0;
   volatile uint32_t                         PIDR1;
   volatile uint32_t                         PIDR2;
   volatile uint32_t                         PIDR3;
   volatile uint32_t                         CIDR0;
   volatile uint32_t                         CIDR1;
   volatile uint32_t                         CIDR2;
   volatile uint32_t                         CIDR3;
} gic500_gicdRegs;

typedef struct {
   volatile uint8_t                          Rsvd0[64];
   volatile uint32_t                         SETSPI_NSR;
   volatile uint8_t                          Rsvd1[4];
   volatile uint32_t                         CLRSPI_NSR;
   volatile uint8_t                          Rsvd2[4];
   volatile uint32_t                         SETSPI_SR;
   volatile uint8_t                          Rsvd3[4];
   volatile uint32_t                         CLRSPI_SR;
} gic500_msgRegs;


typedef struct {
   volatile uint32_t                         CTLR;
   volatile uint32_t                         IIDR;
   volatile uint32_t                         TYPER_LOWER;
   volatile uint32_t                         TYPER_UPPER;
   volatile uint8_t                          Rsvd0[112];
   volatile uint32_t                         CBASER_LOWER;
   volatile uint32_t                         CBASER_UPPER;
   volatile uint32_t                         CWRITER_LOWER;
   volatile uint32_t                         CWRITER_UPPER;
   volatile uint32_t                         CREADR_LOWER;
   volatile uint32_t                         CREADR_UPPER;
   volatile uint8_t                          Rsvd1[104];
   volatile uint32_t                         BASER0_LOWER;
   volatile uint32_t                         BASER0_UPPER;
   volatile uint8_t                          Rsvd2[48888];
   volatile uint32_t                         TRKCTLR;
   volatile uint32_t                         TRKR;
   volatile uint32_t                         TRKDIDR;
   volatile uint32_t                         TRKPIDR;
   volatile uint32_t                         TRKVIDR;
   volatile uint32_t                         TRKTGTR;
   volatile uint32_t                         TRKICR;
   volatile uint32_t                         TRKLCR;
   volatile uint8_t                          Rsvd3[16304];
   volatile uint32_t                         PIDR4;
   volatile uint32_t                         PIDR5;
   volatile uint32_t                         PIDR6;
   volatile uint32_t                         PIDR7;
   volatile uint32_t                         PIDR0;
   volatile uint32_t                         PIDR1;
   volatile uint32_t                         PIDR2;
   volatile uint32_t                         PIDR3;
   volatile uint32_t                         CIDR0;
   volatile uint32_t                         CIDR1;
   volatile uint32_t                         CIDR2;
   volatile uint32_t                         CIDR3;
} gic500_itsRegs;


typedef struct {
   volatile uint32_t                         CTLR;
   volatile uint32_t                         IIDR;
   volatile uint32_t                         TYPER_LOWER;
   volatile uint32_t                         TYPER_UPPER;
   volatile uint32_t                         STATUSR;
   volatile uint32_t                         WAKER;
   volatile uint8_t                          Rsvd0[40];
   volatile uint32_t                         SETLPIR_LOWER;
   volatile uint32_t                         SETLPIR_UPPER;
   volatile uint32_t                         CLRLPIR_LOWER;
   volatile uint32_t                         CLRLPIR_UPPER;
   volatile uint8_t                          Rsvd1[32];
   volatile uint32_t                         PROPBASER_LOWER;
   volatile uint32_t                         PROPBASER_UPPER;
   volatile uint32_t                         PENDBASER_LOWER;
   volatile uint32_t                         PENDBASER_UPPER;
   volatile uint8_t                          Rsvd2[32];
   volatile uint32_t                         INVLPIR_LOWER;
   volatile uint32_t                         INVLPIR_UPPER;
   volatile uint8_t                          Rsvd3[8];
   volatile uint32_t                         INVALLR_LOWER;
   volatile uint32_t                         INVALLR_UPPER;
   volatile uint8_t                          Rsvd4[8];
   volatile uint32_t                         SYNCR;
   volatile uint8_t                          Rsvd5[65292];
   volatile uint32_t                         PIDR4;
   volatile uint32_t                         PIDR5;
   volatile uint32_t                         PIDR6;
   volatile uint32_t                         PIDR7;
   volatile uint32_t                         PIDR0;
   volatile uint32_t                         PIDR1;
   volatile uint32_t                         PIDR2;
   volatile uint32_t                         PIDR3;
   volatile uint32_t                         CIDR0;
   volatile uint32_t                         CIDR1;
   volatile uint32_t                         CIDR2;
   volatile uint32_t                         CIDR3;
} gic500_gicrRegs_core_control;

typedef struct {
   volatile uint8_t                          Rsvd0[128];
   volatile uint32_t                         IGROUPR_SGI_PPI;
   volatile uint8_t                          Rsvd1[124];
   volatile uint32_t                         ISENABLER0;
   volatile uint8_t                          Rsvd2[124];
   volatile uint32_t                         ICENABLER0;
   volatile uint8_t                          Rsvd3[124];
   volatile uint32_t                         ISPENDR0;
   volatile uint8_t                          Rsvd4[124];
   volatile uint32_t                         ICPENDR0;
   volatile uint8_t                          Rsvd5[124];
   volatile uint32_t                         ISACTIVER0;
   volatile uint8_t                          Rsvd6[124];
   volatile uint32_t                         ICACTIVER0;
   volatile uint8_t                          Rsvd7[124];
   volatile uint32_t                         IPRIORITYR[8];
   volatile uint8_t                          Rsvd8[2016];
   volatile uint32_t                         ICFGR0;
   volatile uint32_t                         ICFGR1;
   volatile uint8_t                          Rsvd9[248];
   volatile uint32_t                         IGRPMODR_SGI_PPI;
   volatile uint8_t                          Rsvd10[252];
   volatile uint32_t                         NSACR;
   volatile uint8_t                          Rsvd11[45564];
   volatile uint32_t                         MISCSTATUSR;
   volatile uint8_t                          Rsvd12[124];
   volatile uint32_t                         PPISR;
   volatile uint8_t                          Rsvd13[16252];
} gic500_gicrRegs_core_sgi_ppi;

typedef struct {
   gic500_gicrRegs_core_control          CONTROL;
   gic500_gicrRegs_core_sgi_ppi          SGI_PPI;
} gic500_gicrRegs_core;

typedef struct {
   gic500_gicrRegs_core                  CORE[4];
} gic500_gicrRegs;

typedef struct {
   gic500_gicdRegs                       GICD;
   gic500_msgRegs                        MSG;
   gic500_itsRegs                        ITS;
   volatile uint8_t                      Rsvd0[327680];
   gic500_gicrRegs                       GICR;
} gic500_region0Regs;


typedef struct {
   volatile uint8_t                          Rsvd0[64];
   volatile uint32_t                         TRANSLATER[1048576];
} gic500_translaterRegs;


#endif /* __GIC_500_H__ */
