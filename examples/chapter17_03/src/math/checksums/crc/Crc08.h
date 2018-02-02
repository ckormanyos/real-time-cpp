/*/////////////////////////////////////////////////////////*/
/*  Copyright Christopher Kormanyos 2017 - 2018.           */
/*  Distributed under the Boost Software License,          */
/*  Version 1.0. (See accompanying file LICENSE_1_0.txt    */
/*  or copy at http://www.boost.org/LICENSE_1_0.txt)       */
/*/////////////////////////////////////////////////////////*/

#ifndef CRC08_2017_12_16_H_
  #define CRC08_2017_12_16_H_

  #include <stddef.h>
  #include <stdint.h>

  // The interface to Crc08 can be used in both C as well as C++.

  /* Name            : CRC-8/AUTOSAR */
  /* Width in bits   : 8             */
  /* Polynomial      : 0x2F          */
  /* Initial value   : 0xFF          */
  /* Final XOR       : 0xFF          */
  /* Test: '1'...'9' : 0xDF          */
  /* See also AUTOSAR Version 4.3.   */

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef struct Crc08_Context_Type
  {
    uint8_t Crc08_Value;
  }
  Crc08_Context_Type;

  void Crc08_Initialize  (Crc08_Context_Type* Crc_Context);

  void Crc08_ProcessBytes(const uint8_t*      DataIn,
                          const size_t        DataLength,
                          Crc08_Context_Type* Crc_Context);

  void Crc08_Finalize    (Crc08_Context_Type* Crc_Context);

  #if defined(__cplusplus)
  }
  #endif

#endif // CRC08_2017_12_16_H_
