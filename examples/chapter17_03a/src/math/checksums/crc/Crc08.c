/*/////////////////////////////////////////////////////////*/
/*  Copyright Christopher Kormanyos 2017 - 2018.           */
/*  Distributed under the Boost Software License,          */
/*  Version 1.0. (See accompanying file LICENSE_1_0.txt    */
/*  or copy at http://www.boost.org/LICENSE_1_0.txt)       */
/*/////////////////////////////////////////////////////////*/

#include <math/checksums/crc/Crc08.h>
#include <mcal_memory_progmem.h>

void Crc08_Initialize(Crc08_Context_Type* Crc_Context)
{
  /* Set the initial value. */
  Crc_Context->Crc_Value = UINT8_C(0xFF);
}

void Crc08_ProcessBytes(const uint8_t*      DataIn,
                        const size_t        DataLength,
                        Crc08_Context_Type* Crc_Context)
{
  size_t LoopCnt;

  /* Loop through the input data stream */
  for(LoopCnt = 0U; LoopCnt < DataLength; ++LoopCnt)
  {
    /* CRC-8/AUTOSAR Table based on 8-bit BYTEs. */

    static const uint8_t Crc08_Table[256U] MY_PROGMEM =
    {
      UINT8_C(0x00), UINT8_C(0x2F), UINT8_C(0x5E), UINT8_C(0x71), UINT8_C(0xBC), UINT8_C(0x93), UINT8_C(0xE2), UINT8_C(0xCD),
      UINT8_C(0x57), UINT8_C(0x78), UINT8_C(0x09), UINT8_C(0x26), UINT8_C(0xEB), UINT8_C(0xC4), UINT8_C(0xB5), UINT8_C(0x9A),
      UINT8_C(0xAE), UINT8_C(0x81), UINT8_C(0xF0), UINT8_C(0xDF), UINT8_C(0x12), UINT8_C(0x3D), UINT8_C(0x4C), UINT8_C(0x63),
      UINT8_C(0xF9), UINT8_C(0xD6), UINT8_C(0xA7), UINT8_C(0x88), UINT8_C(0x45), UINT8_C(0x6A), UINT8_C(0x1B), UINT8_C(0x34),
      UINT8_C(0x73), UINT8_C(0x5C), UINT8_C(0x2D), UINT8_C(0x02), UINT8_C(0xCF), UINT8_C(0xE0), UINT8_C(0x91), UINT8_C(0xBE),
      UINT8_C(0x24), UINT8_C(0x0B), UINT8_C(0x7A), UINT8_C(0x55), UINT8_C(0x98), UINT8_C(0xB7), UINT8_C(0xC6), UINT8_C(0xE9),
      UINT8_C(0xDD), UINT8_C(0xF2), UINT8_C(0x83), UINT8_C(0xAC), UINT8_C(0x61), UINT8_C(0x4E), UINT8_C(0x3F), UINT8_C(0x10),
      UINT8_C(0x8A), UINT8_C(0xA5), UINT8_C(0xD4), UINT8_C(0xFB), UINT8_C(0x36), UINT8_C(0x19), UINT8_C(0x68), UINT8_C(0x47),
      UINT8_C(0xE6), UINT8_C(0xC9), UINT8_C(0xB8), UINT8_C(0x97), UINT8_C(0x5A), UINT8_C(0x75), UINT8_C(0x04), UINT8_C(0x2B),
      UINT8_C(0xB1), UINT8_C(0x9E), UINT8_C(0xEF), UINT8_C(0xC0), UINT8_C(0x0D), UINT8_C(0x22), UINT8_C(0x53), UINT8_C(0x7C),
      UINT8_C(0x48), UINT8_C(0x67), UINT8_C(0x16), UINT8_C(0x39), UINT8_C(0xF4), UINT8_C(0xDB), UINT8_C(0xAA), UINT8_C(0x85),
      UINT8_C(0x1F), UINT8_C(0x30), UINT8_C(0x41), UINT8_C(0x6E), UINT8_C(0xA3), UINT8_C(0x8C), UINT8_C(0xFD), UINT8_C(0xD2),
      UINT8_C(0x95), UINT8_C(0xBA), UINT8_C(0xCB), UINT8_C(0xE4), UINT8_C(0x29), UINT8_C(0x06), UINT8_C(0x77), UINT8_C(0x58),
      UINT8_C(0xC2), UINT8_C(0xED), UINT8_C(0x9C), UINT8_C(0xB3), UINT8_C(0x7E), UINT8_C(0x51), UINT8_C(0x20), UINT8_C(0x0F),
      UINT8_C(0x3B), UINT8_C(0x14), UINT8_C(0x65), UINT8_C(0x4A), UINT8_C(0x87), UINT8_C(0xA8), UINT8_C(0xD9), UINT8_C(0xF6),
      UINT8_C(0x6C), UINT8_C(0x43), UINT8_C(0x32), UINT8_C(0x1D), UINT8_C(0xD0), UINT8_C(0xFF), UINT8_C(0x8E), UINT8_C(0xA1),
      UINT8_C(0xE3), UINT8_C(0xCC), UINT8_C(0xBD), UINT8_C(0x92), UINT8_C(0x5F), UINT8_C(0x70), UINT8_C(0x01), UINT8_C(0x2E),
      UINT8_C(0xB4), UINT8_C(0x9B), UINT8_C(0xEA), UINT8_C(0xC5), UINT8_C(0x08), UINT8_C(0x27), UINT8_C(0x56), UINT8_C(0x79),
      UINT8_C(0x4D), UINT8_C(0x62), UINT8_C(0x13), UINT8_C(0x3C), UINT8_C(0xF1), UINT8_C(0xDE), UINT8_C(0xAF), UINT8_C(0x80),
      UINT8_C(0x1A), UINT8_C(0x35), UINT8_C(0x44), UINT8_C(0x6B), UINT8_C(0xA6), UINT8_C(0x89), UINT8_C(0xF8), UINT8_C(0xD7),
      UINT8_C(0x90), UINT8_C(0xBF), UINT8_C(0xCE), UINT8_C(0xE1), UINT8_C(0x2C), UINT8_C(0x03), UINT8_C(0x72), UINT8_C(0x5D),
      UINT8_C(0xC7), UINT8_C(0xE8), UINT8_C(0x99), UINT8_C(0xB6), UINT8_C(0x7B), UINT8_C(0x54), UINT8_C(0x25), UINT8_C(0x0A),
      UINT8_C(0x3E), UINT8_C(0x11), UINT8_C(0x60), UINT8_C(0x4F), UINT8_C(0x82), UINT8_C(0xAD), UINT8_C(0xDC), UINT8_C(0xF3),
      UINT8_C(0x69), UINT8_C(0x46), UINT8_C(0x37), UINT8_C(0x18), UINT8_C(0xD5), UINT8_C(0xFA), UINT8_C(0x8B), UINT8_C(0xA4),
      UINT8_C(0x05), UINT8_C(0x2A), UINT8_C(0x5B), UINT8_C(0x74), UINT8_C(0xB9), UINT8_C(0x96), UINT8_C(0xE7), UINT8_C(0xC8),
      UINT8_C(0x52), UINT8_C(0x7D), UINT8_C(0x0C), UINT8_C(0x23), UINT8_C(0xEE), UINT8_C(0xC1), UINT8_C(0xB0), UINT8_C(0x9F),
      UINT8_C(0xAB), UINT8_C(0x84), UINT8_C(0xF5), UINT8_C(0xDA), UINT8_C(0x17), UINT8_C(0x38), UINT8_C(0x49), UINT8_C(0x66),
      UINT8_C(0xFC), UINT8_C(0xD3), UINT8_C(0xA2), UINT8_C(0x8D), UINT8_C(0x40), UINT8_C(0x6F), UINT8_C(0x1E), UINT8_C(0x31),
      UINT8_C(0x76), UINT8_C(0x59), UINT8_C(0x28), UINT8_C(0x07), UINT8_C(0xCA), UINT8_C(0xE5), UINT8_C(0x94), UINT8_C(0xBB),
      UINT8_C(0x21), UINT8_C(0x0E), UINT8_C(0x7F), UINT8_C(0x50), UINT8_C(0x9D), UINT8_C(0xB2), UINT8_C(0xC3), UINT8_C(0xEC),
      UINT8_C(0xD8), UINT8_C(0xF7), UINT8_C(0x86), UINT8_C(0xA9), UINT8_C(0x64), UINT8_C(0x4B), UINT8_C(0x3A), UINT8_C(0x15),
      UINT8_C(0x8F), UINT8_C(0xA0), UINT8_C(0xD1), UINT8_C(0xFE), UINT8_C(0x33), UINT8_C(0x1C), UINT8_C(0x6D), UINT8_C(0x42),
    };

    /* Perform the CRC-8/AUTOSAR algorithm. */

    const uint_fast8_t DataIndex =
      (uint_fast8_t) ((uint8_t) (  Crc_Context->Crc_Value
                                 ^ DataIn[LoopCnt]));

    const uint8_t TableValue =
      mcal_memory_progmem_read_byte((mcal_progmem_uintptr_t) &Crc08_Table[DataIndex]);

    Crc_Context->Crc_Value = TableValue;
  }
}

void Crc08_Finalize(Crc08_Context_Type* Crc_Context)
{
  Crc_Context->Crc_Value ^= UINT8_C(0xFF);
}
