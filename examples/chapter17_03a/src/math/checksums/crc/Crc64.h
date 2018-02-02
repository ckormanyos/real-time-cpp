/*/////////////////////////////////////////////////////////*/
/*  Copyright Christopher Kormanyos 2017 - 2018.           */
/*  Distributed under the Boost Software License,          */
/*  Version 1.0. (See accompanying file LICENSE_1_0.txt    */
/*  or copy at http://www.boost.org/LICENSE_1_0.txt)       */
/*/////////////////////////////////////////////////////////*/

#ifndef CRC64_2017_12_16_H_
  #define CRC64_2017_12_16_H_

  #include <stddef.h>
  #include <stdint.h>

  // The interface to Crc64 can be used in both C as well as C++.

  /* Name (original) : CRC-64/XZ           */
  /* Width in bits   : 64                  */
  /* Polynomial      : 0x42F0E1EBA9EA3693  */
  /* Initial value   : 0xFFFFFFFFFFFFFFFF  */
  /* Final XOR       : 0xFFFFFFFFFFFFFFFF  */
  /* Test: '1'...'9' : 0x995DC9BBDF1939FA  */

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef struct Crc64_Context_Type
  {
    uint64_t Crc_Value;
  }
  Crc64_Context_Type;

  void Crc64_Initialize  (Crc64_Context_Type* Crc_Context);

  void Crc64_ProcessBytes(const uint8_t*      DataIn,
                          const size_t        DataLength,
                          Crc64_Context_Type* Crc_Context);

  void Crc64_Finalize    (Crc64_Context_Type* Crc_Context);

  #if defined(__cplusplus)
  }
  #endif

#endif // CRC64_2017_12_16_H_
