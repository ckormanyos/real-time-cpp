
#ifndef STM32H7X3_H
#define STM32H7X3_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
  #define   __I      volatile
#else
  #define   __I      volatile const
#endif
#define     __O      volatile
#define     __IO     volatile

#define     __IM     volatile const
#define     __OM     volatile
#define     __IOM    volatile

typedef unsigned long uint32;

/* =========================================================================================================================== */
/* ================                                            RCC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Reset and clock control (RCC)
  */

typedef struct {                                /*!< (@ 0x58024400) RCC Structure                                              */
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000000) clock control register                                     */
    
    struct {
      __IOM uint32 HSION      : 1;            /*!< [0..0] Internal high-speed clock enable                                   */
      __IOM uint32 HSIKERON   : 1;            /*!< [1..1] High Speed Internal clock enable in Stop mode                      */
      __IOM uint32 HSIRDY     : 1;            /*!< [2..2] HSI clock ready flag                                               */
      __IOM uint32 HSIDIV     : 2;            /*!< [4..3] HSI clock divider                                                  */
      __IOM uint32 HSIDIVF    : 1;            /*!< [5..5] HSI divider flag                                                   */
            uint32            : 1;
      __IOM uint32 CSION      : 1;            /*!< [7..7] CSI clock enable                                                   */
      __IOM uint32 CSIRDY     : 1;            /*!< [8..8] CSI clock ready flag                                               */
      __IOM uint32 CSIKERON   : 1;            /*!< [9..9] CSI clock enable in Stop mode                                      */
            uint32            : 2;
      __IOM uint32 RC48ON     : 1;            /*!< [12..12] RC48 clock enable                                                */
      __IOM uint32 RC48RDY    : 1;            /*!< [13..13] RC48 clock ready flag                                            */
      __IOM uint32 D1CKRDY    : 1;            /*!< [14..14] D1 domain clocks ready flag                                      */
      __IOM uint32 D2CKRDY    : 1;            /*!< [15..15] D2 domain clocks ready flag                                      */
      __IOM uint32 HSEON      : 1;            /*!< [16..16] HSE clock enable                                                 */
      __IOM uint32 HSERDY     : 1;            /*!< [17..17] HSE clock ready flag                                             */
      __IOM uint32 HSEBYP     : 1;            /*!< [18..18] HSE clock bypass                                                 */
      __IOM uint32 HSECSSON   : 1;            /*!< [19..19] HSE Clock Security System enable                                 */
            uint32            : 4;
      __IOM uint32 PLL1ON     : 1;            /*!< [24..24] PLL1 enable                                                      */
      __IOM uint32 PLL1RDY    : 1;            /*!< [25..25] PLL1 clock ready flag                                            */
      __IOM uint32 PLL2ON     : 1;            /*!< [26..26] PLL2 enable                                                      */
      __IOM uint32 PLL2RDY    : 1;            /*!< [27..27] PLL2 clock ready flag                                            */
      __IOM uint32 PLL3ON     : 1;            /*!< [28..28] PLL3 enable                                                      */
      __IOM uint32 PLL3RDY    : 1;            /*!< [29..29] PLL3 clock ready flag                                            */
            uint32            : 2;
    } bit;
  } CR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000004) RCC Internal Clock Source Calibration Register             */
    
    struct {
      __IM  uint32 HSICAL     : 12;           /*!< [11..0] HSI clock calibration                                             */
      __IOM uint32 HSITRIM    : 6;            /*!< [17..12] HSI clock trimming                                               */
      __IM  uint32 CSICAL     : 8;            /*!< [25..18] CSI clock calibration                                            */
      __IOM uint32 CSITRIM    : 5;            /*!< [30..26] CSI clock trimming                                               */
            uint32            : 1;
    } bit;
  } ICSCR;
  
  union {
    __IM  uint32 reg;                         /*!< (@ 0x00000008) RCC Clock Recovery RC Register                             */
    
    struct {
      __IM  uint32 RC48CAL    : 10;           /*!< [9..0] Internal RC 48 MHz clock calibration                               */
            uint32            : 22;
    } bit;
  } CRRCR;
  __IM  uint32  RESERVED;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000010) RCC Clock Configuration Register                           */
    
    struct {
      __IOM uint32 SW         : 3;            /*!< [2..0] System clock switch                                                */
      __IOM uint32 SWS        : 3;            /*!< [5..3] System clock switch status                                         */
      __IOM uint32 STOPWUCK   : 1;            /*!< [6..6] System clock selection after a wake up from system Stop            */
      __IOM uint32 STOPKERWUCK : 1;           /*!< [7..7] Kernel clock selection after a wake up from system Stop            */
      __IOM uint32 RTCPRE     : 6;            /*!< [13..8] HSE division factor for RTC clock                                 */
      __IOM uint32 HRTIMSEL   : 1;            /*!< [14..14] High Resolution Timer clock prescaler selection                  */
      __IOM uint32 TIMPRE     : 1;            /*!< [15..15] Timers clocks prescaler selection                                */
            uint32            : 2;
      __IOM uint32 MCO1PRE    : 4;            /*!< [21..18] MCO1 prescaler                                                   */
      __IOM uint32 MCO1SEL    : 3;            /*!< [24..22] Micro-controller clock output 1                                  */
      __IOM uint32 MCO2PRE    : 4;            /*!< [28..25] MCO2 prescaler                                                   */
      __IOM uint32 MCO2SEL    : 3;            /*!< [31..29] Micro-controller clock output 2                                  */
    } bit;
  } CFGR;
  __IM  uint32  RESERVED1;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000018) RCC Domain 1 Clock Configuration Register                  */
    
    struct {
      __IOM uint32 HPRE       : 4;            /*!< [3..0] D1 domain AHB prescaler                                            */
      __IOM uint32 D1PPRE     : 3;            /*!< [6..4] D1 domain APB3 prescaler                                           */
            uint32            : 1;
      __IOM uint32 D1CPRE     : 4;            /*!< [11..8] D1 domain Core prescaler                                          */
            uint32            : 20;
    } bit;
  } D1CFGR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000001C) RCC Domain 2 Clock Configuration Register                  */
    
    struct {
            uint32            : 4;
      __IOM uint32 D2PPRE1    : 3;            /*!< [6..4] D2 domain APB1 prescaler                                           */
            uint32            : 1;
      __IOM uint32 D2PPRE2    : 3;            /*!< [10..8] D2 domain APB2 prescaler                                          */
            uint32            : 21;
    } bit;
  } D2CFGR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000020) RCC Domain 3 Clock Configuration Register                  */
    
    struct {
            uint32            : 4;
      __IOM uint32 D3PPRE     : 3;            /*!< [6..4] D3 domain APB4 prescaler                                           */
            uint32            : 25;
    } bit;
  } D3CFGR;
  __IM  uint32  RESERVED2;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000028) RCC PLLs Clock Source Selection Register                   */
    
    struct {
      __IOM uint32 PLLSRC     : 2;            /*!< [1..0] DIVMx and PLLs clock source selection                              */
            uint32            : 2;
      __IOM uint32 DIVM1      : 6;            /*!< [9..4] Prescaler for PLL1                                                 */
            uint32            : 2;
      __IOM uint32 DIVM2      : 6;            /*!< [17..12] Prescaler for PLL2                                               */
            uint32            : 2;
      __IOM uint32 DIVM3      : 6;            /*!< [25..20] Prescaler for PLL3                                               */
            uint32            : 6;
    } bit;
  } PLLCKSELR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000002C) RCC PLLs Configuration Register                            */
    
    struct {
      __IOM uint32 PLL1FRACEN : 1;            /*!< [0..0] PLL1 fractional latch enable                                       */
      __IOM uint32 PLL1VCOSEL : 1;            /*!< [1..1] PLL1 VCO selection                                                 */
      __IOM uint32 PLL1RGE    : 2;            /*!< [3..2] PLL1 input frequency range                                         */
      __IOM uint32 PLL2FRACEN : 1;            /*!< [4..4] PLL2 fractional latch enable                                       */
      __IOM uint32 PLL2VCOSEL : 1;            /*!< [5..5] PLL2 VCO selection                                                 */
      __IOM uint32 PLL2RGE    : 2;            /*!< [7..6] PLL2 input frequency range                                         */
      __IOM uint32 PLL3FRACEN : 1;            /*!< [8..8] PLL3 fractional latch enable                                       */
      __IOM uint32 PLL3VCOSEL : 1;            /*!< [9..9] PLL3 VCO selection                                                 */
      __IOM uint32 PLL3RGE    : 2;            /*!< [11..10] PLL3 input frequency range                                       */
            uint32            : 4;
      __IOM uint32 DIVP1EN    : 1;            /*!< [16..16] PLL1 DIVP divider output enable                                  */
      __IOM uint32 DIVQ1EN    : 1;            /*!< [17..17] PLL1 DIVQ divider output enable                                  */
      __IOM uint32 DIVR1EN    : 1;            /*!< [18..18] PLL1 DIVR divider output enable                                  */
      __IOM uint32 DIVP2EN    : 1;            /*!< [19..19] PLL2 DIVP divider output enable                                  */
      __IOM uint32 DIVQ2EN    : 1;            /*!< [20..20] PLL2 DIVQ divider output enable                                  */
      __IOM uint32 DIVR2EN    : 1;            /*!< [21..21] PLL2 DIVR divider output enable                                  */
      __IOM uint32 DIVP3EN    : 1;            /*!< [22..22] PLL3 DIVP divider output enable                                  */
      __IOM uint32 DIVQ3EN    : 1;            /*!< [23..23] PLL3 DIVQ divider output enable                                  */
      __IOM uint32 DIVR3EN    : 1;            /*!< [24..24] PLL3 DIVR divider output enable                                  */
            uint32            : 7;
    } bit;
  } PLLCFGR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000030) RCC PLL1 Dividers Configuration Register                   */
    
    struct {
      __IOM uint32 DIVN1      : 9;            /*!< [8..0] Multiplication factor for PLL1 VCO                                 */
      __IOM uint32 DIVP1      : 7;            /*!< [15..9] PLL1 DIVP division factor                                         */
      __IOM uint32 DIVQ1      : 7;            /*!< [22..16] PLL1 DIVQ division factor                                        */
            uint32            : 1;
      __IOM uint32 DIVR1      : 7;            /*!< [30..24] PLL1 DIVR division factor                                        */
            uint32            : 1;
    } bit;
  } PLL1DIVR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000034) RCC PLL1 Fractional Divider Register                       */
    
    struct {
            uint32            : 3;
      __IOM uint32 FRACN1     : 13;           /*!< [15..3] Fractional part of the multiplication factor for PLL1
                                                     VCO                                                                       */
            uint32            : 16;
    } bit;
  } PLL1FRACR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000038) RCC PLL2 Dividers Configuration Register                   */
    
    struct {
      __IOM uint32 DIVN1      : 9;            /*!< [8..0] Multiplication factor for PLL1 VCO                                 */
      __IOM uint32 DIVP1      : 7;            /*!< [15..9] PLL1 DIVP division factor                                         */
      __IOM uint32 DIVQ1      : 7;            /*!< [22..16] PLL1 DIVQ division factor                                        */
            uint32            : 1;
      __IOM uint32 DIVR1      : 7;            /*!< [30..24] PLL1 DIVR division factor                                        */
            uint32            : 1;
    } bit;
  } PLL2DIVR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000003C) RCC PLL2 Fractional Divider Register                       */
    
    struct {
            uint32            : 3;
      __IOM uint32 FRACN2     : 13;           /*!< [15..3] Fractional part of the multiplication factor for PLL
                                                     VCO                                                                       */
            uint32            : 16;
    } bit;
  } PLL2FRACR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000040) RCC PLL3 Dividers Configuration Register                   */
    
    struct {
      __IOM uint32 DIVN3      : 9;            /*!< [8..0] Multiplication factor for PLL1 VCO                                 */
      __IOM uint32 DIVP3      : 7;            /*!< [15..9] PLL DIVP division factor                                          */
      __IOM uint32 DIVQ3      : 7;            /*!< [22..16] PLL DIVQ division factor                                         */
            uint32            : 1;
      __IOM uint32 DIVR3      : 7;            /*!< [30..24] PLL DIVR division factor                                         */
            uint32            : 1;
    } bit;
  } PLL3DIVR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000044) RCC PLL3 Fractional Divider Register                       */
    
    struct {
            uint32            : 3;
      __IOM uint32 FRACN3     : 13;           /*!< [15..3] Fractional part of the multiplication factor for PLL3
                                                     VCO                                                                       */
            uint32            : 16;
    } bit;
  } PLL3FRACR;
  __IM  uint32  RESERVED3;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000004C) RCC Domain 1 Kernel Clock Configuration Register           */
    
    struct {
      __IOM uint32 FMCSRC     : 2;            /*!< [1..0] FMC kernel clock source selection                                  */
            uint32            : 2;
      __IOM uint32 QSPISRC    : 2;            /*!< [5..4] QUADSPI kernel clock source selection                              */
            uint32            : 10;
      __IOM uint32 SDMMCSRC   : 1;            /*!< [16..16] SDMMC kernel clock source selection                              */
            uint32            : 11;
      __IOM uint32 CKPERSRC   : 2;            /*!< [29..28] per_ck clock source selection                                    */
            uint32            : 2;
    } bit;
  } D1CCIPR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000050) RCC Domain 2 Kernel Clock Configuration Register           */
    
    struct {
      __IOM uint32 SAI1SRC    : 3;            /*!< [2..0] SAI1 and DFSDM1 kernel Aclk clock source selection                 */
            uint32            : 3;
      __IOM uint32 SAI23SRC   : 3;            /*!< [8..6] SAI2 and SAI3 kernel clock source selection                        */
            uint32            : 3;
      __IOM uint32 SPI123SRC  : 3;            /*!< [14..12] SPI/I2S1,2 and 3 kernel clock source selection                   */
            uint32            : 1;
      __IOM uint32 SPI45SRC   : 3;            /*!< [18..16] SPI4 and 5 kernel clock source selection                         */
            uint32            : 1;
      __IOM uint32 SPDIFSRC   : 2;            /*!< [21..20] SPDIFRX kernel clock source selection                            */
            uint32            : 2;
      __IOM uint32 DFSDM1SRC  : 1;            /*!< [24..24] DFSDM1 kernel Clk clock source selection                         */
            uint32            : 3;
      __IOM uint32 FDCANSRC   : 2;            /*!< [29..28] FDCAN kernel clock source selection                              */
            uint32            : 1;
      __IOM uint32 SWPSRC     : 1;            /*!< [31..31] SWPMI kernel clock source selection                              */
    } bit;
  } D2CCIP1R;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000054) RCC Domain 2 Kernel Clock Configuration Register           */
    
    struct {
      __IOM uint32 USART234578SRC : 3;        /*!< [2..0] USART2/3, UART4,5, 7/8 (APB1) kernel clock source selection        */
      __IOM uint32 USART16SRC : 3;            /*!< [5..3] USART1 and 6 kernel clock source selection                         */
            uint32            : 2;
      __IOM uint32 RNGSRC     : 2;            /*!< [9..8] RNG kernel clock source selection                                  */
            uint32            : 2;
      __IOM uint32 I2C123SRC  : 2;            /*!< [13..12] I2C1,2,3 kernel clock source selection                           */
            uint32            : 6;
      __IOM uint32 USBSRC     : 2;            /*!< [21..20] USBOTG 1 and 2 kernel clock source selection                     */
      __IOM uint32 CECSRC     : 2;            /*!< [23..22] HDMI-CEC kernel clock source selection                           */
            uint32            : 4;
      __IOM uint32 LPTIM1SRC  : 3;            /*!< [30..28] LPTIM1 kernel clock source selection                             */
            uint32            : 1;
    } bit;
  } D2CCIP2R;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000058) RCC Domain 3 Kernel Clock Configuration Register           */
    
    struct {
      __IOM uint32 LPUART1SRC : 3;            /*!< [2..0] LPUART1 kernel clock source selection                              */
            uint32            : 5;
      __IOM uint32 I2C4SRC    : 2;            /*!< [9..8] I2C4 kernel clock source selection                                 */
      __IOM uint32 LPTIM2SRC  : 3;            /*!< [12..10] LPTIM2 kernel clock source selection                             */
      __IOM uint32 LPTIM345SRC : 3;           /*!< [15..13] LPTIM3,4,5 kernel clock source selection                         */
      __IOM uint32 ADCSRC     : 2;            /*!< [17..16] SAR ADC kernel clock source selection                            */
            uint32            : 3;
      __IOM uint32 SAI4ASRC   : 3;            /*!< [23..21] Sub-Block A of SAI4 kernel clock source selection                */
      __IOM uint32 SAI4BSRC   : 3;            /*!< [26..24] Sub-Block B of SAI4 kernel clock source selection                */
            uint32            : 1;
      __IOM uint32 SPI6SRC    : 3;            /*!< [30..28] SPI6 kernel clock source selection                               */
            uint32            : 1;
    } bit;
  } D3CCIPR;
  __IM  uint32  RESERVED4;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000060) RCC Clock Source Interrupt Enable Register                 */
    
    struct {
      __IOM uint32 LSIRDYIE   : 1;            /*!< [0..0] LSI ready Interrupt Enable                                         */
      __IOM uint32 LSERDYIE   : 1;            /*!< [1..1] LSE ready Interrupt Enable                                         */
      __IOM uint32 HSIRDYIE   : 1;            /*!< [2..2] HSI ready Interrupt Enable                                         */
      __IOM uint32 HSERDYIE   : 1;            /*!< [3..3] HSE ready Interrupt Enable                                         */
      __IOM uint32 CSIRDYIE   : 1;            /*!< [4..4] CSI ready Interrupt Enable                                         */
      __IOM uint32 RC48RDYIE  : 1;            /*!< [5..5] RC48 ready Interrupt Enable                                        */
      __IOM uint32 PLL1RDYIE  : 1;            /*!< [6..6] PLL1 ready Interrupt Enable                                        */
      __IOM uint32 PLL2RDYIE  : 1;            /*!< [7..7] PLL2 ready Interrupt Enable                                        */
      __IOM uint32 PLL3RDYIE  : 1;            /*!< [8..8] PLL3 ready Interrupt Enable                                        */
      __IOM uint32 LSECSSIE   : 1;            /*!< [9..9] LSE clock security system Interrupt Enable                         */
            uint32            : 22;
    } bit;
  } CIER;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000064) RCC Clock Source Interrupt Flag Register                   */
    
    struct {
      __IOM uint32 LSIRDYF    : 1;            /*!< [0..0] LSI ready Interrupt Flag                                           */
      __IOM uint32 LSERDYF    : 1;            /*!< [1..1] LSE ready Interrupt Flag                                           */
      __IOM uint32 HSIRDYF    : 1;            /*!< [2..2] HSI ready Interrupt Flag                                           */
      __IOM uint32 HSERDYF    : 1;            /*!< [3..3] HSE ready Interrupt Flag                                           */
      __IOM uint32 CSIRDY     : 1;            /*!< [4..4] CSI ready Interrupt Flag                                           */
      __IOM uint32 RC48RDYF   : 1;            /*!< [5..5] RC48 ready Interrupt Flag                                          */
      __IOM uint32 PLL1RDYF   : 1;            /*!< [6..6] PLL1 ready Interrupt Flag                                          */
      __IOM uint32 PLL2RDYF   : 1;            /*!< [7..7] PLL2 ready Interrupt Flag                                          */
      __IOM uint32 PLL3RDYF   : 1;            /*!< [8..8] PLL3 ready Interrupt Flag                                          */
      __IOM uint32 LSECSSF    : 1;            /*!< [9..9] LSE clock security system Interrupt Flag                           */
      __IOM uint32 HSECSSF    : 1;            /*!< [10..10] HSE clock security system Interrupt Flag                         */
            uint32            : 21;
    } bit;
  } CIFR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000068) RCC Clock Source Interrupt Clear Register                  */
    
    struct {
      __IOM uint32 LSIRDYC    : 1;            /*!< [0..0] LSI ready Interrupt Clear                                          */
      __IOM uint32 LSERDYC    : 1;            /*!< [1..1] LSE ready Interrupt Clear                                          */
      __IOM uint32 HSIRDYC    : 1;            /*!< [2..2] HSI ready Interrupt Clear                                          */
      __IOM uint32 HSERDYC    : 1;            /*!< [3..3] HSE ready Interrupt Clear                                          */
      __IOM uint32 HSE_ready_Interrupt_Clear : 1;/*!< [4..4] CSI ready Interrupt Clear                                       */
      __IOM uint32 RC48RDYC   : 1;            /*!< [5..5] RC48 ready Interrupt Clear                                         */
      __IOM uint32 PLL1RDYC   : 1;            /*!< [6..6] PLL1 ready Interrupt Clear                                         */
      __IOM uint32 PLL2RDYC   : 1;            /*!< [7..7] PLL2 ready Interrupt Clear                                         */
      __IOM uint32 PLL3RDYC   : 1;            /*!< [8..8] PLL3 ready Interrupt Clear                                         */
      __IOM uint32 LSECSSC    : 1;            /*!< [9..9] LSE clock security system Interrupt Clear                          */
      __IOM uint32 HSECSSC    : 1;            /*!< [10..10] HSE clock security system Interrupt Clear                        */
            uint32            : 21;
    } bit;
  } CICR;
  __IM  uint32  RESERVED5;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000070) RCC Backup Domain Control Register                         */
    
    struct {
      __IOM uint32 LSEON      : 1;            /*!< [0..0] LSE oscillator enabled                                             */
      __IOM uint32 LSERDY     : 1;            /*!< [1..1] LSE oscillator ready                                               */
      __IOM uint32 LSEBYP     : 1;            /*!< [2..2] LSE oscillator bypass                                              */
      __IOM uint32 LSEDRV     : 2;            /*!< [4..3] LSE oscillator driving capability                                  */
      __IOM uint32 LSECSSON   : 1;            /*!< [5..5] LSE clock security system enable                                   */
      __IOM uint32 LSECSSD    : 1;            /*!< [6..6] LSE clock security system failure detection                        */
            uint32            : 1;
      __IOM uint32 RTCSRC     : 2;            /*!< [9..8] RTC clock source selection                                         */
            uint32            : 5;
      __IOM uint32 RTCEN      : 1;            /*!< [15..15] RTC clock enable                                                 */
      __IOM uint32 VSWRST     : 1;            /*!< [16..16] VSwitch domain software reset                                    */
            uint32            : 15;
    } bit;
  } BDCR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000074) RCC Clock Control and Status Register                      */
    
    struct {
      __IOM uint32 LSION      : 1;            /*!< [0..0] LSI oscillator enable                                              */
      __IOM uint32 LSIRDY     : 1;            /*!< [1..1] LSI oscillator ready                                               */
            uint32            : 30;
    } bit;
  } CSR;
  __IM  uint32  RESERVED6;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000007C) RCC AHB3 Reset Register                                    */
    
    struct {
      __IOM uint32 MDMARST    : 1;            /*!< [0..0] MDMA block reset                                                   */
            uint32            : 3;
      __IOM uint32 DMA2DRST   : 1;            /*!< [4..4] DMA2D block reset                                                  */
      __IOM uint32 JPGDECRST  : 1;            /*!< [5..5] JPGDEC block reset                                                 */
            uint32            : 6;
      __IOM uint32 FMCRST     : 1;            /*!< [12..12] FMC block reset                                                  */
            uint32            : 1;
      __IOM uint32 QSPIRST    : 1;            /*!< [14..14] QUADSPI and QUADSPI delay block reset                            */
            uint32            : 1;
      __IOM uint32 SDMMC1RST  : 1;            /*!< [16..16] SDMMC1 and SDMMC1 delay block reset                              */
            uint32            : 14;
      __IOM uint32 CPURST     : 1;            /*!< [31..31] CPU reset                                                        */
    } bit;
  } AHB3RSTR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000080) RCC AHB1 Peripheral Reset Register                         */
    
    struct {
      __IOM uint32 DMA1RST    : 1;            /*!< [0..0] DMA1 block reset                                                   */
      __IOM uint32 DMA2RST    : 1;            /*!< [1..1] DMA2 block reset                                                   */
            uint32            : 3;
      __IOM uint32 ADC12RST   : 1;            /*!< [5..5] ADC1&2 block reset                                                 */
            uint32            : 9;
      __IOM uint32 ETH1MACRST : 1;            /*!< [15..15] ETH1MAC block reset                                              */
            uint32            : 9;
      __IOM uint32 USB1OTGRST : 1;            /*!< [25..25] USB1OTG block reset                                              */
            uint32            : 1;
      __IOM uint32 USB2OTGRST : 1;            /*!< [27..27] USB2OTG block reset                                              */
            uint32            : 4;
    } bit;
  } AHB1RSTR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000084) RCC AHB2 Peripheral Reset Register                         */
    
    struct {
      __IOM uint32 CAMITFRST  : 1;            /*!< [0..0] CAMITF block reset                                                 */
            uint32            : 3;
      __IOM uint32 CRYPTRST   : 1;            /*!< [4..4] Cryptography block reset                                           */
      __IOM uint32 HASHRST    : 1;            /*!< [5..5] Hash block reset                                                   */
      __IOM uint32 RNGRST     : 1;            /*!< [6..6] Random Number Generator block reset                                */
            uint32            : 2;
      __IOM uint32 SDMMC2RST  : 1;            /*!< [9..9] SDMMC2 and SDMMC2 Delay block reset                                */
            uint32            : 22;
    } bit;
  } AHB2RSTR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000088) RCC AHB4 Peripheral Reset Register                         */
    
    struct {
      __IOM uint32 GPIOARST   : 1;            /*!< [0..0] GPIO block reset                                                   */
      __IOM uint32 GPIOBRST   : 1;            /*!< [1..1] GPIO block reset                                                   */
      __IOM uint32 GPIOCRST   : 1;            /*!< [2..2] GPIO block reset                                                   */
      __IOM uint32 GPIODRST   : 1;            /*!< [3..3] GPIO block reset                                                   */
      __IOM uint32 GPIOERST   : 1;            /*!< [4..4] GPIO block reset                                                   */
      __IOM uint32 GPIOFRST   : 1;            /*!< [5..5] GPIO block reset                                                   */
      __IOM uint32 GPIOGRST   : 1;            /*!< [6..6] GPIO block reset                                                   */
      __IOM uint32 GPIOHRST   : 1;            /*!< [7..7] GPIO block reset                                                   */
      __IOM uint32 GPIOIRST   : 1;            /*!< [8..8] GPIO block reset                                                   */
      __IOM uint32 GPIOJRST   : 1;            /*!< [9..9] GPIO block reset                                                   */
      __IOM uint32 GPIOKRST   : 1;            /*!< [10..10] GPIO block reset                                                 */
            uint32            : 8;
      __IOM uint32 CRCRST     : 1;            /*!< [19..19] CRC block reset                                                  */
            uint32            : 1;
      __IOM uint32 BDMARST    : 1;            /*!< [21..21] BDMA block reset                                                 */
            uint32            : 2;
      __IOM uint32 ADC3RST    : 1;            /*!< [24..24] ADC3 block reset                                                 */
      __IOM uint32 HSEMRST    : 1;            /*!< [25..25] HSEM block reset                                                 */
            uint32            : 6;
    } bit;
  } AHB4RSTR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000008C) RCC APB3 Peripheral Reset Register                         */
    
    struct {
            uint32            : 3;
      __IOM uint32 LTDCRST    : 1;            /*!< [3..3] LTDC block reset                                                   */
            uint32            : 28;
    } bit;
  } APB3RSTR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000090) RCC APB1 Peripheral Reset Register                         */
    
    struct {
      __IOM uint32 TIM2RST    : 1;            /*!< [0..0] TIM block reset                                                    */
      __IOM uint32 TIM3RST    : 1;            /*!< [1..1] TIM block reset                                                    */
      __IOM uint32 TIM4RST    : 1;            /*!< [2..2] TIM block reset                                                    */
      __IOM uint32 TIM5RST    : 1;            /*!< [3..3] TIM block reset                                                    */
      __IOM uint32 TIM6RST    : 1;            /*!< [4..4] TIM block reset                                                    */
      __IOM uint32 TIM7RST    : 1;            /*!< [5..5] TIM block reset                                                    */
      __IOM uint32 TIM12RST   : 1;            /*!< [6..6] TIM block reset                                                    */
      __IOM uint32 TIM13RST   : 1;            /*!< [7..7] TIM block reset                                                    */
      __IOM uint32 TIM14RST   : 1;            /*!< [8..8] TIM block reset                                                    */
      __IOM uint32 LPTIM1RST  : 1;            /*!< [9..9] TIM block reset                                                    */
            uint32            : 4;
      __IOM uint32 SPI2RST    : 1;            /*!< [14..14] SPI2 block reset                                                 */
      __IOM uint32 SPI3RST    : 1;            /*!< [15..15] SPI3 block reset                                                 */
      __IOM uint32 SPDIFRXRST : 1;            /*!< [16..16] SPDIFRX block reset                                              */
      __IOM uint32 USART2RST  : 1;            /*!< [17..17] USART2 block reset                                               */
      __IOM uint32 USART3RST  : 1;            /*!< [18..18] USART3 block reset                                               */
      __IOM uint32 UART4RST   : 1;            /*!< [19..19] UART4 block reset                                                */
      __IOM uint32 UART5RST   : 1;            /*!< [20..20] UART5 block reset                                                */
      __IOM uint32 I2C1RST    : 1;            /*!< [21..21] I2C1 block reset                                                 */
      __IOM uint32 I2C2RST    : 1;            /*!< [22..22] I2C2 block reset                                                 */
      __IOM uint32 I2C3RST    : 1;            /*!< [23..23] I2C3 block reset                                                 */
            uint32            : 3;
      __IOM uint32 HDMICECRST : 1;            /*!< [27..27] HDMI-CEC block reset                                             */
            uint32            : 1;
      __IOM uint32 DAC12RST   : 1;            /*!< [29..29] DAC1 and 2 Blocks Reset                                          */
      __IOM uint32 USART7RST  : 1;            /*!< [30..30] USART7 block reset                                               */
      __IOM uint32 USART8RST  : 1;            /*!< [31..31] USART8 block reset                                               */
    } bit;
  } APB1LRSTR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000094) RCC APB1 Peripheral Reset Register                         */
    
    struct {
            uint32            : 1;
      __IOM uint32 CRSRST     : 1;            /*!< [1..1] Clock Recovery System reset                                        */
      __IOM uint32 SWPRST     : 1;            /*!< [2..2] SWPMI block reset                                                  */
            uint32            : 1;
      __IOM uint32 OPAMPRST   : 1;            /*!< [4..4] OPAMP block reset                                                  */
      __IOM uint32 MDIOSRST   : 1;            /*!< [5..5] MDIOS block reset                                                  */
            uint32            : 2;
      __IOM uint32 FDCANRST   : 1;            /*!< [8..8] FDCAN block reset                                                  */
            uint32            : 23;
    } bit;
  } APB1HRSTR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000098) RCC APB2 Peripheral Reset Register                         */
    
    struct {
      __IOM uint32 TIM1RST    : 1;            /*!< [0..0] TIM1 block reset                                                   */
      __IOM uint32 TIM8RST    : 1;            /*!< [1..1] TIM8 block reset                                                   */
            uint32            : 2;
      __IOM uint32 USART1RST  : 1;            /*!< [4..4] USART1 block reset                                                 */
      __IOM uint32 USART6RST  : 1;            /*!< [5..5] USART6 block reset                                                 */
            uint32            : 6;
      __IOM uint32 SPI1RST    : 1;            /*!< [12..12] SPI1 block reset                                                 */
      __IOM uint32 SPI4RST    : 1;            /*!< [13..13] SPI4 block reset                                                 */
            uint32            : 2;
      __IOM uint32 TIM15RST   : 1;            /*!< [16..16] TIM15 block reset                                                */
      __IOM uint32 TIM16RST   : 1;            /*!< [17..17] TIM16 block reset                                                */
      __IOM uint32 TIM17RST   : 1;            /*!< [18..18] TIM17 block reset                                                */
            uint32            : 1;
      __IOM uint32 SPI5RST    : 1;            /*!< [20..20] SPI5 block reset                                                 */
            uint32            : 1;
      __IOM uint32 SAI1RST    : 1;            /*!< [22..22] SAI1 block reset                                                 */
      __IOM uint32 SAI2RST    : 1;            /*!< [23..23] SAI2 block reset                                                 */
      __IOM uint32 SAI3RST    : 1;            /*!< [24..24] SAI3 block reset                                                 */
            uint32            : 3;
      __IOM uint32 DFSDM1RST  : 1;            /*!< [28..28] DFSDM1 block reset                                               */
      __IOM uint32 HRTIMRST   : 1;            /*!< [29..29] HRTIM block reset                                                */
            uint32            : 2;
    } bit;
  } APB2RSTR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000009C) RCC APB4 Peripheral Reset Register                         */
    
    struct {
            uint32            : 1;
      __IOM uint32 SYSCFGRST  : 1;            /*!< [1..1] SYSCFG block reset                                                 */
            uint32            : 1;
      __IOM uint32 LPUART1RST : 1;            /*!< [3..3] LPUART1 block reset                                                */
            uint32            : 1;
      __IOM uint32 SPI6RST    : 1;            /*!< [5..5] SPI6 block reset                                                   */
            uint32            : 1;
      __IOM uint32 I2C4RST    : 1;            /*!< [7..7] I2C4 block reset                                                   */
            uint32            : 1;
      __IOM uint32 LPTIM2RST  : 1;            /*!< [9..9] LPTIM2 block reset                                                 */
      __IOM uint32 LPTIM3RST  : 1;            /*!< [10..10] LPTIM3 block reset                                               */
      __IOM uint32 LPTIM4RST  : 1;            /*!< [11..11] LPTIM4 block reset                                               */
      __IOM uint32 LPTIM5RST  : 1;            /*!< [12..12] LPTIM5 block reset                                               */
            uint32            : 1;
      __IOM uint32 COMP12RST  : 1;            /*!< [14..14] COMP12 Blocks Reset                                              */
      __IOM uint32 VREFRST    : 1;            /*!< [15..15] VREF block reset                                                 */
            uint32            : 5;
      __IOM uint32 SAI4RST    : 1;            /*!< [21..21] SAI4 block reset                                                 */
            uint32            : 10;
    } bit;
  } APB4RSTR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x000000A0) RCC Global Control Register                                */
    
    struct {
      __IOM uint32 WW1RSC     : 1;            /*!< [0..0] WWDG1 reset scope control                                          */
            uint32            : 31;
    } bit;
  } GCR;
  __IM  uint32  RESERVED7;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x000000A8) RCC D3 Autonomous mode Register                            */
    
    struct {
      __IOM uint32 BDMAAMEN   : 1;            /*!< [0..0] BDMA and DMAMUX Autonomous mode enable                             */
            uint32            : 2;
      __IOM uint32 LPUART1AMEN : 1;           /*!< [3..3] LPUART1 Autonomous mode enable                                     */
            uint32            : 1;
      __IOM uint32 SPI6AMEN   : 1;            /*!< [5..5] SPI6 Autonomous mode enable                                        */
            uint32            : 1;
      __IOM uint32 I2C4AMEN   : 1;            /*!< [7..7] I2C4 Autonomous mode enable                                        */
            uint32            : 1;
      __IOM uint32 LPTIM2AMEN : 1;            /*!< [9..9] LPTIM2 Autonomous mode enable                                      */
      __IOM uint32 LPTIM3AMEN : 1;            /*!< [10..10] LPTIM3 Autonomous mode enable                                    */
      __IOM uint32 LPTIM4AMEN : 1;            /*!< [11..11] LPTIM4 Autonomous mode enable                                    */
      __IOM uint32 LPTIM5AMEN : 1;            /*!< [12..12] LPTIM5 Autonomous mode enable                                    */
            uint32            : 1;
      __IOM uint32 COMP12AMEN : 1;            /*!< [14..14] COMP12 Autonomous mode enable                                    */
      __IOM uint32 VREFAMEN   : 1;            /*!< [15..15] VREF Autonomous mode enable                                      */
      __IOM uint32 RTCAMEN    : 1;            /*!< [16..16] RTC Autonomous mode enable                                       */
            uint32            : 2;
      __IOM uint32 CRCAMEN    : 1;            /*!< [19..19] CRC Autonomous mode enable                                       */
            uint32            : 1;
      __IOM uint32 SAI4AMEN   : 1;            /*!< [21..21] SAI4 Autonomous mode enable                                      */
            uint32            : 2;
      __IOM uint32 ADC3AMEN   : 1;            /*!< [24..24] ADC3 Autonomous mode enable                                      */
            uint32            : 3;
      __IOM uint32 BKPSRAMAMEN : 1;           /*!< [28..28] Backup RAM Autonomous mode enable                                */
      __IOM uint32 SRAM4AMEN  : 1;            /*!< [29..29] SRAM4 Autonomous mode enable                                     */
            uint32            : 2;
    } bit;
  } D3AMR;
  __IM  uint32  RESERVED8[9];
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x000000D0) RCC Reset Status Register                                  */
    
    struct {
            uint32            : 16;
      __IOM uint32 RMVF       : 1;            /*!< [16..16] Remove reset flag                                                */
      __IOM uint32 CPURSTF    : 1;            /*!< [17..17] CPU reset flag                                                   */
            uint32            : 1;
      __IOM uint32 D1RSTF     : 1;            /*!< [19..19] D1 domain power switch reset flag                                */
      __IOM uint32 D2RSTF     : 1;            /*!< [20..20] D2 domain power switch reset flag                                */
      __IOM uint32 BORRSTF    : 1;            /*!< [21..21] BOR reset flag                                                   */
      __IOM uint32 PINRSTF    : 1;            /*!< [22..22] Pin reset flag (NRST)                                            */
      __IOM uint32 PORRSTF    : 1;            /*!< [23..23] POR/PDR reset flag                                               */
      __IOM uint32 SFTRSTF    : 1;            /*!< [24..24] System reset from CPU reset flag                                 */
            uint32            : 1;
      __IOM uint32 IWDG1RSTF  : 1;            /*!< [26..26] Independent Watchdog reset flag                                  */
            uint32            : 1;
      __IOM uint32 WWDG1RSTF  : 1;            /*!< [28..28] Window Watchdog reset flag                                       */
            uint32            : 1;
      __IOM uint32 LPWRRSTF   : 1;            /*!< [30..30] Reset due to illegal D1 DStandby or CPU CStop flag               */
            uint32            : 1;
    } bit;
  } RSR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x000000D4) RCC AHB3 Clock Register                                    */
    
    struct {
      __IOM uint32 MDMAEN     : 1;            /*!< [0..0] MDMA Peripheral Clock Enable                                       */
            uint32            : 3;
      __IOM uint32 DMA2DEN    : 1;            /*!< [4..4] DMA2D Peripheral Clock Enable                                      */
      __IOM uint32 JPGDECEN   : 1;            /*!< [5..5] JPGDEC Peripheral Clock Enable                                     */
            uint32            : 6;
      __IOM uint32 FMCEN      : 1;            /*!< [12..12] FMC Peripheral Clocks Enable                                     */
            uint32            : 1;
      __IOM uint32 QSPIEN     : 1;            /*!< [14..14] QUADSPI and QUADSPI Delay Clock Enable                           */
            uint32            : 1;
      __IOM uint32 SDMMC1EN   : 1;            /*!< [16..16] SDMMC1 and SDMMC1 Delay Clock Enable                             */
            uint32            : 15;
    } bit;
  } AHB3ENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x000000D8) RCC AHB1 Clock Register                                    */
    
    struct {
      __IOM uint32 DMA1EN     : 1;            /*!< [0..0] DMA1 Clock Enable                                                  */
      __IOM uint32 DMA2EN     : 1;            /*!< [1..1] DMA2 Clock Enable                                                  */
            uint32            : 3;
      __IOM uint32 ADC12EN    : 1;            /*!< [5..5] ADC1/2 Peripheral Clocks Enable                                    */
            uint32            : 9;
      __IOM uint32 ETH1MACEN  : 1;            /*!< [15..15] Ethernet MAC bus interface Clock Enable                          */
      __IOM uint32 ETH1TXEN   : 1;            /*!< [16..16] Ethernet Transmission Clock Enable                               */
      __IOM uint32 ETH1RXEN   : 1;            /*!< [17..17] Ethernet Reception Clock Enable                                  */
            uint32            : 7;
      __IOM uint32 USB1OTGEN  : 1;            /*!< [25..25] USB1OTG Peripheral Clocks Enable                                 */
      __IOM uint32 USB1ULPIEN : 1;            /*!< [26..26] USB_PHY1 Clocks Enable                                           */
      __IOM uint32 USB2OTGEN  : 1;            /*!< [27..27] USB2OTG Peripheral Clocks Enable                                 */
      __IOM uint32 USB2ULPIEN : 1;            /*!< [28..28] USB_PHY2 Clocks Enable                                           */
            uint32            : 3;
    } bit;
  } AHB1ENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x000000DC) RCC AHB2 Clock Register                                    */
    
    struct {
      __IOM uint32 CAMITFEN   : 1;            /*!< [0..0] CAMITF peripheral clock enable                                     */
            uint32            : 3;
      __IOM uint32 CRYPTEN    : 1;            /*!< [4..4] CRYPT peripheral clock enable                                      */
      __IOM uint32 HASHEN     : 1;            /*!< [5..5] HASH peripheral clock enable                                       */
      __IOM uint32 RNGEN      : 1;            /*!< [6..6] RNG peripheral clocks enable                                       */
            uint32            : 2;
      __IOM uint32 SDMMC2EN   : 1;            /*!< [9..9] SDMMC2 and SDMMC2 delay clock enable                               */
            uint32            : 19;
      __IOM uint32 SRAM1EN    : 1;            /*!< [29..29] SRAM1 block enable                                               */
      __IOM uint32 SRAM2EN    : 1;            /*!< [30..30] SRAM2 block enable                                               */
      __IOM uint32 SRAM3EN    : 1;            /*!< [31..31] SRAM3 block enable                                               */
    } bit;
  } AHB2ENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x000000E0) RCC AHB4 Clock Register                                    */
    
    struct {
      __IOM uint32 GPIOAEN    : 1;            /*!< [0..0] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOBEN    : 1;            /*!< [1..1] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOCEN    : 1;            /*!< [2..2] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIODEN    : 1;            /*!< [3..3] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOEEN    : 1;            /*!< [4..4] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOFEN    : 1;            /*!< [5..5] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOGEN    : 1;            /*!< [6..6] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOHEN    : 1;            /*!< [7..7] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOIEN    : 1;            /*!< [8..8] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOJEN    : 1;            /*!< [9..9] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOKEN    : 1;            /*!< [10..10] 0GPIO peripheral clock enable                                    */
            uint32            : 8;
      __IOM uint32 CRCEN      : 1;            /*!< [19..19] CRC peripheral clock enable                                      */
            uint32            : 1;
      __IOM uint32 BDMAEN     : 1;            /*!< [21..21] BDMA and DMAMUX2 Clock Enable                                    */
            uint32            : 2;
      __IOM uint32 ADC3EN     : 1;            /*!< [24..24] ADC3 Peripheral Clocks Enable                                    */
      __IOM uint32 HSEMEN     : 1;            /*!< [25..25] HSEM peripheral clock enable                                     */
            uint32            : 2;
      __IOM uint32 BKPRAMEN   : 1;            /*!< [28..28] Backup RAM Clock Enable                                          */
            uint32            : 3;
    } bit;
  } AHB4ENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x000000E4) RCC APB3 Clock Register                                    */
    
    struct {
            uint32            : 3;
      __IOM uint32 LTDCEN     : 1;            /*!< [3..3] LTDC peripheral clock enable                                       */
            uint32            : 2;
      __IOM uint32 WWDG1EN    : 1;            /*!< [6..6] WWDG1 Clock Enable                                                 */
            uint32            : 25;
    } bit;
  } APB3ENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x000000E8) RCC APB1 Clock Register                                    */
    
    struct {
      __IOM uint32 TIM2EN     : 1;            /*!< [0..0] TIM peripheral clock enable                                        */
      __IOM uint32 TIM3EN     : 1;            /*!< [1..1] TIM peripheral clock enable                                        */
      __IOM uint32 TIM4EN     : 1;            /*!< [2..2] TIM peripheral clock enable                                        */
      __IOM uint32 TIM5EN     : 1;            /*!< [3..3] TIM peripheral clock enable                                        */
      __IOM uint32 TIM6EN     : 1;            /*!< [4..4] TIM peripheral clock enable                                        */
      __IOM uint32 TIM7EN     : 1;            /*!< [5..5] TIM peripheral clock enable                                        */
      __IOM uint32 TIM12EN    : 1;            /*!< [6..6] TIM peripheral clock enable                                        */
      __IOM uint32 TIM13EN    : 1;            /*!< [7..7] TIM peripheral clock enable                                        */
      __IOM uint32 TIM14EN    : 1;            /*!< [8..8] TIM peripheral clock enable                                        */
      __IOM uint32 LPTIM1EN   : 1;            /*!< [9..9] LPTIM1 Peripheral Clocks Enable                                    */
            uint32            : 4;
      __IOM uint32 SPI2EN     : 1;            /*!< [14..14] SPI2 Peripheral Clocks Enable                                    */
      __IOM uint32 SPI3EN     : 1;            /*!< [15..15] SPI3 Peripheral Clocks Enable                                    */
      __IOM uint32 SPDIFRXEN  : 1;            /*!< [16..16] SPDIFRX Peripheral Clocks Enable                                 */
      __IOM uint32 USART2EN   : 1;            /*!< [17..17] USART2 Peripheral Clocks Enable                                  */
      __IOM uint32 USART3EN   : 1;            /*!< [18..18] USART3 Peripheral Clocks Enable                                  */
      __IOM uint32 UART4EN    : 1;            /*!< [19..19] UART4 Peripheral Clocks Enable                                   */
      __IOM uint32 UART5EN    : 1;            /*!< [20..20] UART5 Peripheral Clocks Enable                                   */
      __IOM uint32 I2C1EN     : 1;            /*!< [21..21] I2C1 Peripheral Clocks Enable                                    */
      __IOM uint32 I2C2EN     : 1;            /*!< [22..22] I2C2 Peripheral Clocks Enable                                    */
      __IOM uint32 I2C3EN     : 1;            /*!< [23..23] I2C3 Peripheral Clocks Enable                                    */
            uint32            : 3;
      __IOM uint32 HDMICECEN  : 1;            /*!< [27..27] HDMI-CEC peripheral clock enable                                 */
            uint32            : 1;
      __IOM uint32 DAC12EN    : 1;            /*!< [29..29] DAC1&2 peripheral clock enable                                   */
      __IOM uint32 USART7EN   : 1;            /*!< [30..30] USART7 Peripheral Clocks Enable                                  */
      __IOM uint32 USART8EN   : 1;            /*!< [31..31] USART8 Peripheral Clocks Enable                                  */
    } bit;
  } APB1LENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x000000EC) RCC APB1 Clock Register                                    */
    
    struct {
            uint32            : 1;
      __IOM uint32 CRSEN      : 1;            /*!< [1..1] Clock Recovery System peripheral clock enable                      */
      __IOM uint32 SWPEN      : 1;            /*!< [2..2] SWPMI Peripheral Clocks Enable                                     */
            uint32            : 1;
      __IOM uint32 OPAMPEN    : 1;            /*!< [4..4] OPAMP peripheral clock enable                                      */
      __IOM uint32 MDIOSEN    : 1;            /*!< [5..5] MDIOS peripheral clock enable                                      */
            uint32            : 2;
      __IOM uint32 FDCANEN    : 1;            /*!< [8..8] FDCAN Peripheral Clocks Enable                                     */
            uint32            : 23;
    } bit;
  } APB1HENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x000000F0) RCC APB2 Clock Register                                    */
    
    struct {
      __IOM uint32 TIM1EN     : 1;            /*!< [0..0] TIM1 peripheral clock enable                                       */
      __IOM uint32 TIM8EN     : 1;            /*!< [1..1] TIM8 peripheral clock enable                                       */
            uint32            : 2;
      __IOM uint32 USART1EN   : 1;            /*!< [4..4] USART1 Peripheral Clocks Enable                                    */
      __IOM uint32 USART6EN   : 1;            /*!< [5..5] USART6 Peripheral Clocks Enable                                    */
            uint32            : 6;
      __IOM uint32 SPI1EN     : 1;            /*!< [12..12] SPI1 Peripheral Clocks Enable                                    */
      __IOM uint32 SPI4EN     : 1;            /*!< [13..13] SPI4 Peripheral Clocks Enable                                    */
            uint32            : 2;
      __IOM uint32 TIM15EN    : 1;            /*!< [16..16] TIM15 peripheral clock enable                                    */
      __IOM uint32 TIM16EN    : 1;            /*!< [17..17] TIM16 peripheral clock enable                                    */
      __IOM uint32 TIM17EN    : 1;            /*!< [18..18] TIM17 peripheral clock enable                                    */
            uint32            : 1;
      __IOM uint32 SPI5EN     : 1;            /*!< [20..20] SPI5 Peripheral Clocks Enable                                    */
            uint32            : 1;
      __IOM uint32 SAI1EN     : 1;            /*!< [22..22] SAI1 Peripheral Clocks Enable                                    */
      __IOM uint32 SAI2EN     : 1;            /*!< [23..23] SAI2 Peripheral Clocks Enable                                    */
      __IOM uint32 SAI3EN     : 1;            /*!< [24..24] SAI3 Peripheral Clocks Enable                                    */
            uint32            : 3;
      __IOM uint32 DFSDM1EN   : 1;            /*!< [28..28] DFSDM1 Peripheral Clocks Enable                                  */
      __IOM uint32 HRTIMEN    : 1;            /*!< [29..29] HRTIM peripheral clock enable                                    */
            uint32            : 2;
    } bit;
  } APB2ENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x000000F4) RCC APB4 Clock Register                                    */
    
    struct {
            uint32            : 1;
      __IOM uint32 SYSCFGEN   : 1;            /*!< [1..1] SYSCFG peripheral clock enable                                     */
            uint32            : 1;
      __IOM uint32 LPUART1EN  : 1;            /*!< [3..3] LPUART1 Peripheral Clocks Enable                                   */
            uint32            : 1;
      __IOM uint32 SPI6EN     : 1;            /*!< [5..5] SPI6 Peripheral Clocks Enable                                      */
            uint32            : 1;
      __IOM uint32 I2C4EN     : 1;            /*!< [7..7] I2C4 Peripheral Clocks Enable                                      */
            uint32            : 1;
      __IOM uint32 LPTIM2EN   : 1;            /*!< [9..9] LPTIM2 Peripheral Clocks Enable                                    */
      __IOM uint32 LPTIM3EN   : 1;            /*!< [10..10] LPTIM3 Peripheral Clocks Enable                                  */
      __IOM uint32 LPTIM4EN   : 1;            /*!< [11..11] LPTIM4 Peripheral Clocks Enable                                  */
      __IOM uint32 LPTIM5EN   : 1;            /*!< [12..12] LPTIM5 Peripheral Clocks Enable                                  */
            uint32            : 1;
      __IOM uint32 COMP12EN   : 1;            /*!< [14..14] COMP1/2 peripheral clock enable                                  */
      __IOM uint32 VREFEN     : 1;            /*!< [15..15] VREF peripheral clock enable                                     */
      __IOM uint32 RTCAPBEN   : 1;            /*!< [16..16] RTC APB Clock Enable                                             */
            uint32            : 4;
      __IOM uint32 SAI4EN     : 1;            /*!< [21..21] SAI4 Peripheral Clocks Enable                                    */
            uint32            : 10;
    } bit;
  } APB4ENR;
  __IM  uint32  RESERVED9;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x000000FC) RCC AHB3 Sleep Clock Register                              */
    
    struct {
      __IOM uint32 MDMALPEN   : 1;            /*!< [0..0] MDMA Clock Enable During CSleep Mode                               */
            uint32            : 3;
      __IOM uint32 DMA2DLPEN  : 1;            /*!< [4..4] DMA2D Clock Enable During CSleep Mode                              */
      __IOM uint32 JPGDECLPEN : 1;            /*!< [5..5] JPGDEC Clock Enable During CSleep Mode                             */
            uint32            : 2;
      __IOM uint32 FLITFLPEN  : 1;            /*!< [8..8] FLITF Clock Enable During CSleep Mode                              */
            uint32            : 3;
      __IOM uint32 FMCLPEN    : 1;            /*!< [12..12] FMC Peripheral Clocks Enable During CSleep Mode                  */
            uint32            : 1;
      __IOM uint32 QSPILPEN   : 1;            /*!< [14..14] QUADSPI and QUADSPI Delay Clock Enable During CSleep
                                                     Mode                                                                      */
            uint32            : 1;
      __IOM uint32 SDMMC1LPEN : 1;            /*!< [16..16] SDMMC1 and SDMMC1 Delay Clock Enable During CSleep
                                                     Mode                                                                      */
            uint32            : 11;
      __IOM uint32 D1DTCM1LPEN : 1;           /*!< [28..28] D1DTCM1 Block Clock Enable During CSleep mode                    */
      __IOM uint32 DTCM2LPEN  : 1;            /*!< [29..29] D1 DTCM2 Block Clock Enable During CSleep mode                   */
      __IOM uint32 ITCMLPEN   : 1;            /*!< [30..30] D1ITCM Block Clock Enable During CSleep mode                     */
      __IOM uint32 AXISRAMLPEN : 1;           /*!< [31..31] AXISRAM Block Clock Enable During CSleep mode                    */
    } bit;
  } AHB3LPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000100) RCC AHB1 Sleep Clock Register                              */
    
    struct {
      __IOM uint32 DMA1LPEN   : 1;            /*!< [0..0] DMA1 Clock Enable During CSleep Mode                               */
      __IOM uint32 DMA2LPEN   : 1;            /*!< [1..1] DMA2 Clock Enable During CSleep Mode                               */
            uint32            : 3;
      __IOM uint32 ADC12LPEN  : 1;            /*!< [5..5] ADC1/2 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 9;
      __IOM uint32 ETH1MACLPEN : 1;           /*!< [15..15] Ethernet MAC bus interface Clock Enable During CSleep
                                                     Mode                                                                      */
      __IOM uint32 ETH1TXLPEN : 1;            /*!< [16..16] Ethernet Transmission Clock Enable During CSleep Mode            */
      __IOM uint32 ETH1RXLPEN : 1;            /*!< [17..17] Ethernet Reception Clock Enable During CSleep Mode               */
            uint32            : 7;
      __IOM uint32 USB1OTGLPEN : 1;           /*!< [25..25] USB1OTG peripheral clock enable during CSleep mode               */
      __IOM uint32 USB1ULPILPEN : 1;          /*!< [26..26] USB_PHY1 clock enable during CSleep mode                         */
      __IOM uint32 USB2OTGLPEN : 1;           /*!< [27..27] USB2OTG peripheral clock enable during CSleep mode               */
      __IOM uint32 USB2ULPILPEN : 1;          /*!< [28..28] USB_PHY2 clocks enable during CSleep mode                        */
            uint32            : 3;
    } bit;
  } AHB1LPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000104) RCC AHB2 Sleep Clock Register                              */
    
    struct {
      __IOM uint32 CAMITFLPEN : 1;            /*!< [0..0] CAMITF peripheral clock enable during CSleep mode                  */
            uint32            : 3;
      __IOM uint32 CRYPTLPEN  : 1;            /*!< [4..4] CRYPT peripheral clock enable during CSleep mode                   */
      __IOM uint32 HASHLPEN   : 1;            /*!< [5..5] HASH peripheral clock enable during CSleep mode                    */
      __IOM uint32 RNGLPEN    : 1;            /*!< [6..6] RNG peripheral clock enable during CSleep mode                     */
            uint32            : 2;
      __IOM uint32 SDMMC2LPEN : 1;            /*!< [9..9] SDMMC2 and SDMMC2 Delay Clock Enable During CSleep Mode            */
            uint32            : 19;
      __IOM uint32 SRAM1LPEN  : 1;            /*!< [29..29] SRAM1 Clock Enable During CSleep Mode                            */
      __IOM uint32 SRAM2LPEN  : 1;            /*!< [30..30] SRAM2 Clock Enable During CSleep Mode                            */
      __IOM uint32 SRAM3LPEN  : 1;            /*!< [31..31] SRAM3 Clock Enable During CSleep Mode                            */
    } bit;
  } AHB2LPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000108) RCC AHB4 Sleep Clock Register                              */
    
    struct {
      __IOM uint32 GPIOALPEN  : 1;            /*!< [0..0] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOBLPEN  : 1;            /*!< [1..1] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOCLPEN  : 1;            /*!< [2..2] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIODLPEN  : 1;            /*!< [3..3] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOELPEN  : 1;            /*!< [4..4] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOFLPEN  : 1;            /*!< [5..5] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOGLPEN  : 1;            /*!< [6..6] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOHLPEN  : 1;            /*!< [7..7] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOILPEN  : 1;            /*!< [8..8] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOJLPEN  : 1;            /*!< [9..9] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOKLPEN  : 1;            /*!< [10..10] GPIO peripheral clock enable during CSleep mode                  */
            uint32            : 8;
      __IOM uint32 CRCLPEN    : 1;            /*!< [19..19] CRC peripheral clock enable during CSleep mode                   */
            uint32            : 1;
      __IOM uint32 BDMALPEN   : 1;            /*!< [21..21] BDMA Clock Enable During CSleep Mode                             */
            uint32            : 2;
      __IOM uint32 ADC3LPEN   : 1;            /*!< [24..24] ADC3 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 3;
      __IOM uint32 BKPRAMLPEN : 1;            /*!< [28..28] Backup RAM Clock Enable During CSleep Mode                       */
      __IOM uint32 SRAM4LPEN  : 1;            /*!< [29..29] SRAM4 Clock Enable During CSleep Mode                            */
            uint32            : 2;
    } bit;
  } AHB4LPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000010C) RCC APB3 Sleep Clock Register                              */
    
    struct {
            uint32            : 3;
      __IOM uint32 LTDCLPEN   : 1;            /*!< [3..3] LTDC peripheral clock enable during CSleep mode                    */
            uint32            : 2;
      __IOM uint32 WWDG1LPEN  : 1;            /*!< [6..6] WWDG1 Clock Enable During CSleep Mode                              */
            uint32            : 25;
    } bit;
  } APB3LPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000110) RCC APB1 Low Sleep Clock Register                          */
    
    struct {
      __IOM uint32 TIM2LPEN   : 1;            /*!< [0..0] TIM2 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM3LPEN   : 1;            /*!< [1..1] TIM3 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM4LPEN   : 1;            /*!< [2..2] TIM4 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM5LPEN   : 1;            /*!< [3..3] TIM5 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM6LPEN   : 1;            /*!< [4..4] TIM6 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM7LPEN   : 1;            /*!< [5..5] TIM7 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM12LPEN  : 1;            /*!< [6..6] TIM12 peripheral clock enable during CSleep mode                   */
      __IOM uint32 TIM13LPEN  : 1;            /*!< [7..7] TIM13 peripheral clock enable during CSleep mode                   */
      __IOM uint32 TIM14LPEN  : 1;            /*!< [8..8] TIM14 peripheral clock enable during CSleep mode                   */
      __IOM uint32 LPTIM1LPEN : 1;            /*!< [9..9] LPTIM1 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 4;
      __IOM uint32 SPI2LPEN   : 1;            /*!< [14..14] SPI2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 SPI3LPEN   : 1;            /*!< [15..15] SPI3 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 SPDIFRXLPEN : 1;           /*!< [16..16] SPDIFRX Peripheral Clocks Enable During CSleep Mode              */
      __IOM uint32 USART2LPEN : 1;            /*!< [17..17] USART2 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32 USART3LPEN : 1;            /*!< [18..18] USART3 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32 UART4LPEN  : 1;            /*!< [19..19] UART4 Peripheral Clocks Enable During CSleep Mode                */
      __IOM uint32 UART5LPEN  : 1;            /*!< [20..20] UART5 Peripheral Clocks Enable During CSleep Mode                */
      __IOM uint32 I2C1LPEN   : 1;            /*!< [21..21] I2C1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 I2C2LPEN   : 1;            /*!< [22..22] I2C2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 I2C3LPEN   : 1;            /*!< [23..23] I2C3 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 3;
      __IOM uint32 HDMICECLPEN : 1;           /*!< [27..27] HDMI-CEC Peripheral Clocks Enable During CSleep Mode             */
            uint32            : 1;
      __IOM uint32 DAC12LPEN  : 1;            /*!< [29..29] DAC1/2 peripheral clock enable during CSleep mode                */
      __IOM uint32 USART7LPEN : 1;            /*!< [30..30] USART7 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32 USART8LPEN : 1;            /*!< [31..31] USART8 Peripheral Clocks Enable During CSleep Mode               */
    } bit;
  } APB1LLPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000114) RCC APB1 High Sleep Clock Register                         */
    
    struct {
            uint32            : 1;
      __IOM uint32 CRSLPEN    : 1;            /*!< [1..1] Clock Recovery System peripheral clock enable during
                                                     CSleep mode                                                               */
      __IOM uint32 SWPLPEN    : 1;            /*!< [2..2] SWPMI Peripheral Clocks Enable During CSleep Mode                  */
            uint32            : 1;
      __IOM uint32 OPAMPLPEN  : 1;            /*!< [4..4] OPAMP peripheral clock enable during CSleep mode                   */
      __IOM uint32 MDIOSLPEN  : 1;            /*!< [5..5] MDIOS peripheral clock enable during CSleep mode                   */
            uint32            : 2;
      __IOM uint32 FDCANLPEN  : 1;            /*!< [8..8] FDCAN Peripheral Clocks Enable During CSleep Mode                  */
            uint32            : 23;
    } bit;
  } APB1HLPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000118) RCC APB2 Sleep Clock Register                              */
    
    struct {
      __IOM uint32 TIM1LPEN   : 1;            /*!< [0..0] TIM1 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM8LPEN   : 1;            /*!< [1..1] TIM8 peripheral clock enable during CSleep mode                    */
            uint32            : 2;
      __IOM uint32 USART1LPEN : 1;            /*!< [4..4] USART1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 USART6LPEN : 1;            /*!< [5..5] USART6 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 6;
      __IOM uint32 SPI1LPEN   : 1;            /*!< [12..12] SPI1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 SPI4LPEN   : 1;            /*!< [13..13] SPI4 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 2;
      __IOM uint32 TIM15LPEN  : 1;            /*!< [16..16] TIM15 peripheral clock enable during CSleep mode                 */
      __IOM uint32 TIM16LPEN  : 1;            /*!< [17..17] TIM16 peripheral clock enable during CSleep mode                 */
      __IOM uint32 TIM17LPEN  : 1;            /*!< [18..18] TIM17 peripheral clock enable during CSleep mode                 */
            uint32            : 1;
      __IOM uint32 SPI5LPEN   : 1;            /*!< [20..20] SPI5 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 1;
      __IOM uint32 SAI1LPEN   : 1;            /*!< [22..22] SAI1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 SAI2LPEN   : 1;            /*!< [23..23] SAI2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 SAI3LPEN   : 1;            /*!< [24..24] SAI3 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 3;
      __IOM uint32 DFSDM1LPEN : 1;            /*!< [28..28] DFSDM1 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32 HRTIMLPEN  : 1;            /*!< [29..29] HRTIM peripheral clock enable during CSleep mode                 */
            uint32            : 2;
    } bit;
  } APB2LPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000011C) RCC APB4 Sleep Clock Register                              */
    
    struct {
            uint32            : 1;
      __IOM uint32 SYSCFGLPEN : 1;            /*!< [1..1] SYSCFG peripheral clock enable during CSleep mode                  */
            uint32            : 1;
      __IOM uint32 LPUART1LPEN : 1;           /*!< [3..3] LPUART1 Peripheral Clocks Enable During CSleep Mode                */
            uint32            : 1;
      __IOM uint32 SPI6LPEN   : 1;            /*!< [5..5] SPI6 Peripheral Clocks Enable During CSleep Mode                   */
            uint32            : 1;
      __IOM uint32 I2C4LPEN   : 1;            /*!< [7..7] I2C4 Peripheral Clocks Enable During CSleep Mode                   */
            uint32            : 1;
      __IOM uint32 LPTIM2LPEN : 1;            /*!< [9..9] LPTIM2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 LPTIM3LPEN : 1;            /*!< [10..10] LPTIM3 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32 LPTIM4LPEN : 1;            /*!< [11..11] LPTIM4 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32 LPTIM5LPEN : 1;            /*!< [12..12] LPTIM5 Peripheral Clocks Enable During CSleep Mode               */
            uint32            : 1;
      __IOM uint32 COMP12LPEN : 1;            /*!< [14..14] COMP1/2 peripheral clock enable during CSleep mode               */
      __IOM uint32 VREFLPEN   : 1;            /*!< [15..15] VREF peripheral clock enable during CSleep mode                  */
      __IOM uint32 RTCAPBLPEN : 1;            /*!< [16..16] RTC APB Clock Enable During CSleep Mode                          */
            uint32            : 4;
      __IOM uint32 SAI4LPEN   : 1;            /*!< [21..21] SAI4 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 10;
    } bit;
  } APB4LPENR;
  __IM  uint32  RESERVED10[4];
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000130) RCC Reset Status Register                                  */
    
    struct {
            uint32            : 16;
      __IOM uint32 RMVF       : 1;            /*!< [16..16] Remove reset flag                                                */
      __IOM uint32 CPURSTF    : 1;            /*!< [17..17] CPU reset flag                                                   */
            uint32            : 1;
      __IOM uint32 D1RSTF     : 1;            /*!< [19..19] D1 domain power switch reset flag                                */
      __IOM uint32 D2RSTF     : 1;            /*!< [20..20] D2 domain power switch reset flag                                */
      __IOM uint32 BORRSTF    : 1;            /*!< [21..21] BOR reset flag                                                   */
      __IOM uint32 PINRSTF    : 1;            /*!< [22..22] Pin reset flag (NRST)                                            */
      __IOM uint32 PORRSTF    : 1;            /*!< [23..23] POR/PDR reset flag                                               */
      __IOM uint32 SFTRSTF    : 1;            /*!< [24..24] System reset from CPU reset flag                                 */
            uint32            : 1;
      __IOM uint32 IWDG1RSTF  : 1;            /*!< [26..26] Independent Watchdog reset flag                                  */
            uint32            : 1;
      __IOM uint32 WWDG1RSTF  : 1;            /*!< [28..28] Window Watchdog reset flag                                       */
            uint32            : 1;
      __IOM uint32 LPWRRSTF   : 1;            /*!< [30..30] Reset due to illegal D1 DStandby or CPU CStop flag               */
            uint32            : 1;
    } bit;
  } C1_RSR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000134) RCC AHB3 Clock Register                                    */
    
    struct {
      __IOM uint32 MDMAEN     : 1;            /*!< [0..0] MDMA Peripheral Clock Enable                                       */
            uint32            : 3;
      __IOM uint32 DMA2DEN    : 1;            /*!< [4..4] DMA2D Peripheral Clock Enable                                      */
      __IOM uint32 JPGDECEN   : 1;            /*!< [5..5] JPGDEC Peripheral Clock Enable                                     */
            uint32            : 6;
      __IOM uint32 FMCEN      : 1;            /*!< [12..12] FMC Peripheral Clocks Enable                                     */
            uint32            : 1;
      __IOM uint32 QSPIEN     : 1;            /*!< [14..14] QUADSPI and QUADSPI Delay Clock Enable                           */
            uint32            : 1;
      __IOM uint32 SDMMC1EN   : 1;            /*!< [16..16] SDMMC1 and SDMMC1 Delay Clock Enable                             */
            uint32            : 15;
    } bit;
  } C1_AHB3ENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000138) RCC AHB1 Clock Register                                    */
    
    struct {
      __IOM uint32 DMA1EN     : 1;            /*!< [0..0] DMA1 Clock Enable                                                  */
      __IOM uint32 DMA2EN     : 1;            /*!< [1..1] DMA2 Clock Enable                                                  */
            uint32            : 3;
      __IOM uint32 ADC12EN    : 1;            /*!< [5..5] ADC1/2 Peripheral Clocks Enable                                    */
            uint32            : 9;
      __IOM uint32 ETH1MACEN  : 1;            /*!< [15..15] Ethernet MAC bus interface Clock Enable                          */
      __IOM uint32 ETH1TXEN   : 1;            /*!< [16..16] Ethernet Transmission Clock Enable                               */
      __IOM uint32 ETH1RXEN   : 1;            /*!< [17..17] Ethernet Reception Clock Enable                                  */
            uint32            : 7;
      __IOM uint32 USB1OTGEN  : 1;            /*!< [25..25] USB1OTG Peripheral Clocks Enable                                 */
      __IOM uint32 USB1ULPIEN : 1;            /*!< [26..26] USB_PHY1 Clocks Enable                                           */
      __IOM uint32 USB2OTGEN  : 1;            /*!< [27..27] USB2OTG Peripheral Clocks Enable                                 */
      __IOM uint32 USB2ULPIEN : 1;            /*!< [28..28] USB_PHY2 Clocks Enable                                           */
            uint32            : 3;
    } bit;
  } C1_AHB1ENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000013C) RCC AHB2 Clock Register                                    */
    
    struct {
      __IOM uint32 CAMITFEN   : 1;            /*!< [0..0] CAMITF peripheral clock enable                                     */
            uint32            : 3;
      __IOM uint32 CRYPTEN    : 1;            /*!< [4..4] CRYPT peripheral clock enable                                      */
      __IOM uint32 HASHEN     : 1;            /*!< [5..5] HASH peripheral clock enable                                       */
      __IOM uint32 RNGEN      : 1;            /*!< [6..6] RNG peripheral clocks enable                                       */
            uint32            : 2;
      __IOM uint32 SDMMC2EN   : 1;            /*!< [9..9] SDMMC2 and SDMMC2 delay clock enable                               */
            uint32            : 19;
      __IOM uint32 SRAM1EN    : 1;            /*!< [29..29] SRAM1 block enable                                               */
      __IOM uint32 SRAM2EN    : 1;            /*!< [30..30] SRAM2 block enable                                               */
      __IOM uint32 SRAM3EN    : 1;            /*!< [31..31] SRAM3 block enable                                               */
    } bit;
  } C1_AHB2ENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000140) RCC AHB4 Clock Register                                    */
    
    struct {
      __IOM uint32 GPIOAEN    : 1;            /*!< [0..0] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOBEN    : 1;            /*!< [1..1] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOCEN    : 1;            /*!< [2..2] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIODEN    : 1;            /*!< [3..3] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOEEN    : 1;            /*!< [4..4] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOFEN    : 1;            /*!< [5..5] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOGEN    : 1;            /*!< [6..6] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOHEN    : 1;            /*!< [7..7] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOIEN    : 1;            /*!< [8..8] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOJEN    : 1;            /*!< [9..9] 0GPIO peripheral clock enable                                      */
      __IOM uint32 GPIOKEN    : 1;            /*!< [10..10] 0GPIO peripheral clock enable                                    */
            uint32            : 8;
      __IOM uint32 CRCEN      : 1;            /*!< [19..19] CRC peripheral clock enable                                      */
            uint32            : 1;
      __IOM uint32 BDMAEN     : 1;            /*!< [21..21] BDMA and DMAMUX2 Clock Enable                                    */
            uint32            : 2;
      __IOM uint32 ADC3EN     : 1;            /*!< [24..24] ADC3 Peripheral Clocks Enable                                    */
      __IOM uint32 HSEMEN     : 1;            /*!< [25..25] HSEM peripheral clock enable                                     */
            uint32            : 2;
      __IOM uint32 BKPRAMEN   : 1;            /*!< [28..28] Backup RAM Clock Enable                                          */
            uint32            : 3;
    } bit;
  } C1_AHB4ENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000144) RCC APB3 Clock Register                                    */
    
    struct {
            uint32            : 3;
      __IOM uint32 LTDCEN     : 1;            /*!< [3..3] LTDC peripheral clock enable                                       */
            uint32            : 2;
      __IOM uint32 WWDG1EN    : 1;            /*!< [6..6] WWDG1 Clock Enable                                                 */
            uint32            : 25;
    } bit;
  } C1_APB3ENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000148) RCC APB1 Clock Register                                    */
    
    struct {
      __IOM uint32 TIM2EN     : 1;            /*!< [0..0] TIM peripheral clock enable                                        */
      __IOM uint32 TIM3EN     : 1;            /*!< [1..1] TIM peripheral clock enable                                        */
      __IOM uint32 TIM4EN     : 1;            /*!< [2..2] TIM peripheral clock enable                                        */
      __IOM uint32 TIM5EN     : 1;            /*!< [3..3] TIM peripheral clock enable                                        */
      __IOM uint32 TIM6EN     : 1;            /*!< [4..4] TIM peripheral clock enable                                        */
      __IOM uint32 TIM7EN     : 1;            /*!< [5..5] TIM peripheral clock enable                                        */
      __IOM uint32 TIM12EN    : 1;            /*!< [6..6] TIM peripheral clock enable                                        */
      __IOM uint32 TIM13EN    : 1;            /*!< [7..7] TIM peripheral clock enable                                        */
      __IOM uint32 TIM14EN    : 1;            /*!< [8..8] TIM peripheral clock enable                                        */
      __IOM uint32 LPTIM1EN   : 1;            /*!< [9..9] LPTIM1 Peripheral Clocks Enable                                    */
            uint32            : 4;
      __IOM uint32 SPI2EN     : 1;            /*!< [14..14] SPI2 Peripheral Clocks Enable                                    */
      __IOM uint32 SPI3EN     : 1;            /*!< [15..15] SPI3 Peripheral Clocks Enable                                    */
      __IOM uint32 SPDIFRXEN  : 1;            /*!< [16..16] SPDIFRX Peripheral Clocks Enable                                 */
      __IOM uint32 USART2EN   : 1;            /*!< [17..17] USART2 Peripheral Clocks Enable                                  */
      __IOM uint32 USART3EN   : 1;            /*!< [18..18] USART3 Peripheral Clocks Enable                                  */
      __IOM uint32 UART4EN    : 1;            /*!< [19..19] UART4 Peripheral Clocks Enable                                   */
      __IOM uint32 UART5EN    : 1;            /*!< [20..20] UART5 Peripheral Clocks Enable                                   */
      __IOM uint32 I2C1EN     : 1;            /*!< [21..21] I2C1 Peripheral Clocks Enable                                    */
      __IOM uint32 I2C2EN     : 1;            /*!< [22..22] I2C2 Peripheral Clocks Enable                                    */
      __IOM uint32 I2C3EN     : 1;            /*!< [23..23] I2C3 Peripheral Clocks Enable                                    */
            uint32            : 3;
      __IOM uint32 HDMICECEN  : 1;            /*!< [27..27] HDMI-CEC peripheral clock enable                                 */
            uint32            : 1;
      __IOM uint32 DAC12EN    : 1;            /*!< [29..29] DAC1&2 peripheral clock enable                                   */
      __IOM uint32 USART7EN   : 1;            /*!< [30..30] USART7 Peripheral Clocks Enable                                  */
      __IOM uint32 USART8EN   : 1;            /*!< [31..31] USART8 Peripheral Clocks Enable                                  */
    } bit;
  } C1_APB1LENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000014C) RCC APB1 Clock Register                                    */
    
    struct {
            uint32            : 1;
      __IOM uint32 CRSEN      : 1;            /*!< [1..1] Clock Recovery System peripheral clock enable                      */
      __IOM uint32 SWPEN      : 1;            /*!< [2..2] SWPMI Peripheral Clocks Enable                                     */
            uint32            : 1;
      __IOM uint32 OPAMPEN    : 1;            /*!< [4..4] OPAMP peripheral clock enable                                      */
      __IOM uint32 MDIOSEN    : 1;            /*!< [5..5] MDIOS peripheral clock enable                                      */
            uint32            : 2;
      __IOM uint32 FDCANEN    : 1;            /*!< [8..8] FDCAN Peripheral Clocks Enable                                     */
            uint32            : 23;
    } bit;
  } C1_APB1HENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000150) RCC APB2 Clock Register                                    */
    
    struct {
      __IOM uint32 TIM1EN     : 1;            /*!< [0..0] TIM1 peripheral clock enable                                       */
      __IOM uint32 TIM8EN     : 1;            /*!< [1..1] TIM8 peripheral clock enable                                       */
            uint32            : 2;
      __IOM uint32 USART1EN   : 1;            /*!< [4..4] USART1 Peripheral Clocks Enable                                    */
      __IOM uint32 USART6EN   : 1;            /*!< [5..5] USART6 Peripheral Clocks Enable                                    */
            uint32            : 6;
      __IOM uint32 SPI1EN     : 1;            /*!< [12..12] SPI1 Peripheral Clocks Enable                                    */
      __IOM uint32 SPI4EN     : 1;            /*!< [13..13] SPI4 Peripheral Clocks Enable                                    */
            uint32            : 2;
      __IOM uint32 TIM15EN    : 1;            /*!< [16..16] TIM15 peripheral clock enable                                    */
      __IOM uint32 TIM16EN    : 1;            /*!< [17..17] TIM16 peripheral clock enable                                    */
      __IOM uint32 TIM17EN    : 1;            /*!< [18..18] TIM17 peripheral clock enable                                    */
            uint32            : 1;
      __IOM uint32 SPI5EN     : 1;            /*!< [20..20] SPI5 Peripheral Clocks Enable                                    */
            uint32            : 1;
      __IOM uint32 SAI1EN     : 1;            /*!< [22..22] SAI1 Peripheral Clocks Enable                                    */
      __IOM uint32 SAI2EN     : 1;            /*!< [23..23] SAI2 Peripheral Clocks Enable                                    */
      __IOM uint32 SAI3EN     : 1;            /*!< [24..24] SAI3 Peripheral Clocks Enable                                    */
            uint32            : 3;
      __IOM uint32 DFSDM1EN   : 1;            /*!< [28..28] DFSDM1 Peripheral Clocks Enable                                  */
      __IOM uint32 HRTIMEN    : 1;            /*!< [29..29] HRTIM peripheral clock enable                                    */
            uint32            : 2;
    } bit;
  } C1_APB2ENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000154) RCC APB4 Clock Register                                    */
    
    struct {
            uint32            : 1;
      __IOM uint32 SYSCFGEN   : 1;            /*!< [1..1] SYSCFG peripheral clock enable                                     */
            uint32            : 1;
      __IOM uint32 LPUART1EN  : 1;            /*!< [3..3] LPUART1 Peripheral Clocks Enable                                   */
            uint32            : 1;
      __IOM uint32 SPI6EN     : 1;            /*!< [5..5] SPI6 Peripheral Clocks Enable                                      */
            uint32            : 1;
      __IOM uint32 I2C4EN     : 1;            /*!< [7..7] I2C4 Peripheral Clocks Enable                                      */
            uint32            : 1;
      __IOM uint32 LPTIM2EN   : 1;            /*!< [9..9] LPTIM2 Peripheral Clocks Enable                                    */
      __IOM uint32 LPTIM3EN   : 1;            /*!< [10..10] LPTIM3 Peripheral Clocks Enable                                  */
      __IOM uint32 LPTIM4EN   : 1;            /*!< [11..11] LPTIM4 Peripheral Clocks Enable                                  */
      __IOM uint32 LPTIM5EN   : 1;            /*!< [12..12] LPTIM5 Peripheral Clocks Enable                                  */
            uint32            : 1;
      __IOM uint32 COMP12EN   : 1;            /*!< [14..14] COMP1/2 peripheral clock enable                                  */
      __IOM uint32 VREFEN     : 1;            /*!< [15..15] VREF peripheral clock enable                                     */
      __IOM uint32 RTCAPBEN   : 1;            /*!< [16..16] RTC APB Clock Enable                                             */
            uint32            : 4;
      __IOM uint32 SAI4EN     : 1;            /*!< [21..21] SAI4 Peripheral Clocks Enable                                    */
            uint32            : 10;
    } bit;
  } C1_APB4ENR;
  __IM  uint32  RESERVED11;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000015C) RCC AHB3 Sleep Clock Register                              */
    
    struct {
      __IOM uint32 MDMALPEN   : 1;            /*!< [0..0] MDMA Clock Enable During CSleep Mode                               */
            uint32            : 3;
      __IOM uint32 DMA2DLPEN  : 1;            /*!< [4..4] DMA2D Clock Enable During CSleep Mode                              */
      __IOM uint32 JPGDECLPEN : 1;            /*!< [5..5] JPGDEC Clock Enable During CSleep Mode                             */
            uint32            : 2;
      __IOM uint32 FLITFLPEN  : 1;            /*!< [8..8] FLITF Clock Enable During CSleep Mode                              */
            uint32            : 3;
      __IOM uint32 FMCLPEN    : 1;            /*!< [12..12] FMC Peripheral Clocks Enable During CSleep Mode                  */
            uint32            : 1;
      __IOM uint32 QSPILPEN   : 1;            /*!< [14..14] QUADSPI and QUADSPI Delay Clock Enable During CSleep
                                                     Mode                                                                      */
            uint32            : 1;
      __IOM uint32 SDMMC1LPEN : 1;            /*!< [16..16] SDMMC1 and SDMMC1 Delay Clock Enable During CSleep
                                                     Mode                                                                      */
            uint32            : 11;
      __IOM uint32 D1DTCM1LPEN : 1;           /*!< [28..28] D1DTCM1 Block Clock Enable During CSleep mode                    */
      __IOM uint32 DTCM2LPEN  : 1;            /*!< [29..29] D1 DTCM2 Block Clock Enable During CSleep mode                   */
      __IOM uint32 ITCMLPEN   : 1;            /*!< [30..30] D1ITCM Block Clock Enable During CSleep mode                     */
      __IOM uint32 AXISRAMLPEN : 1;           /*!< [31..31] AXISRAM Block Clock Enable During CSleep mode                    */
    } bit;
  } C1_AHB3LPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000160) RCC AHB1 Sleep Clock Register                              */
    
    struct {
      __IOM uint32 DMA1LPEN   : 1;            /*!< [0..0] DMA1 Clock Enable During CSleep Mode                               */
      __IOM uint32 DMA2LPEN   : 1;            /*!< [1..1] DMA2 Clock Enable During CSleep Mode                               */
            uint32            : 3;
      __IOM uint32 ADC12LPEN  : 1;            /*!< [5..5] ADC1/2 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 9;
      __IOM uint32 ETH1MACLPEN : 1;           /*!< [15..15] Ethernet MAC bus interface Clock Enable During CSleep
                                                     Mode                                                                      */
      __IOM uint32 ETH1TXLPEN : 1;            /*!< [16..16] Ethernet Transmission Clock Enable During CSleep Mode            */
      __IOM uint32 ETH1RXLPEN : 1;            /*!< [17..17] Ethernet Reception Clock Enable During CSleep Mode               */
            uint32            : 7;
      __IOM uint32 USB1OTGLPEN : 1;           /*!< [25..25] USB1OTG peripheral clock enable during CSleep mode               */
      __IOM uint32 USB1ULPILPEN : 1;          /*!< [26..26] USB_PHY1 clock enable during CSleep mode                         */
      __IOM uint32 USB2OTGLPEN : 1;           /*!< [27..27] USB2OTG peripheral clock enable during CSleep mode               */
      __IOM uint32 USB2ULPILPEN : 1;          /*!< [28..28] USB_PHY2 clocks enable during CSleep mode                        */
            uint32            : 3;
    } bit;
  } C1_AHB1LPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000164) RCC AHB2 Sleep Clock Register                              */
    
    struct {
      __IOM uint32 CAMITFLPEN : 1;            /*!< [0..0] CAMITF peripheral clock enable during CSleep mode                  */
            uint32            : 3;
      __IOM uint32 CRYPTLPEN  : 1;            /*!< [4..4] CRYPT peripheral clock enable during CSleep mode                   */
      __IOM uint32 HASHLPEN   : 1;            /*!< [5..5] HASH peripheral clock enable during CSleep mode                    */
      __IOM uint32 RNGLPEN    : 1;            /*!< [6..6] RNG peripheral clock enable during CSleep mode                     */
            uint32            : 2;
      __IOM uint32 SDMMC2LPEN : 1;            /*!< [9..9] SDMMC2 and SDMMC2 Delay Clock Enable During CSleep Mode            */
            uint32            : 19;
      __IOM uint32 SRAM1LPEN  : 1;            /*!< [29..29] SRAM1 Clock Enable During CSleep Mode                            */
      __IOM uint32 SRAM2LPEN  : 1;            /*!< [30..30] SRAM2 Clock Enable During CSleep Mode                            */
      __IOM uint32 SRAM3LPEN  : 1;            /*!< [31..31] SRAM3 Clock Enable During CSleep Mode                            */
    } bit;
  } C1_AHB2LPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000168) RCC AHB4 Sleep Clock Register                              */
    
    struct {
      __IOM uint32 GPIOALPEN  : 1;            /*!< [0..0] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOBLPEN  : 1;            /*!< [1..1] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOCLPEN  : 1;            /*!< [2..2] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIODLPEN  : 1;            /*!< [3..3] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOELPEN  : 1;            /*!< [4..4] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOFLPEN  : 1;            /*!< [5..5] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOGLPEN  : 1;            /*!< [6..6] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOHLPEN  : 1;            /*!< [7..7] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOILPEN  : 1;            /*!< [8..8] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOJLPEN  : 1;            /*!< [9..9] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32 GPIOKLPEN  : 1;            /*!< [10..10] GPIO peripheral clock enable during CSleep mode                  */
            uint32            : 8;
      __IOM uint32 CRCLPEN    : 1;            /*!< [19..19] CRC peripheral clock enable during CSleep mode                   */
            uint32            : 1;
      __IOM uint32 BDMALPEN   : 1;            /*!< [21..21] BDMA Clock Enable During CSleep Mode                             */
            uint32            : 2;
      __IOM uint32 ADC3LPEN   : 1;            /*!< [24..24] ADC3 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 3;
      __IOM uint32 BKPRAMLPEN : 1;            /*!< [28..28] Backup RAM Clock Enable During CSleep Mode                       */
      __IOM uint32 SRAM4LPEN  : 1;            /*!< [29..29] SRAM4 Clock Enable During CSleep Mode                            */
            uint32            : 2;
    } bit;
  } C1_AHB4LPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000016C) RCC APB3 Sleep Clock Register                              */
    
    struct {
            uint32            : 3;
      __IOM uint32 LTDCLPEN   : 1;            /*!< [3..3] LTDC peripheral clock enable during CSleep mode                    */
            uint32            : 2;
      __IOM uint32 WWDG1LPEN  : 1;            /*!< [6..6] WWDG1 Clock Enable During CSleep Mode                              */
            uint32            : 25;
    } bit;
  } C1_APB3LPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000170) RCC APB1 Low Sleep Clock Register                          */
    
    struct {
      __IOM uint32 TIM2LPEN   : 1;            /*!< [0..0] TIM2 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM3LPEN   : 1;            /*!< [1..1] TIM3 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM4LPEN   : 1;            /*!< [2..2] TIM4 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM5LPEN   : 1;            /*!< [3..3] TIM5 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM6LPEN   : 1;            /*!< [4..4] TIM6 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM7LPEN   : 1;            /*!< [5..5] TIM7 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM12LPEN  : 1;            /*!< [6..6] TIM12 peripheral clock enable during CSleep mode                   */
      __IOM uint32 TIM13LPEN  : 1;            /*!< [7..7] TIM13 peripheral clock enable during CSleep mode                   */
      __IOM uint32 TIM14LPEN  : 1;            /*!< [8..8] TIM14 peripheral clock enable during CSleep mode                   */
      __IOM uint32 LPTIM1LPEN : 1;            /*!< [9..9] LPTIM1 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 4;
      __IOM uint32 SPI2LPEN   : 1;            /*!< [14..14] SPI2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 SPI3LPEN   : 1;            /*!< [15..15] SPI3 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 SPDIFRXLPEN : 1;           /*!< [16..16] SPDIFRX Peripheral Clocks Enable During CSleep Mode              */
      __IOM uint32 USART2LPEN : 1;            /*!< [17..17] USART2 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32 USART3LPEN : 1;            /*!< [18..18] USART3 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32 UART4LPEN  : 1;            /*!< [19..19] UART4 Peripheral Clocks Enable During CSleep Mode                */
      __IOM uint32 UART5LPEN  : 1;            /*!< [20..20] UART5 Peripheral Clocks Enable During CSleep Mode                */
      __IOM uint32 I2C1LPEN   : 1;            /*!< [21..21] I2C1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 I2C2LPEN   : 1;            /*!< [22..22] I2C2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 I2C3LPEN   : 1;            /*!< [23..23] I2C3 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 3;
      __IOM uint32 HDMICECLPEN : 1;           /*!< [27..27] HDMI-CEC Peripheral Clocks Enable During CSleep Mode             */
            uint32            : 1;
      __IOM uint32 DAC12LPEN  : 1;            /*!< [29..29] DAC1/2 peripheral clock enable during CSleep mode                */
      __IOM uint32 USART7LPEN : 1;            /*!< [30..30] USART7 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32 USART8LPEN : 1;            /*!< [31..31] USART8 Peripheral Clocks Enable During CSleep Mode               */
    } bit;
  } C1_APB1LLPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000174) RCC APB1 High Sleep Clock Register                         */
    
    struct {
            uint32            : 1;
      __IOM uint32 CRSLPEN    : 1;            /*!< [1..1] Clock Recovery System peripheral clock enable during
                                                     CSleep mode                                                               */
      __IOM uint32 SWPLPEN    : 1;            /*!< [2..2] SWPMI Peripheral Clocks Enable During CSleep Mode                  */
            uint32            : 1;
      __IOM uint32 OPAMPLPEN  : 1;            /*!< [4..4] OPAMP peripheral clock enable during CSleep mode                   */
      __IOM uint32 MDIOSLPEN  : 1;            /*!< [5..5] MDIOS peripheral clock enable during CSleep mode                   */
            uint32            : 2;
      __IOM uint32 FDCANLPEN  : 1;            /*!< [8..8] FDCAN Peripheral Clocks Enable During CSleep Mode                  */
            uint32            : 23;
    } bit;
  } C1_APB1HLPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000178) RCC APB2 Sleep Clock Register                              */
    
    struct {
      __IOM uint32 TIM1LPEN   : 1;            /*!< [0..0] TIM1 peripheral clock enable during CSleep mode                    */
      __IOM uint32 TIM8LPEN   : 1;            /*!< [1..1] TIM8 peripheral clock enable during CSleep mode                    */
            uint32            : 2;
      __IOM uint32 USART1LPEN : 1;            /*!< [4..4] USART1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 USART6LPEN : 1;            /*!< [5..5] USART6 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 6;
      __IOM uint32 SPI1LPEN   : 1;            /*!< [12..12] SPI1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 SPI4LPEN   : 1;            /*!< [13..13] SPI4 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 2;
      __IOM uint32 TIM15LPEN  : 1;            /*!< [16..16] TIM15 peripheral clock enable during CSleep mode                 */
      __IOM uint32 TIM16LPEN  : 1;            /*!< [17..17] TIM16 peripheral clock enable during CSleep mode                 */
      __IOM uint32 TIM17LPEN  : 1;            /*!< [18..18] TIM17 peripheral clock enable during CSleep mode                 */
            uint32            : 1;
      __IOM uint32 SPI5LPEN   : 1;            /*!< [20..20] SPI5 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 1;
      __IOM uint32 SAI1LPEN   : 1;            /*!< [22..22] SAI1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 SAI2LPEN   : 1;            /*!< [23..23] SAI2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 SAI3LPEN   : 1;            /*!< [24..24] SAI3 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 3;
      __IOM uint32 DFSDM1LPEN : 1;            /*!< [28..28] DFSDM1 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32 HRTIMLPEN  : 1;            /*!< [29..29] HRTIM peripheral clock enable during CSleep mode                 */
            uint32            : 2;
    } bit;
  } C1_APB2LPENR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000017C) RCC APB4 Sleep Clock Register                              */
    
    struct {
            uint32            : 1;
      __IOM uint32 SYSCFGLPEN : 1;            /*!< [1..1] SYSCFG peripheral clock enable during CSleep mode                  */
            uint32            : 1;
      __IOM uint32 LPUART1LPEN : 1;           /*!< [3..3] LPUART1 Peripheral Clocks Enable During CSleep Mode                */
            uint32            : 1;
      __IOM uint32 SPI6LPEN   : 1;            /*!< [5..5] SPI6 Peripheral Clocks Enable During CSleep Mode                   */
            uint32            : 1;
      __IOM uint32 I2C4LPEN   : 1;            /*!< [7..7] I2C4 Peripheral Clocks Enable During CSleep Mode                   */
            uint32            : 1;
      __IOM uint32 LPTIM2LPEN : 1;            /*!< [9..9] LPTIM2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32 LPTIM3LPEN : 1;            /*!< [10..10] LPTIM3 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32 LPTIM4LPEN : 1;            /*!< [11..11] LPTIM4 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32 LPTIM5LPEN : 1;            /*!< [12..12] LPTIM5 Peripheral Clocks Enable During CSleep Mode               */
            uint32            : 1;
      __IOM uint32 COMP12LPEN : 1;            /*!< [14..14] COMP1/2 peripheral clock enable during CSleep mode               */
      __IOM uint32 VREFLPEN   : 1;            /*!< [15..15] VREF peripheral clock enable during CSleep mode                  */
      __IOM uint32 RTCAPBLPEN : 1;            /*!< [16..16] RTC APB Clock Enable During CSleep Mode                          */
            uint32            : 4;
      __IOM uint32 SAI4LPEN   : 1;            /*!< [21..21] SAI4 Peripheral Clocks Enable During CSleep Mode                 */
            uint32            : 10;
    } bit;
  } C1_APB4LPENR;
} RCC_Type;                                     /*!< Size = 384 (0x180)                                                        */

