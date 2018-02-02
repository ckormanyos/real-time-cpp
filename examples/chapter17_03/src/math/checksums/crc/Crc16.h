/*/////////////////////////////////////////////////////////*/
/*  Copyright Christopher Kormanyos 2017 - 2018.           */
/*  Distributed under the Boost Software License,          */
/*  Version 1.0. (See accompanying file LICENSE_1_0.txt    */
/*  or copy at http://www.boost.org/LICENSE_1_0.txt)       */
/*/////////////////////////////////////////////////////////*/

#ifndef CRC16_2017_12_16_H_
  #define CRC16_2017_12_16_H_

  #include <stddef.h>
  #include <stdint.h>

  // The interface to Crc16 can be used in both C as well as C++.

  /* Name            : CRC-16/CCITT-FALSE */
  /* Width in bits   : 16                 */
  /* Polynomial      : 0x1021             */
  /* Initial value   : 0xFFFF             */
  /* Final XOR       : 0x0000             */
  /* Test: '1'...'9' : 0x29B1             */

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef struct Crc16_Context_Type
  {
    uint16_t Crc16_Value;
  }
  Crc16_Context_Type;

  void Crc16_Initialize  (Crc16_Context_Type* Crc_Context);

  void Crc16_ProcessBytes(const uint8_t*      DataIn,
                          const size_t        DataLength,
                          Crc16_Context_Type* Crc_Context);

  void Crc16_Finalize    (Crc16_Context_Type* Crc_Context);

  #if defined(__cplusplus)
  }
  #endif

#endif // CRC16_2017_12_16_H_
