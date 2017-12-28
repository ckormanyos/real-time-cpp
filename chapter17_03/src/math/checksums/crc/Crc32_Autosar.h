/*/////////////////////////////////////////////////////////*/
/*  Copyright Christopher Kormanyos 2017 - 2018.           */
/*  Distributed under the Boost Software License,          */
/*  Version 1.0. (See accompanying file LICENSE_1_0.txt    */
/*  or copy at http://www.boost.org/LICENSE_1_0.txt)       */
/*/////////////////////////////////////////////////////////*/

#ifndef CRC32_AUTOSAR_2017_12_16_H_
  #define CRC32_AUTOSAR_2017_12_16_H_

  #include <stddef.h>
  #include <stdint.h>

  // The interface to Crc32_Autosar can be used in both C as well as C++.

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef struct Crc32_Autosar_Context_Type
  {
    uint32_t Crc_Value;
  }
  Crc32_Autosar_Context_Type;

  void Crc32_Autosar_Initialize  (Crc32_Autosar_Context_Type* Crc_Context);
  void Crc32_Autosar_ProcessBytes(const uint8_t*              DataIn,
                                  const size_t                DataLength,
                                  Crc32_Autosar_Context_Type* Crc_Context);
  void Crc32_Autosar_Finalize    (Crc32_Autosar_Context_Type* Crc_Context);

  #if defined(__cplusplus)
  }
  #endif

#endif // CRC32_AUTOSAR_2017_12_16_H_
