/******************************************************************************************
  Filename    : USB.c
  
  Core        : ARM Cortex-M33 / RISC-V Hazard3
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.09.2024
  
  Description : USB low level device driver implementation
  
******************************************************************************************/

//=============================================================================
// Includes
//=============================================================================
#include "RP2350.h"
#include "USB.h"
#include "usb_hwreg.h"
#include "usb_types.h"
#include <string.h>

//=============================================================================
// Globals (Debug purpose only)
//=============================================================================
#define ENABLE_DEBUG_USB  0
#define ENABLE_DEBUG_HLT  0

#if ENABLE_DEBUG_USB
  #define __DEBUG_USB__
#endif

#if ENABLE_DEBUG_USB && ENABLE_DEBUG_HLT
  #define __DEBUG_HALT__
#endif

#ifdef __DEBUG_USB__
volatile uint64 _EP0_[100] = {0};
volatile uint32 _EP0_index = 0;

volatile uint64 _EP0_SpecificReq[100] = {0};
volatile uint32 _EP0_SpecificReq_index = 0;

volatile uint32 BusResetCounter = 0;

volatile uint32 UsbReceived_EP0_OUT_count = 0;
volatile uint32 UsbReceived_EP0_IN_count = 0;

volatile uint32 UsbReceived_EP1_IN_count = 0;
volatile uint32 UsbReceived_EP1_OUT_count = 0;

volatile uint32 UsbReceived_EP2_IN_count = 0;
volatile uint32 UsbReceived_EP2_OUT_count = 0;

volatile uint32 UsbReceived_EP3_IN_count = 0;
volatile uint32 UsbReceived_EP3_OUT_count = 0;

volatile uint32 UsbNotSupportedRequestCount = 0;

volatile uint32 boHaltBeforeEnableUsb = 1;
#endif
//=============================================================================
// Local types
//=============================================================================
typedef void (*pStandardRequestHandler)(const tUsbSetupPacket* const pUsbSetupPacket);

//=============================================================================
// Static functions
//=============================================================================
static void    UsbDriver_HandleSetupPacket     (const tUsbSetupPacket* const pUsbSetupPacket);
static boolean UsbDriver_SendDataToHost        (uint8 endpoint, uint8 pid, uint8* buffer, uint8 size);
static boolean UsbDriver_ConfigureEpOutBuf     (uint8 endpoint, uint8 pid, uint8 size);
static boolean UsbDriver_SendStallToHost       (uint8 endpoint, uint8 pid);
static boolean UsbDriver_ConfigureEndpoint     (uint8 endpoint, uint8 direction, uint8 type);
static void    UsbDriver_Req_get_status        (const tUsbSetupPacket* const pUsbSetupPacket);
static void    UsbDriver_Req_clear_feature     (const tUsbSetupPacket* const pUsbSetupPacket);
static void    UsbDriver_Req_set_feature       (const tUsbSetupPacket* const pUsbSetupPacket);
static void    UsbDriver_Req_set_address       (const tUsbSetupPacket* const pUsbSetupPacket);
static void    UsbDriver_Req_get_descriptor    (const tUsbSetupPacket* const pUsbSetupPacket);
static void    UsbDriver_Req_set_descriptor    (const tUsbSetupPacket* const pUsbSetupPacket);
static void    UsbDriver_Req_get_configuration (const tUsbSetupPacket* const pUsbSetupPacket);
static void    UsbDriver_Req_set_configuration (const tUsbSetupPacket* const pUsbSetupPacket);
static void    UsbDriver_Req_get_interface     (const tUsbSetupPacket* const pUsbSetupPacket);
static void    UsbDriver_Req_set_interface     (const tUsbSetupPacket* const pUsbSetupPacket);
static void    UsbDriver_Req_synch_frame       (const tUsbSetupPacket* const pUsbSetupPacket);

//=============================================================================
// Globals
//=============================================================================
static volatile uint32 UsbDeviceAddress = 0;
static volatile uint8 EPx_dataPid[16] = {DATA0_PID};

