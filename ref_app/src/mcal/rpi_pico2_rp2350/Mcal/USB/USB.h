/******************************************************************************************
  Filename    : USB.h
  
  Core        : ARM Cortex-M33 / RISC-V Hazard3
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.09.2024
  
  Description : USB low level device driver header file
  
******************************************************************************************/

#ifndef __USB_H__
#define __USB_H__

#include "Platform_Types.h"
#include "usb_types.h"

void USBCTRL_IRQ(void);
void UsbInit(void);
void UsbDriver_SendSerialMsg(uint8* msg);
boolean UsbDriver_IsDeviceConnected(void);

/* endpoints IDs */
#define EP0      0u
#define EP1      1u
#define EP2      2u
#define EP3      3u
#define EP4      4u
#define EP5      5u
#define EP6      6u
#define EP7      7u
#define EP8      8u
#define EP9      9u
#define EP10    10u
#define EP11    11u
#define EP12    12u
#define EP13    13u
#define EP14    14u
#define EP15    15u

/* endpoints direction */
#define EP_DIR_IN   0x80
#define EP_DIR_OUT  0x00

/* Data PIDs */
#define DATA0_PID      0u
#define DATA1_PID      1u

/* SETUP Packet - Standard requests */
#define USB_REQ_GET_STATUS         0u
#define USB_REQ_CLEAR_FEATURE      1u
#define USB_REQ_SET_FEATURE        3u
#define USB_REQ_SET_ADDRESS        5u
#define USB_REQ_GET_DESCRIPTOR     6u
#define USB_REQ_SET_DESCRIPTOR     7u
#define USB_REQ_GET_CONFIGURATION  8u
#define USB_REQ_SET_CONFIGURATION  9u
#define USB_REQ_GET_INTERFACE     10u
#define USB_REQ_SET_INTERFACE     11u
#define USB_REQ_SYNCH_FRAME       12u

#define USB_REQ_DIR_DEVICE_TO_HOST       1u
#define USB_REQ_DIR_HOST_TO_DEVICE       0u

#define USB_REQ_TYPE_STANDARD            0u
#define USB_REQ_TYPE_CLASS               1u
#define USB_REQ_TYPE_VENDOR              2u
#define USB_REQ_TYPE_RESERVED            3u

#define USB_REQ_RECIPIENT_DEVICE         0u
#define USB_REQ_RECIPIENT_INTERFACE      1u
#define USB_REQ_RECIPIENT_ENDPOINT       2u

/* Descriptor Types */
#define USB_DESCRIPTOR_TYPE_DEVICE                     1u
#define USB_DESCRIPTOR_TYPE_CONFIGURATION              2u
#define USB_DESCRIPTOR_TYPE_STRING                     3u
#define USB_DESCRIPTOR_TYPE_INTERFACE                  4u
#define USB_DESCRIPTOR_TYPE_ENDPOINT                   5u
#define USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER           6u
#define USB_DESCRIPTOR_TYPE_OTHER_SPEED_CONFIGURATION  7u
#define USB_DESCRIPTOR_TYPE_INTERFACE_POWER            8u
#define USB_DESCRIPTOR_TYPE_HID_REPORT              0x22u


/* USB device type */
typedef struct
{
  uint32_t                     DeviceAddress;
  tUsbDeviceDescriptor         UsbDeviceDescriptor;
  tUsbEndpointDescriptor       UsbEndpointDescriptor; /* this must be a pointer to a pool of endpoints (maybe a linked list) */
  tUsbConfigurationDescriptor  UsbConfigurationDescriptor;
  uint8_t                      desc[];
}__attribute__((packed)) UsbDeviceDriverContainer_t;

#if 0
static UsbDeviceDriverContainer_t UsbDeviceDriverContainer = {
                                                                 /* DeviceAddress              */
                                                                 0,
                                                                 /* UsbDeviceDescriptor        */
                                                                 {
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
                                                                 },
                                                                 /* UsbEndpointDescriptor      */
                                                                 {
                                                                   0
                                                                 },
                                                                 /* UsbConfigurationDescriptor */
                                                                 {
                                                                      /* Configuration Descriptor */
                                                                      0x09,                                 // bLength: Configuration Descriptor size
                                                                      0x02,                                 // bDescriptorType: Configuration
                                                                      98, 0x00,                             // wTotalLength: The number of bytes in the configuration descriptor and all of its subordinate descriptors
                                                                      0x03,                                 // bNumInterfaces: 3 interfaces (1 for vendor custom class, 1 for CDC Control and 1 for CDC Data)
                                                                      0x01,                                 // bConfigurationValue: this Configuration index
                                                                      0x00,                                 // iConfiguration: Index of string descriptor describing the configuration
                                                                      0x80,                                 // bmAttributes: Self-powered
                                                                      250                                   // bMaxPower: 500 mA
                                                                 },
                                                                 {
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
                                                                     0x01,                                // bDataInterface: Interface number of Data Class interface
                                                                     
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
                                                                 }
                                                             };



#endif



#endif
