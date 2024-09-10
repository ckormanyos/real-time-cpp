
#ifndef __USB_HWREG_H__
#define __USB_HWREG_H__

#include <stdint.h>

#define     __IM    volatile const       /*! Defines 'read only' structure member permissions */
#define     __OM    volatile             /*! Defines 'write only' structure member permissions */
#define     __IOM   volatile             /*! Defines 'read / write' structure member permissions */


typedef union {
  __IOM uint32_t reg;                         /*!< (@ 0x00000080) Buffer control for both buffers of an endpoint.
                                                                  Fields ending in a _1 are for buffer 1.
                                                                  Fields ending in a _0 are for buffer 0.
                                                                  Buffer 1 controls are only valid if the
                                                                  endpoint is in double buffered mode.                       */
  
  struct {
    __IOM uint32_t LENGTH_0   : 10;           /*!< [9..0] The length of the data in buffer 1.                                */
    __IOM uint32_t AVAILABLE_0 : 1;           /*!< [10..10] Buffer 0 is available. This bit is set to indicate
                                                   the buffer can be used by the controller. The controller
                                                   clears the available bit when writing the status back.                    */
    __IOM uint32_t STALL      : 1;            /*!< [11..11] Reply with a stall (valid for both buffers).                     */
    __IOM uint32_t RESET      : 1;            /*!< [12..12] Reset the buffer selector to buffer 0.                           */
    __IOM uint32_t PID_0      : 1;            /*!< [13..13] The data pid of buffer 0.                                        */
    __IOM uint32_t LAST_0     : 1;            /*!< [14..14] Buffer 0 is the last buffer of the transfer.                     */
    __IOM uint32_t FULL_0     : 1;            /*!< [15..15] Buffer 0 is full. For an IN transfer (TX to the host)
                                                   the bit is set to indicate the data is valid. For an OUT
                                                   transfer (RX from the host) this bit should be left as
                                                   a 0. The host will set it when it has filled the buffer
                                                   with data.                                                                */
    __IOM uint32_t LENGTH_1   : 10;           /*!< [25..16] The length of the data in buffer 1.                              */
    __IOM uint32_t AVAILABLE_1 : 1;           /*!< [26..26] Buffer 1 is available. This bit is set to indicate
                                                   the buffer can be used by the controller. The controller
                                                   clears the available bit when writing the status back.                    */
    __IOM uint32_t DOUBLE_BUFFER_ISO_OFFSET : 2;/*!< [28..27] The number of bytes buffer 1 is offset from buffer
                                                   0 in Isochronous mode. Only valid in double buffered mode
                                                   for an Isochronous endpoint.
                                                   For a non Isochronous endpoint the offset is always 64
                                                   bytes.                                                                    */
    __IOM uint32_t PID_1      : 1;            /*!< [29..29] The data pid of buffer 1.                                        */
    __IOM uint32_t LAST_1     : 1;            /*!< [30..30] Buffer 1 is the last buffer of the transfer.                     */
    __IOM uint32_t FULL_1     : 1;            /*!< [31..31] Buffer 1 is full. For an IN transfer (TX to the host)
                                                   the bit is set to indicate the data is valid. For an OUT
                                                   transfer (RX from the host) this bit should be left as
                                                   a 0. The host will set it when it has filled the buffer
                                                   with data.                                                                */
  } bit;
} EPx_BUFFER_CONTROL;

typedef union {
  __IOM uint32_t reg;                         /*!< (@ 0x00000008) EP1_IN_CONTROL                                             */
  
  struct {
    __IOM uint32_t BUFFER_ADDRESS : 16;       /*!< [15..0] 64 byte aligned buffer address for this EP (bits 0-5
                                                   are ignored). Relative to the start of the DPRAM.                         */
    __IOM uint32_t INTERRUPT_ON_NAK : 1;      /*!< [16..16] Trigger an interrupt if a NAK is sent. Intended for
                                                   debug only.                                                               */
    __IOM uint32_t INTERRUPT_ON_STALL : 1;    /*!< [17..17] Trigger an interrupt if a STALL is sent. Intended for
                                                   debug only.                                                               */
          uint32_t            : 8;
    __IOM uint32_t ENDPOINT_TYPE : 2;         /*!< [27..26] ENDPOINT_TYPE                                                    */
    __IOM uint32_t INTERRUPT_PER_DOUBLE_BUFF : 1;/*!< [28..28] Trigger an interrupt each time both buffers are done.
                                                   Only valid in double buffered mode.                                       */
    __IOM uint32_t INTERRUPT_PER_BUFF : 1;    /*!< [29..29] Trigger an interrupt each time a buffer is done.                 */
    __IOM uint32_t DOUBLE_BUFFERED : 1;       /*!< [30..30] This endpoint is double buffered.                                */
    __IOM uint32_t ENABLE     : 1;            /*!< [31..31] Enable this endpoint. The device will not reply to
                                                   any packets for this endpoint if this bit is not set.                     */
  } bit;
} EPx_CONTROL;

#ifndef USBCTRL_DPRAM_BASE
#define USBCTRL_DPRAM_BASE          0x50100000UL
#endif

#ifndef USBCTRL_REGS_BASE
#define USBCTRL_REGS_BASE           0x50110000UL
#endif

#define EPx_IN_CONTROL_OFFSET   0x08
#define EPx_OUT_CONTROL_OFFSET  0x04

#define EPx_IN_BUFFER_CONTROL_OFFSET   0x80
#define EPx_OUT_BUFFER_CONTROL_OFFSET  0x84

#endif /*__USB_HWREG_H__*/
