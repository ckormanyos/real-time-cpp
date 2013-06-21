
#ifndef _INTERRUPT_2013_06_21_H_
  #define _INTERRUPT_2013_06_21_H_

  #include <cstdint>
  #include "hw_intc.h"
  #include "hw_types.h"

  /****************************************************************************
  **                       MACRO DEFINITIONS
  ****************************************************************************/
  /*
  ** Macros which can be passed to IntPrioritySet API as hostIntRoute.
  */
  /* To route an interrupt to IRQ */
  constexpr std::uint32_t AINTC_HOSTINT_ROUTE_IRQ                (0);

  /* To route an interrupt to FIQ */
  constexpr std::uint32_t AINTC_HOSTINT_ROUTE_FIQ                (INTC_ILR_FIQNIRQ);

  /*
  ** Interrupt number list
  */
  constexpr std::uint32_t SYS_INT_EMUINT                         (0);
  constexpr std::uint32_t SYS_INT_COMMTX                         (1);
  constexpr std::uint32_t SYS_INT_COMMRX                         (2);
  constexpr std::uint32_t SYS_INT_BENCH                          (3);
  constexpr std::uint32_t SYS_INT_ELM_IRQ                        (4);
  constexpr std::uint32_t SYS_INT_SSM_WFI_IRQ                    (5);
  constexpr std::uint32_t SYS_INT_SSM_IRQ                        (6);
  constexpr std::uint32_t SYS_INT_NMI                            (7);
  constexpr std::uint32_t SYS_INT_SEC_EVNT                       (8);
  constexpr std::uint32_t SYS_INT_L3DEBUG                        (9);
  constexpr std::uint32_t SYS_INT_L3APPINT                       (10);
  constexpr std::uint32_t SYS_INT_PRCMINT                        (11);
  constexpr std::uint32_t SYS_INT_EDMACOMPINT                    (12);
  constexpr std::uint32_t SYS_INT_EDMAMPERR                      (13);
  constexpr std::uint32_t SYS_INT_EDMAERRINT                     (14);
  constexpr std::uint32_t SYS_INT_WDT0INT                        (15);
  constexpr std::uint32_t SYS_INT_ADC_TSC_GENINT                 (16);
  constexpr std::uint32_t SYS_INT_USBSSINT                       (17);
  constexpr std::uint32_t SYS_INT_USB0                           (18);
  constexpr std::uint32_t SYS_INT_USB1                           (19);
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT0                 (20);
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT1                 (21);
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT2                 (22);
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT3                 (23);
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT4                 (24);
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT5                 (25);
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT6                 (26);
  constexpr std::uint32_t SYS_INT_PRUSS1_EVTOUT7                 (27);
  constexpr std::uint32_t SYS_INT_MMCSD1INT                      (28);
  constexpr std::uint32_t SYS_INT_MMCSD2INT                      (29);
  constexpr std::uint32_t SYS_INT_I2C2INT                        (30);
  constexpr std::uint32_t SYS_INT_eCAP0INT                       (31);
  constexpr std::uint32_t SYS_INT_GPIOINT2A                      (32);
  constexpr std::uint32_t SYS_INT_GPIOINT2B                      (33);
  constexpr std::uint32_t SYS_INT_USBWAKEUP                      (34);
  constexpr std::uint32_t SYS_INT_LCDCINT                        (36);
  constexpr std::uint32_t SYS_INT_GFXINT                         (37);
  constexpr std::uint32_t SYS_INT_2DHWAINT                       (38);
  constexpr std::uint32_t SYS_INT_ePWM2INT                       (39);
  constexpr std::uint32_t SYS_INT_3PGSWRXTHR0                    (40);
  constexpr std::uint32_t SYS_INT_3PGSWRXINT0                    (41);
  constexpr std::uint32_t SYS_INT_3PGSWTXINT0                    (42);
  constexpr std::uint32_t SYS_INT_3PGSWMISC0                     (43);
  constexpr std::uint32_t SYS_INT_UART3INT                       (44);
  constexpr std::uint32_t SYS_INT_UART4INT                       (45);
  constexpr std::uint32_t SYS_INT_UART5INT                       (46);
  constexpr std::uint32_t SYS_INT_eCAP1INT                       (47);
  constexpr std::uint32_t SYS_INT_DCAN0_INT0                     (52);
  constexpr std::uint32_t SYS_INT_DCAN0_INT1                     (53);
  constexpr std::uint32_t SYS_INT_DCAN0_PARITY                   (54);
  constexpr std::uint32_t SYS_INT_DCAN1_INT0                     (55);
  constexpr std::uint32_t SYS_INT_DCAN1_INT1                     (56);
  constexpr std::uint32_t SYS_INT_DCAN1_PARITY                   (57);
  constexpr std::uint32_t SYS_INT_ePWM0_TZINT                    (58);
  constexpr std::uint32_t SYS_INT_ePWM1_TZINT                    (59);
  constexpr std::uint32_t SYS_INT_ePWM2_TZINT                    (60);
  constexpr std::uint32_t SYS_INT_eCAP2INT                       (61);
  constexpr std::uint32_t SYS_INT_GPIOINT3A                      (62);
  constexpr std::uint32_t SYS_INT_GPIOINT3B                      (63);
  constexpr std::uint32_t SYS_INT_MMCSD0INT                      (64);
  constexpr std::uint32_t SYS_INT_SPI0INT                        (65);
  constexpr std::uint32_t SYS_INT_TINT0                          (66);
  constexpr std::uint32_t SYS_INT_TINT1_1MS                      (67);
  constexpr std::uint32_t SYS_INT_TINT2                          (68);
  constexpr std::uint32_t SYS_INT_TINT3                          (69);
  constexpr std::uint32_t SYS_INT_I2C0INT                        (70);
  constexpr std::uint32_t SYS_INT_I2C1INT                        (71);
  constexpr std::uint32_t SYS_INT_UART0INT                       (72);
  constexpr std::uint32_t SYS_INT_UART1INT                       (73);
  constexpr std::uint32_t SYS_INT_UART2INT                       (74);
  constexpr std::uint32_t SYS_INT_RTCINT                         (75);
  constexpr std::uint32_t SYS_INT_RTCALARMINT                    (76);
  constexpr std::uint32_t SYS_INT_MBINT0                         (77);
  constexpr std::uint32_t SYS_INT_M3_TXEV                        (78);
  constexpr std::uint32_t SYS_INT_eQEP0INT                       (79);
  constexpr std::uint32_t SYS_INT_MCATXINT0                      (80);
  constexpr std::uint32_t SYS_INT_MCARXINT0                      (81);
  constexpr std::uint32_t SYS_INT_MCATXINT1                      (82);
  constexpr std::uint32_t SYS_INT_MCARXINT1                      (83);
  constexpr std::uint32_t SYS_INT_ePWM0INT                       (86);
  constexpr std::uint32_t SYS_INT_ePWM1INT                       (87);
  constexpr std::uint32_t SYS_INT_eQEP1INT                       (88);
  constexpr std::uint32_t SYS_INT_eQEP2INT                       (89);
  constexpr std::uint32_t SYS_INT_DMA_INTR_PIN2                  (90);
  constexpr std::uint32_t SYS_INT_WDT1INT                        (91);
  constexpr std::uint32_t SYS_INT_TINT4                          (92);
  constexpr std::uint32_t SYS_INT_TINT5                          (93);
  constexpr std::uint32_t SYS_INT_TINT6                          (94);
  constexpr std::uint32_t SYS_INT_TINT7                          (95);
  constexpr std::uint32_t SYS_INT_GPIOINT0A                      (96);
  constexpr std::uint32_t SYS_INT_GPIOINT0B                      (97);
  constexpr std::uint32_t SYS_INT_GPIOINT1A                      (98);
  constexpr std::uint32_t SYS_INT_GPIOINT1B                      (99);
  constexpr std::uint32_t SYS_INT_GPMCINT                        (100);
  constexpr std::uint32_t SYS_INT_DDRERR0                        (101);
  constexpr std::uint32_t SYS_INT_AES0_IRQ_S                     (102);
  constexpr std::uint32_t SYS_INT_AES0_IRQ_P                     (103);
  constexpr std::uint32_t SYS_INT_SHA_IRQ_S                      (108);
  constexpr std::uint32_t SYS_INT_SHA_IRQ_P                      (109);
  constexpr std::uint32_t SYS_INT_FPKA_SINTREQUEST_S             (110);
  constexpr std::uint32_t SYS_INT_RNG_IRQ                        (111);
  constexpr std::uint32_t SYS_INT_TCERRINT0                      (112);
  constexpr std::uint32_t SYS_INT_TCERRINT1                      (113);
  constexpr std::uint32_t SYS_INT_TCERRINT2                      (114);
  constexpr std::uint32_t SYS_INT_SMRFLX_Sabertooth              (120);
  constexpr std::uint32_t SYS_INT_SMRFLX_Core                    (121);
  constexpr std::uint32_t SYS_INT_DMA_INTR_PIN0                  (123);
  constexpr std::uint32_t SYS_INT_DMA_INTR_PIN1                  (124);
  constexpr std::uint32_t SYS_INT_SPI1INT                        (125);

  /*****************************************************************************
  **                     API FUNCTION PROTOTYPES
  *****************************************************************************/
  extern "C" void IntAINTCInit ();
  extern "C" void IntIfClkFreeRunSet();
  extern "C" void IntIfClkAutoGateSet();
  extern "C" void IntProtectionEnable();
  extern "C" void IntProtectionDisable();
  extern "C" void IntSyncClkFreeRunSet();
  extern "C" void IntSyncClkAutoGateSet();
  extern "C" void IntFuncClkFreeRunSet();
  extern "C" void IntFuncClkAutoGateSet();
  extern "C" void IntPriorityThresholdSet(std::uint32_t threshold);
  extern "C" void IntSoftwareIntSet(std::uint32_t intrNum);
  extern "C" void IntSoftwareIntClear(std::uint32_t intrNum);
  extern "C" void IntMasterIRQEnable();
  extern "C" void IntMasterIRQDisable();
  extern "C" void IntMasterFIQEnable();
  extern "C" void IntMasterFIQDisable();
  extern "C" void IntSystemEnable(std::uint32_t intrNum);
  extern "C" void IntSystemDisable(std::uint32_t intrNum);
  extern "C" void IntUnRegister(std::uint32_t intrNum);
  extern "C" void IntEnable(unsigned char  status);
  extern "C" void IntRegister(std::uint32_t intrNum, void (*pfnHandler)());
  extern "C" void IntPrioritySet(std::uint32_t intrNum, std::uint32_t priority,
                             std::uint32_t hostIntRoute);
  extern "C" unsigned char IntDisable();
  extern "C" std::uint32_t IntMasterStatusGet();
  extern "C" std::uint32_t IntActiveIrqNumGet();
  extern "C" std::uint32_t IntActiveFiqNumGet();
  extern "C" std::uint32_t IntSpurIrqFlagGet();
  extern "C" std::uint32_t IntSpurFiqFlagGet();
  extern "C" std::uint32_t IntCurrIrqPriorityGet();
  extern "C" std::uint32_t IntCurrFiqPriorityGet();
  extern "C" std::uint32_t IntPriorityThresholdGet();
  extern "C" std::uint32_t IntRawStatusGet(std::uint32_t intrNum);
  extern "C" std::uint32_t IntPendingIrqMaskedStatusGet(std::uint32_t intrNum);
  extern "C" std::uint32_t IntPendingFiqMaskedStatusGet(std::uint32_t intrNum);

#endif // _INTERRUPT_2013_06_21_H_