static const pStandardRequestHandler 
    StandardRequestHandlerLockupTable[13] = {
      UsbDriver_Req_get_status,
      UsbDriver_Req_clear_feature,
      NULL,
      UsbDriver_Req_set_feature,
      NULL,
      UsbDriver_Req_set_address,
      UsbDriver_Req_get_descriptor,
      UsbDriver_Req_set_descriptor,
      UsbDriver_Req_get_configuration,
      UsbDriver_Req_set_configuration,
      UsbDriver_Req_get_interface,
      UsbDriver_Req_set_interface,
      UsbDriver_Req_synch_frame
    };

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void USBCTRL_IRQ(void)
{
  /* handle SETUP packets */
  if(USBCTRL_REGS->INTS.bit.SETUP_REQ)
  {
    /* clear the interrupt */
    USBCTRL_REGS->SIE_STATUS.bit.SETUP_REC = 1u;

    /* get the SETUP packet data */
    const tUsbSetupPacket* const UsbSetupPacket = (const tUsbSetupPacket* const)USBCTRL_DPRAM_BASE;
    
    /* call the appropriate SETUP packet handler */
    UsbDriver_HandleSetupPacket(UsbSetupPacket);

#ifdef __DEBUG_USB__
    //save the data
    _EP0_[_EP0_index++] = *(volatile uint64*)(USBCTRL_DPRAM_BASE);
#endif
  }
  
  /* handle bus reset */
  if(USBCTRL_REGS->INTS.bit.BUS_RESET)
  {
    /* clear the bus reset interrupt flag */
    USBCTRL_REGS->SIE_STATUS.bit.BUS_RESET = 1;
    USBCTRL_REGS->ADDR_ENDP.bit.ADDRESS = 0;
    UsbDeviceAddress = 0;
#ifdef __DEBUG_USB__
    BusResetCounter++;
#endif
  }

  /* handle OUT and IN packets */
  if(USBCTRL_REGS->INTS.bit.BUFF_STATUS)
  {
    /***************************************************************************/
    /* endpoint 0 */
    /***************************************************************************/
    if(USBCTRL_REGS->BUFF_STATUS.bit.EP0_OUT)
    {
#ifdef __DEBUG_USB__
        UsbReceived_EP0_OUT_count++;
#endif
       /* clear the EP0_OUT buffer status */
       USBCTRL_REGS->BUFF_STATUS.bit.EP0_OUT = 1;

      /* configure the expected OUT packet */
      UsbDriver_ConfigureEpOutBuf(EP0, DATA1_PID, 64);
    }

    if(USBCTRL_REGS->BUFF_STATUS.bit.EP0_IN)
    {
        /* this bit indicate that the DATA is received by the HOST and we received ACK from HOST, the EP0_IN buffer is empty 
           (USBCTRL_DPRAM->EP0_IN_BUFFER_CONTROL.bit.FULL_0 is cleared to indicate that data has been sent).
        */
#ifdef __DEBUG_USB__
        UsbReceived_EP0_IN_count++;
#endif
       /* clear the EP0_IN buffer status */
       USBCTRL_REGS->BUFF_STATUS.bit.EP0_IN = 1;

      if(UsbDeviceAddress != 0)
      {
        /* setup device address */
        USBCTRL_REGS->ADDR_ENDP.reg |= (uint32)(UsbDeviceAddress & 0x7Ful);
      }

      /* configure the expected OUT packet */
      UsbDriver_ConfigureEpOutBuf(EP0, DATA1_PID, 64);
    }

    /***************************************************************************/
    /* endpoint 1 */
    /***************************************************************************/
    if(USBCTRL_REGS->BUFF_STATUS.bit.EP1_OUT)
    {
#ifdef __DEBUG_USB__
        UsbReceived_EP1_OUT_count++;
#endif
       /* clear the EP1_OUT buffer status */
       USBCTRL_REGS->BUFF_STATUS.bit.EP1_OUT = 1;

       /* TODO: copy the received data and call the handler */

       EPx_dataPid[EP1] ^= 1u;
       UsbDriver_ConfigureEpOutBuf(EP1, EPx_dataPid[EP1], 64u);
    }
    if(USBCTRL_REGS->BUFF_STATUS.bit.EP1_IN)
    {
#ifdef __DEBUG_USB__
        UsbReceived_EP1_IN_count++;
#endif
       /* clear the EP1_IN buffer status */
       USBCTRL_REGS->BUFF_STATUS.bit.EP1_IN = 1;

       /* TODO: notify the handler */

       /* update the EP1_OUT buffer config with the new expect data pid */
       EPx_dataPid[EP1] ^= 1u;
       UsbDriver_ConfigureEpOutBuf(EP1, EPx_dataPid[EP1], 64u);
    }
    /***************************************************************************/
    /* endpoint 2 */
    /***************************************************************************/
    if(USBCTRL_REGS->BUFF_STATUS.bit.EP2_OUT)
    {
#ifdef __DEBUG_USB__
        UsbReceived_EP2_OUT_count++;
#endif
       /* clear the EP2_OUT buffer status */
       USBCTRL_REGS->BUFF_STATUS.bit.EP2_OUT = 1;

       /* TODO: copy the received data and call the handler */

       EPx_dataPid[EP2] ^= 1u;
       UsbDriver_ConfigureEpOutBuf(EP2, EPx_dataPid[EP2], 64u);
    }
    if(USBCTRL_REGS->BUFF_STATUS.bit.EP2_IN)
    {
#ifdef __DEBUG_USB__
        UsbReceived_EP2_IN_count++;
#endif
       /* clear the EP2_IN buffer status */
       USBCTRL_REGS->BUFF_STATUS.bit.EP2_IN = 1;

       /* TODO: notify the handler */

       /* update the EP2_OUT buffer config with the new expect data pid */
       EPx_dataPid[EP2] ^= 1u;
       UsbDriver_ConfigureEpOutBuf(EP2, EPx_dataPid[EP2], 64u);
    }
    /***************************************************************************/
    /* endpoint 3 */
    /***************************************************************************/
    if(USBCTRL_REGS->BUFF_STATUS.bit.EP3_OUT)
    {
#ifdef __DEBUG_USB__
        UsbReceived_EP3_OUT_count++;
#endif
       /* clear the EP3_OUT buffer status */
       USBCTRL_REGS->BUFF_STATUS.bit.EP3_OUT = 1;

       /* TODO: copy the received data and call the handler */

       EPx_dataPid[EP3] ^= 1u;
       UsbDriver_ConfigureEpOutBuf(EP3, EPx_dataPid[EP3], 64u);
    }
    if(USBCTRL_REGS->BUFF_STATUS.bit.EP3_IN)
    {
#ifdef __DEBUG_USB__
        UsbReceived_EP3_IN_count++;
#endif
       /* clear the EP3_IN buffer status */
       USBCTRL_REGS->BUFF_STATUS.bit.EP3_IN = 1;

       /* TODO: notify the handler */

       /* update the EP3_OUT buffer config with the new expect data pid */
       EPx_dataPid[EP3] ^= 1u;
       UsbDriver_ConfigureEpOutBuf(EP3, EPx_dataPid[EP3], 64u);
    }
  }

  /* handle EP's NAK and STALL notification */
  if(USBCTRL_REGS->INTS.bit.EP_STALL_NAK)
  {
    if(USBCTRL_REGS->EP_STATUS_STALL_NAK.bit.EP1_IN)
    {
      /* NAK token was sent by the device controller as response for IN token from host. 
         this means that the host is requesting a DATA packet on EP1_IN
      */
       /* clear the EP1_IN NAK interrupt flag */
       USBCTRL_REGS->EP_STATUS_STALL_NAK.bit.EP1_IN = 1u;

       /* send back the last received data from the host (echo test) */
       uint8* const pBuffer_EP1 = (uint8*)((uint32)(USBCTRL_DPRAM_BASE + 0x100u + (EP1 * 0x80u)));
       UsbDriver_SendDataToHost(EP1, EPx_dataPid[EP1], pBuffer_EP1, 4u);
    }

    if(USBCTRL_REGS->EP_STATUS_STALL_NAK.bit.EP2_IN)
    {
      /* NAK token was sent by the device controller as response for IN token from host.
         this means that the host is requesting a DATA packet on EP2_IN
      */
       /* clear the EP2_IN NAK interrupt flag */
       USBCTRL_REGS->EP_STATUS_STALL_NAK.bit.EP2_IN = 1u;
    }

    if(USBCTRL_REGS->EP_STATUS_STALL_NAK.bit.EP3_IN)
    {
      /* NAK token was sent by the device controller as response for IN token from host.
         this means that the host is requesting a DATA packet on EP3_IN
      */
       /* clear the EP3_IN NAK interrupt flag */
       USBCTRL_REGS->EP_STATUS_STALL_NAK.bit.EP3_IN = 1u;
    }
  }
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void UsbInit(void)
{
   //release the reset of PLL_USB
   RESETS->RESET.bit.pll_usb = 0u;
   while(RESETS->RESET_DONE.bit.pll_usb != 1);

   //configure the PLL_USB
   PLL_USB->CS.bit.REFDIV           = 1u;
   PLL_USB->FBDIV_INT.bit.FBDIV_INT = 40U;
   PLL_USB->PRIM.bit.POSTDIV1       = 5U;
   PLL_USB->PRIM.bit.POSTDIV2       = 2U;

   PLL_USB->PWR.bit.PD        = 0u;
   PLL_USB->PWR.bit.VCOPD     = 0u;

   while(PLL_USB->CS.bit.LOCK != 1u);

   PLL_USB->PWR.bit.POSTDIVPD = 0u;

   // switch the system clock to use the PLL
   CLOCKS->CLK_SYS_CTRL.bit.AUXSRC = CLOCKS_CLK_SYS_CTRL_AUXSRC_clksrc_pll_sys;
   CLOCKS->CLK_SYS_CTRL.bit.SRC    = CLOCKS_CLK_SYS_CTRL_SRC_clksrc_clk_sys_aux;

   //switch on the USB clock
   CLOCKS->CLK_USB_CTRL.bit.AUXSRC = CLOCKS_CLK_USB_CTRL_AUXSRC_clksrc_pll_usb;
   CLOCKS->CLK_USB_CTRL.bit.ENABLE = 1u;

   // switch off the ROSC clock

   //release reset of usb
    RESETS->RESET.bit.usbctrl = 0u;
    while(RESETS->RESET_DONE.bit.usbctrl != 1);

    //clear the DPRAM
    for(uint32 i=0; i < 4096U; i = i+8)
    {
      *(volatile uint64*)(USBCTRL_DPRAM_BASE + i) = 0;
    }

    //enable USB
    USBCTRL_REGS->USB_MUXING.bit.TO_PHY       = 1u;
    USBCTRL_REGS->USB_MUXING.bit.SOFTCON      = 0u;
    USBCTRL_REGS->MAIN_CTRL.bit.HOST_NDEVICE  = 0u;

    USBCTRL_REGS->USB_PWR.bit.VBUS_DETECT = 1u;
    USBCTRL_REGS->USB_PWR.bit.VBUS_DETECT_OVERRIDE_EN = 1u;

    USBCTRL_REGS->MAIN_CTRL.bit.CONTROLLER_EN = 1u;

    USBCTRL_REGS->SIE_CTRL.bit.EP0_INT_1BUF   = 1u;

    //enable usb interrupt
    USBCTRL_REGS->INTE.bit.BUFF_STATUS  = 1u; // note: this interrupt is needed to detect OUT and IN requests send by the host.
    USBCTRL_REGS->INTE.bit.BUS_RESET    = 1u; // note: this interrupt is needed to detect a reset state on the USB bus.
    USBCTRL_REGS->INTE.bit.SETUP_REQ    = 1u; // note: this interrupt is needed to notify the CPU about a received SETUP packet.
    USBCTRL_REGS->INTE.bit.EP_STALL_NAK = 1u; // note: this interrupt is needed to notify the CPU about a sent/received NAK/STALL packet.

    //enable NVIC
    NVIC_EnableIRQ(USBCTRL_IRQ_IRQn);
    __enable_irq();

    /* enable endpoint 1 */
    UsbDriver_ConfigureEndpoint(EP1, EP_DIR_IN, 2u);
    UsbDriver_ConfigureEndpoint(EP1, EP_DIR_OUT, 2u);
    UsbDriver_ConfigureEpOutBuf(EP1, EPx_dataPid[EP1], 64u);

    /* enable endpoint 2 */
    UsbDriver_ConfigureEndpoint(EP2, EP_DIR_IN, 2u);
    UsbDriver_ConfigureEndpoint(EP2, EP_DIR_OUT, 2u);
    UsbDriver_ConfigureEpOutBuf(EP2, EPx_dataPid[EP2], 64u);

    /* enable endpoint 3 */
    UsbDriver_ConfigureEndpoint(EP3, EP_DIR_IN, 3u);

#ifdef __DEBUG_HALT__
    while(boHaltBeforeEnableUsb);
#endif

    /* enable the USB controller */
    USBCTRL_REGS->SIE_CTRL.bit.PULLUP_EN      = 1u;

}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static boolean UsbDriver_ConfigureEndpoint(uint8 endpoint, uint8 direction, uint8 type)
{
  boolean status = FALSE;

  if(endpoint > 0u && endpoint < 16u)
  {
    if(EP_DIR_IN == direction)
    {
      volatile EPx_CONTROL* epx_in_control  = (volatile EPx_CONTROL*)(USBCTRL_DPRAM_BASE + (EPx_IN_CONTROL_OFFSET * endpoint));
      epx_in_control->reg                    = 0;
      epx_in_control->bit.INTERRUPT_PER_BUFF = 1u;
      epx_in_control->bit.INTERRUPT_ON_NAK   = 1u;
      epx_in_control->bit.INTERRUPT_ON_STALL = 1u;
      epx_in_control->bit.ENDPOINT_TYPE      = type & 0x03u;
      epx_in_control->bit.BUFFER_ADDRESS     = (uint16)(0x100u + (endpoint * 0x80u));
      epx_in_control->bit.ENABLE             = 1u;
    }
    else if(EP_DIR_OUT == direction)
    {
      volatile EPx_CONTROL* epx_out_control = (volatile EPx_CONTROL*)(USBCTRL_DPRAM_BASE + EPx_OUT_CONTROL_OFFSET + ((endpoint)* 8ul));
      epx_out_control->reg                    = 0u;
      epx_out_control->bit.INTERRUPT_PER_BUFF = 1u;
      epx_out_control->bit.ENDPOINT_TYPE      = type & 0x03u;
      epx_out_control->bit.BUFFER_ADDRESS     = (uint16)(0x100u + (endpoint * 0x80u));
      epx_out_control->bit.ENABLE             = 1u;
    }
    else
    {
      /* wrong endpoint direction */
      return(status);
    }
    status = TRUE;
  }

  return(status);
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static boolean UsbDriver_SendDataToHost(uint8 endpoint, uint8 pid, uint8* buffer, uint8 size)
{
  boolean status = FALSE;

  EPx_BUFFER_CONTROL* epx_in_buffer_control = (EPx_BUFFER_CONTROL*)(USBCTRL_DPRAM_BASE + EPx_IN_BUFFER_CONTROL_OFFSET + (endpoint * 8ul));

  if((size < 65u) && (endpoint < 16u) && (pid < 2u))
  {
    if(buffer != NULL)
    {
      for(uint8 i = 0; i < size; i++)
      {
        ((volatile uint8*)(USBCTRL_DPRAM_BASE + 0x100ul + (endpoint * 0x80ul)))[i] = buffer[i];
      }
    }

    epx_in_buffer_control->reg             = 0;
    epx_in_buffer_control->bit.LENGTH_0    = size;
    epx_in_buffer_control->bit.AVAILABLE_0 = 1u;
    epx_in_buffer_control->bit.PID_0       = (pid == 0 ? 0 : 1);
    epx_in_buffer_control->bit.FULL_0      = 1u;

    status = TRUE;
  }

  return(status);
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static boolean UsbDriver_SendStallToHost(uint8 endpoint, uint8 pid)
{
  boolean status = FALSE;

  EPx_BUFFER_CONTROL* epx_in_buffer_control = (EPx_BUFFER_CONTROL*)(USBCTRL_DPRAM_BASE + EPx_IN_BUFFER_CONTROL_OFFSET + (endpoint * 8ul));

  if((endpoint < 16u) && (pid < 2u))
  {
    epx_in_buffer_control->reg             = 0;
    epx_in_buffer_control->bit.LENGTH_0    = 0;
    epx_in_buffer_control->bit.AVAILABLE_0 = 1u;
    epx_in_buffer_control->bit.PID_0       = (pid == 0 ? 0 : 1);
    epx_in_buffer_control->bit.STALL       = 1u;

    if(endpoint == EP0)
    {
      USBCTRL_REGS->EP_STALL_ARM.bit.EP0_IN  = 1u;
    }
    epx_in_buffer_control->bit.FULL_0      = 1u;

    status = TRUE;
  }

  return(status);
}
//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static boolean UsbDriver_ConfigureEpOutBuf(uint8 endpoint, uint8 pid, uint8 size)
{
  boolean status = FALSE;

  EPx_BUFFER_CONTROL* epx_out_buffer_control = (EPx_BUFFER_CONTROL*)(USBCTRL_DPRAM_BASE + EPx_OUT_BUFFER_CONTROL_OFFSET + (endpoint * 8ul));
  
  if((size < 65u) && (endpoint < 16u) && (pid < 2u))
  {
    /* configure the expected OUT packet */
    epx_out_buffer_control->reg             = 0;
    epx_out_buffer_control->bit.LENGTH_0    = size;
    epx_out_buffer_control->bit.AVAILABLE_0 = 1u;
    epx_out_buffer_control->bit.PID_0       = (pid == 0 ? 0 : 1);
    epx_out_buffer_control->bit.FULL_0      = 0u;
    status = TRUE;
  }

  return(status);
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UsbDriver_HandleSetupPacket(const tUsbSetupPacket* const pUsbSetupPacket)
{
  const uint8 Request = pUsbSetupPacket->bRequest;
  const tbmRequestType* const bmRequestType = (tbmRequestType*)(pUsbSetupPacket);

  if((bmRequestType->Type == USB_REQ_TYPE_STANDARD) && (Request < 13u) && (StandardRequestHandlerLockupTable[Request] != NULL))
  {
    /* call the appropriate handler */
    StandardRequestHandlerLockupTable[Request](pUsbSetupPacket);
  }
  else if(bmRequestType->Type == USB_REQ_TYPE_CLASS)
  {
    /* class specific requests */
    if(bmRequestType->TransferDirection == USB_REQ_DIR_DEVICE_TO_HOST)
    {
      /* IN token is expected from the host, handle the specific request immediatly to the upper layer */
      if(Request == 0x21u)
      {
        /* GET_LINE_CODING */
        uint8 LineCodingFormat[7] = { 0x80,
                                      0x25,
                                      0,
                                      0,
                                      0,
                                      0,
                                      8
                                    };
        UsbDriver_SendDataToHost(EP0, DATA1_PID, (uint8*)LineCodingFormat, 7u);
      }
    }
    else
    {
      /* OUT token is expected from the host, handle the specific request to upper layer after receiving the data on EP0 */
      if(Request == 0x20u)
      {
        /* SET_LINE_CODING */
        UsbDriver_SendDataToHost(EP0, DATA1_PID, NULL, 0);
      }
      else if(Request == 0x22u)
      {
        /* SET_CONTROL_LINE_STATE */
        UsbDriver_SendDataToHost(EP0, DATA1_PID, NULL, 0);
      }
      else
      {
      }
    }
#ifdef __DEBUG_USB__
    _EP0_SpecificReq[_EP0_SpecificReq_index++] = *(volatile uint64*)pUsbSetupPacket;
#endif
  }
  else
  {
    for(;;);
  }
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UsbDriver_Req_get_status(const tUsbSetupPacket* const pUsbSetupPacket)
{
  (void)pUsbSetupPacket;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UsbDriver_Req_clear_feature(const tUsbSetupPacket* const pUsbSetupPacket)
{
  (void)pUsbSetupPacket;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UsbDriver_Req_set_feature(const tUsbSetupPacket* const pUsbSetupPacket)
{
  (void)pUsbSetupPacket;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UsbDriver_Req_set_address(const tUsbSetupPacket* const pUsbSetupPacket)
{
  UsbDeviceAddress = pUsbSetupPacket->wValue;
  UsbDriver_SendDataToHost(EP0, DATA1_PID, NULL, 0);
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UsbDriver_Req_get_descriptor(const tUsbSetupPacket* const pUsbSetupPacket)
{
  const uint8 DescriptorType = (uint8)(pUsbSetupPacket->wValue >> 8);

  if(USB_DESCRIPTOR_TYPE_DEVICE == DescriptorType)
  {
      /* send the device descriptor */
      const unsigned char device_dsc[0x12] = {
                                                0x12,         // bLength
                                                0x01,         // bDescriptorType (Device)
                                                0x10, 0x01,   // bcdUSB (1.1)
                                                0xEF,         // bDeviceClass (Miscellaneous Device Class)
                                                0x02,         // bDeviceSubClass (Common Class)
                                                0x01,         // bDeviceProtocol (Interface Association Descriptor)
                                                0x40,         // bMaxPacketSize0 (64 bytes)
                                                0x8a, 0x2e,   // idVendor
                                                0x0a, 0x00,   // idProduct
                                                0x01, 0x00,   // bcdDevice (Device Version 0.01)
                                                0x01,         // iManufacturer (String Index 1)
                                                0x02,         // iProduct (String Index 2)
                                                0x03,         // iSerialNumber (String Index 3)
                                                0x01          // bNumConfigurations (1 configuration)
                                             };
      UsbDriver_SendDataToHost(EP0, DATA1_PID, (uint8*)device_dsc, sizeof(device_dsc));
    }
    else if(USB_DESCRIPTOR_TYPE_CONFIGURATION == DescriptorType)
    {
      /* send configuration descriptor */
      static const uint8 configuration_dsc[] = {
          /* Configuration Descriptor */
          0x09,                                 // bLength: Configuration Descriptor size
          0x02,                                 // bDescriptorType: Configuration
          98, 0x00,                             // wTotalLength: The number of bytes in the configuration descriptor and all of its subordinate descriptors
          0x03,                                 // bNumInterfaces: 3 interfaces (1 for vendor custom class, 1 for CDC Control and 1 for CDC Data)
          0x01,                                 // bConfigurationValue: this Configuration index
          0x00,                                 // iConfiguration: Index of string descriptor describing the configuration
          0x80,                                 // bmAttributes: Self-powered
          250,                                  // bMaxPower: 500 mA

          // Interface Descriptor (vendor custom class)
          0x09,                                // bLength - Descriptor size in bytes (09h)
          0x04,                                // bDescriptorType - The constant Interface (04h)
          0,                                   // bInterfaceNumber - Interface number 0
          0,                                   // bAlternateSetting - A number that identifies a descriptor with alternate settings for this bInterfaceNumber.
          2,                                   // bNumEndpoint - Number of endpoints supported not counting endpoint zero
          0xff,                                // bInterfaceClass - Class code
          0xff,                                // bInterfaceSubclass - Subclass code
          0xff,                                // bInterfaceProtocol - Protocol code
          0,                                   // iInterface - Interface string index
          
          // Endpoint Descriptor (IN)
          0x07,                                // bLength - Descriptor size in bytes (07h)
          0x05,                                // bDescriptorType - The constant Endpoint (05h)
          EP_DIR_IN | EP1,                     // bEndpointAddress - Endpoint number and direction
          0x02,                                // bmAttributes - Transfer type and supplementary information
          0x40,0x00,                           // wMaxPacketSize - Maximum packet size supported
          255,                                 // bInterval - Service interval or NAK rate
          
          // Endpoint Descriptor (OUT)
          0x07,                                // bLength - Descriptor size in bytes (07h)
          0x05,                                // bDescriptorType - The constant Endpoint (05h)
          EP_DIR_OUT | EP1,                    // bEndpointAddress - Endpoint number and direction
          0x02,                                // bmAttributes - Transfer type and supplementary information
          0x40,0x00,                           // wMaxPacketSize - Maximum packet size supported
          255,                                 // bInterval - Service interval or NAK rate

          /* Interface Association Descriptor (IAD) for CDC/ACM */
          0x08,                                // bLength: Interface Descriptor size
          0x0B,                                // bDescriptorType: IAD
          0x01,                                // bFirstInterface: First interface number (1)
          0x02,                                // bInterfaceCount: Number of interfaces for this function (2)
          0x02,                                // bFunctionClass: Communication Interface Class (CDC)
          0x02,                                // bFunctionSubClass: Abstract Control Model (ACM)
          0x00,                                // bFunctionProtocol: ????
          0x00,                                // iFunction: Index of string descriptor describing this function
      
          /* Interface Descriptor (CDC Control) */
          0x09,                                // bLength: Interface Descriptor size
          0x04,                                // bDescriptorType: Interface
          1,                                   // bInterfaceNumber: Interface number 1
          0x00,                                // bAlternateSetting: Alternate setting
          0x01,                                // bNumEndpoints: One endpoint (CDC Control)
          0x02,                                // bInterfaceClass: CDC
          0x02,                                // bInterfaceSubClass: Abstract Control Model
          0x00,                                // bInterfaceProtocol: V.25ter (AT commands)
          0x00,                                // iInterface: Index of string descriptor describing this interface
      
          /* CDC Header Functional Descriptor */
          0x05,                                // bLength: CDC header Descriptor size
          0x24,                                // bDescriptorType: CS_INTERFACE
          0x00,                                // bDescriptorSubType: Header
          0x20, 0x01,                          // bcdCDC: CDC specification release number
      
          /* CDC Call Management Functional Descriptor */
          0x05,                                // bLength: CDC Call Management Descriptor size
          0x24,                                // bDescriptorType: CS_INTERFACE
          0x01,                                // bDescriptorSubType: Call Management
          0x00,                                // bmCapabilities: Device does not handle call management itself
          0x02,                                // bDataInterface: Interface number of Data Class interface
      
          /* CDC Abstract Control Management Functional Descriptor */
          0x04,                                // bLength: CDC Abstract Control Management Descriptor size
          0x24,                                // bDescriptorType: CS_INTERFACE
          0x02,                                // bDescriptorSubType: Abstract Control Management
          0x02,                                // bmCapabilities: Device supports the request combination of Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State
      
          /* CDC Union Functional Descriptor */
          0x05,                                // bLength: CDC Union Descriptor size
          0x24,                                // bDescriptorType: CS_INTERFACE
          0x06,                                // bDescriptorSubType: Union
          0x01,                                // bControlInterface: Interface number of the Control interface
          0x02,                                // bSubordinateInterface0: Interface number of the subordinate interface
      
          /* Endpoint Descriptor (CDC Control IN) */
          0x07,                                // bLength: Endpoint Descriptor size
          0x05,                                // bDescriptorType: Endpoint
          EP_DIR_IN | EP3,                     // bEndpointAddress: CDC Control endpoint address (IN)
          0x03,                                // bmAttributes: Interrupt
          0x08, 0x00,                          // wMaxPacketSize: CDC Control packet size (8 bytes)
          0x10,                                // bInterval: Polling interval (16ms)
      
          /* Interface Descriptor (CDC Data) */
          0x09,                                // bLength: Interface Descriptor size
          0x04,                                // bDescriptorType: Interface
          2,                                   // bInterfaceNumber: Interface number 2
          0x00,                                // bAlternateSetting: Alternate setting
          0x02,                                // bNumEndpoints: Two endpoints (CDC Data)
          0x0A,                                // bInterfaceClass: CDC Data
          0x00,                                // bInterfaceSubClass
          0x00,                                // bInterfaceProtocol
          0x00,                                // iInterface: Index of string descriptor describing this interface
      
          /* Endpoint Descriptor (CDC Data IN) */
          0x07,                                // bLength: Endpoint Descriptor size
          0x05,                                // bDescriptorType: Endpoint
          EP_DIR_IN | EP2,                     // bEndpointAddress: CDC Data IN endpoint address
          0x02,                                // bmAttributes: Bulk
          0x40, 0x00,                          // wMaxPacketSize: CDC Data packet size (64 bytes)
          0x00,                                // bInterval: Never NAK
      
          /* Endpoint Descriptor (CDC Data OUT) */
          0x07,                                // bLength: Endpoint Descriptor size
          0x05,                                // bDescriptorType: Endpoint
          EP_DIR_OUT | EP2,                    // bEndpointAddress: CDC Data OUT endpoint address
          0x02,                                // bmAttributes: Bulk
          0x40, 0x00,                          // wMaxPacketSize: CDC Data packet size (64 bytes)
          0x00                                 // bInterval: Never NAK
      };


      /* check the configuration size requested by the host 
         note: we must send exactly the requested size otherwise the host will abort the enumeration process */
      const uint8 size = (((uint8)(pUsbSetupPacket->wLength) > sizeof(configuration_dsc)) && (sizeof(configuration_dsc) < 65u)) ? sizeof(configuration_dsc) : (uint8)(pUsbSetupPacket->wLength);

      const uint8 number_of_64_packet_size   = sizeof(configuration_dsc) / 64u;
      const uint8 remaining_config_data_size = sizeof(configuration_dsc) % 64u;

      EPx_BUFFER_CONTROL* epx_in_buffer_control = (EPx_BUFFER_CONTROL*)(USBCTRL_DPRAM_BASE + EPx_IN_BUFFER_CONTROL_OFFSET + (EP0 * 8ul));

      if(size > 64u)
      {
        uint8 data_pid = DATA1_PID;

        for(uint32 i=0; i < number_of_64_packet_size; i++)
        {
          UsbDriver_SendDataToHost(EP0, data_pid, (uint8*)((uint32)configuration_dsc + i*64u), (uint8)64);
          
          data_pid ^= 1u;

          /* wait till the buffer got transmitterd */
          while(epx_in_buffer_control->bit.FULL_0);
        }

        /* send the remaining data */
        UsbDriver_SendDataToHost(EP0, data_pid, (uint8*)((uint32)configuration_dsc + number_of_64_packet_size*64u), (uint8)remaining_config_data_size);

      }
      else
      {
        /* only one packet of 64-byte max */
        /* send the configuration to the host */
        UsbDriver_SendDataToHost(EP0, DATA1_PID, (uint8*)configuration_dsc, (uint8)size);
      }
    }
    else if(USB_DESCRIPTOR_TYPE_HID_REPORT == DescriptorType)
    {
      const uint8 hid_rpt_desc[] =
        {
            0x06, 0x00, 0xFF,       // Usage Page = 0xFF00 (Vendor Defined Page 1)
            0x09, 0x01,             // Usage (Vendor Usage 1)
            0xA1, 0x01,             // Collection (Application)
            // Input report
            0x19, 0x01,             // Usage Minimum
            0x29, 0x40,             // Usage Maximum
            0x15, 0x00,             // Logical Minimum (data bytes in the report may have minimum value = 0x00)
            0x26, 0xFF, 0x00,       // Logical Maximum (data bytes in the report may have maximum value = 0x00FF = unsigned 255)
            0x75, 0x08,             // Report Size: 8-bit field size
            0x95, 64,               // Report Count
            0x81, 0x02,             // Input (Data, Array, Abs)
            // Output report
            0x19, 0x01,             // Usage Minimum
            0x29, 0x40,             // Usage Maximum
            0x75, 0x08,             // Report Size: 8-bit field size
            0x95, 64,               // Report Count
            0x91, 0x02,             // Output (Data, Array, Abs)
            0xC0                    // End Collection
        };

         UsbDriver_SendDataToHost(EP0, DATA1_PID, (uint8*)hid_rpt_desc, sizeof(hid_rpt_desc));

    }
    else if(USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER == DescriptorType)
    {
      /* As DEVICE_QUALIFIER is used only for high speed we will not support it on RP2350 (has only a full speed device controller) */
      UsbDriver_SendStallToHost(EP0, DATA1_PID);
    }
    else if(USB_DESCRIPTOR_TYPE_STRING == DescriptorType)
    {
      const tUsbStringDescriptor UsbStringDescriptor = {4, 0x03, {0x0409}};
      const tUsbSubsequentStringDescriptor UsbSubsequentStringDescriptor_0 = {30, 0x03, {'C','H','A','L','A','N','D','I',' ','A','M','I','N','E'}};              /* Manufacturer string descriptor */
      const tUsbSubsequentStringDescriptor UsbSubsequentStringDescriptor_1 = {36, 0x03, {'C','H','A','L','A','N','D','I',' ','D','E','B','U','G','G','E','R'}};  /* Product string descriptor */
      const tUsbSubsequentStringDescriptor UsbSubsequentStringDescriptor_2 = {10, 0x03, {'2','0','2','3'}};                                                      /* SerialNumber */
     
      const uint8 StrIdx = (uint8)pUsbSetupPacket->wValue;

      if(StrIdx == 0u)
      {
        UsbDriver_SendDataToHost(EP0, DATA1_PID, (uint8*)&UsbStringDescriptor,UsbStringDescriptor.bLength);
      }
      else if(StrIdx == 1u)
      {
        UsbDriver_SendDataToHost(EP0, DATA1_PID, (uint8*)&UsbSubsequentStringDescriptor_0, UsbSubsequentStringDescriptor_0.bLength);
      }
      else if(StrIdx == 2u)
      {
        UsbDriver_SendDataToHost(EP0, DATA1_PID, (uint8*)&UsbSubsequentStringDescriptor_1, UsbSubsequentStringDescriptor_1.bLength);
      }
      else if(StrIdx == 3u)
      {
        UsbDriver_SendDataToHost(EP0, DATA1_PID, (uint8*)&UsbSubsequentStringDescriptor_2, UsbSubsequentStringDescriptor_2.bLength);
      }
      else
      {
        UsbDriver_SendStallToHost(EP0, DATA1_PID);
      }
    }
    else
    {

    }
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UsbDriver_Req_set_descriptor(const tUsbSetupPacket* const pUsbSetupPacket)
{
  (void)pUsbSetupPacket;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UsbDriver_Req_get_configuration(const tUsbSetupPacket* const pUsbSetupPacket)
{
  /* as we have only one configuration just send one to the host */
  (void)pUsbSetupPacket;
  const uint8 config = 1;
  UsbDriver_SendDataToHost(EP0, DATA1_PID, (uint8*)&config, 1);
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UsbDriver_Req_set_configuration(const tUsbSetupPacket* const pUsbSetupPacket)
{
  /* as we have only one configuration just send ACK to the host */
  (void)pUsbSetupPacket;
  UsbDriver_SendDataToHost(EP0, DATA1_PID, NULL, 0);
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UsbDriver_Req_get_interface(const tUsbSetupPacket* const pUsbSetupPacket)
{
  (void)pUsbSetupPacket;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UsbDriver_Req_set_interface(const tUsbSetupPacket* const pUsbSetupPacket)
{
  (void)pUsbSetupPacket;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
static void UsbDriver_Req_synch_frame(const tUsbSetupPacket* const pUsbSetupPacket)
{
  (void)pUsbSetupPacket;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void UsbDriver_SendSerialMsg(uint8* msg)
{
  UsbDriver_SendDataToHost(EP2, EPx_dataPid[EP2], (uint8*)msg, (uint8)strlen((const char*)msg));
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
boolean UsbDriver_IsDeviceConnected(void)
{
  return(USBCTRL_REGS->SIE_STATUS.bit.CONNECTED == 1u ? TRUE : FALSE);
}
