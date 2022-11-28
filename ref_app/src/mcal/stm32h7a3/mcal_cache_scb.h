///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CACHE_SCB_2022_11_25_H_
#define MCAL_CACHE_SCB_2022_11_25_H_

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
} SCB_PartialType;

#ifdef __cplusplus
}
#endif

#define SCB_PARTIAL   ((SCB_PartialType*)   UINT32_C(0xE000ED00))

#endif // MCAL_CACHE_SCB_2022_11_25_H_
