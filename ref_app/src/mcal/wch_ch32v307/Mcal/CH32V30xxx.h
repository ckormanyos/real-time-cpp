
#ifndef CH32V30XXX_H
#define CH32V30XXX_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __IM
  #define __IM   volatile const
#endif
#ifndef __OM
  #define __OM   volatile
#endif
#ifndef __IOM
  #define __IOM  volatile
#endif

#include <stdint.h>

/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/* =========================================================================================================================== */
/* ================                                            RNG                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40023C00) RNG Structure                                              */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) control register                                           */
    
    struct {
      __IM  uint32_t            : 2;
      __IOM uint32_t RNGEN      : 1;            /*!< [2..2] Random number generator enable                                     */
      __IOM uint32_t IE         : 1;            /*!< [3..3] Interrupt enable                                                   */
    } bit;
  } CR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) status register                                            */
    
    struct {
      __IM  uint32_t DRDY       : 1;            /*!< [0..0] Data ready                                                         */
      __IM  uint32_t CECS       : 1;            /*!< [1..1] Clock error current status                                         */
      __IM  uint32_t SECS       : 1;            /*!< [2..2] Seed error current status                                          */
      __IM  uint32_t            : 2;
      __IOM uint32_t CEIS       : 1;            /*!< [5..5] Clock error interrupt status                                       */
      __IOM uint32_t SEIS       : 1;            /*!< [6..6] Seed error interrupt status                                        */
    } bit;
  } SR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000008) data register                                              */
    
    struct {
      __IM  uint32_t RNDATA     : 32;           /*!< [31..0] Random data                                                       */
    } bit;
  } DR;
} RNG_Type;                                     /*!< Size = 12 (0xc)                                                           */



/* =========================================================================================================================== */
/* ================                                            USB                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40005C00) USB Structure                                              */
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000000) endpoint 0 register                                        */
    
    struct {
      __IOM uint16_t EA         : 4;            /*!< [3..0] Endpoint address                                                   */
      __IOM uint16_t STAT_TX    : 2;            /*!< [5..4] Status bits, for transmission transfers                            */
      __IOM uint16_t DTOG_TX    : 1;            /*!< [6..6] Data Toggle, for transmission transfers                            */
      __IOM uint16_t CTR_TX     : 1;            /*!< [7..7] Correct Transfer for transmission                                  */
      __IOM uint16_t EP_KIND    : 1;            /*!< [8..8] Endpoint kind                                                      */
      __IOM uint16_t EP_TYPE    : 2;            /*!< [10..9] Endpoint type                                                     */
      __IOM uint16_t SETUP      : 1;            /*!< [11..11] Setup transaction completed                                      */
      __IOM uint16_t STAT_RX    : 2;            /*!< [13..12] Status bits, for reception transfers                             */
      __IOM uint16_t DTOG_RX    : 1;            /*!< [14..14] Data Toggle, for reception transfers                             */
      __IOM uint16_t CTR_RX     : 1;            /*!< [15..15] Correct transfer for reception                                   */
    } bit;
  } EP0R;
  __IM  uint16_t  RESERVED;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000004) endpoint 1 register                                        */
    
    struct {
      __IOM uint16_t EA         : 4;            /*!< [3..0] Endpoint address                                                   */
      __IOM uint16_t STAT_TX    : 2;            /*!< [5..4] Status bits, for transmission transfers                            */
      __IOM uint16_t DTOG_TX    : 1;            /*!< [6..6] Data Toggle, for transmission transfers                            */
      __IOM uint16_t CTR_TX     : 1;            /*!< [7..7] Correct Transfer for transmission                                  */
      __IOM uint16_t EP_KIND    : 1;            /*!< [8..8] Endpoint kind                                                      */
      __IOM uint16_t EP_TYPE    : 2;            /*!< [10..9] Endpoint type                                                     */
      __IOM uint16_t SETUP      : 1;            /*!< [11..11] Setup transaction completed                                      */
      __IOM uint16_t STAT_RX    : 2;            /*!< [13..12] Status bits, for reception transfers                             */
      __IOM uint16_t DTOG_RX    : 1;            /*!< [14..14] Data Toggle, for reception transfers                             */
      __IOM uint16_t CTR_RX     : 1;            /*!< [15..15] Correct transfer for reception                                   */
    } bit;
  } EP1R;
  __IM  uint16_t  RESERVED1;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000008) endpoint 2 register                                        */
    
    struct {
      __IOM uint16_t EA         : 4;            /*!< [3..0] Endpoint address                                                   */
      __IOM uint16_t STAT_TX    : 2;            /*!< [5..4] Status bits, for transmission transfers                            */
      __IOM uint16_t DTOG_TX    : 1;            /*!< [6..6] Data Toggle, for transmission transfers                            */
      __IOM uint16_t CTR_TX     : 1;            /*!< [7..7] Correct Transfer for transmission                                  */
      __IOM uint16_t EP_KIND    : 1;            /*!< [8..8] Endpoint kind                                                      */
      __IOM uint16_t EP_TYPE    : 2;            /*!< [10..9] Endpoint type                                                     */
      __IOM uint16_t SETUP      : 1;            /*!< [11..11] Setup transaction completed                                      */
      __IOM uint16_t STAT_RX    : 2;            /*!< [13..12] Status bits, for reception transfers                             */
      __IOM uint16_t DTOG_RX    : 1;            /*!< [14..14] Data Toggle, for reception transfers                             */
      __IOM uint16_t CTR_RX     : 1;            /*!< [15..15] Correct transfer for reception                                   */
    } bit;
  } EP2R;
  __IM  uint16_t  RESERVED2;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000000C) endpoint 3 register                                        */
    
    struct {
      __IOM uint16_t EA         : 4;            /*!< [3..0] Endpoint address                                                   */
      __IOM uint16_t STAT_TX    : 2;            /*!< [5..4] Status bits, for transmission transfers                            */
      __IOM uint16_t DTOG_TX    : 1;            /*!< [6..6] Data Toggle, for transmission transfers                            */
      __IOM uint16_t CTR_TX     : 1;            /*!< [7..7] Correct Transfer for transmission                                  */
      __IOM uint16_t EP_KIND    : 1;            /*!< [8..8] Endpoint kind                                                      */
      __IOM uint16_t EP_TYPE    : 2;            /*!< [10..9] Endpoint type                                                     */
      __IOM uint16_t SETUP      : 1;            /*!< [11..11] Setup transaction completed                                      */
      __IOM uint16_t STAT_RX    : 2;            /*!< [13..12] Status bits, for reception transfers                             */
      __IOM uint16_t DTOG_RX    : 1;            /*!< [14..14] Data Toggle, for reception transfers                             */
      __IOM uint16_t CTR_RX     : 1;            /*!< [15..15] Correct transfer for reception                                   */
    } bit;
  } EP3R;
  __IM  uint16_t  RESERVED3;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000010) endpoint 4 register                                        */
    
    struct {
      __IOM uint16_t EA         : 4;            /*!< [3..0] Endpoint address                                                   */
      __IOM uint16_t STAT_TX    : 2;            /*!< [5..4] Status bits, for transmission transfers                            */
      __IOM uint16_t DTOG_TX    : 1;            /*!< [6..6] Data Toggle, for transmission transfers                            */
      __IOM uint16_t CTR_TX     : 1;            /*!< [7..7] Correct Transfer for transmission                                  */
      __IOM uint16_t EP_KIND    : 1;            /*!< [8..8] Endpoint kind                                                      */
      __IOM uint16_t EP_TYPE    : 2;            /*!< [10..9] Endpoint type                                                     */
      __IOM uint16_t SETUP      : 1;            /*!< [11..11] Setup transaction completed                                      */
      __IOM uint16_t STAT_RX    : 2;            /*!< [13..12] Status bits, for reception transfers                             */
      __IOM uint16_t DTOG_RX    : 1;            /*!< [14..14] Data Toggle, for reception transfers                             */
      __IOM uint16_t CTR_RX     : 1;            /*!< [15..15] Correct transfer for reception                                   */
    } bit;
  } EP4R;
  __IM  uint16_t  RESERVED4;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000014) endpoint 5 register                                        */
    
    struct {
      __IOM uint16_t EA         : 4;            /*!< [3..0] Endpoint address                                                   */
      __IOM uint16_t STAT_TX    : 2;            /*!< [5..4] Status bits, for transmission transfers                            */
      __IOM uint16_t DTOG_TX    : 1;            /*!< [6..6] Data Toggle, for transmission transfers                            */
      __IOM uint16_t CTR_TX     : 1;            /*!< [7..7] Correct Transfer for transmission                                  */
      __IOM uint16_t EP_KIND    : 1;            /*!< [8..8] Endpoint kind                                                      */
      __IOM uint16_t EP_TYPE    : 2;            /*!< [10..9] Endpoint type                                                     */
      __IOM uint16_t SETUP      : 1;            /*!< [11..11] Setup transaction completed                                      */
      __IOM uint16_t STAT_RX    : 2;            /*!< [13..12] Status bits, for reception transfers                             */
      __IOM uint16_t DTOG_RX    : 1;            /*!< [14..14] Data Toggle, for reception transfers                             */
      __IOM uint16_t CTR_RX     : 1;            /*!< [15..15] Correct transfer for reception                                   */
    } bit;
  } EP5R;
  __IM  uint16_t  RESERVED5;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000018) endpoint 6 register                                        */
    
    struct {
      __IOM uint16_t EA         : 4;            /*!< [3..0] Endpoint address                                                   */
      __IOM uint16_t STAT_TX    : 2;            /*!< [5..4] Status bits, for transmission transfers                            */
      __IOM uint16_t DTOG_TX    : 1;            /*!< [6..6] Data Toggle, for transmission transfers                            */
      __IOM uint16_t CTR_TX     : 1;            /*!< [7..7] Correct Transfer for transmission                                  */
      __IOM uint16_t EP_KIND    : 1;            /*!< [8..8] Endpoint kind                                                      */
      __IOM uint16_t EP_TYPE    : 2;            /*!< [10..9] Endpoint type                                                     */
      __IOM uint16_t SETUP      : 1;            /*!< [11..11] Setup transaction completed                                      */
      __IOM uint16_t STAT_RX    : 2;            /*!< [13..12] Status bits, for reception transfers                             */
      __IOM uint16_t DTOG_RX    : 1;            /*!< [14..14] Data Toggle, for reception transfers                             */
      __IOM uint16_t CTR_RX     : 1;            /*!< [15..15] Correct transfer for reception                                   */
    } bit;
  } EP6R;
  __IM  uint16_t  RESERVED6;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000001C) endpoint 7 register                                        */
    
    struct {
      __IOM uint16_t EA         : 4;            /*!< [3..0] Endpoint address                                                   */
      __IOM uint16_t STAT_TX    : 2;            /*!< [5..4] Status bits, for transmission transfers                            */
      __IOM uint16_t DTOG_TX    : 1;            /*!< [6..6] Data Toggle, for transmission transfers                            */
      __IOM uint16_t CTR_TX     : 1;            /*!< [7..7] Correct Transfer for transmission                                  */
      __IOM uint16_t EP_KIND    : 1;            /*!< [8..8] Endpoint kind                                                      */
      __IOM uint16_t EP_TYPE    : 2;            /*!< [10..9] Endpoint type                                                     */
      __IOM uint16_t SETUP      : 1;            /*!< [11..11] Setup transaction completed                                      */
      __IOM uint16_t STAT_RX    : 2;            /*!< [13..12] Status bits, for reception transfers                             */
      __IOM uint16_t DTOG_RX    : 1;            /*!< [14..14] Data Toggle, for reception transfers                             */
      __IOM uint16_t CTR_RX     : 1;            /*!< [15..15] Correct transfer for reception                                   */
    } bit;
  } EP7R;
  __IM  uint16_t  RESERVED7;
  __IM  uint32_t  RESERVED8[8];
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000040) control register                                           */
    
    struct {
      __IOM uint16_t FRES       : 1;            /*!< [0..0] Force USB Reset                                                    */
      __IOM uint16_t PDWN       : 1;            /*!< [1..1] Power down                                                         */
      __IOM uint16_t LPMODE     : 1;            /*!< [2..2] Low-power mode                                                     */
      __IOM uint16_t FSUSP      : 1;            /*!< [3..3] Force suspend                                                      */
      __IOM uint16_t RESUME     : 1;            /*!< [4..4] Resume request                                                     */
      __IM  uint16_t            : 3;
      __IOM uint16_t ESOFM      : 1;            /*!< [8..8] Expected start of frame interrupt mask                             */
      __IOM uint16_t SOFM       : 1;            /*!< [9..9] Start of frame interrupt mask                                      */
      __IOM uint16_t RESETM     : 1;            /*!< [10..10] USB reset interrupt mask                                         */
      __IOM uint16_t SUSPM      : 1;            /*!< [11..11] Suspend mode interrupt mask                                      */
      __IOM uint16_t WKUPM      : 1;            /*!< [12..12] Wakeup interrupt mask                                            */
      __IOM uint16_t ERRM       : 1;            /*!< [13..13] Error interrupt mask                                             */
      __IOM uint16_t PMAOVRM    : 1;            /*!< [14..14] Packet memory area over / underrun interrupt mask                */
      __IOM uint16_t CTRM       : 1;            /*!< [15..15] Correct transfer interrupt mask                                  */
    } bit;
  } CNTR;
  __IM  uint16_t  RESERVED9;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000044) interrupt status register                                  */
    
    struct {
      __IOM uint16_t EP_ID      : 4;            /*!< [3..0] Endpoint Identifier                                                */
      __IOM uint16_t DIR        : 1;            /*!< [4..4] Direction of transaction                                           */
      __IM  uint16_t            : 3;
      __IOM uint16_t ESOF       : 1;            /*!< [8..8] Expected start frame                                               */
      __IOM uint16_t SOF        : 1;            /*!< [9..9] start of frame                                                     */
      __IOM uint16_t RESET      : 1;            /*!< [10..10] reset request                                                    */
      __IOM uint16_t SUSP       : 1;            /*!< [11..11] Suspend mode request                                             */
      __IOM uint16_t WKUP       : 1;            /*!< [12..12] Wakeup                                                           */
      __IOM uint16_t ERR        : 1;            /*!< [13..13] Error                                                            */
      __IOM uint16_t PMAOVR     : 1;            /*!< [14..14] Packet memory area over / underrun                               */
      __IOM uint16_t CTR        : 1;            /*!< [15..15] Correct transfer                                                 */
    } bit;
  } ISTR;
  __IM  uint16_t  RESERVED10;
  
  union {
    __IM  uint16_t reg;                         /*!< (@ 0x00000048) frame number register                                      */
    
    struct {
      __IM  uint16_t FN         : 11;           /*!< [10..0] Frame number                                                      */
      __IM  uint16_t LSOF       : 2;            /*!< [12..11] Lost SOF                                                         */
      __IM  uint16_t LCK        : 1;            /*!< [13..13] Locked                                                           */
      __IM  uint16_t RXDM       : 1;            /*!< [14..14] Receive data - line status                                       */
      __IM  uint16_t RXDP       : 1;            /*!< [15..15] Receive data + line status                                       */
    } bit;
  } FNR;
  __IM  uint16_t  RESERVED11;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000004C) device address                                             */
    
    struct {
      __IOM uint16_t ADD        : 7;            /*!< [6..0] Device address                                                     */
      __IOM uint16_t EF         : 1;            /*!< [7..7] Enable function                                                    */
    } bit;
  } DADDR;
  __IM  uint16_t  RESERVED12;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000050) Buffer table address                                       */
    
    struct {
      __IM  uint32_t            : 3;
      __IOM uint32_t BTABLE     : 13;           /*!< [15..3] Buffer table                                                      */
    } bit;
  } BTABLE;
} USB_Type;                                     /*!< Size = 84 (0x54)                                                          */



/* =========================================================================================================================== */
/* ================                                           CAN1                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40006400) CAN1 Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) CAN Master control register                                */
    
    struct {
      __IOM uint32_t INRQ       : 1;            /*!< [0..0] Initialization request                                             */
      __IOM uint32_t SLEEP      : 1;            /*!< [1..1] Sleep mode request                                                 */
      __IOM uint32_t TXFP       : 1;            /*!< [2..2] Transmit FIFO priority                                             */
      __IOM uint32_t RFLM       : 1;            /*!< [3..3] Receive FIFO locked mode                                           */
      __IOM uint32_t NART       : 1;            /*!< [4..4] No automatic retransmission                                        */
      __IOM uint32_t AWUM       : 1;            /*!< [5..5] Automatic wakeup mode                                              */
      __IOM uint32_t ABOM       : 1;            /*!< [6..6] Automatic bus-off management                                       */
      __IOM uint32_t TTCM       : 1;            /*!< [7..7] Time triggered communication mode                                  */
      __IM  uint32_t            : 7;
      __IOM uint32_t RESET      : 1;            /*!< [15..15] Software master reset                                            */
      __IOM uint32_t DBF        : 1;            /*!< [16..16] Debug freeze                                                     */
    } bit;
  } CTLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) CAN master status register                                 */
    
    struct {
      __IM  uint32_t INAK       : 1;            /*!< [0..0] Initialization acknowledge                                         */
      __IM  uint32_t SLAK       : 1;            /*!< [1..1] Sleep acknowledge                                                  */
      __IOM uint32_t ERRI       : 1;            /*!< [2..2] Error interrupt                                                    */
      __IOM uint32_t WKUI       : 1;            /*!< [3..3] Wakeup interrupt                                                   */
      __IOM uint32_t SLAKI      : 1;            /*!< [4..4] Sleep acknowledge interrupt                                        */
      __IM  uint32_t            : 3;
      __IM  uint32_t TXM        : 1;            /*!< [8..8] Transmit mode                                                      */
      __IM  uint32_t RXM        : 1;            /*!< [9..9] Receive mode                                                       */
      __IM  uint32_t SAMP       : 1;            /*!< [10..10] Last sample point                                                */
      __IM  uint32_t RX         : 1;            /*!< [11..11] Rx signal                                                        */
    } bit;
  } STATR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) CAN transmit status register                               */
    
    struct {
      __IOM uint32_t RQCP0      : 1;            /*!< [0..0] Request completed mailbox0                                         */
      __IOM uint32_t TXOK0      : 1;            /*!< [1..1] Transmission OK of mailbox0                                        */
      __IOM uint32_t ALST0      : 1;            /*!< [2..2] Arbitration lost for mailbox0                                      */
      __IOM uint32_t TERR0      : 1;            /*!< [3..3] Transmission error of mailbox0                                     */
      __IM  uint32_t            : 3;
      __IOM uint32_t ABRQ0      : 1;            /*!< [7..7] Abort request for mailbox0                                         */
      __IOM uint32_t RQCP1      : 1;            /*!< [8..8] Request completed mailbox1                                         */
      __IOM uint32_t TXOK1      : 1;            /*!< [9..9] Transmission OK of mailbox1                                        */
      __IOM uint32_t ALST1      : 1;            /*!< [10..10] Arbitration lost for mailbox1                                    */
      __IOM uint32_t TERR1      : 1;            /*!< [11..11] Transmission error of mailbox1                                   */
      __IM  uint32_t            : 3;
      __IOM uint32_t ABRQ1      : 1;            /*!< [15..15] Abort request for mailbox 1                                      */
      __IOM uint32_t RQCP2      : 1;            /*!< [16..16] Request completed mailbox2                                       */
      __IOM uint32_t TXOK2      : 1;            /*!< [17..17] Transmission OK of mailbox 2                                     */
      __IOM uint32_t ALST2      : 1;            /*!< [18..18] Arbitration lost for mailbox 2                                   */
      __IOM uint32_t TERR2      : 1;            /*!< [19..19] Transmission error of mailbox 2                                  */
      __IM  uint32_t            : 3;
      __IOM uint32_t ABRQ2      : 1;            /*!< [23..23] Abort request for mailbox 2                                      */
      __IM  uint32_t CODE       : 2;            /*!< [25..24] Mailbox code                                                     */
      __IM  uint32_t TME0       : 1;            /*!< [26..26] Transmit mailbox 0 empty                                         */
      __IM  uint32_t TME1       : 1;            /*!< [27..27] Transmit mailbox 1 empty                                         */
      __IM  uint32_t TME2       : 1;            /*!< [28..28] Transmit mailbox 2 empty                                         */
      __IM  uint32_t LOW0       : 1;            /*!< [29..29] Lowest priority flag for mailbox 0                               */
      __IM  uint32_t LOW1       : 1;            /*!< [30..30] Lowest priority flag for mailbox 1                               */
      __IM  uint32_t LOW2       : 1;            /*!< [31..31] Lowest priority flag for mailbox 2                               */
    } bit;
  } TSTATR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) CAN receive FIFO 0 register                                */
    
    struct {
      __IM  uint32_t FMP0       : 2;            /*!< [1..0] FIFO 0 message pending                                             */
      __IM  uint32_t            : 1;
      __IOM uint32_t FULL0      : 1;            /*!< [3..3] FIFO 0 full                                                        */
      __IOM uint32_t FOVR0      : 1;            /*!< [4..4] FIFO 0 overrun                                                     */
      __IOM uint32_t RFOM0      : 1;            /*!< [5..5] Release FIFO 0 output mailbox                                      */
    } bit;
  } RFIFO0;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) CAN receive FIFO 1 register                                */
    
    struct {
      __IM  uint32_t FMP1       : 2;            /*!< [1..0] FIFO 1 message pending                                             */
      __IM  uint32_t            : 1;
      __IOM uint32_t FULL1      : 1;            /*!< [3..3] FIFO 1 full                                                        */
      __IOM uint32_t FOVR1      : 1;            /*!< [4..4] FIFO 1 overrun                                                     */
      __IOM uint32_t RFOM1      : 1;            /*!< [5..5] Release FIFO 1 output mailbox                                      */
    } bit;
  } RFIFO1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) CAN interrupt enable register                              */
    
    struct {
      __IOM uint32_t TMEIE      : 1;            /*!< [0..0] Transmit mailbox empty interrupt  enable                           */
      __IOM uint32_t FMPIE0     : 1;            /*!< [1..1] FIFO message pending interrupt  enable                             */
      __IOM uint32_t FFIE0      : 1;            /*!< [2..2] FIFO full interrupt  enable                                        */
      __IOM uint32_t FOVIE0     : 1;            /*!< [3..3] FIFO overrun interrupt  enable                                     */
      __IOM uint32_t FMPIE1     : 1;            /*!< [4..4] FIFO message pending interrupt  enable                             */
      __IOM uint32_t FFIE1      : 1;            /*!< [5..5] FIFO full interrupt  enable                                        */
      __IOM uint32_t FOVIE1     : 1;            /*!< [6..6] FIFO overrun interrupt  enable                                     */
      __IM  uint32_t            : 1;
      __IOM uint32_t EWGIE      : 1;            /*!< [8..8] Error warning interrupt  enable                                    */
      __IOM uint32_t EPVIE      : 1;            /*!< [9..9] Error passive interrupt  enable                                    */
      __IOM uint32_t BOFIE      : 1;            /*!< [10..10] Bus-off interrupt  enable                                        */
      __IOM uint32_t LECIE      : 1;            /*!< [11..11] Last error code interrupt  enable                                */
      __IM  uint32_t            : 3;
      __IOM uint32_t ERRIE      : 1;            /*!< [15..15] Error interrupt  enable                                          */
      __IOM uint32_t WKUIE      : 1;            /*!< [16..16] Wakeup interrupt  enable                                         */
      __IOM uint32_t SLKIE      : 1;            /*!< [17..17] Sleep interrupt  enable                                          */
    } bit;
  } INTENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) CAN error status register                                  */
    
    struct {
      __IM  uint32_t EWGF       : 1;            /*!< [0..0] Error warning  flag                                                */
      __IM  uint32_t EPVF       : 1;            /*!< [1..1] Error passive  flag                                                */
      __IM  uint32_t BOFF       : 1;            /*!< [2..2] Bus-off  flag                                                      */
      __IM  uint32_t            : 1;
      __IOM uint32_t LEC        : 3;            /*!< [6..4] Last error code                                                    */
      __IM  uint32_t            : 9;
      __IM  uint32_t TEC        : 8;            /*!< [23..16] Least significant byte of the 9-bit transmit error
                                                     counter                                                                   */
      __IM  uint32_t REC        : 8;            /*!< [31..24] Receive error counter                                            */
    } bit;
  } ERRSR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) CAN bit timing register                                    */
    
    struct {
      __IOM uint32_t BRP        : 10;           /*!< [9..0] Baud rate prescaler                                                */
      __IM  uint32_t            : 6;
      __IOM uint32_t TS1        : 4;            /*!< [19..16] Time segment 1                                                   */
      __IOM uint32_t TS2        : 3;            /*!< [22..20] Time segment 2                                                   */
      __IM  uint32_t            : 1;
      __IOM uint32_t SJW        : 2;            /*!< [25..24] Resynchronization jump width                                     */
      __IM  uint32_t            : 4;
      __IOM uint32_t LBKM       : 1;            /*!< [30..30] Loop back mode (debug)                                           */
      __IOM uint32_t SILM       : 1;            /*!< [31..31] Silent mode (debug)                                              */
    } bit;
  } BTIMR;
  __IM  uint32_t  RESERVED[88];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000180) CAN TX mailbox identifier register                         */
    
    struct {
      __IOM uint32_t TXRQ       : 1;            /*!< [0..0] Transmit mailbox request                                           */
      __IOM uint32_t RTR        : 1;            /*!< [1..1] Remote transmission request                                        */
      __IOM uint32_t IDE        : 1;            /*!< [2..2] Identifier extension                                               */
      __IOM uint32_t EXID       : 18;           /*!< [20..3] extended identifier                                               */
      __IOM uint32_t STID       : 11;           /*!< [31..21] Standard identifier                                              */
    } bit;
  } TXMIR0;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000184) CAN mailbox data length control and time stamp
                                                                    register                                                   */
    
    struct {
      __IOM uint32_t DLC        : 4;            /*!< [3..0] Data length code                                                   */
      __IM  uint32_t            : 4;
      __IOM uint32_t TGT        : 1;            /*!< [8..8] Transmit global time                                               */
      __IM  uint32_t            : 7;
      __IOM uint32_t TIME       : 16;           /*!< [31..16] Message time stamp                                               */
    } bit;
  } TXMDTR0;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000188) CAN mailbox data low register                              */
    
    struct {
      __IOM uint32_t DATA0      : 8;            /*!< [7..0] Data byte 0                                                        */
      __IOM uint32_t DATA1      : 8;            /*!< [15..8] Data byte 1                                                       */
      __IOM uint32_t DATA2      : 8;            /*!< [23..16] Data byte 2                                                      */
      __IOM uint32_t DATA3      : 8;            /*!< [31..24] Data byte 3                                                      */
    } bit;
  } TXMDLR0;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000018C) CAN mailbox data high register                             */
    
    struct {
      __IOM uint32_t DATA4      : 8;            /*!< [7..0] Data byte 4                                                        */
      __IOM uint32_t DATA5      : 8;            /*!< [15..8] Data byte 5                                                       */
      __IOM uint32_t DATA6      : 8;            /*!< [23..16] Data byte 6                                                      */
      __IOM uint32_t DATA7      : 8;            /*!< [31..24] Data byte 7                                                      */
    } bit;
  } TXMDHR0;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000190) CAN TX mailbox identifier register                         */
    
    struct {
      __IOM uint32_t TXRQ       : 1;            /*!< [0..0] Transmit mailbox request                                           */
      __IOM uint32_t RTR        : 1;            /*!< [1..1] Remote transmission request                                        */
      __IOM uint32_t IDE        : 1;            /*!< [2..2] Identifier extension                                               */
      __IOM uint32_t EXID       : 18;           /*!< [20..3] extended identifier                                               */
      __IOM uint32_t STID       : 11;           /*!< [31..21] Standard identifier                                              */
    } bit;
  } TXMIR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000194) CAN mailbox data length control and time stamp
                                                                    register                                                   */
    
    struct {
      __IOM uint32_t DLC        : 4;            /*!< [3..0] Data length code                                                   */
      __IM  uint32_t            : 4;
      __IOM uint32_t TGT        : 1;            /*!< [8..8] Transmit global time                                               */
      __IM  uint32_t            : 7;
      __IOM uint32_t TIME       : 16;           /*!< [31..16] Message time stamp                                               */
    } bit;
  } TXMDTR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000198) CAN mailbox data low register                              */
    
    struct {
      __IOM uint32_t DATA0      : 8;            /*!< [7..0] Data byte 0                                                        */
      __IOM uint32_t DATA1      : 8;            /*!< [15..8] Data byte 1                                                       */
      __IOM uint32_t DATA2      : 8;            /*!< [23..16] Data byte 2                                                      */
      __IOM uint32_t DATA3      : 8;            /*!< [31..24] Data byte 3                                                      */
    } bit;
  } TXMDLR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000019C) CAN mailbox data high register                             */
    
    struct {
      __IOM uint32_t DATA4      : 8;            /*!< [7..0] Data byte 4                                                        */
      __IOM uint32_t DATA5      : 8;            /*!< [15..8] Data byte 5                                                       */
      __IOM uint32_t DATA6      : 8;            /*!< [23..16] Data byte 6                                                      */
      __IOM uint32_t DATA7      : 8;            /*!< [31..24] Data byte 7                                                      */
    } bit;
  } TXMDHR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000001A0) CAN TX mailbox identifier register                         */
    
    struct {
      __IOM uint32_t TXRQ       : 1;            /*!< [0..0] Transmit mailbox request                                           */
      __IOM uint32_t RTR        : 1;            /*!< [1..1] Remote transmission request                                        */
      __IOM uint32_t IDE        : 1;            /*!< [2..2] Identifier extension                                               */
      __IOM uint32_t EXID       : 18;           /*!< [20..3] extended identifier                                               */
      __IOM uint32_t STID       : 11;           /*!< [31..21] Standard identifier                                              */
    } bit;
  } TXMIR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000001A4) CAN mailbox data length control and time stamp
                                                                    register                                                   */
    
    struct {
      __IOM uint32_t DLC        : 4;            /*!< [3..0] Data length code                                                   */
      __IM  uint32_t            : 4;
      __IOM uint32_t TGT        : 1;            /*!< [8..8] Transmit global time                                               */
      __IM  uint32_t            : 7;
      __IOM uint32_t TIME       : 16;           /*!< [31..16] Message time stamp                                               */
    } bit;
  } TXMDTR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000001A8) CAN mailbox data low register                              */
    
    struct {
      __IOM uint32_t DATA0      : 8;            /*!< [7..0] Data byte 0                                                        */
      __IOM uint32_t DATA1      : 8;            /*!< [15..8] Data byte 1                                                       */
      __IOM uint32_t DATA2      : 8;            /*!< [23..16] Data byte 2                                                      */
      __IOM uint32_t DATA3      : 8;            /*!< [31..24] Data byte 3                                                      */
    } bit;
  } TXMDLR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000001AC) CAN mailbox data high register                             */
    
    struct {
      __IOM uint32_t DATA4      : 8;            /*!< [7..0] Data byte 4                                                        */
      __IOM uint32_t DATA5      : 8;            /*!< [15..8] Data byte 5                                                       */
      __IOM uint32_t DATA6      : 8;            /*!< [23..16] Data byte 6                                                      */
      __IOM uint32_t DATA7      : 8;            /*!< [31..24] Data byte 7                                                      */
    } bit;
  } TXMDHR2;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x000001B0) CAN receive FIFO mailbox identifier register               */
    
    struct {
      __IM  uint32_t            : 1;
      __IM  uint32_t RTR        : 1;            /*!< [1..1] Remote transmission request                                        */
      __IM  uint32_t IDE        : 1;            /*!< [2..2] Identifier extension                                               */
      __IM  uint32_t EXID       : 18;           /*!< [20..3] extended identifier                                               */
      __IM  uint32_t STID       : 11;           /*!< [31..21] Standard identifier                                              */
    } bit;
  } RXMIR0;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x000001B4) CAN receive FIFO mailbox data length control
                                                                    and time stamp  register                                   */
    
    struct {
      __IM  uint32_t DLC        : 4;            /*!< [3..0] Data length code                                                   */
      __IM  uint32_t            : 4;
      __IM  uint32_t FMI        : 8;            /*!< [15..8] Filter match index                                                */
      __IM  uint32_t TIME       : 16;           /*!< [31..16] Message time stamp                                               */
    } bit;
  } RXMDTR0;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x000001B8) CAN receive FIFO mailbox data low register                 */
    
    struct {
      __IM  uint32_t DATA0      : 8;            /*!< [7..0] Data Byte 0                                                        */
      __IM  uint32_t DATA1      : 8;            /*!< [15..8] Data Byte 1                                                       */
      __IM  uint32_t DATA2      : 8;            /*!< [23..16] Data Byte 2                                                      */
      __IM  uint32_t DATA3      : 8;            /*!< [31..24] Data Byte 3                                                      */
    } bit;
  } RXMDLR0;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x000001BC) CAN receive FIFO mailbox data high register                */
    
    struct {
      __IM  uint32_t DATA4      : 8;            /*!< [7..0] DATA4                                                              */
      __IM  uint32_t DATA5      : 8;            /*!< [15..8] DATA5                                                             */
      __IM  uint32_t DATA6      : 8;            /*!< [23..16] DATA6                                                            */
      __IM  uint32_t DATA7      : 8;            /*!< [31..24] DATA7                                                            */
    } bit;
  } RXMDHR0;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x000001C0) CAN receive FIFO mailbox identifier register               */
    
    struct {
      __IM  uint32_t            : 1;
      __IM  uint32_t RTR        : 1;            /*!< [1..1] Remote transmission request                                        */
      __IM  uint32_t IDE        : 1;            /*!< [2..2] Identifier extension                                               */
      __IM  uint32_t EXID       : 18;           /*!< [20..3] extended identifier                                               */
      __IM  uint32_t STID       : 11;           /*!< [31..21] Standard identifier                                              */
    } bit;
  } RXMIR1;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x000001C4) CAN receive FIFO mailbox data length control
                                                                    and time stamp  register                                   */
    
    struct {
      __IM  uint32_t DLC        : 4;            /*!< [3..0] Data length code                                                   */
      __IM  uint32_t            : 4;
      __IM  uint32_t FMI        : 8;            /*!< [15..8] Filter match index                                                */
      __IM  uint32_t TIME       : 16;           /*!< [31..16] Message time stamp                                               */
    } bit;
  } RXMDTR1;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x000001C8) CAN receive FIFO mailbox data low register                 */
    
    struct {
      __IM  uint32_t DATA0      : 8;            /*!< [7..0] Data Byte 0                                                        */
      __IM  uint32_t DATA1      : 8;            /*!< [15..8] Data Byte 1                                                       */
      __IM  uint32_t DATA2      : 8;            /*!< [23..16] Data Byte 2                                                      */
      __IM  uint32_t DATA3      : 8;            /*!< [31..24] Data Byte 3                                                      */
    } bit;
  } RXMDLR1;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x000001CC) CAN receive FIFO mailbox data high register                */
    
    struct {
      __IM  uint32_t DATA4      : 8;            /*!< [7..0] DATA4                                                              */
      __IM  uint32_t DATA5      : 8;            /*!< [15..8] DATA5                                                             */
      __IM  uint32_t DATA6      : 8;            /*!< [23..16] DATA6                                                            */
      __IM  uint32_t DATA7      : 8;            /*!< [31..24] DATA7                                                            */
    } bit;
  } RXMDHR1;
  __IM  uint32_t  RESERVED1[12];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000200) CAN filter master register                                 */
    
    struct {
      __IOM uint32_t FINIT      : 1;            /*!< [0..0] Filter init mode                                                   */
      __IM  uint32_t            : 7;
      __IOM uint32_t CAN2SB     : 6;            /*!< [13..8] CAN2 start bank                                                   */
    } bit;
  } FCTLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000204) CAN filter mode register                                   */
    
    struct {
      __IOM uint32_t FBM0       : 1;            /*!< [0..0] Filter mode                                                        */
      __IOM uint32_t FBM1       : 1;            /*!< [1..1] Filter mode                                                        */
      __IOM uint32_t FBM2       : 1;            /*!< [2..2] Filter mode                                                        */
      __IOM uint32_t FBM3       : 1;            /*!< [3..3] Filter mode                                                        */
      __IOM uint32_t FBM4       : 1;            /*!< [4..4] Filter mode                                                        */
      __IOM uint32_t FBM5       : 1;            /*!< [5..5] Filter mode                                                        */
      __IOM uint32_t FBM6       : 1;            /*!< [6..6] Filter mode                                                        */
      __IOM uint32_t FBM7       : 1;            /*!< [7..7] Filter mode                                                        */
      __IOM uint32_t FBM8       : 1;            /*!< [8..8] Filter mode                                                        */
      __IOM uint32_t FBM9       : 1;            /*!< [9..9] Filter mode                                                        */
      __IOM uint32_t FBM10      : 1;            /*!< [10..10] Filter mode                                                      */
      __IOM uint32_t FBM11      : 1;            /*!< [11..11] Filter mode                                                      */
      __IOM uint32_t FBM12      : 1;            /*!< [12..12] Filter mode                                                      */
      __IOM uint32_t FBM13      : 1;            /*!< [13..13] Filter mode                                                      */
    } bit;
  } FMCFGR;
  __IM  uint32_t  RESERVED2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000020C) CAN filter scale register                                  */
    
    struct {
      __IOM uint32_t FSC0       : 1;            /*!< [0..0] Filter scale configuration                                         */
      __IOM uint32_t FSC1       : 1;            /*!< [1..1] Filter scale configuration                                         */
      __IOM uint32_t FSC2       : 1;            /*!< [2..2] Filter scale configuration                                         */
      __IOM uint32_t FSC3       : 1;            /*!< [3..3] Filter scale configuration                                         */
      __IOM uint32_t FSC4       : 1;            /*!< [4..4] Filter scale configuration                                         */
      __IOM uint32_t FSC5       : 1;            /*!< [5..5] Filter scale configuration                                         */
      __IOM uint32_t FSC6       : 1;            /*!< [6..6] Filter scale configuration                                         */
      __IOM uint32_t FSC7       : 1;            /*!< [7..7] Filter scale configuration                                         */
      __IOM uint32_t FSC8       : 1;            /*!< [8..8] Filter scale configuration                                         */
      __IOM uint32_t FSC9       : 1;            /*!< [9..9] Filter scale configuration                                         */
      __IOM uint32_t FSC10      : 1;            /*!< [10..10] Filter scale configuration                                       */
      __IOM uint32_t FSC11      : 1;            /*!< [11..11] Filter scale configuration                                       */
      __IOM uint32_t FSC12      : 1;            /*!< [12..12] Filter scale configuration                                       */
      __IOM uint32_t FSC13      : 1;            /*!< [13..13] Filter scale configuration                                       */
    } bit;
  } FSCFGR;
  __IM  uint32_t  RESERVED3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000214) CAN filter FIFO assignment register                        */
    
    struct {
      __IOM uint32_t FFA0       : 1;            /*!< [0..0] Filter FIFO assignment for filter 0                                */
      __IOM uint32_t FFA1       : 1;            /*!< [1..1] Filter FIFO assignment for filter 1                                */
      __IOM uint32_t FFA2       : 1;            /*!< [2..2] Filter FIFO assignment for filter 2                                */
      __IOM uint32_t FFA3       : 1;            /*!< [3..3] Filter FIFO assignment for filter 3                                */
      __IOM uint32_t FFA4       : 1;            /*!< [4..4] Filter FIFO assignment for filter 4                                */
      __IOM uint32_t FFA5       : 1;            /*!< [5..5] Filter FIFO assignment for filter 5                                */
      __IOM uint32_t FFA6       : 1;            /*!< [6..6] Filter FIFO assignment for filter 6                                */
      __IOM uint32_t FFA7       : 1;            /*!< [7..7] Filter FIFO assignment for filter 7                                */
      __IOM uint32_t FFA8       : 1;            /*!< [8..8] Filter FIFO assignment for filter 8                                */
      __IOM uint32_t FFA9       : 1;            /*!< [9..9] Filter FIFO assignment for filter 9                                */
      __IOM uint32_t FFA10      : 1;            /*!< [10..10] Filter FIFO assignment for filter 10                             */
      __IOM uint32_t FFA11      : 1;            /*!< [11..11] Filter FIFO assignment for filter 11                             */
      __IOM uint32_t FFA12      : 1;            /*!< [12..12] Filter FIFO assignment for filter 12                             */
      __IOM uint32_t FFA13      : 1;            /*!< [13..13] Filter FIFO assignment for filter 13                             */
    } bit;
  } FAFIFOR;
  __IM  uint32_t  RESERVED4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000021C) CAN filter activation register                             */
    
    struct {
      __IOM uint32_t FACT0      : 1;            /*!< [0..0] Filter active                                                      */
      __IOM uint32_t FACT1      : 1;            /*!< [1..1] Filter active                                                      */
      __IOM uint32_t FACT2      : 1;            /*!< [2..2] Filter active                                                      */
      __IOM uint32_t FACT3      : 1;            /*!< [3..3] Filter active                                                      */
      __IOM uint32_t FACT4      : 1;            /*!< [4..4] Filter active                                                      */
      __IOM uint32_t FACT5      : 1;            /*!< [5..5] Filter active                                                      */
      __IOM uint32_t FACT6      : 1;            /*!< [6..6] Filter active                                                      */
      __IOM uint32_t FACT7      : 1;            /*!< [7..7] Filter active                                                      */
      __IOM uint32_t FACT8      : 1;            /*!< [8..8] Filter active                                                      */
      __IOM uint32_t FACT9      : 1;            /*!< [9..9] Filter active                                                      */
      __IOM uint32_t FACT10     : 1;            /*!< [10..10] Filter active                                                    */
      __IOM uint32_t FACT11     : 1;            /*!< [11..11] Filter active                                                    */
      __IOM uint32_t FACT12     : 1;            /*!< [12..12] Filter active                                                    */
      __IOM uint32_t FACT13     : 1;            /*!< [13..13] Filter active                                                    */
    } bit;
  } FWR;
  __IM  uint32_t  RESERVED5[8];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000240) Filter bank 0 register 1                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F0R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000244) Filter bank 0 register 2                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F0R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000248) Filter bank 1 register 1                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F1R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000024C) Filter bank 1 register 2                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F1R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000250) Filter bank 2 register 1                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F2R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000254) Filter bank 2 register 2                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F2R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000258) Filter bank 3 register 1                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F3R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000025C) Filter bank 3 register 2                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F3R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000260) Filter bank 4 register 1                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F4R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000264) Filter bank 4 register 2                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F4R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000268) Filter bank 5 register 1                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F5R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000026C) Filter bank 5 register 2                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F5R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000270) Filter bank 6 register 1                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F6R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000274) Filter bank 6 register 2                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F6R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000278) Filter bank 7 register 1                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F7R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000027C) Filter bank 7 register 2                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F7R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000280) Filter bank 8 register 1                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F8R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000284) Filter bank 8 register 2                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F8R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000288) Filter bank 9 register 1                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F9R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000028C) Filter bank 9 register 2                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F9R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000290) Filter bank 10 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F10R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000294) Filter bank 10 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F10R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000298) Filter bank 11 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F11R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000029C) Filter bank 11 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F11R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002A0) Filter bank 4 register 1                                   */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F12R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002A4) Filter bank 12 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F12R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002A8) Filter bank 13 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F13R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002AC) Filter bank 13 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F13R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002B0) Filter bank 14 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F14R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002B4) Filter bank 14 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F14R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002B8) Filter bank 15 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F15R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002BC) Filter bank 15 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F15R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002C0) Filter bank 16 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F16R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002C4) Filter bank 16 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F16R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002C8) Filter bank 17 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F17R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002CC) Filter bank 17 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F17R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002D0) Filter bank 18 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F18R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002D4) Filter bank 18 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F18R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002D8) Filter bank 19 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F19R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002DC) Filter bank 19 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F19R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002E0) Filter bank 20 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F20R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002E4) Filter bank 20 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F20R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002E8) Filter bank 21 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F21R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002EC) Filter bank 21 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F21R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002F0) Filter bank 22 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F22R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002F4) Filter bank 22 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F22R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002F8) Filter bank 23 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F23R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000002FC) Filter bank 23 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F23R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000300) Filter bank 24 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F24R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000304) Filter bank 24 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F24R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000308) Filter bank 25 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F25R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000030C) Filter bank 25 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F25R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000310) Filter bank 26 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F26R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000314) Filter bank 26 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F26R2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000318) Filter bank 27 register 1                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F27R1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000031C) Filter bank 27 register 2                                  */
    
    struct {
      __IOM uint32_t FB0        : 1;            /*!< [0..0] Filter bits                                                        */
      __IOM uint32_t FB1        : 1;            /*!< [1..1] Filter bits                                                        */
      __IOM uint32_t FB2        : 1;            /*!< [2..2] Filter bits                                                        */
      __IOM uint32_t FB3        : 1;            /*!< [3..3] Filter bits                                                        */
      __IOM uint32_t FB4        : 1;            /*!< [4..4] Filter bits                                                        */
      __IOM uint32_t FB5        : 1;            /*!< [5..5] Filter bits                                                        */
      __IOM uint32_t FB6        : 1;            /*!< [6..6] Filter bits                                                        */
      __IOM uint32_t FB7        : 1;            /*!< [7..7] Filter bits                                                        */
      __IOM uint32_t FB8        : 1;            /*!< [8..8] Filter bits                                                        */
      __IOM uint32_t FB9        : 1;            /*!< [9..9] Filter bits                                                        */
      __IOM uint32_t FB10       : 1;            /*!< [10..10] Filter bits                                                      */
      __IOM uint32_t FB11       : 1;            /*!< [11..11] Filter bits                                                      */
      __IOM uint32_t FB12       : 1;            /*!< [12..12] Filter bits                                                      */
      __IOM uint32_t FB13       : 1;            /*!< [13..13] Filter bits                                                      */
      __IOM uint32_t FB14       : 1;            /*!< [14..14] Filter bits                                                      */
      __IOM uint32_t FB15       : 1;            /*!< [15..15] Filter bits                                                      */
      __IOM uint32_t FB16       : 1;            /*!< [16..16] Filter bits                                                      */
      __IOM uint32_t FB17       : 1;            /*!< [17..17] Filter bits                                                      */
      __IOM uint32_t FB18       : 1;            /*!< [18..18] Filter bits                                                      */
      __IOM uint32_t FB19       : 1;            /*!< [19..19] Filter bits                                                      */
      __IOM uint32_t FB20       : 1;            /*!< [20..20] Filter bits                                                      */
      __IOM uint32_t FB21       : 1;            /*!< [21..21] Filter bits                                                      */
      __IOM uint32_t FB22       : 1;            /*!< [22..22] Filter bits                                                      */
      __IOM uint32_t FB23       : 1;            /*!< [23..23] Filter bits                                                      */
      __IOM uint32_t FB24       : 1;            /*!< [24..24] Filter bits                                                      */
      __IOM uint32_t FB25       : 1;            /*!< [25..25] Filter bits                                                      */
      __IOM uint32_t FB26       : 1;            /*!< [26..26] Filter bits                                                      */
      __IOM uint32_t FB27       : 1;            /*!< [27..27] Filter bits                                                      */
      __IOM uint32_t FB28       : 1;            /*!< [28..28] Filter bits                                                      */
      __IOM uint32_t FB29       : 1;            /*!< [29..29] Filter bits                                                      */
      __IOM uint32_t FB30       : 1;            /*!< [30..30] Filter bits                                                      */
      __IOM uint32_t FB31       : 1;            /*!< [31..31] Filter bits                                                      */
    } bit;
  } F27R2;
} CAN1_Type;                                    /*!< Size = 800 (0x320)                                                        */



/* =========================================================================================================================== */
/* ================                                       ETHERNET_MAC                                        ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40028000) ETHERNET_MAC Structure                                     */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Ethernet MAC configuration register (ETH_MACCR)            */
    
    struct {
      __IOM uint32_t TCES       : 1;            /*!< [0..0] Send clock selection bit                                           */
      __IOM uint32_t TCF        : 1;            /*!< [1..1] Send clock reversal                                                */
      __IOM uint32_t RE         : 1;            /*!< [2..2] Receiver enable                                                    */
      __IOM uint32_t TE         : 1;            /*!< [3..3] Transmitter enable                                                 */
      __IOM uint32_t DC         : 1;            /*!< [4..4] Deferral check                                                     */
      __IOM uint32_t BL         : 2;            /*!< [6..5] Back-off limit                                                     */
      __IOM uint32_t APCS       : 1;            /*!< [7..7] Automatic pad/CRC stripping                                        */
      __IM  uint32_t            : 1;
      __IOM uint32_t RD         : 1;            /*!< [9..9] Retry disable                                                      */
      __IOM uint32_t IPCO       : 1;            /*!< [10..10] IPv4 checksum offload                                            */
      __IOM uint32_t DM         : 1;            /*!< [11..11] Duplex mode                                                      */
      __IOM uint32_t LM         : 1;            /*!< [12..12] Loopback mode                                                    */
      __IOM uint32_t ROD        : 1;            /*!< [13..13] Receive own disable                                              */
      __IOM uint32_t FES        : 1;            /*!< [14..14] Fast Ethernet speed                                              */
      __IM  uint32_t            : 1;
      __IOM uint32_t CSD        : 1;            /*!< [16..16] Carrier sense disable                                            */
      __IOM uint32_t IFG        : 3;            /*!< [19..17] Interframe gap                                                   */
      __IOM uint32_t IRE        : 1;            /*!< [20..20] 10MPHY 50Ω set                                                  */
      __IOM uint32_t PDI        : 1;            /*!< [21..21] 10MPHY TX DRIVER bisa current                                    */
      __IOM uint32_t JD         : 1;            /*!< [22..22] Jabber disable                                                   */
      __IOM uint32_t WD         : 1;            /*!< [23..23] Watchdog disable                                                 */
      __IM  uint32_t            : 5;
      __IOM uint32_t TCD        : 3;            /*!< [31..29] SEND clock delay                                                 */
    } bit;
  } MACCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Ethernet MAC frame filter register (ETH_MACCFFR)           */
    
    struct {
      __IOM uint32_t PM         : 1;            /*!< [0..0] Promiscuous mode                                                   */
      __IOM uint32_t HU         : 1;            /*!< [1..1] Hash unicast                                                       */
      __IOM uint32_t HM         : 1;            /*!< [2..2] Hash multicast                                                     */
      __IOM uint32_t DAIF       : 1;            /*!< [3..3] Destination address inverse filtering                              */
      __IOM uint32_t PAM        : 1;            /*!< [4..4] Pass all multicast                                                 */
      __IOM uint32_t BFD        : 1;            /*!< [5..5] Broadcast frames disable                                           */
      __IOM uint32_t PCF        : 2;            /*!< [7..6] Pass control frames                                                */
      __IOM uint32_t SAIF       : 1;            /*!< [8..8] Source address inverse filtering                                   */
      __IOM uint32_t SAF        : 1;            /*!< [9..9] Source address filter                                              */
      __IOM uint32_t HPF        : 1;            /*!< [10..10] Hash or perfect filter                                           */
      __IM  uint32_t            : 20;
      __IOM uint32_t RA         : 1;            /*!< [31..31] Receive all                                                      */
    } bit;
  } MACFFR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Ethernet MAC hash table high register                      */
    
    struct {
      __IOM uint32_t HTH        : 32;           /*!< [31..0] Hash table high                                                   */
    } bit;
  } MACHTHR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Ethernet MAC hash table low register                       */
    
    struct {
      __IOM uint32_t HTL        : 32;           /*!< [31..0] Hash table low                                                    */
    } bit;
  } MACHTLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) Ethernet MAC MII address register (ETH_MACMIIAR)           */
    
    struct {
      __IOM uint32_t MB         : 1;            /*!< [0..0] MII busy                                                           */
      __IOM uint32_t MW         : 1;            /*!< [1..1] MII write                                                          */
      __IOM uint32_t CR         : 3;            /*!< [4..2] Clock range                                                        */
      __IM  uint32_t            : 1;
      __IOM uint32_t MR         : 5;            /*!< [10..6] MII register                                                      */
      __IOM uint32_t PA         : 5;            /*!< [15..11] PHY address                                                      */
    } bit;
  } MACMIIAR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Ethernet MAC MII data register (ETH_MACMIIDR)              */
    
    struct {
      __IOM uint32_t MD         : 16;           /*!< [15..0] MII data                                                          */
    } bit;
  } MACMIIDR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) Ethernet MAC flow control register (ETH_MACFCR)            */
    
    struct {
      __IOM uint32_t FCB_BPA    : 1;            /*!< [0..0] Flow control busy/back pressure activate                           */
      __IOM uint32_t TFCE       : 1;            /*!< [1..1] Transmit flow control enable                                       */
      __IOM uint32_t RFCE       : 1;            /*!< [2..2] Receive flow control enable                                        */
      __IOM uint32_t UPFD       : 1;            /*!< [3..3] Unicast pause frame detect                                         */
      __IOM uint32_t PLT        : 2;            /*!< [5..4] Pause low threshold                                                */
      __IM  uint32_t            : 1;
      __IOM uint32_t ZQPD       : 1;            /*!< [7..7] Zero-quanta pause disable                                          */
      __IM  uint32_t            : 8;
      __IOM uint32_t PT         : 16;           /*!< [31..16] Pass control frames                                              */
    } bit;
  } MACFCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) Ethernet MAC VLAN tag register (ETH_MACVLANTR)             */
    
    struct {
      __IOM uint32_t VLANTI     : 16;           /*!< [15..0] VLAN tag identifier (for receive frames)                          */
      __IOM uint32_t VLANTC     : 1;            /*!< [16..16] 12-bit VLAN tag comparison                                       */
    } bit;
  } MACVLANTR;
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  MACRWUFFR;                    /*!< (@ 0x00000028) Ethernet MAC remote wakeup frame filter register
                                                                    (ETH_MACRWUFFR)                                            */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) Ethernet MAC PMT control and status register
                                                                    (ETH_MACPMTCSR)                                            */
    
    struct {
      __IOM uint32_t PD         : 1;            /*!< [0..0] Power down                                                         */
      __IOM uint32_t MPE        : 1;            /*!< [1..1] Magic Packet enable                                                */
      __IOM uint32_t WFE        : 1;            /*!< [2..2] Wakeup frame enable                                                */
      __IM  uint32_t            : 2;
      __IOM uint32_t MPR        : 1;            /*!< [5..5] Magic packet received                                              */
      __IOM uint32_t WFR        : 1;            /*!< [6..6] Wakeup frame received                                              */
      __IM  uint32_t            : 2;
      __IOM uint32_t GU         : 1;            /*!< [9..9] Global unicast                                                     */
      __IM  uint32_t            : 21;
      __IOM uint32_t WFFRPR     : 1;            /*!< [31..31] Wakeup frame filter register pointer reset                       */
    } bit;
  } MACPMTCSR;
  __IM  uint32_t  RESERVED1[2];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) Ethernet MAC interrupt status register (ETH_MACSR)         */
    
    struct {
      __IM  uint32_t            : 3;
      __IOM uint32_t PMTS       : 1;            /*!< [3..3] PMT status                                                         */
      __IOM uint32_t MMCS       : 1;            /*!< [4..4] MMC status                                                         */
      __IOM uint32_t MMCRS      : 1;            /*!< [5..5] MMC receive status                                                 */
      __IOM uint32_t MMCTS      : 1;            /*!< [6..6] MMC transmit status                                                */
      __IM  uint32_t            : 2;
      __IOM uint32_t TSTS       : 1;            /*!< [9..9] Time stamp trigger status                                          */
    } bit;
  } MACSR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000003C) Ethernet MAC interrupt mask register (ETH_MACIMR)          */
    
    struct {
      __IM  uint32_t            : 3;
      __IOM uint32_t PMTIM      : 1;            /*!< [3..3] PMT interrupt mask                                                 */
      __IM  uint32_t            : 5;
      __IOM uint32_t TSTIM      : 1;            /*!< [9..9] Time stamp trigger interrupt mask                                  */
    } bit;
  } MACIMR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) Ethernet MAC address 0 high register (ETH_MACA0HR)         */
    
    struct {
      __IOM uint32_t MACA0H     : 16;           /*!< [15..0] MAC address0 high                                                 */
      __IM  uint32_t            : 15;
      __IM  uint32_t MO         : 1;            /*!< [31..31] Always 1                                                         */
    } bit;
  } MACA0HR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000044) Ethernet MAC address 0 low register                        */
    
    struct {
      __IOM uint32_t MACA0L     : 32;           /*!< [31..0] MAC address0 low                                                  */
    } bit;
  } MACA0LR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) Ethernet MAC address 1 high register (ETH_MACA1HR)         */
    
    struct {
      __IOM uint32_t MACA1H     : 16;           /*!< [15..0] MAC address1 high                                                 */
      __IM  uint32_t            : 8;
      __IOM uint32_t MBC        : 6;            /*!< [29..24] Mask byte control                                                */
      __IOM uint32_t SA         : 1;            /*!< [30..30] Source address                                                   */
      __IOM uint32_t AE         : 1;            /*!< [31..31] Address enable                                                   */
    } bit;
  } MACA1HR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) Ethernet MAC address1 low register                         */
    
    struct {
      __IOM uint32_t MACA1L     : 32;           /*!< [31..0] MAC address1 low                                                  */
    } bit;
  } MACA1LR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000050) Ethernet MAC address 2 high register (ETH_MACA2HR)         */
    
    struct {
      __IOM uint32_t ETH_MACA2HR : 16;          /*!< [15..0] Ethernet MAC address 2 high register                              */
      __IM  uint32_t            : 8;
      __IOM uint32_t MBC        : 6;            /*!< [29..24] Mask byte control                                                */
      __IOM uint32_t SA         : 1;            /*!< [30..30] Source address                                                   */
      __IOM uint32_t AE         : 1;            /*!< [31..31] Address enable                                                   */
    } bit;
  } MACA2HR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000054) Ethernet MAC address 2 low register                        */
    
    struct {
      __IOM uint32_t MACA2L     : 31;           /*!< [30..0] MAC address2 low                                                  */
    } bit;
  } MACA2LR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000058) Ethernet MAC address 3 high register (ETH_MACA3HR)         */
    
    struct {
      __IOM uint32_t MACA3H     : 16;           /*!< [15..0] MAC address3 high                                                 */
      __IM  uint32_t            : 8;
      __IOM uint32_t MBC        : 6;            /*!< [29..24] Mask byte control                                                */
      __IOM uint32_t SA         : 1;            /*!< [30..30] Source address                                                   */
      __IOM uint32_t AE         : 1;            /*!< [31..31] Address enable                                                   */
    } bit;
  } MACA3HR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000005C) Ethernet MAC address 3 low register                        */
    
    struct {
      __IOM uint32_t MBCA3L     : 32;           /*!< [31..0] MAC address3 low                                                  */
    } bit;
  } MACA3LR;
} ETHERNET_MAC_Type;                            /*!< Size = 96 (0x60)                                                          */



/* =========================================================================================================================== */
/* ================                                       ETHERNET_MMC                                        ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40028100) ETHERNET_MMC Structure                                     */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Ethernet MMC control register (ETH_MMCCR)                  */
    
    struct {
      __IOM uint32_t CR         : 1;            /*!< [0..0] Counter reset                                                      */
      __IOM uint32_t CSR        : 1;            /*!< [1..1] Counter stop rollover                                              */
      __IOM uint32_t ROR        : 1;            /*!< [2..2] Reset on read                                                      */
      __IM  uint32_t            : 28;
      __IOM uint32_t MCF        : 1;            /*!< [31..31] MMC counter freeze                                               */
    } bit;
  } MMCCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Ethernet MMC receive interrupt register (ETH_MMCRIR)       */
    
    struct {
      __IM  uint32_t            : 5;
      __IOM uint32_t RFCES      : 1;            /*!< [5..5] Received frames CRC error status                                   */
      __IOM uint32_t RFAES      : 1;            /*!< [6..6] Received frames alignment error status                             */
      __IM  uint32_t            : 10;
      __IOM uint32_t RGUFS      : 1;            /*!< [17..17] Received Good Unicast Frames Status                              */
    } bit;
  } MMCRIR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Ethernet MMC transmit interrupt register (ETH_MMCTIR)      */
    
    struct {
      __IM  uint32_t            : 14;
      __IOM uint32_t TGFSCS     : 1;            /*!< [14..14] Transmitted good frames single collision status                  */
      __IOM uint32_t TGFMSCS    : 1;            /*!< [15..15] Transmitted good frames more single collision status             */
      __IM  uint32_t            : 5;
      __IOM uint32_t TGFS       : 1;            /*!< [21..21] Transmitted good frames status                                   */
    } bit;
  } MMCTIR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Ethernet MMC receive interrupt mask register
                                                                    (ETH_MMCRIMR)                                              */
    
    struct {
      __IM  uint32_t            : 5;
      __IOM uint32_t RFCEM      : 1;            /*!< [5..5] Received frame CRC error mask                                      */
      __IOM uint32_t RFAEM      : 1;            /*!< [6..6] Received frames alignment error mask                               */
      __IM  uint32_t            : 10;
      __IOM uint32_t RGUFM      : 1;            /*!< [17..17] Received good unicast frames mask                                */
    } bit;
  } MMCRIMR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) Ethernet MMC transmit interrupt mask register
                                                                    (ETH_MMCTIMR)                                              */
    
    struct {
      __IM  uint32_t            : 14;
      __IOM uint32_t TGFSCM     : 1;            /*!< [14..14] Transmitted good frames single collision mask                    */
      __IOM uint32_t TGFMSCM    : 1;            /*!< [15..15] Transmitted good frames more single collision mask               */
      __IM  uint32_t            : 5;
      __IOM uint32_t TGFM       : 1;            /*!< [21..21] Transmitted good frames mask                                     */
    } bit;
  } MMCTIMR;
  __IM  uint32_t  RESERVED[14];
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x0000004C) Ethernet MMC transmitted good frames after a
                                                                    single collision counter                                   */
    
    struct {
      __IM  uint32_t TGFSCC     : 32;           /*!< [31..0] Transmitted good frames after a single collision counter          */
    } bit;
  } MMCTGFSCCR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000050) Ethernet MMC transmitted good frames after more
                                                                    than a single collision                                    */
    
    struct {
      __IM  uint32_t TGFMSCC    : 32;           /*!< [31..0] Transmitted good frames after more than a single collision
                                                     counter                                                                   */
    } bit;
  } MMCTGFMSCCR;
  __IM  uint32_t  RESERVED1[5];
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000068) Ethernet MMC transmitted good frames counter
                                                                    register                                                   */
    
    struct {
      __IM  uint32_t TGFC       : 32;           /*!< [31..0] Transmitted good frames counter                                   */
    } bit;
  } MMCTGFCR;
  __IM  uint32_t  RESERVED2[10];
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000094) Ethernet MMC received frames with CRC error counter
                                                                    register                                                   */
    
    struct {
      __IM  uint32_t RFCFC      : 32;           /*!< [31..0] Received frames with CRC error counter                            */
    } bit;
  } MMCRFCECR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000098) Ethernet MMC received frames with alignment error
                                                                    counter register                                           */
    
    struct {
      __IM  uint32_t RFAEC      : 32;           /*!< [31..0] Received frames with alignment error counter                      */
    } bit;
  } MMCRFAECR;
  __IM  uint32_t  RESERVED3[10];
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x000000C4) MMC received good unicast frames counter register          */
    
    struct {
      __IM  uint32_t RGUFC      : 32;           /*!< [31..0] Received good unicast frames counter                              */
    } bit;
  } MMCRGUFCR;
} ETHERNET_MMC_Type;                            /*!< Size = 200 (0xc8)                                                         */



/* =========================================================================================================================== */
/* ================                                       ETHERNET_PTP                                        ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40028700) ETHERNET_PTP Structure                                     */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Ethernet PTP time stamp control register (ETH_PTPTSCR)     */
    
    struct {
      __IOM uint32_t TSE        : 1;            /*!< [0..0] Time stamp enable                                                  */
      __IOM uint32_t TSFCU      : 1;            /*!< [1..1] Time stamp fine or coarse update                                   */
      __IOM uint32_t TSSTI      : 1;            /*!< [2..2] Time stamp system time initialize                                  */
      __IOM uint32_t TSSTU      : 1;            /*!< [3..3] Time stamp system time update                                      */
      __IOM uint32_t TSITE      : 1;            /*!< [4..4] Time stamp interrupt trigger enable                                */
      __IOM uint32_t TSARU      : 1;            /*!< [5..5] Time stamp addend register update                                  */
    } bit;
  } PTPTSCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Ethernet PTP subsecond increment register                  */
    
    struct {
      __IOM uint32_t STSSI      : 8;            /*!< [7..0] System time subsecond increment                                    */
    } bit;
  } PTPSSIR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000008) Ethernet PTP time stamp high register                      */
    
    struct {
      __IM  uint32_t STS        : 32;           /*!< [31..0] System time second                                                */
    } bit;
  } PTPTSHR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x0000000C) Ethernet PTP time stamp low register (ETH_PTPTSLR)         */
    
    struct {
      __IM  uint32_t STSS       : 31;           /*!< [30..0] System time subseconds                                            */
      __IM  uint32_t STPNS      : 1;            /*!< [31..31] System time positive or negative sign                            */
    } bit;
  } PTPTSLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) Ethernet PTP time stamp high update register               */
    
    struct {
      __IOM uint32_t TSUS       : 32;           /*!< [31..0] Time stamp update second                                          */
    } bit;
  } PTPTSHUR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Ethernet PTP time stamp low update register (ETH_PTPTSLUR) */
    
    struct {
      __IOM uint32_t TSUSS      : 31;           /*!< [30..0] Time stamp update subseconds                                      */
      __IOM uint32_t TSUPNS     : 1;            /*!< [31..31] Time stamp update positive or negative sign                      */
    } bit;
  } PTPTSLUR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) Ethernet PTP time stamp addend register                    */
    
    struct {
      __IOM uint32_t TSA        : 32;           /*!< [31..0] Time stamp addend                                                 */
    } bit;
  } PTPTSAR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) Ethernet PTP target time high register                     */
    
    struct {
      __IOM uint32_t TTSH       : 32;           /*!< [31..0] Target time stamp high                                            */
    } bit;
  } PTPTTHR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) Ethernet PTP target time low register                      */
    
    struct {
      __IOM uint32_t TTSL       : 32;           /*!< [31..0] Target time stamp low                                             */
    } bit;
  } PTPTTLR;
} ETHERNET_PTP_Type;                            /*!< Size = 36 (0x24)                                                          */



/* =========================================================================================================================== */
/* ================                                       ETHERNET_DMA                                        ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40029000) ETHERNET_DMA Structure                                     */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Ethernet DMA bus mode register                             */
    
    struct {
      __IOM uint32_t SR         : 1;            /*!< [0..0] Software reset                                                     */
      __IOM uint32_t DA         : 1;            /*!< [1..1] DMA Arbitration                                                    */
      __IOM uint32_t DSL        : 5;            /*!< [6..2] Descriptor skip length                                             */
      __IM  uint32_t            : 1;
      __IOM uint32_t PBL        : 6;            /*!< [13..8] Programmable burst length                                         */
      __IOM uint32_t RTPR       : 2;            /*!< [15..14] Rx Tx priority ratio                                             */
      __IOM uint32_t FB         : 1;            /*!< [16..16] Fixed burst                                                      */
      __IOM uint32_t RDP        : 6;            /*!< [22..17] Rx DMA PBL                                                       */
      __IOM uint32_t USP        : 1;            /*!< [23..23] Use separate PBL                                                 */
      __IOM uint32_t FPM        : 1;            /*!< [24..24] 4xPBL mode                                                       */
      __IOM uint32_t AAB        : 1;            /*!< [25..25] Address-aligned beats                                            */
    } bit;
  } DMABMR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Ethernet DMA transmit poll demand register                 */
    
    struct {
      __IOM uint32_t TPD        : 32;           /*!< [31..0] Transmit poll demand                                              */
    } bit;
  } DMATPDR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) EHERNET DMA receive poll demand register                   */
    
    struct {
      __IOM uint32_t RPD        : 32;           /*!< [31..0] Receive poll demand                                               */
    } bit;
  } DMARPDR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Ethernet DMA receive descriptor list address
                                                                    register                                                   */
    
    struct {
      __IOM uint32_t SRL        : 32;           /*!< [31..0] Start of receive list                                             */
    } bit;
  } DMARDLAR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) Ethernet DMA transmit descriptor list address
                                                                    register                                                   */
    
    struct {
      __IOM uint32_t STL        : 32;           /*!< [31..0] Start of transmit list                                            */
    } bit;
  } DMATDLAR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Ethernet DMA status register                               */
    
    struct {
      __IOM uint32_t TS         : 1;            /*!< [0..0] Transmit status                                                    */
      __IOM uint32_t TPSS       : 1;            /*!< [1..1] Transmit process stopped status                                    */
      __IOM uint32_t TBUS       : 1;            /*!< [2..2] Transmit buffer unavailable status                                 */
      __IOM uint32_t TJTS       : 1;            /*!< [3..3] Transmit jabber timeout status                                     */
      __IOM uint32_t ROS        : 1;            /*!< [4..4] Receive overflow status                                            */
      __IOM uint32_t TUS        : 1;            /*!< [5..5] Transmit underflow status                                          */
      __IOM uint32_t RS         : 1;            /*!< [6..6] Receive status                                                     */
      __IOM uint32_t RBUS       : 1;            /*!< [7..7] Receive buffer unavailable status                                  */
      __IOM uint32_t RPSS       : 1;            /*!< [8..8] Receive process stopped status                                     */
      __IOM uint32_t PWTS       : 1;            /*!< [9..9] Receive watchdog timeout status                                    */
      __IOM uint32_t ETS        : 1;            /*!< [10..10] Early transmit status                                            */
      __IM  uint32_t            : 2;
      __IOM uint32_t FBES       : 1;            /*!< [13..13] Fatal bus error status                                           */
      __IOM uint32_t ERS        : 1;            /*!< [14..14] Early receive status                                             */
      __IOM uint32_t AIS        : 1;            /*!< [15..15] Abnormal interrupt summary                                       */
      __IOM uint32_t NIS        : 1;            /*!< [16..16] Normal interrupt summary                                         */
      __IM  uint32_t RPS        : 3;            /*!< [19..17] Receive process state                                            */
      __IM  uint32_t TPS        : 3;            /*!< [22..20] Transmit process state                                           */
      __IM  uint32_t EBS        : 3;            /*!< [25..23] Error bits status                                                */
      __IM  uint32_t            : 1;
      __IM  uint32_t MMCS       : 1;            /*!< [27..27] MMC status                                                       */
      __IM  uint32_t PMTS       : 1;            /*!< [28..28] PMT status                                                       */
      __IM  uint32_t TSTS       : 1;            /*!< [29..29] Time stamp trigger status                                        */
      __IM  uint32_t            : 1;
      __IM  uint32_t IPLS       : 1;            /*!< [31..31] 10MPHY Physical layer variation                                  */
    } bit;
  } DMASR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) Ethernet DMA operation mode register                       */
    
    struct {
      __IM  uint32_t            : 1;
      __IOM uint32_t SR         : 1;            /*!< [1..1] SR                                                                 */
      __IOM uint32_t OSF        : 1;            /*!< [2..2] OSF                                                                */
      __IOM uint32_t RTC        : 2;            /*!< [4..3] RTC                                                                */
      __IM  uint32_t            : 1;
      __IOM uint32_t FUGF       : 1;            /*!< [6..6] FUGF                                                               */
      __IOM uint32_t FEF        : 1;            /*!< [7..7] FEF                                                                */
      __IM  uint32_t            : 5;
      __IOM uint32_t ST         : 1;            /*!< [13..13] ST                                                               */
      __IOM uint32_t TTC        : 3;            /*!< [16..14] TTC                                                              */
      __IM  uint32_t            : 3;
      __IOM uint32_t FTF        : 1;            /*!< [20..20] FTF                                                              */
      __IOM uint32_t TSF        : 1;            /*!< [21..21] TSF                                                              */
      __IM  uint32_t            : 2;
      __IOM uint32_t DFRF       : 1;            /*!< [24..24] DFRF                                                             */
      __IOM uint32_t RSF        : 1;            /*!< [25..25] RSF                                                              */
      __IOM uint32_t DTCEFD     : 1;            /*!< [26..26] DTCEFD                                                           */
    } bit;
  } DMAOMR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) Ethernet DMA interrupt enable register                     */
    
    struct {
      __IOM uint32_t TIE        : 1;            /*!< [0..0] Transmit interrupt enable                                          */
      __IOM uint32_t TPSIE      : 1;            /*!< [1..1] Transmit process stopped interrupt enable                          */
      __IOM uint32_t TBUIE      : 1;            /*!< [2..2] Transmit buffer unavailable interrupt enable                       */
      __IOM uint32_t TJTIE      : 1;            /*!< [3..3] Transmit jabber timeout interrupt enable                           */
      __IOM uint32_t ROIE       : 1;            /*!< [4..4] Overflow interrupt enable                                          */
      __IOM uint32_t TUIE       : 1;            /*!< [5..5] Underflow interrupt enable                                         */
      __IOM uint32_t RIE        : 1;            /*!< [6..6] Receive interrupt enable                                           */
      __IOM uint32_t RBUIE      : 1;            /*!< [7..7] Receive buffer unavailable interrupt enable                        */
      __IOM uint32_t RPSIE      : 1;            /*!< [8..8] Receive process stopped interrupt enable                           */
      __IOM uint32_t RWTIE      : 1;            /*!< [9..9] receive watchdog timeout interrupt enable                          */
      __IOM uint32_t ETIE       : 1;            /*!< [10..10] Early transmit interrupt enable                                  */
      __IM  uint32_t            : 2;
      __IOM uint32_t FBEIE      : 1;            /*!< [13..13] Fatal bus error interrupt enable                                 */
      __IOM uint32_t ERIE       : 1;            /*!< [14..14] Early receive interrupt enable                                   */
      __IOM uint32_t AISE       : 1;            /*!< [15..15] Abnormal interrupt summary enable                                */
      __IOM uint32_t NISE       : 1;            /*!< [16..16] Normal interrupt summary enable                                  */
      __IM  uint32_t            : 14;
      __IOM uint32_t IPLE       : 1;            /*!< [31..31] 10M Physical layer connection                                    */
    } bit;
  } DMAIER;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000020) Ethernet DMA missed frame and buffer overflow
                                                                    counter register                                           */
    
    struct {
      __IM  uint32_t MFC        : 16;           /*!< [15..0] Missed frames by the controller                                   */
      __IM  uint32_t OMFC       : 1;            /*!< [16..16] Overflow bit for missed frame counter                            */
      __IM  uint32_t MFA        : 11;           /*!< [27..17] Missed frames by the application                                 */
      __IM  uint32_t OFOC       : 1;            /*!< [28..28] Overflow bit for FIFO overflow counter                           */
    } bit;
  } DMAMFBOCR;
  __IM  uint32_t  RESERVED[9];
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000048) Ethernet DMA current host transmit descriptor
                                                                    register                                                   */
    
    struct {
      __IM  uint32_t HTDAP      : 32;           /*!< [31..0] Host transmit descriptor address pointer                          */
    } bit;
  } DMACHTDR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x0000004C) Ethernet DMA current host receive descriptor
                                                                    register                                                   */
    
    struct {
      __IM  uint32_t HRDAP      : 32;           /*!< [31..0] Host receive descriptor address pointer                           */
    } bit;
  } DMACHRDR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000050) Ethernet DMA current host transmit buffer address
                                                                    register                                                   */
    
    struct {
      __IM  uint32_t HTBAP      : 32;           /*!< [31..0] Host transmit buffer address pointer                              */
    } bit;
  } DMACHTBAR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000054) Ethernet DMA current host receive buffer address
                                                                    register                                                   */
    
    struct {
      __IM  uint32_t HRBAP      : 32;           /*!< [31..0] Host receive buffer address pointer                               */
    } bit;
  } DMACHRBAR;
} ETHERNET_DMA_Type;                            /*!< Size = 88 (0x58)                                                          */



/* =========================================================================================================================== */
/* ================                                           SDIO                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40018000) SDIO Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Bits 1:0 = PWRCTRL: Power supply control bits              */
    
    struct {
      __IOM uint32_t PWRCTRL    : 2;            /*!< [1..0] Power supply control bits                                          */
    } bit;
  } POWER;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) SDI clock control register (SDIO_CLKCR)                    */
    
    struct {
      __IOM uint32_t CLKDIV     : 8;            /*!< [7..0] Clock divide factor                                                */
      __IOM uint32_t CLKEN      : 1;            /*!< [8..8] Clock enable bit                                                   */
      __IOM uint32_t PWRSAV     : 1;            /*!< [9..9] Power saving configuration bit                                     */
      __IOM uint32_t BYPASS     : 1;            /*!< [10..10] Clock divider bypass enable bit                                  */
      __IOM uint32_t WIDBUS     : 2;            /*!< [12..11] Wide bus mode enable bit                                         */
      __IOM uint32_t NEGEDGE    : 1;            /*!< [13..13] SDIO_CK dephasing selection bit                                  */
      __IOM uint32_t HWFC_EN    : 1;            /*!< [14..14] HW Flow Control enable                                           */
    } bit;
  } CLKCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Bits 31:0 = : Command argument                             */
    
    struct {
      __IOM uint32_t CMDARG     : 32;           /*!< [31..0] Command argument                                                  */
    } bit;
  } ARG;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) SDIO command register (SDIO_CMD)                           */
    
    struct {
      __IOM uint32_t CMDINDEX   : 6;            /*!< [5..0] Command index                                                      */
      __IOM uint32_t WAITRESP   : 2;            /*!< [7..6] Wait for response bits                                             */
      __IOM uint32_t WAITINT    : 1;            /*!< [8..8] CPSM waits for interrupt request                                   */
      __IOM uint32_t WAITPEND   : 1;            /*!< [9..9] CPSM Waits for ends of data transfer (CmdPend internal
                                                     signal)                                                                   */
      __IOM uint32_t CPSMEN     : 1;            /*!< [10..10] Command path state machine (CPSM) Enable bit                     */
      __IOM uint32_t SDIOSuspend : 1;           /*!< [11..11] SD I/O suspend command                                           */
      __IOM uint32_t ENCMDcompl : 1;            /*!< [12..12] Enable CMD completion                                            */
      __IOM uint32_t nIEN       : 1;            /*!< [13..13] not Interrupt Enable                                             */
      __IOM uint32_t CE_ATACMD  : 1;            /*!< [14..14] CE-ATA command                                                   */
    } bit;
  } CMD;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000010) SDIO command register                                      */
    
    struct {
      __IM  uint32_t RESPCMD    : 6;            /*!< [5..0] Response command index                                             */
    } bit;
  } RESPCMD;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000014) Bits 31:0 = CARDSTATUS1                                    */
    
    struct {
      __IM  uint32_t CARDSTATUS1 : 32;          /*!< [31..0] Card status 1                                                     */
    } bit;
  } RESP1;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000018) Bits 31:0 = CARDSTATUS2                                    */
    
    struct {
      __IM  uint32_t CARDSTATUS2 : 32;          /*!< [31..0] Card status 2                                                     */
    } bit;
  } RESP2;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x0000001C) Bits 31:0 = CARDSTATUS3                                    */
    
    struct {
      __IM  uint32_t CARDSTATUS3 : 32;          /*!< [31..0] Card status 3                                                     */
    } bit;
  } RESP3;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000020) Bits 31:0 = CARDSTATUS4                                    */
    
    struct {
      __IM  uint32_t CARDSTATUS4 : 32;          /*!< [31..0] Card status 4                                                     */
    } bit;
  } RESP4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) Bits 31:0 = DATATIME: Data timeout period                  */
    
    struct {
      __IOM uint32_t DATATIME   : 32;           /*!< [31..0] Data timeout period                                               */
    } bit;
  } DTIMER;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) Bits 24:0 = DATALENGTH: Data length value                  */
    
    struct {
      __IOM uint32_t DATALENGTH : 25;           /*!< [24..0] Data length value                                                 */
    } bit;
  } DLEN;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) SDIO data control register (SDIO_DCTRL)                    */
    
    struct {
      __IOM uint32_t DTEN       : 1;            /*!< [0..0] Data transfer enabled bit                                          */
      __IOM uint32_t DTDIR      : 1;            /*!< [1..1] Data transfer direction selection                                  */
      __IOM uint32_t DTMODE     : 1;            /*!< [2..2] Data transfer mode selection 1: Stream or SDIO multibyte
                                                     data transfer                                                             */
      __IOM uint32_t DMAEN      : 1;            /*!< [3..3] DMA enable bit                                                     */
      __IOM uint32_t DBLOCKSIZE : 4;            /*!< [7..4] Data block size                                                    */
      __IOM uint32_t PWSTART    : 1;            /*!< [8..8] Read wait start                                                    */
      __IOM uint32_t PWSTOP     : 1;            /*!< [9..9] Read wait stop                                                     */
      __IOM uint32_t RWMOD      : 1;            /*!< [10..10] Read wait mode                                                   */
      __IOM uint32_t SDIOEN     : 1;            /*!< [11..11] SD I/O enable functions                                          */
    } bit;
  } DCTRL;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000030) Bits 24:0 = DATACOUNT: Data count value                    */
    
    struct {
      __IM  uint32_t DATACOUNT  : 25;           /*!< [24..0] Data count value                                                  */
    } bit;
  } DCOUNT;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000034) SDIO status register (SDIO_STA)                            */
    
    struct {
      __IM  uint32_t CCRCFAIL   : 1;            /*!< [0..0] Command response received (CRC check failed)                       */
      __IM  uint32_t DCRCFAIL   : 1;            /*!< [1..1] Data block sent/received (CRC check failed)                        */
      __IM  uint32_t CTIMEOUT   : 1;            /*!< [2..2] Command response timeout                                           */
      __IM  uint32_t DTIMEOUT   : 1;            /*!< [3..3] Data timeout                                                       */
      __IM  uint32_t TXUNDERR   : 1;            /*!< [4..4] Transmit FIFO underrun error                                       */
      __IM  uint32_t RXOVERR    : 1;            /*!< [5..5] Received FIFO overrun error                                        */
      __IM  uint32_t CMDREND    : 1;            /*!< [6..6] Command response received (CRC check passed)                       */
      __IM  uint32_t CMDSENT    : 1;            /*!< [7..7] Command sent (no response required)                                */
      __IM  uint32_t DATAEND    : 1;            /*!< [8..8] Data end (data counter, SDIDCOUNT, is zero)                        */
      __IM  uint32_t STBITERR   : 1;            /*!< [9..9] Start bit not detected on all data signals in wide bus
                                                     mode                                                                      */
      __IM  uint32_t DBCKEND    : 1;            /*!< [10..10] Data block sent/received (CRC check passed)                      */
      __IM  uint32_t CMDACT     : 1;            /*!< [11..11] Command transfer in progress                                     */
      __IM  uint32_t TXACT      : 1;            /*!< [12..12] Data transmit in progress                                        */
      __IM  uint32_t RXACT      : 1;            /*!< [13..13] Data receive in progress                                         */
      __IM  uint32_t TXFIFOHE   : 1;            /*!< [14..14] Transmit FIFO half empty: at least 8 words can be written
                                                     into the  FIFO                                                            */
      __IM  uint32_t RXFIFOHF   : 1;            /*!< [15..15] Receive FIFO half full: there are at least 8 words
                                                     in the  FIFO                                                              */
      __IM  uint32_t TXFIFOF    : 1;            /*!< [16..16] Transmit FIFO full                                               */
      __IM  uint32_t RXFIFOF    : 1;            /*!< [17..17] Receive FIFO full                                                */
      __IM  uint32_t TXFIFOE    : 1;            /*!< [18..18] Transmit FIFO empty                                              */
      __IM  uint32_t RXFIFOE    : 1;            /*!< [19..19] Receive FIFO empty                                               */
      __IM  uint32_t TXDAVL     : 1;            /*!< [20..20] Data available in transmit FIFO                                  */
      __IM  uint32_t RXDAVL     : 1;            /*!< [21..21] Data available in receive FIFO                                   */
      __IM  uint32_t SDIOIT     : 1;            /*!< [22..22] SDIO interrupt received                                          */
      __IM  uint32_t CEATAEND   : 1;            /*!< [23..23] CE-ATA command completion signal received for CMD61              */
    } bit;
  } STA;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) SDIO interrupt clear register (SDIO_ICR)                   */
    
    struct {
      __IOM uint32_t CCRCFAILC  : 1;            /*!< [0..0] CCRCFAIL flag clear bit                                            */
      __IOM uint32_t DCRCFAILC  : 1;            /*!< [1..1] DCRCFAIL flag clear bit                                            */
      __IOM uint32_t CTIMEOUTC  : 1;            /*!< [2..2] CTIMEOUT flag clear bit                                            */
      __IOM uint32_t DTIMEOUTC  : 1;            /*!< [3..3] DTIMEOUT flag clear bit                                            */
      __IOM uint32_t TXUNDERRC  : 1;            /*!< [4..4] TXUNDERR flag clear bit                                            */
      __IOM uint32_t RXOVERRC   : 1;            /*!< [5..5] RXOVERR flag clear bit                                             */
      __IOM uint32_t CMDRENDC   : 1;            /*!< [6..6] CMDREND flag clear bit                                             */
      __IOM uint32_t CMDSENTC   : 1;            /*!< [7..7] CMDSENT flag clear bit                                             */
      __IOM uint32_t DATAENDC   : 1;            /*!< [8..8] DATAEND flag clear bit                                             */
      __IOM uint32_t STBITERRC  : 1;            /*!< [9..9] STBITERR flag clear bit                                            */
      __IOM uint32_t DBCKENDC   : 1;            /*!< [10..10] DBCKEND flag clear bit                                           */
      __IM  uint32_t            : 11;
      __IOM uint32_t SDIOITC    : 1;            /*!< [22..22] SDIOIT flag clear bit                                            */
      __IOM uint32_t CEATAENDC  : 1;            /*!< [23..23] CEATAEND flag clear bit                                          */
    } bit;
  } ICR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000003C) SDIO mask register (SDIO_MASK)                             */
    
    struct {
      __IOM uint32_t CCRCFAILIE : 1;            /*!< [0..0] Command CRC fail interrupt  enable                                 */
      __IOM uint32_t DCRCFAILIE : 1;            /*!< [1..1] Data CRC fail interrupt  enable                                    */
      __IOM uint32_t CTIMEOUTIE : 1;            /*!< [2..2] Command timeout interrupt  enable                                  */
      __IOM uint32_t DTIMEOUTIE : 1;            /*!< [3..3] Data timeout interrupt  enable                                     */
      __IOM uint32_t TXUNDERRIE : 1;            /*!< [4..4] Tx FIFO underrun error interrupt  enable                           */
      __IOM uint32_t RXOVERRIE  : 1;            /*!< [5..5] Rx FIFO overrun error interrupt  enable                            */
      __IOM uint32_t CMDRENDIE  : 1;            /*!< [6..6] Command response received interrupt  enable                        */
      __IOM uint32_t CMDSENTIE  : 1;            /*!< [7..7] Command sent interrupt  enable                                     */
      __IOM uint32_t DATAENDIE  : 1;            /*!< [8..8] Data end interrupt  enable                                         */
      __IOM uint32_t STBITERRIE : 1;            /*!< [9..9] Start bit error interrupt  enable                                  */
      __IOM uint32_t DBACKENDIE : 1;            /*!< [10..10] Data block end interrupt  enable                                 */
      __IOM uint32_t CMDACTIE   : 1;            /*!< [11..11] Command acting interrupt  enable                                 */
      __IOM uint32_t TXACTIE    : 1;            /*!< [12..12] Data transmit acting interrupt  enable                           */
      __IOM uint32_t RXACTIE    : 1;            /*!< [13..13] Data receive acting interrupt  enable                            */
      __IOM uint32_t TXFIFOHEIE : 1;            /*!< [14..14] Tx FIFO half empty interrupt  enable                             */
      __IOM uint32_t RXFIFOHFIE : 1;            /*!< [15..15] Rx FIFO half full interrupt  enable                              */
      __IOM uint32_t TXFIFOFIE  : 1;            /*!< [16..16] Tx FIFO full interrupt  enable                                   */
      __IOM uint32_t RXFIFOFIE  : 1;            /*!< [17..17] Rx FIFO full interrupt  enable                                   */
      __IOM uint32_t TXFIFOEIE  : 1;            /*!< [18..18] Tx FIFO empty interrupt  enable                                  */
      __IOM uint32_t RXFIFOEIE  : 1;            /*!< [19..19] Rx FIFO empty interrupt  enable                                  */
      __IOM uint32_t TXDAVLIE   : 1;            /*!< [20..20] Data available in Tx FIFO interrupt  enable                      */
      __IOM uint32_t RXDAVLIE   : 1;            /*!< [21..21] Data available in Rx FIFO interrupt  enable                      */
      __IOM uint32_t SDIOITIE   : 1;            /*!< [22..22] SDIO mode interrupt received interrupt  enable                   */
      __IOM uint32_t CEATENDIE  : 1;            /*!< [23..23] CE-ATA command completion signal received interrupt
                                                     enable                                                                    */
    } bit;
  } MASK;
  __IM  uint32_t  RESERVED[2];
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000048) Bits 23:0 = FIFOCOUNT: Remaining number of words
                                                                    to be written to or read from the FIFO                     */
    
    struct {
      __IM  uint32_t FIF0COUNT  : 32;           /*!< [31..0] Remaining number of words to be written to or read from
                                                     the  FIFO                                                                 */
    } bit;
  } FIFOCNT;
  __IM  uint32_t  RESERVED1[13];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000080) bits 31:0 = FIFOData: Receive and transmit FIFO
                                                                    data                                                       */
    
    struct {
      __IOM uint32_t FIFOData   : 32;           /*!< [31..0] Receive and transmit FIFO data                                    */
    } bit;
  } FIFO;
} SDIO_Type;                                    /*!< Size = 132 (0x84)                                                         */



/* =========================================================================================================================== */
/* ================                                           FSMC                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0xA0000000) FSMC Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) SRAM/NOR-Flash chip-select control register 1              */
    
    struct {
      __IOM uint32_t MBKEN      : 1;            /*!< [0..0] Memory bank enable bit                                             */
      __IOM uint32_t MUXEN      : 1;            /*!< [1..1] Address/data multiplexing enable bit                               */
      __IOM uint32_t MTYP       : 2;            /*!< [3..2] Memory type                                                        */
      __IOM uint32_t MWID       : 2;            /*!< [5..4] Memory databus width                                               */
      __IOM uint32_t FACCEN     : 1;            /*!< [6..6] Flash access enable                                                */
      __IM  uint32_t            : 1;
      __IOM uint32_t BURSTEN    : 1;            /*!< [8..8] Burst enable bit                                                   */
      __IOM uint32_t WAITPOL    : 1;            /*!< [9..9] Wait signal polarity bit                                           */
      __IOM uint32_t WRAPMOD    : 1;            /*!< [10..10] Wrapped burst mode support                                       */
      __IOM uint32_t WAITCFG    : 1;            /*!< [11..11] Wait timing configuration                                        */
      __IOM uint32_t WREN       : 1;            /*!< [12..12] Write enable bit                                                 */
      __IOM uint32_t WAITEN     : 1;            /*!< [13..13] Wait enable bit                                                  */
      __IOM uint32_t EXTMOD     : 1;            /*!< [14..14] Extended mode enable                                             */
      __IOM uint32_t ASYNCWAIT  : 1;            /*!< [15..15] Wait signal during asynchronous transfers                        */
      __IM  uint32_t            : 3;
      __IOM uint32_t CBURSTRW   : 1;            /*!< [19..19] Write burst enable                                               */
    } bit;
  } BCR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) SRAM/NOR-Flash chip-select timing register 1               */
    
    struct {
      __IOM uint32_t ADDSET     : 4;            /*!< [3..0] Address setup phase duration                                       */
      __IOM uint32_t ADDHLD     : 4;            /*!< [7..4] Address-hold phase duration                                        */
      __IOM uint32_t DATAST     : 8;            /*!< [15..8] Data-phase duration                                               */
      __IOM uint32_t BUSTURN    : 4;            /*!< [19..16] Bus turnaround phase duration                                    */
      __IOM uint32_t CLKDIV     : 4;            /*!< [23..20] Clock divide ratio (for FSMC_CLK signal)                         */
      __IOM uint32_t DATLAT     : 4;            /*!< [27..24] Data latency for synchronous NOR Flash memory                    */
      __IOM uint32_t ACCMOD     : 2;            /*!< [29..28] Access mode                                                      */
    } bit;
  } BTR1;
  __IM  uint32_t  RESERVED[22];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000060) PC Card/NAND Flash control register 2                      */
    
    struct {
      __IM  uint32_t            : 1;
      __IOM uint32_t PWAITEN    : 1;            /*!< [1..1] Wait feature enable bit                                            */
      __IOM uint32_t PBKEN      : 1;            /*!< [2..2] PC Card/NAND Flash memory bank enable bit                          */
      __IOM uint32_t PTYP       : 1;            /*!< [3..3] Memory type                                                        */
      __IOM uint32_t PWID       : 2;            /*!< [5..4] Databus width                                                      */
      __IOM uint32_t ECCEN      : 1;            /*!< [6..6] ECC computation logic enable bit                                   */
      __IM  uint32_t            : 2;
      __IOM uint32_t TCLR       : 4;            /*!< [12..9] CLE to RE delay                                                   */
      __IOM uint32_t TAR        : 4;            /*!< [16..13] ALE to RE delay                                                  */
      __IOM uint32_t ECCPS      : 3;            /*!< [19..17] ECC page size                                                    */
    } bit;
  } PCR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000064) FIFO status and interrupt register 2                       */
    
    struct {
      __IOM uint32_t IRS        : 1;            /*!< [0..0] Interrupt rising edge status                                       */
      __IOM uint32_t ILS        : 1;            /*!< [1..1] Interrupt high-level status                                        */
      __IOM uint32_t IFS        : 1;            /*!< [2..2] Interrupt falling edge status                                      */
      __IOM uint32_t IREN       : 1;            /*!< [3..3] Interrupt rising edge detection enable bit                         */
      __IOM uint32_t ILEN       : 1;            /*!< [4..4] Interrupt high-level detection enable bit                          */
      __IOM uint32_t IFEN       : 1;            /*!< [5..5] Interrupt falling edge detection enable bit                        */
      __IM  uint32_t FEMPT      : 1;            /*!< [6..6] FIFO empty                                                         */
    } bit;
  } SR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000068) Common memory space timing register 2                      */
    
    struct {
      __IOM uint32_t MEMSETx    : 8;            /*!< [7..0] Common memory x setup  time                                        */
      __IOM uint32_t MEMWAITx   : 8;            /*!< [15..8] Common memory x wait  time                                        */
      __IOM uint32_t MEMHOLDx   : 8;            /*!< [23..16] Common memory x hold  time                                       */
      __IOM uint32_t MEMHIZx    : 8;            /*!< [31..24] Common memory x databus HiZ  time                                */
    } bit;
  } PMEM2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000006C) Attribute memory space timing register 2                   */
    
    struct {
      __IOM uint32_t ATTSETx    : 8;            /*!< [7..0] Attribute memory x setup time                                      */
      __IOM uint32_t ATTWAITx   : 8;            /*!< [15..8] Attribute memory x wait time                                      */
      __IOM uint32_t ATTHOLDx   : 8;            /*!< [23..16] Attribute memory x hold time                                     */
      __IOM uint32_t ATTHIZx    : 8;            /*!< [31..24] Attribute memory x databus HiZ time                              */
    } bit;
  } PATT2;
  __IM  uint32_t  RESERVED1;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000074) ECC result register 2                                      */
    
    struct {
      __IM  uint32_t ECCx       : 32;           /*!< [31..0] ECC result                                                        */
    } bit;
  } ECCR2;
  __IM  uint32_t  RESERVED2[35];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000104) SRAM/NOR-Flash write timing registers 1                    */
    
    struct {
      __IOM uint32_t ADDSET     : 4;            /*!< [3..0] Address setup phase duration                                       */
      __IOM uint32_t ADDHLD     : 4;            /*!< [7..4] Address-hold phase duration                                        */
      __IOM uint32_t DATAST     : 8;            /*!< [15..8] Data-phase duration                                               */
      __IM  uint32_t            : 4;
      __IOM uint32_t CLKDIV     : 4;            /*!< [23..20] Clock divide ratio (for FSMC_CLK signal)                         */
      __IOM uint32_t DATLAT     : 4;            /*!< [27..24] Data latency for synchronous NOR Flash memory                    */
      __IOM uint32_t ACCMOD     : 2;            /*!< [29..28] Access mode                                                      */
    } bit;
  } BWTR1;
} FSMC_Type;                                    /*!< Size = 264 (0x108)                                                        */



/* =========================================================================================================================== */
/* ================                                            DVP                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x50050000) DVP Structure                                              */
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000000) Digital Video control register (DVP_CR0)                   */
    
    struct {
      __IOM uint8_t RB_DVP_ENABLE : 1;          /*!< [0..0] DVP enable                                                         */
      __IOM uint8_t RB_DVP_V_POLAR : 1;         /*!< [1..1] DVP VSYNC polarity control                                         */
      __IOM uint8_t RB_DVP_H_POLAR : 1;         /*!< [2..2] DVP HSYNC polarity control                                         */
      __IOM uint8_t RB_DVP_P_POLAR : 1;         /*!< [3..3] DVP PCLK polarity control                                          */
      __IOM uint8_t RB_DVP_MSK_DAT_MOD : 2;     /*!< [5..4] DVP data mode                                                      */
      __IOM uint8_t RB_DVP_JPEG : 1;            /*!< [6..6] DVP JPEG mode                                                      */
    } bit;
  } CR0;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000001) Digital Video control register (DVP_CR1)                   */
    
    struct {
      __IOM uint8_t RB_DVP_DMA_EN : 1;          /*!< [0..0] DVP dma enable                                                     */
      __IOM uint8_t RB_DVP_ALL_CLR : 1;         /*!< [1..1] DVP all clear                                                      */
      __IOM uint8_t RB_DVP_RCV_CLR : 1;         /*!< [2..2] DVP receive logic clear                                            */
      __IOM uint8_t RB_DVP_BUF_TOG : 1;         /*!< [3..3] DVP bug toggle by software                                         */
      __IOM uint8_t RB_DVP_CM   : 1;            /*!< [4..4] DVP capture mode                                                   */
      __IOM uint8_t RB_DVP_CROP : 1;            /*!< [5..5] DVP Crop feature enable                                            */
      __IOM uint8_t RB_DVP_FCRC : 2;            /*!< [7..6] DVP frame capture rate control                                     */
    } bit;
  } CR1;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000002) Digital Video Interrupt register (DVP_IER)                 */
    
    struct {
      __IOM uint8_t RB_DVP_IE_STR_FRM : 1;      /*!< [0..0] DVP frame start interrupt enable                                   */
      __IOM uint8_t RB_DVP_IE_ROW_DONE : 1;     /*!< [1..1] DVP row received done interrupt enable                             */
      __IOM uint8_t RB_DVP_IE_FRM_DONE : 1;     /*!< [2..2] DVP frame received done interrupt enable                           */
      __IOM uint8_t RB_DVP_IE_FIFO_OV : 1;      /*!< [3..3] DVP receive fifo overflow interrupt enable                         */
      __IOM uint8_t RB_DVP_IE_STP_FRM : 1;      /*!< [4..4] DVP frame stop interrupt enable                                    */
    } bit;
  } IER;
  __IM  uint8_t   RESERVED;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000004) Image line count configuration register (DVP_ROW_NUM)      */
    
    struct {
      __IOM uint16_t RB_DVP_ROW_NUM : 16;       /*!< [15..0] The number of rows of frame image data                            */
    } bit;
  } ROW_NUM;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000006) Image column number configuration register (DVP_COL_NUM)   */
    
    struct {
      __IOM uint16_t RB_DVP_COL_NUM : 16;       /*!< [15..0] Number of PCLK cycles for row data                                */
    } bit;
  } COL_NUM;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Digital Video DMA address register (DVP_DMA_BUF0)          */
    
    struct {
      __IOM uint32_t RB_DVP_DMA_BUF0 : 17;      /*!< [16..0] DMA receive address 0                                             */
    } bit;
  } DMA_BUF0;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Digital Video DMA address register (DVP_DMA_BUF1)          */
    
    struct {
      __IOM uint32_t RB_DVP_DMA_BUF1 : 17;      /*!< [16..0] DMA receive address 1                                             */
    } bit;
  } DMA_BUF1;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000010) Digital Video Flag register (DVP_IFR)                      */
    
    struct {
      __IOM uint8_t RB_DVP_IF_STR_FRM : 1;      /*!< [0..0] DVP frame start interrupt enable                                   */
      __IOM uint8_t RB_DVP_IF_ROW_DONE : 1;     /*!< [1..1] DVP row received done interrupt enable                             */
      __IOM uint8_t RB_DVP_IF_FRM_DONE : 1;     /*!< [2..2] DVP frame received done interrupt enable                           */
      __IOM uint8_t RB_DVP_IF_FIFO_OV : 1;      /*!< [3..3] DVP receive fifo overflow interrupt enable                         */
      __IOM uint8_t RB_DVP_IF_STP_FRM : 1;      /*!< [4..4] DVP frame stop interrupt enable                                    */
    } bit;
  } IFR;
  
  union {
    __IM  uint8_t reg;                          /*!< (@ 0x00000011) Digital Video STATUS register (DVP_STATUS)                 */
    
    struct {
      __IM  uint8_t RB_DVP_FIFO_RDY : 1;        /*!< [0..0] DVP frame start interrupt enable                                   */
      __IM  uint8_t RB_DVP_FIFO_FULL : 1;       /*!< [1..1] DVP row received done interrupt enable                             */
      __IM  uint8_t RB_DVP_FIFO_OV : 1;         /*!< [2..2] DVP frame received done interrupt enable                           */
      __IM  uint8_t             : 1;
      __IM  uint8_t RB_DVP_MSK_FIFO_CNT : 3;    /*!< [6..4] DVP receive fifo overflow interrupt enable                         */
    } bit;
  } STATUS;
  __IM  uint16_t  RESERVED1;
  
  union {
    __IM  uint16_t reg;                         /*!< (@ 0x00000014) Digital Video line counter register (DVP_ROW_CNT)          */
    
    struct {
      __IM  uint16_t RB_DVP_ROW_CNT : 16;       /*!< [15..0] The number of rows of frame image data                            */
    } bit;
  } ROW_CNT;
  __IM  uint16_t  RESERVED2;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000018) Digital Video horizontal displacement register
                                                                    (DVP_HOFFCNT)                                              */
    
    struct {
      __IOM uint16_t RB_DVP_HOFFCNT : 16;       /*!< [15..0] Number of PCLK cycles for row data                                */
    } bit;
  } HOFFCNT;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000001A) Digital Video line number register (DVP_VST)               */
    
    struct {
      __IOM uint16_t RB_DVP_VST : 16;           /*!< [15..0] The number of lines captured by the image                         */
    } bit;
  } VST;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000001C) Digital Video Capture count register (DVP_CAPCNT)          */
    
    struct {
      __IOM uint16_t RB_DVP_CAPCNT : 16;        /*!< [15..0] Number of PCLK cycles captured by clipping window                 */
    } bit;
  } CAPCNT;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000001E) Digital Video Vertical line count register (DVP_VLINE)     */
    
    struct {
      __IOM uint16_t RB_DVP_VLINE : 16;         /*!< [15..0] Crop the number of rows captured by window                        */
    } bit;
  } VLINE;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000020) Digital Video Data register (DVP_DR)                       */
    
    struct {
      __IM  uint32_t RB_DVP_DR  : 32;           /*!< [31..0] Prevent DMA overflow                                              */
    } bit;
  } DR;
} DVP_Type;                                     /*!< Size = 36 (0x24)                                                          */



/* =========================================================================================================================== */
/* ================                                            DAC                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40007400) DAC Structure                                              */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Control register (DAC_CR)                                  */
    
    struct {
      __IOM uint32_t EN1        : 1;            /*!< [0..0] DAC channel1 enable                                                */
      __IOM uint32_t BOFF1      : 1;            /*!< [1..1] DAC channel1 output buffer disable                                 */
      __IOM uint32_t TEN1       : 1;            /*!< [2..2] DAC channel1 trigger enable                                        */
      __IOM uint32_t TSEL1      : 3;            /*!< [5..3] DAC channel1 trigger selection                                     */
      __IOM uint32_t WAVE1      : 2;            /*!< [7..6] DAC channel1 noise/triangle wave generation enable                 */
      __IOM uint32_t MAMP1      : 4;            /*!< [11..8] DAC channel1 mask/amplitude selector                              */
      __IOM uint32_t DMAEN1     : 1;            /*!< [12..12] DAC channel1 DMA enable                                          */
      __IM  uint32_t            : 3;
      __IOM uint32_t EN2        : 1;            /*!< [16..16] DAC channel2 enable                                              */
      __IOM uint32_t BOFF2      : 1;            /*!< [17..17] DAC channel2 output buffer disable                               */
      __IOM uint32_t TEN2       : 1;            /*!< [18..18] DAC channel2 trigger enable                                      */
      __IOM uint32_t TSEL2      : 3;            /*!< [21..19] DAC channel2 trigger selection                                   */
      __IOM uint32_t WAVE2      : 2;            /*!< [23..22] DAC channel2 noise/triangle wave generation enable               */
      __IOM uint32_t MAMP2      : 4;            /*!< [27..24] DAC channel2 mask/amplitude selector                             */
      __IOM uint32_t DMAEN2     : 1;            /*!< [28..28] DAC channel2 DMA enable                                          */
    } bit;
  } CTLR;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000004) DAC software trigger register (DAC_SWTRIGR)                */
    
    struct {
      __OM  uint32_t SWTRIG1    : 1;            /*!< [0..0] DAC channel1 software trigger                                      */
      __OM  uint32_t SWTRIG2    : 1;            /*!< [1..1] DAC channel2 software trigger                                      */
    } bit;
  } SWTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) DAC channel1 12-bit right-aligned data holding
                                                                    register(DAC_DHR12R1)                                      */
    
    struct {
      __IOM uint32_t DACC1DHR   : 12;           /*!< [11..0] DAC channel1 12-bit right-aligned data                            */
    } bit;
  } R12BDHR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) DAC channel1 12-bit left aligned data holding
                                                                    register (DAC_DHR12L1)                                     */
    
    struct {
      __IM  uint32_t            : 4;
      __IOM uint32_t DACC1DHR   : 12;           /*!< [15..4] DAC channel1 12-bit left-aligned data                             */
    } bit;
  } L12BDHR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) DAC channel1 8-bit right aligned data holding
                                                                    register (DAC_DHR8R1)                                      */
    
    struct {
      __IOM uint32_t DACC1DHR   : 8;            /*!< [7..0] DAC channel1 8-bit right-aligned data                              */
    } bit;
  } R8BDHR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) DAC channel2 12-bit right aligned data holding
                                                                    register (DAC_DHR12R2)                                     */
    
    struct {
      __IOM uint32_t DACC2DHR   : 12;           /*!< [11..0] DAC channel2 12-bit right-aligned data                            */
    } bit;
  } R12BDHR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) DAC channel2 12-bit left aligned data holding
                                                                    register (DAC_DHR12L2)                                     */
    
    struct {
      __IM  uint32_t            : 4;
      __IOM uint32_t DACC2DHR   : 12;           /*!< [15..4] DAC channel2 12-bit left-aligned data                             */
    } bit;
  } L12BDHR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) DAC channel2 8-bit right-aligned data holding
                                                                    register (DAC_DHR8R2)                                      */
    
    struct {
      __IOM uint32_t DACC2DHR   : 8;            /*!< [7..0] DAC channel2 8-bit right-aligned data                              */
    } bit;
  } R8BDHR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) Dual DAC 12-bit right-aligned data holding register
                                                                    (DAC_DHR12RD), Bits 31:28 Reserved, Bits
                                                                    15:12 Reserved                                             */
    
    struct {
      __IOM uint32_t DACC1DHR   : 12;           /*!< [11..0] DAC channel1 12-bit right-aligned data                            */
      __IM  uint32_t            : 4;
      __IOM uint32_t DACC2DHR   : 12;           /*!< [27..16] DAC channel2 12-bit right-aligned data                           */
    } bit;
  } RD12BDHR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) DUAL DAC 12-bit left aligned data holding register
                                                                    (DAC_DHR12LD), Bits 19:16 Reserved, Bits
                                                                    3:0 Reserved                                               */
    
    struct {
      __IM  uint32_t            : 4;
      __IOM uint32_t DACC1DHR   : 12;           /*!< [15..4] DAC channel1 12-bit left-aligned data                             */
      __IM  uint32_t            : 4;
      __IOM uint32_t DACC2DHR   : 12;           /*!< [31..20] DAC channel2 12-bit right-aligned data                           */
    } bit;
  } LD12BDHR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) DUAL DAC 8-bit right aligned data holding register
                                                                    (DAC_DHR8RD), Bits 31:16 Reserved                          */
    
    struct {
      __IOM uint32_t DACC1DHR   : 8;            /*!< [7..0] DAC channel1 8-bit right-aligned data                              */
      __IOM uint32_t DACC2DHR   : 8;            /*!< [15..8] DAC channel2 8-bit right-aligned data                             */
    } bit;
  } RD8BDHR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x0000002C) DAC channel1 data output register (DAC_DOR1)               */
    
    struct {
      __IM  uint32_t DACC1DOR   : 12;           /*!< [11..0] DAC channel1 data output                                          */
    } bit;
  } DOR1;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000030) DAC channel2 data output register (DAC_DOR2)               */
    
    struct {
      __IM  uint32_t DACC2DOR   : 12;           /*!< [11..0] DAC channel2 data output                                          */
    } bit;
  } DOR2;
} DAC_Type;                                     /*!< Size = 52 (0x34)                                                          */



/* =========================================================================================================================== */
/* ================                                            PWR                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40007000) PWR Structure                                              */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Power control register (PWR_CTRL)                          */
    
    struct {
      __IOM uint32_t LPDS       : 1;            /*!< [0..0] Low Power Deep Sleep                                               */
      __IOM uint32_t PDDS       : 1;            /*!< [1..1] Power Down Deep Sleep                                              */
      __IOM uint32_t CWUF       : 1;            /*!< [2..2] Clear Wake-up Flag                                                 */
      __IOM uint32_t CSBF       : 1;            /*!< [3..3] Clear STANDBY Flag                                                 */
      __IOM uint32_t PVDE       : 1;            /*!< [4..4] Power Voltage Detector Enable                                      */
      __IOM uint32_t PLS        : 3;            /*!< [7..5] PVD Level Selection                                                */
      __IOM uint32_t DBP        : 1;            /*!< [8..8] Disable Backup Domain write protection                             */
      __IM  uint32_t            : 7;
      __IOM uint32_t R2K_STYEN  : 1;            /*!< [16..16] standby 2k ram enable                                            */
      __IOM uint32_t R30K_STYEN : 1;            /*!< [17..17] standby 30k ram enable                                           */
      __IOM uint32_t R2K_VBATEN : 1;            /*!< [18..18] VBAT 30k ram enable                                              */
      __IOM uint32_t R30K_VBATEN : 1;           /*!< [19..19] VBAT 30k ram enable                                              */
      __IOM uint32_t RAM_LVEN   : 1;            /*!< [20..20] Ram LV Enable                                                    */
    } bit;
  } CTLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Power control register (PWR_CSR)                           */
    
    struct {
      __IM  uint32_t WUF        : 1;            /*!< [0..0] Wake-Up Flag                                                       */
      __IM  uint32_t SBF        : 1;            /*!< [1..1] STANDBY Flag                                                       */
      __IM  uint32_t PVDO       : 1;            /*!< [2..2] PVD Output                                                         */
      __IM  uint32_t            : 5;
      __IOM uint32_t EWUP       : 1;            /*!< [8..8] Enable WKUP pin                                                    */
    } bit;
  } CSR;
} PWR_Type;                                     /*!< Size = 8 (0x8)                                                            */



/* =========================================================================================================================== */
/* ================                                            RCC                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40021000) RCC Structure                                              */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Clock control register                                     */
    
    struct {
      __IOM uint32_t HSION      : 1;            /*!< [0..0] Internal High Speed clock enable                                   */
      __IM  uint32_t HSIRDY     : 1;            /*!< [1..1] Internal High Speed clock ready flag                               */
      __IM  uint32_t            : 1;
      __IOM uint32_t HSITRIM    : 5;            /*!< [7..3] Internal High Speed clock trimming                                 */
      __IM  uint32_t HSICAL     : 8;            /*!< [15..8] Internal High Speed clock Calibration                             */
      __IOM uint32_t HSEON      : 1;            /*!< [16..16] External High Speed clock enable                                 */
      __IM  uint32_t HSERDY     : 1;            /*!< [17..17] External High Speed clock ready flag                             */
      __IOM uint32_t HSEBYP     : 1;            /*!< [18..18] External High Speed clock Bypass                                 */
      __IOM uint32_t CSSON      : 1;            /*!< [19..19] Clock Security System enable                                     */
      __IM  uint32_t            : 4;
      __IOM uint32_t PLLON      : 1;            /*!< [24..24] PLL enable                                                       */
      __IM  uint32_t PLLRDY     : 1;            /*!< [25..25] PLL clock ready flag                                             */
      __IOM uint32_t PLL2ON     : 1;            /*!< [26..26] PLL2 enable                                                      */
      __IM  uint32_t PLL2RDY    : 1;            /*!< [27..27] PLL2 clock ready flag                                            */
      __IOM uint32_t PLL3ON     : 1;            /*!< [28..28] PLL3 enable                                                      */
      __IM  uint32_t PLL3RDY    : 1;            /*!< [29..29] PLL3 clock ready flag                                            */
    } bit;
  } CTLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Clock configuration register (RCC_CFGR0)                   */
    
    struct {
      __IOM uint32_t SW         : 2;            /*!< [1..0] System clock Switch                                                */
      __IM  uint32_t SWS        : 2;            /*!< [3..2] System Clock Switch Status                                         */
      __IOM uint32_t HPRE       : 4;            /*!< [7..4] AHB prescaler                                                      */
      __IOM uint32_t PPRE1      : 3;            /*!< [10..8] APB Low speed prescaler (APB1)                                    */
      __IOM uint32_t PPRE2      : 3;            /*!< [13..11] APB High speed prescaler (APB2)                                  */
      __IOM uint32_t ADCPRE     : 2;            /*!< [15..14] ADC prescaler                                                    */
      __IOM uint32_t PLLSRC     : 1;            /*!< [16..16] PLL entry clock source                                           */
      __IOM uint32_t PLLXTPRE   : 1;            /*!< [17..17] HSE divider for PLL entry                                        */
      __IOM uint32_t PLLMUL     : 4;            /*!< [21..18] PLL Multiplication Factor                                        */
      __IOM uint32_t USBPRE     : 2;            /*!< [23..22] USB prescaler                                                    */
      __IOM uint32_t MCO        : 4;            /*!< [27..24] Microcontroller clock output                                     */
      __IM  uint32_t            : 3;
      __IOM uint32_t ADC_CLK_ADJ : 1;           /*!< [31..31] ADC clock ADJ                                                    */
    } bit;
  } CFGR0;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Clock interrupt register (RCC_INTR)                        */
    
    struct {
      __IM  uint32_t LSIRDYF    : 1;            /*!< [0..0] LSI Ready Interrupt flag                                           */
      __IM  uint32_t LSERDYF    : 1;            /*!< [1..1] LSE Ready Interrupt flag                                           */
      __IM  uint32_t HSIRDYF    : 1;            /*!< [2..2] HSI Ready Interrupt flag                                           */
      __IM  uint32_t HSERDYF    : 1;            /*!< [3..3] HSE Ready Interrupt flag                                           */
      __IM  uint32_t PLLRDYF    : 1;            /*!< [4..4] PLL Ready Interrupt flag                                           */
      __IM  uint32_t PLL2RDYF   : 1;            /*!< [5..5] PLL2 Ready Interrupt flag                                          */
      __IM  uint32_t PLL3RDYF   : 1;            /*!< [6..6] PLL3 Ready Interrupt flag                                          */
      __IM  uint32_t CSSF       : 1;            /*!< [7..7] Clock Security System Interrupt flag                               */
      __IOM uint32_t LSIRDYIE   : 1;            /*!< [8..8] LSI Ready Interrupt Enable                                         */
      __IOM uint32_t LSERDYIE   : 1;            /*!< [9..9] LSE Ready Interrupt Enable                                         */
      __IOM uint32_t HSIRDYIE   : 1;            /*!< [10..10] HSI Ready Interrupt Enable                                       */
      __IOM uint32_t HSERDYIE   : 1;            /*!< [11..11] HSE Ready Interrupt Enable                                       */
      __IOM uint32_t PLLRDYIE   : 1;            /*!< [12..12] PLL Ready Interrupt Enable                                       */
      __IOM uint32_t PLL2RDYIE  : 1;            /*!< [13..13] PLL2 Ready Interrupt Enable                                      */
      __IOM uint32_t PLL3RDYIE  : 1;            /*!< [14..14] PLL3 Ready Interrupt Enable                                      */
      __IM  uint32_t            : 1;
      __OM  uint32_t LSIRDYC    : 1;            /*!< [16..16] LSI Ready Interrupt Clear                                        */
      __OM  uint32_t LSERDYC    : 1;            /*!< [17..17] LSE Ready Interrupt Clear                                        */
      __OM  uint32_t HSIRDYC    : 1;            /*!< [18..18] HSI Ready Interrupt Clear                                        */
      __OM  uint32_t HSERDYC    : 1;            /*!< [19..19] HSE Ready Interrupt Clear                                        */
      __OM  uint32_t PLLRDYC    : 1;            /*!< [20..20] PLL Ready Interrupt Clear                                        */
      __OM  uint32_t PLL2RDYC   : 1;            /*!< [21..21] PLL2 Ready Interrupt Clear                                       */
      __OM  uint32_t PLL3RDYC   : 1;            /*!< [22..22] PLL3 Ready Interrupt Clear                                       */
      __OM  uint32_t CSSC       : 1;            /*!< [23..23] Clock security system interrupt clear                            */
    } bit;
  } INTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) APB2 peripheral reset register (RCC_APB2PRSTR)             */
    
    struct {
      __IOM uint32_t AFIORST    : 1;            /*!< [0..0] Alternate function I/O reset                                       */
      __IM  uint32_t            : 1;
      __IOM uint32_t IOPARST    : 1;            /*!< [2..2] IO port A reset                                                    */
      __IOM uint32_t IOPBRST    : 1;            /*!< [3..3] IO port B reset                                                    */
      __IOM uint32_t IOPCRST    : 1;            /*!< [4..4] IO port C reset                                                    */
      __IOM uint32_t IOPDRST    : 1;            /*!< [5..5] IO port D reset                                                    */
      __IOM uint32_t IOPERST    : 1;            /*!< [6..6] IO port E reset                                                    */
      __IM  uint32_t            : 2;
      __IOM uint32_t ADC1RST    : 1;            /*!< [9..9] ADC 1 interface reset                                              */
      __IOM uint32_t ADC2RST    : 1;            /*!< [10..10] ADC 2 interface reset                                            */
      __IOM uint32_t TIM1RST    : 1;            /*!< [11..11] TIM1 timer reset                                                 */
      __IOM uint32_t SPI1RST    : 1;            /*!< [12..12] SPI 1 reset                                                      */
      __IOM uint32_t TIM8RST    : 1;            /*!< [13..13] TIM8 timer reset                                                 */
      __IOM uint32_t USART1RST  : 1;            /*!< [14..14] USART1 reset                                                     */
      __IM  uint32_t            : 4;
      __IOM uint32_t TIM9RST    : 1;            /*!< [19..19] TIM9 timer reset                                                 */
      __IOM uint32_t TIM10RST   : 1;            /*!< [20..20] TIM10 timer reset                                                */
    } bit;
  } APB2PRSTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) APB1 peripheral reset register (RCC_APB1PRSTR)             */
    
    struct {
      __IOM uint32_t TIM2RST    : 1;            /*!< [0..0] Timer 2 reset                                                      */
      __IOM uint32_t TIM3RST    : 1;            /*!< [1..1] Timer 3 reset                                                      */
      __IOM uint32_t TIM4RST    : 1;            /*!< [2..2] Timer 4 reset                                                      */
      __IOM uint32_t TIM5RST    : 1;            /*!< [3..3] Timer 5 reset                                                      */
      __IOM uint32_t TIM6RST    : 1;            /*!< [4..4] Timer 6 reset                                                      */
      __IOM uint32_t TIM7RST    : 1;            /*!< [5..5] Timer 7 reset                                                      */
      __IOM uint32_t UART6RST   : 1;            /*!< [6..6] UART 6 reset                                                       */
      __IOM uint32_t UART7RST   : 1;            /*!< [7..7] UART 7 reset                                                       */
      __IOM uint32_t UART8RST   : 1;            /*!< [8..8] UART 8 reset                                                       */
      __IM  uint32_t            : 2;
      __IOM uint32_t WWDGRST    : 1;            /*!< [11..11] Window watchdog reset                                            */
      __IM  uint32_t            : 2;
      __IOM uint32_t SPI2RST    : 1;            /*!< [14..14] SPI2 reset                                                       */
      __IOM uint32_t SPI3RST    : 1;            /*!< [15..15] SPI3 reset                                                       */
      __IM  uint32_t            : 1;
      __IOM uint32_t USART2RST  : 1;            /*!< [17..17] USART 2 reset                                                    */
      __IOM uint32_t USART3RST  : 1;            /*!< [18..18] USART 3 reset                                                    */
      __IOM uint32_t USART4RST  : 1;            /*!< [19..19] USART 4 reset                                                    */
      __IOM uint32_t USART5RST  : 1;            /*!< [20..20] USART 5 reset                                                    */
      __IOM uint32_t I2C1RST    : 1;            /*!< [21..21] I2C1 reset                                                       */
      __IOM uint32_t I2C2RST    : 1;            /*!< [22..22] I2C2 reset                                                       */
      __IOM uint32_t USBDRST    : 1;            /*!< [23..23] USBD reset                                                       */
      __IM  uint32_t            : 1;
      __IOM uint32_t CAN1RST    : 1;            /*!< [25..25] CAN1 reset                                                       */
      __IOM uint32_t CAN2RST    : 1;            /*!< [26..26] CAN2 reset                                                       */
      __IOM uint32_t BKPRST     : 1;            /*!< [27..27] Backup interface reset                                           */
      __IOM uint32_t PWRRST     : 1;            /*!< [28..28] Power interface reset                                            */
      __IOM uint32_t DACRST     : 1;            /*!< [29..29] DAC interface reset                                              */
    } bit;
  } APB1PRSTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) AHB Peripheral Clock enable register (RCC_AHBPCENR)        */
    
    struct {
      __IOM uint32_t DMA1EN     : 1;            /*!< [0..0] DMA clock enable                                                   */
      __IOM uint32_t DMA2EN     : 1;            /*!< [1..1] DMA2 clock enable                                                  */
      __IOM uint32_t SRAMEN     : 1;            /*!< [2..2] SRAM interface clock enable                                        */
      __IM  uint32_t            : 1;
      __IOM uint32_t FLITFEN    : 1;            /*!< [4..4] FLITF clock enable                                                 */
      __IM  uint32_t            : 1;
      __IOM uint32_t CRCEN      : 1;            /*!< [6..6] CRC clock enable                                                   */
      __IM  uint32_t            : 1;
      __IOM uint32_t FSMCEN     : 1;            /*!< [8..8] FSMC clock enable                                                  */
      __IOM uint32_t TRNG_EN    : 1;            /*!< [9..9] TRNG clock enable                                                  */
      __IOM uint32_t SDIOEN     : 1;            /*!< [10..10] SDIO clock enable                                                */
      __IOM uint32_t USBHS_EN   : 1;            /*!< [11..11] USBHS clock enable                                               */
      __IOM uint32_t OTG_EN     : 1;            /*!< [12..12] OTG clock enable                                                 */
      __IOM uint32_t DVP_EN     : 1;            /*!< [13..13] DVP clock enable                                                 */
      __IOM uint32_t ETHMACEN   : 1;            /*!< [14..14] Ethernet MAC clock enable                                        */
      __IOM uint32_t ETHMACTXEN : 1;            /*!< [15..15] Ethernet MAC TX clock enable                                     */
      __IOM uint32_t ETHMACRXEN : 1;            /*!< [16..16] Ethernet MAC RX clock enable                                     */
    } bit;
  } AHBPCENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) APB2 peripheral clock enable register (RCC_APB2PCENR)      */
    
    struct {
      __IOM uint32_t AFIOEN     : 1;            /*!< [0..0] Alternate function I/O clock enable                                */
      __IM  uint32_t            : 1;
      __IOM uint32_t IOPAEN     : 1;            /*!< [2..2] I/O port A clock enable                                            */
      __IOM uint32_t IOPBEN     : 1;            /*!< [3..3] I/O port B clock enable                                            */
      __IOM uint32_t IOPCEN     : 1;            /*!< [4..4] I/O port C clock enable                                            */
      __IOM uint32_t IOPDEN     : 1;            /*!< [5..5] I/O port D clock enable                                            */
      __IOM uint32_t IOPEEN     : 1;            /*!< [6..6] I/O port E clock enable                                            */
      __IM  uint32_t            : 2;
      __IOM uint32_t ADC1EN     : 1;            /*!< [9..9] ADC1 interface clock enable                                        */
      __IOM uint32_t ADC2EN     : 1;            /*!< [10..10] ADC 2 interface clock enable                                     */
      __IOM uint32_t TIM1EN     : 1;            /*!< [11..11] TIM1 Timer clock enable                                          */
      __IOM uint32_t SPI1EN     : 1;            /*!< [12..12] SPI 1 clock enable                                               */
      __IOM uint32_t TIM8EN     : 1;            /*!< [13..13] TIM8 Timer clock enable                                          */
      __IOM uint32_t USART1EN   : 1;            /*!< [14..14] USART1 clock enable                                              */
      __IM  uint32_t            : 4;
      __IOM uint32_t TIM9_EN    : 1;            /*!< [19..19] TIM9 Timer clock enable                                          */
      __IOM uint32_t TIM10_EN   : 1;            /*!< [20..20] TIM10 Timer clock enable                                         */
    } bit;
  } APB2PCENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) APB1 peripheral clock enable register (RCC_APB1PCENR)      */
    
    struct {
      __IOM uint32_t TIM2EN     : 1;            /*!< [0..0] Timer 2 clock enable                                               */
      __IOM uint32_t TIM3EN     : 1;            /*!< [1..1] Timer 3 clock enable                                               */
      __IOM uint32_t TIM4EN     : 1;            /*!< [2..2] Timer 4 clock enable                                               */
      __IOM uint32_t TIM5EN     : 1;            /*!< [3..3] Timer 5 clock enable                                               */
      __IOM uint32_t TIM6EN     : 1;            /*!< [4..4] Timer 6 clock enable                                               */
      __IOM uint32_t TIM7EN     : 1;            /*!< [5..5] Timer 7 clock enable                                               */
      __IOM uint32_t USART6_EN  : 1;            /*!< [6..6] USART 6 clock enable                                               */
      __IOM uint32_t USART7_EN  : 1;            /*!< [7..7] USART 7 clock enable                                               */
      __IOM uint32_t USART8_EN  : 1;            /*!< [8..8] USART 8 clock enable                                               */
      __IM  uint32_t            : 2;
      __IOM uint32_t WWDGEN     : 1;            /*!< [11..11] Window watchdog clock enable                                     */
      __IM  uint32_t            : 2;
      __IOM uint32_t SPI2EN     : 1;            /*!< [14..14] SPI 2 clock enable                                               */
      __IOM uint32_t SPI3EN     : 1;            /*!< [15..15] SPI 3 clock enable                                               */
      __IM  uint32_t            : 1;
      __IOM uint32_t USART2EN   : 1;            /*!< [17..17] USART 2 clock enable                                             */
      __IOM uint32_t USART3EN   : 1;            /*!< [18..18] USART 3 clock enable                                             */
      __IOM uint32_t UART4EN    : 1;            /*!< [19..19] UART 4 clock enable                                              */
      __IOM uint32_t UART5EN    : 1;            /*!< [20..20] UART 5 clock enable                                              */
      __IOM uint32_t I2C1EN     : 1;            /*!< [21..21] I2C 1 clock enable                                               */
      __IOM uint32_t I2C2EN     : 1;            /*!< [22..22] I2C 2 clock enable                                               */
      __IOM uint32_t USBDEN     : 1;            /*!< [23..23] USBD clock enable                                                */
      __IM  uint32_t            : 1;
      __IOM uint32_t CAN1EN     : 1;            /*!< [25..25] CAN1 clock enable                                                */
      __IOM uint32_t CAN2EN     : 1;            /*!< [26..26] CAN2 clock enable                                                */
      __IOM uint32_t BKPEN      : 1;            /*!< [27..27] Backup interface clock enable                                    */
      __IOM uint32_t PWREN      : 1;            /*!< [28..28] Power interface clock enable                                     */
      __IOM uint32_t DACEN      : 1;            /*!< [29..29] DAC interface clock enable                                       */
    } bit;
  } APB1PCENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) Backup domain control register (RCC_BDCTLR)                */
    
    struct {
      __IOM uint32_t LSEON      : 1;            /*!< [0..0] External Low Speed oscillator enable                               */
      __IM  uint32_t LSERDY     : 1;            /*!< [1..1] External Low Speed oscillator ready                                */
      __IOM uint32_t LSEBYP     : 1;            /*!< [2..2] External Low Speed oscillator bypass                               */
      __IM  uint32_t            : 5;
      __IOM uint32_t RTCSEL     : 2;            /*!< [9..8] RTC clock source selection                                         */
      __IM  uint32_t            : 5;
      __IOM uint32_t RTCEN      : 1;            /*!< [15..15] RTC clock enable                                                 */
      __IOM uint32_t BDRST      : 1;            /*!< [16..16] Backup domain software reset                                     */
    } bit;
  } BDCTLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) Control/status register (RCC_RSTSCKR)                      */
    
    struct {
      __IOM uint32_t LSION      : 1;            /*!< [0..0] Internal low speed oscillator enable                               */
      __IM  uint32_t LSIRDY     : 1;            /*!< [1..1] Internal low speed oscillator ready                                */
      __IM  uint32_t            : 22;
      __IOM uint32_t RMVF       : 1;            /*!< [24..24] Remove reset flag                                                */
      __IM  uint32_t            : 1;
      __IOM uint32_t PINRSTF    : 1;            /*!< [26..26] PIN reset flag                                                   */
      __IOM uint32_t PORRSTF    : 1;            /*!< [27..27] POR/PDR reset flag                                               */
      __IOM uint32_t SFTRSTF    : 1;            /*!< [28..28] Software reset flag                                              */
      __IOM uint32_t IWDGRSTF   : 1;            /*!< [29..29] Independent watchdog reset flag                                  */
      __IOM uint32_t WWDGRSTF   : 1;            /*!< [30..30] Window watchdog reset flag                                       */
      __IOM uint32_t LPWRRSTF   : 1;            /*!< [31..31] Low-power reset flag                                             */
    } bit;
  } RSTSCKR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) AHB reset register (RCC_APHBRSTR)                          */
    
    struct {
      __IM  uint32_t            : 12;
      __IOM uint32_t USBHDRST   : 1;            /*!< [12..12] USBHD reset                                                      */
      __IM  uint32_t DVPRST     : 1;            /*!< [13..13] DVP reset                                                        */
      __IOM uint32_t ETHMACRST  : 1;            /*!< [14..14] Ethernet MAC reset                                               */
    } bit;
  } AHBRSTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) Clock configuration register2 (RCC_CFGR2)                  */
    
    struct {
      __IOM uint32_t PREDIV1    : 4;            /*!< [3..0] PREDIV1 division factor                                            */
      __IOM uint32_t PREDIV2    : 4;            /*!< [7..4] PREDIV2 division factor                                            */
      __IOM uint32_t PLL2MUL    : 4;            /*!< [11..8] PLL2 Multiplication Factor                                        */
      __IOM uint32_t PLL3MUL    : 4;            /*!< [15..12] PLL3 Multiplication Factor                                       */
      __IOM uint32_t PREDIV1SRC : 1;            /*!< [16..16] PREDIV1 entry clock source                                       */
      __IOM uint32_t I2S2SRC    : 1;            /*!< [17..17] I2S2 clock source                                                */
      __IOM uint32_t I2S3SRC    : 1;            /*!< [18..18] I2S3 clock source                                                */
      __IOM uint32_t TRNG_SRC   : 1;            /*!< [19..19] TRNG clock source                                                */
      __IOM uint32_t ETH1G_SRC  : 2;            /*!< [21..20] ETH1G clock source                                               */
      __IOM uint32_t ETH1G_125M_EN : 1;         /*!< [22..22] ETH1G _125M clock enable                                         */
      __IM  uint32_t            : 1;
      __IOM uint32_t USBHS_PREDIY : 3;          /*!< [26..24] USB HS PREDIV division factor                                    */
      __IOM uint32_t USBHS_PLL_SRC : 1;         /*!< [27..27] USB HS Multiplication Factor clock source                        */
      __IOM uint32_t USBHS_CKPEF_SEL : 2;       /*!< [29..28] USB HS Peference Clock source                                    */
      __IOM uint32_t USBHS_PLLALIVE : 1;        /*!< [30..30] USB HS Multiplication control                                    */
      __IOM uint32_t USBHS_CLK_SRC : 1;         /*!< [31..31] USB HS clock source                                              */
    } bit;
  } CFGR2;
} RCC_Type;                                     /*!< Size = 48 (0x30)                                                          */



/* =========================================================================================================================== */
/* ================                                          EXTEND                                           ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40023800) EXTEND Structure                                           */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) EXTEND register                                            */
    
    struct {
      __IOM uint32_t USBDLS     : 1;            /*!< [0..0] USBD Lowspeed Enable                                               */
      __IOM uint32_t USBDPU     : 1;            /*!< [1..1] USBD pullup Enable                                                 */
      __IOM uint32_t ETH_10M_EN : 1;            /*!< [2..2] ETH 10M Enable                                                     */
      __IOM uint32_t ETH_RGMII_EN : 1;          /*!< [3..3] ETH RGMII Enable                                                   */
      __IOM uint32_t PLL_HSI_PRE : 1;           /*!< [4..4] Whether HSI is divided                                             */
      __IM  uint32_t            : 1;
      __IOM uint32_t LOCKUP_EN  : 1;            /*!< [6..6] LOCKUP_Eable                                                       */
      __IOM uint32_t LOCKUP_RSTF : 1;           /*!< [7..7] LOCKUP RESET                                                       */
      __IOM uint32_t ULLDO_TRIM : 2;            /*!< [9..8] ULLDO_TRIM                                                         */
      __IOM uint32_t LDO_TRIM   : 2;            /*!< [11..10] LDO_TRIM                                                         */
      __IOM uint32_t HSE_KEEP_LP : 1;           /*!< [12..12] HSE_KEEP_LP                                                      */
    } bit;
  } EXTEND_CTR;
} EXTEND_Type;                                  /*!< Size = 4 (0x4)                                                            */



/* =========================================================================================================================== */
/* ================                                            OPA                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40023804) OPA Structure                                              */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Control register                                           */
    
    struct {
      __IOM uint32_t EN1        : 1;            /*!< [0..0] OPA Enable1                                                        */
      __IOM uint32_t MODE1      : 1;            /*!< [1..1] OPA MODE1                                                          */
      __IOM uint32_t NSEL1      : 1;            /*!< [2..2] OPA NSEL1                                                          */
      __IOM uint32_t PSEL1      : 1;            /*!< [3..3] OPA PSEL1                                                          */
      __IOM uint32_t EN2        : 1;            /*!< [4..4] OPA Enable2                                                        */
      __IOM uint32_t MODE2      : 1;            /*!< [5..5] OPA MODE2                                                          */
      __IOM uint32_t NSEL2      : 1;            /*!< [6..6] OPA NSEL2                                                          */
      __IOM uint32_t PSEL2      : 1;            /*!< [7..7] OPA PSEL2                                                          */
      __IOM uint32_t EN3        : 1;            /*!< [8..8] OPA Eable3                                                         */
      __IOM uint32_t MODE3      : 1;            /*!< [9..9] OPA MODE3                                                          */
      __IOM uint32_t NSEL3      : 1;            /*!< [10..10] OPA NSEL3                                                        */
      __IOM uint32_t PSEL3      : 1;            /*!< [11..11] OPA PSEL3                                                        */
      __IOM uint32_t EN4        : 1;            /*!< [12..12] OPA Enable4                                                      */
      __IOM uint32_t MODE4      : 1;            /*!< [13..13] OPA MODE4                                                        */
      __IOM uint32_t NSEL4      : 1;            /*!< [14..14] OPA NSEL4                                                        */
      __IOM uint32_t PSEL4      : 1;            /*!< [15..15] OPA PSEL4                                                        */
    } bit;
  } CR;
} OPA_Type;                                     /*!< Size = 4 (0x4)                                                            */



/* =========================================================================================================================== */
/* ================                                           GPIOA                                           ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40010800) GPIOA Structure                                            */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Port configuration register low (GPIOn_CFGLR)              */
    
    struct {
      __IOM uint32_t MODE0      : 2;            /*!< [1..0] Port n.0 mode bits                                                 */
      __IOM uint32_t CNF0       : 2;            /*!< [3..2] Port n.0 configuration bits                                        */
      __IOM uint32_t MODE1      : 2;            /*!< [5..4] Port n.1 mode bits                                                 */
      __IOM uint32_t CNF1       : 2;            /*!< [7..6] Port n.1 configuration bits                                        */
      __IOM uint32_t MODE2      : 2;            /*!< [9..8] Port n.2 mode bits                                                 */
      __IOM uint32_t CNF2       : 2;            /*!< [11..10] Port n.2 configuration bits                                      */
      __IOM uint32_t MODE3      : 2;            /*!< [13..12] Port n.3 mode bits                                               */
      __IOM uint32_t CNF3       : 2;            /*!< [15..14] Port n.3 configuration bits                                      */
      __IOM uint32_t MODE4      : 2;            /*!< [17..16] Port n.4 mode bits                                               */
      __IOM uint32_t CNF4       : 2;            /*!< [19..18] Port n.4 configuration bits                                      */
      __IOM uint32_t MODE5      : 2;            /*!< [21..20] Port n.5 mode bits                                               */
      __IOM uint32_t CNF5       : 2;            /*!< [23..22] Port n.5 configuration bits                                      */
      __IOM uint32_t MODE6      : 2;            /*!< [25..24] Port n.6 mode bits                                               */
      __IOM uint32_t CNF6       : 2;            /*!< [27..26] Port n.6 configuration bits                                      */
      __IOM uint32_t MODE7      : 2;            /*!< [29..28] Port n.7 mode bits                                               */
      __IOM uint32_t CNF7       : 2;            /*!< [31..30] Port n.7 configuration bits                                      */
    } bit;
  } CFGLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Port configuration register high (GPIOn_CFGHR)             */
    
    struct {
      __IOM uint32_t MODE8      : 2;            /*!< [1..0] Port n.8 mode bits                                                 */
      __IOM uint32_t CNF8       : 2;            /*!< [3..2] Port n.8 configuration bits                                        */
      __IOM uint32_t MODE9      : 2;            /*!< [5..4] Port n.9 mode bits                                                 */
      __IOM uint32_t CNF9       : 2;            /*!< [7..6] Port n.9 configuration bits                                        */
      __IOM uint32_t MODE10     : 2;            /*!< [9..8] Port n.10 mode bits                                                */
      __IOM uint32_t CNF10      : 2;            /*!< [11..10] Port n.10 configuration bits                                     */
      __IOM uint32_t MODE11     : 2;            /*!< [13..12] Port n.11 mode bits                                              */
      __IOM uint32_t CNF11      : 2;            /*!< [15..14] Port n.11 configuration bits                                     */
      __IOM uint32_t MODE12     : 2;            /*!< [17..16] Port n.12 mode bits                                              */
      __IOM uint32_t CNF12      : 2;            /*!< [19..18] Port n.12 configuration bits                                     */
      __IOM uint32_t MODE13     : 2;            /*!< [21..20] Port n.13 mode bits                                              */
      __IOM uint32_t CNF13      : 2;            /*!< [23..22] Port n.13 configuration bits                                     */
      __IOM uint32_t MODE14     : 2;            /*!< [25..24] Port n.14 mode bits                                              */
      __IOM uint32_t CNF14      : 2;            /*!< [27..26] Port n.14 configuration bits                                     */
      __IOM uint32_t MODE15     : 2;            /*!< [29..28] Port n.15 mode bits                                              */
      __IOM uint32_t CNF15      : 2;            /*!< [31..30] Port n.15 configuration bits                                     */
    } bit;
  } CFGHR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000008) Port input data register (GPIOn_INDR)                      */
    
    struct {
      __IM  uint32_t IDR0       : 1;            /*!< [0..0] Port input data                                                    */
      __IM  uint32_t IDR1       : 1;            /*!< [1..1] Port input data                                                    */
      __IM  uint32_t IDR2       : 1;            /*!< [2..2] Port input data                                                    */
      __IM  uint32_t IDR3       : 1;            /*!< [3..3] Port input data                                                    */
      __IM  uint32_t IDR4       : 1;            /*!< [4..4] Port input data                                                    */
      __IM  uint32_t IDR5       : 1;            /*!< [5..5] Port input data                                                    */
      __IM  uint32_t IDR6       : 1;            /*!< [6..6] Port input data                                                    */
      __IM  uint32_t IDR7       : 1;            /*!< [7..7] Port input data                                                    */
      __IM  uint32_t IDR8       : 1;            /*!< [8..8] Port input data                                                    */
      __IM  uint32_t IDR9       : 1;            /*!< [9..9] Port input data                                                    */
      __IM  uint32_t IDR10      : 1;            /*!< [10..10] Port input data                                                  */
      __IM  uint32_t IDR11      : 1;            /*!< [11..11] Port input data                                                  */
      __IM  uint32_t IDR12      : 1;            /*!< [12..12] Port input data                                                  */
      __IM  uint32_t IDR13      : 1;            /*!< [13..13] Port input data                                                  */
      __IM  uint32_t IDR14      : 1;            /*!< [14..14] Port input data                                                  */
      __IM  uint32_t IDR15      : 1;            /*!< [15..15] Port input data                                                  */
    } bit;
  } INDR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Port output data register (GPIOn_OUTDR)                    */
    
    struct {
      __IOM uint32_t ODR0       : 1;            /*!< [0..0] Port output data                                                   */
      __IOM uint32_t ODR1       : 1;            /*!< [1..1] Port output data                                                   */
      __IOM uint32_t ODR2       : 1;            /*!< [2..2] Port output data                                                   */
      __IOM uint32_t ODR3       : 1;            /*!< [3..3] Port output data                                                   */
      __IOM uint32_t ODR4       : 1;            /*!< [4..4] Port output data                                                   */
      __IOM uint32_t ODR5       : 1;            /*!< [5..5] Port output data                                                   */
      __IOM uint32_t ODR6       : 1;            /*!< [6..6] Port output data                                                   */
      __IOM uint32_t ODR7       : 1;            /*!< [7..7] Port output data                                                   */
      __IOM uint32_t ODR8       : 1;            /*!< [8..8] Port output data                                                   */
      __IOM uint32_t ODR9       : 1;            /*!< [9..9] Port output data                                                   */
      __IOM uint32_t ODR10      : 1;            /*!< [10..10] Port output data                                                 */
      __IOM uint32_t ODR11      : 1;            /*!< [11..11] Port output data                                                 */
      __IOM uint32_t ODR12      : 1;            /*!< [12..12] Port output data                                                 */
      __IOM uint32_t ODR13      : 1;            /*!< [13..13] Port output data                                                 */
      __IOM uint32_t ODR14      : 1;            /*!< [14..14] Port output data                                                 */
      __IOM uint32_t ODR15      : 1;            /*!< [15..15] Port output data                                                 */
    } bit;
  } OUTDR;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000010) Port bit set/reset register (GPIOn_BSHR)                   */
    
    struct {
      __OM  uint32_t BS0        : 1;            /*!< [0..0] Set bit 0                                                          */
      __OM  uint32_t BS1        : 1;            /*!< [1..1] Set bit 1                                                          */
      __OM  uint32_t BS2        : 1;            /*!< [2..2] Set bit 1                                                          */
      __OM  uint32_t BS3        : 1;            /*!< [3..3] Set bit 3                                                          */
      __OM  uint32_t BS4        : 1;            /*!< [4..4] Set bit 4                                                          */
      __OM  uint32_t BS5        : 1;            /*!< [5..5] Set bit 5                                                          */
      __OM  uint32_t BS6        : 1;            /*!< [6..6] Set bit 6                                                          */
      __OM  uint32_t BS7        : 1;            /*!< [7..7] Set bit 7                                                          */
      __OM  uint32_t BS8        : 1;            /*!< [8..8] Set bit 8                                                          */
      __OM  uint32_t BS9        : 1;            /*!< [9..9] Set bit 9                                                          */
      __OM  uint32_t BS10       : 1;            /*!< [10..10] Set bit 10                                                       */
      __OM  uint32_t BS11       : 1;            /*!< [11..11] Set bit 11                                                       */
      __OM  uint32_t BS12       : 1;            /*!< [12..12] Set bit 12                                                       */
      __OM  uint32_t BS13       : 1;            /*!< [13..13] Set bit 13                                                       */
      __OM  uint32_t BS14       : 1;            /*!< [14..14] Set bit 14                                                       */
      __OM  uint32_t BS15       : 1;            /*!< [15..15] Set bit 15                                                       */
      __OM  uint32_t BR0        : 1;            /*!< [16..16] Reset bit 0                                                      */
      __OM  uint32_t BR1        : 1;            /*!< [17..17] Reset bit 1                                                      */
      __OM  uint32_t BR2        : 1;            /*!< [18..18] Reset bit 2                                                      */
      __OM  uint32_t BR3        : 1;            /*!< [19..19] Reset bit 3                                                      */
      __OM  uint32_t BR4        : 1;            /*!< [20..20] Reset bit 4                                                      */
      __OM  uint32_t BR5        : 1;            /*!< [21..21] Reset bit 5                                                      */
      __OM  uint32_t BR6        : 1;            /*!< [22..22] Reset bit 6                                                      */
      __OM  uint32_t BR7        : 1;            /*!< [23..23] Reset bit 7                                                      */
      __OM  uint32_t BR8        : 1;            /*!< [24..24] Reset bit 8                                                      */
      __OM  uint32_t BR9        : 1;            /*!< [25..25] Reset bit 9                                                      */
      __OM  uint32_t BR10       : 1;            /*!< [26..26] Reset bit 10                                                     */
      __OM  uint32_t BR11       : 1;            /*!< [27..27] Reset bit 11                                                     */
      __OM  uint32_t BR12       : 1;            /*!< [28..28] Reset bit 12                                                     */
      __OM  uint32_t BR13       : 1;            /*!< [29..29] Reset bit 13                                                     */
      __OM  uint32_t BR14       : 1;            /*!< [30..30] Reset bit 14                                                     */
      __OM  uint32_t BR15       : 1;            /*!< [31..31] Reset bit 15                                                     */
    } bit;
  } BSHR;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000014) Port bit reset register (GPIOn_BCR)                        */
    
    struct {
      __OM  uint32_t BR0        : 1;            /*!< [0..0] Reset bit 0                                                        */
      __OM  uint32_t BR1        : 1;            /*!< [1..1] Reset bit 1                                                        */
      __OM  uint32_t BR2        : 1;            /*!< [2..2] Reset bit 1                                                        */
      __OM  uint32_t BR3        : 1;            /*!< [3..3] Reset bit 3                                                        */
      __OM  uint32_t BR4        : 1;            /*!< [4..4] Reset bit 4                                                        */
      __OM  uint32_t BR5        : 1;            /*!< [5..5] Reset bit 5                                                        */
      __OM  uint32_t BR6        : 1;            /*!< [6..6] Reset bit 6                                                        */
      __OM  uint32_t BR7        : 1;            /*!< [7..7] Reset bit 7                                                        */
      __OM  uint32_t BR8        : 1;            /*!< [8..8] Reset bit 8                                                        */
      __OM  uint32_t BR9        : 1;            /*!< [9..9] Reset bit 9                                                        */
      __OM  uint32_t BR10       : 1;            /*!< [10..10] Reset bit 10                                                     */
      __OM  uint32_t BR11       : 1;            /*!< [11..11] Reset bit 11                                                     */
      __OM  uint32_t BR12       : 1;            /*!< [12..12] Reset bit 12                                                     */
      __OM  uint32_t BR13       : 1;            /*!< [13..13] Reset bit 13                                                     */
      __OM  uint32_t BR14       : 1;            /*!< [14..14] Reset bit 14                                                     */
      __OM  uint32_t BR15       : 1;            /*!< [15..15] Reset bit 15                                                     */
    } bit;
  } BCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) Port configuration lock register                           */
    
    struct {
      __IOM uint32_t LCK0       : 1;            /*!< [0..0] Port A Lock bit 0                                                  */
      __IOM uint32_t LCK1       : 1;            /*!< [1..1] Port A Lock bit 1                                                  */
      __IOM uint32_t LCK2       : 1;            /*!< [2..2] Port A Lock bit 2                                                  */
      __IOM uint32_t LCK3       : 1;            /*!< [3..3] Port A Lock bit 3                                                  */
      __IOM uint32_t LCK4       : 1;            /*!< [4..4] Port A Lock bit 4                                                  */
      __IOM uint32_t LCK5       : 1;            /*!< [5..5] Port A Lock bit 5                                                  */
      __IOM uint32_t LCK6       : 1;            /*!< [6..6] Port A Lock bit 6                                                  */
      __IOM uint32_t LCK7       : 1;            /*!< [7..7] Port A Lock bit 7                                                  */
      __IOM uint32_t LCK8       : 1;            /*!< [8..8] Port A Lock bit 8                                                  */
      __IOM uint32_t LCK9       : 1;            /*!< [9..9] Port A Lock bit 9                                                  */
      __IOM uint32_t LCK10      : 1;            /*!< [10..10] Port A Lock bit 10                                               */
      __IOM uint32_t LCK11      : 1;            /*!< [11..11] Port A Lock bit 11                                               */
      __IOM uint32_t LCK12      : 1;            /*!< [12..12] Port A Lock bit 12                                               */
      __IOM uint32_t LCK13      : 1;            /*!< [13..13] Port A Lock bit 13                                               */
      __IOM uint32_t LCK14      : 1;            /*!< [14..14] Port A Lock bit 14                                               */
      __IOM uint32_t LCK15      : 1;            /*!< [15..15] Port A Lock bit 15                                               */
      __IOM uint32_t LCKK       : 1;            /*!< [16..16] Lock key                                                         */
    } bit;
  } LCKR;
} GPIOA_Type;                                   /*!< Size = 28 (0x1c)                                                          */



/* =========================================================================================================================== */
/* ================                                           AFIO                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40010000) AFIO Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Event Control Register (AFIO_ECR)                          */
    
    struct {
      __IOM uint32_t PIN        : 4;            /*!< [3..0] Pin selection                                                      */
      __IOM uint32_t PORT       : 3;            /*!< [6..4] Port selection                                                     */
      __IOM uint32_t EVOE       : 1;            /*!< [7..7] Event Output Enable                                                */
    } bit;
  } ECR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) AF remap and debug I/O configuration register
                                                                    (AFIO_PCFR)                                                */
    
    struct {
      __IOM uint32_t SPI1RM     : 1;            /*!< [0..0] SPI1 remapping                                                     */
      __IOM uint32_t I2C1RM     : 1;            /*!< [1..1] I2C1 remapping                                                     */
      __IOM uint32_t USART1RM   : 1;            /*!< [2..2] USART1 remapping                                                   */
      __IOM uint32_t USART2RM   : 1;            /*!< [3..3] USART2 remapping                                                   */
      __IOM uint32_t USART3RM   : 2;            /*!< [5..4] USART3 remapping                                                   */
      __IOM uint32_t TIM1RM     : 2;            /*!< [7..6] TIM1 remapping                                                     */
      __IOM uint32_t TIM2RM     : 2;            /*!< [9..8] TIM2 remapping                                                     */
      __IOM uint32_t TIM3RM     : 2;            /*!< [11..10] TIM3 remapping                                                   */
      __IOM uint32_t TIM4RM     : 1;            /*!< [12..12] TIM4 remapping                                                   */
      __IOM uint32_t CAN1RM     : 2;            /*!< [14..13] CAN1 remapping                                                   */
      __IOM uint32_t PD01RM     : 1;            /*!< [15..15] Port D0/Port D1 mapping on OSCIN/OSCOUT                          */
      __IOM uint32_t TIM5CH4RM  : 1;            /*!< [16..16] TIM5 channel4 internal remap                                     */
      __IOM uint32_t ADC1_ETRGINJ_RM : 1;       /*!< [17..17] ADC 1 External trigger injected conversion remapping             */
      __IOM uint32_t ADC1_ETRGREG_RM : 1;       /*!< [18..18] ADC 1 external trigger regular conversion remapping              */
      __IOM uint32_t ADC2_ETRGINJ_RM : 1;       /*!< [19..19] ADC 2 External trigger injected conversion remapping             */
      __IOM uint32_t ADC2_ETRGREG_RM : 1;       /*!< [20..20] ADC 2 external trigger regular conversion remapping              */
      __IOM uint32_t ETHRM      : 1;            /*!< [21..21] Ethernet remapping                                               */
      __IOM uint32_t CAN2RM     : 1;            /*!< [22..22] CAN2 remapping                                                   */
      __IOM uint32_t MII_RMII_SEL : 1;          /*!< [23..23] MII_RMII_SEL                                                     */
      __OM  uint32_t SWCFG      : 3;            /*!< [26..24] Serial wire JTAG configuration                                   */
      __IM  uint32_t            : 1;
      __IOM uint32_t SPI3_RM    : 1;            /*!< [28..28] SPI3 remapping                                                   */
      __IOM uint32_t TIM2ITRA_RM : 1;           /*!< [29..29] TIM2 internally triggers 1 remapping                             */
      __IOM uint32_t PTP_PPSP_RM : 1;           /*!< [30..30] Ethernet PTP_PPS remapping                                       */
    } bit;
  } PCFR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) External interrupt configuration register 1 (AFIO_EXTICR1) */
    
    struct {
      __IOM uint32_t EXTI0      : 4;            /*!< [3..0] EXTI0 configuration                                                */
      __IOM uint32_t EXTI1      : 4;            /*!< [7..4] EXTI1 configuration                                                */
      __IOM uint32_t EXTI2      : 4;            /*!< [11..8] EXTI2 configuration                                               */
      __IOM uint32_t EXTI3      : 4;            /*!< [15..12] EXTI3 configuration                                              */
    } bit;
  } EXTICR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) External interrupt configuration register 2 (AFIO_EXTICR2) */
    
    struct {
      __IOM uint32_t EXTI4      : 4;            /*!< [3..0] EXTI4 configuration                                                */
      __IOM uint32_t EXTI5      : 4;            /*!< [7..4] EXTI5 configuration                                                */
      __IOM uint32_t EXTI6      : 4;            /*!< [11..8] EXTI6 configuration                                               */
      __IOM uint32_t EXTI7      : 4;            /*!< [15..12] EXTI7 configuration                                              */
    } bit;
  } EXTICR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) External interrupt configuration register 3 (AFIO_EXTICR3) */
    
    struct {
      __IOM uint32_t EXTI8      : 4;            /*!< [3..0] EXTI8 configuration                                                */
      __IOM uint32_t EXTI9      : 4;            /*!< [7..4] EXTI9 configuration                                                */
      __IOM uint32_t EXTI10     : 4;            /*!< [11..8] EXTI10 configuration                                              */
      __IOM uint32_t EXTI11     : 4;            /*!< [15..12] EXTI11 configuration                                             */
    } bit;
  } EXTICR3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) External interrupt configuration register 4 (AFIO_EXTICR4) */
    
    struct {
      __IOM uint32_t EXTI12     : 4;            /*!< [3..0] EXTI12 configuration                                               */
      __IOM uint32_t EXTI13     : 4;            /*!< [7..4] EXTI13 configuration                                               */
      __IOM uint32_t EXTI14     : 4;            /*!< [11..8] EXTI14 configuration                                              */
      __IOM uint32_t EXTI15     : 4;            /*!< [15..12] EXTI15 configuration                                             */
    } bit;
  } EXTICR4;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) AF remap and debug I/O configuration register
                                                                    (AFIO_PCFR2)                                               */
    
    struct {
      __IM  uint32_t            : 2;
      __IOM uint32_t TIM8_REMAP : 1;            /*!< [2..2] TIM8 remapping                                                     */
      __IOM uint32_t TIM9_REMAP : 2;            /*!< [4..3] TIM9 remapping                                                     */
      __IOM uint32_t TIM10_REMAP : 2;           /*!< [6..5] TIM10 remapping                                                    */
      __IM  uint32_t            : 3;
      __IOM uint32_t FSMC_NADV  : 1;            /*!< [10..10] FSMC_NADV                                                        */
      __IM  uint32_t            : 5;
      __IOM uint32_t UART4_REMAP : 2;           /*!< [17..16] UART4 remapping                                                  */
      __IOM uint32_t UART5_REMAP : 2;           /*!< [19..18] UART5 remapping                                                  */
      __IOM uint32_t UART6_REMAP : 2;           /*!< [21..20] UART6 remapping                                                  */
      __IOM uint32_t UART7_REMAP : 2;           /*!< [23..22] UART7 remapping                                                  */
      __IOM uint32_t UART8_REMAP : 2;           /*!< [25..24] UART8 remapping                                                  */
      __IOM uint32_t UART1_REMAP2 : 1;          /*!< [26..26] UART1 remapping                                                  */
    } bit;
  } PCFR2;
} AFIO_Type;                                    /*!< Size = 32 (0x20)                                                          */



/* =========================================================================================================================== */
/* ================                                           EXTI                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40010400) EXTI Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Interrupt mask register (EXTI_INTENR)                      */
    
    struct {
      __IOM uint32_t MR0        : 1;            /*!< [0..0] Interrupt Mask on line 0                                           */
      __IOM uint32_t MR1        : 1;            /*!< [1..1] Interrupt Mask on line 1                                           */
      __IOM uint32_t MR2        : 1;            /*!< [2..2] Interrupt Mask on line 2                                           */
      __IOM uint32_t MR3        : 1;            /*!< [3..3] Interrupt Mask on line 3                                           */
      __IOM uint32_t MR4        : 1;            /*!< [4..4] Interrupt Mask on line 4                                           */
      __IOM uint32_t MR5        : 1;            /*!< [5..5] Interrupt Mask on line 5                                           */
      __IOM uint32_t MR6        : 1;            /*!< [6..6] Interrupt Mask on line 6                                           */
      __IOM uint32_t MR7        : 1;            /*!< [7..7] Interrupt Mask on line 7                                           */
      __IOM uint32_t MR8        : 1;            /*!< [8..8] Interrupt Mask on line 8                                           */
      __IOM uint32_t MR9        : 1;            /*!< [9..9] Interrupt Mask on line 9                                           */
      __IOM uint32_t MR10       : 1;            /*!< [10..10] Interrupt Mask on line 10                                        */
      __IOM uint32_t MR11       : 1;            /*!< [11..11] Interrupt Mask on line 11                                        */
      __IOM uint32_t MR12       : 1;            /*!< [12..12] Interrupt Mask on line 12                                        */
      __IOM uint32_t MR13       : 1;            /*!< [13..13] Interrupt Mask on line 13                                        */
      __IOM uint32_t MR14       : 1;            /*!< [14..14] Interrupt Mask on line 14                                        */
      __IOM uint32_t MR15       : 1;            /*!< [15..15] Interrupt Mask on line 15                                        */
      __IOM uint32_t MR16       : 1;            /*!< [16..16] Interrupt Mask on line 16                                        */
      __IOM uint32_t MR17       : 1;            /*!< [17..17] Interrupt Mask on line 17                                        */
      __IOM uint32_t MR18       : 1;            /*!< [18..18] Interrupt Mask on line 18                                        */
      __IOM uint32_t MR19       : 1;            /*!< [19..19] Interrupt Mask on line 19                                        */
    } bit;
  } INTENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Event mask register (EXTI_EVENR)                           */
    
    struct {
      __IOM uint32_t MR0        : 1;            /*!< [0..0] Event Mask on line 0                                               */
      __IOM uint32_t MR1        : 1;            /*!< [1..1] Event Mask on line 1                                               */
      __IOM uint32_t MR2        : 1;            /*!< [2..2] Event Mask on line 2                                               */
      __IOM uint32_t MR3        : 1;            /*!< [3..3] Event Mask on line 3                                               */
      __IOM uint32_t MR4        : 1;            /*!< [4..4] Event Mask on line 4                                               */
      __IOM uint32_t MR5        : 1;            /*!< [5..5] Event Mask on line 5                                               */
      __IOM uint32_t MR6        : 1;            /*!< [6..6] Event Mask on line 6                                               */
      __IOM uint32_t MR7        : 1;            /*!< [7..7] Event Mask on line 7                                               */
      __IOM uint32_t MR8        : 1;            /*!< [8..8] Event Mask on line 8                                               */
      __IOM uint32_t MR9        : 1;            /*!< [9..9] Event Mask on line 9                                               */
      __IOM uint32_t MR10       : 1;            /*!< [10..10] Event Mask on line 10                                            */
      __IOM uint32_t MR11       : 1;            /*!< [11..11] Event Mask on line 11                                            */
      __IOM uint32_t MR12       : 1;            /*!< [12..12] Event Mask on line 12                                            */
      __IOM uint32_t MR13       : 1;            /*!< [13..13] Event Mask on line 13                                            */
      __IOM uint32_t MR14       : 1;            /*!< [14..14] Event Mask on line 14                                            */
      __IOM uint32_t MR15       : 1;            /*!< [15..15] Event Mask on line 15                                            */
      __IOM uint32_t MR16       : 1;            /*!< [16..16] Event Mask on line 16                                            */
      __IOM uint32_t MR17       : 1;            /*!< [17..17] Event Mask on line 17                                            */
      __IOM uint32_t MR18       : 1;            /*!< [18..18] Event Mask on line 18                                            */
      __IOM uint32_t MR19       : 1;            /*!< [19..19] Event Mask on line 19                                            */
    } bit;
  } EVENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Rising Trigger selection register (EXTI_RTENR)             */
    
    struct {
      __IOM uint32_t TR0        : 1;            /*!< [0..0] Rising trigger event configuration of line 0                       */
      __IOM uint32_t TR1        : 1;            /*!< [1..1] Rising trigger event configuration of line 1                       */
      __IOM uint32_t TR2        : 1;            /*!< [2..2] Rising trigger event configuration of line 2                       */
      __IOM uint32_t TR3        : 1;            /*!< [3..3] Rising trigger event configuration of line 3                       */
      __IOM uint32_t TR4        : 1;            /*!< [4..4] Rising trigger event configuration of line 4                       */
      __IOM uint32_t TR5        : 1;            /*!< [5..5] Rising trigger event configuration of line 5                       */
      __IOM uint32_t TR6        : 1;            /*!< [6..6] Rising trigger event configuration of line 6                       */
      __IOM uint32_t TR7        : 1;            /*!< [7..7] Rising trigger event configuration of line 7                       */
      __IOM uint32_t TR8        : 1;            /*!< [8..8] Rising trigger event configuration of line 8                       */
      __IOM uint32_t TR9        : 1;            /*!< [9..9] Rising trigger event configuration of line 9                       */
      __IOM uint32_t TR10       : 1;            /*!< [10..10] Rising trigger event configuration of line 10                    */
      __IOM uint32_t TR11       : 1;            /*!< [11..11] Rising trigger event configuration of line 11                    */
      __IOM uint32_t TR12       : 1;            /*!< [12..12] Rising trigger event configuration of line 12                    */
      __IOM uint32_t TR13       : 1;            /*!< [13..13] Rising trigger event configuration of line 13                    */
      __IOM uint32_t TR14       : 1;            /*!< [14..14] Rising trigger event configuration of line 14                    */
      __IOM uint32_t TR15       : 1;            /*!< [15..15] Rising trigger event configuration of line 15                    */
      __IOM uint32_t TR16       : 1;            /*!< [16..16] Rising trigger event configuration of line 16                    */
      __IOM uint32_t TR17       : 1;            /*!< [17..17] Rising trigger event configuration of line 17                    */
      __IOM uint32_t TR18       : 1;            /*!< [18..18] Rising trigger event configuration of line 18                    */
      __IOM uint32_t TR19       : 1;            /*!< [19..19] Rising trigger event configuration of line 19                    */
    } bit;
  } RTENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Falling Trigger selection register (EXTI_FTENR)            */
    
    struct {
      __IOM uint32_t TR0        : 1;            /*!< [0..0] Falling trigger event configuration of line 0                      */
      __IOM uint32_t TR1        : 1;            /*!< [1..1] Falling trigger event configuration of line 1                      */
      __IOM uint32_t TR2        : 1;            /*!< [2..2] Falling trigger event configuration of line 2                      */
      __IOM uint32_t TR3        : 1;            /*!< [3..3] Falling trigger event configuration of line 3                      */
      __IOM uint32_t TR4        : 1;            /*!< [4..4] Falling trigger event configuration of line 4                      */
      __IOM uint32_t TR5        : 1;            /*!< [5..5] Falling trigger event configuration of line 5                      */
      __IOM uint32_t TR6        : 1;            /*!< [6..6] Falling trigger event configuration of line 6                      */
      __IOM uint32_t TR7        : 1;            /*!< [7..7] Falling trigger event configuration of line 7                      */
      __IOM uint32_t TR8        : 1;            /*!< [8..8] Falling trigger event configuration of line 8                      */
      __IOM uint32_t TR9        : 1;            /*!< [9..9] Falling trigger event configuration of line 9                      */
      __IOM uint32_t TR10       : 1;            /*!< [10..10] Falling trigger event configuration of line 10                   */
      __IOM uint32_t TR11       : 1;            /*!< [11..11] Falling trigger event configuration of line 11                   */
      __IOM uint32_t TR12       : 1;            /*!< [12..12] Falling trigger event configuration of line 12                   */
      __IOM uint32_t TR13       : 1;            /*!< [13..13] Falling trigger event configuration of line 13                   */
      __IOM uint32_t TR14       : 1;            /*!< [14..14] Falling trigger event configuration of line 14                   */
      __IOM uint32_t TR15       : 1;            /*!< [15..15] Falling trigger event configuration of line 15                   */
      __IOM uint32_t TR16       : 1;            /*!< [16..16] Falling trigger event configuration of line 16                   */
      __IOM uint32_t TR17       : 1;            /*!< [17..17] Falling trigger event configuration of line 17                   */
      __IOM uint32_t TR18       : 1;            /*!< [18..18] Falling trigger event configuration of line 18                   */
      __IOM uint32_t TR19       : 1;            /*!< [19..19] Falling trigger event configuration of line 19                   */
    } bit;
  } FTENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) Software interrupt event register (EXTI_SWIEVR)            */
    
    struct {
      __IOM uint32_t SWIER0     : 1;            /*!< [0..0] Software Interrupt on line 0                                       */
      __IOM uint32_t SWIER1     : 1;            /*!< [1..1] Software Interrupt on line 1                                       */
      __IOM uint32_t SWIER2     : 1;            /*!< [2..2] Software Interrupt on line 2                                       */
      __IOM uint32_t SWIER3     : 1;            /*!< [3..3] Software Interrupt on line 3                                       */
      __IOM uint32_t SWIER4     : 1;            /*!< [4..4] Software Interrupt on line 4                                       */
      __IOM uint32_t SWIER5     : 1;            /*!< [5..5] Software Interrupt on line 5                                       */
      __IOM uint32_t SWIER6     : 1;            /*!< [6..6] Software Interrupt on line 6                                       */
      __IOM uint32_t SWIER7     : 1;            /*!< [7..7] Software Interrupt on line 7                                       */
      __IOM uint32_t SWIER8     : 1;            /*!< [8..8] Software Interrupt on line 8                                       */
      __IOM uint32_t SWIER9     : 1;            /*!< [9..9] Software Interrupt on line 9                                       */
      __IOM uint32_t SWIER10    : 1;            /*!< [10..10] Software Interrupt on line 10                                    */
      __IOM uint32_t SWIER11    : 1;            /*!< [11..11] Software Interrupt on line 11                                    */
      __IOM uint32_t SWIER12    : 1;            /*!< [12..12] Software Interrupt on line 12                                    */
      __IOM uint32_t SWIER13    : 1;            /*!< [13..13] Software Interrupt on line 13                                    */
      __IOM uint32_t SWIER14    : 1;            /*!< [14..14] Software Interrupt on line 14                                    */
      __IOM uint32_t SWIER15    : 1;            /*!< [15..15] Software Interrupt on line 15                                    */
      __IOM uint32_t SWIER16    : 1;            /*!< [16..16] Software Interrupt on line 16                                    */
      __IOM uint32_t SWIER17    : 1;            /*!< [17..17] Software Interrupt on line 17                                    */
      __IOM uint32_t SWIER18    : 1;            /*!< [18..18] Software Interrupt on line 18                                    */
      __IOM uint32_t SWIER19    : 1;            /*!< [19..19] Software Interrupt on line 19                                    */
    } bit;
  } SWIEVR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Pending register (EXTI_INTFR)                              */
    
    struct {
      __IOM uint32_t PR0        : 1;            /*!< [0..0] Pending bit 0                                                      */
      __IOM uint32_t PR1        : 1;            /*!< [1..1] Pending bit 1                                                      */
      __IOM uint32_t PR2        : 1;            /*!< [2..2] Pending bit 2                                                      */
      __IOM uint32_t PR3        : 1;            /*!< [3..3] Pending bit 3                                                      */
      __IOM uint32_t PR4        : 1;            /*!< [4..4] Pending bit 4                                                      */
      __IOM uint32_t PR5        : 1;            /*!< [5..5] Pending bit 5                                                      */
      __IOM uint32_t PR6        : 1;            /*!< [6..6] Pending bit 6                                                      */
      __IOM uint32_t PR7        : 1;            /*!< [7..7] Pending bit 7                                                      */
      __IOM uint32_t PR8        : 1;            /*!< [8..8] Pending bit 8                                                      */
      __IOM uint32_t PR9        : 1;            /*!< [9..9] Pending bit 9                                                      */
      __IOM uint32_t PR10       : 1;            /*!< [10..10] Pending bit 10                                                   */
      __IOM uint32_t PR11       : 1;            /*!< [11..11] Pending bit 11                                                   */
      __IOM uint32_t PR12       : 1;            /*!< [12..12] Pending bit 12                                                   */
      __IOM uint32_t PR13       : 1;            /*!< [13..13] Pending bit 13                                                   */
      __IOM uint32_t PR14       : 1;            /*!< [14..14] Pending bit 14                                                   */
      __IOM uint32_t PR15       : 1;            /*!< [15..15] Pending bit 15                                                   */
      __IOM uint32_t PR16       : 1;            /*!< [16..16] Pending bit 16                                                   */
      __IOM uint32_t PR17       : 1;            /*!< [17..17] Pending bit 17                                                   */
      __IOM uint32_t PR18       : 1;            /*!< [18..18] Pending bit 18                                                   */
      __IOM uint32_t PR19       : 1;            /*!< [19..19] Pending bit 19                                                   */
    } bit;
  } INTFR;
} EXTI_Type;                                    /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                           DMA1                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40020000) DMA1 Structure                                             */
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000000) DMA interrupt status register (DMA_INTFR)                  */
    
    struct {
      __IM  uint32_t GIF1       : 1;            /*!< [0..0] Channel 1 Global interrupt flag                                    */
      __IM  uint32_t TCIF1      : 1;            /*!< [1..1] Channel 1 Transfer Complete flag                                   */
      __IM  uint32_t HTIF1      : 1;            /*!< [2..2] Channel 1 Half Transfer Complete flag                              */
      __IM  uint32_t TEIF1      : 1;            /*!< [3..3] Channel 1 Transfer Error flag                                      */
      __IM  uint32_t GIF2       : 1;            /*!< [4..4] Channel 2 Global interrupt flag                                    */
      __IM  uint32_t TCIF2      : 1;            /*!< [5..5] Channel 2 Transfer Complete flag                                   */
      __IM  uint32_t HTIF2      : 1;            /*!< [6..6] Channel 2 Half Transfer Complete flag                              */
      __IM  uint32_t TEIF2      : 1;            /*!< [7..7] Channel 2 Transfer Error flag                                      */
      __IM  uint32_t GIF3       : 1;            /*!< [8..8] Channel 3 Global interrupt flag                                    */
      __IM  uint32_t TCIF3      : 1;            /*!< [9..9] Channel 3 Transfer Complete flag                                   */
      __IM  uint32_t HTIF3      : 1;            /*!< [10..10] Channel 3 Half Transfer Complete flag                            */
      __IM  uint32_t TEIF3      : 1;            /*!< [11..11] Channel 3 Transfer Error flag                                    */
      __IM  uint32_t GIF4       : 1;            /*!< [12..12] Channel 4 Global interrupt flag                                  */
      __IM  uint32_t TCIF4      : 1;            /*!< [13..13] Channel 4 Transfer Complete flag                                 */
      __IM  uint32_t HTIF4      : 1;            /*!< [14..14] Channel 4 Half Transfer Complete flag                            */
      __IM  uint32_t TEIF4      : 1;            /*!< [15..15] Channel 4 Transfer Error flag                                    */
      __IM  uint32_t GIF5       : 1;            /*!< [16..16] Channel 5 Global interrupt flag                                  */
      __IM  uint32_t TCIF5      : 1;            /*!< [17..17] Channel 5 Transfer Complete flag                                 */
      __IM  uint32_t HTIF5      : 1;            /*!< [18..18] Channel 5 Half Transfer Complete flag                            */
      __IM  uint32_t TEIF5      : 1;            /*!< [19..19] Channel 5 Transfer Error flag                                    */
      __IM  uint32_t GIF6       : 1;            /*!< [20..20] Channel 6 Global interrupt flag                                  */
      __IM  uint32_t TCIF6      : 1;            /*!< [21..21] Channel 6 Transfer Complete flag                                 */
      __IM  uint32_t HTIF6      : 1;            /*!< [22..22] Channel 6 Half Transfer Complete flag                            */
      __IM  uint32_t TEIF6      : 1;            /*!< [23..23] Channel 6 Transfer Error flag                                    */
      __IM  uint32_t GIF7       : 1;            /*!< [24..24] Channel 7 Global interrupt flag                                  */
      __IM  uint32_t TCIF7      : 1;            /*!< [25..25] Channel 7 Transfer Complete flag                                 */
      __IM  uint32_t HTIF7      : 1;            /*!< [26..26] Channel 7 Half Transfer Complete flag                            */
      __IM  uint32_t TEIF7      : 1;            /*!< [27..27] Channel 7 Transfer Error flag                                    */
    } bit;
  } INTFR;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000004) DMA interrupt flag clear register (DMA_INTFCR)             */
    
    struct {
      __OM  uint32_t CGIF1      : 1;            /*!< [0..0] Channel 1 Global interrupt clear                                   */
      __OM  uint32_t CTCIF1     : 1;            /*!< [1..1] Channel 1 Transfer Complete clear                                  */
      __OM  uint32_t CHTIF1     : 1;            /*!< [2..2] Channel 1 Half Transfer clear                                      */
      __OM  uint32_t CTEIF1     : 1;            /*!< [3..3] Channel 1 Transfer Error clear                                     */
      __OM  uint32_t CGIF2      : 1;            /*!< [4..4] Channel 2 Global interrupt clear                                   */
      __OM  uint32_t CTCIF2     : 1;            /*!< [5..5] Channel 2 Transfer Complete clear                                  */
      __OM  uint32_t CHTIF2     : 1;            /*!< [6..6] Channel 2 Half Transfer clear                                      */
      __OM  uint32_t CTEIF2     : 1;            /*!< [7..7] Channel 2 Transfer Error clear                                     */
      __OM  uint32_t CGIF3      : 1;            /*!< [8..8] Channel 3 Global interrupt clear                                   */
      __OM  uint32_t CTCIF3     : 1;            /*!< [9..9] Channel 3 Transfer Complete clear                                  */
      __OM  uint32_t CHTIF3     : 1;            /*!< [10..10] Channel 3 Half Transfer clear                                    */
      __OM  uint32_t CTEIF3     : 1;            /*!< [11..11] Channel 3 Transfer Error clear                                   */
      __OM  uint32_t CGIF4      : 1;            /*!< [12..12] Channel 4 Global interrupt clear                                 */
      __OM  uint32_t CTCIF4     : 1;            /*!< [13..13] Channel 4 Transfer Complete clear                                */
      __OM  uint32_t CHTIF4     : 1;            /*!< [14..14] Channel 4 Half Transfer clear                                    */
      __OM  uint32_t CTEIF4     : 1;            /*!< [15..15] Channel 4 Transfer Error clear                                   */
      __OM  uint32_t CGIF5      : 1;            /*!< [16..16] Channel 5 Global interrupt clear                                 */
      __OM  uint32_t CTCIF5     : 1;            /*!< [17..17] Channel 5 Transfer Complete clear                                */
      __OM  uint32_t CHTIF5     : 1;            /*!< [18..18] Channel 5 Half Transfer clear                                    */
      __OM  uint32_t CTEIF5     : 1;            /*!< [19..19] Channel 5 Transfer Error clear                                   */
      __OM  uint32_t CGIF6      : 1;            /*!< [20..20] Channel 6 Global interrupt clear                                 */
      __OM  uint32_t CTCIF6     : 1;            /*!< [21..21] Channel 6 Transfer Complete clear                                */
      __OM  uint32_t CHTIF6     : 1;            /*!< [22..22] Channel 6 Half Transfer clear                                    */
      __OM  uint32_t CTEIF6     : 1;            /*!< [23..23] Channel 6 Transfer Error clear                                   */
      __OM  uint32_t CGIF7      : 1;            /*!< [24..24] Channel 7 Global interrupt clear                                 */
      __OM  uint32_t CTCIF7     : 1;            /*!< [25..25] Channel 7 Transfer Complete clear                                */
      __OM  uint32_t CHTIF7     : 1;            /*!< [26..26] Channel 7 Half Transfer clear                                    */
      __OM  uint32_t CTEIF7     : 1;            /*!< [27..27] Channel 7 Transfer Error clear                                   */
    } bit;
  } INTFCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) DMA channel 1 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) DMA channel 1 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) DMA channel 1 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR1;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) DMA channel 2 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) DMA channel 2 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) DMA channel 2 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR2;
  __IM  uint32_t  RESERVED1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) DMA channel 3 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) DMA channel 3 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000003C) DMA channel 3 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR3;
  __IM  uint32_t  RESERVED2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000044) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) DMA channel 4 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) DMA channel 4 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000050) DMA channel 4 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR4;
  __IM  uint32_t  RESERVED3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000058) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR5;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000005C) DMA channel 5 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR5;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000060) DMA channel 5 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR5;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000064) DMA channel 5 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR5;
  __IM  uint32_t  RESERVED4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000006C) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR6;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000070) DMA channel 6 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR6;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000074) DMA channel 6 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR6;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000078) DMA channel 6 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR6;
  __IM  uint32_t  RESERVED5;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000080) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR7;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000084) DMA channel 7 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR7;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000088) DMA channel 7 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR7;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000008C) DMA channel 7 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR7;
} DMA1_Type;                                    /*!< Size = 144 (0x90)                                                         */



/* =========================================================================================================================== */
/* ================                                           DMA2                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40020400) DMA2 Structure                                             */
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000000) DMA interrupt status register (DMA_INTFR)                  */
    
    struct {
      __IM  uint32_t GIF1       : 1;            /*!< [0..0] Channel 1 Global interrupt flag                                    */
      __IM  uint32_t TCIF1      : 1;            /*!< [1..1] Channel 1 Transfer Complete flag                                   */
      __IM  uint32_t HTIF1      : 1;            /*!< [2..2] Channel 1 Half Transfer Complete flag                              */
      __IM  uint32_t TEIF1      : 1;            /*!< [3..3] Channel 1 Transfer Error flag                                      */
      __IM  uint32_t GIF2       : 1;            /*!< [4..4] Channel 2 Global interrupt flag                                    */
      __IM  uint32_t TCIF2      : 1;            /*!< [5..5] Channel 2 Transfer Complete flag                                   */
      __IM  uint32_t HTIF2      : 1;            /*!< [6..6] Channel 2 Half Transfer Complete flag                              */
      __IM  uint32_t TEIF2      : 1;            /*!< [7..7] Channel 2 Transfer Error flag                                      */
      __IM  uint32_t GIF3       : 1;            /*!< [8..8] Channel 3 Global interrupt flag                                    */
      __IM  uint32_t TCIF3      : 1;            /*!< [9..9] Channel 3 Transfer Complete flag                                   */
      __IM  uint32_t HTIF3      : 1;            /*!< [10..10] Channel 3 Half Transfer Complete flag                            */
      __IM  uint32_t TEIF3      : 1;            /*!< [11..11] Channel 3 Transfer Error flag                                    */
      __IM  uint32_t GIF4       : 1;            /*!< [12..12] Channel 4 Global interrupt flag                                  */
      __IM  uint32_t TCIF4      : 1;            /*!< [13..13] Channel 4 Transfer Complete flag                                 */
      __IM  uint32_t HTIF4      : 1;            /*!< [14..14] Channel 4 Half Transfer Complete flag                            */
      __IM  uint32_t TEIF4      : 1;            /*!< [15..15] Channel 4 Transfer Error flag                                    */
      __IM  uint32_t GIF5       : 1;            /*!< [16..16] Channel 5 Global interrupt flag                                  */
      __IM  uint32_t TCIF5      : 1;            /*!< [17..17] Channel 5 Transfer Complete flag                                 */
      __IM  uint32_t HTIF5      : 1;            /*!< [18..18] Channel 5 Half Transfer Complete flag                            */
      __IM  uint32_t TEIF5      : 1;            /*!< [19..19] Channel 5 Transfer Error flag                                    */
      __IM  uint32_t GIF6       : 1;            /*!< [20..20] Channel 6 Global interrupt flag                                  */
      __IM  uint32_t TCIF6      : 1;            /*!< [21..21] Channel 6 Transfer Complete flag                                 */
      __IM  uint32_t HTIF6      : 1;            /*!< [22..22] Channel 6 Half Transfer Complete flag                            */
      __IM  uint32_t TEIF6      : 1;            /*!< [23..23] Channel 6 Transfer Error flag                                    */
      __IM  uint32_t GIF7       : 1;            /*!< [24..24] Channel 7 Global interrupt flag                                  */
      __IM  uint32_t TCIF7      : 1;            /*!< [25..25] Channel 7 Transfer Complete flag                                 */
      __IM  uint32_t HTIF7      : 1;            /*!< [26..26] Channel 7 Half Transfer Complete flag                            */
      __IM  uint32_t TEIF7      : 1;            /*!< [27..27] Channel 7 Transfer Error flag                                    */
    } bit;
  } INTFR;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000004) DMA interrupt flag clear register (DMA_INTFCR)             */
    
    struct {
      __OM  uint32_t CGIF1      : 1;            /*!< [0..0] Channel 1 Global interrupt clear                                   */
      __OM  uint32_t CTCIF1     : 1;            /*!< [1..1] Channel 1 Transfer Complete clear                                  */
      __OM  uint32_t CHTIF1     : 1;            /*!< [2..2] Channel 1 Half Transfer clear                                      */
      __OM  uint32_t CTEIF1     : 1;            /*!< [3..3] Channel 1 Transfer Error clear                                     */
      __OM  uint32_t CGIF2      : 1;            /*!< [4..4] Channel 2 Global interrupt clear                                   */
      __OM  uint32_t CTCIF2     : 1;            /*!< [5..5] Channel 2 Transfer Complete clear                                  */
      __OM  uint32_t CHTIF2     : 1;            /*!< [6..6] Channel 2 Half Transfer clear                                      */
      __OM  uint32_t CTEIF2     : 1;            /*!< [7..7] Channel 2 Transfer Error clear                                     */
      __OM  uint32_t CGIF3      : 1;            /*!< [8..8] Channel 3 Global interrupt clear                                   */
      __OM  uint32_t CTCIF3     : 1;            /*!< [9..9] Channel 3 Transfer Complete clear                                  */
      __OM  uint32_t CHTIF3     : 1;            /*!< [10..10] Channel 3 Half Transfer clear                                    */
      __OM  uint32_t CTEIF3     : 1;            /*!< [11..11] Channel 3 Transfer Error clear                                   */
      __OM  uint32_t CGIF4      : 1;            /*!< [12..12] Channel 4 Global interrupt clear                                 */
      __OM  uint32_t CTCIF4     : 1;            /*!< [13..13] Channel 4 Transfer Complete clear                                */
      __OM  uint32_t CHTIF4     : 1;            /*!< [14..14] Channel 4 Half Transfer clear                                    */
      __OM  uint32_t CTEIF4     : 1;            /*!< [15..15] Channel 4 Transfer Error clear                                   */
      __OM  uint32_t CGIF5      : 1;            /*!< [16..16] Channel 5 Global interrupt clear                                 */
      __OM  uint32_t CTCIF5     : 1;            /*!< [17..17] Channel 5 Transfer Complete clear                                */
      __OM  uint32_t CHTIF5     : 1;            /*!< [18..18] Channel 5 Half Transfer clear                                    */
      __OM  uint32_t CTEIF5     : 1;            /*!< [19..19] Channel 5 Transfer Error clear                                   */
      __OM  uint32_t CGIF6      : 1;            /*!< [20..20] Channel 6 Global interrupt clear                                 */
      __OM  uint32_t CTCIF6     : 1;            /*!< [21..21] Channel 6 Transfer Complete clear                                */
      __OM  uint32_t CHTIF6     : 1;            /*!< [22..22] Channel 6 Half Transfer clear                                    */
      __OM  uint32_t CTEIF6     : 1;            /*!< [23..23] Channel 6 Transfer Error clear                                   */
      __OM  uint32_t CGIF7      : 1;            /*!< [24..24] Channel 7 Global interrupt clear                                 */
      __OM  uint32_t CTCIF7     : 1;            /*!< [25..25] Channel 7 Transfer Complete clear                                */
      __OM  uint32_t CHTIF7     : 1;            /*!< [26..26] Channel 7 Half Transfer clear                                    */
      __OM  uint32_t CTEIF7     : 1;            /*!< [27..27] Channel 7 Transfer Error clear                                   */
    } bit;
  } INTFCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) DMA channel 1 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) DMA channel 1 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) DMA channel 1 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR1;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) DMA channel 2 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) DMA channel 2 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) DMA channel 2 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR2;
  __IM  uint32_t  RESERVED1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) DMA channel 3 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) DMA channel 3 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000003C) DMA channel 3 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR3;
  __IM  uint32_t  RESERVED2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000044) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) DMA channel 4 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) DMA channel 4 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000050) DMA channel 4 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR4;
  __IM  uint32_t  RESERVED3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000058) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR5;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000005C) DMA channel 5 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR5;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000060) DMA channel 5 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR5;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000064) DMA channel 5 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR5;
  __IM  uint32_t  RESERVED4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000006C) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR6;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000070) DMA channel 6 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR6;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000074) DMA channel 6 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR6;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000078) DMA channel 6 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR6;
  __IM  uint32_t  RESERVED5;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000080) DMA channel configuration register (DMA_CFGR)              */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR7;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000084) DMA channel 7 number of data register                      */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR7;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000088) DMA channel 7 peripheral address register                  */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR7;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000008C) DMA channel 7 memory address register                      */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR7;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000090) DMA channel configuration register (DMA_CFGR)
                                                                    used in ch32v30x_D8/D8C                                    */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR8;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000094) DMA channel 8 number of data register used in
                                                                    ch32v30x_D8/D8C                                            */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR8;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000098) DMA channel 8 peripheral address register used
                                                                    in ch32v30x_D8/D8C                                         */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR8;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000009C) DMA channel 8 memory address register used in
                                                                    ch32v30x_D8/D8C                                            */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR8;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000A0) DMA channel configuration register (DMA_CFGR)
                                                                    used in ch32v30x_D8/D8C                                    */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR9;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000A4) DMA channel 9 number of data register used in
                                                                    ch32v30x_D8/D8C                                            */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR9;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000A8) DMA channel 7 peripheral address register used
                                                                    in ch32v30x_D8/D8C                                         */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR9;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000AC) DMA channel 9 memory address register used in
                                                                    ch32v30x_D8/D8C                                            */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR9;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000B0) DMA channel configuration register (DMA_CFGR)
                                                                    used in ch32v30x_D8/D8C                                    */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR10;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000B4) DMA channel 10 number of data register used in
                                                                    ch32v30x_D8/D8C                                            */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR10;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000B8) DMA channel 10 peripheral address register used
                                                                    in ch32v30x_D8/D8C                                         */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR10;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000BC) DMA channel 10 memory address register used in
                                                                    ch32v30x_D8/D8C                                            */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR10;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000C0) DMA channel configuration register (DMA_CFGR)
                                                                    used in ch32v30x_D8/D8C                                    */
    
    struct {
      __IOM uint32_t EN         : 1;            /*!< [0..0] Channel enable                                                     */
      __IOM uint32_t TCIE       : 1;            /*!< [1..1] Transfer complete interrupt enable                                 */
      __IOM uint32_t HTIE       : 1;            /*!< [2..2] Half Transfer interrupt enable                                     */
      __IOM uint32_t TEIE       : 1;            /*!< [3..3] Transfer error interrupt enable                                    */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Data transfer direction                                            */
      __IOM uint32_t CIRC       : 1;            /*!< [5..5] Circular mode                                                      */
      __IOM uint32_t PINC       : 1;            /*!< [6..6] Peripheral increment mode                                          */
      __IOM uint32_t MINC       : 1;            /*!< [7..7] Memory increment mode                                              */
      __IOM uint32_t PSIZE      : 2;            /*!< [9..8] Peripheral size                                                    */
      __IOM uint32_t MSIZE      : 2;            /*!< [11..10] Memory size                                                      */
      __IOM uint32_t PL         : 2;            /*!< [13..12] Channel Priority level                                           */
      __IOM uint32_t MEM2MEM    : 1;            /*!< [14..14] Memory to memory mode                                            */
    } bit;
  } CFGR11;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000C4) DMA channel 11 number of data register used in
                                                                    ch32v30x_D8/D8C                                            */
    
    struct {
      __IOM uint32_t NDT        : 16;           /*!< [15..0] Number of data to transfer                                        */
    } bit;
  } CNTR11;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000C8) DMA channel 11 peripheral address register used
                                                                    in ch32v30x_D8/D8C                                         */
    
    struct {
      __IOM uint32_t PA         : 32;           /*!< [31..0] Peripheral address                                                */
    } bit;
  } PADDR11;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000CC) DMA channel 11 memory address register used in
                                                                    ch32v30x_D8/D8C                                            */
    
    struct {
      __IOM uint32_t MA         : 32;           /*!< [31..0] Memory address                                                    */
    } bit;
  } MADDR11;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x000000D0) DMA2 EXTEN interrupt status register (DMA_INTFR)used
                                                                    in ch32v30x_D8/D8C                                         */
    
    struct {
      __IM  uint32_t GIF8       : 1;            /*!< [0..0] Channel 8 Global interrupt flag                                    */
      __IM  uint32_t TCIF8      : 1;            /*!< [1..1] Channel 8 Transfer Complete flag                                   */
      __IM  uint32_t HTIF8      : 1;            /*!< [2..2] Channel 8 Half Transfer Complete flag                              */
      __IM  uint32_t TEIF8      : 1;            /*!< [3..3] Channel 8 Transfer Error flag                                      */
      __IM  uint32_t GIF9       : 1;            /*!< [4..4] Channel 9 Global interrupt flag                                    */
      __IM  uint32_t TCIF9      : 1;            /*!< [5..5] Channel 9 Transfer Complete flag                                   */
      __IM  uint32_t HTIF9      : 1;            /*!< [6..6] Channel 9 Half Transfer Complete flag                              */
      __IM  uint32_t TEIF9      : 1;            /*!< [7..7] Channel 9 Transfer Error flag                                      */
      __IM  uint32_t GIF10      : 1;            /*!< [8..8] Channel 10 Global interrupt flag                                   */
      __IM  uint32_t TCIF10     : 1;            /*!< [9..9] Channel 10 Transfer Complete flag                                  */
      __IM  uint32_t HTIF10     : 1;            /*!< [10..10] Channel 10 Half Transfer Complete flag                           */
      __IM  uint32_t TEIF10     : 1;            /*!< [11..11] Channel 10 Transfer Error flag                                   */
      __IM  uint32_t GIF11      : 1;            /*!< [12..12] Channel 11 Global interrupt flag                                 */
      __IM  uint32_t TCIF11     : 1;            /*!< [13..13] Channel 11 Transfer Complete flag                                */
      __IM  uint32_t HTIF11     : 1;            /*!< [14..14] Channel 11 Half Transfer Complete flag                           */
      __IM  uint32_t TEIF11     : 1;            /*!< [15..15] Channel 11 Transfer Error flag                                   */
    } bit;
  } EXTEN_INTFR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000D4) DMA2 EXTEN interrupt flag clear register (DMA_INTFCR)used
                                                                    in ch32v30x_D8/D8C                                         */
    
    struct {
      __IOM uint32_t CGIF8      : 1;            /*!< [0..0] Channel 8 Global interrupt clear                                   */
      __IOM uint32_t CTCIF8     : 1;            /*!< [1..1] Channel 8 Global interrupt clear                                   */
      __IOM uint32_t CHTIF8     : 1;            /*!< [2..2] Channel 8 Global interrupt clear                                   */
      __IOM uint32_t CTEIF8     : 1;            /*!< [3..3] Channel 8 Global interrupt clear                                   */
      __IOM uint32_t CGIF9      : 1;            /*!< [4..4] Channel 9 Global interrupt clear                                   */
      __IOM uint32_t CTCIF9     : 1;            /*!< [5..5] Channel 9 Global interrupt clear                                   */
      __IOM uint32_t CHTIF9     : 1;            /*!< [6..6] Channel 9 Global interrupt clear                                   */
      __IOM uint32_t CTEIF9     : 1;            /*!< [7..7] Channel 9 Global interrupt clear                                   */
      __IOM uint32_t CGIF10     : 1;            /*!< [8..8] Channel 10 Global interrupt clear                                  */
      __IOM uint32_t CTCIF10    : 1;            /*!< [9..9] Channel 10 Global interrupt clear                                  */
      __IOM uint32_t CHTIF10    : 1;            /*!< [10..10] Channel 10 Global interrupt clear                                */
      __IOM uint32_t CTEIF10    : 1;            /*!< [11..11] Channel 10 Global interrupt clear                                */
      __IOM uint32_t CGIF11     : 1;            /*!< [12..12] Channel 11 Global interrupt clear                                */
      __IOM uint32_t CTCIF11    : 1;            /*!< [13..13] Channel 11 Global interrupt clear                                */
      __IOM uint32_t CHTIF11    : 1;            /*!< [14..14] Channel 11 Global interrupt clear                                */
      __IOM uint32_t CTEIF11    : 1;            /*!< [15..15] Channel 11 Global interrupt clear                                */
    } bit;
  } EXTEN_INTFCR;
} DMA2_Type;                                    /*!< Size = 216 (0xd8)                                                         */



/* =========================================================================================================================== */
/* ================                                            RTC                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40002800) RTC Structure                                              */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) RTC Control Register High                                  */
    
    struct {
      __IOM uint32_t SECIE      : 1;            /*!< [0..0] Second interrupt Enable                                            */
      __IOM uint32_t ALRIE      : 1;            /*!< [1..1] Alarm interrupt Enable                                             */
      __IOM uint32_t OWIE       : 1;            /*!< [2..2] Overflow interrupt Enable                                          */
    } bit;
  } CTLRH;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) RTC Control Register Low                                   */
    
    struct {
      __IOM uint32_t SECF       : 1;            /*!< [0..0] Second Flag                                                        */
      __IOM uint32_t ALRF       : 1;            /*!< [1..1] Alarm Flag                                                         */
      __IOM uint32_t OWF        : 1;            /*!< [2..2] Overflow Flag                                                      */
      __IOM uint32_t RSF        : 1;            /*!< [3..3] Registers Synchronized Flag                                        */
      __IOM uint32_t CNF        : 1;            /*!< [4..4] Configuration Flag                                                 */
      __IM  uint32_t RTOFF      : 1;            /*!< [5..5] RTC operation OFF                                                  */
    } bit;
  } CTLRL;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000008) RTC Prescaler Load Register High                           */
    
    struct {
      __OM  uint32_t PRLH       : 4;            /*!< [3..0] RTC Prescaler Load Register High                                   */
    } bit;
  } PSCRH;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x0000000C) RTC Prescaler Load Register Low                            */
    
    struct {
      __OM  uint32_t PRLL       : 16;           /*!< [15..0] RTC Prescaler Divider Register Low                                */
    } bit;
  } PSCRL;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000010) RTC Prescaler Divider Register High                        */
    
    struct {
      __IM  uint32_t DIVH       : 4;            /*!< [3..0] RTC prescaler divider register high                                */
    } bit;
  } DIVH;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000014) RTC Prescaler Divider Register Low                         */
    
    struct {
      __IM  uint32_t DIVL       : 16;           /*!< [15..0] RTC prescaler divider register Low                                */
    } bit;
  } DIVL;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) RTC Counter Register High                                  */
    
    struct {
      __IOM uint32_t CNTH       : 16;           /*!< [15..0] RTC counter register high                                         */
    } bit;
  } CNTH;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) RTC Counter Register Low                                   */
    
    struct {
      __IOM uint32_t CNTL       : 16;           /*!< [15..0] RTC counter register Low                                          */
    } bit;
  } CNTL;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000020) RTC Alarm Register High                                    */
    
    struct {
      __OM  uint32_t ALRH       : 16;           /*!< [15..0] RTC alarm register high                                           */
    } bit;
  } ALRMH;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000024) RTC Alarm Register Low                                     */
    
    struct {
      __OM  uint32_t ALRL       : 16;           /*!< [15..0] RTC alarm register low                                            */
    } bit;
  } ALRML;
} RTC_Type;                                     /*!< Size = 40 (0x28)                                                          */



/* =========================================================================================================================== */
/* ================                                            BKP                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40006C00) BKP Structure                                              */
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D1         : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D2         : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D3         : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D4         : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D5         : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR5;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D6         : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR6;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D7         : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR7;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D8         : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR8;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D9         : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR9;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D10        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR10;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) RTC clock calibration register (BKP_OCTLR)                 */
    
    struct {
      __IOM uint32_t CAL        : 7;            /*!< [6..0] Calibration value                                                  */
      __IOM uint32_t CCO        : 1;            /*!< [7..7] Calibration Clock Output                                           */
      __IOM uint32_t ASOE       : 1;            /*!< [8..8] Alarm or second output enable                                      */
      __IOM uint32_t ASOS       : 1;            /*!< [9..9] Alarm or second output selection                                   */
    } bit;
  } OCTLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) Backup control register (BKP_TPCTLR)                       */
    
    struct {
      __IOM uint32_t TPE        : 1;            /*!< [0..0] Tamper pin enable                                                  */
      __IOM uint32_t TPAL       : 1;            /*!< [1..1] Tamper pin active level                                            */
    } bit;
  } TPCTLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) BKP_TPCSR control/status register (BKP_CSR)                */
    
    struct {
      __OM  uint32_t CTE        : 1;            /*!< [0..0] Clear Tamper event                                                 */
      __OM  uint32_t CTI        : 1;            /*!< [1..1] Clear Tamper Interrupt                                             */
      __IOM uint32_t TPIE       : 1;            /*!< [2..2] Tamper Pin interrupt enable                                        */
      __IM  uint32_t            : 5;
      __IM  uint32_t TEF        : 1;            /*!< [8..8] Tamper Event Flag                                                  */
      __IM  uint32_t TIF        : 1;            /*!< [9..9] Tamper Interrupt Flag                                              */
    } bit;
  } TPCSR;
  __IM  uint32_t  RESERVED1[2];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t DR11       : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR11;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000044) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t DR12       : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR12;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t DR13       : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR13;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D14        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR14;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000050) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D15        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR15;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000054) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D16        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR16;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000058) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D17        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR17;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000005C) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D18        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR18;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000060) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D19        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR19;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000064) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D20        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR20;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000068) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D21        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR21;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000006C) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D22        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR22;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000070) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D23        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR23;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000074) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D24        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR24;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000078) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D25        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR25;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000007C) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D26        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR26;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000080) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D27        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR27;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000084) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D28        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR28;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000088) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D29        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR29;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000008C) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D30        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR30;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000090) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D31        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR31;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000094) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D32        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR32;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000098) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D33        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR33;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000009C) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D34        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR34;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000A0) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D35        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR35;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000A4) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D36        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR36;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000A8) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D37        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR37;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000AC) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D38        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR38;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000B0) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D39        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR39;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000B4) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D40        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR40;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000B8) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D41        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR41;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x000000BC) Backup data register (BKP_DR)                              */
    
    struct {
      __IOM uint32_t D42        : 16;           /*!< [15..0] Backup data                                                       */
    } bit;
  } DATAR42;
} BKP_Type;                                     /*!< Size = 192 (0xc0)                                                         */



/* =========================================================================================================================== */
/* ================                                           IWDG                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40003000) IWDG Structure                                             */
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000000) Key register (IWDG_CTLR)                                   */
    
    struct {
      __OM  uint32_t KEY        : 16;           /*!< [15..0] Key value                                                         */
    } bit;
  } CTLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Prescaler register (IWDG_PSCR)                             */
    
    struct {
      __IOM uint32_t PR         : 3;            /*!< [2..0] Prescaler divider                                                  */
    } bit;
  } PSCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Reload register (IWDG_RLDR)                                */
    
    struct {
      __IOM uint32_t RL         : 12;           /*!< [11..0] Watchdog counter reload value                                     */
    } bit;
  } RLDR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x0000000C) Status register (IWDG_SR)                                  */
    
    struct {
      __IM  uint32_t PVU        : 1;            /*!< [0..0] Watchdog prescaler value update                                    */
      __IM  uint32_t RVU        : 1;            /*!< [1..1] Watchdog counter reload value update                               */
    } bit;
  } STATR;
} IWDG_Type;                                    /*!< Size = 16 (0x10)                                                          */



/* =========================================================================================================================== */
/* ================                                           WWDG                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40002C00) WWDG Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Control register (WWDG_CR)                                 */
    
    struct {
      __IOM uint32_t T          : 7;            /*!< [6..0] 7-bit counter (MSB to LSB)                                         */
      __IOM uint32_t WDGA       : 1;            /*!< [7..7] Activation bit                                                     */
    } bit;
  } CTLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Configuration register (WWDG_CFR)                          */
    
    struct {
      __IOM uint32_t W          : 7;            /*!< [6..0] 7-bit window value                                                 */
      __IOM uint32_t WDGTB      : 2;            /*!< [8..7] Timer Base                                                         */
      __IOM uint32_t EWI        : 1;            /*!< [9..9] Early Wakeup Interrupt                                             */
    } bit;
  } CFGR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Status register (WWDG_SR)                                  */
    
    struct {
      __IOM uint32_t WEIF       : 1;            /*!< [0..0] Early Wakeup Interrupt Flag                                        */
    } bit;
  } STATR;
} WWDG_Type;                                    /*!< Size = 12 (0xc)                                                           */



/* =========================================================================================================================== */
/* ================                                           TIM1                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40012C00) TIM1 Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) control register 1                                         */
    
    struct {
      __IOM uint32_t CEN        : 1;            /*!< [0..0] Counter enable                                                     */
      __IOM uint32_t UDIS       : 1;            /*!< [1..1] Update disable                                                     */
      __IOM uint32_t URS        : 1;            /*!< [2..2] Update request source                                              */
      __IOM uint32_t OPM        : 1;            /*!< [3..3] One-pulse mode                                                     */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Direction                                                          */
      __IOM uint32_t CMS        : 2;            /*!< [6..5] Center-aligned mode selection                                      */
      __IOM uint32_t ARPE       : 1;            /*!< [7..7] Auto-reload preload enable                                         */
      __IOM uint32_t CKD        : 2;            /*!< [9..8] Clock division                                                     */
    } bit;
  } CTLR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) control register 2                                         */
    
    struct {
      __IOM uint32_t CCPC       : 1;            /*!< [0..0] Capture/compare preloaded control                                  */
      __IM  uint32_t            : 1;
      __IOM uint32_t CCUS       : 1;            /*!< [2..2] Capture/compare control update selection                           */
      __IOM uint32_t CCDS       : 1;            /*!< [3..3] Capture/compare DMA selection                                      */
      __IOM uint32_t MMS        : 3;            /*!< [6..4] Master mode selection                                              */
      __IOM uint32_t TI1S       : 1;            /*!< [7..7] TI1 selection                                                      */
      __IOM uint32_t OIS1       : 1;            /*!< [8..8] Output Idle state 1                                                */
      __IOM uint32_t OIS1N      : 1;            /*!< [9..9] Output Idle state 1                                                */
      __IOM uint32_t OIS2       : 1;            /*!< [10..10] Output Idle state 2                                              */
      __IOM uint32_t OIS2N      : 1;            /*!< [11..11] Output Idle state 2                                              */
      __IOM uint32_t OIS3       : 1;            /*!< [12..12] Output Idle state 3                                              */
      __IOM uint32_t OIS3N      : 1;            /*!< [13..13] Output Idle state 3                                              */
      __IOM uint32_t OIS4       : 1;            /*!< [14..14] Output Idle state 4                                              */
    } bit;
  } CTLR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) slave mode control register                                */
    
    struct {
      __IOM uint32_t SMS        : 3;            /*!< [2..0] Slave mode selection                                               */
      __IM  uint32_t            : 1;
      __IOM uint32_t TS         : 3;            /*!< [6..4] Trigger selection                                                  */
      __IOM uint32_t MSM        : 1;            /*!< [7..7] Master/Slave mode                                                  */
      __IOM uint32_t ETF        : 4;            /*!< [11..8] External trigger filter                                           */
      __IOM uint32_t ETPS       : 2;            /*!< [13..12] External trigger prescaler                                       */
      __IOM uint32_t ECE        : 1;            /*!< [14..14] External clock enable                                            */
      __IOM uint32_t ETP        : 1;            /*!< [15..15] External trigger polarity                                        */
    } bit;
  } SMCFGR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) DMA/Interrupt enable register                              */
    
    struct {
      __IOM uint32_t UIE        : 1;            /*!< [0..0] Update interrupt enable                                            */
      __IOM uint32_t CC1IE      : 1;            /*!< [1..1] Capture/Compare 1 interrupt enable                                 */
      __IOM uint32_t CC2IE      : 1;            /*!< [2..2] Capture/Compare 2 interrupt enable                                 */
      __IOM uint32_t CC3IE      : 1;            /*!< [3..3] Capture/Compare 3 interrupt enable                                 */
      __IOM uint32_t CC4IE      : 1;            /*!< [4..4] Capture/Compare 4 interrupt enable                                 */
      __IOM uint32_t COMIE      : 1;            /*!< [5..5] COM interrupt enable                                               */
      __IOM uint32_t TIE        : 1;            /*!< [6..6] Trigger interrupt enable                                           */
      __IOM uint32_t BIE        : 1;            /*!< [7..7] Break interrupt enable                                             */
      __IOM uint32_t UDE        : 1;            /*!< [8..8] Update DMA request enable                                          */
      __IOM uint32_t CC1DE      : 1;            /*!< [9..9] Capture/Compare 1 DMA request enable                               */
      __IOM uint32_t CC2DE      : 1;            /*!< [10..10] Capture/Compare 2 DMA request enable                             */
      __IOM uint32_t CC3DE      : 1;            /*!< [11..11] Capture/Compare 3 DMA request enable                             */
      __IOM uint32_t CC4DE      : 1;            /*!< [12..12] Capture/Compare 4 DMA request enable                             */
      __IOM uint32_t COMDE      : 1;            /*!< [13..13] COM DMA request enable                                           */
      __IOM uint32_t TDE        : 1;            /*!< [14..14] Trigger DMA request enable                                       */
    } bit;
  } DMAINTENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) status register                                            */
    
    struct {
      __IOM uint32_t UIF        : 1;            /*!< [0..0] Update interrupt flag                                              */
      __IOM uint32_t CC1IF      : 1;            /*!< [1..1] Capture/compare 1 interrupt flag                                   */
      __IOM uint32_t CC2IF      : 1;            /*!< [2..2] Capture/Compare 2 interrupt flag                                   */
      __IOM uint32_t CC3IF      : 1;            /*!< [3..3] Capture/Compare 3 interrupt flag                                   */
      __IOM uint32_t CC4IF      : 1;            /*!< [4..4] Capture/Compare 4 interrupt flag                                   */
      __IOM uint32_t COMIF      : 1;            /*!< [5..5] COM interrupt flag                                                 */
      __IOM uint32_t TIF        : 1;            /*!< [6..6] Trigger interrupt flag                                             */
      __IOM uint32_t BIF        : 1;            /*!< [7..7] Break interrupt flag                                               */
      __IM  uint32_t            : 1;
      __IOM uint32_t CC1OF      : 1;            /*!< [9..9] Capture/Compare 1 overcapture flag                                 */
      __IOM uint32_t CC2OF      : 1;            /*!< [10..10] Capture/compare 2 overcapture flag                               */
      __IOM uint32_t CC3OF      : 1;            /*!< [11..11] Capture/Compare 3 overcapture flag                               */
      __IOM uint32_t CC4OF      : 1;            /*!< [12..12] Capture/Compare 4 overcapture flag                               */
    } bit;
  } INTFR;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000014) event generation register                                  */
    
    struct {
      __OM  uint32_t UG         : 1;            /*!< [0..0] Update generation                                                  */
      __OM  uint32_t CC1G       : 1;            /*!< [1..1] Capture/compare 1 generation                                       */
      __OM  uint32_t CC2G       : 1;            /*!< [2..2] Capture/compare 2 generation                                       */
      __OM  uint32_t CC3G       : 1;            /*!< [3..3] Capture/compare 3 generation                                       */
      __OM  uint32_t CC4G       : 1;            /*!< [4..4] Capture/compare 4 generation                                       */
      __OM  uint32_t COMG       : 1;            /*!< [5..5] Capture/Compare control update generation                          */
      __OM  uint32_t TG         : 1;            /*!< [6..6] Trigger generation                                                 */
      __OM  uint32_t BG         : 1;            /*!< [7..7] Break generation                                                   */
    } bit;
  } SWEVGR;
  
  union {
    union {
      __IOM uint32_t reg;                       /*!< (@ 0x00000018) capture/compare mode register (output mode)                */
      
      struct {
        __IOM uint32_t CC1S     : 2;            /*!< [1..0] Capture/Compare 1 selection                                        */
        __IOM uint32_t OC1FE    : 1;            /*!< [2..2] Output Compare 1 fast enable                                       */
        __IOM uint32_t OC1PE    : 1;            /*!< [3..3] Output Compare 1 preload enable                                    */
        __IOM uint32_t OC1M     : 3;            /*!< [6..4] Output Compare 1 mode                                              */
        __IOM uint32_t OC1CE    : 1;            /*!< [7..7] Output Compare 1 clear enable                                      */
        __IOM uint32_t CC2S     : 2;            /*!< [9..8] Capture/Compare 2 selection                                        */
        __IOM uint32_t OC2FE    : 1;            /*!< [10..10] Output Compare 2 fast enable                                     */
        __IOM uint32_t OC2PE    : 1;            /*!< [11..11] Output Compare 2 preload enable                                  */
        __IOM uint32_t OC2M     : 3;            /*!< [14..12] Output Compare 2 mode                                            */
        __IOM uint32_t OC2CE    : 1;            /*!< [15..15] Output Compare 2 clear enable                                    */
      } bit;
    } CHCTLR1_Output;
    
    union {
      __IOM uint32_t reg;                       /*!< (@ 0x00000018) capture/compare mode register 1 (input mode)               */
      
      struct {
        __IOM uint32_t CC1S     : 2;            /*!< [1..0] Capture/Compare 1 selection                                        */
        __IOM uint32_t IC1PSC   : 2;            /*!< [3..2] Input capture 1 prescaler                                          */
        __IOM uint32_t IC1F     : 4;            /*!< [7..4] Input capture 1 filter                                             */
        __IOM uint32_t CC2S     : 2;            /*!< [9..8] Capture/Compare 2 selection                                        */
        __IOM uint32_t IC2PCS   : 2;            /*!< [11..10] Input capture 2 prescaler                                        */
        __IOM uint32_t IC2F     : 4;            /*!< [15..12] Input capture 2 filter                                           */
      } bit;
    } CHCTLR1_Input;
  };
  
  union {
    union {
      __IOM uint32_t reg;                       /*!< (@ 0x0000001C) capture/compare mode register (output mode)                */
      
      struct {
        __IOM uint32_t CC3S     : 2;            /*!< [1..0] Capture/Compare 3 selection                                        */
        __IOM uint32_t OC3FE    : 1;            /*!< [2..2] Output compare 3 fast enable                                       */
        __IOM uint32_t OC3PE    : 1;            /*!< [3..3] Output compare 3 preload enable                                    */
        __IOM uint32_t OC3M     : 3;            /*!< [6..4] Output compare 3 mode                                              */
        __IOM uint32_t OC3CE    : 1;            /*!< [7..7] Output compare 3 clear enable                                      */
        __IOM uint32_t CC4S     : 2;            /*!< [9..8] Capture/Compare 4 selection                                        */
        __IOM uint32_t OC4FE    : 1;            /*!< [10..10] Output compare 4 fast enable                                     */
        __IOM uint32_t OC4PE    : 1;            /*!< [11..11] Output compare 4 preload enable                                  */
        __IOM uint32_t OC4M     : 3;            /*!< [14..12] Output compare 4 mode                                            */
        __IOM uint32_t OC4CE    : 1;            /*!< [15..15] Output compare 4 clear enable                                    */
      } bit;
    } CHCTLR2_Output;
    
    union {
      __IOM uint32_t reg;                       /*!< (@ 0x0000001C) capture/compare mode register 2 (input mode)               */
      
      struct {
        __IOM uint32_t CC3S     : 2;            /*!< [1..0] Capture/compare 3 selection                                        */
        __IOM uint32_t IC3PSC   : 2;            /*!< [3..2] Input capture 3 prescaler                                          */
        __IOM uint32_t IC3F     : 4;            /*!< [7..4] Input capture 3 filter                                             */
        __IOM uint32_t CC4S     : 2;            /*!< [9..8] Capture/Compare 4 selection                                        */
        __IOM uint32_t IC4PSC   : 2;            /*!< [11..10] Input capture 4 prescaler                                        */
        __IOM uint32_t IC4F     : 4;            /*!< [15..12] Input capture 4 filter                                           */
      } bit;
    } CHCTLR2_Input;
  };
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) capture/compare enable register                            */
    
    struct {
      __IOM uint32_t CC1E       : 1;            /*!< [0..0] Capture/Compare 1 output enable                                    */
      __IOM uint32_t CC1P       : 1;            /*!< [1..1] Capture/Compare 1 output Polarity                                  */
      __IOM uint32_t CC1NE      : 1;            /*!< [2..2] Capture/Compare 1 complementary output enable                      */
      __IOM uint32_t CC1NP      : 1;            /*!< [3..3] Capture/Compare 1 output Polarity                                  */
      __IOM uint32_t CC2E       : 1;            /*!< [4..4] Capture/Compare 2 output enable                                    */
      __IOM uint32_t CC2P       : 1;            /*!< [5..5] Capture/Compare 2 output Polarity                                  */
      __IOM uint32_t CC2NE      : 1;            /*!< [6..6] Capture/Compare 2 complementary output enable                      */
      __IOM uint32_t CC2NP      : 1;            /*!< [7..7] Capture/Compare 2 output Polarity                                  */
      __IOM uint32_t CC3E       : 1;            /*!< [8..8] Capture/Compare 3 output enable                                    */
      __IOM uint32_t CC3P       : 1;            /*!< [9..9] Capture/Compare 3 output Polarity                                  */
      __IOM uint32_t CC3NE      : 1;            /*!< [10..10] Capture/Compare 3 complementary output enable                    */
      __IOM uint32_t CC3NP      : 1;            /*!< [11..11] Capture/Compare 3 output Polarity                                */
      __IOM uint32_t CC4E       : 1;            /*!< [12..12] Capture/Compare 4 output enable                                  */
      __IOM uint32_t CC4P       : 1;            /*!< [13..13] Capture/Compare 3 output Polarity                                */
    } bit;
  } CCER;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) counter                                                    */
    
    struct {
      __IOM uint32_t CNT        : 16;           /*!< [15..0] counter value                                                     */
    } bit;
  } CNT;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) prescaler                                                  */
    
    struct {
      __IOM uint32_t PSC        : 16;           /*!< [15..0] Prescaler value                                                   */
    } bit;
  } PSC;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) auto-reload register                                       */
    
    struct {
      __IOM uint32_t ATRLR      : 16;           /*!< [15..0] Auto-reload value                                                 */
    } bit;
  } ATRLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) repetition counter register                                */
    
    struct {
      __IOM uint32_t RPTCR      : 8;            /*!< [7..0] Repetition counter value                                           */
    } bit;
  } RPTCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) capture/compare register 1                                 */
    
    struct {
      __IOM uint32_t CH1CVR     : 16;           /*!< [15..0] Capture/Compare 1 value                                           */
    } bit;
  } CH1CVR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) capture/compare register 2                                 */
    
    struct {
      __IOM uint32_t CH2CVR     : 16;           /*!< [15..0] Capture/Compare 2 value                                           */
    } bit;
  } CH2CVR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000003C) capture/compare register 3                                 */
    
    struct {
      __IOM uint32_t CH3CVR     : 16;           /*!< [15..0] Capture/Compare value                                             */
    } bit;
  } CH3CVR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) capture/compare register 4                                 */
    
    struct {
      __IOM uint32_t CH4CVR     : 16;           /*!< [15..0] Capture/Compare value                                             */
    } bit;
  } CH4CVR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000044) break and dead-time register                               */
    
    struct {
      __IOM uint32_t DTG        : 8;            /*!< [7..0] Dead-time generator setup                                          */
      __IOM uint32_t LOCK       : 2;            /*!< [9..8] Lock configuration                                                 */
      __IOM uint32_t OSSI       : 1;            /*!< [10..10] Off-state selection for Idle mode                                */
      __IOM uint32_t OSSR       : 1;            /*!< [11..11] Off-state selection for Run mode                                 */
      __IOM uint32_t BKE        : 1;            /*!< [12..12] Break enable                                                     */
      __IOM uint32_t BKP        : 1;            /*!< [13..13] Break polarity                                                   */
      __IOM uint32_t AOE        : 1;            /*!< [14..14] Automatic output enable                                          */
      __IOM uint32_t MOE        : 1;            /*!< [15..15] Main output enable                                               */
    } bit;
  } BDTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) DMA control register                                       */
    
    struct {
      __IOM uint32_t DBA        : 5;            /*!< [4..0] DMA base address                                                   */
      __IM  uint32_t            : 3;
      __IOM uint32_t DBL        : 5;            /*!< [12..8] DMA burst length                                                  */
    } bit;
  } DMACFGR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) DMA address for full transfer                              */
    
    struct {
      __IOM uint32_t DMAADR     : 16;           /*!< [15..0] DMA register for burst accesses                                   */
    } bit;
  } DMAADR;
} TIM1_Type;                                    /*!< Size = 80 (0x50)                                                          */



/* =========================================================================================================================== */
/* ================                                           TIM2                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40000000) TIM2 Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) control register 1                                         */
    
    struct {
      __IOM uint32_t CEN        : 1;            /*!< [0..0] Counter enable                                                     */
      __IOM uint32_t UDIS       : 1;            /*!< [1..1] Update disable                                                     */
      __IOM uint32_t URS        : 1;            /*!< [2..2] Update request source                                              */
      __IOM uint32_t OPM        : 1;            /*!< [3..3] One-pulse mode                                                     */
      __IOM uint32_t DIR        : 1;            /*!< [4..4] Direction                                                          */
      __IOM uint32_t CMS        : 2;            /*!< [6..5] Center-aligned mode selection                                      */
      __IOM uint32_t ARPE       : 1;            /*!< [7..7] Auto-reload preload enable                                         */
      __IOM uint32_t CKD        : 2;            /*!< [9..8] Clock division                                                     */
    } bit;
  } CTLR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) control register 2                                         */
    
    struct {
      __IOM uint32_t CCPC       : 1;            /*!< [0..0] Compare selection                                                  */
      __IM  uint32_t            : 1;
      __IOM uint32_t CCUS       : 1;            /*!< [2..2] Update selection                                                   */
      __IOM uint32_t CCDS       : 1;            /*!< [3..3] Capture/compare DMA selection                                      */
      __IOM uint32_t MMS        : 3;            /*!< [6..4] Master mode selection                                              */
      __IOM uint32_t TI1S       : 1;            /*!< [7..7] TI1 selection                                                      */
    } bit;
  } CTLR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) slave mode control register                                */
    
    struct {
      __IOM uint32_t SMS        : 3;            /*!< [2..0] Slave mode selection                                               */
      __IM  uint32_t            : 1;
      __IOM uint32_t TS         : 3;            /*!< [6..4] Trigger selection                                                  */
      __IOM uint32_t MSM        : 1;            /*!< [7..7] Master/Slave mode                                                  */
      __IOM uint32_t ETF        : 4;            /*!< [11..8] External trigger filter                                           */
      __IOM uint32_t ETPS       : 2;            /*!< [13..12] External trigger prescaler                                       */
      __IOM uint32_t ECE        : 1;            /*!< [14..14] External clock enable                                            */
      __IOM uint32_t ETP        : 1;            /*!< [15..15] External trigger polarity                                        */
    } bit;
  } SMCFGR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) DMA/Interrupt enable register                              */
    
    struct {
      __IOM uint32_t UIE        : 1;            /*!< [0..0] Update interrupt enable                                            */
      __IOM uint32_t CC1IE      : 1;            /*!< [1..1] Capture/Compare 1 interrupt enable                                 */
      __IOM uint32_t CC2IE      : 1;            /*!< [2..2] Capture/Compare 2 interrupt enable                                 */
      __IOM uint32_t CC3IE      : 1;            /*!< [3..3] Capture/Compare 3 interrupt enable                                 */
      __IOM uint32_t CC4IE      : 1;            /*!< [4..4] Capture/Compare 4 interrupt enable                                 */
      __IM  uint32_t            : 1;
      __IOM uint32_t TIE        : 1;            /*!< [6..6] Trigger interrupt enable                                           */
      __IM  uint32_t            : 1;
      __IOM uint32_t UDE        : 1;            /*!< [8..8] Update DMA request enable                                          */
      __IOM uint32_t CC1DE      : 1;            /*!< [9..9] Capture/Compare 1 DMA request enable                               */
      __IOM uint32_t CC2DE      : 1;            /*!< [10..10] Capture/Compare 2 DMA request enable                             */
      __IOM uint32_t CC3DE      : 1;            /*!< [11..11] Capture/Compare 3 DMA request enable                             */
      __IOM uint32_t CC4DE      : 1;            /*!< [12..12] Capture/Compare 4 DMA request enable                             */
      __IOM uint32_t COMDE      : 1;            /*!< [13..13] COM DMA request enable                                           */
      __IOM uint32_t TDE        : 1;            /*!< [14..14] Trigger DMA request enable                                       */
    } bit;
  } DMAINTENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) status register                                            */
    
    struct {
      __IOM uint32_t UIF        : 1;            /*!< [0..0] Update interrupt flag                                              */
      __IOM uint32_t CC1IF      : 1;            /*!< [1..1] Capture/compare 1 interrupt flag                                   */
      __IOM uint32_t CC2IF      : 1;            /*!< [2..2] Capture/Compare 2 interrupt flag                                   */
      __IOM uint32_t CC3IF      : 1;            /*!< [3..3] Capture/Compare 3 interrupt flag                                   */
      __IOM uint32_t CC4IF      : 1;            /*!< [4..4] Capture/Compare 4 interrupt flag                                   */
      __IM  uint32_t            : 1;
      __IOM uint32_t TIF        : 1;            /*!< [6..6] Trigger interrupt flag                                             */
      __IM  uint32_t            : 2;
      __IOM uint32_t CC1OF      : 1;            /*!< [9..9] Capture/Compare 1 overcapture flag                                 */
      __IOM uint32_t CC2OF      : 1;            /*!< [10..10] Capture/compare 2 overcapture flag                               */
      __IOM uint32_t CC3OF      : 1;            /*!< [11..11] Capture/Compare 3 overcapture flag                               */
      __IOM uint32_t CC4OF      : 1;            /*!< [12..12] Capture/Compare 4 overcapture flag                               */
    } bit;
  } INTFR;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000014) event generation register                                  */
    
    struct {
      __OM  uint32_t UG         : 1;            /*!< [0..0] Update generation                                                  */
      __OM  uint32_t CC1G       : 1;            /*!< [1..1] Capture/compare 1 generation                                       */
      __OM  uint32_t CC2G       : 1;            /*!< [2..2] Capture/compare 2 generation                                       */
      __OM  uint32_t CC3G       : 1;            /*!< [3..3] Capture/compare 3 generation                                       */
      __OM  uint32_t CC4G       : 1;            /*!< [4..4] Capture/compare 4 generation                                       */
      __OM  uint32_t COMG       : 1;            /*!< [5..5] Capture/compare generation                                         */
      __OM  uint32_t TG         : 1;            /*!< [6..6] Trigger generation                                                 */
      __OM  uint32_t BG         : 1;            /*!< [7..7] Brake generation                                                   */
    } bit;
  } SWEVGR;
  
  union {
    union {
      __IOM uint32_t reg;                       /*!< (@ 0x00000018) capture/compare mode register 1 (output mode)              */
      
      struct {
        __IOM uint32_t CC1S     : 2;            /*!< [1..0] Capture/Compare 1 selection                                        */
        __IOM uint32_t OC1FE    : 1;            /*!< [2..2] Output compare 1 fast enable                                       */
        __IOM uint32_t OC1PE    : 1;            /*!< [3..3] Output compare 1 preload enable                                    */
        __IOM uint32_t OC1M     : 3;            /*!< [6..4] Output compare 1 mode                                              */
        __IOM uint32_t OC1CE    : 1;            /*!< [7..7] Output compare 1 clear enable                                      */
        __IOM uint32_t CC2S     : 2;            /*!< [9..8] Capture/Compare 2 selection                                        */
        __IOM uint32_t OC2FE    : 1;            /*!< [10..10] Output compare 2 fast enable                                     */
        __IOM uint32_t OC2PE    : 1;            /*!< [11..11] Output compare 2 preload enable                                  */
        __IOM uint32_t OC2M     : 3;            /*!< [14..12] Output compare 2 mode                                            */
        __IOM uint32_t OC2CE    : 1;            /*!< [15..15] Output compare 2 clear enable                                    */
      } bit;
    } CHCTLR1_Output;
    
    union {
      __IOM uint32_t reg;                       /*!< (@ 0x00000018) capture/compare mode register 1 (input mode)               */
      
      struct {
        __IOM uint32_t CC1S     : 2;            /*!< [1..0] Capture/Compare 1 selection                                        */
        __IOM uint32_t IC1PSC   : 2;            /*!< [3..2] Input capture 1 prescaler                                          */
        __IOM uint32_t IC1F     : 4;            /*!< [7..4] Input capture 1 filter                                             */
        __IOM uint32_t CC2S     : 2;            /*!< [9..8] Capture/compare 2 selection                                        */
        __IOM uint32_t IC2PSC   : 2;            /*!< [11..10] Input capture 2 prescaler                                        */
        __IOM uint32_t IC2F     : 4;            /*!< [15..12] Input capture 2 filter                                           */
      } bit;
    } CHCTLR1_Input;
  };
  
  union {
    union {
      __IOM uint32_t reg;                       /*!< (@ 0x0000001C) capture/compare mode register 2 (output mode)              */
      
      struct {
        __IOM uint32_t CC3S     : 2;            /*!< [1..0] Capture/Compare 3 selection                                        */
        __IOM uint32_t OC3FE    : 1;            /*!< [2..2] Output compare 3 fast enable                                       */
        __IOM uint32_t OC3PE    : 1;            /*!< [3..3] Output compare 3 preload enable                                    */
        __IOM uint32_t OC3M     : 3;            /*!< [6..4] Output compare 3 mode                                              */
        __IOM uint32_t OC3CE    : 1;            /*!< [7..7] Output compare 3 clear enable                                      */
        __IOM uint32_t CC4S     : 2;            /*!< [9..8] Capture/Compare 4 selection                                        */
        __IOM uint32_t OC4FE    : 1;            /*!< [10..10] Output compare 4 fast enable                                     */
        __IOM uint32_t OC4PE    : 1;            /*!< [11..11] Output compare 4 preload enable                                  */
        __IOM uint32_t OC4M     : 3;            /*!< [14..12] Output compare 4 mode                                            */
        __IOM uint32_t OC4CE    : 1;            /*!< [15..15] Output compare 4 clear enable                                    */
      } bit;
    } CHCTLR2_Output;
    
    union {
      __IOM uint32_t reg;                       /*!< (@ 0x0000001C) capture/compare mode register 2 (input mode)               */
      
      struct {
        __IOM uint32_t CC3S     : 2;            /*!< [1..0] Capture/Compare 3 selection                                        */
        __IOM uint32_t IC3PSC   : 2;            /*!< [3..2] Input capture 3 prescaler                                          */
        __IOM uint32_t IC3F     : 4;            /*!< [7..4] Input capture 3 filter                                             */
        __IOM uint32_t CC4S     : 2;            /*!< [9..8] Capture/Compare 4 selection                                        */
        __IOM uint32_t IC4PSC   : 2;            /*!< [11..10] Input capture 4 prescaler                                        */
        __IOM uint32_t IC4F     : 4;            /*!< [15..12] Input capture 4 filter                                           */
      } bit;
    } CHCTLR2_Input;
  };
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) capture/compare enable register                            */
    
    struct {
      __IOM uint32_t CC1E       : 1;            /*!< [0..0] Capture/Compare 1 output enable                                    */
      __IOM uint32_t CC1P       : 1;            /*!< [1..1] Capture/Compare 1 output Polarity                                  */
      __IM  uint32_t            : 2;
      __IOM uint32_t CC2E       : 1;            /*!< [4..4] Capture/Compare 2 output enable                                    */
      __IOM uint32_t CC2P       : 1;            /*!< [5..5] Capture/Compare 2 output Polarity                                  */
      __IM  uint32_t            : 2;
      __IOM uint32_t CC3E       : 1;            /*!< [8..8] Capture/Compare 3 output enable                                    */
      __IOM uint32_t CC3P       : 1;            /*!< [9..9] Capture/Compare 3 output Polarity                                  */
      __IM  uint32_t            : 2;
      __IOM uint32_t CC4E       : 1;            /*!< [12..12] Capture/Compare 4 output enable                                  */
      __IOM uint32_t CC4P       : 1;            /*!< [13..13] Capture/Compare 3 output Polarity                                */
    } bit;
  } CCER;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) counter                                                    */
    
    struct {
      __IOM uint32_t CNT        : 16;           /*!< [15..0] counter value                                                     */
    } bit;
  } CNT;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) prescaler                                                  */
    
    struct {
      __IOM uint32_t PSC        : 16;           /*!< [15..0] Prescaler value                                                   */
    } bit;
  } PSC;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) auto-reload register                                       */
    
    struct {
      __IOM uint32_t ATRLR      : 16;           /*!< [15..0] Auto-reload value                                                 */
    } bit;
  } ATRLR;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) capture/compare register 1                                 */
    
    struct {
      __IOM uint32_t CH1CVR     : 16;           /*!< [15..0] Capture/Compare 1 value                                           */
    } bit;
  } CH1CVR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) capture/compare register 2                                 */
    
    struct {
      __IOM uint32_t CH2CVR     : 16;           /*!< [15..0] Capture/Compare 2 value                                           */
    } bit;
  } CH2CVR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000003C) capture/compare register 3                                 */
    
    struct {
      __IOM uint32_t CH3CVR     : 16;           /*!< [15..0] Capture/Compare value                                             */
    } bit;
  } CH3CVR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) capture/compare register 4                                 */
    
    struct {
      __IOM uint32_t CH4CVR     : 16;           /*!< [15..0] Capture/Compare value                                             */
    } bit;
  } CH4CVR;
  __IM  uint32_t  RESERVED1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) DMA control register                                       */
    
    struct {
      __IOM uint32_t DBA        : 5;            /*!< [4..0] DMA base address                                                   */
      __IM  uint32_t            : 3;
      __IOM uint32_t DBL        : 5;            /*!< [12..8] DMA burst length                                                  */
    } bit;
  } DMACFGR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) DMA address for full transfer                              */
    
    struct {
      __IOM uint32_t DMAADR     : 16;           /*!< [15..0] DMA register for burst accesses                                   */
    } bit;
  } DMAADR;
} TIM2_Type;                                    /*!< Size = 80 (0x50)                                                          */



/* =========================================================================================================================== */
/* ================                                           TIM6                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40001000) TIM6 Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) control register 1                                         */
    
    struct {
      __IOM uint32_t CEN        : 1;            /*!< [0..0] Counter enable                                                     */
      __IOM uint32_t UDIS       : 1;            /*!< [1..1] Update disable                                                     */
      __IOM uint32_t URS        : 1;            /*!< [2..2] Update request source                                              */
      __IOM uint32_t OPM        : 1;            /*!< [3..3] One-pulse mode                                                     */
      __IM  uint32_t            : 3;
      __IOM uint32_t ARPE       : 1;            /*!< [7..7] Auto-reload preload enable                                         */
    } bit;
  } CTLR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) control register 2                                         */
    
    struct {
      __IM  uint32_t            : 4;
      __IOM uint32_t MMS        : 3;            /*!< [6..4] Master mode selection                                              */
    } bit;
  } CTLR2;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) DMA/Interrupt enable register                              */
    
    struct {
      __IOM uint32_t UIE        : 1;            /*!< [0..0] Update interrupt enable                                            */
      __IM  uint32_t            : 7;
      __IOM uint32_t UDE        : 1;            /*!< [8..8] Update DMA request enable                                          */
    } bit;
  } DMAINTENR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) status register                                            */
    
    struct {
      __IOM uint32_t UIF        : 1;            /*!< [0..0] Update interrupt flag                                              */
    } bit;
  } INTFR;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000014) event generation register                                  */
    
    struct {
      __OM  uint32_t UG         : 1;            /*!< [0..0] Update generation                                                  */
    } bit;
  } SWEVGR;
  __IM  uint32_t  RESERVED1[3];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) counter                                                    */
    
    struct {
      __IOM uint32_t CNT        : 16;           /*!< [15..0] counter value                                                     */
    } bit;
  } CNT;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) prescaler                                                  */
    
    struct {
      __IOM uint32_t PSC        : 16;           /*!< [15..0] Prescaler value                                                   */
    } bit;
  } PSC;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) auto-reload register                                       */
    
    struct {
      __IOM uint32_t ATRLR      : 16;           /*!< [15..0] Auto-reload value                                                 */
    } bit;
  } ATRLR;
} TIM6_Type;                                    /*!< Size = 48 (0x30)                                                          */



/* =========================================================================================================================== */
/* ================                                           I2C1                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40005400) I2C1 Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Control register 1                                         */
    
    struct {
      __IOM uint32_t PE         : 1;            /*!< [0..0] Peripheral enable                                                  */
      __IOM uint32_t SMBUS      : 1;            /*!< [1..1] SMBus mode                                                         */
      __IM  uint32_t            : 1;
      __IOM uint32_t SMBTYPE    : 1;            /*!< [3..3] SMBus type                                                         */
      __IOM uint32_t ENARP      : 1;            /*!< [4..4] ARP enable                                                         */
      __IOM uint32_t ENPEC      : 1;            /*!< [5..5] PEC enable                                                         */
      __IOM uint32_t ENGC       : 1;            /*!< [6..6] General call enable                                                */
      __IOM uint32_t NOSTRETCH  : 1;            /*!< [7..7] Clock stretching disable (Slave mode)                              */
      __IOM uint32_t START      : 1;            /*!< [8..8] Start generation                                                   */
      __IOM uint32_t STOP       : 1;            /*!< [9..9] Stop generation                                                    */
      __IOM uint32_t ACK        : 1;            /*!< [10..10] Acknowledge enable                                               */
      __IOM uint32_t POS        : 1;            /*!< [11..11] Acknowledge/PEC Position (for data reception)                    */
      __IOM uint32_t PEC        : 1;            /*!< [12..12] Packet error checking                                            */
      __IOM uint32_t ALERT      : 1;            /*!< [13..13] SMBus alert                                                      */
      __IM  uint32_t            : 1;
      __IOM uint32_t SWRST      : 1;            /*!< [15..15] Software reset                                                   */
    } bit;
  } CTLR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Control register 2                                         */
    
    struct {
      __IOM uint32_t FREQ       : 6;            /*!< [5..0] Peripheral clock frequency                                         */
      __IM  uint32_t            : 2;
      __IOM uint32_t ITERREN    : 1;            /*!< [8..8] Error interrupt enable                                             */
      __IOM uint32_t ITEVTEN    : 1;            /*!< [9..9] Event interrupt enable                                             */
      __IOM uint32_t ITBUFEN    : 1;            /*!< [10..10] Buffer interrupt enable                                          */
      __IOM uint32_t DMAEN      : 1;            /*!< [11..11] DMA requests enable                                              */
      __IOM uint32_t LAST       : 1;            /*!< [12..12] DMA last transfer                                                */
    } bit;
  } CTLR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Own address register 1                                     */
    
    struct {
      __IOM uint32_t ADD0       : 1;            /*!< [0..0] Interface address                                                  */
      __IOM uint32_t ADD7_1     : 7;            /*!< [7..1] Interface address                                                  */
      __IOM uint32_t ADD9_8     : 2;            /*!< [9..8] Interface address                                                  */
      __IM  uint32_t            : 4;
      __IOM uint32_t MUST1      : 1;            /*!< [14..14] Must be 1                                                        */
      __IOM uint32_t ADDMODE    : 1;            /*!< [15..15] Addressing mode (slave mode)                                     */
    } bit;
  } OADDR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Own address register 2                                     */
    
    struct {
      __IOM uint32_t ENDUAL     : 1;            /*!< [0..0] Dual addressing mode enable                                        */
      __IOM uint32_t ADD2       : 7;            /*!< [7..1] Interface address                                                  */
    } bit;
  } OADDR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) Data register                                              */
    
    struct {
      __IOM uint32_t DATAR      : 8;            /*!< [7..0] 8-bit data register                                                */
    } bit;
  } DATAR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Status register 1                                          */
    
    struct {
      __IM  uint32_t SB         : 1;            /*!< [0..0] Start bit (Master mode)                                            */
      __IM  uint32_t ADDR       : 1;            /*!< [1..1] Address sent (master mode)/matched (slave mode)                    */
      __IM  uint32_t BTF        : 1;            /*!< [2..2] Byte transfer finished                                             */
      __IM  uint32_t ADD10      : 1;            /*!< [3..3] 10-bit header sent (Master mode)                                   */
      __IM  uint32_t STOPF      : 1;            /*!< [4..4] Stop detection (slave mode)                                        */
      __IM  uint32_t            : 1;
      __IM  uint32_t RxNE       : 1;            /*!< [6..6] Data register not empty (receivers)                                */
      __IM  uint32_t TxE        : 1;            /*!< [7..7] Data register empty (transmitters)                                 */
      __IOM uint32_t BERR       : 1;            /*!< [8..8] Bus error                                                          */
      __IOM uint32_t ARLO       : 1;            /*!< [9..9] Arbitration lost (master mode)                                     */
      __IOM uint32_t AF         : 1;            /*!< [10..10] Acknowledge failure                                              */
      __IOM uint32_t OVR        : 1;            /*!< [11..11] Overrun/Underrun                                                 */
      __IOM uint32_t PECERR     : 1;            /*!< [12..12] PEC Error in reception                                           */
      __IM  uint32_t            : 1;
      __IOM uint32_t TIMEOUT    : 1;            /*!< [14..14] Timeout or Tlow error                                            */
      __IOM uint32_t SMBALERT   : 1;            /*!< [15..15] SMBus alert                                                      */
    } bit;
  } STAR1;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000018) Status register 2                                          */
    
    struct {
      __IM  uint32_t MSL        : 1;            /*!< [0..0] Master/slave                                                       */
      __IM  uint32_t BUSY       : 1;            /*!< [1..1] Bus busy                                                           */
      __IM  uint32_t TRA        : 1;            /*!< [2..2] Transmitter/receiver                                               */
      __IM  uint32_t            : 1;
      __IM  uint32_t GENCALL    : 1;            /*!< [4..4] General call address (Slave mode)                                  */
      __IM  uint32_t SMBDEFAULT : 1;            /*!< [5..5] SMBus device default address (Slave mode)                          */
      __IM  uint32_t SMBHOST    : 1;            /*!< [6..6] SMBus host header (Slave mode)                                     */
      __IM  uint32_t DUALF      : 1;            /*!< [7..7] Dual flag (Slave mode)                                             */
      __IM  uint32_t PEC        : 8;            /*!< [15..8] acket error checking register                                     */
    } bit;
  } STAR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) Clock control register                                     */
    
    struct {
      __IOM uint32_t CCR        : 12;           /*!< [11..0] Clock control register in Fast/Standard mode (Master
                                                     mode)                                                                     */
      __IM  uint32_t            : 2;
      __IOM uint32_t DUTY       : 1;            /*!< [14..14] Fast mode duty cycle                                             */
      __IOM uint32_t F_S        : 1;            /*!< [15..15] I2C master mode selection                                        */
    } bit;
  } CKCFGR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) Raise time register                                        */
    
    struct {
      __IOM uint32_t TRISE      : 6;            /*!< [5..0] Maximum rise time in Fast/Standard mode (Master mode)              */
    } bit;
  } RTR;
} I2C1_Type;                                    /*!< Size = 36 (0x24)                                                          */



/* =========================================================================================================================== */
/* ================                                           SPI1                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40013000) SPI1 Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) control register 1                                         */
    
    struct {
      __IOM uint32_t CPHA       : 1;            /*!< [0..0] Clock phase                                                        */
      __IOM uint32_t CPOL       : 1;            /*!< [1..1] Clock polarity                                                     */
      __IOM uint32_t MSTR       : 1;            /*!< [2..2] Master selection                                                   */
      __IOM uint32_t BR         : 3;            /*!< [5..3] Baud rate control                                                  */
      __IOM uint32_t SPE        : 1;            /*!< [6..6] SPI enable                                                         */
      __IOM uint32_t LSBFIRST   : 1;            /*!< [7..7] Frame format                                                       */
      __IOM uint32_t SSI        : 1;            /*!< [8..8] Internal slave select                                              */
      __IOM uint32_t SSM        : 1;            /*!< [9..9] Software slave management                                          */
      __IOM uint32_t RXONLY     : 1;            /*!< [10..10] Receive only                                                     */
      __IOM uint32_t DFF        : 1;            /*!< [11..11] Data frame format                                                */
      __IOM uint32_t CRCNEXT    : 1;            /*!< [12..12] CRC transfer next                                                */
      __IOM uint32_t CRCEN      : 1;            /*!< [13..13] Hardware CRC calculation enable                                  */
      __IOM uint32_t BIDIOE     : 1;            /*!< [14..14] Output enable in bidirectional mode                              */
      __IOM uint32_t BIDIMODE   : 1;            /*!< [15..15] Bidirectional data mode enable                                   */
    } bit;
  } CTLR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) control register 2                                         */
    
    struct {
      __IOM uint32_t RXDMAEN    : 1;            /*!< [0..0] Rx buffer DMA enable                                               */
      __IOM uint32_t TXDMAEN    : 1;            /*!< [1..1] Tx buffer DMA enable                                               */
      __IOM uint32_t SSOE       : 1;            /*!< [2..2] SS output enable                                                   */
      __IM  uint32_t            : 2;
      __IOM uint32_t ERRIE      : 1;            /*!< [5..5] Error interrupt enable                                             */
      __IOM uint32_t RXNEIE     : 1;            /*!< [6..6] RX buffer not empty interrupt enable                               */
      __IOM uint32_t TXEIE      : 1;            /*!< [7..7] Tx buffer empty interrupt enable                                   */
    } bit;
  } CTLR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) status register                                            */
    
    struct {
      __IM  uint32_t RXNE       : 1;            /*!< [0..0] Receive buffer not empty                                           */
      __IM  uint32_t TXE        : 1;            /*!< [1..1] Transmit buffer empty                                              */
      __IM  uint32_t CHSID      : 1;            /*!< [2..2] Channel side                                                       */
      __IM  uint32_t UDR        : 1;            /*!< [3..3] Underrun flag                                                      */
      __IOM uint32_t CRCERR     : 1;            /*!< [4..4] CRC error flag                                                     */
      __IM  uint32_t MODF       : 1;            /*!< [5..5] Mode fault                                                         */
      __IM  uint32_t OVR        : 1;            /*!< [6..6] Overrun flag                                                       */
      __IM  uint32_t BSY        : 1;            /*!< [7..7] Busy flag                                                          */
    } bit;
  } STATR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) data register                                              */
    
    struct {
      __IOM uint32_t DATAR      : 16;           /*!< [15..0] Data register                                                     */
    } bit;
  } DATAR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) CRCR polynomial register                                   */
    
    struct {
      __IOM uint32_t CRCPOLY    : 16;           /*!< [15..0] CRC polynomial register                                           */
    } bit;
  } CRCR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000014) RX CRC register                                            */
    
    struct {
      __IM  uint32_t RXCRC      : 16;           /*!< [15..0] Rx CRC register                                                   */
    } bit;
  } RCRCR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000018) TX CRC register                                            */
    
    struct {
      __IM  uint32_t TXCRC      : 16;           /*!< [15..0] Tx CRC register                                                   */
    } bit;
  } TCRCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) SPI_I2S configure register                                 */
    
    struct {
      __IOM uint32_t CHLEN      : 1;            /*!< [0..0] Channel length (number of bits per audio channel)                  */
      __IOM uint32_t DATLEN     : 2;            /*!< [2..1] DATLEN[1:0] bits (Data length to be transferred)                   */
      __IOM uint32_t CKPOL      : 1;            /*!< [3..3] steady state clock polarity                                        */
      __IOM uint32_t I2SSTD     : 2;            /*!< [5..4] I2SSTD[1:0] bits (I2S standard selection)                          */
      __IM  uint32_t            : 1;
      __IOM uint32_t PCMSYNC    : 1;            /*!< [7..7] PCM frame synchronization                                          */
      __IOM uint32_t I2SCFG     : 2;            /*!< [9..8] I2SCFG[1:0] bits (I2S configuration mode)                          */
      __IOM uint32_t I2SE       : 1;            /*!< [10..10] I2S Enable                                                       */
      __IOM uint32_t I2SMOD     : 1;            /*!< [11..11] I2S mode selection                                               */
    } bit;
  } SPI_I2S_CFGR;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) high speed control register                                */
    
    struct {
      __IOM uint32_t HSRXEN     : 1;            /*!< [0..0] High speed mode read enable                                        */
    } bit;
  } HSCR;
} SPI1_Type;                                    /*!< Size = 40 (0x28)                                                          */



/* =========================================================================================================================== */
/* ================                                           SPI2                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40003800) SPI2 Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) control register 1                                         */
    
    struct {
      __IOM uint32_t CPHA       : 1;            /*!< [0..0] Clock phase                                                        */
      __IOM uint32_t CPOL       : 1;            /*!< [1..1] Clock polarity                                                     */
      __IOM uint32_t MSTR       : 1;            /*!< [2..2] Master selection                                                   */
      __IOM uint32_t BR         : 3;            /*!< [5..3] Baud rate control                                                  */
      __IOM uint32_t SPE        : 1;            /*!< [6..6] SPI enable                                                         */
      __IOM uint32_t LSBFIRST   : 1;            /*!< [7..7] Frame format                                                       */
      __IOM uint32_t SSI        : 1;            /*!< [8..8] Internal slave select                                              */
      __IOM uint32_t SSM        : 1;            /*!< [9..9] Software slave management                                          */
      __IOM uint32_t RXONLY     : 1;            /*!< [10..10] Receive only                                                     */
      __IOM uint32_t DFF        : 1;            /*!< [11..11] Data frame format                                                */
      __IOM uint32_t CRCNEXT    : 1;            /*!< [12..12] CRC transfer next                                                */
      __IOM uint32_t CRCEN      : 1;            /*!< [13..13] Hardware CRC calculation enable                                  */
      __IOM uint32_t BIDIOE     : 1;            /*!< [14..14] Output enable in bidirectional mode                              */
      __IOM uint32_t BIDIMODE   : 1;            /*!< [15..15] Bidirectional data mode enable                                   */
    } bit;
  } CTLR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) control register 2                                         */
    
    struct {
      __IOM uint32_t RXDMAEN    : 1;            /*!< [0..0] Rx buffer DMA enable                                               */
      __IOM uint32_t TXDMAEN    : 1;            /*!< [1..1] Tx buffer DMA enable                                               */
      __IOM uint32_t SSOE       : 1;            /*!< [2..2] SS output enable                                                   */
      __IM  uint32_t            : 2;
      __IOM uint32_t ERRIE      : 1;            /*!< [5..5] Error interrupt enable                                             */
      __IOM uint32_t RXNEIE     : 1;            /*!< [6..6] RX buffer not empty interrupt enable                               */
      __IOM uint32_t TXEIE      : 1;            /*!< [7..7] Tx buffer empty interrupt enable                                   */
    } bit;
  } CTLR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) status register                                            */
    
    struct {
      __IM  uint32_t RXNE       : 1;            /*!< [0..0] Receive buffer not empty                                           */
      __IM  uint32_t TXE        : 1;            /*!< [1..1] Transmit buffer empty                                              */
      __IM  uint32_t            : 2;
      __IOM uint32_t CRCERR     : 1;            /*!< [4..4] CRC error flag                                                     */
      __IM  uint32_t MODF       : 1;            /*!< [5..5] Mode fault                                                         */
      __IM  uint32_t OVR        : 1;            /*!< [6..6] Overrun flag                                                       */
      __IM  uint32_t BSY        : 1;            /*!< [7..7] Busy flag                                                          */
    } bit;
  } STATR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) data register                                              */
    
    struct {
      __IOM uint32_t DATAR      : 16;           /*!< [15..0] Data register                                                     */
    } bit;
  } DATAR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) CRCR polynomial register                                   */
    
    struct {
      __IOM uint32_t CRCPOLY    : 16;           /*!< [15..0] CRC polynomial register                                           */
    } bit;
  } CRCR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000014) RX CRC register                                            */
    
    struct {
      __IM  uint32_t RXCRC      : 16;           /*!< [15..0] Rx CRC register                                                   */
    } bit;
  } RCRCR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000018) TX CRC register                                            */
    
    struct {
      __IM  uint32_t TXCRC      : 16;           /*!< [15..0] Tx CRC register                                                   */
    } bit;
  } TCRCR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) I2S configuration register                                 */
    
    struct {
      __IOM uint32_t CHLEN      : 1;            /*!< [0..0] Channel length (number of bits per audio channel)                  */
      __IOM uint32_t DATLEN     : 2;            /*!< [2..1] Data length to be transferred                                      */
      __IOM uint32_t CKPOL      : 1;            /*!< [3..3] Steady state clock polarity                                        */
      __IOM uint32_t I2SSTD     : 2;            /*!< [5..4] I2S standard selection                                             */
      __IM  uint32_t            : 1;
      __IOM uint32_t PCMSYNC    : 1;            /*!< [7..7] PCM frame synchronization                                          */
      __IOM uint32_t I2SCFG     : 2;            /*!< [9..8] I2S configuration mode                                             */
      __IOM uint32_t I2SE       : 1;            /*!< [10..10] I2S Enable                                                       */
      __IOM uint32_t I2SMOD     : 1;            /*!< [11..11] I2S mode selection                                               */
    } bit;
  } I2SCFGR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) I2S prescaler register                                     */
    
    struct {
      __IOM uint32_t I2SDIV     : 8;            /*!< [7..0] I2S Linear prescaler                                               */
      __IOM uint32_t ODD        : 1;            /*!< [8..8] Odd factor for the prescaler                                       */
      __IOM uint32_t MCKOE      : 1;            /*!< [9..9] Master clock output enable                                         */
    } bit;
  } I2SPR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) high speed control register                                */
    
    struct {
      __IOM uint32_t HSRXEN     : 1;            /*!< [0..0] High speed mode read enable                                        */
    } bit;
  } HSCR;
} SPI2_Type;                                    /*!< Size = 40 (0x28)                                                          */



/* =========================================================================================================================== */
/* ================                                          USART1                                           ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40013800) USART1 Structure                                           */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Status register                                            */
    
    struct {
      __IM  uint32_t PE         : 1;            /*!< [0..0] Parity error                                                       */
      __IM  uint32_t FE         : 1;            /*!< [1..1] Framing error                                                      */
      __IM  uint32_t NE         : 1;            /*!< [2..2] Noise error flag                                                   */
      __IM  uint32_t ORE        : 1;            /*!< [3..3] Overrun error                                                      */
      __IM  uint32_t IDLE       : 1;            /*!< [4..4] IDLE line detected                                                 */
      __IOM uint32_t RXNE       : 1;            /*!< [5..5] Read data register not empty                                       */
      __IOM uint32_t TC         : 1;            /*!< [6..6] Transmission complete                                              */
      __IM  uint32_t TXE        : 1;            /*!< [7..7] Transmit data register empty                                       */
      __IOM uint32_t LBD        : 1;            /*!< [8..8] LIN break detection flag                                           */
      __IOM uint32_t CTS        : 1;            /*!< [9..9] CTS flag                                                           */
    } bit;
  } STATR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Data register                                              */
    
    struct {
      __IOM uint32_t DR         : 9;            /*!< [8..0] Data value                                                         */
    } bit;
  } DATAR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) Baud rate register                                         */
    
    struct {
      __IOM uint32_t DIV_Fraction : 4;          /*!< [3..0] fraction of USARTDIV                                               */
      __IOM uint32_t DIV_Mantissa : 12;         /*!< [15..4] mantissa of USARTDIV                                              */
    } bit;
  } BRR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Control register 1                                         */
    
    struct {
      __IOM uint32_t SBK        : 1;            /*!< [0..0] Send break                                                         */
      __IOM uint32_t RWU        : 1;            /*!< [1..1] Receiver wakeup                                                    */
      __IOM uint32_t RE         : 1;            /*!< [2..2] Receiver enable                                                    */
      __IOM uint32_t TE         : 1;            /*!< [3..3] Transmitter enable                                                 */
      __IOM uint32_t IDLEIE     : 1;            /*!< [4..4] IDLE interrupt enable                                              */
      __IOM uint32_t RXNEIE     : 1;            /*!< [5..5] RXNE interrupt enable                                              */
      __IOM uint32_t TCIE       : 1;            /*!< [6..6] Transmission complete interrupt enable                             */
      __IOM uint32_t TXEIE      : 1;            /*!< [7..7] TXE interrupt enable                                               */
      __IOM uint32_t PEIE       : 1;            /*!< [8..8] PE interrupt enable                                                */
      __IOM uint32_t PS         : 1;            /*!< [9..9] Parity selection                                                   */
      __IOM uint32_t PCE        : 1;            /*!< [10..10] Parity control enable                                            */
      __IOM uint32_t WAKE       : 1;            /*!< [11..11] Wakeup method                                                    */
      __IOM uint32_t M          : 1;            /*!< [12..12] Word length                                                      */
      __IOM uint32_t UE         : 1;            /*!< [13..13] USART enable                                                     */
    } bit;
  } CTLR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) Control register 2                                         */
    
    struct {
      __IOM uint32_t ADD        : 4;            /*!< [3..0] Address of the USART node                                          */
      __IM  uint32_t            : 1;
      __IOM uint32_t LBDL       : 1;            /*!< [5..5] lin break detection length                                         */
      __IOM uint32_t LBDIE      : 1;            /*!< [6..6] LIN break detection interrupt enable                               */
      __IM  uint32_t            : 1;
      __IOM uint32_t LBCL       : 1;            /*!< [8..8] Last bit clock pulse                                               */
      __IOM uint32_t CPHA       : 1;            /*!< [9..9] Clock phase                                                        */
      __IOM uint32_t CPOL       : 1;            /*!< [10..10] Clock polarity                                                   */
      __IOM uint32_t CLKEN      : 1;            /*!< [11..11] Clock enable                                                     */
      __IOM uint32_t STOP       : 2;            /*!< [13..12] STOP bits                                                        */
      __IOM uint32_t LINEN      : 1;            /*!< [14..14] LIN mode enable                                                  */
    } bit;
  } CTLR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) Control register 3                                         */
    
    struct {
      __IOM uint32_t EIE        : 1;            /*!< [0..0] Error interrupt enable                                             */
      __IOM uint32_t IREN       : 1;            /*!< [1..1] IrDA mode enable                                                   */
      __IOM uint32_t IRLP       : 1;            /*!< [2..2] IrDA low-power                                                     */
      __IOM uint32_t HDSEL      : 1;            /*!< [3..3] Half-duplex selection                                              */
      __IOM uint32_t NACK       : 1;            /*!< [4..4] Smartcard NACK enable                                              */
      __IOM uint32_t SCEN       : 1;            /*!< [5..5] Smartcard mode enable                                              */
      __IOM uint32_t DMAR       : 1;            /*!< [6..6] DMA enable receiver                                                */
      __IOM uint32_t DMAT       : 1;            /*!< [7..7] DMA enable transmitter                                             */
      __IOM uint32_t RTSE       : 1;            /*!< [8..8] RTS enable                                                         */
      __IOM uint32_t CTSE       : 1;            /*!< [9..9] CTS enable                                                         */
      __IOM uint32_t CTSIE      : 1;            /*!< [10..10] CTS interrupt enable                                             */
    } bit;
  } CTLR3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) Guard time and prescaler register                          */
    
    struct {
      __IOM uint32_t PSC        : 8;            /*!< [7..0] Prescaler value                                                    */
      __IOM uint32_t GT         : 8;            /*!< [15..8] Guard time value                                                  */
    } bit;
  } GPR;
} USART1_Type;                                  /*!< Size = 28 (0x1c)                                                          */



/* =========================================================================================================================== */
/* ================                                           ADC1                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40012400) ADC1 Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) status register                                            */
    
    struct {
      __IOM uint32_t AWD        : 1;            /*!< [0..0] Analog watchdog flag                                               */
      __IOM uint32_t EOC        : 1;            /*!< [1..1] Regular channel end of conversion                                  */
      __IOM uint32_t JEOC       : 1;            /*!< [2..2] Injected channel end of conversion                                 */
      __IOM uint32_t JSTRT      : 1;            /*!< [3..3] Injected channel start flag                                        */
      __IOM uint32_t STRT       : 1;            /*!< [4..4] Regular channel start flag                                         */
    } bit;
  } STATR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) control register 1/TKEY_V_CTLR                             */
    
    struct {
      __IOM uint32_t AWDCH      : 5;            /*!< [4..0] Analog watchdog channel select bits                                */
      __IOM uint32_t EOCIE      : 1;            /*!< [5..5] Interrupt enable for EOC                                           */
      __IOM uint32_t AWDIE      : 1;            /*!< [6..6] Analog watchdog interrupt enable                                   */
      __IOM uint32_t JEOCIE     : 1;            /*!< [7..7] Interrupt enable for injected channels                             */
      __IOM uint32_t SCAN       : 1;            /*!< [8..8] Scan mode enable                                                   */
      __IOM uint32_t AWDSGL     : 1;            /*!< [9..9] Enable the watchdog on a single channel in scan mode               */
      __IOM uint32_t JAUTO      : 1;            /*!< [10..10] Automatic injected group conversion                              */
      __IOM uint32_t DISCEN     : 1;            /*!< [11..11] Discontinuous mode on regular channels                           */
      __IOM uint32_t JDISCEN    : 1;            /*!< [12..12] Discontinuous mode on injected channels                          */
      __IOM uint32_t DISCNUM    : 3;            /*!< [15..13] Discontinuous mode channel count                                 */
      __IOM uint32_t DUALMOD    : 4;            /*!< [19..16] Dual mode selection                                              */
      __IM  uint32_t            : 2;
      __IOM uint32_t JAWDEN     : 1;            /*!< [22..22] Analog watchdog enable on injected channels                      */
      __IOM uint32_t AWDEN      : 1;            /*!< [23..23] Analog watchdog enable on regular channels                       */
      __IOM uint32_t TKEYEN     : 1;            /*!< [24..24] TKEY enable, including TKEY_F and TKEY_V                         */
      __IOM uint32_t TKITUNE    : 1;            /*!< [25..25] TKEY_I enable                                                    */
      __IOM uint32_t BUFEN      : 1;            /*!< [26..26] TKEY_BUF_Enable                                                  */
      __IOM uint32_t PGA        : 2;            /*!< [28..27] ADC_PGA                                                          */
    } bit;
  } CTLR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) control register 2                                         */
    
    struct {
      __IOM uint32_t ADON       : 1;            /*!< [0..0] A/D converter ON / OFF                                             */
      __IOM uint32_t CONT       : 1;            /*!< [1..1] Continuous conversion                                              */
      __IOM uint32_t CAL        : 1;            /*!< [2..2] A/D calibration                                                    */
      __IOM uint32_t RSTCAL     : 1;            /*!< [3..3] Reset calibration                                                  */
      __IM  uint32_t            : 4;
      __IOM uint32_t DMA        : 1;            /*!< [8..8] Direct memory access mode                                          */
      __IM  uint32_t            : 2;
      __IOM uint32_t ALIGN      : 1;            /*!< [11..11] Data alignment                                                   */
      __IOM uint32_t JEXTSEL    : 3;            /*!< [14..12] External event select for injected group                         */
      __IOM uint32_t JEXTTRIG   : 1;            /*!< [15..15] External trigger conversion mode for injected channels           */
      __IM  uint32_t            : 1;
      __IOM uint32_t EXTSEL     : 3;            /*!< [19..17] External event select for regular group                          */
      __IOM uint32_t EXTTRIG    : 1;            /*!< [20..20] External trigger conversion mode for regular channels            */
      __IOM uint32_t JSWSTART   : 1;            /*!< [21..21] Start conversion of injected channels                            */
      __IOM uint32_t SWSTART    : 1;            /*!< [22..22] Start conversion of regular channels                             */
      __IOM uint32_t TSVREFE    : 1;            /*!< [23..23] Temperature sensor and VREFINT enable                            */
    } bit;
  } CTLR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) sample time register 1                                     */
    
    struct {
      __IOM uint32_t SMP10_TKCG10 : 3;          /*!< [2..0] Channel 10 sample time selection                                   */
      __IOM uint32_t SMP11_TKCG11 : 3;          /*!< [5..3] Channel 11 sample time selection                                   */
      __IOM uint32_t SMP12_TKCG12 : 3;          /*!< [8..6] Channel 12 sample time selection                                   */
      __IOM uint32_t SMP13_TKCG13 : 3;          /*!< [11..9] Channel 13 sample time selection                                  */
      __IOM uint32_t SMP14_TKCG14 : 3;          /*!< [14..12] Channel 14 sample time selection                                 */
      __IOM uint32_t SMP15_TKCG15 : 3;          /*!< [17..15] Channel 15 sample time selection                                 */
      __IOM uint32_t SMP16_TKCG16 : 3;          /*!< [20..18] Channel 16 sample time selection                                 */
      __IOM uint32_t SMP17_TKCG17 : 3;          /*!< [23..21] Channel 17 sample time selection                                 */
    } bit;
  } SAMPTR1_CHARGE1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) sample time register 2                                     */
    
    struct {
      __IOM uint32_t SMP0_TKCG0 : 3;            /*!< [2..0] Channel 0 sample time selection                                    */
      __IOM uint32_t SMP1_TKCG1 : 3;            /*!< [5..3] Channel 1 sample time selection                                    */
      __IOM uint32_t SMP2_TKCG2 : 3;            /*!< [8..6] Channel 2 sample time selection                                    */
      __IOM uint32_t SMP3_TKCG3 : 3;            /*!< [11..9] Channel 3 sample time selection                                   */
      __IOM uint32_t SMP4_TKCG4 : 3;            /*!< [14..12] Channel 4 sample time selection                                  */
      __IOM uint32_t SMP5_TKCG5 : 3;            /*!< [17..15] Channel 5 sample time selection                                  */
      __IOM uint32_t SMP6_TKCG6 : 3;            /*!< [20..18] Channel 6 sample time selection                                  */
      __IOM uint32_t SMP7_TKCG7 : 3;            /*!< [23..21] Channel 7 sample time selection                                  */
      __IOM uint32_t SMP8_TKCG8 : 3;            /*!< [26..24] Channel 8 sample time selection                                  */
      __IOM uint32_t SMP9_TKCG9 : 3;            /*!< [29..27] Channel 9 sample time selection                                  */
    } bit;
  } SAMPTR2_CHARGE2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) injected channel data offset register x                    */
    
    struct {
      __IOM uint32_t JOFFSET1   : 12;           /*!< [11..0] Data offset for injected channel x                                */
    } bit;
  } IOFR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) injected channel data offset register x                    */
    
    struct {
      __IOM uint32_t JOFFSET2   : 12;           /*!< [11..0] Data offset for injected channel x                                */
    } bit;
  } IOFR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) injected channel data offset register x                    */
    
    struct {
      __IOM uint32_t JOFFSET3   : 12;           /*!< [11..0] Data offset for injected channel x                                */
    } bit;
  } IOFR3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) injected channel data offset register x                    */
    
    struct {
      __IOM uint32_t JOFFSET4   : 12;           /*!< [11..0] Data offset for injected channel x                                */
    } bit;
  } IOFR4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) watchdog higher threshold register                         */
    
    struct {
      __IOM uint32_t HT         : 12;           /*!< [11..0] Analog watchdog higher threshold                                  */
    } bit;
  } WDHTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) watchdog lower threshold register                          */
    
    struct {
      __IOM uint32_t LT         : 12;           /*!< [11..0] Analog watchdog lower threshold                                   */
    } bit;
  } WDLTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) regular sequence register 1                                */
    
    struct {
      __IOM uint32_t SQ13       : 5;            /*!< [4..0] 13th conversion in regular sequence                                */
      __IOM uint32_t SQ14       : 5;            /*!< [9..5] 14th conversion in regular sequence                                */
      __IOM uint32_t SQ15       : 5;            /*!< [14..10] 15th conversion in regular sequence                              */
      __IOM uint32_t SQ16       : 5;            /*!< [19..15] 16th conversion in regular sequence                              */
      __IOM uint32_t L          : 4;            /*!< [23..20] Regular channel sequence length                                  */
    } bit;
  } RSQR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) regular sequence register 2                                */
    
    struct {
      __IOM uint32_t SQ7        : 5;            /*!< [4..0] 7th conversion in regular sequence                                 */
      __IOM uint32_t SQ8        : 5;            /*!< [9..5] 8th conversion in regular sequence                                 */
      __IOM uint32_t SQ9        : 5;            /*!< [14..10] 9th conversion in regular sequence                               */
      __IOM uint32_t SQ10       : 5;            /*!< [19..15] 10th conversion in regular sequence                              */
      __IOM uint32_t SQ11       : 5;            /*!< [24..20] 11th conversion in regular sequence                              */
      __IOM uint32_t SQ12       : 5;            /*!< [29..25] 12th conversion in regular sequence                              */
    } bit;
  } RSQR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) regular sequence register 3;TKEY_V_CHANNEL                 */
    
    struct {
      __IOM uint32_t SQ1__CHSEL : 5;            /*!< [4..0] 1st conversion in regular sequence;TKDY_V channel select           */
      __IOM uint32_t SQ2        : 5;            /*!< [9..5] 2nd conversion in regular sequence                                 */
      __IOM uint32_t SQ3        : 5;            /*!< [14..10] 3rd conversion in regular sequence                               */
      __IOM uint32_t SQ4        : 5;            /*!< [19..15] 4th conversion in regular sequence                               */
      __IOM uint32_t SQ5        : 5;            /*!< [24..20] 5th conversion in regular sequence                               */
      __IOM uint32_t SQ6        : 5;            /*!< [29..25] 6th conversion in regular sequence                               */
    } bit;
  } RSQR3__CHANNEL;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) injected sequence register                                 */
    
    struct {
      __IOM uint32_t JSQ1       : 5;            /*!< [4..0] 1st conversion in injected sequence                                */
      __IOM uint32_t JSQ2       : 5;            /*!< [9..5] 2nd conversion in injected sequence                                */
      __IOM uint32_t JSQ3       : 5;            /*!< [14..10] 3rd conversion in injected sequence                              */
      __IOM uint32_t JSQ4       : 5;            /*!< [19..15] 4th conversion in injected sequence                              */
      __IOM uint32_t JL         : 2;            /*!< [21..20] Injected sequence length                                         */
    } bit;
  } ISQR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x0000003C) injected data register x_Charge data offset for
                                                                    injected channel x                                         */
    
    struct {
      __IM  uint32_t IDATA0_7_TKCGOFFSET : 8;   /*!< [7..0] Injected data_Touch key charge data offset for injected
                                                     channel x                                                                 */
      __IM  uint32_t IDATA8_15  : 8;            /*!< [15..8] Injected data                                                     */
    } bit;
  } IDATAR1_CHGOFFSET;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000040) injected data register x                                   */
    
    struct {
      __IM  uint32_t JDATA      : 16;           /*!< [15..0] Injected data                                                     */
    } bit;
  } IDATAR2;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000044) injected data register x                                   */
    
    struct {
      __IM  uint32_t JDATA      : 16;           /*!< [15..0] Injected data                                                     */
    } bit;
  } IDATAR3;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000048) injected data register x                                   */
    
    struct {
      __IM  uint32_t JDATA      : 16;           /*!< [15..0] Injected data                                                     */
    } bit;
  } IDATAR4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) regular data register_start and discharge time
                                                                    register                                                   */
    
    struct {
      __IOM uint32_t DATA0_7_TKACT_DCG : 8;     /*!< [7..0] Regular data_Touch key start and discharge time register           */
      __IOM uint32_t DATA8_15   : 8;            /*!< [15..8] Regular data                                                      */
    } bit;
  } RDATAR_DR_ACT_DCG;
} ADC1_Type;                                    /*!< Size = 80 (0x50)                                                          */



/* =========================================================================================================================== */
/* ================                                           ADC2                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40012800) ADC2 Structure                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) status register                                            */
    
    struct {
      __IOM uint32_t AWD        : 1;            /*!< [0..0] Analog watchdog flag                                               */
      __IOM uint32_t EOC        : 1;            /*!< [1..1] Regular channel end of conversion                                  */
      __IOM uint32_t JEOC       : 1;            /*!< [2..2] Injected channel end of conversion                                 */
      __IOM uint32_t JSTRT      : 1;            /*!< [3..3] Injected channel start flag                                        */
      __IOM uint32_t STRT       : 1;            /*!< [4..4] Regular channel start flag                                         */
    } bit;
  } STATR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) control register 1/TKEY_V_CTLR                             */
    
    struct {
      __IOM uint32_t AWDCH      : 5;            /*!< [4..0] Analog watchdog channel select bits                                */
      __IOM uint32_t EOCIE      : 1;            /*!< [5..5] Interrupt enable for EOC                                           */
      __IOM uint32_t AWDIE      : 1;            /*!< [6..6] Analog watchdog interrupt enable                                   */
      __IOM uint32_t JEOCIE     : 1;            /*!< [7..7] Interrupt enable for injected channels                             */
      __IOM uint32_t SCAN       : 1;            /*!< [8..8] Scan mode enable                                                   */
      __IOM uint32_t AWDSGL     : 1;            /*!< [9..9] Enable the watchdog on a single channel in scan mode               */
      __IOM uint32_t JAUTO      : 1;            /*!< [10..10] Automatic injected group conversion                              */
      __IOM uint32_t DISCEN     : 1;            /*!< [11..11] Discontinuous mode on regular channels                           */
      __IOM uint32_t JDISCEN    : 1;            /*!< [12..12] Discontinuous mode on injected channels                          */
      __IOM uint32_t DISCNUM    : 3;            /*!< [15..13] Discontinuous mode channel count                                 */
      __IOM uint32_t DUALMOD    : 4;            /*!< [19..16] Dual mode selection                                              */
      __IM  uint32_t            : 2;
      __IOM uint32_t JAWDEN     : 1;            /*!< [22..22] Analog watchdog enable on injected channels                      */
      __IOM uint32_t AWDEN      : 1;            /*!< [23..23] Analog watchdog enable on regular channels                       */
      __IOM uint32_t TKEYEN     : 1;            /*!< [24..24] TKEY enable, including TKEY_F and TKEY_V                         */
      __IOM uint32_t TKITUNE    : 1;            /*!< [25..25] TKEY_I enable                                                    */
      __IOM uint32_t BUFEN      : 1;            /*!< [26..26] TKEY_BUF_Enable                                                  */
      __IOM uint32_t PGA        : 2;            /*!< [28..27] ADC_PGA                                                          */
    } bit;
  } CTLR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000008) control register 2                                         */
    
    struct {
      __IOM uint32_t ADON       : 1;            /*!< [0..0] A/D converter ON / OFF                                             */
      __IOM uint32_t CONT       : 1;            /*!< [1..1] Continuous conversion                                              */
      __IOM uint32_t CAL        : 1;            /*!< [2..2] A/D calibration                                                    */
      __IOM uint32_t RSTCAL     : 1;            /*!< [3..3] Reset calibration                                                  */
      __IM  uint32_t            : 4;
      __IOM uint32_t DMA        : 1;            /*!< [8..8] Direct memory access mode                                          */
      __IM  uint32_t            : 2;
      __IOM uint32_t ALIGN      : 1;            /*!< [11..11] Data alignment                                                   */
      __IOM uint32_t JEXTSEL    : 3;            /*!< [14..12] External event select for injected group                         */
      __IOM uint32_t JEXTTRIG   : 1;            /*!< [15..15] External trigger conversion mode for injected channels           */
      __IM  uint32_t            : 1;
      __IOM uint32_t EXTSEL     : 3;            /*!< [19..17] External event select for regular group                          */
      __IOM uint32_t EXTTRIG    : 1;            /*!< [20..20] External trigger conversion mode for regular channels            */
      __IOM uint32_t JSWSTART   : 1;            /*!< [21..21] Start conversion of injected channels                            */
      __IOM uint32_t SWSTART    : 1;            /*!< [22..22] Start conversion of regular channels                             */
      __IOM uint32_t TSVREFE    : 1;            /*!< [23..23] Temperature sensor and VREFINT enable                            */
    } bit;
  } CTLR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) sample time register 1                                     */
    
    struct {
      __IOM uint32_t SMP10_TKCG10 : 3;          /*!< [2..0] Channel 10 sample time selection                                   */
      __IOM uint32_t SMP11_TKCG11 : 3;          /*!< [5..3] Channel 11 sample time selection                                   */
      __IOM uint32_t SMP12_TKCG12 : 3;          /*!< [8..6] Channel 12 sample time selection                                   */
      __IOM uint32_t SMP13_TKCG13 : 3;          /*!< [11..9] Channel 13 sample time selection                                  */
      __IOM uint32_t SMP14_TKCG14 : 3;          /*!< [14..12] Channel 14 sample time selection                                 */
      __IOM uint32_t SMP15_TKCG15 : 3;          /*!< [17..15] Channel 15 sample time selection                                 */
      __IOM uint32_t SMP16_TKCG16 : 3;          /*!< [20..18] Channel 16 sample time selection                                 */
      __IOM uint32_t SMP17_TKCG17 : 3;          /*!< [23..21] Channel 17 sample time selection                                 */
    } bit;
  } SAMPTR1_CHARGE1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) sample time register 2                                     */
    
    struct {
      __IOM uint32_t SMP0_TKCG0 : 3;            /*!< [2..0] Channel 0 sample time selection                                    */
      __IOM uint32_t SMP1_TKCG1 : 3;            /*!< [5..3] Channel 1 sample time selection                                    */
      __IOM uint32_t SMP2_TKCG2 : 3;            /*!< [8..6] Channel 2 sample time selection                                    */
      __IOM uint32_t SMP3_TKCG3 : 3;            /*!< [11..9] Channel 3 sample time selection                                   */
      __IOM uint32_t SMP4_TKCG4 : 3;            /*!< [14..12] Channel 4 sample time selection                                  */
      __IOM uint32_t SMP5_TKCG5 : 3;            /*!< [17..15] Channel 5 sample time selection                                  */
      __IOM uint32_t SMP6_TKCG6 : 3;            /*!< [20..18] Channel 6 sample time selection                                  */
      __IOM uint32_t SMP7_TKCG7 : 3;            /*!< [23..21] Channel 7 sample time selection                                  */
      __IOM uint32_t SMP8_TKCG8 : 3;            /*!< [26..24] Channel 8 sample time selection                                  */
      __IOM uint32_t SMP9_TKCG9 : 3;            /*!< [29..27] Channel 9 sample time selection                                  */
    } bit;
  } SAMPTR2_CHARGE2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) injected channel data offset register x                    */
    
    struct {
      __IOM uint32_t JOFFSET1   : 12;           /*!< [11..0] Data offset for injected channel x                                */
    } bit;
  } IOFR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) injected channel data offset register x                    */
    
    struct {
      __IOM uint32_t JOFFSET2   : 12;           /*!< [11..0] Data offset for injected channel x                                */
    } bit;
  } IOFR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000001C) injected channel data offset register x                    */
    
    struct {
      __IOM uint32_t JOFFSET3   : 12;           /*!< [11..0] Data offset for injected channel x                                */
    } bit;
  } IOFR3;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000020) injected channel data offset register x                    */
    
    struct {
      __IOM uint32_t JOFFSET4   : 12;           /*!< [11..0] Data offset for injected channel x                                */
    } bit;
  } IOFR4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000024) watchdog higher threshold register                         */
    
    struct {
      __IOM uint32_t HT         : 12;           /*!< [11..0] Analog watchdog higher threshold                                  */
    } bit;
  } WDHTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000028) watchdog lower threshold register                          */
    
    struct {
      __IOM uint32_t LT         : 12;           /*!< [11..0] Analog watchdog lower threshold                                   */
    } bit;
  } WDLTR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000002C) regular sequence register 1                                */
    
    struct {
      __IOM uint32_t SQ13       : 5;            /*!< [4..0] 13th conversion in regular sequence                                */
      __IOM uint32_t SQ14       : 5;            /*!< [9..5] 14th conversion in regular sequence                                */
      __IOM uint32_t SQ15       : 5;            /*!< [14..10] 15th conversion in regular sequence                              */
      __IOM uint32_t SQ16       : 5;            /*!< [19..15] 16th conversion in regular sequence                              */
      __IOM uint32_t L          : 4;            /*!< [23..20] Regular channel sequence length                                  */
    } bit;
  } RSQR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000030) regular sequence register 2                                */
    
    struct {
      __IOM uint32_t SQ7        : 5;            /*!< [4..0] 7th conversion in regular sequence                                 */
      __IOM uint32_t SQ8        : 5;            /*!< [9..5] 8th conversion in regular sequence                                 */
      __IOM uint32_t SQ9        : 5;            /*!< [14..10] 9th conversion in regular sequence                               */
      __IOM uint32_t SQ10       : 5;            /*!< [19..15] 10th conversion in regular sequence                              */
      __IOM uint32_t SQ11       : 5;            /*!< [24..20] 11th conversion in regular sequence                              */
      __IOM uint32_t SQ12       : 5;            /*!< [29..25] 12th conversion in regular sequence                              */
    } bit;
  } RSQR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000034) regular sequence register 3;TKEY_V_CHANNEL                 */
    
    struct {
      __IOM uint32_t SQ1__CHSEL : 5;            /*!< [4..0] 1st conversion in regular sequence;TKDY_V channel select           */
      __IOM uint32_t SQ2        : 5;            /*!< [9..5] 2nd conversion in regular sequence                                 */
      __IOM uint32_t SQ3        : 5;            /*!< [14..10] 3rd conversion in regular sequence                               */
      __IOM uint32_t SQ4        : 5;            /*!< [19..15] 4th conversion in regular sequence                               */
      __IOM uint32_t SQ5        : 5;            /*!< [24..20] 5th conversion in regular sequence                               */
      __IOM uint32_t SQ6        : 5;            /*!< [29..25] 6th conversion in regular sequence                               */
    } bit;
  } RSQR3__CHANNEL;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000038) injected sequence register                                 */
    
    struct {
      __IOM uint32_t JSQ1       : 5;            /*!< [4..0] 1st conversion in injected sequence                                */
      __IOM uint32_t JSQ2       : 5;            /*!< [9..5] 2nd conversion in injected sequence                                */
      __IOM uint32_t JSQ3       : 5;            /*!< [14..10] 3rd conversion in injected sequence                              */
      __IOM uint32_t JSQ4       : 5;            /*!< [19..15] 4th conversion in injected sequence                              */
      __IOM uint32_t JL         : 2;            /*!< [21..20] Injected sequence length                                         */
    } bit;
  } ISQR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x0000003C) injected data register x_Charge data offset for
                                                                    injected channel x                                         */
    
    struct {
      __IM  uint32_t IDATA0_7_TKCGOFFSET : 8;   /*!< [7..0] Injected data_Touch key charge data offset for injected
                                                     channel x                                                                 */
      __IM  uint32_t IDATA8_15  : 8;            /*!< [15..8] Injected data                                                     */
    } bit;
  } IDATAR1_CHGOFFSET;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000040) injected data register x                                   */
    
    struct {
      __IM  uint32_t JDATA      : 16;           /*!< [15..0] Injected data                                                     */
    } bit;
  } IDATAR2;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000044) injected data register x                                   */
    
    struct {
      __IM  uint32_t JDATA      : 16;           /*!< [15..0] Injected data                                                     */
    } bit;
  } IDATAR3;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000048) injected data register x                                   */
    
    struct {
      __IM  uint32_t JDATA      : 16;           /*!< [15..0] Injected data                                                     */
    } bit;
  } IDATAR4;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000004C) regular data register_start and discharge time
                                                                    register                                                   */
    
    struct {
      __IOM uint32_t DATA0_7_TKACT_DCG : 8;     /*!< [7..0] Regular data_Touch key start and discharge time register           */
      __IOM uint32_t DATA8_15   : 8;            /*!< [15..8] Regular data                                                      */
    } bit;
  } RDATAR_DR_ACT_DCG;
} ADC2_Type;                                    /*!< Size = 80 (0x50)                                                          */



/* =========================================================================================================================== */
/* ================                                            DBG                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0xE000D000) DBG Structure                                              */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) DBGMCU_CFGR1                                               */
    
    struct {
      __IOM uint32_t DEG_IWDG   : 1;            /*!< [0..0] DEG_IWDG                                                           */
      __IOM uint32_t DEG_WWDG   : 1;            /*!< [1..1] DEG_WWDG                                                           */
      __IOM uint32_t DEG_I2C1   : 1;            /*!< [2..2] DEG_I2C1                                                           */
      __IOM uint32_t DEG_I2C2   : 1;            /*!< [3..3] DEG_I2C2                                                           */
      __IOM uint32_t DEG_TIM1   : 1;            /*!< [4..4] DEG_TIM1                                                           */
      __IOM uint32_t DEG_TIM2   : 1;            /*!< [5..5] DEG_TIM2                                                           */
      __IOM uint32_t DEG_TIM3   : 1;            /*!< [6..6] DEG_TIM3                                                           */
      __IOM uint32_t DEG_TIM4   : 1;            /*!< [7..7] DEG_TIM4                                                           */
    } bit;
  } CFGR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) DBGMCU_CFGR2                                               */
    
    struct {
      __IOM uint32_t DBG_SLEEP  : 1;            /*!< [0..0] DBG_SLEEP                                                          */
      __IOM uint32_t DBG_STOP   : 1;            /*!< [1..1] DBG_STOP                                                           */
      __IOM uint32_t DBG_STANDBY : 1;           /*!< [2..2] DBG_STANDBY                                                        */
    } bit;
  } CFGR2;
} DBG_Type;                                     /*!< Size = 8 (0x8)                                                            */



/* =========================================================================================================================== */
/* ================                                           USBHD                                           ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40023400) USBHD Structure                                            */
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000000) USB base control                                           */
    
    struct {
      __IOM uint8_t RB_UC_DMA_EN : 1;           /*!< [0..0] DMA enable and DMA interrupt enable for USB                        */
      __IOM uint8_t RB_UC_CLR_ALL : 1;          /*!< [1..1] force clear FIFO and count of USB                                  */
      __IOM uint8_t RB_UC_RESET_SIE : 1;        /*!< [2..2] force reset USB SIE, need software clear                           */
      __IOM uint8_t RB_UC_INT_BUSY : 1;         /*!< [3..3] enable automatic responding busy for device mode or automatic
                                                     pause for host mode during interrupt flag UIF_TRANSFER
                                                     valid                                                                     */
      __IOM uint8_t RB_UC_DEV_PU_EN : 1;        /*!< [4..4] USB device enable and internal pullup resistance enable            */
      __IOM uint8_t RB_UC_SPEED_TYPE : 2;       /*!< [6..5] enable USB low speed: 00=full speed, 01=high speed, 10
                                                     =low speed                                                                */
      __IOM uint8_t RB_UC_HOST_MODE : 1;        /*!< [7..7] enable USB host mode: 0=device mode, 1=host mode                   */
    } bit;
  } USB_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000001) USB HOST control                                           */
    
    struct {
      __IOM uint8_t bUH_TX_BUS_RESET : 1;       /*!< [0..0] USB host bus reset status                                          */
      __IOM uint8_t bUH_TX_BUS_SUSPEND : 1;     /*!< [1..1] the host sends hang sigal                                          */
      __IOM uint8_t bUH_TX_BUS_RESUME : 1;      /*!< [2..2] host wake up device                                                */
      __IOM uint8_t bUH_REMOTE_WKUP : 1;        /*!< [3..3] the remoke wake-up                                                 */
      __IOM uint8_t bUH_PHY_SUSPENDM : 1;       /*!< [4..4] USB-PHY thesuspended state the internal USB-PLL is turned
                                                     off                                                                       */
      __IM  uint8_t             : 1;
      __IM  uint8_t bUH_SOF_FREE : 1;           /*!< [6..6] the bus is idle                                                    */
      __IOM uint8_t bUH_SOF_EN  : 1;            /*!< [7..7] automatically generate the SOF packet enabling control
                                                     bit                                                                       */
    } bit;
  } UHOST_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000002) USB interrupt enable                                       */
    
    struct {
      __IOM uint8_t RB_UIE_BUS_RST__RB_UIE_DETECT : 1;/*!< [0..0] enable interrupt for USB bus reset event for USB device
                                                     mode;enable interrupt for USB device detected event for
                                                     USB host mode                                                             */
      __IOM uint8_t RB_UIE_TRANSFER : 1;        /*!< [1..1] enable interrupt for USB transfer completion                       */
      __IOM uint8_t RB_UIE_SUSPEND : 1;         /*!< [2..2] enable interrupt for USB suspend or resume event                   */
      __IOM uint8_t RB_UIE_SOF_ACT : 1;         /*!< [3..3] indicate host SOF timer action status for USB host                 */
      __IOM uint8_t RB_UIE_FIFO_OV : 1;         /*!< [4..4] enable interrupt for FIFO overflow                                 */
      __IOM uint8_t RB_UIE_SETUP_ACT : 1;       /*!< [5..5] indicate host SETUP timer action status for USB host               */
      __IOM uint8_t RB_UIE_ISO_ACT : 1;         /*!< [6..6] enable interrupt for NAK responded for USB device mode             */
      __IOM uint8_t RB_UIE_DEV_NAK : 1;         /*!< [7..7] enable interrupt for NAK responded for USB device mode             */
    } bit;
  } USB_INT_EN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000003) USB device address                                         */
    
    struct {
      __IOM uint8_t MASK_USB_ADDR : 7;          /*!< [6..0] bit mask for USB device address                                    */
      __IOM uint8_t RB_UDA_GP_BIT : 1;          /*!< [7..7] general purpose bit                                                */
    } bit;
  } USB_DEV_AD;
  
  union {
    __IM  uint16_t reg;                         /*!< (@ 0x00000004) USB_FRAME_NO                                               */
    
    struct {
      __IM  uint16_t USB_FRAME_NO : 16;         /*!< [15..0] USB_FRAME_NO                                                      */
    } bit;
  } USB_FRAME_NO;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000006) indicate USB suspend status                                */
    
    struct {
      __IOM uint8_t USB_SYS_MOD : 2;            /*!< [1..0] USB_SYS_MOD                                                        */
      __IOM uint8_t USB_WAKEUP  : 1;            /*!< [2..2] remote resume                                                      */
      __IM  uint8_t             : 1;
      __IOM uint8_t USB_LINESTATE : 2;          /*!< [5..4] USB_LINESTATE                                                      */
    } bit;
  } USB_USB_SUSPEND;
  __IM  uint8_t   RESERVED;
  
  union {
    __IM  uint8_t reg;                          /*!< (@ 0x00000008) USB_SPEED_TYPE                                             */
    
    struct {
      __IM  uint8_t USB_SPEED_TYPE : 2;         /*!< [1..0] USB_SPEED_TYPE                                                     */
    } bit;
  } USB_SPEED_TYPE;
  
  union {
    __IM  uint8_t reg;                          /*!< (@ 0x00000009) USB miscellaneous status                                   */
    
    struct {
      __IM  uint8_t RB_UMS_SPLIT_CAN : 1;       /*!< [0..0] RO, indicate device attached status on USB host                    */
      __IM  uint8_t RB_UMS_ATTACH : 1;          /*!< [1..1] RO, indicate UDM level saved at device attached to USB
                                                     host                                                                      */
      __IM  uint8_t RB_UMS_SUSPEND : 1;         /*!< [2..2] RO, indicate USB suspend status                                    */
      __IM  uint8_t RB_UMS_BUS_RESET : 1;       /*!< [3..3] RO, indicate USB bus reset status                                  */
      __IM  uint8_t RB_UMS_R_FIFO_RDY : 1;      /*!< [4..4] RO, indicate USB receiving FIFO ready status (not empty)           */
      __IM  uint8_t RB_UMS_SIE_FREE : 1;        /*!< [5..5] RO, indicate USB SIE free status                                   */
      __IM  uint8_t RB_UMS_SOF_ACT : 1;         /*!< [6..6] RO, indicate host SOF timer action status for USB host             */
      __IM  uint8_t RB_UMS_SOF_PRES : 1;        /*!< [7..7] RO, indicate host SOF timer presage status                         */
    } bit;
  } USB_MIS_ST;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000000A) USB interrupt flag                                         */
    
    struct {
      __IOM uint8_t RB_UIF_BUS_RST : 1;         /*!< [0..0] RB_UIF_BUS_RST                                                     */
      __IOM uint8_t RB_UIF_TRANSFER : 1;        /*!< [1..1] USB transfer completion interrupt flag, direct bit address
                                                     clear or write 1 to clear                                                 */
      __IOM uint8_t RB_UIF_SUSPEND : 1;         /*!< [2..2] USB suspend or resume event interrupt flag, direct bit
                                                     address clear or write 1 to clear                                         */
      __IOM uint8_t RB_UIF_HST_SOF : 1;         /*!< [3..3] host SOF timer interrupt flag for USB host, direct bit
                                                     address clear or write 1 to clear                                         */
      __IOM uint8_t RB_UIF_FIFO_OV : 1;         /*!< [4..4] FIFO overflow interrupt flag for USB, direct bit address
                                                     clear or write 1 to clear                                                 */
      __IM  uint8_t RB_U_SETUP_ACT : 1;         /*!< [5..5] USB_SETUP_ACT                                                      */
      __IM  uint8_t UIF_ISO_ACT : 1;            /*!< [6..6] UIF_ISO_ACT                                                        */
      __IM  uint8_t RB_U_IS_NAK : 1;            /*!< [7..7] RO, indicate current USB transfer is NAK received                  */
    } bit;
  } USB_INT_FG;
  
  union {
    __IM  uint8_t reg;                          /*!< (@ 0x0000000B) USB interrupt status                                       */
    
    struct {
      __IM  uint8_t MASK_UIS_H_RES__MASK_UIS_ENDP : 4;/*!< [3..0] RO, bit mask of current transfer handshake response for
                                                     USB host mode: 0000=no response, time out from device,
                                                     others=handshake response PID received;RO, bit mask of
                                                     current transfer endpoint number for USB device mode                      */
      __IM  uint8_t MASK_UIS_TOKEN : 2;         /*!< [5..4] RO, bit mask of current token PID code received for USB
                                                     device mode                                                               */
      __IM  uint8_t RB_UIS_TOG_OK : 1;          /*!< [6..6] RO, indicate current USB transfer toggle is OK                     */
      __IM  uint8_t RB_UIS_IS_NAK : 1;          /*!< [7..7] RO, indicate current USB transfer is NAK received for
                                                     USB device mode                                                           */
    } bit;
  } USB_INT_ST;
  
  union {
    __IM  uint16_t reg;                         /*!< (@ 0x0000000C) USB receiving length                                       */
    
    struct {
      __IM  uint16_t R16_USB_RX_LEN : 16;       /*!< [15..0] length of received bytes                                          */
    } bit;
  } USB_RX_LEN;
  __IM  uint16_t  RESERVED1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) USB endpoint configuration                                 */
    
    struct {
      __IM  uint32_t            : 1;
      __IOM uint32_t bUEP_T_EN_bUH_TX_EN : 15;  /*!< [15..1] endpoint TX enable/bUH_TX_EN                                      */
      __IM  uint32_t            : 1;
      __IOM uint32_t bUEP_R_EN__UH_EP_MOD : 15; /*!< [31..17] endpoint RX enable/bUH_TX_EN                                     */
    } bit;
  } UEP_CONFIG;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000014) USB endpoint type                                          */
    
    struct {
      __IM  uint32_t            : 1;
      __IOM uint32_t bUEP_T_TYPE : 15;          /*!< [15..1] endpoint TX type                                                  */
      __IM  uint32_t            : 1;
      __IOM uint32_t bUEP_R_TYPE : 15;          /*!< [31..17] endpoint RX type                                                 */
    } bit;
  } UEP_TYPE;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000018) USB endpoint buffer mode                                   */
    
    struct {
      __IOM uint32_t bUEP_BUF_MOD : 16;         /*!< [15..0] buffer mode of USB endpoint                                       */
      __IOM uint32_t bUEP_ISO_BUF_MOD : 16;     /*!< [31..16] buffer mode of USB endpoint                                      */
    } bit;
  } UEP_BUF_MOD;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000001C) B endpoint 0 DMA buffer address                            */
    
    struct {
      __IOM uint16_t UEP0_DMA   : 16;           /*!< [15..0] endpoint 0 DMA buffer address                                     */
    } bit;
  } UEP0_DMA;
  __IM  uint16_t  RESERVED2;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000020) endpoint 1 DMA RX buffer address                           */
    
    struct {
      __IOM uint16_t UEP1_RX_DMA : 16;          /*!< [15..0] endpoint 1 DMA buffer address                                     */
    } bit;
  } UEP1_RX_DMA;
  __IM  uint16_t  RESERVED3;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000024) endpoint 2 DMA RX buffer address/UH_RX_DMA                 */
    
    struct {
      __IOM uint16_t UEP2_RX_DMA__UH_RX_DMA : 16;/*!< [15..0] endpoint 2 DMA buffer address                                    */
    } bit;
  } UEP2_RX_DMA__UH_RX_DMA;
  __IM  uint16_t  RESERVED4;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000028) endpoint 3 DMA RX buffer address                           */
    
    struct {
      __IOM uint16_t UEP3_RX_DMA : 16;          /*!< [15..0] endpoint 3 DMA buffer address                                     */
    } bit;
  } UEP3_RX_DMA;
  __IM  uint16_t  RESERVED5;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000002C) endpoint 4 DMA RX buffer address                           */
    
    struct {
      __IOM uint16_t UEP4_RX_DMA : 16;          /*!< [15..0] endpoint 4 DMA buffer address                                     */
    } bit;
  } UEP4_RX_DMA;
  __IM  uint16_t  RESERVED6;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000030) endpoint 5 DMA RX buffer address                           */
    
    struct {
      __IOM uint16_t UEP5_DMA   : 16;           /*!< [15..0] endpoint 5 DMA buffer address                                     */
    } bit;
  } UEP5_RX_DMA;
  __IM  uint16_t  RESERVED7;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000034) endpoint 6 DMA RX buffer address                           */
    
    struct {
      __IOM uint16_t UEP6_RX_DMA : 16;          /*!< [15..0] endpoint 6 DMA buffer address                                     */
    } bit;
  } UEP6_RX_DMA;
  __IM  uint16_t  RESERVED8;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000038) endpoint 7 DMA RX buffer address                           */
    
    struct {
      __IOM uint16_t UEP7_RX_DMA : 16;          /*!< [15..0] endpoint 7 DMA buffer address                                     */
    } bit;
  } UEP7_RX_DMA;
  __IM  uint16_t  RESERVED9;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000003C) endpoint 8 DMA RX buffer address                           */
    
    struct {
      __IOM uint16_t UEP8_RX_DMA : 16;          /*!< [15..0] endpoint 8 DMA buffer address                                     */
    } bit;
  } UEP8_RX_DMA;
  __IM  uint16_t  RESERVED10;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000040) endpoint 9 DMA RX buffer address                           */
    
    struct {
      __IOM uint16_t UEP9_RX_DMA : 16;          /*!< [15..0] endpoint 9 DMA buffer address                                     */
    } bit;
  } UEP9_RX_DMA;
  __IM  uint16_t  RESERVED11;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000044) endpoint 10 DMA RX buffer address                          */
    
    struct {
      __IOM uint16_t UEP10_RX_DMA : 16;         /*!< [15..0] endpoint 10 DMA buffer address                                    */
    } bit;
  } UEP10_RX_DMA;
  __IM  uint16_t  RESERVED12;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000048) endpoint 11 DMA RX buffer address                          */
    
    struct {
      __IOM uint16_t UEP11_RX_DMA : 16;         /*!< [15..0] endpoint 11 DMA buffer address                                    */
    } bit;
  } UEP11_RX_DMA;
  __IM  uint16_t  RESERVED13;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000004C) endpoint 12 DMA RX buffer address                          */
    
    struct {
      __IOM uint16_t UEP12_RX_DMA : 16;         /*!< [15..0] endpoint 12 DMA buffer address                                    */
    } bit;
  } UEP12_RX_DMA;
  __IM  uint16_t  RESERVED14;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000050) endpoint 13 DMA RX buffer address                          */
    
    struct {
      __IOM uint16_t UEP13_RX_DMA : 16;         /*!< [15..0] endpoint 13 DMA buffer address                                    */
    } bit;
  } UEP13_RX_DMA;
  __IM  uint16_t  RESERVED15;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000054) endpoint 14 DMA RX buffer address                          */
    
    struct {
      __IOM uint16_t UEP14_RX_DMA : 16;         /*!< [15..0] endpoint 14 DMA buffer address                                    */
    } bit;
  } UEP14_RX_DMA;
  __IM  uint16_t  RESERVED16;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000058) endpoint 15 DMA RX buffer address                          */
    
    struct {
      __IOM uint16_t UEP15_RX_DMA : 16;         /*!< [15..0] endpoint 15 DMA buffer address                                    */
    } bit;
  } UEP15_RX_DMA;
  __IM  uint16_t  RESERVED17;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000005C) endpoint 1 DMA TX buffer address                           */
    
    struct {
      __IOM uint16_t UEP1_TX_DMA : 16;          /*!< [15..0] endpoint 1 DMA buffer address                                     */
    } bit;
  } UEP1_TX_DMA;
  __IM  uint16_t  RESERVED18;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000060) endpoint 2 DMA TX buffer address                           */
    
    struct {
      __IOM uint16_t UEP2_TX_DMA : 16;          /*!< [15..0] endpoint 2 DMA buffer address                                     */
    } bit;
  } UEP2_TX_DMA;
  __IM  uint16_t  RESERVED19;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000064) endpoint 3 DMA TX buffer address                           */
    
    struct {
      __IOM uint16_t UEP3_TX_DMA__UH_TX_DMA : 16;/*!< [15..0] endpoint 3 DMA buffer address                                    */
    } bit;
  } UEP3_TX_DMA__UH_TX_DMA;
  __IM  uint16_t  RESERVED20;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000068) endpoint 4 DMA TX buffer address                           */
    
    struct {
      __IOM uint16_t UEP4_TX_DMA : 16;          /*!< [15..0] endpoint 4 DMA buffer address                                     */
    } bit;
  } UEP4_TX_DMA;
  __IM  uint16_t  RESERVED21;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000006C) endpoint 5 DMA TX buffer address                           */
    
    struct {
      __IOM uint16_t UEP5_TX_DMA : 16;          /*!< [15..0] endpoint 5 DMA buffer address                                     */
    } bit;
  } UEP5_TX_DMA;
  __IM  uint16_t  RESERVED22;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000070) endpoint 6 DMA TX buffer address                           */
    
    struct {
      __IOM uint16_t UEP6_TX_DMA : 16;          /*!< [15..0] endpoint 6 DMA buffer address                                     */
    } bit;
  } UEP6_TX_DMA;
  __IM  uint16_t  RESERVED23;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000074) endpoint 7 DMA TX buffer address                           */
    
    struct {
      __IOM uint16_t UEP7_TX_DMA : 16;          /*!< [15..0] endpoint 7 DMA buffer address                                     */
    } bit;
  } UEP7_TX_DMA;
  __IM  uint16_t  RESERVED24;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000078) endpoint 8 DMA TX buffer address                           */
    
    struct {
      __IOM uint16_t UEP8_TX_DMA : 16;          /*!< [15..0] endpoint 8 DMA buffer address                                     */
    } bit;
  } UEP8_TX_DMA;
  __IM  uint16_t  RESERVED25;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000007C) endpoint 9 DMA TX buffer address                           */
    
    struct {
      __IOM uint16_t UEP9_TX_DMA : 16;          /*!< [15..0] endpoint 9 DMA buffer address                                     */
    } bit;
  } UEP9_TX_DMA;
  __IM  uint16_t  RESERVED26;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000080) endpoint 10 DMA TX buffer address                          */
    
    struct {
      __IOM uint16_t UEP10_TX_DMA : 16;         /*!< [15..0] endpoint 10 DMA buffer address                                    */
    } bit;
  } UEP10_TX_DMA;
  __IM  uint16_t  RESERVED27;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000084) endpoint 11 DMA TX buffer address                          */
    
    struct {
      __IOM uint16_t UEP11_TX_DMA : 16;         /*!< [15..0] endpoint 11 DMA buffer address                                    */
    } bit;
  } UEP11_TX_DMA;
  __IM  uint16_t  RESERVED28;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000088) endpoint 12 DMA TX buffer address                          */
    
    struct {
      __IOM uint16_t UEP12_TX_DMA___UH_SPLIT_DATA : 16;/*!< [15..0] endpoint 12 DMA buffer address                             */
    } bit;
  } UEP12_TX_DMA____UH_SPLIT_DATA;
  __IM  uint16_t  RESERVED29;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000008C) endpoint 13 DMA TX buffer address                          */
    
    struct {
      __IOM uint16_t UEP13_TX_DMA : 16;         /*!< [15..0] endpoint 13 DMA buffer address                                    */
    } bit;
  } UEP13_TX_DMA;
  __IM  uint16_t  RESERVED30;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000090) endpoint 14 DMA TX buffer address                          */
    
    struct {
      __IOM uint16_t UEP14_TX_DMA : 16;         /*!< [15..0] endpoint 14 DMA buffer address                                    */
    } bit;
  } UEP14_TX_DMA;
  __IM  uint16_t  RESERVED31;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000094) endpoint 15 DMA TX buffer address                          */
    
    struct {
      __IOM uint16_t UEP15_TX_DMA : 16;         /*!< [15..0] endpoint 15 DMA buffer address                                    */
    } bit;
  } UEP15_TX_DMA;
  __IM  uint16_t  RESERVED32;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000098) endpoint 0 max acceptable length                           */
    
    struct {
      __IOM uint16_t UEP0_MAX_LEN : 11;         /*!< [10..0] endpoint 0 max acceptable length                                  */
    } bit;
  } UEP0_MAX_LEN;
  __IM  uint16_t  RESERVED33;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000009C) endpoint 1 max acceptable length                           */
    
    struct {
      __IOM uint16_t UEP1_MAX_LEN : 11;         /*!< [10..0] endpoint 1 max acceptable length                                  */
    } bit;
  } UEP1_MAX_LEN;
  __IM  uint16_t  RESERVED34;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000A0) endpoint 2 max acceptable length                           */
    
    struct {
      __IOM uint16_t UEP2_MAX_LEN__UH_RX_MAX_LEN : 11;/*!< [10..0] endpoint 2 max acceptable length                            */
    } bit;
  } UEP2_MAX_LEN__UH_RX_MAX_LEN;
  __IM  uint16_t  RESERVED35;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000A4) endpoint 3 MAX_LEN TX                                      */
    
    struct {
      __IOM uint16_t UEP3_MAX_LEN : 11;         /*!< [10..0] endpoint 3 max acceptable length                                  */
    } bit;
  } UEP3_MAX_LEN;
  __IM  uint16_t  RESERVED36;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000A8) endpoint 4 max acceptable length                           */
    
    struct {
      __IOM uint16_t UEP4_MAX_LEN : 11;         /*!< [10..0] endpoint 4 max acceptable length                                  */
    } bit;
  } UEP4_MAX_LEN;
  __IM  uint16_t  RESERVED37;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000AC) endpoint 5 max acceptable length                           */
    
    struct {
      __IOM uint16_t UEP5_MAX_LEN : 11;         /*!< [10..0] endpoint 5 max acceptable length                                  */
    } bit;
  } UEP5_MAX_LEN;
  __IM  uint16_t  RESERVED38;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000B0) endpoint 6 max acceptable length                           */
    
    struct {
      __IOM uint16_t UEP6_MAX_LEN : 11;         /*!< [10..0] endpoint 6 max acceptable length                                  */
    } bit;
  } UEP6_MAX_LEN;
  __IM  uint16_t  RESERVED39;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000B4) endpoint 7 max acceptable length                           */
    
    struct {
      __IOM uint16_t UEP7_MAX_LEN : 11;         /*!< [10..0] endpoint 7 max acceptable length                                  */
    } bit;
  } UEP7_MAX_LEN;
  __IM  uint16_t  RESERVED40;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000B8) endpoint 8 max acceptable length                           */
    
    struct {
      __IOM uint16_t UEP8_MAX_LEN : 11;         /*!< [10..0] endpoint 8 max acceptable length                                  */
    } bit;
  } UEP8_MAX_LEN;
  __IM  uint16_t  RESERVED41;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000BC) endpoint 9 max acceptable length                           */
    
    struct {
      __IOM uint16_t UEP9_MAX_LEN : 11;         /*!< [10..0] endpoint 9 max acceptable length                                  */
    } bit;
  } UEP9_MAX_LEN;
  __IM  uint16_t  RESERVED42;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000C0) endpoint 10 max acceptable length                          */
    
    struct {
      __IOM uint16_t UEP10_MAX_LEN : 11;        /*!< [10..0] endpoint 10 max acceptable length                                 */
    } bit;
  } UEP10_MAX_LEN;
  __IM  uint16_t  RESERVED43;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000C4) endpoint 11 max acceptable length                          */
    
    struct {
      __IOM uint16_t UEP11_MAX_LEN : 11;        /*!< [10..0] endpoint 11 max acceptable length                                 */
    } bit;
  } UEP11_MAX_LEN;
  __IM  uint16_t  RESERVED44;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000C8) endpoint 12 max acceptable length                          */
    
    struct {
      __IOM uint16_t UEP12_MAX_LEN : 11;        /*!< [10..0] endpoint 12 max acceptable length                                 */
    } bit;
  } UEP12_MAX_LEN;
  __IM  uint16_t  RESERVED45;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000CC) endpoint 13 max acceptable length                          */
    
    struct {
      __IOM uint16_t UEP13_MAX_LEN : 11;        /*!< [10..0] endpoint 13 max acceptable length                                 */
    } bit;
  } UEP13_MAX_LEN;
  __IM  uint16_t  RESERVED46;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000D0) endpoint 14 max acceptable length                          */
    
    struct {
      __IOM uint16_t UEP14_MAX_LEN : 11;        /*!< [10..0] endpoint 14 max acceptable length                                 */
    } bit;
  } UEP14_MAX_LEN;
  __IM  uint16_t  RESERVED47;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000D4) endpoint 15 max acceptable length                          */
    
    struct {
      __IOM uint16_t UEP15_MAX_LEN : 11;        /*!< [10..0] endpoint 15 max acceptable length                                 */
    } bit;
  } UEP15_MAX_LEN;
  __IM  uint16_t  RESERVED48;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000D8) endpoint 0 send the length                                 */
    
    struct {
      __IOM uint16_t UEP0_T_LEN : 11;           /*!< [10..0] endpoint 0 send the length                                        */
    } bit;
  } UEP0_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000DA) endpoint 0 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 0 control of the send response to IN transactions         */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 0 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 0 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP0_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000DB) endpoint 0 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 0 control of the accept response to OUT transactions      */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 0 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 0 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP0_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000DC) endpoint 1 send the length                                 */
    
    struct {
      __IOM uint16_t UEP1_T_LEN : 11;           /*!< [10..0] endpoint 1 send the length                                        */
    } bit;
  } UEP1_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000DE) endpoint 1 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 1 control of the send response to IN transactions         */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 1 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 1 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP1_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000DF) endpoint 1 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 1 control of the accept response to OUT transactions      */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 1 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 1 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP1_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000E0) endpoint 2 send the length                                 */
    
    struct {
      __IOM uint16_t UEP2_T_LEN__MASK_UH_ENDP__MASK_UH_TOKEN : 11;/*!< [10..0] endpoint 2 send the length                      */
    } bit;
  } UEP2_T_LEN__UH_EP_PID;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000E2) endpoint 2 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 2 control of the send response to IN transactions         */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 2 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 2 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP2_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000E3) endpoint 2 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES__MASK_UH_R_RES : 2;/*!< [1..0] endpoint 2 control of the accept response to OUT transactions */
      __IOM uint8_t bUH_R_RES_NO : 1;           /*!< [2..2] bUH_R_RES_NO                                                       */
      __IOM uint8_t MASK_UEP_R_TOG__MASK_UH_R_TOG : 2;/*!< [4..3] endpoint 2 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO__bUH_R_AUTO_TOG : 1;/*!< [5..5] endpoint 2 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
      __IOM uint8_t bUH_R_DATA_NO : 1;          /*!< [6..6] bUH_R_DATA_NO                                                      */
    } bit;
  } UEP2_R_CTRL__UH_RX_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000E4) endpoint 3 send the length                                 */
    
    struct {
      __IOM uint16_t UEP3_T_LEN___UH_TX_LEN_H : 11;/*!< [10..0] endpoint 3 send the length                                     */
    } bit;
  } UEP3_T_LEN___UH_TX_LEN_H;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000E6) endpoint 3 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES_____MASK_UH_T_RES : 2;/*!< [1..0] endpoint 3 control of the send response to IN transactions */
      __IOM uint8_t bUH_T_RES_NO : 1;           /*!< [2..2] bUH_T_RES_NO                                                       */
      __IOM uint8_t MASK_UEP_T_TOG____MASK_UH_T_TOG : 2;/*!< [4..3] endpoint 3 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO____bUH_T_AUTO_TOG : 1;/*!< [5..5] endpoint 3 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
      __IOM uint8_t bUH_T_DATA_NO : 1;          /*!< [6..6] bUH_T_DATA_NO                                                      */
    } bit;
  } UEP3_T_CTRL___UH_TX_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000E7) endpoint 3 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 3 control of the accept response to OUT transactions      */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 3 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 3 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP3_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000E8) endpoint 4 send the length                                 */
    
    struct {
      __IOM uint16_t UEP4_T_LEN : 11;           /*!< [10..0] endpoint 0 send the length                                        */
    } bit;
  } UEP4_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000EA) endpoint 4 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 4 control of the send response to IN transactions         */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 4 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 4 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP4_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000EB) endpoint 4 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 4 control of the accept response to OUT transactions      */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 4 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 4 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP4_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000EC) endpoint 5 send the length                                 */
    
    struct {
      __IOM uint16_t UEP5_T_LEN : 11;           /*!< [10..0] endpoint 5 send the length                                        */
    } bit;
  } UEP5_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000EE) endpoint 5 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 5 control of the send response to IN transactions         */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 5 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 5 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP5_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000EF) endpoint 5 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 5 control of the accept response to OUT transactions      */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 5 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 5 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP5_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000F0) endpoint 6 send the length                                 */
    
    struct {
      __IOM uint16_t UEP6_T_LEN : 11;           /*!< [10..0] endpoint 6 send the length                                        */
    } bit;
  } UEP6_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000F2) endpoint 6 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 6 control of the send response to IN transactions         */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 6 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 6 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP6_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000F3) endpoint 6 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 6 control of the accept response to OUT transactions      */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 6 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 6 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP6_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000F4) endpoint 7 send the length                                 */
    
    struct {
      __IOM uint16_t UEP7_T_LEN : 11;           /*!< [10..0] endpoint 7 send the length                                        */
    } bit;
  } UEP7_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000F6) endpoint 7 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 7 control of the send response to IN transactions         */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 7 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 7 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP7_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000F7) endpoint 7 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 7 control of the accept response to OUT transactions      */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 7 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 7 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP7_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000F8) endpoint 8 send the length                                 */
    
    struct {
      __IOM uint16_t UEP8_T_LEN : 11;           /*!< [10..0] endpoint 8 send the length                                        */
    } bit;
  } UEP8_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000FA) endpoint 8 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 8 control of the send response to IN transactions         */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 8 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 8 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP8_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000FB) endpoint 8 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 8 control of the accept response to OUT transactions      */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 8 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 8 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP8_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x000000FC) endpoint9 send the length                                  */
    
    struct {
      __IOM uint16_t UEP9_T_LEN : 11;           /*!< [10..0] endpoint 9 send the length                                        */
    } bit;
  } UEP9_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000FE) endpoint 9 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 9 control of the send response to IN transactions         */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 9 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 9 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP9_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x000000FF) endpoint 9 send control                                    */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 9 control of the accept response to OUT transactions      */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 9 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 9 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP9_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000100) endpoint 10 send the length                                */
    
    struct {
      __IOM uint16_t UEP10_T_LEN : 11;          /*!< [10..0] endpoint 10 send the length                                       */
    } bit;
  } UEP10_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000102) endpoint 10 send control                                   */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 10 control of the send response to IN transactions        */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 10 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 10 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP10_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000103) endpoint 10 send control                                   */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 10 control of the accept response to OUT transactions     */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 10 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 10 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP10_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000104) endpoint 11 send the length                                */
    
    struct {
      __IOM uint16_t UEP0_T_LEN : 11;           /*!< [10..0] endpoint 11 send the length                                       */
    } bit;
  } UEP11_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000106) endpoint 11 send control                                   */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 11 control of the send response to IN transactions        */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 11 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 11 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP11_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000107) endpoint 11 send control                                   */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 11 control of the accept response to OUT transactions     */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 11 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 11 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP11_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000108) endpoint 12 send the length                                */
    
    struct {
      __IOM uint16_t UEP0_T_LEN : 11;           /*!< [10..0] endpoint 12 send the length                                       */
    } bit;
  } UEP12_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000010A) endpoint 12 send control                                   */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 12 control of the send response to IN transactions        */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 12 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 12 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP12_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000010B) endpoint 12 send control                                   */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 12 control of the accept response to OUT transactions     */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 12 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 12 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP12_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x0000010C) endpoint 13 send the length                                */
    
    struct {
      __IOM uint16_t UEP13_T_LEN : 11;          /*!< [10..0] endpoint 13 send the length                                       */
    } bit;
  } UEP13_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000010E) endpoint 13 send control                                   */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 13 control of the send response to IN transactions        */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 13 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 13 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP13_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000010F) endpoint 13 send control                                   */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 13 control of the accept response to OUT transactions     */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 13 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 13 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP13_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000110) endpoint 14 send the length                                */
    
    struct {
      __IOM uint16_t UEP14_T_LEN : 11;          /*!< [10..0] endpoint 14 send the length                                       */
    } bit;
  } UEP14_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000112) endpoint 14 send control                                   */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 14 control of the send response to IN transactions        */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 14 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 14 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP14_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000113) endpoint 14 send control                                   */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 14 control of the accept response to OUT transactions     */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 14 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 14 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP14_R_CTRL;
  
  union {
    __IOM uint16_t reg;                         /*!< (@ 0x00000114) endpoint 15 send the length                                */
    
    struct {
      __IOM uint16_t UEP0_T_LEN : 11;           /*!< [10..0] endpoint 15 send the length                                       */
    } bit;
  } UEP15_T_LEN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000116) endpoint 15 send control                                   */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] endpoint 15 control of the send response to IN transactions        */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_T_TOG : 2;         /*!< [4..3] endpoint 15 synchronous trigger bit for the sender to
                                                     prepare                                                                   */
      __IOM uint8_t bUEP_T_TOG_AUTO : 1;        /*!< [5..5] endpoint 15 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP15_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000117) endpoint 15 send control                                   */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] endpoint 15 control of the accept response to OUT transactions     */
      __IM  uint8_t             : 1;
      __IOM uint8_t MASK_UEP_R_TOG : 2;         /*!< [4..3] endpoint 15 synchronous trigger bit for the accept to
                                                     prepare                                                                   */
      __IM  uint8_t bUEP_R_TOG_AUTO : 1;        /*!< [5..5] endpoint 15 synchronous trigger bit automatic filp enables
                                                     the control bit                                                           */
    } bit;
  } UEP15_R_CTRL;
} USBHD_Type;                                   /*!< Size = 280 (0x118)                                                        */



/* =========================================================================================================================== */
/* ================                                            CRC                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40023000) CRC Structure                                              */
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000000) Data register                                              */
    
    struct {
      __IOM uint32_t DR         : 32;           /*!< [31..0] Data Register                                                     */
    } bit;
  } DATAR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000004) Independent Data register                                  */
    
    struct {
      __IOM uint32_t IDR        : 8;            /*!< [7..0] Independent Data register                                          */
    } bit;
  } IDATAR;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000008) Control register                                           */
    
    struct {
      __OM  uint32_t RESET      : 1;            /*!< [0..0] Reset bit                                                          */
    } bit;
  } CTLR;
} CRC_Type;                                     /*!< Size = 12 (0xc)                                                           */



/* =========================================================================================================================== */
/* ================                                           FLASH                                           ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40022000) FLASH Structure                                            */
  __IM  uint32_t  RESERVED;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000004) Flash key register                                         */
    
    struct {
      __OM  uint32_t KEYR       : 32;           /*!< [31..0] FPEC key                                                          */
    } bit;
  } KEYR;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000008) Flash option key register                                  */
    
    struct {
      __OM  uint32_t OPTKEY     : 32;           /*!< [31..0] Option byte key                                                   */
    } bit;
  } OBKEYR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000000C) Status register                                            */
    
    struct {
      __IM  uint32_t BSY        : 1;            /*!< [0..0] Busy                                                               */
      __IM  uint32_t WR_BSY     : 1;            /*!< [1..1] Quick page programming                                             */
      __IM  uint32_t            : 2;
      __IOM uint32_t WRPRTERR   : 1;            /*!< [4..4] Write protection error                                             */
      __IOM uint32_t EOP        : 1;            /*!< [5..5] End of operation                                                   */
      __IM  uint32_t            : 1;
      __IM  uint32_t ENHANCE_MOD_STA : 1;       /*!< [7..7] Enhance mode start                                                 */
    } bit;
  } STATR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000010) Control register                                           */
    
    struct {
      __IOM uint32_t PG         : 1;            /*!< [0..0] Programming                                                        */
      __IOM uint32_t PER        : 1;            /*!< [1..1] Page Erase                                                         */
      __IOM uint32_t MER        : 1;            /*!< [2..2] Mass Erase                                                         */
      __IM  uint32_t            : 1;
      __IOM uint32_t OBPG       : 1;            /*!< [4..4] Option byte programming                                            */
      __IOM uint32_t OBER       : 1;            /*!< [5..5] Option byte erase                                                  */
      __IOM uint32_t STRT       : 1;            /*!< [6..6] Start                                                              */
      __IOM uint32_t LOCK       : 1;            /*!< [7..7] Lock                                                               */
      __IM  uint32_t            : 1;
      __IOM uint32_t OBWRE      : 1;            /*!< [9..9] Option bytes write enable                                          */
      __IOM uint32_t ERRIE      : 1;            /*!< [10..10] Error interrupt enable                                           */
      __IM  uint32_t            : 1;
      __IOM uint32_t EOPIE      : 1;            /*!< [12..12] End of operation interrupt enable                                */
      __IM  uint32_t            : 2;
      __IOM uint32_t FLOCK      : 1;            /*!< [15..15] Fast programmable lock                                           */
      __IOM uint32_t PAGE_PG    : 1;            /*!< [16..16] Fast programming                                                 */
      __IOM uint32_t PAGE_ER    : 1;            /*!< [17..17] Fast erase                                                       */
      __IOM uint32_t BER32      : 1;            /*!< [18..18] Block Erase 32K                                                  */
      __IOM uint32_t BER64      : 1;            /*!< [19..19] Block Erase 64K                                                  */
      __IM  uint32_t            : 1;
      __IOM uint32_t PGSTART    : 1;            /*!< [21..21] Page Programming Start                                           */
      __IOM uint32_t RSENACT    : 1;            /*!< [22..22] Reset Flash Enhance read mode                                    */
      __IM  uint32_t            : 1;
      __IOM uint32_t ENHANCEMODE : 1;           /*!< [24..24] Flash Enhance read mode                                          */
      __IOM uint32_t SCKMODE    : 1;            /*!< [25..25] Flash SCK mode                                                   */
    } bit;
  } CTLR;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000014) Flash address register                                     */
    
    struct {
      __OM  uint32_t FAR        : 32;           /*!< [31..0] Flash Address                                                     */
    } bit;
  } ADDR;
  __IM  uint32_t  RESERVED1;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x0000001C) Option byte register                                       */
    
    struct {
      __IM  uint32_t OBERR      : 1;            /*!< [0..0] Option byte error                                                  */
      __IM  uint32_t RDPRT      : 1;            /*!< [1..1] Read protection                                                    */
      __IM  uint32_t IWDG_SW    : 1;            /*!< [2..2] IWDG_SW                                                            */
      __IM  uint32_t STOP_RST   : 1;            /*!< [3..3] STOP_RST                                                           */
      __IM  uint32_t STANDY_RST : 1;            /*!< [4..4] STANDY_RST                                                         */
      __IM  uint32_t            : 3;
      __IM  uint32_t SRAM_CODE_MODE : 2;        /*!< [9..8] SRAM_CODE_MODE                                                     */
    } bit;
  } OBR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000020) Write protection register                                  */
    
    struct {
      __IM  uint32_t WRP        : 32;           /*!< [31..0] Write protect                                                     */
    } bit;
  } WPR;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000024) Mode select register                                       */
    
    struct {
      __OM  uint32_t MODEKEYR   : 32;           /*!< [31..0] Mode select                                                       */
    } bit;
  } MODEKEYR;
} FLASH_Type;                                   /*!< Size = 40 (0x28)                                                          */



/* =========================================================================================================================== */
/* ================                                        USB_OTG_FS                                         ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x50000000) USB_OTG_FS Structure                                       */
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000000) USB base control                                           */
    
    struct {
      __IOM uint8_t USBHD_UC_DMA_EN : 1;        /*!< [0..0] DMA enable and DMA interrupt enable for USB                        */
      __IOM uint8_t USBHD_UC_CLR_ALL : 1;       /*!< [1..1] force clear FIFO and count of USB                                  */
      __IOM uint8_t USBHD_UC_RESET_SIE : 1;     /*!< [2..2] force reset USB SIE, need software clear                           */
      __IOM uint8_t USBHD_UC_INT_BUSY : 1;      /*!< [3..3] enable automatic responding busy for device mode or automatic
                                                     pause for host mode during interrupt flag UIF_TRANSFER
                                                     valid                                                                     */
      __IOM uint8_t USBHD_UC_SYS_CTRL_MASK : 2; /*!< [5..4] USB device enable and internal pullup resistance enable            */
      __IOM uint8_t USBHD_UC_LOW_SPEED : 1;     /*!< [6..6] enable USB low speed: 0=12Mbps, 1=1.5Mbps                          */
      __IOM uint8_t RB_UC_HOST_MODE : 1;        /*!< [7..7] enable USB host mode: 0=device mode, 1=host mode                   */
    } bit;
  } USBHD_BASE_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000001) USB device/host physical prot control                      */
    
    struct {
      __IOM uint8_t USBHD_UH_PORT_EN__USBHD_UD_PORT_EN : 1;/*!< [0..0] enable USB port: 0=disable, 1=enable port, automatic
                                                     disabled if USB device detached                                           */
      __IOM uint8_t USBHD_UH_BUS_RESET__USBHD_UD_GP_BIT : 1;/*!< [1..1] force clear FIFO and count of USB                      */
      __IOM uint8_t USBHD_UH_LOW_SPEED__USBHD_UD_LOW_SPEED : 1;/*!< [2..2] enable USB port low speed: 0=full speed, 1=low speed */
      __IM  uint8_t             : 1;
      __IOM uint8_t USBHD_UH_DM_PIN__USBHD_UD_DM_PIN : 1;/*!< [4..4] ReadOnly: indicate current UDM pin level                  */
      __IOM uint8_t USBHD_UH_DP_PIN__USBHD_UD_DP_PIN : 1;/*!< [5..5] USB device enable and internal pullup resistance enable   */
      __IM  uint8_t             : 1;
      __IOM uint8_t USBHD_UH_PD_DIS__USBHD_UD_PD_DIS : 1;/*!< [7..7] disable USB UDP/UDM pulldown resistance: 0=enable pulldown,
                                                     1=disable                                                                 */
    } bit;
  } USBHD_UDEV_CTRL__USBHD_UHOST_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000002) USB interrupt enable                                       */
    
    struct {
      __IOM uint8_t USBHD_UIE_BUS_RST__USBHD_UIE_DETECT : 1;/*!< [0..0] enable interrupt for USB bus reset event for USB device
                                                     mode                                                                      */
      __IOM uint8_t USBHD_UIE_TRANSFER : 1;     /*!< [1..1] enable interrupt for USB transfer completion                       */
      __IOM uint8_t USBHD_UIE_SUSPEND : 1;      /*!< [2..2] enable interrupt for USB suspend or resume event                   */
      __IOM uint8_t USBHD_UIE_HST_SOF : 1;      /*!< [3..3] enable interrupt for host SOF timer action for USB host
                                                     mode                                                                      */
      __IOM uint8_t USBHD_UIE_FIFO_OV : 1;      /*!< [4..4] enable interrupt for FIFO overflow                                 */
      __IM  uint8_t             : 1;
      __IOM uint8_t USBHD_UIE_DEV_NAK : 1;      /*!< [6..6] enable interrupt for NAK responded for USB device mode             */
      __IOM uint8_t USBHD_UIE_DEV_SOF : 1;      /*!< [7..7] enable interrupt for SOF received for USB device mode              */
    } bit;
  } R8_USB_INT_EN;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000003) USB device address                                         */
    
    struct {
      __IOM uint8_t MASK_USB_ADDR : 7;          /*!< [6..0] bit mask for USB device address                                    */
      __IOM uint8_t RB_UDA_GP_BIT : 1;          /*!< [7..7] general purpose bit                                                */
    } bit;
  } R8_USB_DEV_AD;
  __IM  uint8_t   RESERVED;
  
  union {
    __IM  uint8_t reg;                          /*!< (@ 0x00000005) USB miscellaneous status                                   */
    
    struct {
      __IM  uint8_t RB_UMS_DEV_ATTACH : 1;      /*!< [0..0] RO, indicate device attached status on USB host                    */
      __IM  uint8_t RB_UMS_DM_LEVEL : 1;        /*!< [1..1] RO, indicate UDM level saved at device attached to USB
                                                     host                                                                      */
      __IM  uint8_t RB_UMS_SUSPEND : 1;         /*!< [2..2] RO, indicate USB suspend status                                    */
      __IM  uint8_t RB_UMS_BUS_RESET : 1;       /*!< [3..3] RO, indicate USB bus reset status                                  */
      __IM  uint8_t RB_UMS_R_FIFO_RDY : 1;      /*!< [4..4] RO, indicate USB receiving FIFO ready status (not empty)           */
      __IM  uint8_t RB_UMS_SIE_FREE : 1;        /*!< [5..5] RO, indicate USB SIE free status                                   */
      __IM  uint8_t RB_UMS_SOF_ACT : 1;         /*!< [6..6] RO, indicate host SOF timer action status for USB host             */
      __IM  uint8_t RB_UMS_SOF_PRES : 1;        /*!< [7..7] RO, indicate host SOF timer presage status                         */
    } bit;
  } R8_USB_MIS_ST;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000006) USB interrupt flag                                         */
    
    struct {
      __IOM uint8_t RB_UIF_BUS_RST__RB_UIF_DETECT : 1;/*!< [0..0] bus reset event interrupt flag for USB device mode, direct
                                                     bit address clear or write 1 to clear;device detected event
                                                     interrupt flag for USB host mode, direct bit address clear
                                                     or write 1 to clear                                                       */
      __IOM uint8_t RB_UIF_TRANSFER : 1;        /*!< [1..1] USB transfer completion interrupt flag, direct bit address
                                                     clear or write 1 to clear                                                 */
      __IOM uint8_t RB_UIF_SUSPEND : 1;         /*!< [2..2] USB suspend or resume event interrupt flag, direct bit
                                                     address clear or write 1 to clear                                         */
      __IOM uint8_t RB_UIF_HST_SOF : 1;         /*!< [3..3] host SOF timer interrupt flag for USB host, direct bit
                                                     address clear or write 1 to clear                                         */
      __IOM uint8_t RB_UIF_FIFO_OV : 1;         /*!< [4..4] FIFO overflow interrupt flag for USB, direct bit address
                                                     clear or write 1 to clear                                                 */
      __IM  uint8_t RB_U_SIE_FREE : 1;          /*!< [5..5] RO, indicate USB SIE free status                                   */
      __IM  uint8_t RB_U_TOG_OK : 1;            /*!< [6..6] RO, indicate current USB transfer toggle is OK                     */
      __IM  uint8_t RB_U_IS_NAK : 1;            /*!< [7..7] RO, indicate current USB transfer is NAK received                  */
    } bit;
  } R8_USB_INT_FG;
  
  union {
    __IM  uint8_t reg;                          /*!< (@ 0x00000007) USB interrupt status                                       */
    
    struct {
      __IM  uint8_t MASK_UIS_H_RES__MASK_UIS_ENDP : 4;/*!< [3..0] RO, bit mask of current transfer handshake response for
                                                     USB host mode: 0000=no response, time out from device,
                                                     others=handshake response PID received;RO, bit mask of
                                                     current transfer endpoint number for USB device mode                      */
      __IM  uint8_t MASK_UIS_TOKEN : 2;         /*!< [5..4] RO, bit mask of current token PID code received for USB
                                                     device mode                                                               */
      __IM  uint8_t RB_UIS_TOG_OK : 1;          /*!< [6..6] RO, indicate current USB transfer toggle is OK                     */
      __IM  uint8_t RB_UIS_IS_NAK : 1;          /*!< [7..7] RO, indicate current USB transfer is NAK received for
                                                     USB device mode                                                           */
    } bit;
  } R8_USB_INT_ST;
  __IM  uint16_t  R16_USB_RX_LEN;               /*!< (@ 0x00000008) USB receiving length                                       */
  __IM  uint16_t  RESERVED1;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000000C) endpoint 4/1 mode                                          */
    
    struct {
      __IM  uint8_t             : 2;
      __IOM uint8_t RB_UEP4_TX_EN : 1;          /*!< [2..2] enable USB endpoint 4 transmittal (IN)                             */
      __IOM uint8_t RB_UEP4_RX_EN : 1;          /*!< [3..3] enable USB endpoint 4 receiving (OUT)                              */
      __IOM uint8_t RB_UEP1_BUF_MOD : 1;        /*!< [4..4] buffer mode of USB endpoint 1                                      */
      __IM  uint8_t             : 1;
      __IOM uint8_t RB_UEP1_TX_EN : 1;          /*!< [6..6] enable USB endpoint 1 transmittal (IN)                             */
      __IOM uint8_t RB_UEP1_RX_EN : 1;          /*!< [7..7] enable USB endpoint 1 receiving (OUT)                              */
    } bit;
  } R8_UEP4_1_MOD;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000000D) endpoint 2/3 mode;host endpoint mode                       */
    
    struct {
      __IOM uint8_t RB_UEP2_BUF_MOD__RB_UH_EP_RBUF_MOD : 1;/*!< [0..0] buffer mode of USB endpoint 2;buffer mode of USB host
                                                     IN endpoint                                                               */
      __IM  uint8_t             : 1;
      __IOM uint8_t RB_UEP2_TX_EN : 1;          /*!< [2..2] enable USB endpoint 2 transmittal (IN)                             */
      __IOM uint8_t RB_UEP2_RX_EN__RB_UH_EP_RX_EN : 1;/*!< [3..3] enable USB endpoint 2 receiving (OUT);enable USB host
                                                     IN endpoint receiving                                                     */
      __IOM uint8_t RB_UEP3_BUF_MOD__RB_UH_EP_TBUF_MOD : 1;/*!< [4..4] buffer mode of USB endpoint 3;buffer mode of USB host
                                                     OUT endpoint                                                              */
      __IM  uint8_t             : 1;
      __IOM uint8_t RB_UEP3_TX_EN__RB_UH_EP_TX_EN : 1;/*!< [6..6] enable USB endpoint 3 transmittal (IN);enable USB host
                                                     OUT endpoint transmittal                                                  */
      __IOM uint8_t RB_UEP3_RX_EN : 1;          /*!< [7..7] enable USB endpoint 3 receiving (OUT)                              */
    } bit;
  } R8_UEP2_3_MOD__R8_UH_EP_MOD;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000000E) endpoint 5/6 mode                                          */
    
    struct {
      __IOM uint8_t RB_UEP5_BUF_MOD : 1;        /*!< [0..0] buffer mode of USB endpoint 5                                      */
      __IM  uint8_t             : 1;
      __IOM uint8_t RB_UEP5_TX_EN : 1;          /*!< [2..2] enable USB endpoint 5 transmittal (IN)                             */
      __IOM uint8_t RB_UEP5_RX_EN : 1;          /*!< [3..3] enable USB endpoint 5 receiving (OUT)                              */
      __IOM uint8_t RB_UEP6_BUF_MOD : 1;        /*!< [4..4] buffer mode of USB endpoint 6                                      */
      __IM  uint8_t             : 1;
      __IOM uint8_t RB_UEP6_TX_EN : 1;          /*!< [6..6] enable USB endpoint 6 transmittal (IN)                             */
      __IOM uint8_t RB_UEP3_RX_EN : 1;          /*!< [7..7] enable USB endpoint 6 receiving (OUT)                              */
    } bit;
  } R8_UEP5_6_MOD;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000000F) endpoint 7 mode                                            */
    
    struct {
      __IOM uint8_t RB_UEP7_BUF_MOD : 1;        /*!< [0..0] buffer mode of USB endpoint 7                                      */
      __IM  uint8_t             : 1;
      __IOM uint8_t RB_UEP7_TX_EN : 1;          /*!< [2..2] enable USB endpoint 7 transmittal (IN)                             */
      __IOM uint8_t RB_UEP7_RX_EN : 1;          /*!< [3..3] enable USB endpoint 7 receiving (OUT)                              */
    } bit;
  } R8_UEP7_MOD;
  __IOM uint32_t  R32_UEP0_DMA;                 /*!< (@ 0x00000010) endpoint 0 DMA buffer address                              */
  __IOM uint32_t  R32_UEP1_DMA;                 /*!< (@ 0x00000014) endpoint 1 DMA buffer address                              */
  __IOM uint32_t  R32_UEP2_DMA__R32_UH_RX_DMA;  /*!< (@ 0x00000018) endpoint 2 DMA buffer address;host rx endpoint
                                                                    buffer high address                                        */
  __IOM uint32_t  R32_UEP3_DMA__R32_UH_TX_DMA;  /*!< (@ 0x0000001C) endpoint 3 DMA buffer address;host tx endpoint
                                                                    buffer high address                                        */
  __IOM uint32_t  R32_UEP4_DMA;                 /*!< (@ 0x00000020) endpoint 4 DMA buffer address                              */
  __IOM uint32_t  R32_UEP5_DMA;                 /*!< (@ 0x00000024) endpoint 5 DMA buffer address                              */
  __IOM uint32_t  R32_UEP6_DMA;                 /*!< (@ 0x00000028) endpoint 6 DMA buffer address                              */
  __IOM uint32_t  R32_UEP7_DMA;                 /*!< (@ 0x0000002C) endpoint 7 DMA buffer address                              */
  __IOM uint8_t   R8_UEP0_T_LEN;                /*!< (@ 0x00000030) endpoint 0 transmittal length                              */
  __IM  uint8_t   RESERVED2;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000032) endpoint 0 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X transmittal (IN)                                                        */
      __IOM uint8_t USBHD_UEP_T_TOG : 1;        /*!< [2..2] prepared data toggle flag of USB endpoint X transmittal
                                                     (IN): 0=DATA0, 1=DATA1                                                    */
      __IOM uint8_t USBHD_UEP_AUTO_TOG : 1;     /*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP0_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000033) endpoint 0 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X receiving (OUT)                                                         */
      __IOM uint8_t USBHD_UEP_R_TOG : 1;        /*!< [2..2] expected data toggle flag of USB endpoint X receiving
                                                     (OUT): 0=DATA0, 1=DATA1                                                   */
      __IOM uint8_t USBHD_UEP_AUTO_TOG : 1;     /*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP0_R_CTRL;
  __IOM uint8_t   R8_UEP1_T_LEN;                /*!< (@ 0x00000034) endpoint 1 transmittal length                              */
  __IM  uint8_t   RESERVED3;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000036) endpoint 1 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X transmittal (IN)                                                        */
      __IOM uint8_t USBHD_UEP_T_TOG_ : 1;       /*!< [2..2] prepared data toggle flag of USB endpoint X transmittal
                                                     (IN): 0=DATA0, 1=DATA1                                                    */
      __IOM uint8_t USBHD_UEP_AUTO_TOG : 1;     /*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
      __IM  uint8_t             : 2;
      __IOM uint8_t USBHD_UH_SOF_EN : 1;        /*!< [6..6] USB host automatic SOF enable                                      */
      __IOM uint8_t USBHD_UH_PRE_PID_EN : 1;    /*!< [7..7] USB host PRE PID enable for low speed device via hub               */
    } bit;
  } R8_UEP1_T_CTRL___USBHD_UH_SETUP;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000037) endpoint 1 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X receiving (OUT)                                                         */
      __IOM uint8_t USBHD_UEP_R_TOG : 1;        /*!< [2..2] expected data toggle flag of USB endpoint X receiving
                                                     (OUT): 0=DATA0, 1=DATA1                                                   */
      __IOM uint8_t USBHD_UEP_AUTO_TOG : 1;     /*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP1_R_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000038) endpoint 2 transmittal length                              */
    
    struct {
      __IOM uint8_t USBHD_UH_ENDP_MASK : 4;     /*!< [3..0] bit mask of endpoint number for USB host transfer                  */
      __IOM uint8_t USBHD_UH_TOKEN_MASK : 4;    /*!< [7..4] bit mask of token PID for USB host transfer                        */
    } bit;
  } R8_UEP2_T_LEN__USBHD_UH_EP_PID;
  __IM  uint8_t   RESERVED4;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000003A) endpoint 2 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X transmittal (IN)                                                        */
      __IOM uint8_t USBHD_UEP_T_TOG_ : 1;       /*!< [2..2] prepared data toggle flag of USB endpoint X transmittal
                                                     (IN): 0=DATA0, 1=DATA1                                                    */
      __IOM uint8_t USBHD_UEP_AUTO_TOG : 1;     /*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP2_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000003B) endpoint 2 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES___USBHD_UH_R_RES : 2;/*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X receiving (OUT)                                                         */
      __IOM uint8_t USBHD_UEP_R_TOG___USBHD_UH_R_TOG : 1;/*!< [2..2] expected data toggle flag of USB endpoint X receiving
                                                     (OUT): 0=DATA0, 1=DATA1                                                   */
      __IOM uint8_t USBHD_UEP_AUTO_TOG___USBHD_UH_R_AUTO_TOG : 1;/*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP2_R_CTRL__USBHD_UH_RX_CTRL;
  __IOM uint8_t   R8_UEP3_T_LEN__USBHD_UH_TX_LEN;/*!< (@ 0x0000003C) endpoint 3 transmittal length                             */
  __IM  uint8_t   RESERVED5;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000003E) endpoint 3 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES___USBHD_UH_T_RES : 2;/*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X transmittal (IN)                                                        */
      __IOM uint8_t USBHD_UEP_T_TOG___USBHD_UH_T_TOG : 1;/*!< [2..2] prepared data toggle flag of USB endpoint X transmittal
                                                     (IN): 0=DATA0, 1=DATA1                                                    */
      __IOM uint8_t USBHD_UEP_AUTO_TOG__USBHD_UH_T_AUTO_TOG : 1;/*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP3_T_CTRL__USBHD_UH_TX_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000003F) endpoint 3 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X receiving (OUT)                                                         */
      __IOM uint8_t USBHD_UEP_R_TOG : 1;        /*!< [2..2] expected data toggle flag of USB endpoint X receiving
                                                     (OUT): 0=DATA0, 1=DATA1                                                   */
      __IOM uint8_t USBHD_UEP_AUTO_TOG : 1;     /*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP3_R_CTRL_;
  __IOM uint8_t   R8_UEP4_T_LEN;                /*!< (@ 0x00000040) endpoint 4 transmittal length                              */
  __IM  uint8_t   RESERVED6;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000042) endpoint 4 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X transmittal (IN)                                                        */
      __IOM uint8_t USBHD_UEP_T_TOG___USBHD_UH_T_TOG : 1;/*!< [2..2] prepared data toggle flag of USB endpoint X transmittal
                                                     (IN): 0=DATA0, 1=DATA1                                                    */
      __IOM uint8_t USBHD_UEP_AUTO_TOG__USBHD_UH_T_AUTO_TOG : 1;/*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP4_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000043) endpoint 4 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X receiving (OUT)                                                         */
      __IOM uint8_t USBHD_UEP_R_TOG : 1;        /*!< [2..2] expected data toggle flag of USB endpoint X receiving
                                                     (OUT): 0=DATA0, 1=DATA1                                                   */
      __IOM uint8_t USBHD_UEP_AUTO_TOG : 1;     /*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP4_R_CTRL_;
  __IOM uint8_t   R8_UEP5_T_LEN;                /*!< (@ 0x00000044) endpoint 5 transmittal length                              */
  __IM  uint8_t   RESERVED7;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000046) endpoint 5 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X transmittal (IN)                                                        */
      __IOM uint8_t USBHD_UEP_T_TOG___USBHD_UH_T_TOG : 1;/*!< [2..2] prepared data toggle flag of USB endpoint X transmittal
                                                     (IN): 0=DATA0, 1=DATA1                                                    */
      __IOM uint8_t USBHD_UEP_AUTO_TOG__USBHD_UH_T_AUTO_TOG : 1;/*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP5_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x00000047) endpoint 5 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X receiving (OUT)                                                         */
      __IOM uint8_t USBHD_UEP_R_TOG : 1;        /*!< [2..2] expected data toggle flag of USB endpoint X receiving
                                                     (OUT): 0=DATA0, 1=DATA1                                                   */
      __IOM uint8_t USBHD_UEP_AUTO_TOG : 1;     /*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP5_R_CTRL_;
  __IOM uint8_t   R8_UEP6_T_LEN;                /*!< (@ 0x00000048) endpoint 6 transmittal length                              */
  __IM  uint8_t   RESERVED8;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000004A) endpoint 6 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X transmittal (IN)                                                        */
      __IOM uint8_t USBHD_UEP_T_TOG___USBHD_UH_T_TOG : 1;/*!< [2..2] prepared data toggle flag of USB endpoint X transmittal
                                                     (IN): 0=DATA0, 1=DATA1                                                    */
      __IOM uint8_t USBHD_UEP_AUTO_TOG__USBHD_UH_T_AUTO_TOG : 1;/*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP6_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000004B) endpoint 6 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X receiving (OUT)                                                         */
      __IOM uint8_t USBHD_UEP_R_TOG : 1;        /*!< [2..2] expected data toggle flag of USB endpoint X receiving
                                                     (OUT): 0=DATA0, 1=DATA1                                                   */
      __IOM uint8_t USBHD_UEP_AUTO_TOG : 1;     /*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP6_R_CTRL_;
  __IOM uint8_t   R8_UEP7_T_LEN;                /*!< (@ 0x0000004C) endpoint 7 transmittal length                              */
  __IM  uint8_t   RESERVED9;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000004E) endpoint 7 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_T_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X transmittal (IN)                                                        */
      __IOM uint8_t USBHD_UEP_T_TOG___USBHD_UH_T_TOG : 1;/*!< [2..2] prepared data toggle flag of USB endpoint X transmittal
                                                     (IN): 0=DATA0, 1=DATA1                                                    */
      __IOM uint8_t USBHD_UEP_AUTO_TOG__USBHD_UH_T_AUTO_TOG : 1;/*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP7_T_CTRL;
  
  union {
    __IOM uint8_t reg;                          /*!< (@ 0x0000004F) endpoint 7 control                                         */
    
    struct {
      __IOM uint8_t MASK_UEP_R_RES : 2;         /*!< [1..0] bit mask of handshake response type for USB endpoint
                                                     X receiving (OUT)                                                         */
      __IOM uint8_t USBHD_UEP_R_TOG : 1;        /*!< [2..2] expected data toggle flag of USB endpoint X receiving
                                                     (OUT): 0=DATA0, 1=DATA1                                                   */
      __IOM uint8_t USBHD_UEP_AUTO_TOG : 1;     /*!< [3..3] enable automatic toggle after successful transfer completion
                                                     on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle                    */
    } bit;
  } R8_UEP7_R_CTRL_;
  __IM  uint32_t  RESERVED10;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000054) usb otg control                                            */
    
    struct {
      __IOM uint32_t USB_OTG_CR_DISCHARGEVBUS : 1;/*!< [0..0] usb otg control                                                  */
      __IOM uint32_t USB_OTG_CR_CHARGEVBUS : 1; /*!< [1..1] usb otg control                                                    */
      __IOM uint32_t USB_OTG_CR_IDPU : 1;       /*!< [2..2] usb otg control                                                    */
      __IOM uint32_t USB_OTG_CR_OTG_EN : 1;     /*!< [3..3] usb otg control                                                    */
      __IOM uint32_t USB_OTG_CR_VBUS : 1;       /*!< [4..4] usb otg control                                                    */
      __IOM uint32_t USB_OTG_CR_SESS : 1;       /*!< [5..5] usb otg control                                                    */
    } bit;
  } USB_OTG_CR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000058) usb otg status                                             */
    
    struct {
      __IOM uint32_t USB_OTG_SR_VBUS_VLD : 1;   /*!< [0..0] usb otg status                                                     */
      __IOM uint32_t USB_OTG_SR_SESS_VLD : 1;   /*!< [1..1] usb otg status                                                     */
      __IOM uint32_t USB_OTG_SR_SESS_END : 1;   /*!< [2..2] usb otg status                                                     */
      __IOM uint32_t USB_OTG_SR_ID_DIG : 1;     /*!< [3..3] usb otg status                                                     */
    } bit;
  } USB_OTG_SR;
} USB_OTG_FS_Type;                              /*!< Size = 92 (0x5c)                                                          */



/* =========================================================================================================================== */
/* ================                                           PFIC                                            ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0xE000E000) PFIC Structure                                             */
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000000) Interrupt Status Register                                  */
    
    struct {
      __IM  uint32_t            : 2;
      __IM  uint32_t INTENSTA2_3 : 2;           /*!< [3..2] Interrupt ID Status                                                */
      __IM  uint32_t            : 8;
      __IM  uint32_t INTENSTA12_31 : 20;        /*!< [31..12] Interrupt ID Status                                              */
    } bit;
  } ISR1;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000004) Interrupt Status Register                                  */
    
    struct {
      __IM  uint32_t INTENSTA   : 32;           /*!< [31..0] Interrupt ID Status                                               */
    } bit;
  } ISR2;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000008) Interrupt Status Register                                  */
    
    struct {
      __IM  uint32_t INTENSTA   : 32;           /*!< [31..0] Interrupt ID Status                                               */
    } bit;
  } ISR3;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x0000000C) Interrupt Status Register                                  */
    
    struct {
      __IM  uint32_t INTENSTA   : 8;            /*!< [7..0] Interrupt ID Status                                                */
    } bit;
  } ISR4;
  __IM  uint32_t  RESERVED[4];
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000020) Interrupt Pending Register                                 */
    
    struct {
      __IM  uint32_t            : 2;
      __IM  uint32_t PENDSTA2_3 : 2;            /*!< [3..2] PENDSTA                                                            */
      __IM  uint32_t            : 8;
      __IM  uint32_t PENDSTA12_31 : 20;         /*!< [31..12] PENDSTA                                                          */
    } bit;
  } IPR1;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000024) Interrupt Pending Register                                 */
    
    struct {
      __IM  uint32_t PENDSTA    : 32;           /*!< [31..0] PENDSTA                                                           */
    } bit;
  } IPR2;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x00000028) Interrupt Pending Register                                 */
    
    struct {
      __IM  uint32_t PENDSTA    : 32;           /*!< [31..0] PENDSTA                                                           */
    } bit;
  } IPR3;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x0000002C) Interrupt Pending Register                                 */
    
    struct {
      __IM  uint32_t PENDSTA    : 8;            /*!< [7..0] PENDSTA                                                            */
    } bit;
  } IPR4;
  __IM  uint32_t  RESERVED1[4];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000040) Interrupt Priority Register                                */
    
    struct {
      __IOM uint32_t THRESHOLD  : 8;            /*!< [7..0] THRESHOLD                                                          */
    } bit;
  } ITHRESDR;
  __IM  uint32_t  RESERVED2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000048) Interrupt Config Register                                  */
    
    struct {
      __IM  uint32_t            : 7;
      __OM  uint32_t RESETSYS   : 1;            /*!< [7..7] RESETSYS                                                           */
      __IM  uint32_t            : 8;
      __OM  uint32_t KEYCODE    : 16;           /*!< [31..16] KEYCODE                                                          */
    } bit;
  } CFGR;
  
  union {
    __IM  uint32_t reg;                         /*!< (@ 0x0000004C) Interrupt Global Register                                  */
    
    struct {
      __IM  uint32_t NESTSTA    : 8;            /*!< [7..0] NESTSTA                                                            */
      __IM  uint32_t GACTSTA    : 1;            /*!< [8..8] GACTSTA                                                            */
      __IM  uint32_t GPENDSTA   : 1;            /*!< [9..9] GPENDSTA                                                           */
    } bit;
  } GISR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000050) ID Config Register                                         */
    
    struct {
      __IOM uint32_t VTFID0     : 8;            /*!< [7..0] VTFID0                                                             */
      __IOM uint32_t VTFID1     : 8;            /*!< [15..8] VTFID1                                                            */
      __IOM uint32_t VTFID2     : 8;            /*!< [23..16] VTFID2                                                           */
      __IOM uint32_t VTFID3     : 8;            /*!< [31..24] VTFID3                                                           */
    } bit;
  } VTFIDR;
  __IM  uint32_t  RESERVED3[3];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000060) Interrupt 0 address Register                               */
    
    struct {
      __IOM uint32_t VTF0EN     : 1;            /*!< [0..0] VTF0EN                                                             */
      __IOM uint32_t ADDR0      : 31;           /*!< [31..1] ADDR0                                                             */
    } bit;
  } VTFADDRR0;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000064) Interrupt 1 address Register                               */
    
    struct {
      __IOM uint32_t VTF1EN     : 1;            /*!< [0..0] VTF1EN                                                             */
      __IOM uint32_t ADDR1      : 31;           /*!< [31..1] ADDR1                                                             */
    } bit;
  } VTFADDRR1;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000068) Interrupt 2 address Register                               */
    
    struct {
      __IOM uint32_t VTF2EN     : 1;            /*!< [0..0] VTF2EN                                                             */
      __IOM uint32_t ADDR2      : 31;           /*!< [31..1] ADDR2                                                             */
    } bit;
  } VTFADDRR2;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000006C) Interrupt 3 address Register                               */
    
    struct {
      __IOM uint32_t VTF3EN     : 1;            /*!< [0..0] VTF3EN                                                             */
      __IOM uint32_t ADDR3      : 31;           /*!< [31..1] ADDR3                                                             */
    } bit;
  } VTFADDRR3;
  __IM  uint32_t  RESERVED4[36];
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000100) Interrupt Setting Register                                 */
    
    struct {
      __IM  uint32_t            : 12;
      __OM  uint32_t INTEN      : 20;           /*!< [31..12] INTEN                                                            */
    } bit;
  } IENR1;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000104) Interrupt Setting Register                                 */
    
    struct {
      __OM  uint32_t INTEN      : 32;           /*!< [31..0] INTEN                                                             */
    } bit;
  } IENR2;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000108) Interrupt Setting Register                                 */
    
    struct {
      __OM  uint32_t INTEN      : 32;           /*!< [31..0] INTEN                                                             */
    } bit;
  } IENR3;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x0000010C) Interrupt Setting Register                                 */
    
    struct {
      __OM  uint32_t INTEN      : 8;            /*!< [7..0] INTEN                                                              */
    } bit;
  } IENR4;
  __IM  uint32_t  RESERVED5[28];
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000180) Interrupt Clear Register                                   */
    
    struct {
      __IM  uint32_t            : 12;
      __OM  uint32_t INTRSET    : 20;           /*!< [31..12] INTRSET                                                          */
    } bit;
  } IRER1;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000184) Interrupt Clear Register                                   */
    
    struct {
      __OM  uint32_t INTRSET    : 32;           /*!< [31..0] INTRSET                                                           */
    } bit;
  } IRER2;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000188) Interrupt Clear Register                                   */
    
    struct {
      __OM  uint32_t INTRSET    : 32;           /*!< [31..0] INTRSET                                                           */
    } bit;
  } IRER3;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x0000018C) Interrupt Clear Register                                   */
    
    struct {
      __OM  uint32_t INTRSET    : 8;            /*!< [7..0] INTRSET                                                            */
    } bit;
  } IRER4;
  __IM  uint32_t  RESERVED6[28];
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000200) Interrupt Pending Register                                 */
    
    struct {
      __IM  uint32_t            : 2;
      __OM  uint32_t PENDSET2_3 : 2;            /*!< [3..2] PENDSET                                                            */
      __IM  uint32_t            : 8;
      __OM  uint32_t PENDSET12_31 : 20;         /*!< [31..12] PENDSET                                                          */
    } bit;
  } IPSR1;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000204) Interrupt Pending Register                                 */
    
    struct {
      __OM  uint32_t PENDSET    : 32;           /*!< [31..0] PENDSET                                                           */
    } bit;
  } IPSR2;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000208) Interrupt Pending Register                                 */
    
    struct {
      __OM  uint32_t PENDSET    : 32;           /*!< [31..0] PENDSET                                                           */
    } bit;
  } IPSR3;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x0000020C) Interrupt Pending Register                                 */
    
    struct {
      __OM  uint32_t PENDSET    : 8;            /*!< [7..0] PENDSET                                                            */
    } bit;
  } IPSR4;
  __IM  uint32_t  RESERVED7[28];
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000280) Interrupt Pending Clear Register                           */
    
    struct {
      __IM  uint32_t            : 2;
      __OM  uint32_t PENDRESET2_3 : 2;          /*!< [3..2] PENDRESET                                                          */
      __IM  uint32_t            : 8;
      __OM  uint32_t PENDRESET12_31 : 20;       /*!< [31..12] PENDRESET                                                        */
    } bit;
  } IPRR1;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000284) Interrupt Pending Clear Register                           */
    
    struct {
      __OM  uint32_t PENDRESET  : 32;           /*!< [31..0] PENDRESET                                                         */
    } bit;
  } IPRR2;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000288) Interrupt Pending Clear Register                           */
    
    struct {
      __OM  uint32_t PENDRESET  : 32;           /*!< [31..0] PENDRESET                                                         */
    } bit;
  } IPRR3;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x0000028C) Interrupt Pending Clear Register                           */
    
    struct {
      __OM  uint32_t PENDRESET  : 8;            /*!< [7..0] PENDRESET                                                          */
    } bit;
  } IPRR4;
  __IM  uint32_t  RESERVED8[28];
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000300) Interrupt ACTIVE Register                                  */
    
    struct {
      __IM  uint32_t            : 2;
      __OM  uint32_t IACTS2_3   : 2;            /*!< [3..2] IACTS                                                              */
      __IM  uint32_t            : 8;
      __OM  uint32_t IACTS12_31 : 20;           /*!< [31..12] IACTS                                                            */
    } bit;
  } IACTR1;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000304) Interrupt ACTIVE Register                                  */
    
    struct {
      __OM  uint32_t IACTS      : 32;           /*!< [31..0] IACTS                                                             */
    } bit;
  } IACTR2;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x00000308) Interrupt ACTIVE Register                                  */
    
    struct {
      __OM  uint32_t IACTS      : 32;           /*!< [31..0] IACTS                                                             */
    } bit;
  } IACTR3;
  
  union {
    __OM  uint32_t reg;                         /*!< (@ 0x0000030C) Interrupt ACTIVE Register                                  */
    
    struct {
      __OM  uint32_t IACTS      : 8;            /*!< [7..0] IACTS                                                              */
    } bit;
  } IACTR4;
  __IM  uint32_t  RESERVED9[60];
  __IOM uint8_t   IPRIOR0;                      /*!< (@ 0x00000400) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR1;                      /*!< (@ 0x00000401) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR2;                      /*!< (@ 0x00000402) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR3;                      /*!< (@ 0x00000403) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR4;                      /*!< (@ 0x00000404) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR5;                      /*!< (@ 0x00000405) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR6;                      /*!< (@ 0x00000406) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR7;                      /*!< (@ 0x00000407) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR8;                      /*!< (@ 0x00000408) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR9;                      /*!< (@ 0x00000409) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR10;                     /*!< (@ 0x0000040A) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR11;                     /*!< (@ 0x0000040B) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR12;                     /*!< (@ 0x0000040C) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR13;                     /*!< (@ 0x0000040D) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR14;                     /*!< (@ 0x0000040E) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR15;                     /*!< (@ 0x0000040F) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR16;                     /*!< (@ 0x00000410) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR17;                     /*!< (@ 0x00000411) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR18;                     /*!< (@ 0x00000412) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR19;                     /*!< (@ 0x00000413) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR20;                     /*!< (@ 0x00000414) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR21;                     /*!< (@ 0x00000415) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR22;                     /*!< (@ 0x00000416) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR23;                     /*!< (@ 0x00000417) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR24;                     /*!< (@ 0x00000418) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR25;                     /*!< (@ 0x00000419) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR26;                     /*!< (@ 0x0000041A) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR27;                     /*!< (@ 0x0000041B) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR28;                     /*!< (@ 0x0000041C) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR29;                     /*!< (@ 0x0000041D) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR30;                     /*!< (@ 0x0000041E) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR31;                     /*!< (@ 0x0000041F) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR32;                     /*!< (@ 0x00000420) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR33;                     /*!< (@ 0x00000421) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR34;                     /*!< (@ 0x00000422) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR35;                     /*!< (@ 0x00000423) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR36;                     /*!< (@ 0x00000424) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR37;                     /*!< (@ 0x00000425) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR38;                     /*!< (@ 0x00000426) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR39;                     /*!< (@ 0x00000427) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR40;                     /*!< (@ 0x00000428) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR41;                     /*!< (@ 0x00000429) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR42;                     /*!< (@ 0x0000042A) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR43;                     /*!< (@ 0x0000042B) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR44;                     /*!< (@ 0x0000042C) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR45;                     /*!< (@ 0x0000042D) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR46;                     /*!< (@ 0x0000042E) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR47;                     /*!< (@ 0x0000042F) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR48;                     /*!< (@ 0x00000430) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR49;                     /*!< (@ 0x00000431) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR50;                     /*!< (@ 0x00000432) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR51;                     /*!< (@ 0x00000433) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR52;                     /*!< (@ 0x00000434) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR53;                     /*!< (@ 0x00000435) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR54;                     /*!< (@ 0x00000436) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR55;                     /*!< (@ 0x00000437) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR56;                     /*!< (@ 0x00000438) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR57;                     /*!< (@ 0x00000439) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR58;                     /*!< (@ 0x0000043A) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR59;                     /*!< (@ 0x0000043B) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR60;                     /*!< (@ 0x0000043C) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR61;                     /*!< (@ 0x0000043D) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR62;                     /*!< (@ 0x0000043E) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR63;                     /*!< (@ 0x0000043F) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR64;                     /*!< (@ 0x00000440) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR65;                     /*!< (@ 0x00000441) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR66;                     /*!< (@ 0x00000442) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR67;                     /*!< (@ 0x00000443) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR68;                     /*!< (@ 0x00000444) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR69;                     /*!< (@ 0x00000445) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR70;                     /*!< (@ 0x00000446) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR71;                     /*!< (@ 0x00000447) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR72;                     /*!< (@ 0x00000448) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR73;                     /*!< (@ 0x00000449) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR74;                     /*!< (@ 0x0000044A) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR75;                     /*!< (@ 0x0000044B) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR76;                     /*!< (@ 0x0000044C) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR77;                     /*!< (@ 0x0000044D) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR78;                     /*!< (@ 0x0000044E) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR79;                     /*!< (@ 0x0000044F) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR80;                     /*!< (@ 0x00000450) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR81;                     /*!< (@ 0x00000451) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR82;                     /*!< (@ 0x00000452) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR83;                     /*!< (@ 0x00000453) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR84;                     /*!< (@ 0x00000454) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR85;                     /*!< (@ 0x00000455) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR86;                     /*!< (@ 0x00000456) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR87;                     /*!< (@ 0x00000457) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR88;                     /*!< (@ 0x00000458) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR89;                     /*!< (@ 0x00000459) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR90;                     /*!< (@ 0x0000045A) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR91;                     /*!< (@ 0x0000045B) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR92;                     /*!< (@ 0x0000045C) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR93;                     /*!< (@ 0x0000045D) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR94;                     /*!< (@ 0x0000045E) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR95;                     /*!< (@ 0x0000045F) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR96;                     /*!< (@ 0x00000460) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR97;                     /*!< (@ 0x00000461) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR98;                     /*!< (@ 0x00000462) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR99;                     /*!< (@ 0x00000463) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR100;                    /*!< (@ 0x00000464) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR101;                    /*!< (@ 0x00000465) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR102;                    /*!< (@ 0x00000466) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR103;                    /*!< (@ 0x00000467) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR104;                    /*!< (@ 0x00000468) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR105;                    /*!< (@ 0x00000469) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR106;                    /*!< (@ 0x0000046A) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR107;                    /*!< (@ 0x0000046B) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR108;                    /*!< (@ 0x0000046C) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR109;                    /*!< (@ 0x0000046D) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR110;                    /*!< (@ 0x0000046E) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR111;                    /*!< (@ 0x0000046F) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR112;                    /*!< (@ 0x00000470) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR113;                    /*!< (@ 0x00000471) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR114;                    /*!< (@ 0x00000472) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR115;                    /*!< (@ 0x00000473) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR116;                    /*!< (@ 0x00000474) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR117;                    /*!< (@ 0x00000475) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR118;                    /*!< (@ 0x00000476) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR119;                    /*!< (@ 0x00000477) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR120;                    /*!< (@ 0x00000478) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR121;                    /*!< (@ 0x00000479) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR122;                    /*!< (@ 0x0000047A) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR123;                    /*!< (@ 0x0000047B) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR124;                    /*!< (@ 0x0000047C) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR125;                    /*!< (@ 0x0000047D) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR126;                    /*!< (@ 0x0000047E) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR127;                    /*!< (@ 0x0000047F) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR128;                    /*!< (@ 0x00000480) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR129;                    /*!< (@ 0x00000481) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR130;                    /*!< (@ 0x00000482) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR131;                    /*!< (@ 0x00000483) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR132;                    /*!< (@ 0x00000484) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR133;                    /*!< (@ 0x00000485) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR134;                    /*!< (@ 0x00000486) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR135;                    /*!< (@ 0x00000487) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR136;                    /*!< (@ 0x00000488) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR137;                    /*!< (@ 0x00000489) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR138;                    /*!< (@ 0x0000048A) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR139;                    /*!< (@ 0x0000048B) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR140;                    /*!< (@ 0x0000048C) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR141;                    /*!< (@ 0x0000048D) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR142;                    /*!< (@ 0x0000048E) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR143;                    /*!< (@ 0x0000048F) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR144;                    /*!< (@ 0x00000490) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR145;                    /*!< (@ 0x00000491) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR146;                    /*!< (@ 0x00000492) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR147;                    /*!< (@ 0x00000493) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR148;                    /*!< (@ 0x00000494) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR149;                    /*!< (@ 0x00000495) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR150;                    /*!< (@ 0x00000496) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR151;                    /*!< (@ 0x00000497) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR152;                    /*!< (@ 0x00000498) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR153;                    /*!< (@ 0x00000499) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR154;                    /*!< (@ 0x0000049A) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR155;                    /*!< (@ 0x0000049B) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR156;                    /*!< (@ 0x0000049C) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR157;                    /*!< (@ 0x0000049D) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR158;                    /*!< (@ 0x0000049E) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR159;                    /*!< (@ 0x0000049F) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR160;                    /*!< (@ 0x000004A0) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR161;                    /*!< (@ 0x000004A1) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR162;                    /*!< (@ 0x000004A2) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR163;                    /*!< (@ 0x000004A3) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR164;                    /*!< (@ 0x000004A4) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR165;                    /*!< (@ 0x000004A5) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR166;                    /*!< (@ 0x000004A6) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR167;                    /*!< (@ 0x000004A7) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR168;                    /*!< (@ 0x000004A8) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR169;                    /*!< (@ 0x000004A9) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR170;                    /*!< (@ 0x000004AA) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR171;                    /*!< (@ 0x000004AB) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR172;                    /*!< (@ 0x000004AC) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR173;                    /*!< (@ 0x000004AD) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR174;                    /*!< (@ 0x000004AE) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR175;                    /*!< (@ 0x000004AF) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR176;                    /*!< (@ 0x000004B0) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR177;                    /*!< (@ 0x000004B1) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR178;                    /*!< (@ 0x000004B2) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR179;                    /*!< (@ 0x000004B3) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR180;                    /*!< (@ 0x000004B4) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR181;                    /*!< (@ 0x000004B5) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR182;                    /*!< (@ 0x000004B6) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR183;                    /*!< (@ 0x000004B7) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR184;                    /*!< (@ 0x000004B8) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR185;                    /*!< (@ 0x000004B9) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR186;                    /*!< (@ 0x000004BA) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR187;                    /*!< (@ 0x000004BB) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR188;                    /*!< (@ 0x000004BC) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR189;                    /*!< (@ 0x000004BD) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR190;                    /*!< (@ 0x000004BE) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR191;                    /*!< (@ 0x000004BF) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR192;                    /*!< (@ 0x000004C0) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR193;                    /*!< (@ 0x000004C1) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR194;                    /*!< (@ 0x000004C2) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR195;                    /*!< (@ 0x000004C3) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR196;                    /*!< (@ 0x000004C4) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR197;                    /*!< (@ 0x000004C5) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR198;                    /*!< (@ 0x000004C6) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR199;                    /*!< (@ 0x000004C7) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR200;                    /*!< (@ 0x000004C8) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR201;                    /*!< (@ 0x000004C9) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR202;                    /*!< (@ 0x000004CA) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR203;                    /*!< (@ 0x000004CB) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR204;                    /*!< (@ 0x000004CC) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR205;                    /*!< (@ 0x000004CD) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR206;                    /*!< (@ 0x000004CE) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR207;                    /*!< (@ 0x000004CF) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR208;                    /*!< (@ 0x000004D0) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR209;                    /*!< (@ 0x000004D1) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR210;                    /*!< (@ 0x000004D2) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR211;                    /*!< (@ 0x000004D3) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR212;                    /*!< (@ 0x000004D4) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR213;                    /*!< (@ 0x000004D5) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR214;                    /*!< (@ 0x000004D6) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR215;                    /*!< (@ 0x000004D7) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR216;                    /*!< (@ 0x000004D8) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR217;                    /*!< (@ 0x000004D9) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR218;                    /*!< (@ 0x000004DA) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR219;                    /*!< (@ 0x000004DB) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR220;                    /*!< (@ 0x000004DC) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR221;                    /*!< (@ 0x000004DD) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR222;                    /*!< (@ 0x000004DE) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR223;                    /*!< (@ 0x000004DF) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR224;                    /*!< (@ 0x000004E0) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR225;                    /*!< (@ 0x000004E1) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR226;                    /*!< (@ 0x000004E2) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR227;                    /*!< (@ 0x000004E3) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR228;                    /*!< (@ 0x000004E4) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR229;                    /*!< (@ 0x000004E5) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR230;                    /*!< (@ 0x000004E6) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR231;                    /*!< (@ 0x000004E7) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR232;                    /*!< (@ 0x000004E8) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR233;                    /*!< (@ 0x000004E9) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR234;                    /*!< (@ 0x000004EA) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR235;                    /*!< (@ 0x000004EB) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR236;                    /*!< (@ 0x000004EC) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR237;                    /*!< (@ 0x000004ED) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR238;                    /*!< (@ 0x000004EE) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR239;                    /*!< (@ 0x000004EF) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR240;                    /*!< (@ 0x000004F0) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR241;                    /*!< (@ 0x000004F1) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR242;                    /*!< (@ 0x000004F2) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR243;                    /*!< (@ 0x000004F3) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR244;                    /*!< (@ 0x000004F4) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR245;                    /*!< (@ 0x000004F5) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR246;                    /*!< (@ 0x000004F6) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR247;                    /*!< (@ 0x000004F7) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR248;                    /*!< (@ 0x000004F8) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR249;                    /*!< (@ 0x000004F9) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR250;                    /*!< (@ 0x000004FA) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR251;                    /*!< (@ 0x000004FB) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR252;                    /*!< (@ 0x000004FC) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR253;                    /*!< (@ 0x000004FD) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR254;                    /*!< (@ 0x000004FE) Interrupt Priority Register                                */
  __IOM uint8_t   IPRIOR255;                    /*!< (@ 0x000004FF) Interrupt Priority Register                                */
  __IM  uint32_t  RESERVED10[516];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00000D10) System Control Register                                    */
    
    struct {
      __IM  uint32_t            : 1;
      __IOM uint32_t SLEEPONEXIT : 1;           /*!< [1..1] SLEEPONEXIT                                                        */
      __IOM uint32_t SLEEPDEEP  : 1;            /*!< [2..2] SLEEPDEEP                                                          */
      __IOM uint32_t WFITOWFE   : 1;            /*!< [3..3] WFITOWFE                                                           */
      __IOM uint32_t SEVONPEND  : 1;            /*!< [4..4] SEVONPEND                                                          */
      __IOM uint32_t SETEVENT   : 1;            /*!< [5..5] SETEVENT                                                           */
      __IM  uint32_t            : 25;
      __IOM uint32_t SYSRESET   : 1;            /*!< [31..31] SYSRESET                                                         */
    } bit;
  } SCTLR;
  __IM  uint32_t  RESERVED11[187];
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00001000) System counter control register                            */
    
    struct {
      __IOM uint32_t STE        : 1;            /*!< [0..0] System counter enable                                              */
      __IOM uint32_t STIE       : 1;            /*!< [1..1] System counter interrupt enable                                    */
      __IOM uint32_t STCLK      : 1;            /*!< [2..2] System selects the clock source                                    */
      __IOM uint32_t STRE       : 1;            /*!< [3..3] System reload register                                             */
      __IOM uint32_t MODE       : 1;            /*!< [4..4] System Mode                                                        */
      __IOM uint32_t INIT       : 1;            /*!< [5..5] System Initialization update                                       */
      __IM  uint32_t            : 25;
      __IOM uint32_t SWIE       : 1;            /*!< [31..31] System software triggered interrupts enable                      */
    } bit;
  } STK_CTLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00001004) System START                                               */
    
    struct {
      __IOM uint32_t CNTIF      : 1;            /*!< [0..0] CNTIF                                                              */
    } bit;
  } STK_SR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00001008) System counter low register                                */
    
    struct {
      __IOM uint32_t CNTL       : 32;           /*!< [31..0] CNTL                                                              */
    } bit;
  } STK_CNTL;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x0000100C) System counter high register                               */
    
    struct {
      __IOM uint32_t CNTH       : 32;           /*!< [31..0] CNTH                                                              */
    } bit;
  } STK_CNTH;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00001010) System compare low register                                */
    
    struct {
      __IOM uint32_t CMPL       : 32;           /*!< [31..0] CMPL                                                              */
    } bit;
  } STK_CMPLR;
  
  union {
    __IOM uint32_t reg;                         /*!< (@ 0x00001014) System compare high register                               */
    
    struct {
      __IOM uint32_t CMPH       : 32;           /*!< [31..0] CMPH                                                              */
    } bit;
  } STK_CMPHR;
} PFIC_Type;                                    /*!< Size = 4120 (0x1018)                                                      */


/** @} */ /* End of group Device_Peripheral_peripherals */


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */

#define RNG_BASE                    0x40023C00UL
#define USB_BASE                    0x40005C00UL
#define CAN1_BASE                   0x40006400UL
#define CAN2_BASE                   0x40006800UL
#define ETHERNET_MAC_BASE           0x40028000UL
#define ETHERNET_MMC_BASE           0x40028100UL
#define ETHERNET_PTP_BASE           0x40028700UL
#define ETHERNET_DMA_BASE           0x40029000UL
#define SDIO_BASE                   0x40018000UL
#define FSMC_BASE                   0xA0000000UL
#define DVP_BASE                    0x50050000UL
#define DAC_BASE                    0x40007400UL
#define PWR_BASE                    0x40007000UL
#define RCC_BASE                    0x40021000UL
#define EXTEND_BASE                 0x40023800UL
#define OPA_BASE                    0x40023804UL
#define GPIOA_BASE                  0x40010800UL
#define GPIOB_BASE                  0x40010C00UL
#define GPIOC_BASE                  0x40011000UL
#define GPIOD_BASE                  0x40011400UL
#define GPIOE_BASE                  0x40011800UL
#define AFIO_BASE                   0x40010000UL
#define EXTI_BASE                   0x40010400UL
#define DMA1_BASE                   0x40020000UL
#define DMA2_BASE                   0x40020400UL
#define RTC_BASE                    0x40002800UL
#define BKP_BASE                    0x40006C00UL
#define IWDG_BASE                   0x40003000UL
#define WWDG_BASE                   0x40002C00UL
#define TIM1_BASE                   0x40012C00UL
#define TIM8_BASE                   0x40013400UL
#define TIM9_BASE                   0x40014C00UL
#define TIM10_BASE                  0x40015000UL
#define TIM2_BASE                   0x40000000UL
#define TIM3_BASE                   0x40000400UL
#define TIM4_BASE                   0x40000800UL
#define TIM5_BASE                   0x40000C00UL
#define TIM6_BASE                   0x40001000UL
#define TIM7_BASE                   0x40001400UL
#define I2C1_BASE                   0x40005400UL
#define I2C2_BASE                   0x40005800UL
#define SPI1_BASE                   0x40013000UL
#define SPI2_BASE                   0x40003800UL
#define SPI3_BASE                   0x40003C00UL
#define USART1_BASE                 0x40013800UL
#define USART2_BASE                 0x40004400UL
#define USART3_BASE                 0x40004800UL
#define UART4_BASE                  0x40004C00UL
#define UART5_BASE                  0x40005000UL
#define UART6_BASE                  0x40001800UL
#define UART7_BASE                  0x40001C00UL
#define UART8_BASE                  0x40002000UL
#define ADC1_BASE                   0x40012400UL
#define ADC2_BASE                   0x40012800UL
#define DBG_BASE                    0xE000D000UL
#define USBHD_BASE                  0x40023400UL
#define CRC_BASE                    0x40023000UL
#define FLASH_BASE                  0x40022000UL
#define USB_OTG_FS_BASE             0x50000000UL
#define PFIC_BASE                   0xE000E000UL

/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

#define RNG                         ((RNG_Type*)               RNG_BASE)
#define USB                         ((USB_Type*)               USB_BASE)
#define CAN1                        ((CAN1_Type*)              CAN1_BASE)
#define CAN2                        ((CAN1_Type*)              CAN2_BASE)
#define ETHERNET_MAC                ((ETHERNET_MAC_Type*)      ETHERNET_MAC_BASE)
#define ETHERNET_MMC                ((ETHERNET_MMC_Type*)      ETHERNET_MMC_BASE)
#define ETHERNET_PTP                ((ETHERNET_PTP_Type*)      ETHERNET_PTP_BASE)
#define ETHERNET_DMA                ((ETHERNET_DMA_Type*)      ETHERNET_DMA_BASE)
#define SDIO                        ((SDIO_Type*)              SDIO_BASE)
#define FSMC                        ((FSMC_Type*)              FSMC_BASE)
#define DVP                         ((DVP_Type*)               DVP_BASE)
#define DAC                         ((DAC_Type*)               DAC_BASE)
#define PWR                         ((PWR_Type*)               PWR_BASE)
#define RCC                         ((RCC_Type*)               RCC_BASE)
#define EXTEND                      ((EXTEND_Type*)            EXTEND_BASE)
#define OPA                         ((OPA_Type*)               OPA_BASE)
#define GPIOA                       ((GPIOA_Type*)             GPIOA_BASE)
#define GPIOB                       ((GPIOA_Type*)             GPIOB_BASE)
#define GPIOC                       ((GPIOA_Type*)             GPIOC_BASE)
#define GPIOD                       ((GPIOA_Type*)             GPIOD_BASE)
#define GPIOE                       ((GPIOA_Type*)             GPIOE_BASE)
#define AFIO                        ((AFIO_Type*)              AFIO_BASE)
#define EXTI                        ((EXTI_Type*)              EXTI_BASE)
#define DMA1                        ((DMA1_Type*)              DMA1_BASE)
#define DMA2                        ((DMA2_Type*)              DMA2_BASE)
#define RTC                         ((RTC_Type*)               RTC_BASE)
#define BKP                         ((BKP_Type*)               BKP_BASE)
#define IWDG                        ((IWDG_Type*)              IWDG_BASE)
#define WWDG                        ((WWDG_Type*)              WWDG_BASE)
#define TIM1                        ((TIM1_Type*)              TIM1_BASE)
#define TIM8                        ((TIM1_Type*)              TIM8_BASE)
#define TIM9                        ((TIM1_Type*)              TIM9_BASE)
#define TIM10                       ((TIM1_Type*)              TIM10_BASE)
#define TIM2                        ((TIM2_Type*)              TIM2_BASE)
#define TIM3                        ((TIM2_Type*)              TIM3_BASE)
#define TIM4                        ((TIM2_Type*)              TIM4_BASE)
#define TIM5                        ((TIM2_Type*)              TIM5_BASE)
#define TIM6                        ((TIM6_Type*)              TIM6_BASE)
#define TIM7                        ((TIM6_Type*)              TIM7_BASE)
#define I2C1                        ((I2C1_Type*)              I2C1_BASE)
#define I2C2                        ((I2C1_Type*)              I2C2_BASE)
#define SPI1                        ((SPI1_Type*)              SPI1_BASE)
#define SPI2                        ((SPI2_Type*)              SPI2_BASE)
#define SPI3                        ((SPI2_Type*)              SPI3_BASE)
#define USART1                      ((USART1_Type*)            USART1_BASE)
#define USART2                      ((USART1_Type*)            USART2_BASE)
#define USART3                      ((USART1_Type*)            USART3_BASE)
#define UART4                       ((USART1_Type*)            UART4_BASE)
#define UART5                       ((USART1_Type*)            UART5_BASE)
#define UART6                       ((USART1_Type*)            UART6_BASE)
#define UART7                       ((USART1_Type*)            UART7_BASE)
#define UART8                       ((USART1_Type*)            UART8_BASE)
#define ADC1                        ((ADC1_Type*)              ADC1_BASE)
#define ADC2                        ((ADC2_Type*)              ADC2_BASE)
#define DBG                         ((DBG_Type*)               DBG_BASE)
#define USBHD                       ((USBHD_Type*)             USBHD_BASE)
#define CRC                         ((CRC_Type*)               CRC_BASE)
#define FLASH                       ((FLASH_Type*)             FLASH_BASE)
#define USB_OTG_FS                  ((USB_OTG_FS_Type*)        USB_OTG_FS_BASE)
#define PFIC                        ((PFIC_Type*)              PFIC_BASE)

#ifdef __cplusplus
}
#endif

#endif /* CH32V30XXX_H */
