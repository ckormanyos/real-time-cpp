/*/////////////////////////////////////////////////////////*/
/*  Copyright Christopher Kormanyos 2017 - 2018.           */
/*  Distributed under the Boost Software License,          */
/*  Version 1.0. (See accompanying file LICENSE_1_0.txt    */
/*  or copy at http://www.boost.org/LICENSE_1_0.txt)       */
/*/////////////////////////////////////////////////////////*/

#ifndef CRC64_XZ_2017_12_16_H_
  #define CRC64_XZ_2017_12_16_H_

  #include <stddef.h>
  #include <stdint.h>

  // The interface to Crc64_Xz can be used in both C as well as C++.

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef struct Crc64_Xz_Context_Type
  {
    uint64_t Crc_Value;
  }
  Crc64_Xz_Context_Type;

  void Crc64_Xz_Initialize  (Crc64_Xz_Context_Type* Crc_Context);
  void Crc64_Xz_ProcessBytes(const uint8_t*         DataIn,
                             const size_t           DataLength,
                             Crc64_Xz_Context_Type* Crc_Context);
  void Crc64_Xz_Finalize    (Crc64_Xz_Context_Type* Crc_Context);

  #if defined(__cplusplus)
  }
  #endif

#endif // CRC64_XZ_2017_12_16_H_
