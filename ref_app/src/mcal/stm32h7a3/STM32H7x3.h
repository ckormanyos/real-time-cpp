
#ifndef STM32H7X3_2022_11_25_H_
#define STM32H7X3_2022_11_25_H_

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

// Flash
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

// SCB
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

#ifdef __cplusplus
}
#endif

#define RCC   ((RCC_Type*)   UINT32_C(0x58024400))
#define Flash ((Flash_Type*) UINT32_C(0x52002000))
#define SCB   ((SCB_Type*)   UINT32_C(0xE000ED00))

#endif // STM32H7X3_2022_11_25_H_