/* =========================================================================================================================== */
/* ================                                           Flash                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief Flash (Flash)
  */

typedef struct{                                /*!< (@ 0x52002000) Flash Structure                                            */

  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000000) Access control register                                    */
    
    struct {
      __IOM uint32 LATENCY    : 3;            /*!< [2..0] Read latency                                                       */
            uint32            : 1;
      __IOM uint32 WRHIGHFREQ : 2;            /*!< [5..4] Flash signal delay                                                 */
            uint32            : 26;
    } bit;
  } ACR;

} Flash_Type;                                   /*!< Size = 356 (0x164)                                                        */


/* =========================================================================================================================== */
/* ================                                            SCB                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief System control block (SCB)
  */

typedef struct {                                /*!< (@ 0xE000ED00) SCB Structure                                              */
  
  union {
    __IM  uint32 reg;                         /*!< (@ 0x00000000) CPUID base register                                        */
    
    struct {
      __IM  uint32 Revision   : 4;            /*!< [3..0] Revision number                                                    */
      __IM  uint32 PartNo     : 12;           /*!< [15..4] Part number of the processor                                      */
      __IM  uint32 Constant   : 4;            /*!< [19..16] Reads as 0xF                                                     */
      __IM  uint32 Variant    : 4;            /*!< [23..20] Variant number                                                   */
      __IM  uint32 Implementer : 8;           /*!< [31..24] Implementer code                                                 */
    } bit;
  } CPUID;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000004) Interrupt control and state register                       */
    
    struct {
      __IOM uint32 VECTACTIVE : 9;            /*!< [8..0] Active vector                                                      */
            uint32            : 2;
      __IOM uint32 RETTOBASE  : 1;            /*!< [11..11] Return to base level                                             */
      __IOM uint32 VECTPENDING : 7;           /*!< [18..12] Pending vector                                                   */
            uint32            : 3;
      __IOM uint32 ISRPENDING : 1;            /*!< [22..22] Interrupt pending flag                                           */
            uint32            : 2;
      __IOM uint32 PENDSTCLR  : 1;            /*!< [25..25] SysTick exception clear-pending bit                              */
      __IOM uint32 PENDSTSET  : 1;            /*!< [26..26] SysTick exception set-pending bit                                */
      __IOM uint32 PENDSVCLR  : 1;            /*!< [27..27] PendSV clear-pending bit                                         */
      __IOM uint32 PENDSVSET  : 1;            /*!< [28..28] PendSV set-pending bit                                           */
            uint32            : 2;
      __IOM uint32 NMIPENDSET : 1;            /*!< [31..31] NMI set-pending bit.                                             */
    } bit;
  } ICSR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000008) Vector table offset register                               */
    
    struct {
            uint32            : 9;
      __IOM uint32 TBLOFF     : 21;           /*!< [29..9] Vector table base offset field                                    */
            uint32            : 2;
    } bit;
  } VTOR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000000C) Application interrupt and reset control register           */
    
    struct {
      __IOM uint32 VECTRESET  : 1;            /*!< [0..0] VECTRESET                                                          */
      __IOM uint32 VECTCLRACTIVE : 1;         /*!< [1..1] VECTCLRACTIVE                                                      */
      __IOM uint32 SYSRESETREQ : 1;           /*!< [2..2] SYSRESETREQ                                                        */
            uint32            : 5;
      __IOM uint32 PRIGROUP   : 3;            /*!< [10..8] PRIGROUP                                                          */
            uint32            : 4;
      __IOM uint32 ENDIANESS  : 1;            /*!< [15..15] ENDIANESS                                                        */
      __IOM uint32 VECTKEYSTAT : 16;          /*!< [31..16] Register key                                                     */
    } bit;
  } AIRCR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000010) System control register                                    */
    
    struct {
            uint32            : 1;
      __IOM uint32 SLEEPONEXIT : 1;           /*!< [1..1] SLEEPONEXIT                                                        */
      __IOM uint32 SLEEPDEEP  : 1;            /*!< [2..2] SLEEPDEEP                                                          */
            uint32            : 1;
      __IOM uint32 SEVEONPEND : 1;            /*!< [4..4] Send Event on Pending bit                                          */
            uint32            : 27;
    } bit;
  } SCR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000014) Configuration and control register                         */
    
    struct {
      __IOM uint32 NONBASETHRDENA : 1;        /*!< [0..0] Configures how the processor enters Thread mode                    */
      __IOM uint32 USERSETMPEND : 1;          /*!< [1..1] USERSETMPEND                                                       */
            uint32            : 1;
      __IOM uint32 UNALIGN__TRP : 1;          /*!< [3..3] UNALIGN_ TRP                                                       */
      __IOM uint32 DIV_0_TRP  : 1;            /*!< [4..4] DIV_0_TRP                                                          */
            uint32            : 3;
      __IOM uint32 BFHFNMIGN  : 1;            /*!< [8..8] BFHFNMIGN                                                          */
      __IOM uint32 STKALIGN   : 1;            /*!< [9..9] STKALIGN                                                           */
            uint32            : 6;
      __IOM uint32 DC         : 1;            /*!< [16..16] DC                                                               */
      __IOM uint32 IC         : 1;            /*!< [17..17] IC                                                               */
      __IOM uint32 BP         : 1;            /*!< [18..18] BP                                                               */
            uint32            : 13;
    } bit;
  } CCR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000018) System handler priority registers                          */
    
    struct {
      __IOM uint32 PRI_4      : 8;            /*!< [7..0] Priority of system handler 4                                       */
      __IOM uint32 PRI_5      : 8;            /*!< [15..8] Priority of system handler 5                                      */
      __IOM uint32 PRI_6      : 8;            /*!< [23..16] Priority of system handler 6                                     */
            uint32            : 8;
    } bit;
  } SHPR1;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000001C) System handler priority registers                          */
    
    struct {
            uint32            : 24;
      __IOM uint32 PRI_11     : 8;            /*!< [31..24] Priority of system handler 11                                    */
    } bit;
  } SHPR2;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000020) System handler priority registers                          */
    
    struct {
            uint32            : 16;
      __IOM uint32 PRI_14     : 8;            /*!< [23..16] Priority of system handler 14                                    */
      __IOM uint32 PRI_15     : 8;            /*!< [31..24] Priority of system handler 15                                    */
    } bit;
  } SHPR3;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000024) System handler control and state register                  */
    
    struct {
      __IOM uint32 MEMFAULTACT : 1;           /*!< [0..0] Memory management fault exception active bit                       */
      __IOM uint32 BUSFAULTACT : 1;           /*!< [1..1] Bus fault exception active bit                                     */
            uint32            : 1;
      __IOM uint32 USGFAULTACT : 1;           /*!< [3..3] Usage fault exception active bit                                   */
            uint32            : 3;
      __IOM uint32 SVCALLACT  : 1;            /*!< [7..7] SVC call active bit                                                */
      __IOM uint32 MONITORACT : 1;            /*!< [8..8] Debug monitor active bit                                           */
            uint32            : 1;
      __IOM uint32 PENDSVACT  : 1;            /*!< [10..10] PendSV exception active bit                                      */
      __IOM uint32 SYSTICKACT : 1;            /*!< [11..11] SysTick exception active bit                                     */
      __IOM uint32 USGFAULTPENDED : 1;        /*!< [12..12] Usage fault exception pending bit                                */
      __IOM uint32 MEMFAULTPENDED : 1;        /*!< [13..13] Memory management fault exception pending bit                    */
      __IOM uint32 BUSFAULTPENDED : 1;        /*!< [14..14] Bus fault exception pending bit                                  */
      __IOM uint32 SVCALLPENDED : 1;          /*!< [15..15] SVC call pending bit                                             */
      __IOM uint32 MEMFAULTENA : 1;           /*!< [16..16] Memory management fault enable bit                               */
      __IOM uint32 BUSFAULTENA : 1;           /*!< [17..17] Bus fault enable bit                                             */
      __IOM uint32 USGFAULTENA : 1;           /*!< [18..18] Usage fault enable bit                                           */
            uint32            : 13;
    } bit;
  } SHCRS;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000028) Configurable fault status register                         */
    
    struct {
      __IOM uint32 IACCVIOL   : 1;            /*!< [0..0] IACCVIOL                                                           */
      __IOM uint32 DACCVIOL   : 1;            /*!< [1..1] DACCVIOL                                                           */
            uint32            : 1;
      __IOM uint32 MUNSTKERR  : 1;            /*!< [3..3] MUNSTKERR                                                          */
      __IOM uint32 MSTKERR    : 1;            /*!< [4..4] MSTKERR                                                            */
      __IOM uint32 MLSPERR    : 1;            /*!< [5..5] MLSPERR                                                            */
            uint32            : 1;
      __IOM uint32 MMARVALID  : 1;            /*!< [7..7] MMARVALID                                                          */
      __IOM uint32 IBUSERR    : 1;            /*!< [8..8] Instruction bus error                                              */
      __IOM uint32 PRECISERR  : 1;            /*!< [9..9] Precise data bus error                                             */
      __IOM uint32 IMPRECISERR : 1;           /*!< [10..10] Imprecise data bus error                                         */
      __IOM uint32 UNSTKERR   : 1;            /*!< [11..11] Bus fault on unstacking for a return from exception              */
      __IOM uint32 STKERR     : 1;            /*!< [12..12] Bus fault on stacking for exception entry                        */
      __IOM uint32 LSPERR     : 1;            /*!< [13..13] Bus fault on floating-point lazy state preservation              */
            uint32            : 1;
      __IOM uint32 BFARVALID  : 1;            /*!< [15..15] Bus Fault Address Register (BFAR) valid flag                     */
      __IOM uint32 UNDEFINSTR : 1;            /*!< [16..16] Undefined instruction usage fault                                */
      __IOM uint32 INVSTATE   : 1;            /*!< [17..17] Invalid state usage fault                                        */
      __IOM uint32 INVPC      : 1;            /*!< [18..18] Invalid PC load usage fault                                      */
      __IOM uint32 NOCP       : 1;            /*!< [19..19] No coprocessor usage fault.                                      */
            uint32            : 4;
      __IOM uint32 UNALIGNED  : 1;            /*!< [24..24] Unaligned access usage fault                                     */
      __IOM uint32 DIVBYZERO  : 1;            /*!< [25..25] Divide by zero usage fault                                       */
            uint32            : 6;
    } bit;
  } CFSR_UFSR_BFSR_MMFSR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x0000002C) Hard fault status register                                 */
    
    struct {
            uint32            : 1;
      __IOM uint32 VECTTBL    : 1;            /*!< [1..1] Vector table hard fault                                            */
            uint32            : 28;
      __IOM uint32 FORCED     : 1;            /*!< [30..30] Forced hard fault                                                */
      __IOM uint32 DEBUG_VT   : 1;            /*!< [31..31] Reserved for Debug use                                           */
    } bit;
  } HFSR;
  __IM  uint32  RESERVED;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000034) Memory management fault address register                   */
    
    struct {
      __IOM uint32 ADDRESS    : 32;           /*!< [31..0] Memory management fault address                                   */
    } bit;
  } MMFAR;
  
  union {
    __IOM uint32 reg;                         /*!< (@ 0x00000038) Bus fault address register                                 */
    
    struct {
      __IOM uint32 ADDRESS    : 32;           /*!< [31..0] Bus fault address                                                 */
    } bit;
  } BFAR;
} SCB_Type;                                     /*!< Size = 60 (0x3c)                                                          */



/** @} */ /* End of group Device_Peripheral_peripherals */


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */

#define RCC_BASE                    0x58024400UL
#define Flash_BASE                  0x52002000UL
#define SCB_BASE                    0xE000ED00UL

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define RCC                         ((RCC_Type*)               RCC_BASE)
#define Flash                       ((Flash_Type*)             Flash_BASE)
#define SCB                         ((SCB_Type*)               SCB_BASE)

#define CPACR  (*(volatile unsigned long*)(0xE000ED88UL))
#define ITCMCR (*(volatile unsigned long*)(0xE000EF90UL))
#define DTCMCR (*(volatile unsigned long*)(0xE000EF94UL))

#ifdef __cplusplus
}
#endif

#endif /* STM32H7X3_H */
