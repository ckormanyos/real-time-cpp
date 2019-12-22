#include <cstdint>

#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */


//  ARMCM4.h

typedef enum IRQn
{
/* -------------------  Cortex-M4 Processor Exceptions Numbers  ------------------- */
  NonMaskableInt_IRQn           = -14,      /*  2 Non Maskable Interrupt */
  HardFault_IRQn                = -13,      /*  3 HardFault Interrupt */
  MemoryManagement_IRQn         = -12,      /*  4 Memory Management Interrupt */
  BusFault_IRQn                 = -11,      /*  5 Bus Fault Interrupt */
  UsageFault_IRQn               = -10,      /*  6 Usage Fault Interrupt */
  SVCall_IRQn                   =  -5,      /* 11 SV Call Interrupt */
  DebugMonitor_IRQn             =  -4,      /* 12 Debug Monitor Interrupt */
  PendSV_IRQn                   =  -2,      /* 14 Pend SV Interrupt */
  SysTick_IRQn                  =  -1,      /* 15 System Tick Interrupt */

/* ----------------------  ARMCM4 Specific Interrupt Numbers  --------------------- */
  WDT_IRQn                      =   0,      /* Watchdog Timer Interrupt */
  RTC_IRQn                      =   1,      /* Real Time Clock Interrupt */
  TIM0_IRQn                     =   2,      /* Timer0 / Timer1 Interrupt */
  TIM2_IRQn                     =   3,      /* Timer2 / Timer3 Interrupt */
  MCIA_IRQn                     =   4,      /* MCIa Interrupt */
  MCIB_IRQn                     =   5,      /* MCIb Interrupt */
  UART0_IRQn                    =   6,      /* UART0 Interrupt */
  UART1_IRQn                    =   7,      /* UART1 Interrupt */
  UART2_IRQn                    =   8,      /* UART2 Interrupt */
  UART4_IRQn                    =   9,      /* UART4 Interrupt */
  AACI_IRQn                     =  10,      /* AACI / AC97 Interrupt */
  CLCD_IRQn                     =  11,      /* CLCD Combined Interrupt */
  ENET_IRQn                     =  12,      /* Ethernet Interrupt */
  USBDC_IRQn                    =  13,      /* USB Device Interrupt */
  USBHC_IRQn                    =  14,      /* USB Host Controller Interrupt */
  CHLCD_IRQn                    =  15,      /* Character LCD Interrupt */
  FLEXRAY_IRQn                  =  16,      /* Flexray Interrupt */
  CAN_IRQn                      =  17,      /* CAN Interrupt */
  LIN_IRQn                      =  18,      /* LIN Interrupt */
  I2C_IRQn                      =  19,      /* I2C ADC/DAC Interrupt */
  CPU_CLCD_IRQn                 =  28,      /* CPU CLCD Combined Interrupt */
  UART3_IRQn                    =  30,      /* UART3 Interrupt */
  SPI_IRQn                      =  31       /* SPI Touchscreen Interrupt */
} IRQn_Type;

/* --------  Configuration of the Cortex-M4 Processor and Core Peripherals  ------- */
#define __CM4_REV                 0x0001U   /* Core revision r0p1 */
#define __MPU_PRESENT             1         /* MPU present */
#define __VTOR_PRESENT            1         /* VTOR present */
#define __NVIC_PRIO_BITS          3         /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0         /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             0         /* no FPU present */



typedef struct
{
  __IM  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IOM uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __IOM uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IOM uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __IOM uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IOM uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IOM uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IOM uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __IOM uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IOM uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IOM uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __IOM uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IM  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __IM  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __IM  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IM  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IM  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[5U];
  __IOM uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
}
SCB_Type;

typedef struct
{
  __IOM uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[24U];
  __IOM uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RSERVED1[24U];
  __IOM uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[24U];
  __IOM uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32_t RESERVED3[24U];
  __IOM uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
        uint32_t RESERVED4[56U];
  __IOM uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
        uint32_t RESERVED5[644U];
  __OM  uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}
NVIC_Type;

typedef struct
{
  __IOM uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IOM uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __IOM uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __IM  uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
}
SysTick_Type;

/* Memory mapping of Cortex-M4 Hardware */
#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define ITM_BASE            (0xE0000000UL)                            /*!< ITM Base Address */
#define DWT_BASE            (0xE0001000UL)                            /*!< DWT Base Address */
#define TPI_BASE            (0xE0040000UL)                            /*!< TPI Base Address */
#define CoreDebug_BASE      (0xE000EDF0UL)                            /*!< Core Debug Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */

#define SCnSCB              ((SCnSCB_Type    *)     SCS_BASE      )   /*!< System control Register not in SCB */
#define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB configuration struct */
#define SysTick             ((SysTick_Type   *)     SysTick_BASE  )   /*!< SysTick configuration struct */
#define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC configuration struct */
#define ITM                 ((ITM_Type       *)     ITM_BASE      )   /*!< ITM configuration struct */
#define DWT                 ((DWT_Type       *)     DWT_BASE      )   /*!< DWT configuration struct */
#define TPI                 ((TPI_Type       *)     TPI_BASE      )   /*!< TPI configuration struct */
#define CoreDebug           ((CoreDebug_Type *)     CoreDebug_BASE)   /*!< Core Debug configuration struct */

#ifndef __NVIC_PRIO_BITS
  #define __NVIC_PRIO_BITS          4U
#endif

template<const std::int32_t  IRQn,
         const std::uint32_t priority,
         const std::uint32_t SCB_BASE_ADDRESS,
         const std::uint32_t SHP_OFFSET>
void NVIC_SetPriorityT()
{
  constexpr std::uint32_t address_to_set =   SCB_BASE_ADDRESS
                                           + SHP_OFFSET
                                           + (((((uint32_t)(int32_t) IRQn) & 0xFUL) - 4UL) * 1U);

  constexpr std::uint8_t value_to_set    = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t) 0xFFUL);

  *reinterpret_cast<std::uint8_t*>(address_to_set) = value_to_set;
}

extern "C"
uint32_t SysTick_Config(uint32_t ticks);

uint32_t SysTick_Config(uint32_t ticks)
{
  uint32_t result;

  if((ticks - UINT32_C(1)) > UINT32_C(0x00FFFFFF))
  {
    // Reload value impossible is too large.
    result = UINT32_C(1);
  }
  else
  {
    // Set the reload register.
    SysTick->LOAD  = static_cast<std::uint32_t>(ticks - UINT32_C(1));

    // Set the priority for the system tick interrupt.
    NVIC_SetPriorityT<SysTick_IRQn,
                      (1UL << __NVIC_PRIO_BITS) - 1UL,
                      0xE000E000 + 0x0D00,
                      0x18U>();

    // Load the system tick counter value.
    SysTick->VAL = UINT32_C(0);

    // Enable the system tick interrupt.
    // Set the clock source mask to the CPU frequency.
    // And start the system tick timer.
    SysTick->CTRL  = UINT32_C(7);

    result = UINT32_C(0);
  }

  return result;
}

#if 0
__STATIC_INLINE void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) < 0)
  {
    // index = 11 for IRQn = -1
    // SCB base = 0xE000E000 + 0x0D00
    // SHP offset = 0x18
    // SCB->SHP[11] address is (0xE000E000 + 0x0D00) + 0x18 + (11 * 1)
    SCB->SHP[(((uint32_t)(int32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
  else
  {
    NVIC->IP[((uint32_t)(int32_t)IRQn)]               = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
}
#endif
