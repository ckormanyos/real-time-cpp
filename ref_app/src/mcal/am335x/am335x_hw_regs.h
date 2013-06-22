
#ifndef _AM335X_HW_REGS_2013_06_22_H_
  #define _AM335X_HW_REGS_2013_06_22_H_

  #include <stdint.h>

  #ifdef __cplusplus
    #define   __I     volatile         // defines 'read only' permissions
  #else
    #define   __I     volatile const   // defines 'read only' permissions
  #endif
  #define     __O     volatile         // defines 'write only' permissions
  #define     __IO    volatile         // defines 'read / write' permissions

  typedef struct
  {
    __IO uint32_t TIDR;              // 0x000
    uint32_t  RESERVED0[3];          // 0x004
    __IO uint32_t TIOCP_CFG;         // 0x010
    uint32_t  RESERVED1[3];          // 0x014
    __IO uint32_t IRQ_EOI;           // 0x020
    __IO uint32_t IRQSTATUS_RAW;
    __IO uint32_t IRQSTATUS;
    __IO uint32_t IRQENABLE_SET;
    __IO uint32_t IRQENABLE_CLR;
    __IO uint32_t IRQWAKEEN;
    __IO uint32_t TCLR;
    __IO uint32_t TCRR;
    __IO uint32_t TLDR;
    __IO uint32_t TTGR;
    __IO uint32_t TWPS;
    __IO uint32_t TMAR;
    __IO uint32_t TCAR1;
    __IO uint32_t TSICR;
    __IO uint32_t TCAR2;
  } DMTIMER_TypeDef;

  /**
    * @brief DMTimer
    */
  typedef struct
  {
    __IO uint32_t TIDR;            // 0x000
    uint32_t  RESERVED0[3];        // 0x004
    __IO uint32_t TIOCP_CFG;       // 0x010
    __IO uint32_t TISTAT;
    __IO uint32_t TISR;
    __IO uint32_t TIER;
    __IO uint32_t TWER;
    __IO uint32_t TCLR;
    __IO uint32_t TCRR;
    __IO uint32_t TLDR;
    __IO uint32_t TTGR;
    __IO uint32_t TWPS;
    __IO uint32_t TMAR;
    __IO uint32_t TCAR1;
    __IO uint32_t TSICR;
    __IO uint32_t TCAR2;
    __IO uint32_t TPIR;
    __IO uint32_t TNIR;
    __IO uint32_t TCVR;
    __IO uint32_t TOCR;
    __IO uint32_t TOWR;
  } DMTIMER_1MS_TypeDef;

  /**
    * @brief UART
    */
  typedef struct
  {
    __IO uint32_t RHR_THR_DLL;       // 0x000
    __IO uint32_t IER_DLH;
    __IO uint32_t IIR_FCR_EFR;
    __IO uint32_t LCR;
    __IO uint32_t MCR_XON1ADDR;      // 0x010
    __IO uint32_t LSR_XON2ADDR;
    __IO uint32_t MSR_TCT_XOFF1TCR;
    __IO uint32_t SPR_TLR_XOFF2TLR;
    __IO uint32_t MDR1;              // 0x020
    __IO uint32_t MDR2;
    __IO uint32_t SFLSR_TXFLL;
    __IO uint32_t RESUME_TXFLH;
    __IO uint32_t SFREGL_RXFLL;      // 0x030
    __IO uint32_t SFREGH_TXFLH;
    __IO uint32_t BKR_UASR;
    __IO uint32_t ACREG;
    __IO uint32_t SCR;               // 0x040
    __IO uint32_t SSR;
    __IO uint32_t EBLR;
    uint32_t  RESERVED0[1];          // 0x04c
    __IO uint32_t MVR;               // 0x050
    __IO uint32_t SYSC;
    __IO uint32_t SYSS;
    __IO uint32_t WER;
    __IO uint32_t CFPS;              // 0x060
    __IO uint32_t RXFIFO_LVL;
    __IO uint32_t TXFIFO_LVL;
    __IO uint32_t IER2;
    __IO uint32_t ISR2;              // 0x070
    __IO uint32_t FREQ_SEL;
    uint32_t  RESERVED1[2];          // 0x078
    __IO uint32_t MDR3;              // 0x080
    __IO uint32_t TXDMA;
  } UART_TypeDef;

  /**
    * @brief WDT
    */
  typedef struct
  {
    __IO uint32_t WIDR;              // 0x000
    uint32_t  RESERVED0[3];          // 0x004
    __IO uint32_t WDSC;              // 0x010
    __IO uint32_t WDST;
    __IO uint32_t WISR;
    __IO uint32_t WIER;
    uint32_t  RESERVED1[1];          // 0x020
    __IO uint32_t WCLR;              // 0x024
    __IO uint32_t WCRR;
    __IO uint32_t WLDR;
    __IO uint32_t WTGR;
    __IO uint32_t WWPS;
    uint32_t  RESERVED2[3];          // 0x038
    __IO uint32_t WDLY;              // 0x044
    __IO uint32_t WSPR;
    uint32_t  RESERVED3[2];          // 0x04c
    __IO uint32_t WIRQSTATRAW;       // 0x054
    __IO uint32_t WIRQSTAT;
    __IO uint32_t WIRQENSET;
    __IO uint32_t WIRQENCLR;
  } WDT_TypeDef;

  /**
    * @brief General Purpose I/O
    */

  typedef struct
  {
    __IO uint32_t REVISION;          // 0x000
    uint32_t  RESERVED0[3];          // 0x004
    __IO uint32_t SYSCONFIG;         // 0x010
    uint32_t  RESERVED1[3];          // 0x014
    __IO uint32_t EOI;               // 0x020
    __IO uint32_t IRQSTATUS_RAW_0;
    __IO uint32_t IRQSTATUS_RAW_1;
    __IO uint32_t IRQSTATUS_0;
    __IO uint32_t IRQSTATUS_1;       // 0x030
    __IO uint32_t IRQSTATUS_SET_0;
    __IO uint32_t IRQSTATUS_SET_1;
    __IO uint32_t IRQSTATUS_CLR_0;
    __IO uint32_t IRQSTATUS_CLR_1;
    uint32_t  RESERVED2[0x34];       // 0x044
    __IO uint32_t SYSSTATUS;         // 0x114
    uint32_t  RESERVED3[6];          // 0x118
    __IO uint32_t CTRL;              // 0x130
    __IO uint32_t OE;
    __IO uint32_t DATAIN;
    __IO uint32_t DATAOUT;
    __IO uint32_t LEVELDETECT0;      // 0x140
    __IO uint32_t LEVELDETECT1;
    __IO uint32_t RISINGDETECT;
    __IO uint32_t FALLINGDETECT;
    __IO uint32_t DEBOUNCENABLE;     // 0x150
    __IO uint32_t DEBOUNCINGTIME;
    uint32_t  RESERVED4[0xe];        // 0x158
    __IO uint32_t CLEARDATAOUT;      // 0x190
    __IO uint32_t SETDATAOUT;
  } GPIO_TypeDef;

  /**
    * @brief Interrupt Registers
    */
  typedef struct
  {
    __IO  uint32_t ITR;              // 0x080
    __IO  uint32_t MIR;
    __IO  uint32_t MIR_CLEAR;
    __IO  uint32_t MIR_SET;
    __IO  uint32_t ISR_SET;          // 0x090
    __IO  uint32_t ISR_CLEAR;
    __IO  uint32_t PENDING_IRQ;
    __IO  uint32_t PENDING_FIQ;
  } _sub_INTC_TypeDef;

  typedef struct
  {
    __IO  uint32_t REVISION;         // 0x000
    uint32_t  RESERVED0[3];
    __IO  uint32_t SYSCONFIG;        // 0x010
    __IO  uint32_t SYSSTATUS;
    uint32_t  RESERVED1[10];         // 0x018
    __IO  uint32_t SIR_IRQ;          // 0x040
    __IO  uint32_t SIR_FIQ;
    __IO  uint32_t CONTROL;
    __IO  uint32_t PROTECTION;
    __IO  uint32_t IDLE;             // 0x050
    uint32_t  RESERVED2[3];
    __IO  uint32_t IRQ_PRIORITY;     // 0x060
    __IO  uint32_t FIQ_PRIORITY;
    __IO  uint32_t THRESHOLD;
    uint32_t  RESERVED3[5];
    _sub_INTC_TypeDef REG[4];
  /*
    __IO  uint32_t ITR0;             // 0x080
    __IO  uint32_t MIR0;
    __IO  uint32_t MIR_CLEAR0;
    __IO  uint32_t MIR_SET0;
    __IO  uint32_t ISR_SET0;         // 0x090
    __IO  uint32_t ISR_CLEAR0;
    __IO  uint32_t PENDING_IRQ0;
    __IO  uint32_t PENDING_FIQ0;
    __IO  uint32_t ITR1;             // 0x0a0
    __IO  uint32_t MIR1;
    __IO  uint32_t MIR_CLEAR1;
    __IO  uint32_t MIR_SET1;
    __IO  uint32_t ISR_SET1;         // 0x0b0
    __IO  uint32_t ISR_CLEAR1;
    __IO  uint32_t PENDING_IRQ1;
    __IO  uint32_t PENDING_FIQ1;
    __IO  uint32_t ITR2;             // 0x0c0
    __IO  uint32_t MIR2;
    __IO  uint32_t MIR_CLEAR2;
    __IO  uint32_t MIR_SET2;
    __IO  uint32_t ISR_SET2;         // 0x0d0
    __IO  uint32_t ISR_CLEAR2;
    __IO  uint32_t PENDING_IRQ2;
    __IO  uint32_t PENDING_FIQ2;
    __IO  uint32_t ITR3;             // 0x0e0
    __IO  uint32_t MIR3;
    __IO  uint32_t MIR_CLEAR3;
    __IO  uint32_t MIR_SET3;
    __IO  uint32_t ISR_SET3;         // 0x0f0
    __IO  uint32_t ISR_CLEAR3;
    __IO  uint32_t PENDING_IRQ3;
    __IO  uint32_t PENDING_FIQ3;
  */
    __IO  uint32_t ILR[128];         // 0x100
  } INTC_TypeDef;

  /**
    * @brief CM Wakeup Module Registers
    */
  typedef struct
  {
    __IO  uint32_t CLKSTCTRL;                 // 0x000
    __IO  uint32_t CONTROL_CLKCTRL;
    __IO  uint32_t GPIO0_CLKCTRL;
    __IO  uint32_t L4WKUP_CLKCTRL;
    __IO  uint32_t TIMER0_CLKCTRL;            // 0x010
    __IO  uint32_t DEBUGSS_CLKCTRL;
    __IO  uint32_t L3_AON_CLKSTCTRL;
    __IO  uint32_t AUTOIDLE_DPLL_MPU;
    __IO  uint32_t IDLEST_DPLL_MPU;           // 0x020
    __IO  uint32_t SSC_DELTAMSTEP_DPLL_MPU;
    __IO  uint32_t SSC_MODFREQDIV_DPLL_MPU;
    __IO  uint32_t CLKSEL_DPLL_MPU;
    __IO  uint32_t AUTOIDLE_DPLL_DDR;         // 0x030
    __IO  uint32_t IDLEST_DPLL_DDR;
    __IO  uint32_t SSC_DELTAMSTEP_DPLL_DDR;
    __IO  uint32_t SSC_MODFREQDIV_DPLL_DDR;
    __IO  uint32_t CLKSEL_DPLL_DDR;           // 0x040
    __IO  uint32_t AUTOIDLE_DPLL_DISP;
    __IO  uint32_t IDLEST_DPLL_DISP;
    __IO  uint32_t SSC_DELTAMSTEP_DPLL_DISP;
    __IO  uint32_t SSC_MODFREQDIV_DPLL_DISP;  // 0x050
    __IO  uint32_t CLKSEL_DPLL_DISP;
    __IO  uint32_t AUTOIDLE_DPLL_CORE;
    __IO  uint32_t IDLEST_DPLL_CORE;
    __IO  uint32_t SSC_DELTAMSTEP_DPLL_CORE;  // 0x060
    __IO  uint32_t SSC_MODFREQDIV_DPLL_CORE;
    __IO  uint32_t CLKSEL_DPLL_CORE;
    __IO  uint32_t AUTOIDLE_DPLL_PER;
    __IO  uint32_t IDLEST_DPLL_PER;           // 0x070
    __IO  uint32_t SSC_DELTAMSTEP_DPLL_PER;
    __IO  uint32_t SSC_MODFREQDIV_DPLL_PER;
    __IO  uint32_t CLKDCOLDO_DPLL_PER;
    __IO  uint32_t DIV_M4_DPLL_CORE;          // 0x080
    __IO  uint32_t DIV_M5_DPLL_CORE;
    __IO  uint32_t CLKMODE_DPLL_MPU;
    __IO  uint32_t CLKMODE_DPLL_PER;
    __IO  uint32_t CLKMODE_DPLL_CORE;         // 0x090
    __IO  uint32_t CLKMODE_DPLL_DDR;
    __IO  uint32_t CLKMODE_DPLL_DISP;
    __IO  uint32_t CLKSEL_DPLL_PERIPH;
    __IO  uint32_t DIV_M2_DPLL_DDR;           // 0x0a0
    __IO  uint32_t DIV_M2_DPLL_DISP;
    __IO  uint32_t DIV_M2_DPLL_MPU;
    __IO  uint32_t DIV_M2_DPLL_PER;
    __IO  uint32_t WKUP_M3_CLKCTRL;           // 0x0b0
    __IO  uint32_t UART0_CLKCTRL;
    __IO  uint32_t I2C0_CLKCTRL;
    __IO  uint32_t ADC_TSC_CLKCTRL;
    __IO  uint32_t SMARTREFLEX0_CLKCTRL;      // 0x0c0
    __IO  uint32_t TIMER1_CLKCTRL;
    __IO  uint32_t SMARTREFLEX1_CLKCTRL;
    __IO  uint32_t L4_WKUP_AON_CLKSTCTRL;
    uint32_t  RESERVED0[1];                   // 0x0d0
    __IO  uint32_t WDT1_CLKCTRL;              // 0x0d4
    __IO  uint32_t DIV_M6_DPLL_CORE;
  } CM_WKUP_TypeDef;

  /**
    * @brief  CM_DPLL Registers
    */
  typedef struct
  {
    uint32_t  RESERVED0[1];
    __IO  uint32_t CLKSEL_TIMER7_CLK;         // 0x004
    __IO  uint32_t CLKSEL_TIMER2_CLK;
    __IO  uint32_t CLKSEL_TIMER3_CLK;
    __IO  uint32_t CLKSEL_TIMER4_CLK;
    __IO  uint32_t CM_MAC_CLKSEL;             // 0x014
    __IO  uint32_t CLKSEL_TIMER5_CLK;
    __IO  uint32_t CLKSEL_TIMER6_CLK;
    __IO  uint32_t CM_CPTS_RFT_CLKSEL;
    uint32_t  RESERVED1[1];                   // 0x024
    __IO  uint32_t CLKSEL_TIMER1MS_CLK;
    __IO  uint32_t CLKSEL_GFX_FCLK;
    __IO  uint32_t CLKSEL_PRUSS_OCP_CLK;
    __IO  uint32_t CLKSEL_LCDC_PIXEL_CLK;     // 0x034
    __IO  uint32_t CLKSEL_WDT1_CLK;
    __IO  uint32_t CLKSEL_GPIO0_DBCLK;
  } CM_DPLL_TypeDef;

  /**
    * @brief Clock Module Registers
    */
  typedef struct
  {
    __IO  uint32_t L4LS_CLKSTCTRL;       // 0x000
    __IO  uint32_t L3S_CLKSTCTRL;
    uint32_t  RESERVED0[1];              // 0x008
    __IO  uint32_t L3_CLKSTCTRL;         // 0x00c
    uint32_t  RESERVED1[1];              // 0x010
    __IO  uint32_t CPGMAC0_CLKCTRL;      // 0x014
    __IO  uint32_t LCDC_CLKCTRL;
    __IO  uint32_t USB0_CLKCTRL;
    uint32_t  RESERVED2[1];              // 0x020
    __IO  uint32_t TPTC0_CLKCTRL;        // 0x024
    __IO  uint32_t EMIF_CLKCTRL;
    __IO  uint32_t OCMCRAM_CLKCTRL;
    __IO  uint32_t GPMC_CLKCTRL;         // 0x030
    __IO  uint32_t MCASP0_CLKCTRL;
    __IO  uint32_t UART5_CLKCTRL;
    __IO  uint32_t MMC0_CLKCTRL;
    __IO  uint32_t ELM_CLKCTRL;          // 0x040
    __IO  uint32_t I2C2_CLKCTRL;
    __IO  uint32_t I2C1_CLKCTRL;
    __IO  uint32_t SPI0_CLKCTRL;
    __IO  uint32_t SPI1_CLKCTRL;         // 0x050
    uint32_t  RESERVED3[3];              // 0x054
    __IO  uint32_t L4LS_CLKCTRL;         // 0x060
    __IO  uint32_t L4FW_CLKCTRL;
    __IO  uint32_t MCASP1_CLKCTRL;
    __IO  uint32_t UART1_CLKCTRL;
    __IO  uint32_t UART2_CLKCTRL;        // 0x070
    __IO  uint32_t UART3_CLKCTRL;
    __IO  uint32_t UART4_CLKCTRL;
    __IO  uint32_t TIMER7_CLKCTRL;
    __IO  uint32_t TIMER2_CLKCTRL;       // 0x080
    __IO  uint32_t TIMER3_CLKCTRL;
    __IO  uint32_t TIMER4_CLKCTRL;
    uint32_t  RESERVED4[8];              // 0x08c
    __IO  uint32_t GPIO1_CLKCTRL;        // 0x0ac
    __IO  uint32_t GPIO2_CLKCTRL;
    __IO  uint32_t GPIO3_CLKCTRL;
    uint32_t  RESERVED5[1];              // 0x0b8
    __IO  uint32_t TPCC_CLKCTRL;         // 0x0bc
    __IO  uint32_t DCAN0_CLKCTRL;
    __IO  uint32_t DCAN1_CLKCTRL;
    uint32_t  RESERVED6[1];              // 0x0c8
    __IO  uint32_t EPWMSS1_CLKCTRL;      // 0x0cc
    uint32_t  RESERVED7[1];              // 0x0d0
    __IO  uint32_t EPWMSS0_CLKCTRL;      // 0x0d4
    __IO  uint32_t EPWMSS2_CLKCTRL;
    __IO  uint32_t L3_INSTR_CLKCTRL;
    __IO  uint32_t L3_CLKCTRL;           // 0x0e0
    __IO  uint32_t IEEE5000_CLKCTRL;
    __IO  uint32_t PRUSS_CLKCTRL;
    __IO  uint32_t TIMER5_CLKCTRL;
    __IO  uint32_t TIMER6_CLKCTRL;       // 0x0f0
    __IO  uint32_t MMC1_CLKCTRL;
    __IO  uint32_t MMC2_CLKCTRL;
    __IO  uint32_t TPTC1_CLKCTRL;
    __IO  uint32_t TPTC2_CLKCTRL;        // 0x100
    uint32_t  RESERVED8[2];              // 0x104
    __IO  uint32_t SPINLOCK_CLKCTRL;     // 0x10c
    __IO  uint32_t MAILBOX0_CLKCTRL;
    uint32_t  RESERVED9[2];              // 0x114
    __IO  uint32_t L4HS_CLKSTCTRL;       // 0x11c
    __IO  uint32_t L4HS_CLKCTRL;
    uint32_t  RESERVED10[2];             // 0x124
    __IO  uint32_t OCPWP_L3_CLKSTCTRL;   // 0x12c
    __IO  uint32_t OCPWP_CLKCTRL;
    uint32_t  RESERVED11[3];             // 0x134
    __IO  uint32_t PRUSS_CLKSTCTRL;      // 0x140
    __IO  uint32_t CPSW_CLKSTCTRL;
    __IO  uint32_t LCDC_CLKSTCTRL;
    __IO  uint32_t CLKDIV32K_CLKCTRL;
    __IO  uint32_t CLK_24MHZ_CLKSTCTRL;  // 0x150
  } CM_PER_TypeDef;

  /**
    * @brief DDR2/3/mDDR PHY Registers
    */
  typedef struct
  {
    __IO  uint32_t CMD0_REG_PHY_CTRL_SLAVE_RATIO_0;     // 0x000
    __IO  uint32_t CMD0_REG_PHY_DLL_LOCK_DIFF_0;
    uint32_t  RESERVED0[1];                             // 0x008
    __IO  uint32_t CMD0_REG_PHY_INVERT_CLKOUT_0;        // 0x00c
    uint32_t  RESERVED1[1];                             // 0x010
    __IO  uint32_t CMD1_REG_PHY_CTRL_SLAVE_RATIO_0;     // 0x014
    __IO  uint32_t CMD1_REG_PHY_DLL_LOCK_DIFF_0;
    __IO  uint32_t CMD1_REG_PHY_INVERT_CLKOUT_0;
    uint32_t  RESERVED2[1];                             // 0x020
    __IO  uint32_t CMD2_REG_PHY_CTRL_SLAVE_RATIO_0;     // 0x024
    __IO  uint32_t CMD2_REG_PHY_DLL_LOCK_DIFF_0;
    __IO  uint32_t CMD2_REG_PHY_INVERT_CLKOUT_0;
    __IO  uint32_t DATA0_REG_PHY_RD_DQS_SLAVE_RATIO_0;  // 0x030
    __IO  uint32_t DATA0_REG_PHY_WR_DQS_SLAVE_RATIO_0;
    __IO  uint32_t DATA0_REG_PHY_WRLVL_INIT_RATIO_0;
    __IO  uint32_t DATA0_REG_PHY_WRLVL_INIT_MODE_0;
    __IO  uint32_t DATA0_REG_PHY_GATELVL_INIT_RATIO_0;  // 0x040
    __IO  uint32_t DATA0_REG_PHY_GATELVL_INIT_MODE_0;
    __IO  uint32_t DATA0_REG_PHY_FIFO_WE_SLAVE_RATIO_0;
    __IO  uint32_t DATA0_REG_PHY_DQ_OFFSET_0;
    __IO  uint32_t DATA0_REG_PHY_WR_DATA_SLAVE_RATIO_0; // 0x050
    uint32_t  RESERVED3[3];                             // 0x054
    __IO  uint32_t DATA0_REG_PHY_USE_RANK0_DELAYS;      // 0x060
    __IO  uint32_t DATA0_REG_PHY_DLL_LOCK_DIFF_0;
    __IO  uint32_t DATA1_REG_PHY_RD_DQS_SLAVE_RATIO_0;
    __IO  uint32_t DATA1_REG_PHY_WR_DQS_SLAVE_RATIO_0;
    __IO  uint32_t DATA1_REG_PHY_WRLVL_INIT_RATIO_0;    // 0x070
    __IO  uint32_t DATA1_REG_PHY_WRLVL_INIT_MODE_0;
    __IO  uint32_t DATA1_REG_PHY_GATELVL_INIT_RATIO_0;
    __IO  uint32_t DATA1_REG_PHY_GATELVL_INIT_MODE_0;
    __IO  uint32_t DATA1_REG_PHY_FIFO_WE_SLAVE_RATIO_0; // 0x080
    __IO  uint32_t DATA1_REG_PHY_DQ_OFFSET_1;
    __IO  uint32_t DATA1_REG_PHY_WR_DATA_SLAVE_RATIO_0;
    uint32_t  RESERVED4[8];                             // 0x08c
    __IO  uint32_t DATA1_REG_PHY_USE_RANK0_DELAYS;      // 0x0ac
    __IO  uint32_t DATA1_REG_PHY_DLL_LOCK_DIFF_0;

    uint32_t  RESERVED5[1];              // 0x0b8
    uint32_t  RESERVED6[1];              // 0x0c8
    uint32_t  RESERVED7[1];              // 0x0d0
    uint32_t  RESERVED8[2];              // 0x104
    uint32_t  RESERVED9[2];              // 0x114
    uint32_t  RESERVED10[2];             // 0x124
    uint32_t  RESERVED11[3];             // 0x134
  } DDR_PHY_TypeDef;

  /**
    * @brief Control Module
    */

  typedef struct
  {
    __IO  uint32_t CONTROL_REVISION;     // 0x000
    __IO  uint32_t CONTROL_HWINFO;
    uint32_t  RESERVED0[2];              // 0x008
    __IO  uint32_t CONTROL_SYSCONFIG;    // 0x010
    uint32_t  RESERVED1[0xb];            // 0x014
    __IO  uint32_t CONTROL_STATUS;       // 0x040
    uint32_t  RESERVED2[0xf6];           // 0x044
    __IO  uint32_t CORTEX_VBBLDO_CTRL;   // 0x41c
    uint32_t  RESERVED3[2];              // 0x420
    __IO  uint32_t CORE_SLDO_CTRL;       // 0x428
    __IO  uint32_t MPU_SLDO_CTRL;
    uint32_t  RESERVED4[5];              // 0x430
    __IO  uint32_t CLK32KDIVRATIO_CTRL;  // 0x444
    __IO  uint32_t BANDGAP_CTRL;
    __IO  uint32_t BANDGAP_TRIM;
    uint32_t  RESERVED5[2];              // 0x450
    __IO  uint32_t PLL_CLKINPULOW_CTRL;  // 0x458
    uint32_t  RESERVED6[3];              // 0x45c
    __IO  uint32_t MOSC_CTRL;            // 0x468
    __IO  uint32_t RCOSC_CTRL;
    __IO  uint32_t DEEPSLEEP_CTRL;
    uint32_t  RESERVED7[0x63];           // 0x474
    __IO  uint32_t DEVICE_ID;            // 0x600
    __IO  uint32_t DEV_FEATURE;
    __IO  uint32_t INIT_PRIORITY_0;
    __IO  uint32_t INIT_PRIORITY_1;
    __IO  uint32_t MMU_CFG;
    __IO  uint32_t TPTC_CFG;
    uint32_t  RESERVED8[2];              // 0x618
    __IO  uint32_t USB_CTRL0;            // 0x620
    __IO  uint32_t USB_STS0;
    __IO  uint32_t USB_CTRL1;
    __IO  uint32_t USB_STS1;
    __IO  uint32_t MAC_ID0_LO;
    __IO  uint32_t MAC_ID0_HI;
    __IO  uint32_t MAC_ID1_LO;
    __IO  uint32_t MAC_ID1_HI;
    uint32_t  RESERVED9[1];              // 0x640
    __IO  uint32_t DCAN_RAMINIT;         // 0x644
    __IO  uint32_t USB_WKUP_CTRL;
    uint32_t  RESERVED10[1];             // 0x64c
    __IO  uint32_t GMII_SEL;             // 0x650
    uint32_t  RESERVED11[4];             // 0x654
    __IO  uint32_t PWMSS_CTRL;           // 0x664
    uint32_t  RESERVED12[2];             // 0x668
    __IO  uint32_t MREQPRIO_0;           // 0x670
    __IO  uint32_t MREQPRIO_1;
    uint32_t  RESERVED13[6];             // 0x678
    __IO  uint32_t HW_EVENT_SEL_GRP1;    // 0x690
    __IO  uint32_t HW_EVENT_SEL_GRP2;
    __IO  uint32_t HW_EVENT_SEL_GRP3;
    __IO  uint32_t HW_EVENT_SEL_GRP4;
    __IO  uint32_t SMRT_CTRL;
    __IO  uint32_t MPUSS_HW_DEBUG_SEL;
    __IO  uint32_t MPUSS_HW_DBG_INFO;
    uint32_t  RESERVED14[0x31];          // 0x6ac
    __IO  uint32_t VDD_MPU_OPP_050;      // 0x770
    __IO  uint32_t VDD_MPU_OPP_100;
    __IO  uint32_t VDD_MPU_OPP_120;
    __IO  uint32_t VDD_MPU_OPP_TURBO;
    uint32_t  RESERVED15[0xe];           // 0x780
    __IO  uint32_t VDD_CORE_OPP_050;     // 0x7b8
    __IO  uint32_t VDD_CORE_OPP_100;
    uint32_t  RESERVED16[4];             // 0x7c0
    __IO  uint32_t BB_SCALE;             // 0x7d0
    uint32_t  RESERVED17[8];             // 0x7d4
    __IO  uint32_t USB_VID_PID;          // 0x7f4
    uint32_t  RESERVED18[2];             // 0x7f8
    __IO  uint32_t CONF_GPMC_AD0;        // 0x800
    __IO  uint32_t CONF_GPMC_AD1;
    __IO  uint32_t CONF_GPMC_AD2;
    __IO  uint32_t CONF_GPMC_AD3;
    __IO  uint32_t CONF_GPMC_AD4;          // 0x810
    __IO  uint32_t CONF_GPMC_AD5;
    __IO  uint32_t CONF_GPMC_AD6;
    __IO  uint32_t CONF_GPMC_AD7;
    __IO  uint32_t CONF_GPMC_AD8;          // 0x820
    __IO  uint32_t CONF_GPMC_AD9;
    __IO  uint32_t CONF_GPMC_AD10;
    __IO  uint32_t CONF_GPMC_AD11;
    __IO  uint32_t CONF_GPMC_AD12;         // 0x830
    __IO  uint32_t CONF_GPMC_AD13;
    __IO  uint32_t CONF_GPMC_AD14;
    __IO  uint32_t CONF_GPMC_AD15;
    __IO  uint32_t CONF_GPMC_A0;           // 0x840
    __IO  uint32_t CONF_GPMC_A1;
    __IO  uint32_t CONF_GPMC_A2;
    __IO  uint32_t CONF_GPMC_A3;
    __IO  uint32_t CONF_GPMC_A4;           // 0x850
    __IO  uint32_t CONF_GPMC_A5;
    __IO  uint32_t CONF_GPMC_A6;
    __IO  uint32_t CONF_GPMC_A7;
    __IO  uint32_t CONF_GPMC_A8;           // 0x860
    __IO  uint32_t CONF_GPMC_A9;
    __IO  uint32_t CONF_GPMC_A10;
    __IO  uint32_t CONF_GPMC_A11;
    __IO  uint32_t CONF_GPMC_WAIT0;        // 0x870
    __IO  uint32_t CONF_GPMC_WPN;
    __IO  uint32_t CONF_GPMC_BE1N;
    __IO  uint32_t CONF_GPMC_CSN0;
    __IO  uint32_t CONF_GPMC_CSN1;         // 0x880
    __IO  uint32_t CONF_GPMC_CSN2;
    __IO  uint32_t CONF_GPMC_CSN3;
    __IO  uint32_t CONF_GPMC_CLK;
    __IO  uint32_t CONF_GPMC_ADVN_ALE;     // 0x890
    __IO  uint32_t CONF_GPMC_OEN_REN;
    __IO  uint32_t CONF_GPMC_WEN;
    __IO  uint32_t CONF_GPMC_BE0N_CLE;
    __IO  uint32_t CONF_LCD_DATA0;         // 0x8a0
    __IO  uint32_t CONF_LCD_DATA1;
    __IO  uint32_t CONF_LCD_DATA2;
    __IO  uint32_t CONF_LCD_DATA3;
    __IO  uint32_t CONF_LCD_DATA4;         // 0x8b0
    __IO  uint32_t CONF_LCD_DATA5;
    __IO  uint32_t CONF_LCD_DATA6;
    __IO  uint32_t CONF_LCD_DATA7;
    __IO  uint32_t CONF_LCD_DATA8;         // 0x8c0
    __IO  uint32_t CONF_LCD_DATA9;
    __IO  uint32_t CONF_LCD_DATA10;
    __IO  uint32_t CONF_LCD_DATA11;
    __IO  uint32_t CONF_LCD_DATA12;        // 0x8d0
    __IO  uint32_t CONF_LCD_DATA13;
    __IO  uint32_t CONF_LCD_DATA14;
    __IO  uint32_t CONF_LCD_DATA15;
    __IO  uint32_t CONF_LCD_VSYNC;         // 0x8e0
    __IO  uint32_t CONF_LCD_HSYNC;
    __IO  uint32_t CONF_LCD_PCLK;
    __IO  uint32_t CONF_LCD_AC_BIAS_EN;
    __IO  uint32_t CONF_MMC0_DAT3;         // 0x8f0
    __IO  uint32_t CONF_MMC0_DAT2;
    __IO  uint32_t CONF_MMC0_DAT1;
    __IO  uint32_t CONF_MMC0_DAT0;
    __IO  uint32_t CONF_MMC0_CLK;          // 0x900
    __IO  uint32_t CONF_MMC0_CMD;
    __IO  uint32_t CONF_MII1_COL;
    __IO  uint32_t CONF_MII1_CRS;
    __IO  uint32_t CONF_MII1_RXERR;        // 0x910
    __IO  uint32_t CONF_MII1_TXEN;
    __IO  uint32_t CONF_MII1_RXDV;
    __IO  uint32_t CONF_MII1_TXD3;
    __IO  uint32_t CONF_MII1_TXD2;         // 0x920
    __IO  uint32_t CONF_MII1_TXD1;
    __IO  uint32_t CONF_MII1_TXD0;
    __IO  uint32_t CONF_MII1_TXCLK;
    __IO  uint32_t CONF_MII1_RXCLK;        // 0x930
    __IO  uint32_t CONF_MII1_RXD3;
    __IO  uint32_t CONF_MII1_RXD2;
    __IO  uint32_t CONF_MII1_RXD1;
    __IO  uint32_t CONF_MII1_RXD0;         // 0x940
    __IO  uint32_t CONF_RMII1_REFCLK;
    __IO  uint32_t CONF_MDIO_DATA;
    __IO  uint32_t CONF_MDIO_CLK;
    __IO  uint32_t CONF_SPI0_SCLK;         // 0x950
    __IO  uint32_t CONF_SPI0_D0;
    __IO  uint32_t CONF_SPI0_D1;
    __IO  uint32_t CONF_SPI0_CS0;
    __IO  uint32_t CONF_SPI0_CS1;          // 0x960
    __IO  uint32_t CONF_ECAP0_IN_PWM0_OUT;
    __IO  uint32_t CONF_UART0_CTSN;
    __IO  uint32_t CONF_UART0_RTSN;
    __IO  uint32_t CONF_UART0_RXD;         // 0x970
    __IO  uint32_t CONF_UART0_TXD;
    __IO  uint32_t CONF_UART1_CTSN;
    __IO  uint32_t CONF_UART1_RTSN;
    __IO  uint32_t CONF_UART1_RXD;         // 0x980
    __IO  uint32_t CONF_UART1_TXD;
    __IO  uint32_t CONF_I2C0_SDA;
    __IO  uint32_t CONF_I2C0_SCL;
    __IO  uint32_t CONF_MCASP0_ACLKX;      // 0x990
    __IO  uint32_t CONF_MCASP0_FSX;
    __IO  uint32_t CONF_MCASP0_AXR0;
    __IO  uint32_t CONF_MCASP0_AHCLKR;
    __IO  uint32_t CONF_MCASP0_ACLKR;      // 0x9a0
    __IO  uint32_t CONF_MCASP0_FSR;
    __IO  uint32_t CONF_MCASP0_AXR1;
    __IO  uint32_t CONF_MCASP0_AHCLKX;
    __IO  uint32_t CONF_XDMA_EVENT_INTR0;  // 0x9b0
    __IO  uint32_t CONF_XDMA_EVENT_INTR1;
    __IO  uint32_t CONF_NRESETIN_OUT;
    __IO  uint32_t CONF_PORZ;
    __IO  uint32_t CONF_NNMI;              // 0x9c0
    __IO  uint32_t CONF_OSC0_IN;
    __IO  uint32_t CONF_OSC0_OUT;
    __IO  uint32_t CONF_OSC0_VSS;
    __IO  uint32_t CONF_TMS;               // 0x9d0
    __IO  uint32_t CONF_TDI;
    __IO  uint32_t CONF_TDO;
    __IO  uint32_t CONF_TCK;
    __IO  uint32_t CONF_NTRST;             // 0x9e0
    __IO  uint32_t CONF_EMU0;
    __IO  uint32_t CONF_EMU1;
    __IO  uint32_t CONF_OSC1_IN;
    __IO  uint32_t CONF_OSC1_OUT;          // 0x9f0
    __IO  uint32_t CONF_OSC1_VSS;
    __IO  uint32_t CONF_RTC_PORZ;
    __IO  uint32_t CONF_PMIC_POWER_EN;
    __IO  uint32_t CONF_EXT_WAKEUP;        // 0xa00
    __IO  uint32_t CONF_ENZ_KALDO_1P8V;
    __IO  uint32_t CONF_USB0_DM;
    __IO  uint32_t CONF_USB0_DP;
    __IO  uint32_t CONF_USB0_CE;           // 0xa10
    __IO  uint32_t CONF_USB0_ID;
    __IO  uint32_t CONF_USB0_VBUS;
    __IO  uint32_t CONF_USB0_DRVVBUS;
    __IO  uint32_t CONF_USB1_DM;           // 0xa20
    __IO  uint32_t CONF_USB1_DP;
    __IO  uint32_t CONF_USB1_CE;
    __IO  uint32_t CONF_USB1_ID;
    __IO  uint32_t CONF_USB1_VBUS;         // 0xa30
    __IO  uint32_t CONF_USB1_DRVVBUS;
    __IO  uint32_t CONF_DDR_RESETN;
    __IO  uint32_t CONF_DDR_CSN0;
    __IO  uint32_t CONF_DDR_CKE;           // 0xa40
    uint32_t  RESERVED19[1];               // 0xa44
    __IO  uint32_t CONF_DDR_NCK;           // 0xa48
    __IO  uint32_t CONF_DDR_CASN;
    __IO  uint32_t CONF_DDR_RASN;          // 0xa50
    __IO  uint32_t CONF_DDR_WEN;
    __IO  uint32_t CONF_DDR_BA0;
    __IO  uint32_t CONF_DDR_BA1;
    __IO  uint32_t CONF_DDR_BA2;           // 0xa60
    __IO  uint32_t CONF_DDR_A0;
    __IO  uint32_t CONF_DDR_A1;
    __IO  uint32_t CONF_DDR_A2;
    __IO  uint32_t CONF_DDR_A3;            // 0xa70
    __IO  uint32_t CONF_DDR_A4;
    __IO  uint32_t CONF_DDR_A5;
    __IO  uint32_t CONF_DDR_A6;
    __IO  uint32_t CONF_DDR_A7;            // 0xa80
    __IO  uint32_t CONF_DDR_A8;
    __IO  uint32_t CONF_DDR_A9;
    __IO  uint32_t CONF_DDR_A10;
    __IO  uint32_t CONF_DDR_A11;           // 0xa90
    __IO  uint32_t CONF_DDR_A12;
    __IO  uint32_t CONF_DDR_A13;
    __IO  uint32_t CONF_DDR_A14;
    __IO  uint32_t CONF_DDR_A15;           // 0xaa0
    __IO  uint32_t CONF_DDR_ODT;
    __IO  uint32_t CONF_DDR_D0;
    __IO  uint32_t CONF_DDR_D1;
    __IO  uint32_t CONF_DDR_D2;            // 0xab0
    __IO  uint32_t CONF_DDR_D3;
    __IO  uint32_t CONF_DDR_D4;
    __IO  uint32_t CONF_DDR_D5;
    __IO  uint32_t CONF_DDR_D6;            // 0xac0
    __IO  uint32_t CONF_DDR_D7;
    __IO  uint32_t CONF_DDR_D8;
    __IO  uint32_t CONF_DDR_D9;
    __IO  uint32_t CONF_DDR_D10;           // 0xad0
    __IO  uint32_t CONF_DDR_D11;
    __IO  uint32_t CONF_DDR_D12;
    __IO  uint32_t CONF_DDR_D13;
    __IO  uint32_t CONF_DDR_D14;           // 0xae0
    __IO  uint32_t CONF_DDR_D15;
    __IO  uint32_t CONF_DDR_DQM0;
    __IO  uint32_t CONF_DDR_DQM1;
    __IO  uint32_t CONF_DDR_DQS0;          // 0xaf0
    __IO  uint32_t CONF_DDR_DQSN0;
    __IO  uint32_t CONF_DDR_DQS1;
    __IO  uint32_t CONF_DDR_DQSN1;
    __IO  uint32_t CONF_DDR_VREF;          // 0xb00
    __IO  uint32_t CONF_DDR_VTP;
    __IO  uint32_t CONF_DDR_STRBEN0;
    __IO  uint32_t CONF_DDR_STRBEN1;
    __IO  uint32_t CONF_AIN7;              // 0xb10
    __IO  uint32_t CONF_AIN6;
    __IO  uint32_t CONF_AIN5;
    __IO  uint32_t CONF_AIN4;
    __IO  uint32_t CONF_AIN3;              // 0xb20
    __IO  uint32_t CONF_AIN2;
    __IO  uint32_t CONF_AIN1;
    __IO  uint32_t CONF_AIN0;
    __IO  uint32_t CONF_VREFP;             // 0xb30
    __IO  uint32_t CONF_VREFN;
    __IO  uint32_t CONF_AVDD;
    __IO  uint32_t CONF_AVSS;
    __IO  uint32_t CONF_IFORCE;            // 0xb40
    __IO  uint32_t CONF_VSENSE;
    __IO  uint32_t CONF_TESTOUT;
    uint32_t  RESERVED20[0xad];            // 0xb4c
    __IO  uint32_t CQDETECT_STATUS;        // 0xe00
    __IO  uint32_t DDR_IO_CTRL;
    uint32_t  RESERVED21[1];               // 0xe08
    __IO  uint32_t VTP_CTRL;               // 0xe0c
    uint32_t  RESERVED22[1];               // 0xe10
    __IO  uint32_t VREF_CTRL;              // 0xe14
    uint32_t  RESERVED23[0x5e];            // 0xe18
    __IO  uint32_t TPCC_EVT_MUX_0_3;       // 0xf90
    __IO  uint32_t TPCC_EVT_MUX_4_7;
    __IO  uint32_t TPCC_EVT_MUX_8_11;
    __IO  uint32_t TPCC_EVT_MUX_12_15;
    __IO  uint32_t TPCC_EVT_MUX_16_19;     // 0xfa0
    __IO  uint32_t TPCC_EVT_MUX_20_23;
    __IO  uint32_t TPCC_EVT_MUX_24_27;
    __IO  uint32_t TPCC_EVT_MUX_28_31;
    __IO  uint32_t TPCC_EVT_MUX_32_35;     // 0xfb0
    __IO  uint32_t TPCC_EVT_MUX_36_39;
    __IO  uint32_t TPCC_EVT_MUX_40_43;
    __IO  uint32_t TPCC_EVT_MUX_44_47;
    __IO  uint32_t TPCC_EVT_MUX_48_51;     // 0xfc0
    __IO  uint32_t TPCC_EVT_MUX_52_55;
    __IO  uint32_t TPCC_EVT_MUX_56_59;
    __IO  uint32_t TPCC_EVT_MUX_60_63;
    __IO  uint32_t TIMER_EVT_CAPT;         // 0xfd0
    __IO  uint32_t ECAP_EVT_CAPT;
    __IO  uint32_t ADC_EVT_CAPT;
    uint32_t  RESERVED24[9];               // 0xfdc
    __IO  uint32_t RESET_ISO;              // 0x1000
    uint32_t  RESERVED25[0xc6];            // 0x1004
    __IO  uint32_t DDR_CKE_CTRL;           // 0x131c
    __IO  uint32_t SMA2;                   // 0x1320
    __IO  uint32_t M3_TXEV_EOI;
    __IO  uint32_t IPC_MSG_REG0;
    __IO  uint32_t IPC_MSG_REG1;
    __IO  uint32_t IPC_MSG_REG2;           // 0x1330
    __IO  uint32_t IPC_MSG_REG3;
    __IO  uint32_t IPC_MSG_REG4;
    __IO  uint32_t IPC_MSG_REG5;
    __IO  uint32_t IPC_MSG_REG6;           // 0x1340
    __IO  uint32_t IPC_MSG_REG7;
    uint32_t  RESERVED26[0x2f];            // 0x1348
    __IO  uint32_t DDR_CMD0_IOCTRL;        // 0x1404
    __IO  uint32_t DDR_CMD1_IOCTRL;
    __IO  uint32_t DDR_CMD2_IOCTRL;
    uint32_t  RESERVED27[0xc];             // 0x1410
    __IO  uint32_t DDR_DATA0_IOCTRL;       // 0x1440
    __IO  uint32_t DDR_DATA1_IOCTRL;
  } CONTROL_TypeDef;

  #define L4_WKUP_BASE      ((uint32_t) 0x44C00000)  // Peripheral base address in the alias region
  #define L4_PER_BASE       ((uint32_t) 0x48000000)  // Peripheral base address in the alias region

  #define CONTROL_BASE      (L4_WKUP_BASE + 0x210000)
  #define GPIO0_BASE        (L4_WKUP_BASE + 0x207000)
  #define GPIO1_BASE        (L4_PER_BASE  + 0x04C000)
  #define GPIO2_BASE        (L4_PER_BASE  + 0x1AC000)
  #define GPIO3_BASE        (L4_PER_BASE  + 0x1AE000)
  #define DMTIMER0_BASE     (L4_WKUP_BASE + 0x205000)
  #define DMTIMER1_1MS_BASE (L4_WKUP_BASE + 0x231000)
  #define DMTIMER2_BASE     (L4_PER_BASE  + 0x040000)
  #define DMTIMER3_BASE     (L4_PER_BASE  + 0x042000)
  #define DMTIMER4_BASE     (L4_PER_BASE  + 0x044000)
  #define DMTIMER5_BASE     (L4_PER_BASE  + 0x046000)
  #define DMTIMER6_BASE     (L4_PER_BASE  + 0x048000)
  #define DMTIMER7_BASE     (L4_PER_BASE  + 0x04A000)
  #define WDT1_BASE         (L4_WKUP_BASE + 0x235000)
  #define CM_PER_BASE       (L4_WKUP_BASE + 0x200000)
  #define CM_WKUP_BASE      (L4_WKUP_BASE + 0x200400)
  #define CM_DPLL_BASE      (L4_WKUP_BASE + 0x200500)
  #define DDR_PHY_BASE      (L4_WKUP_BASE + 0x212000)
  #define INTC_BASE         (L4_PER_BASE  + 0x200000)
  #define UART0_BASE        (L4_WKUP_BASE + 0x209000)
  #define UART1_BASE        (L4_PER_BASE  + 0x022000)
  #define UART2_BASE        (L4_PER_BASE  + 0x024000)
  #define UART3_BASE        (L4_PER_BASE  + 0x1A6000)
  #define UART4_BASE        (L4_PER_BASE  + 0x1A8000)
  #define UART5_BASE        (L4_PER_BASE  + 0x1AA000)

  #define CONTROL       ((CONTROL_TypeDef*)     CONTROL_BASE)
  #define GPIO0         ((GPIO_TypeDef*)        GPIO0_BASE)
  #define GPIO1         ((GPIO_TypeDef*)        GPIO1_BASE)
  #define GPIO2         ((GPIO_TypeDef*)        GPIO2_BASE)
  #define GPIO3         ((GPIO_TypeDef*)        GPIO3_BASE)
  #define DMTIMER0      ((DMTIMER_TypeDef*)     DMTIMER0_BASE)
  #define DMTIMER1_1MS  ((DMTIMER_1MS_TypeDef*) DMTIMER1_1MS_BASE)
  #define DMTIMER2      ((DMTIMER_TypeDef*)     DMTIMER2_BASE)
  #define DMTIMER3      ((DMTIMER_TypeDef*)     DMTIMER3_BASE)
  #define DMTIMER4      ((DMTIMER_TypeDef*)     DMTIMER4_BASE)
  #define DMTIMER5      ((DMTIMER_TypeDef*)     DMTIMER5_BASE)
  #define DMTIMER6      ((DMTIMER_TypeDef*)     DMTIMER6_BASE)
  #define DMTIMER7      ((DMTIMER_TypeDef*)     DMTIMER7_BASE)
  #define WDT1          ((WDT_TypeDef*)         WDT1_BASE)
  #define CM_PER        ((CM_PER_TypeDef*)      CM_PER_BASE)
  #define CM_WKUP       ((CM_WKUP_TypeDef*)     CM_WKUP_BASE)
  #define CM_DPLL       ((CM_DPLL_TypeDef*)     CM_DPLL_BASE)
  #define DDR_PHY       ((DDR_PHY_TypeDef*)     DDR_PHY_BASE)
  #define INTC          ((INTC_TypeDef*)        INTC_BASE)
  #define UART0         ((UART_TypeDef*)        UART0_BASE)
  #define UART1         ((UART_TypeDef*)        UART1_BASE)

#endif // _AM335X_HW_REGS_2013_06_22_H_
