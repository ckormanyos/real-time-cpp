
#ifndef STM32H7X3_H
#define STM32H7X3_H

#include <stdint.h>

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

/* =========================================================================================================================== */
/* ================                                            RCC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Reset and clock control (RCC)
  */

typedef struct {                                /*!< (@ 0x58024400) RCC Structure                                              */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) clock control register                                     */
    
    struct {
      __IOM uint32_t HSION      : 1;            /*!< [0..0] Internal high-speed clock enable                                   */
      __IOM uint32_t HSIKERON   : 1;            /*!< [1..1] High Speed Internal clock enable in Stop mode                      */
      __IOM uint32_t HSIRDY     : 1;            /*!< [2..2] HSI clock ready flag                                               */
      __IOM uint32_t HSIDIV     : 2;            /*!< [4..3] HSI clock divider                                                  */
      __IOM uint32_t HSIDIVF    : 1;            /*!< [5..5] HSI divider flag                                                   */
            uint32_t            : 1;
      __IOM uint32_t CSION      : 1;            /*!< [7..7] CSI clock enable                                                   */
      __IOM uint32_t CSIRDY     : 1;            /*!< [8..8] CSI clock ready flag                                               */
      __IOM uint32_t CSIKERON   : 1;            /*!< [9..9] CSI clock enable in Stop mode                                      */
            uint32_t            : 2;
      __IOM uint32_t RC48ON     : 1;            /*!< [12..12] RC48 clock enable                                                */
      __IOM uint32_t RC48RDY    : 1;            /*!< [13..13] RC48 clock ready flag                                            */
      __IOM uint32_t D1CKRDY    : 1;            /*!< [14..14] D1 domain clocks ready flag                                      */
      __IOM uint32_t D2CKRDY    : 1;            /*!< [15..15] D2 domain clocks ready flag                                      */
      __IOM uint32_t HSEON      : 1;            /*!< [16..16] HSE clock enable                                                 */
      __IOM uint32_t HSERDY     : 1;            /*!< [17..17] HSE clock ready flag                                             */
      __IOM uint32_t HSEBYP     : 1;            /*!< [18..18] HSE clock bypass                                                 */
      __IOM uint32_t HSECSSON   : 1;            /*!< [19..19] HSE Clock Security System enable                                 */
            uint32_t            : 4;
      __IOM uint32_t PLL1ON     : 1;            /*!< [24..24] PLL1 enable                                                      */
      __IOM uint32_t PLL1RDY    : 1;            /*!< [25..25] PLL1 clock ready flag                                            */
      __IOM uint32_t PLL2ON     : 1;            /*!< [26..26] PLL2 enable                                                      */
      __IOM uint32_t PLL2RDY    : 1;            /*!< [27..27] PLL2 clock ready flag                                            */
      __IOM uint32_t PLL3ON     : 1;            /*!< [28..28] PLL3 enable                                                      */
      __IOM uint32_t PLL3RDY    : 1;            /*!< [29..29] PLL3 clock ready flag                                            */
            uint32_t            : 2;
    } bit;
  } CR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) RCC Internal Clock Source Calibration Register             */
    
    struct {
      __IM  uint32_t HSICAL     : 12;           /*!< [11..0] HSI clock calibration                                             */
      __IOM uint32_t HSITRIM    : 6;            /*!< [17..12] HSI clock trimming                                               */
      __IM  uint32_t CSICAL     : 8;            /*!< [25..18] CSI clock calibration                                            */
      __IOM uint32_t CSITRIM    : 5;            /*!< [30..26] CSI clock trimming                                               */
            uint32_t            : 1;
    } bit;
  } ICSCR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000008) RCC Clock Recovery RC Register                             */
    
    struct {
      __IM  uint32_t RC48CAL    : 10;           /*!< [9..0] Internal RC 48 MHz clock calibration                               */
            uint32_t            : 22;
    } bit;
  } CRRCR;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) RCC Clock Configuration Register                           */
    
    struct {
      __IOM uint32_t SW         : 3;            /*!< [2..0] System clock switch                                                */
      __IOM uint32_t SWS        : 3;            /*!< [5..3] System clock switch status                                         */
      __IOM uint32_t STOPWUCK   : 1;            /*!< [6..6] System clock selection after a wake up from system Stop            */
      __IOM uint32_t STOPKERWUCK : 1;           /*!< [7..7] Kernel clock selection after a wake up from system Stop            */
      __IOM uint32_t RTCPRE     : 6;            /*!< [13..8] HSE division factor for RTC clock                                 */
      __IOM uint32_t HRTIMSEL   : 1;            /*!< [14..14] High Resolution Timer clock prescaler selection                  */
      __IOM uint32_t TIMPRE     : 1;            /*!< [15..15] Timers clocks prescaler selection                                */
            uint32_t            : 2;
      __IOM uint32_t MCO1PRE    : 4;            /*!< [21..18] MCO1 prescaler                                                   */
      __IOM uint32_t MCO1SEL    : 3;            /*!< [24..22] Micro-controller clock output 1                                  */
      __IOM uint32_t MCO2PRE    : 4;            /*!< [28..25] MCO2 prescaler                                                   */
      __IOM uint32_t MCO2SEL    : 3;            /*!< [31..29] Micro-controller clock output 2                                  */
    } bit;
  } CFGR;
  __IM  uint32_t  RESERVED1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) RCC Domain 1 Clock Configuration Register                  */
    
    struct {
      __IOM uint32_t HPRE       : 4;            /*!< [3..0] D1 domain AHB prescaler                                            */
      __IOM uint32_t D1PPRE     : 3;            /*!< [6..4] D1 domain APB3 prescaler                                           */
            uint32_t            : 1;
      __IOM uint32_t D1CPRE     : 4;            /*!< [11..8] D1 domain Core prescaler                                          */
            uint32_t            : 20;
    } bit;
  } D1CFGR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) RCC Domain 2 Clock Configuration Register                  */
    
    struct {
            uint32_t            : 4;
      __IOM uint32_t D2PPRE1    : 3;            /*!< [6..4] D2 domain APB1 prescaler                                           */
            uint32_t            : 1;
      __IOM uint32_t D2PPRE2    : 3;            /*!< [10..8] D2 domain APB2 prescaler                                          */
            uint32_t            : 21;
    } bit;
  } D2CFGR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) RCC Domain 3 Clock Configuration Register                  */
    
    struct {
            uint32_t            : 4;
      __IOM uint32_t D3PPRE     : 3;            /*!< [6..4] D3 domain APB4 prescaler                                           */
            uint32_t            : 25;
    } bit;
  } D3CFGR;
  __IM  uint32_t  RESERVED2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) RCC PLLs Clock Source Selection Register                   */
    
    struct {
      __IOM uint32_t PLLSRC     : 2;            /*!< [1..0] DIVMx and PLLs clock source selection                              */
            uint32_t            : 2;
      __IOM uint32_t DIVM1      : 6;            /*!< [9..4] Prescaler for PLL1                                                 */
            uint32_t            : 2;
      __IOM uint32_t DIVM2      : 6;            /*!< [17..12] Prescaler for PLL2                                               */
            uint32_t            : 2;
      __IOM uint32_t DIVM3      : 6;            /*!< [25..20] Prescaler for PLL3                                               */
            uint32_t            : 6;
    } bit;
  } PLLCKSELR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) RCC PLLs Configuration Register                            */
    
    struct {
      __IOM uint32_t PLL1FRACEN : 1;            /*!< [0..0] PLL1 fractional latch enable                                       */
      __IOM uint32_t PLL1VCOSEL : 1;            /*!< [1..1] PLL1 VCO selection                                                 */
      __IOM uint32_t PLL1RGE    : 2;            /*!< [3..2] PLL1 input frequency range                                         */
      __IOM uint32_t PLL2FRACEN : 1;            /*!< [4..4] PLL2 fractional latch enable                                       */
      __IOM uint32_t PLL2VCOSEL : 1;            /*!< [5..5] PLL2 VCO selection                                                 */
      __IOM uint32_t PLL2RGE    : 2;            /*!< [7..6] PLL2 input frequency range                                         */
      __IOM uint32_t PLL3FRACEN : 1;            /*!< [8..8] PLL3 fractional latch enable                                       */
      __IOM uint32_t PLL3VCOSEL : 1;            /*!< [9..9] PLL3 VCO selection                                                 */
      __IOM uint32_t PLL3RGE    : 2;            /*!< [11..10] PLL3 input frequency range                                       */
            uint32_t            : 4;
      __IOM uint32_t DIVP1EN    : 1;            /*!< [16..16] PLL1 DIVP divider output enable                                  */
      __IOM uint32_t DIVQ1EN    : 1;            /*!< [17..17] PLL1 DIVQ divider output enable                                  */
      __IOM uint32_t DIVR1EN    : 1;            /*!< [18..18] PLL1 DIVR divider output enable                                  */
      __IOM uint32_t DIVP2EN    : 1;            /*!< [19..19] PLL2 DIVP divider output enable                                  */
      __IOM uint32_t DIVQ2EN    : 1;            /*!< [20..20] PLL2 DIVQ divider output enable                                  */
      __IOM uint32_t DIVR2EN    : 1;            /*!< [21..21] PLL2 DIVR divider output enable                                  */
      __IOM uint32_t DIVP3EN    : 1;            /*!< [22..22] PLL3 DIVP divider output enable                                  */
      __IOM uint32_t DIVQ3EN    : 1;            /*!< [23..23] PLL3 DIVQ divider output enable                                  */
      __IOM uint32_t DIVR3EN    : 1;            /*!< [24..24] PLL3 DIVR divider output enable                                  */
            uint32_t            : 7;
    } bit;
  } PLLCFGR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) RCC PLL1 Dividers Configuration Register                   */
    
    struct {
      __IOM uint32_t DIVN1      : 9;            /*!< [8..0] Multiplication factor for PLL1 VCO                                 */
      __IOM uint32_t DIVP1      : 7;            /*!< [15..9] PLL1 DIVP division factor                                         */
      __IOM uint32_t DIVQ1      : 7;            /*!< [22..16] PLL1 DIVQ division factor                                        */
            uint32_t            : 1;
      __IOM uint32_t DIVR1      : 7;            /*!< [30..24] PLL1 DIVR division factor                                        */
            uint32_t            : 1;
    } bit;
  } PLL1DIVR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) RCC PLL1 Fractional Divider Register                       */
    
    struct {
            uint32_t            : 3;
      __IOM uint32_t FRACN1     : 13;           /*!< [15..3] Fractional part of the multiplication factor for PLL1
                                                     VCO                                                                       */
            uint32_t            : 16;
    } bit;
  } PLL1FRACR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) RCC PLL2 Dividers Configuration Register                   */
    
    struct {
      __IOM uint32_t DIVN1      : 9;            /*!< [8..0] Multiplication factor for PLL1 VCO                                 */
      __IOM uint32_t DIVP1      : 7;            /*!< [15..9] PLL1 DIVP division factor                                         */
      __IOM uint32_t DIVQ1      : 7;            /*!< [22..16] PLL1 DIVQ division factor                                        */
            uint32_t            : 1;
      __IOM uint32_t DIVR1      : 7;            /*!< [30..24] PLL1 DIVR division factor                                        */
            uint32_t            : 1;
    } bit;
  } PLL2DIVR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000003C) RCC PLL2 Fractional Divider Register                       */
    
    struct {
            uint32_t            : 3;
      __IOM uint32_t FRACN2     : 13;           /*!< [15..3] Fractional part of the multiplication factor for PLL
                                                     VCO                                                                       */
            uint32_t            : 16;
    } bit;
  } PLL2FRACR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) RCC PLL3 Dividers Configuration Register                   */
    
    struct {
      __IOM uint32_t DIVN3      : 9;            /*!< [8..0] Multiplication factor for PLL1 VCO                                 */
      __IOM uint32_t DIVP3      : 7;            /*!< [15..9] PLL DIVP division factor                                          */
      __IOM uint32_t DIVQ3      : 7;            /*!< [22..16] PLL DIVQ division factor                                         */
            uint32_t            : 1;
      __IOM uint32_t DIVR3      : 7;            /*!< [30..24] PLL DIVR division factor                                         */
            uint32_t            : 1;
    } bit;
  } PLL3DIVR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000044) RCC PLL3 Fractional Divider Register                       */
    
    struct {
            uint32_t            : 3;
      __IOM uint32_t FRACN3     : 13;           /*!< [15..3] Fractional part of the multiplication factor for PLL3
                                                     VCO                                                                       */
            uint32_t            : 16;
    } bit;
  } PLL3FRACR;
  __IM  uint32_t  RESERVED3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) RCC Domain 1 Kernel Clock Configuration Register           */
    
    struct {
      __IOM uint32_t FMCSRC     : 2;            /*!< [1..0] FMC kernel clock source selection                                  */
            uint32_t            : 2;
      __IOM uint32_t QSPISRC    : 2;            /*!< [5..4] QUADSPI kernel clock source selection                              */
            uint32_t            : 10;
      __IOM uint32_t SDMMCSRC   : 1;            /*!< [16..16] SDMMC kernel clock source selection                              */
            uint32_t            : 11;
      __IOM uint32_t CKPERSRC   : 2;            /*!< [29..28] per_ck clock source selection                                    */
            uint32_t            : 2;
    } bit;
  } D1CCIPR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000050) RCC Domain 2 Kernel Clock Configuration Register           */
    
    struct {
      __IOM uint32_t SAI1SRC    : 3;            /*!< [2..0] SAI1 and DFSDM1 kernel Aclk clock source selection                 */
            uint32_t            : 3;
      __IOM uint32_t SAI23SRC   : 3;            /*!< [8..6] SAI2 and SAI3 kernel clock source selection                        */
            uint32_t            : 3;
      __IOM uint32_t SPI123SRC  : 3;            /*!< [14..12] SPI/I2S1,2 and 3 kernel clock source selection                   */
            uint32_t            : 1;
      __IOM uint32_t SPI45SRC   : 3;            /*!< [18..16] SPI4 and 5 kernel clock source selection                         */
            uint32_t            : 1;
      __IOM uint32_t SPDIFSRC   : 2;            /*!< [21..20] SPDIFRX kernel clock source selection                            */
            uint32_t            : 2;
      __IOM uint32_t DFSDM1SRC  : 1;            /*!< [24..24] DFSDM1 kernel Clk clock source selection                         */
            uint32_t            : 3;
      __IOM uint32_t FDCANSRC   : 2;            /*!< [29..28] FDCAN kernel clock source selection                              */
            uint32_t            : 1;
      __IOM uint32_t SWPSRC     : 1;            /*!< [31..31] SWPMI kernel clock source selection                              */
    } bit;
  } D2CCIP1R;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000054) RCC Domain 2 Kernel Clock Configuration Register           */
    
    struct {
      __IOM uint32_t USART234578SRC : 3;        /*!< [2..0] USART2/3, UART4,5, 7/8 (APB1) kernel clock source selection        */
      __IOM uint32_t USART16SRC : 3;            /*!< [5..3] USART1 and 6 kernel clock source selection                         */
            uint32_t            : 2;
      __IOM uint32_t RNGSRC     : 2;            /*!< [9..8] RNG kernel clock source selection                                  */
            uint32_t            : 2;
      __IOM uint32_t I2C123SRC  : 2;            /*!< [13..12] I2C1,2,3 kernel clock source selection                           */
            uint32_t            : 6;
      __IOM uint32_t USBSRC     : 2;            /*!< [21..20] USBOTG 1 and 2 kernel clock source selection                     */
      __IOM uint32_t CECSRC     : 2;            /*!< [23..22] HDMI-CEC kernel clock source selection                           */
            uint32_t            : 4;
      __IOM uint32_t LPTIM1SRC  : 3;            /*!< [30..28] LPTIM1 kernel clock source selection                             */
            uint32_t            : 1;
    } bit;
  } D2CCIP2R;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000058) RCC Domain 3 Kernel Clock Configuration Register           */
    
    struct {
      __IOM uint32_t LPUART1SRC : 3;            /*!< [2..0] LPUART1 kernel clock source selection                              */
            uint32_t            : 5;
      __IOM uint32_t I2C4SRC    : 2;            /*!< [9..8] I2C4 kernel clock source selection                                 */
      __IOM uint32_t LPTIM2SRC  : 3;            /*!< [12..10] LPTIM2 kernel clock source selection                             */
      __IOM uint32_t LPTIM345SRC : 3;           /*!< [15..13] LPTIM3,4,5 kernel clock source selection                         */
      __IOM uint32_t ADCSRC     : 2;            /*!< [17..16] SAR ADC kernel clock source selection                            */
            uint32_t            : 3;
      __IOM uint32_t SAI4ASRC   : 3;            /*!< [23..21] Sub-Block A of SAI4 kernel clock source selection                */
      __IOM uint32_t SAI4BSRC   : 3;            /*!< [26..24] Sub-Block B of SAI4 kernel clock source selection                */
            uint32_t            : 1;
      __IOM uint32_t SPI6SRC    : 3;            /*!< [30..28] SPI6 kernel clock source selection                               */
            uint32_t            : 1;
    } bit;
  } D3CCIPR;
  __IM  uint32_t  RESERVED4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000060) RCC Clock Source Interrupt Enable Register                 */
    
    struct {
      __IOM uint32_t LSIRDYIE   : 1;            /*!< [0..0] LSI ready Interrupt Enable                                         */
      __IOM uint32_t LSERDYIE   : 1;            /*!< [1..1] LSE ready Interrupt Enable                                         */
      __IOM uint32_t HSIRDYIE   : 1;            /*!< [2..2] HSI ready Interrupt Enable                                         */
      __IOM uint32_t HSERDYIE   : 1;            /*!< [3..3] HSE ready Interrupt Enable                                         */
      __IOM uint32_t CSIRDYIE   : 1;            /*!< [4..4] CSI ready Interrupt Enable                                         */
      __IOM uint32_t RC48RDYIE  : 1;            /*!< [5..5] RC48 ready Interrupt Enable                                        */
      __IOM uint32_t PLL1RDYIE  : 1;            /*!< [6..6] PLL1 ready Interrupt Enable                                        */
      __IOM uint32_t PLL2RDYIE  : 1;            /*!< [7..7] PLL2 ready Interrupt Enable                                        */
      __IOM uint32_t PLL3RDYIE  : 1;            /*!< [8..8] PLL3 ready Interrupt Enable                                        */
      __IOM uint32_t LSECSSIE   : 1;            /*!< [9..9] LSE clock security system Interrupt Enable                         */
            uint32_t            : 22;
    } bit;
  } CIER;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000064) RCC Clock Source Interrupt Flag Register                   */
    
    struct {
      __IOM uint32_t LSIRDYF    : 1;            /*!< [0..0] LSI ready Interrupt Flag                                           */
      __IOM uint32_t LSERDYF    : 1;            /*!< [1..1] LSE ready Interrupt Flag                                           */
      __IOM uint32_t HSIRDYF    : 1;            /*!< [2..2] HSI ready Interrupt Flag                                           */
      __IOM uint32_t HSERDYF    : 1;            /*!< [3..3] HSE ready Interrupt Flag                                           */
      __IOM uint32_t CSIRDY     : 1;            /*!< [4..4] CSI ready Interrupt Flag                                           */
      __IOM uint32_t RC48RDYF   : 1;            /*!< [5..5] RC48 ready Interrupt Flag                                          */
      __IOM uint32_t PLL1RDYF   : 1;            /*!< [6..6] PLL1 ready Interrupt Flag                                          */
      __IOM uint32_t PLL2RDYF   : 1;            /*!< [7..7] PLL2 ready Interrupt Flag                                          */
      __IOM uint32_t PLL3RDYF   : 1;            /*!< [8..8] PLL3 ready Interrupt Flag                                          */
      __IOM uint32_t LSECSSF    : 1;            /*!< [9..9] LSE clock security system Interrupt Flag                           */
      __IOM uint32_t HSECSSF    : 1;            /*!< [10..10] HSE clock security system Interrupt Flag                         */
            uint32_t            : 21;
    } bit;
  } CIFR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000068) RCC Clock Source Interrupt Clear Register                  */
    
    struct {
      __IOM uint32_t LSIRDYC    : 1;            /*!< [0..0] LSI ready Interrupt Clear                                          */
      __IOM uint32_t LSERDYC    : 1;            /*!< [1..1] LSE ready Interrupt Clear                                          */
      __IOM uint32_t HSIRDYC    : 1;            /*!< [2..2] HSI ready Interrupt Clear                                          */
      __IOM uint32_t HSERDYC    : 1;            /*!< [3..3] HSE ready Interrupt Clear                                          */
      __IOM uint32_t HSE_ready_Interrupt_Clear : 1;/*!< [4..4] CSI ready Interrupt Clear                                       */
      __IOM uint32_t RC48RDYC   : 1;            /*!< [5..5] RC48 ready Interrupt Clear                                         */
      __IOM uint32_t PLL1RDYC   : 1;            /*!< [6..6] PLL1 ready Interrupt Clear                                         */
      __IOM uint32_t PLL2RDYC   : 1;            /*!< [7..7] PLL2 ready Interrupt Clear                                         */
      __IOM uint32_t PLL3RDYC   : 1;            /*!< [8..8] PLL3 ready Interrupt Clear                                         */
      __IOM uint32_t LSECSSC    : 1;            /*!< [9..9] LSE clock security system Interrupt Clear                          */
      __IOM uint32_t HSECSSC    : 1;            /*!< [10..10] HSE clock security system Interrupt Clear                        */
            uint32_t            : 21;
    } bit;
  } CICR;
  __IM  uint32_t  RESERVED5;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000070) RCC Backup Domain Control Register                         */
    
    struct {
      __IOM uint32_t LSEON      : 1;            /*!< [0..0] LSE oscillator enabled                                             */
      __IOM uint32_t LSERDY     : 1;            /*!< [1..1] LSE oscillator ready                                               */
      __IOM uint32_t LSEBYP     : 1;            /*!< [2..2] LSE oscillator bypass                                              */
      __IOM uint32_t LSEDRV     : 2;            /*!< [4..3] LSE oscillator driving capability                                  */
      __IOM uint32_t LSECSSON   : 1;            /*!< [5..5] LSE clock security system enable                                   */
      __IOM uint32_t LSECSSD    : 1;            /*!< [6..6] LSE clock security system failure detection                        */
            uint32_t            : 1;
      __IOM uint32_t RTCSRC     : 2;            /*!< [9..8] RTC clock source selection                                         */
            uint32_t            : 5;
      __IOM uint32_t RTCEN      : 1;            /*!< [15..15] RTC clock enable                                                 */
      __IOM uint32_t VSWRST     : 1;            /*!< [16..16] VSwitch domain software reset                                    */
            uint32_t            : 15;
    } bit;
  } BDCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000074) RCC Clock Control and Status Register                      */
    
    struct {
      __IOM uint32_t LSION      : 1;            /*!< [0..0] LSI oscillator enable                                              */
      __IOM uint32_t LSIRDY     : 1;            /*!< [1..1] LSI oscillator ready                                               */
            uint32_t            : 30;
    } bit;
  } CSR;
  __IM  uint32_t  RESERVED6;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000007C) RCC AHB3 Reset Register                                    */
    
    struct {
      __IOM uint32_t MDMARST    : 1;            /*!< [0..0] MDMA block reset                                                   */
            uint32_t            : 3;
      __IOM uint32_t DMA2DRST   : 1;            /*!< [4..4] DMA2D block reset                                                  */
      __IOM uint32_t JPGDECRST  : 1;            /*!< [5..5] JPGDEC block reset                                                 */
            uint32_t            : 6;
      __IOM uint32_t FMCRST     : 1;            /*!< [12..12] FMC block reset                                                  */
            uint32_t            : 1;
      __IOM uint32_t QSPIRST    : 1;            /*!< [14..14] QUADSPI and QUADSPI delay block reset                            */
            uint32_t            : 1;
      __IOM uint32_t SDMMC1RST  : 1;            /*!< [16..16] SDMMC1 and SDMMC1 delay block reset                              */
            uint32_t            : 14;
      __IOM uint32_t CPURST     : 1;            /*!< [31..31] CPU reset                                                        */
    } bit;
  } AHB3RSTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000080) RCC AHB1 Peripheral Reset Register                         */
    
    struct {
      __IOM uint32_t DMA1RST    : 1;            /*!< [0..0] DMA1 block reset                                                   */
      __IOM uint32_t DMA2RST    : 1;            /*!< [1..1] DMA2 block reset                                                   */
            uint32_t            : 3;
      __IOM uint32_t ADC12RST   : 1;            /*!< [5..5] ADC1&2 block reset                                                 */
            uint32_t            : 9;
      __IOM uint32_t ETH1MACRST : 1;            /*!< [15..15] ETH1MAC block reset                                              */
            uint32_t            : 9;
      __IOM uint32_t USB1OTGRST : 1;            /*!< [25..25] USB1OTG block reset                                              */
            uint32_t            : 1;
      __IOM uint32_t USB2OTGRST : 1;            /*!< [27..27] USB2OTG block reset                                              */
            uint32_t            : 4;
    } bit;
  } AHB1RSTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000084) RCC AHB2 Peripheral Reset Register                         */
    
    struct {
      __IOM uint32_t CAMITFRST  : 1;            /*!< [0..0] CAMITF block reset                                                 */
            uint32_t            : 3;
      __IOM uint32_t CRYPTRST   : 1;            /*!< [4..4] Cryptography block reset                                           */
      __IOM uint32_t HASHRST    : 1;            /*!< [5..5] Hash block reset                                                   */
      __IOM uint32_t RNGRST     : 1;            /*!< [6..6] Random Number Generator block reset                                */
            uint32_t            : 2;
      __IOM uint32_t SDMMC2RST  : 1;            /*!< [9..9] SDMMC2 and SDMMC2 Delay block reset                                */
            uint32_t            : 22;
    } bit;
  } AHB2RSTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000088) RCC AHB4 Peripheral Reset Register                         */
    
    struct {
      __IOM uint32_t GPIOARST   : 1;            /*!< [0..0] GPIO block reset                                                   */
      __IOM uint32_t GPIOBRST   : 1;            /*!< [1..1] GPIO block reset                                                   */
      __IOM uint32_t GPIOCRST   : 1;            /*!< [2..2] GPIO block reset                                                   */
      __IOM uint32_t GPIODRST   : 1;            /*!< [3..3] GPIO block reset                                                   */
      __IOM uint32_t GPIOERST   : 1;            /*!< [4..4] GPIO block reset                                                   */
      __IOM uint32_t GPIOFRST   : 1;            /*!< [5..5] GPIO block reset                                                   */
      __IOM uint32_t GPIOGRST   : 1;            /*!< [6..6] GPIO block reset                                                   */
      __IOM uint32_t GPIOHRST   : 1;            /*!< [7..7] GPIO block reset                                                   */
      __IOM uint32_t GPIOIRST   : 1;            /*!< [8..8] GPIO block reset                                                   */
      __IOM uint32_t GPIOJRST   : 1;            /*!< [9..9] GPIO block reset                                                   */
      __IOM uint32_t GPIOKRST   : 1;            /*!< [10..10] GPIO block reset                                                 */
            uint32_t            : 8;
      __IOM uint32_t CRCRST     : 1;            /*!< [19..19] CRC block reset                                                  */
            uint32_t            : 1;
      __IOM uint32_t BDMARST    : 1;            /*!< [21..21] BDMA block reset                                                 */
            uint32_t            : 2;
      __IOM uint32_t ADC3RST    : 1;            /*!< [24..24] ADC3 block reset                                                 */
      __IOM uint32_t HSEMRST    : 1;            /*!< [25..25] HSEM block reset                                                 */
            uint32_t            : 6;
    } bit;
  } AHB4RSTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000008C) RCC APB3 Peripheral Reset Register                         */
    
    struct {
            uint32_t            : 3;
      __IOM uint32_t LTDCRST    : 1;            /*!< [3..3] LTDC block reset                                                   */
            uint32_t            : 28;
    } bit;
  } APB3RSTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000090) RCC APB1 Peripheral Reset Register                         */
    
    struct {
      __IOM uint32_t TIM2RST    : 1;            /*!< [0..0] TIM block reset                                                    */
      __IOM uint32_t TIM3RST    : 1;            /*!< [1..1] TIM block reset                                                    */
      __IOM uint32_t TIM4RST    : 1;            /*!< [2..2] TIM block reset                                                    */
      __IOM uint32_t TIM5RST    : 1;            /*!< [3..3] TIM block reset                                                    */
      __IOM uint32_t TIM6RST    : 1;            /*!< [4..4] TIM block reset                                                    */
      __IOM uint32_t TIM7RST    : 1;            /*!< [5..5] TIM block reset                                                    */
      __IOM uint32_t TIM12RST   : 1;            /*!< [6..6] TIM block reset                                                    */
      __IOM uint32_t TIM13RST   : 1;            /*!< [7..7] TIM block reset                                                    */
      __IOM uint32_t TIM14RST   : 1;            /*!< [8..8] TIM block reset                                                    */
      __IOM uint32_t LPTIM1RST  : 1;            /*!< [9..9] TIM block reset                                                    */
            uint32_t            : 4;
      __IOM uint32_t SPI2RST    : 1;            /*!< [14..14] SPI2 block reset                                                 */
      __IOM uint32_t SPI3RST    : 1;            /*!< [15..15] SPI3 block reset                                                 */
      __IOM uint32_t SPDIFRXRST : 1;            /*!< [16..16] SPDIFRX block reset                                              */
      __IOM uint32_t USART2RST  : 1;            /*!< [17..17] USART2 block reset                                               */
      __IOM uint32_t USART3RST  : 1;            /*!< [18..18] USART3 block reset                                               */
      __IOM uint32_t UART4RST   : 1;            /*!< [19..19] UART4 block reset                                                */
      __IOM uint32_t UART5RST   : 1;            /*!< [20..20] UART5 block reset                                                */
      __IOM uint32_t I2C1RST    : 1;            /*!< [21..21] I2C1 block reset                                                 */
      __IOM uint32_t I2C2RST    : 1;            /*!< [22..22] I2C2 block reset                                                 */
      __IOM uint32_t I2C3RST    : 1;            /*!< [23..23] I2C3 block reset                                                 */
            uint32_t            : 3;
      __IOM uint32_t HDMICECRST : 1;            /*!< [27..27] HDMI-CEC block reset                                             */
            uint32_t            : 1;
      __IOM uint32_t DAC12RST   : 1;            /*!< [29..29] DAC1 and 2 Blocks Reset                                          */
      __IOM uint32_t USART7RST  : 1;            /*!< [30..30] USART7 block reset                                               */
      __IOM uint32_t USART8RST  : 1;            /*!< [31..31] USART8 block reset                                               */
    } bit;
  } APB1LRSTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000094) RCC APB1 Peripheral Reset Register                         */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t CRSRST     : 1;            /*!< [1..1] Clock Recovery System reset                                        */
      __IOM uint32_t SWPRST     : 1;            /*!< [2..2] SWPMI block reset                                                  */
            uint32_t            : 1;
      __IOM uint32_t OPAMPRST   : 1;            /*!< [4..4] OPAMP block reset                                                  */
      __IOM uint32_t MDIOSRST   : 1;            /*!< [5..5] MDIOS block reset                                                  */
            uint32_t            : 2;
      __IOM uint32_t FDCANRST   : 1;            /*!< [8..8] FDCAN block reset                                                  */
            uint32_t            : 23;
    } bit;
  } APB1HRSTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000098) RCC APB2 Peripheral Reset Register                         */
    
    struct {
      __IOM uint32_t TIM1RST    : 1;            /*!< [0..0] TIM1 block reset                                                   */
      __IOM uint32_t TIM8RST    : 1;            /*!< [1..1] TIM8 block reset                                                   */
            uint32_t            : 2;
      __IOM uint32_t USART1RST  : 1;            /*!< [4..4] USART1 block reset                                                 */
      __IOM uint32_t USART6RST  : 1;            /*!< [5..5] USART6 block reset                                                 */
            uint32_t            : 6;
      __IOM uint32_t SPI1RST    : 1;            /*!< [12..12] SPI1 block reset                                                 */
      __IOM uint32_t SPI4RST    : 1;            /*!< [13..13] SPI4 block reset                                                 */
            uint32_t            : 2;
      __IOM uint32_t TIM15RST   : 1;            /*!< [16..16] TIM15 block reset                                                */
      __IOM uint32_t TIM16RST   : 1;            /*!< [17..17] TIM16 block reset                                                */
      __IOM uint32_t TIM17RST   : 1;            /*!< [18..18] TIM17 block reset                                                */
            uint32_t            : 1;
      __IOM uint32_t SPI5RST    : 1;            /*!< [20..20] SPI5 block reset                                                 */
            uint32_t            : 1;
      __IOM uint32_t SAI1RST    : 1;            /*!< [22..22] SAI1 block reset                                                 */
      __IOM uint32_t SAI2RST    : 1;            /*!< [23..23] SAI2 block reset                                                 */
      __IOM uint32_t SAI3RST    : 1;            /*!< [24..24] SAI3 block reset                                                 */
            uint32_t            : 3;
      __IOM uint32_t DFSDM1RST  : 1;            /*!< [28..28] DFSDM1 block reset                                               */
      __IOM uint32_t HRTIMRST   : 1;            /*!< [29..29] HRTIM block reset                                                */
            uint32_t            : 2;
    } bit;
  } APB2RSTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000009C) RCC APB4 Peripheral Reset Register                         */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t SYSCFGRST  : 1;            /*!< [1..1] SYSCFG block reset                                                 */
            uint32_t            : 1;
      __IOM uint32_t LPUART1RST : 1;            /*!< [3..3] LPUART1 block reset                                                */
            uint32_t            : 1;
      __IOM uint32_t SPI6RST    : 1;            /*!< [5..5] SPI6 block reset                                                   */
            uint32_t            : 1;
      __IOM uint32_t I2C4RST    : 1;            /*!< [7..7] I2C4 block reset                                                   */
            uint32_t            : 1;
      __IOM uint32_t LPTIM2RST  : 1;            /*!< [9..9] LPTIM2 block reset                                                 */
      __IOM uint32_t LPTIM3RST  : 1;            /*!< [10..10] LPTIM3 block reset                                               */
      __IOM uint32_t LPTIM4RST  : 1;            /*!< [11..11] LPTIM4 block reset                                               */
      __IOM uint32_t LPTIM5RST  : 1;            /*!< [12..12] LPTIM5 block reset                                               */
            uint32_t            : 1;
      __IOM uint32_t COMP12RST  : 1;            /*!< [14..14] COMP12 Blocks Reset                                              */
      __IOM uint32_t VREFRST    : 1;            /*!< [15..15] VREF block reset                                                 */
            uint32_t            : 5;
      __IOM uint32_t SAI4RST    : 1;            /*!< [21..21] SAI4 block reset                                                 */
            uint32_t            : 10;
    } bit;
  } APB4RSTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000A0) RCC Global Control Register                                */
    
    struct {
      __IOM uint32_t WW1RSC     : 1;            /*!< [0..0] WWDG1 reset scope control                                          */
            uint32_t            : 31;
    } bit;
  } GCR;
  __IM  uint32_t  RESERVED7;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000A8) RCC D3 Autonomous mode Register                            */
    
    struct {
      __IOM uint32_t BDMAAMEN   : 1;            /*!< [0..0] BDMA and DMAMUX Autonomous mode enable                             */
            uint32_t            : 2;
      __IOM uint32_t LPUART1AMEN : 1;           /*!< [3..3] LPUART1 Autonomous mode enable                                     */
            uint32_t            : 1;
      __IOM uint32_t SPI6AMEN   : 1;            /*!< [5..5] SPI6 Autonomous mode enable                                        */
            uint32_t            : 1;
      __IOM uint32_t I2C4AMEN   : 1;            /*!< [7..7] I2C4 Autonomous mode enable                                        */
            uint32_t            : 1;
      __IOM uint32_t LPTIM2AMEN : 1;            /*!< [9..9] LPTIM2 Autonomous mode enable                                      */
      __IOM uint32_t LPTIM3AMEN : 1;            /*!< [10..10] LPTIM3 Autonomous mode enable                                    */
      __IOM uint32_t LPTIM4AMEN : 1;            /*!< [11..11] LPTIM4 Autonomous mode enable                                    */
      __IOM uint32_t LPTIM5AMEN : 1;            /*!< [12..12] LPTIM5 Autonomous mode enable                                    */
            uint32_t            : 1;
      __IOM uint32_t COMP12AMEN : 1;            /*!< [14..14] COMP12 Autonomous mode enable                                    */
      __IOM uint32_t VREFAMEN   : 1;            /*!< [15..15] VREF Autonomous mode enable                                      */
      __IOM uint32_t RTCAMEN    : 1;            /*!< [16..16] RTC Autonomous mode enable                                       */
            uint32_t            : 2;
      __IOM uint32_t CRCAMEN    : 1;            /*!< [19..19] CRC Autonomous mode enable                                       */
            uint32_t            : 1;
      __IOM uint32_t SAI4AMEN   : 1;            /*!< [21..21] SAI4 Autonomous mode enable                                      */
            uint32_t            : 2;
      __IOM uint32_t ADC3AMEN   : 1;            /*!< [24..24] ADC3 Autonomous mode enable                                      */
            uint32_t            : 3;
      __IOM uint32_t BKPSRAMAMEN : 1;           /*!< [28..28] Backup RAM Autonomous mode enable                                */
      __IOM uint32_t SRAM4AMEN  : 1;            /*!< [29..29] SRAM4 Autonomous mode enable                                     */
            uint32_t            : 2;
    } bit;
  } D3AMR;
  __IM  uint32_t  RESERVED8[9];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000D0) RCC Reset Status Register                                  */
    
    struct {
            uint32_t            : 16;
      __IOM uint32_t RMVF       : 1;            /*!< [16..16] Remove reset flag                                                */
      __IOM uint32_t CPURSTF    : 1;            /*!< [17..17] CPU reset flag                                                   */
            uint32_t            : 1;
      __IOM uint32_t D1RSTF     : 1;            /*!< [19..19] D1 domain power switch reset flag                                */
      __IOM uint32_t D2RSTF     : 1;            /*!< [20..20] D2 domain power switch reset flag                                */
      __IOM uint32_t BORRSTF    : 1;            /*!< [21..21] BOR reset flag                                                   */
      __IOM uint32_t PINRSTF    : 1;            /*!< [22..22] Pin reset flag (NRST)                                            */
      __IOM uint32_t PORRSTF    : 1;            /*!< [23..23] POR/PDR reset flag                                               */
      __IOM uint32_t SFTRSTF    : 1;            /*!< [24..24] System reset from CPU reset flag                                 */
            uint32_t            : 1;
      __IOM uint32_t IWDG1RSTF  : 1;            /*!< [26..26] Independent Watchdog reset flag                                  */
            uint32_t            : 1;
      __IOM uint32_t WWDG1RSTF  : 1;            /*!< [28..28] Window Watchdog reset flag                                       */
            uint32_t            : 1;
      __IOM uint32_t LPWRRSTF   : 1;            /*!< [30..30] Reset due to illegal D1 DStandby or CPU CStop flag               */
            uint32_t            : 1;
    } bit;
  } RSR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000D4) RCC AHB3 Clock Register                                    */
    
    struct {
      __IOM uint32_t MDMAEN     : 1;            /*!< [0..0] MDMA Peripheral Clock Enable                                       */
            uint32_t            : 3;
      __IOM uint32_t DMA2DEN    : 1;            /*!< [4..4] DMA2D Peripheral Clock Enable                                      */
      __IOM uint32_t JPGDECEN   : 1;            /*!< [5..5] JPGDEC Peripheral Clock Enable                                     */
            uint32_t            : 6;
      __IOM uint32_t FMCEN      : 1;            /*!< [12..12] FMC Peripheral Clocks Enable                                     */
            uint32_t            : 1;
      __IOM uint32_t QSPIEN     : 1;            /*!< [14..14] QUADSPI and QUADSPI Delay Clock Enable                           */
            uint32_t            : 1;
      __IOM uint32_t SDMMC1EN   : 1;            /*!< [16..16] SDMMC1 and SDMMC1 Delay Clock Enable                             */
            uint32_t            : 15;
    } bit;
  } AHB3ENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000D8) RCC AHB1 Clock Register                                    */
    
    struct {
      __IOM uint32_t DMA1EN     : 1;            /*!< [0..0] DMA1 Clock Enable                                                  */
      __IOM uint32_t DMA2EN     : 1;            /*!< [1..1] DMA2 Clock Enable                                                  */
            uint32_t            : 3;
      __IOM uint32_t ADC12EN    : 1;            /*!< [5..5] ADC1/2 Peripheral Clocks Enable                                    */
            uint32_t            : 9;
      __IOM uint32_t ETH1MACEN  : 1;            /*!< [15..15] Ethernet MAC bus interface Clock Enable                          */
      __IOM uint32_t ETH1TXEN   : 1;            /*!< [16..16] Ethernet Transmission Clock Enable                               */
      __IOM uint32_t ETH1RXEN   : 1;            /*!< [17..17] Ethernet Reception Clock Enable                                  */
            uint32_t            : 7;
      __IOM uint32_t USB1OTGEN  : 1;            /*!< [25..25] USB1OTG Peripheral Clocks Enable                                 */
      __IOM uint32_t USB1ULPIEN : 1;            /*!< [26..26] USB_PHY1 Clocks Enable                                           */
      __IOM uint32_t USB2OTGEN  : 1;            /*!< [27..27] USB2OTG Peripheral Clocks Enable                                 */
      __IOM uint32_t USB2ULPIEN : 1;            /*!< [28..28] USB_PHY2 Clocks Enable                                           */
            uint32_t            : 3;
    } bit;
  } AHB1ENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000DC) RCC AHB2 Clock Register                                    */
    
    struct {
      __IOM uint32_t CAMITFEN   : 1;            /*!< [0..0] CAMITF peripheral clock enable                                     */
            uint32_t            : 3;
      __IOM uint32_t CRYPTEN    : 1;            /*!< [4..4] CRYPT peripheral clock enable                                      */
      __IOM uint32_t HASHEN     : 1;            /*!< [5..5] HASH peripheral clock enable                                       */
      __IOM uint32_t RNGEN      : 1;            /*!< [6..6] RNG peripheral clocks enable                                       */
            uint32_t            : 2;
      __IOM uint32_t SDMMC2EN   : 1;            /*!< [9..9] SDMMC2 and SDMMC2 delay clock enable                               */
            uint32_t            : 19;
      __IOM uint32_t SRAM1EN    : 1;            /*!< [29..29] SRAM1 block enable                                               */
      __IOM uint32_t SRAM2EN    : 1;            /*!< [30..30] SRAM2 block enable                                               */
      __IOM uint32_t SRAM3EN    : 1;            /*!< [31..31] SRAM3 block enable                                               */
    } bit;
  } AHB2ENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000E0) RCC AHB4 Clock Register                                    */
    
    struct {
      __IOM uint32_t GPIOAEN    : 1;            /*!< [0..0] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOBEN    : 1;            /*!< [1..1] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOCEN    : 1;            /*!< [2..2] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIODEN    : 1;            /*!< [3..3] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOEEN    : 1;            /*!< [4..4] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOFEN    : 1;            /*!< [5..5] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOGEN    : 1;            /*!< [6..6] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOHEN    : 1;            /*!< [7..7] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOIEN    : 1;            /*!< [8..8] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOJEN    : 1;            /*!< [9..9] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOKEN    : 1;            /*!< [10..10] 0GPIO peripheral clock enable                                    */
            uint32_t            : 8;
      __IOM uint32_t CRCEN      : 1;            /*!< [19..19] CRC peripheral clock enable                                      */
            uint32_t            : 1;
      __IOM uint32_t BDMAEN     : 1;            /*!< [21..21] BDMA and DMAMUX2 Clock Enable                                    */
            uint32_t            : 2;
      __IOM uint32_t ADC3EN     : 1;            /*!< [24..24] ADC3 Peripheral Clocks Enable                                    */
      __IOM uint32_t HSEMEN     : 1;            /*!< [25..25] HSEM peripheral clock enable                                     */
            uint32_t            : 2;
      __IOM uint32_t BKPRAMEN   : 1;            /*!< [28..28] Backup RAM Clock Enable                                          */
            uint32_t            : 3;
    } bit;
  } AHB4ENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000E4) RCC APB3 Clock Register                                    */
    
    struct {
            uint32_t            : 3;
      __IOM uint32_t LTDCEN     : 1;            /*!< [3..3] LTDC peripheral clock enable                                       */
            uint32_t            : 2;
      __IOM uint32_t WWDG1EN    : 1;            /*!< [6..6] WWDG1 Clock Enable                                                 */
            uint32_t            : 25;
    } bit;
  } APB3ENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000E8) RCC APB1 Clock Register                                    */
    
    struct {
      __IOM uint32_t TIM2EN     : 1;            /*!< [0..0] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM3EN     : 1;            /*!< [1..1] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM4EN     : 1;            /*!< [2..2] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM5EN     : 1;            /*!< [3..3] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM6EN     : 1;            /*!< [4..4] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM7EN     : 1;            /*!< [5..5] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM12EN    : 1;            /*!< [6..6] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM13EN    : 1;            /*!< [7..7] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM14EN    : 1;            /*!< [8..8] TIM peripheral clock enable                                        */
      __IOM uint32_t LPTIM1EN   : 1;            /*!< [9..9] LPTIM1 Peripheral Clocks Enable                                    */
            uint32_t            : 4;
      __IOM uint32_t SPI2EN     : 1;            /*!< [14..14] SPI2 Peripheral Clocks Enable                                    */
      __IOM uint32_t SPI3EN     : 1;            /*!< [15..15] SPI3 Peripheral Clocks Enable                                    */
      __IOM uint32_t SPDIFRXEN  : 1;            /*!< [16..16] SPDIFRX Peripheral Clocks Enable                                 */
      __IOM uint32_t USART2EN   : 1;            /*!< [17..17] USART2 Peripheral Clocks Enable                                  */
      __IOM uint32_t USART3EN   : 1;            /*!< [18..18] USART3 Peripheral Clocks Enable                                  */
      __IOM uint32_t UART4EN    : 1;            /*!< [19..19] UART4 Peripheral Clocks Enable                                   */
      __IOM uint32_t UART5EN    : 1;            /*!< [20..20] UART5 Peripheral Clocks Enable                                   */
      __IOM uint32_t I2C1EN     : 1;            /*!< [21..21] I2C1 Peripheral Clocks Enable                                    */
      __IOM uint32_t I2C2EN     : 1;            /*!< [22..22] I2C2 Peripheral Clocks Enable                                    */
      __IOM uint32_t I2C3EN     : 1;            /*!< [23..23] I2C3 Peripheral Clocks Enable                                    */
            uint32_t            : 3;
      __IOM uint32_t HDMICECEN  : 1;            /*!< [27..27] HDMI-CEC peripheral clock enable                                 */
            uint32_t            : 1;
      __IOM uint32_t DAC12EN    : 1;            /*!< [29..29] DAC1&2 peripheral clock enable                                   */
      __IOM uint32_t USART7EN   : 1;            /*!< [30..30] USART7 Peripheral Clocks Enable                                  */
      __IOM uint32_t USART8EN   : 1;            /*!< [31..31] USART8 Peripheral Clocks Enable                                  */
    } bit;
  } APB1LENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000EC) RCC APB1 Clock Register                                    */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t CRSEN      : 1;            /*!< [1..1] Clock Recovery System peripheral clock enable                      */
      __IOM uint32_t SWPEN      : 1;            /*!< [2..2] SWPMI Peripheral Clocks Enable                                     */
            uint32_t            : 1;
      __IOM uint32_t OPAMPEN    : 1;            /*!< [4..4] OPAMP peripheral clock enable                                      */
      __IOM uint32_t MDIOSEN    : 1;            /*!< [5..5] MDIOS peripheral clock enable                                      */
            uint32_t            : 2;
      __IOM uint32_t FDCANEN    : 1;            /*!< [8..8] FDCAN Peripheral Clocks Enable                                     */
            uint32_t            : 23;
    } bit;
  } APB1HENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000F0) RCC APB2 Clock Register                                    */
    
    struct {
      __IOM uint32_t TIM1EN     : 1;            /*!< [0..0] TIM1 peripheral clock enable                                       */
      __IOM uint32_t TIM8EN     : 1;            /*!< [1..1] TIM8 peripheral clock enable                                       */
            uint32_t            : 2;
      __IOM uint32_t USART1EN   : 1;            /*!< [4..4] USART1 Peripheral Clocks Enable                                    */
      __IOM uint32_t USART6EN   : 1;            /*!< [5..5] USART6 Peripheral Clocks Enable                                    */
            uint32_t            : 6;
      __IOM uint32_t SPI1EN     : 1;            /*!< [12..12] SPI1 Peripheral Clocks Enable                                    */
      __IOM uint32_t SPI4EN     : 1;            /*!< [13..13] SPI4 Peripheral Clocks Enable                                    */
            uint32_t            : 2;
      __IOM uint32_t TIM15EN    : 1;            /*!< [16..16] TIM15 peripheral clock enable                                    */
      __IOM uint32_t TIM16EN    : 1;            /*!< [17..17] TIM16 peripheral clock enable                                    */
      __IOM uint32_t TIM17EN    : 1;            /*!< [18..18] TIM17 peripheral clock enable                                    */
            uint32_t            : 1;
      __IOM uint32_t SPI5EN     : 1;            /*!< [20..20] SPI5 Peripheral Clocks Enable                                    */
            uint32_t            : 1;
      __IOM uint32_t SAI1EN     : 1;            /*!< [22..22] SAI1 Peripheral Clocks Enable                                    */
      __IOM uint32_t SAI2EN     : 1;            /*!< [23..23] SAI2 Peripheral Clocks Enable                                    */
      __IOM uint32_t SAI3EN     : 1;            /*!< [24..24] SAI3 Peripheral Clocks Enable                                    */
            uint32_t            : 3;
      __IOM uint32_t DFSDM1EN   : 1;            /*!< [28..28] DFSDM1 Peripheral Clocks Enable                                  */
      __IOM uint32_t HRTIMEN    : 1;            /*!< [29..29] HRTIM peripheral clock enable                                    */
            uint32_t            : 2;
    } bit;
  } APB2ENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000F4) RCC APB4 Clock Register                                    */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t SYSCFGEN   : 1;            /*!< [1..1] SYSCFG peripheral clock enable                                     */
            uint32_t            : 1;
      __IOM uint32_t LPUART1EN  : 1;            /*!< [3..3] LPUART1 Peripheral Clocks Enable                                   */
            uint32_t            : 1;
      __IOM uint32_t SPI6EN     : 1;            /*!< [5..5] SPI6 Peripheral Clocks Enable                                      */
            uint32_t            : 1;
      __IOM uint32_t I2C4EN     : 1;            /*!< [7..7] I2C4 Peripheral Clocks Enable                                      */
            uint32_t            : 1;
      __IOM uint32_t LPTIM2EN   : 1;            /*!< [9..9] LPTIM2 Peripheral Clocks Enable                                    */
      __IOM uint32_t LPTIM3EN   : 1;            /*!< [10..10] LPTIM3 Peripheral Clocks Enable                                  */
      __IOM uint32_t LPTIM4EN   : 1;            /*!< [11..11] LPTIM4 Peripheral Clocks Enable                                  */
      __IOM uint32_t LPTIM5EN   : 1;            /*!< [12..12] LPTIM5 Peripheral Clocks Enable                                  */
            uint32_t            : 1;
      __IOM uint32_t COMP12EN   : 1;            /*!< [14..14] COMP1/2 peripheral clock enable                                  */
      __IOM uint32_t VREFEN     : 1;            /*!< [15..15] VREF peripheral clock enable                                     */
      __IOM uint32_t RTCAPBEN   : 1;            /*!< [16..16] RTC APB Clock Enable                                             */
            uint32_t            : 4;
      __IOM uint32_t SAI4EN     : 1;            /*!< [21..21] SAI4 Peripheral Clocks Enable                                    */
            uint32_t            : 10;
    } bit;
  } APB4ENR;
  __IM  uint32_t  RESERVED9;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000FC) RCC AHB3 Sleep Clock Register                              */
    
    struct {
      __IOM uint32_t MDMALPEN   : 1;            /*!< [0..0] MDMA Clock Enable During CSleep Mode                               */
            uint32_t            : 3;
      __IOM uint32_t DMA2DLPEN  : 1;            /*!< [4..4] DMA2D Clock Enable During CSleep Mode                              */
      __IOM uint32_t JPGDECLPEN : 1;            /*!< [5..5] JPGDEC Clock Enable During CSleep Mode                             */
            uint32_t            : 2;
      __IOM uint32_t FLITFLPEN  : 1;            /*!< [8..8] FLITF Clock Enable During CSleep Mode                              */
            uint32_t            : 3;
      __IOM uint32_t FMCLPEN    : 1;            /*!< [12..12] FMC Peripheral Clocks Enable During CSleep Mode                  */
            uint32_t            : 1;
      __IOM uint32_t QSPILPEN   : 1;            /*!< [14..14] QUADSPI and QUADSPI Delay Clock Enable During CSleep
                                                     Mode                                                                      */
            uint32_t            : 1;
      __IOM uint32_t SDMMC1LPEN : 1;            /*!< [16..16] SDMMC1 and SDMMC1 Delay Clock Enable During CSleep
                                                     Mode                                                                      */
            uint32_t            : 11;
      __IOM uint32_t D1DTCM1LPEN : 1;           /*!< [28..28] D1DTCM1 Block Clock Enable During CSleep mode                    */
      __IOM uint32_t DTCM2LPEN  : 1;            /*!< [29..29] D1 DTCM2 Block Clock Enable During CSleep mode                   */
      __IOM uint32_t ITCMLPEN   : 1;            /*!< [30..30] D1ITCM Block Clock Enable During CSleep mode                     */
      __IOM uint32_t AXISRAMLPEN : 1;           /*!< [31..31] AXISRAM Block Clock Enable During CSleep mode                    */
    } bit;
  } AHB3LPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000100) RCC AHB1 Sleep Clock Register                              */
    
    struct {
      __IOM uint32_t DMA1LPEN   : 1;            /*!< [0..0] DMA1 Clock Enable During CSleep Mode                               */
      __IOM uint32_t DMA2LPEN   : 1;            /*!< [1..1] DMA2 Clock Enable During CSleep Mode                               */
            uint32_t            : 3;
      __IOM uint32_t ADC12LPEN  : 1;            /*!< [5..5] ADC1/2 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 9;
      __IOM uint32_t ETH1MACLPEN : 1;           /*!< [15..15] Ethernet MAC bus interface Clock Enable During CSleep
                                                     Mode                                                                      */
      __IOM uint32_t ETH1TXLPEN : 1;            /*!< [16..16] Ethernet Transmission Clock Enable During CSleep Mode            */
      __IOM uint32_t ETH1RXLPEN : 1;            /*!< [17..17] Ethernet Reception Clock Enable During CSleep Mode               */
            uint32_t            : 7;
      __IOM uint32_t USB1OTGLPEN : 1;           /*!< [25..25] USB1OTG peripheral clock enable during CSleep mode               */
      __IOM uint32_t USB1ULPILPEN : 1;          /*!< [26..26] USB_PHY1 clock enable during CSleep mode                         */
      __IOM uint32_t USB2OTGLPEN : 1;           /*!< [27..27] USB2OTG peripheral clock enable during CSleep mode               */
      __IOM uint32_t USB2ULPILPEN : 1;          /*!< [28..28] USB_PHY2 clocks enable during CSleep mode                        */
            uint32_t            : 3;
    } bit;
  } AHB1LPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000104) RCC AHB2 Sleep Clock Register                              */
    
    struct {
      __IOM uint32_t CAMITFLPEN : 1;            /*!< [0..0] CAMITF peripheral clock enable during CSleep mode                  */
            uint32_t            : 3;
      __IOM uint32_t CRYPTLPEN  : 1;            /*!< [4..4] CRYPT peripheral clock enable during CSleep mode                   */
      __IOM uint32_t HASHLPEN   : 1;            /*!< [5..5] HASH peripheral clock enable during CSleep mode                    */
      __IOM uint32_t RNGLPEN    : 1;            /*!< [6..6] RNG peripheral clock enable during CSleep mode                     */
            uint32_t            : 2;
      __IOM uint32_t SDMMC2LPEN : 1;            /*!< [9..9] SDMMC2 and SDMMC2 Delay Clock Enable During CSleep Mode            */
            uint32_t            : 19;
      __IOM uint32_t SRAM1LPEN  : 1;            /*!< [29..29] SRAM1 Clock Enable During CSleep Mode                            */
      __IOM uint32_t SRAM2LPEN  : 1;            /*!< [30..30] SRAM2 Clock Enable During CSleep Mode                            */
      __IOM uint32_t SRAM3LPEN  : 1;            /*!< [31..31] SRAM3 Clock Enable During CSleep Mode                            */
    } bit;
  } AHB2LPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000108) RCC AHB4 Sleep Clock Register                              */
    
    struct {
      __IOM uint32_t GPIOALPEN  : 1;            /*!< [0..0] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOBLPEN  : 1;            /*!< [1..1] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOCLPEN  : 1;            /*!< [2..2] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIODLPEN  : 1;            /*!< [3..3] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOELPEN  : 1;            /*!< [4..4] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOFLPEN  : 1;            /*!< [5..5] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOGLPEN  : 1;            /*!< [6..6] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOHLPEN  : 1;            /*!< [7..7] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOILPEN  : 1;            /*!< [8..8] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOJLPEN  : 1;            /*!< [9..9] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOKLPEN  : 1;            /*!< [10..10] GPIO peripheral clock enable during CSleep mode                  */
            uint32_t            : 8;
      __IOM uint32_t CRCLPEN    : 1;            /*!< [19..19] CRC peripheral clock enable during CSleep mode                   */
            uint32_t            : 1;
      __IOM uint32_t BDMALPEN   : 1;            /*!< [21..21] BDMA Clock Enable During CSleep Mode                             */
            uint32_t            : 2;
      __IOM uint32_t ADC3LPEN   : 1;            /*!< [24..24] ADC3 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 3;
      __IOM uint32_t BKPRAMLPEN : 1;            /*!< [28..28] Backup RAM Clock Enable During CSleep Mode                       */
      __IOM uint32_t SRAM4LPEN  : 1;            /*!< [29..29] SRAM4 Clock Enable During CSleep Mode                            */
            uint32_t            : 2;
    } bit;
  } AHB4LPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000010C) RCC APB3 Sleep Clock Register                              */
    
    struct {
            uint32_t            : 3;
      __IOM uint32_t LTDCLPEN   : 1;            /*!< [3..3] LTDC peripheral clock enable during CSleep mode                    */
            uint32_t            : 2;
      __IOM uint32_t WWDG1LPEN  : 1;            /*!< [6..6] WWDG1 Clock Enable During CSleep Mode                              */
            uint32_t            : 25;
    } bit;
  } APB3LPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000110) RCC APB1 Low Sleep Clock Register                          */
    
    struct {
      __IOM uint32_t TIM2LPEN   : 1;            /*!< [0..0] TIM2 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM3LPEN   : 1;            /*!< [1..1] TIM3 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM4LPEN   : 1;            /*!< [2..2] TIM4 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM5LPEN   : 1;            /*!< [3..3] TIM5 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM6LPEN   : 1;            /*!< [4..4] TIM6 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM7LPEN   : 1;            /*!< [5..5] TIM7 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM12LPEN  : 1;            /*!< [6..6] TIM12 peripheral clock enable during CSleep mode                   */
      __IOM uint32_t TIM13LPEN  : 1;            /*!< [7..7] TIM13 peripheral clock enable during CSleep mode                   */
      __IOM uint32_t TIM14LPEN  : 1;            /*!< [8..8] TIM14 peripheral clock enable during CSleep mode                   */
      __IOM uint32_t LPTIM1LPEN : 1;            /*!< [9..9] LPTIM1 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 4;
      __IOM uint32_t SPI2LPEN   : 1;            /*!< [14..14] SPI2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t SPI3LPEN   : 1;            /*!< [15..15] SPI3 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t SPDIFRXLPEN : 1;           /*!< [16..16] SPDIFRX Peripheral Clocks Enable During CSleep Mode              */
      __IOM uint32_t USART2LPEN : 1;            /*!< [17..17] USART2 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32_t USART3LPEN : 1;            /*!< [18..18] USART3 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32_t UART4LPEN  : 1;            /*!< [19..19] UART4 Peripheral Clocks Enable During CSleep Mode                */
      __IOM uint32_t UART5LPEN  : 1;            /*!< [20..20] UART5 Peripheral Clocks Enable During CSleep Mode                */
      __IOM uint32_t I2C1LPEN   : 1;            /*!< [21..21] I2C1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t I2C2LPEN   : 1;            /*!< [22..22] I2C2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t I2C3LPEN   : 1;            /*!< [23..23] I2C3 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 3;
      __IOM uint32_t HDMICECLPEN : 1;           /*!< [27..27] HDMI-CEC Peripheral Clocks Enable During CSleep Mode             */
            uint32_t            : 1;
      __IOM uint32_t DAC12LPEN  : 1;            /*!< [29..29] DAC1/2 peripheral clock enable during CSleep mode                */
      __IOM uint32_t USART7LPEN : 1;            /*!< [30..30] USART7 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32_t USART8LPEN : 1;            /*!< [31..31] USART8 Peripheral Clocks Enable During CSleep Mode               */
    } bit;
  } APB1LLPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000114) RCC APB1 High Sleep Clock Register                         */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t CRSLPEN    : 1;            /*!< [1..1] Clock Recovery System peripheral clock enable during
                                                     CSleep mode                                                               */
      __IOM uint32_t SWPLPEN    : 1;            /*!< [2..2] SWPMI Peripheral Clocks Enable During CSleep Mode                  */
            uint32_t            : 1;
      __IOM uint32_t OPAMPLPEN  : 1;            /*!< [4..4] OPAMP peripheral clock enable during CSleep mode                   */
      __IOM uint32_t MDIOSLPEN  : 1;            /*!< [5..5] MDIOS peripheral clock enable during CSleep mode                   */
            uint32_t            : 2;
      __IOM uint32_t FDCANLPEN  : 1;            /*!< [8..8] FDCAN Peripheral Clocks Enable During CSleep Mode                  */
            uint32_t            : 23;
    } bit;
  } APB1HLPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000118) RCC APB2 Sleep Clock Register                              */
    
    struct {
      __IOM uint32_t TIM1LPEN   : 1;            /*!< [0..0] TIM1 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM8LPEN   : 1;            /*!< [1..1] TIM8 peripheral clock enable during CSleep mode                    */
            uint32_t            : 2;
      __IOM uint32_t USART1LPEN : 1;            /*!< [4..4] USART1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t USART6LPEN : 1;            /*!< [5..5] USART6 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 6;
      __IOM uint32_t SPI1LPEN   : 1;            /*!< [12..12] SPI1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t SPI4LPEN   : 1;            /*!< [13..13] SPI4 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 2;
      __IOM uint32_t TIM15LPEN  : 1;            /*!< [16..16] TIM15 peripheral clock enable during CSleep mode                 */
      __IOM uint32_t TIM16LPEN  : 1;            /*!< [17..17] TIM16 peripheral clock enable during CSleep mode                 */
      __IOM uint32_t TIM17LPEN  : 1;            /*!< [18..18] TIM17 peripheral clock enable during CSleep mode                 */
            uint32_t            : 1;
      __IOM uint32_t SPI5LPEN   : 1;            /*!< [20..20] SPI5 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 1;
      __IOM uint32_t SAI1LPEN   : 1;            /*!< [22..22] SAI1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t SAI2LPEN   : 1;            /*!< [23..23] SAI2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t SAI3LPEN   : 1;            /*!< [24..24] SAI3 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 3;
      __IOM uint32_t DFSDM1LPEN : 1;            /*!< [28..28] DFSDM1 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32_t HRTIMLPEN  : 1;            /*!< [29..29] HRTIM peripheral clock enable during CSleep mode                 */
            uint32_t            : 2;
    } bit;
  } APB2LPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000011C) RCC APB4 Sleep Clock Register                              */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t SYSCFGLPEN : 1;            /*!< [1..1] SYSCFG peripheral clock enable during CSleep mode                  */
            uint32_t            : 1;
      __IOM uint32_t LPUART1LPEN : 1;           /*!< [3..3] LPUART1 Peripheral Clocks Enable During CSleep Mode                */
            uint32_t            : 1;
      __IOM uint32_t SPI6LPEN   : 1;            /*!< [5..5] SPI6 Peripheral Clocks Enable During CSleep Mode                   */
            uint32_t            : 1;
      __IOM uint32_t I2C4LPEN   : 1;            /*!< [7..7] I2C4 Peripheral Clocks Enable During CSleep Mode                   */
            uint32_t            : 1;
      __IOM uint32_t LPTIM2LPEN : 1;            /*!< [9..9] LPTIM2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t LPTIM3LPEN : 1;            /*!< [10..10] LPTIM3 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32_t LPTIM4LPEN : 1;            /*!< [11..11] LPTIM4 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32_t LPTIM5LPEN : 1;            /*!< [12..12] LPTIM5 Peripheral Clocks Enable During CSleep Mode               */
            uint32_t            : 1;
      __IOM uint32_t COMP12LPEN : 1;            /*!< [14..14] COMP1/2 peripheral clock enable during CSleep mode               */
      __IOM uint32_t VREFLPEN   : 1;            /*!< [15..15] VREF peripheral clock enable during CSleep mode                  */
      __IOM uint32_t RTCAPBLPEN : 1;            /*!< [16..16] RTC APB Clock Enable During CSleep Mode                          */
            uint32_t            : 4;
      __IOM uint32_t SAI4LPEN   : 1;            /*!< [21..21] SAI4 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 10;
    } bit;
  } APB4LPENR;
  __IM  uint32_t  RESERVED10[4];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000130) RCC Reset Status Register                                  */
    
    struct {
            uint32_t            : 16;
      __IOM uint32_t RMVF       : 1;            /*!< [16..16] Remove reset flag                                                */
      __IOM uint32_t CPURSTF    : 1;            /*!< [17..17] CPU reset flag                                                   */
            uint32_t            : 1;
      __IOM uint32_t D1RSTF     : 1;            /*!< [19..19] D1 domain power switch reset flag                                */
      __IOM uint32_t D2RSTF     : 1;            /*!< [20..20] D2 domain power switch reset flag                                */
      __IOM uint32_t BORRSTF    : 1;            /*!< [21..21] BOR reset flag                                                   */
      __IOM uint32_t PINRSTF    : 1;            /*!< [22..22] Pin reset flag (NRST)                                            */
      __IOM uint32_t PORRSTF    : 1;            /*!< [23..23] POR/PDR reset flag                                               */
      __IOM uint32_t SFTRSTF    : 1;            /*!< [24..24] System reset from CPU reset flag                                 */
            uint32_t            : 1;
      __IOM uint32_t IWDG1RSTF  : 1;            /*!< [26..26] Independent Watchdog reset flag                                  */
            uint32_t            : 1;
      __IOM uint32_t WWDG1RSTF  : 1;            /*!< [28..28] Window Watchdog reset flag                                       */
            uint32_t            : 1;
      __IOM uint32_t LPWRRSTF   : 1;            /*!< [30..30] Reset due to illegal D1 DStandby or CPU CStop flag               */
            uint32_t            : 1;
    } bit;
  } C1_RSR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000134) RCC AHB3 Clock Register                                    */
    
    struct {
      __IOM uint32_t MDMAEN     : 1;            /*!< [0..0] MDMA Peripheral Clock Enable                                       */
            uint32_t            : 3;
      __IOM uint32_t DMA2DEN    : 1;            /*!< [4..4] DMA2D Peripheral Clock Enable                                      */
      __IOM uint32_t JPGDECEN   : 1;            /*!< [5..5] JPGDEC Peripheral Clock Enable                                     */
            uint32_t            : 6;
      __IOM uint32_t FMCEN      : 1;            /*!< [12..12] FMC Peripheral Clocks Enable                                     */
            uint32_t            : 1;
      __IOM uint32_t QSPIEN     : 1;            /*!< [14..14] QUADSPI and QUADSPI Delay Clock Enable                           */
            uint32_t            : 1;
      __IOM uint32_t SDMMC1EN   : 1;            /*!< [16..16] SDMMC1 and SDMMC1 Delay Clock Enable                             */
            uint32_t            : 15;
    } bit;
  } C1_AHB3ENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000138) RCC AHB1 Clock Register                                    */
    
    struct {
      __IOM uint32_t DMA1EN     : 1;            /*!< [0..0] DMA1 Clock Enable                                                  */
      __IOM uint32_t DMA2EN     : 1;            /*!< [1..1] DMA2 Clock Enable                                                  */
            uint32_t            : 3;
      __IOM uint32_t ADC12EN    : 1;            /*!< [5..5] ADC1/2 Peripheral Clocks Enable                                    */
            uint32_t            : 9;
      __IOM uint32_t ETH1MACEN  : 1;            /*!< [15..15] Ethernet MAC bus interface Clock Enable                          */
      __IOM uint32_t ETH1TXEN   : 1;            /*!< [16..16] Ethernet Transmission Clock Enable                               */
      __IOM uint32_t ETH1RXEN   : 1;            /*!< [17..17] Ethernet Reception Clock Enable                                  */
            uint32_t            : 7;
      __IOM uint32_t USB1OTGEN  : 1;            /*!< [25..25] USB1OTG Peripheral Clocks Enable                                 */
      __IOM uint32_t USB1ULPIEN : 1;            /*!< [26..26] USB_PHY1 Clocks Enable                                           */
      __IOM uint32_t USB2OTGEN  : 1;            /*!< [27..27] USB2OTG Peripheral Clocks Enable                                 */
      __IOM uint32_t USB2ULPIEN : 1;            /*!< [28..28] USB_PHY2 Clocks Enable                                           */
            uint32_t            : 3;
    } bit;
  } C1_AHB1ENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000013C) RCC AHB2 Clock Register                                    */
    
    struct {
      __IOM uint32_t CAMITFEN   : 1;            /*!< [0..0] CAMITF peripheral clock enable                                     */
            uint32_t            : 3;
      __IOM uint32_t CRYPTEN    : 1;            /*!< [4..4] CRYPT peripheral clock enable                                      */
      __IOM uint32_t HASHEN     : 1;            /*!< [5..5] HASH peripheral clock enable                                       */
      __IOM uint32_t RNGEN      : 1;            /*!< [6..6] RNG peripheral clocks enable                                       */
            uint32_t            : 2;
      __IOM uint32_t SDMMC2EN   : 1;            /*!< [9..9] SDMMC2 and SDMMC2 delay clock enable                               */
            uint32_t            : 19;
      __IOM uint32_t SRAM1EN    : 1;            /*!< [29..29] SRAM1 block enable                                               */
      __IOM uint32_t SRAM2EN    : 1;            /*!< [30..30] SRAM2 block enable                                               */
      __IOM uint32_t SRAM3EN    : 1;            /*!< [31..31] SRAM3 block enable                                               */
    } bit;
  } C1_AHB2ENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000140) RCC AHB4 Clock Register                                    */
    
    struct {
      __IOM uint32_t GPIOAEN    : 1;            /*!< [0..0] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOBEN    : 1;            /*!< [1..1] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOCEN    : 1;            /*!< [2..2] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIODEN    : 1;            /*!< [3..3] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOEEN    : 1;            /*!< [4..4] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOFEN    : 1;            /*!< [5..5] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOGEN    : 1;            /*!< [6..6] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOHEN    : 1;            /*!< [7..7] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOIEN    : 1;            /*!< [8..8] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOJEN    : 1;            /*!< [9..9] 0GPIO peripheral clock enable                                      */
      __IOM uint32_t GPIOKEN    : 1;            /*!< [10..10] 0GPIO peripheral clock enable                                    */
            uint32_t            : 8;
      __IOM uint32_t CRCEN      : 1;            /*!< [19..19] CRC peripheral clock enable                                      */
            uint32_t            : 1;
      __IOM uint32_t BDMAEN     : 1;            /*!< [21..21] BDMA and DMAMUX2 Clock Enable                                    */
            uint32_t            : 2;
      __IOM uint32_t ADC3EN     : 1;            /*!< [24..24] ADC3 Peripheral Clocks Enable                                    */
      __IOM uint32_t HSEMEN     : 1;            /*!< [25..25] HSEM peripheral clock enable                                     */
            uint32_t            : 2;
      __IOM uint32_t BKPRAMEN   : 1;            /*!< [28..28] Backup RAM Clock Enable                                          */
            uint32_t            : 3;
    } bit;
  } C1_AHB4ENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000144) RCC APB3 Clock Register                                    */
    
    struct {
            uint32_t            : 3;
      __IOM uint32_t LTDCEN     : 1;            /*!< [3..3] LTDC peripheral clock enable                                       */
            uint32_t            : 2;
      __IOM uint32_t WWDG1EN    : 1;            /*!< [6..6] WWDG1 Clock Enable                                                 */
            uint32_t            : 25;
    } bit;
  } C1_APB3ENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000148) RCC APB1 Clock Register                                    */
    
    struct {
      __IOM uint32_t TIM2EN     : 1;            /*!< [0..0] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM3EN     : 1;            /*!< [1..1] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM4EN     : 1;            /*!< [2..2] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM5EN     : 1;            /*!< [3..3] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM6EN     : 1;            /*!< [4..4] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM7EN     : 1;            /*!< [5..5] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM12EN    : 1;            /*!< [6..6] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM13EN    : 1;            /*!< [7..7] TIM peripheral clock enable                                        */
      __IOM uint32_t TIM14EN    : 1;            /*!< [8..8] TIM peripheral clock enable                                        */
      __IOM uint32_t LPTIM1EN   : 1;            /*!< [9..9] LPTIM1 Peripheral Clocks Enable                                    */
            uint32_t            : 4;
      __IOM uint32_t SPI2EN     : 1;            /*!< [14..14] SPI2 Peripheral Clocks Enable                                    */
      __IOM uint32_t SPI3EN     : 1;            /*!< [15..15] SPI3 Peripheral Clocks Enable                                    */
      __IOM uint32_t SPDIFRXEN  : 1;            /*!< [16..16] SPDIFRX Peripheral Clocks Enable                                 */
      __IOM uint32_t USART2EN   : 1;            /*!< [17..17] USART2 Peripheral Clocks Enable                                  */
      __IOM uint32_t USART3EN   : 1;            /*!< [18..18] USART3 Peripheral Clocks Enable                                  */
      __IOM uint32_t UART4EN    : 1;            /*!< [19..19] UART4 Peripheral Clocks Enable                                   */
      __IOM uint32_t UART5EN    : 1;            /*!< [20..20] UART5 Peripheral Clocks Enable                                   */
      __IOM uint32_t I2C1EN     : 1;            /*!< [21..21] I2C1 Peripheral Clocks Enable                                    */
      __IOM uint32_t I2C2EN     : 1;            /*!< [22..22] I2C2 Peripheral Clocks Enable                                    */
      __IOM uint32_t I2C3EN     : 1;            /*!< [23..23] I2C3 Peripheral Clocks Enable                                    */
            uint32_t            : 3;
      __IOM uint32_t HDMICECEN  : 1;            /*!< [27..27] HDMI-CEC peripheral clock enable                                 */
            uint32_t            : 1;
      __IOM uint32_t DAC12EN    : 1;            /*!< [29..29] DAC1&2 peripheral clock enable                                   */
      __IOM uint32_t USART7EN   : 1;            /*!< [30..30] USART7 Peripheral Clocks Enable                                  */
      __IOM uint32_t USART8EN   : 1;            /*!< [31..31] USART8 Peripheral Clocks Enable                                  */
    } bit;
  } C1_APB1LENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000014C) RCC APB1 Clock Register                                    */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t CRSEN      : 1;            /*!< [1..1] Clock Recovery System peripheral clock enable                      */
      __IOM uint32_t SWPEN      : 1;            /*!< [2..2] SWPMI Peripheral Clocks Enable                                     */
            uint32_t            : 1;
      __IOM uint32_t OPAMPEN    : 1;            /*!< [4..4] OPAMP peripheral clock enable                                      */
      __IOM uint32_t MDIOSEN    : 1;            /*!< [5..5] MDIOS peripheral clock enable                                      */
            uint32_t            : 2;
      __IOM uint32_t FDCANEN    : 1;            /*!< [8..8] FDCAN Peripheral Clocks Enable                                     */
            uint32_t            : 23;
    } bit;
  } C1_APB1HENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000150) RCC APB2 Clock Register                                    */
    
    struct {
      __IOM uint32_t TIM1EN     : 1;            /*!< [0..0] TIM1 peripheral clock enable                                       */
      __IOM uint32_t TIM8EN     : 1;            /*!< [1..1] TIM8 peripheral clock enable                                       */
            uint32_t            : 2;
      __IOM uint32_t USART1EN   : 1;            /*!< [4..4] USART1 Peripheral Clocks Enable                                    */
      __IOM uint32_t USART6EN   : 1;            /*!< [5..5] USART6 Peripheral Clocks Enable                                    */
            uint32_t            : 6;
      __IOM uint32_t SPI1EN     : 1;            /*!< [12..12] SPI1 Peripheral Clocks Enable                                    */
      __IOM uint32_t SPI4EN     : 1;            /*!< [13..13] SPI4 Peripheral Clocks Enable                                    */
            uint32_t            : 2;
      __IOM uint32_t TIM15EN    : 1;            /*!< [16..16] TIM15 peripheral clock enable                                    */
      __IOM uint32_t TIM16EN    : 1;            /*!< [17..17] TIM16 peripheral clock enable                                    */
      __IOM uint32_t TIM17EN    : 1;            /*!< [18..18] TIM17 peripheral clock enable                                    */
            uint32_t            : 1;
      __IOM uint32_t SPI5EN     : 1;            /*!< [20..20] SPI5 Peripheral Clocks Enable                                    */
            uint32_t            : 1;
      __IOM uint32_t SAI1EN     : 1;            /*!< [22..22] SAI1 Peripheral Clocks Enable                                    */
      __IOM uint32_t SAI2EN     : 1;            /*!< [23..23] SAI2 Peripheral Clocks Enable                                    */
      __IOM uint32_t SAI3EN     : 1;            /*!< [24..24] SAI3 Peripheral Clocks Enable                                    */
            uint32_t            : 3;
      __IOM uint32_t DFSDM1EN   : 1;            /*!< [28..28] DFSDM1 Peripheral Clocks Enable                                  */
      __IOM uint32_t HRTIMEN    : 1;            /*!< [29..29] HRTIM peripheral clock enable                                    */
            uint32_t            : 2;
    } bit;
  } C1_APB2ENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000154) RCC APB4 Clock Register                                    */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t SYSCFGEN   : 1;            /*!< [1..1] SYSCFG peripheral clock enable                                     */
            uint32_t            : 1;
      __IOM uint32_t LPUART1EN  : 1;            /*!< [3..3] LPUART1 Peripheral Clocks Enable                                   */
            uint32_t            : 1;
      __IOM uint32_t SPI6EN     : 1;            /*!< [5..5] SPI6 Peripheral Clocks Enable                                      */
            uint32_t            : 1;
      __IOM uint32_t I2C4EN     : 1;            /*!< [7..7] I2C4 Peripheral Clocks Enable                                      */
            uint32_t            : 1;
      __IOM uint32_t LPTIM2EN   : 1;            /*!< [9..9] LPTIM2 Peripheral Clocks Enable                                    */
      __IOM uint32_t LPTIM3EN   : 1;            /*!< [10..10] LPTIM3 Peripheral Clocks Enable                                  */
      __IOM uint32_t LPTIM4EN   : 1;            /*!< [11..11] LPTIM4 Peripheral Clocks Enable                                  */
      __IOM uint32_t LPTIM5EN   : 1;            /*!< [12..12] LPTIM5 Peripheral Clocks Enable                                  */
            uint32_t            : 1;
      __IOM uint32_t COMP12EN   : 1;            /*!< [14..14] COMP1/2 peripheral clock enable                                  */
      __IOM uint32_t VREFEN     : 1;            /*!< [15..15] VREF peripheral clock enable                                     */
      __IOM uint32_t RTCAPBEN   : 1;            /*!< [16..16] RTC APB Clock Enable                                             */
            uint32_t            : 4;
      __IOM uint32_t SAI4EN     : 1;            /*!< [21..21] SAI4 Peripheral Clocks Enable                                    */
            uint32_t            : 10;
    } bit;
  } C1_APB4ENR;
  __IM  uint32_t  RESERVED11;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000015C) RCC AHB3 Sleep Clock Register                              */
    
    struct {
      __IOM uint32_t MDMALPEN   : 1;            /*!< [0..0] MDMA Clock Enable During CSleep Mode                               */
            uint32_t            : 3;
      __IOM uint32_t DMA2DLPEN  : 1;            /*!< [4..4] DMA2D Clock Enable During CSleep Mode                              */
      __IOM uint32_t JPGDECLPEN : 1;            /*!< [5..5] JPGDEC Clock Enable During CSleep Mode                             */
            uint32_t            : 2;
      __IOM uint32_t FLITFLPEN  : 1;            /*!< [8..8] FLITF Clock Enable During CSleep Mode                              */
            uint32_t            : 3;
      __IOM uint32_t FMCLPEN    : 1;            /*!< [12..12] FMC Peripheral Clocks Enable During CSleep Mode                  */
            uint32_t            : 1;
      __IOM uint32_t QSPILPEN   : 1;            /*!< [14..14] QUADSPI and QUADSPI Delay Clock Enable During CSleep
                                                     Mode                                                                      */
            uint32_t            : 1;
      __IOM uint32_t SDMMC1LPEN : 1;            /*!< [16..16] SDMMC1 and SDMMC1 Delay Clock Enable During CSleep
                                                     Mode                                                                      */
            uint32_t            : 11;
      __IOM uint32_t D1DTCM1LPEN : 1;           /*!< [28..28] D1DTCM1 Block Clock Enable During CSleep mode                    */
      __IOM uint32_t DTCM2LPEN  : 1;            /*!< [29..29] D1 DTCM2 Block Clock Enable During CSleep mode                   */
      __IOM uint32_t ITCMLPEN   : 1;            /*!< [30..30] D1ITCM Block Clock Enable During CSleep mode                     */
      __IOM uint32_t AXISRAMLPEN : 1;           /*!< [31..31] AXISRAM Block Clock Enable During CSleep mode                    */
    } bit;
  } C1_AHB3LPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000160) RCC AHB1 Sleep Clock Register                              */
    
    struct {
      __IOM uint32_t DMA1LPEN   : 1;            /*!< [0..0] DMA1 Clock Enable During CSleep Mode                               */
      __IOM uint32_t DMA2LPEN   : 1;            /*!< [1..1] DMA2 Clock Enable During CSleep Mode                               */
            uint32_t            : 3;
      __IOM uint32_t ADC12LPEN  : 1;            /*!< [5..5] ADC1/2 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 9;
      __IOM uint32_t ETH1MACLPEN : 1;           /*!< [15..15] Ethernet MAC bus interface Clock Enable During CSleep
                                                     Mode                                                                      */
      __IOM uint32_t ETH1TXLPEN : 1;            /*!< [16..16] Ethernet Transmission Clock Enable During CSleep Mode            */
      __IOM uint32_t ETH1RXLPEN : 1;            /*!< [17..17] Ethernet Reception Clock Enable During CSleep Mode               */
            uint32_t            : 7;
      __IOM uint32_t USB1OTGLPEN : 1;           /*!< [25..25] USB1OTG peripheral clock enable during CSleep mode               */
      __IOM uint32_t USB1ULPILPEN : 1;          /*!< [26..26] USB_PHY1 clock enable during CSleep mode                         */
      __IOM uint32_t USB2OTGLPEN : 1;           /*!< [27..27] USB2OTG peripheral clock enable during CSleep mode               */
      __IOM uint32_t USB2ULPILPEN : 1;          /*!< [28..28] USB_PHY2 clocks enable during CSleep mode                        */
            uint32_t            : 3;
    } bit;
  } C1_AHB1LPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000164) RCC AHB2 Sleep Clock Register                              */
    
    struct {
      __IOM uint32_t CAMITFLPEN : 1;            /*!< [0..0] CAMITF peripheral clock enable during CSleep mode                  */
            uint32_t            : 3;
      __IOM uint32_t CRYPTLPEN  : 1;            /*!< [4..4] CRYPT peripheral clock enable during CSleep mode                   */
      __IOM uint32_t HASHLPEN   : 1;            /*!< [5..5] HASH peripheral clock enable during CSleep mode                    */
      __IOM uint32_t RNGLPEN    : 1;            /*!< [6..6] RNG peripheral clock enable during CSleep mode                     */
            uint32_t            : 2;
      __IOM uint32_t SDMMC2LPEN : 1;            /*!< [9..9] SDMMC2 and SDMMC2 Delay Clock Enable During CSleep Mode            */
            uint32_t            : 19;
      __IOM uint32_t SRAM1LPEN  : 1;            /*!< [29..29] SRAM1 Clock Enable During CSleep Mode                            */
      __IOM uint32_t SRAM2LPEN  : 1;            /*!< [30..30] SRAM2 Clock Enable During CSleep Mode                            */
      __IOM uint32_t SRAM3LPEN  : 1;            /*!< [31..31] SRAM3 Clock Enable During CSleep Mode                            */
    } bit;
  } C1_AHB2LPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000168) RCC AHB4 Sleep Clock Register                              */
    
    struct {
      __IOM uint32_t GPIOALPEN  : 1;            /*!< [0..0] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOBLPEN  : 1;            /*!< [1..1] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOCLPEN  : 1;            /*!< [2..2] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIODLPEN  : 1;            /*!< [3..3] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOELPEN  : 1;            /*!< [4..4] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOFLPEN  : 1;            /*!< [5..5] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOGLPEN  : 1;            /*!< [6..6] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOHLPEN  : 1;            /*!< [7..7] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOILPEN  : 1;            /*!< [8..8] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOJLPEN  : 1;            /*!< [9..9] GPIO peripheral clock enable during CSleep mode                    */
      __IOM uint32_t GPIOKLPEN  : 1;            /*!< [10..10] GPIO peripheral clock enable during CSleep mode                  */
            uint32_t            : 8;
      __IOM uint32_t CRCLPEN    : 1;            /*!< [19..19] CRC peripheral clock enable during CSleep mode                   */
            uint32_t            : 1;
      __IOM uint32_t BDMALPEN   : 1;            /*!< [21..21] BDMA Clock Enable During CSleep Mode                             */
            uint32_t            : 2;
      __IOM uint32_t ADC3LPEN   : 1;            /*!< [24..24] ADC3 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 3;
      __IOM uint32_t BKPRAMLPEN : 1;            /*!< [28..28] Backup RAM Clock Enable During CSleep Mode                       */
      __IOM uint32_t SRAM4LPEN  : 1;            /*!< [29..29] SRAM4 Clock Enable During CSleep Mode                            */
            uint32_t            : 2;
    } bit;
  } C1_AHB4LPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000016C) RCC APB3 Sleep Clock Register                              */
    
    struct {
            uint32_t            : 3;
      __IOM uint32_t LTDCLPEN   : 1;            /*!< [3..3] LTDC peripheral clock enable during CSleep mode                    */
            uint32_t            : 2;
      __IOM uint32_t WWDG1LPEN  : 1;            /*!< [6..6] WWDG1 Clock Enable During CSleep Mode                              */
            uint32_t            : 25;
    } bit;
  } C1_APB3LPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000170) RCC APB1 Low Sleep Clock Register                          */
    
    struct {
      __IOM uint32_t TIM2LPEN   : 1;            /*!< [0..0] TIM2 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM3LPEN   : 1;            /*!< [1..1] TIM3 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM4LPEN   : 1;            /*!< [2..2] TIM4 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM5LPEN   : 1;            /*!< [3..3] TIM5 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM6LPEN   : 1;            /*!< [4..4] TIM6 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM7LPEN   : 1;            /*!< [5..5] TIM7 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM12LPEN  : 1;            /*!< [6..6] TIM12 peripheral clock enable during CSleep mode                   */
      __IOM uint32_t TIM13LPEN  : 1;            /*!< [7..7] TIM13 peripheral clock enable during CSleep mode                   */
      __IOM uint32_t TIM14LPEN  : 1;            /*!< [8..8] TIM14 peripheral clock enable during CSleep mode                   */
      __IOM uint32_t LPTIM1LPEN : 1;            /*!< [9..9] LPTIM1 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 4;
      __IOM uint32_t SPI2LPEN   : 1;            /*!< [14..14] SPI2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t SPI3LPEN   : 1;            /*!< [15..15] SPI3 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t SPDIFRXLPEN : 1;           /*!< [16..16] SPDIFRX Peripheral Clocks Enable During CSleep Mode              */
      __IOM uint32_t USART2LPEN : 1;            /*!< [17..17] USART2 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32_t USART3LPEN : 1;            /*!< [18..18] USART3 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32_t UART4LPEN  : 1;            /*!< [19..19] UART4 Peripheral Clocks Enable During CSleep Mode                */
      __IOM uint32_t UART5LPEN  : 1;            /*!< [20..20] UART5 Peripheral Clocks Enable During CSleep Mode                */
      __IOM uint32_t I2C1LPEN   : 1;            /*!< [21..21] I2C1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t I2C2LPEN   : 1;            /*!< [22..22] I2C2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t I2C3LPEN   : 1;            /*!< [23..23] I2C3 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 3;
      __IOM uint32_t HDMICECLPEN : 1;           /*!< [27..27] HDMI-CEC Peripheral Clocks Enable During CSleep Mode             */
            uint32_t            : 1;
      __IOM uint32_t DAC12LPEN  : 1;            /*!< [29..29] DAC1/2 peripheral clock enable during CSleep mode                */
      __IOM uint32_t USART7LPEN : 1;            /*!< [30..30] USART7 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32_t USART8LPEN : 1;            /*!< [31..31] USART8 Peripheral Clocks Enable During CSleep Mode               */
    } bit;
  } C1_APB1LLPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000174) RCC APB1 High Sleep Clock Register                         */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t CRSLPEN    : 1;            /*!< [1..1] Clock Recovery System peripheral clock enable during
                                                     CSleep mode                                                               */
      __IOM uint32_t SWPLPEN    : 1;            /*!< [2..2] SWPMI Peripheral Clocks Enable During CSleep Mode                  */
            uint32_t            : 1;
      __IOM uint32_t OPAMPLPEN  : 1;            /*!< [4..4] OPAMP peripheral clock enable during CSleep mode                   */
      __IOM uint32_t MDIOSLPEN  : 1;            /*!< [5..5] MDIOS peripheral clock enable during CSleep mode                   */
            uint32_t            : 2;
      __IOM uint32_t FDCANLPEN  : 1;            /*!< [8..8] FDCAN Peripheral Clocks Enable During CSleep Mode                  */
            uint32_t            : 23;
    } bit;
  } C1_APB1HLPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000178) RCC APB2 Sleep Clock Register                              */
    
    struct {
      __IOM uint32_t TIM1LPEN   : 1;            /*!< [0..0] TIM1 peripheral clock enable during CSleep mode                    */
      __IOM uint32_t TIM8LPEN   : 1;            /*!< [1..1] TIM8 peripheral clock enable during CSleep mode                    */
            uint32_t            : 2;
      __IOM uint32_t USART1LPEN : 1;            /*!< [4..4] USART1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t USART6LPEN : 1;            /*!< [5..5] USART6 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 6;
      __IOM uint32_t SPI1LPEN   : 1;            /*!< [12..12] SPI1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t SPI4LPEN   : 1;            /*!< [13..13] SPI4 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 2;
      __IOM uint32_t TIM15LPEN  : 1;            /*!< [16..16] TIM15 peripheral clock enable during CSleep mode                 */
      __IOM uint32_t TIM16LPEN  : 1;            /*!< [17..17] TIM16 peripheral clock enable during CSleep mode                 */
      __IOM uint32_t TIM17LPEN  : 1;            /*!< [18..18] TIM17 peripheral clock enable during CSleep mode                 */
            uint32_t            : 1;
      __IOM uint32_t SPI5LPEN   : 1;            /*!< [20..20] SPI5 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 1;
      __IOM uint32_t SAI1LPEN   : 1;            /*!< [22..22] SAI1 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t SAI2LPEN   : 1;            /*!< [23..23] SAI2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t SAI3LPEN   : 1;            /*!< [24..24] SAI3 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 3;
      __IOM uint32_t DFSDM1LPEN : 1;            /*!< [28..28] DFSDM1 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32_t HRTIMLPEN  : 1;            /*!< [29..29] HRTIM peripheral clock enable during CSleep mode                 */
            uint32_t            : 2;
    } bit;
  } C1_APB2LPENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000017C) RCC APB4 Sleep Clock Register                              */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t SYSCFGLPEN : 1;            /*!< [1..1] SYSCFG peripheral clock enable during CSleep mode                  */
            uint32_t            : 1;
      __IOM uint32_t LPUART1LPEN : 1;           /*!< [3..3] LPUART1 Peripheral Clocks Enable During CSleep Mode                */
            uint32_t            : 1;
      __IOM uint32_t SPI6LPEN   : 1;            /*!< [5..5] SPI6 Peripheral Clocks Enable During CSleep Mode                   */
            uint32_t            : 1;
      __IOM uint32_t I2C4LPEN   : 1;            /*!< [7..7] I2C4 Peripheral Clocks Enable During CSleep Mode                   */
            uint32_t            : 1;
      __IOM uint32_t LPTIM2LPEN : 1;            /*!< [9..9] LPTIM2 Peripheral Clocks Enable During CSleep Mode                 */
      __IOM uint32_t LPTIM3LPEN : 1;            /*!< [10..10] LPTIM3 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32_t LPTIM4LPEN : 1;            /*!< [11..11] LPTIM4 Peripheral Clocks Enable During CSleep Mode               */
      __IOM uint32_t LPTIM5LPEN : 1;            /*!< [12..12] LPTIM5 Peripheral Clocks Enable During CSleep Mode               */
            uint32_t            : 1;
      __IOM uint32_t COMP12LPEN : 1;            /*!< [14..14] COMP1/2 peripheral clock enable during CSleep mode               */
      __IOM uint32_t VREFLPEN   : 1;            /*!< [15..15] VREF peripheral clock enable during CSleep mode                  */
      __IOM uint32_t RTCAPBLPEN : 1;            /*!< [16..16] RTC APB Clock Enable During CSleep Mode                          */
            uint32_t            : 4;
      __IOM uint32_t SAI4LPEN   : 1;            /*!< [21..21] SAI4 Peripheral Clocks Enable During CSleep Mode                 */
            uint32_t            : 10;
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
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Access control register                                    */
    
    struct {
      __IOM uint32_t LATENCY    : 3;            /*!< [2..0] Read latency                                                       */
            uint32_t            : 1;
      __IOM uint32_t WRHIGHFREQ : 2;            /*!< [5..4] Flash signal delay                                                 */
            uint32_t            : 26;
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
    __IM  uint32_t reg;                         /*!< (@ 0x00000000) CPUID base register                                        */
    
    struct {
      __IM  uint32_t Revision   : 4;            /*!< [3..0] Revision number                                                    */
      __IM  uint32_t PartNo     : 12;           /*!< [15..4] Part number of the processor                                      */
      __IM  uint32_t Constant   : 4;            /*!< [19..16] Reads as 0xF                                                     */
      __IM  uint32_t Variant    : 4;            /*!< [23..20] Variant number                                                   */
      __IM  uint32_t Implementer : 8;           /*!< [31..24] Implementer code                                                 */
    } bit;
  } CPUID;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Interrupt control and state register                       */
    
    struct {
      __IOM uint32_t VECTACTIVE : 9;            /*!< [8..0] Active vector                                                      */
            uint32_t            : 2;
      __IOM uint32_t RETTOBASE  : 1;            /*!< [11..11] Return to base level                                             */
      __IOM uint32_t VECTPENDING : 7;           /*!< [18..12] Pending vector                                                   */
            uint32_t            : 3;
      __IOM uint32_t ISRPENDING : 1;            /*!< [22..22] Interrupt pending flag                                           */
            uint32_t            : 2;
      __IOM uint32_t PENDSTCLR  : 1;            /*!< [25..25] SysTick exception clear-pending bit                              */
      __IOM uint32_t PENDSTSET  : 1;            /*!< [26..26] SysTick exception set-pending bit                                */
      __IOM uint32_t PENDSVCLR  : 1;            /*!< [27..27] PendSV clear-pending bit                                         */
      __IOM uint32_t PENDSVSET  : 1;            /*!< [28..28] PendSV set-pending bit                                           */
            uint32_t            : 2;
      __IOM uint32_t NMIPENDSET : 1;            /*!< [31..31] NMI set-pending bit.                                             */
    } bit;
  } ICSR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Vector table offset register                               */
    
    struct {
            uint32_t            : 9;
      __IOM uint32_t TBLOFF     : 21;           /*!< [29..9] Vector table base offset field                                    */
            uint32_t            : 2;
    } bit;
  } VTOR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Application interrupt and reset control register           */
    
    struct {
      __IOM uint32_t VECTRESET  : 1;            /*!< [0..0] VECTRESET                                                          */
      __IOM uint32_t VECTCLRACTIVE : 1;         /*!< [1..1] VECTCLRACTIVE                                                      */
      __IOM uint32_t SYSRESETREQ : 1;           /*!< [2..2] SYSRESETREQ                                                        */
            uint32_t            : 5;
      __IOM uint32_t PRIGROUP   : 3;            /*!< [10..8] PRIGROUP                                                          */
            uint32_t            : 4;
      __IOM uint32_t ENDIANESS  : 1;            /*!< [15..15] ENDIANESS                                                        */
      __IOM uint32_t VECTKEYSTAT : 16;          /*!< [31..16] Register key                                                     */
    } bit;
  } AIRCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) System control register                                    */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t SLEEPONEXIT : 1;           /*!< [1..1] SLEEPONEXIT                                                        */
      __IOM uint32_t SLEEPDEEP  : 1;            /*!< [2..2] SLEEPDEEP                                                          */
            uint32_t            : 1;
      __IOM uint32_t SEVEONPEND : 1;            /*!< [4..4] Send Event on Pending bit                                          */
            uint32_t            : 27;
    } bit;
  } SCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Configuration and control register                         */
    
    struct {
      __IOM uint32_t NONBASETHRDENA : 1;        /*!< [0..0] Configures how the processor enters Thread mode                    */
      __IOM uint32_t USERSETMPEND : 1;          /*!< [1..1] USERSETMPEND                                                       */
            uint32_t            : 1;
      __IOM uint32_t UNALIGN__TRP : 1;          /*!< [3..3] UNALIGN_ TRP                                                       */
      __IOM uint32_t DIV_0_TRP  : 1;            /*!< [4..4] DIV_0_TRP                                                          */
            uint32_t            : 3;
      __IOM uint32_t BFHFNMIGN  : 1;            /*!< [8..8] BFHFNMIGN                                                          */
      __IOM uint32_t STKALIGN   : 1;            /*!< [9..9] STKALIGN                                                           */
            uint32_t            : 6;
      __IOM uint32_t DC         : 1;            /*!< [16..16] DC                                                               */
      __IOM uint32_t IC         : 1;            /*!< [17..17] IC                                                               */
      __IOM uint32_t BP         : 1;            /*!< [18..18] BP                                                               */
            uint32_t            : 13;
    } bit;
  } CCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) System handler priority registers                          */
    
    struct {
      __IOM uint32_t PRI_4      : 8;            /*!< [7..0] Priority of system handler 4                                       */
      __IOM uint32_t PRI_5      : 8;            /*!< [15..8] Priority of system handler 5                                      */
      __IOM uint32_t PRI_6      : 8;            /*!< [23..16] Priority of system handler 6                                     */
            uint32_t            : 8;
    } bit;
  } SHPR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) System handler priority registers                          */
    
    struct {
            uint32_t            : 24;
      __IOM uint32_t PRI_11     : 8;            /*!< [31..24] Priority of system handler 11                                    */
    } bit;
  } SHPR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) System handler priority registers                          */
    
    struct {
            uint32_t            : 16;
      __IOM uint32_t PRI_14     : 8;            /*!< [23..16] Priority of system handler 14                                    */
      __IOM uint32_t PRI_15     : 8;            /*!< [31..24] Priority of system handler 15                                    */
    } bit;
  } SHPR3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) System handler control and state register                  */
    
    struct {
      __IOM uint32_t MEMFAULTACT : 1;           /*!< [0..0] Memory management fault exception active bit                       */
      __IOM uint32_t BUSFAULTACT : 1;           /*!< [1..1] Bus fault exception active bit                                     */
            uint32_t            : 1;
      __IOM uint32_t USGFAULTACT : 1;           /*!< [3..3] Usage fault exception active bit                                   */
            uint32_t            : 3;
      __IOM uint32_t SVCALLACT  : 1;            /*!< [7..7] SVC call active bit                                                */
      __IOM uint32_t MONITORACT : 1;            /*!< [8..8] Debug monitor active bit                                           */
            uint32_t            : 1;
      __IOM uint32_t PENDSVACT  : 1;            /*!< [10..10] PendSV exception active bit                                      */
      __IOM uint32_t SYSTICKACT : 1;            /*!< [11..11] SysTick exception active bit                                     */
      __IOM uint32_t USGFAULTPENDED : 1;        /*!< [12..12] Usage fault exception pending bit                                */
      __IOM uint32_t MEMFAULTPENDED : 1;        /*!< [13..13] Memory management fault exception pending bit                    */
      __IOM uint32_t BUSFAULTPENDED : 1;        /*!< [14..14] Bus fault exception pending bit                                  */
      __IOM uint32_t SVCALLPENDED : 1;          /*!< [15..15] SVC call pending bit                                             */
      __IOM uint32_t MEMFAULTENA : 1;           /*!< [16..16] Memory management fault enable bit                               */
      __IOM uint32_t BUSFAULTENA : 1;           /*!< [17..17] Bus fault enable bit                                             */
      __IOM uint32_t USGFAULTENA : 1;           /*!< [18..18] Usage fault enable bit                                           */
            uint32_t            : 13;
    } bit;
  } SHCRS;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) Configurable fault status register                         */
    
    struct {
      __IOM uint32_t IACCVIOL   : 1;            /*!< [0..0] IACCVIOL                                                           */
      __IOM uint32_t DACCVIOL   : 1;            /*!< [1..1] DACCVIOL                                                           */
            uint32_t            : 1;
      __IOM uint32_t MUNSTKERR  : 1;            /*!< [3..3] MUNSTKERR                                                          */
      __IOM uint32_t MSTKERR    : 1;            /*!< [4..4] MSTKERR                                                            */
      __IOM uint32_t MLSPERR    : 1;            /*!< [5..5] MLSPERR                                                            */
            uint32_t            : 1;
      __IOM uint32_t MMARVALID  : 1;            /*!< [7..7] MMARVALID                                                          */
      __IOM uint32_t IBUSERR    : 1;            /*!< [8..8] Instruction bus error                                              */
      __IOM uint32_t PRECISERR  : 1;            /*!< [9..9] Precise data bus error                                             */
      __IOM uint32_t IMPRECISERR : 1;           /*!< [10..10] Imprecise data bus error                                         */
      __IOM uint32_t UNSTKERR   : 1;            /*!< [11..11] Bus fault on unstacking for a return from exception              */
      __IOM uint32_t STKERR     : 1;            /*!< [12..12] Bus fault on stacking for exception entry                        */
      __IOM uint32_t LSPERR     : 1;            /*!< [13..13] Bus fault on floating-point lazy state preservation              */
            uint32_t            : 1;
      __IOM uint32_t BFARVALID  : 1;            /*!< [15..15] Bus Fault Address Register (BFAR) valid flag                     */
      __IOM uint32_t UNDEFINSTR : 1;            /*!< [16..16] Undefined instruction usage fault                                */
      __IOM uint32_t INVSTATE   : 1;            /*!< [17..17] Invalid state usage fault                                        */
      __IOM uint32_t INVPC      : 1;            /*!< [18..18] Invalid PC load usage fault                                      */
      __IOM uint32_t NOCP       : 1;            /*!< [19..19] No coprocessor usage fault.                                      */
            uint32_t            : 4;
      __IOM uint32_t UNALIGNED  : 1;            /*!< [24..24] Unaligned access usage fault                                     */
      __IOM uint32_t DIVBYZERO  : 1;            /*!< [25..25] Divide by zero usage fault                                       */
            uint32_t            : 6;
    } bit;
  } CFSR_UFSR_BFSR_MMFSR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) Hard fault status register                                 */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t VECTTBL    : 1;            /*!< [1..1] Vector table hard fault                                            */
            uint32_t            : 28;
      __IOM uint32_t FORCED     : 1;            /*!< [30..30] Forced hard fault                                                */
      __IOM uint32_t DEBUG_VT   : 1;            /*!< [31..31] Reserved for Debug use                                           */
    } bit;
  } HFSR;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) Memory management fault address register                   */
    
    struct {
      __IOM uint32_t ADDRESS    : 32;           /*!< [31..0] Memory management fault address                                   */
    } bit;
  } MMFAR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) Bus fault address register                                 */
    
    struct {
      __IOM uint32_t ADDRESS    : 32;           /*!< [31..0] Bus fault address                                                 */
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
