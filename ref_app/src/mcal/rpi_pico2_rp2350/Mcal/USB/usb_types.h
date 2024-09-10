
#ifndef __USB_TYPES_H__
#define __USB_TYPES_H__

#include "Platform_Types.h"

//------------------------------------------------------------------------------------------------------------------
// Setup Packet
//------------------------------------------------------------------------------------------------------------------
typedef struct
{
  uint8  bmRequestType;
  uint8  bRequest;
  uint16 wValue;
  uint16 wIndex;
  uint16 wLength;
}tUsbSetupPacket;

typedef struct
{
  uint8 Recipient:5u;
  uint8 Type:2u;
  uint8 TransferDirection:1u;
}tbmRequestType;

//------------------------------------------------------------------------------------------------------------------
// Device Descriptor
//------------------------------------------------------------------------------------------------------------------
typedef struct
{
  uint8  bLength;             //Size of the Descriptor in Bytes (18 bytes)
  uint8  bDescriptorType;     //Constant Device Descriptor (0x01)
  uint8  bcdUSB_L;            //USB Specification Number (LSB byte) which device complies too.
  uint8  bcdUSB_H;            //USB Specification Number (MSB byte) which device complies too.
  uint8  bDeviceClass;        //Class Code (Assigned by USB Org) If equal to Zero, each interface specifies it’s own class code If equal to 0xFF, the class code is vendor specified. Otherwise field is valid Class Code.
  uint8  bDeviceSubClass;     //SubClass Subclass Code (Assigned by USB Org)
  uint8  bDeviceProtocol;     //Protocol Protocol Code (Assigned by USB Org)
  uint8  bMaxPacketSize;      //Number Maximum Packet Size for Zero Endpoint. Valid Sizes are 8, 16, 32, 64
  uint8  idVendor_L;          //Vendor ID (LSB byte) (Assigned by USB Org)
  uint8  idVendor_H;          //Vendor ID (MSB byte) (Assigned by USB Org)
  uint8  idProduct_L;         //Product ID (LSB byte) (Assigned by Manufacturer)
  uint8  idProduct_H;         //Product ID (MSB byte) (Assigned by Manufacturer)
  uint8  bcdDevice_L;         //Device Release Number (LSB byte)
  uint8  bcdDevice_H;         //Device Release Number (MSB byte)
  uint8  iManufacturer;       //Index of Manufacturer String Descriptor
  uint8  iProduct;            //Index of Product String Descriptor
  uint8  iSerialNumber;       //Index of Serial Number String Descriptor
  uint8  bNumConfigurations;  //Number of Possible Configurations
}tUsbDeviceDescriptor;

//------------------------------------------------------------------------------------------------------------------
// Configuration Descriptor
//------------------------------------------------------------------------------------------------------------------
typedef struct
{
  uint8  bLength;              //Size of Descriptor in Bytes
  uint8  bDescriptorType;      //Configuration Descriptor (0x02)
  uint8  wTotalLength_L;       //Total length in bytes of data returned (LSB byte)
  uint8  wTotalLength_H;       //Total length in bytes of data returned (MSB byte)
  uint8  bNumInterfaces;       //Number of Interfaces
  uint8  bConfigurationValue;  //Value to use as an argument to select this configuration
  uint8  iConfiguration;       //Index of String Descriptor describing this configuration
  uint8  bmAttributes;         //D7 Reserved, set to 1. (USB 1.0 Bus Powered) D6 Self Powered, D5 Remote Wakeup, D4..0 Reserved, set to 0.
  uint8  bMaxPower;            //Maximum Power Consumption in 2mA units
}tUsbConfigurationDescriptor;

//------------------------------------------------------------------------------------------------------------------
// Interface Descriptor
//------------------------------------------------------------------------------------------------------------------
typedef struct
{
  uint8  bLength;             //Size of Descriptor in Bytes (9 Bytes)
  uint8  bDescriptorType;     //Interface Descriptor (0x04)
  uint8  bInterfaceNumber;    //Number of Interface
  uint8  bAlternateSetting;   //Value used to select alternative setting
  uint8  bNumEndpoints;       //Number of Endpoints used for this interface
  uint8  bInterfaceClass;     //Class Code (Assigned by USB Org)
  uint8  bInterfaceSubClass;  //Subclass Code (Assigned by USB Org)
  uint8  bInterfaceProtocol;  //Protocol Code (Assigned by USB Org)
  uint8  iInterface;          //Index of String Descriptor Describing this interface
}tUsbInterfaceDescriptor;

//------------------------------------------------------------------------------------------------------------------
// Endpoint Descriptor
//------------------------------------------------------------------------------------------------------------------
typedef struct
{
  uint8  bLength;           //Size of Descriptor in Bytes (7 bytes)
  uint8  bDescriptorType;   //Endpoint Descriptor (0x05)
  uint8  bEndpointAddress;  //Endpoint AddressBits 0..3b Endpoint Number.Bits 4..6b Reserved. Set to Zero Bits 7 Direction 0 = Out, 1 = In (Ignored for Control Endpoints)
  uint8  bmAttributes;      //Bits 0..1 Transfer Type
                            //00 = Control
                            //01 = Isochronous
                            //10 = Bulk
                            //11 = Interrupt
                            //Bits 2..7 are reserved. If Isochronous endpoint,
                            //Bits 3..2 = Synchronisation Type (Iso Mode)
                            //00 = No Synchonisation
                            //01 = Asynchronous
                            //10 = Adaptive
                            //11 = Synchronous
                            //Bits 5..4 = Usage Type (Iso Mode)
                            //00 = Data Endpoint
                            //01 = Feedback Endpoint
                            //10 = Explicit Feedback Data Endpoint
                            //11 = Reserved
  uint8  wMaxPacketSize_L;  //Maximum Packet Size this endpoint is capable of sending or receiving (LSB byte)
  uint8  wMaxPacketSize_H;  //Maximum Packet Size this endpoint is capable of sending or receiving (MSB byte)
  uint8  bInterval;         //Interval for polling endpoint data transfers. Value in frame counts. Ignored for Bulk & Control Endpoints. Isochronous must equal 1 and field may range from 1 to 255 for interrupt endpoints.
}tUsbEndpointDescriptor;

//------------------------------------------------------------------------------------------------------------------
// String Descriptors
//------------------------------------------------------------------------------------------------------------------
#define USB_NUMBER_OF_SUPPORTED_LANGUAGE  1U
#define USB_MAX_STRING_LENGTH             50U

typedef struct
{
  uint8  bLength;                                    //Size of Descriptor in Bytes
  uint8  bDescriptorType;                            //String Descriptor (0x03)
  uint16 wLANGID[USB_NUMBER_OF_SUPPORTED_LANGUAGE];  //Supported Language Code (e.g. 0x0409 English - United States)
}tUsbStringDescriptor;


typedef struct
{
  uint8  bLength;                         //Size of Descriptor in Bytes
  uint8  bDescriptorType;                 //String Descriptor (0x03)
  uint16 bString[USB_MAX_STRING_LENGTH];  //Unicode Encoded String
}tUsbSubsequentStringDescriptor;

#endif
