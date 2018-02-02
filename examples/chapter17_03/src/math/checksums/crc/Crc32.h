/*/////////////////////////////////////////////////////////*/
/*  Copyright Christopher Kormanyos 2017 - 2018.           */
/*  Distributed under the Boost Software License,          */
/*  Version 1.0. (See accompanying file LICENSE_1_0.txt    */
/*  or copy at http://www.boost.org/LICENSE_1_0.txt)       */
/*/////////////////////////////////////////////////////////*/

#ifndef CRC32_2017_12_16_H_
  #define CRC32_2017_12_16_H_

  #include <stddef.h>
  #include <stdint.h>

  // The interface to Crc32 can be used in both C as well as C++.

  /* Name            : CRC-32/AUTOSAR */
  /* Width in bits   : 32             */
  /* Polynomial      : 0xF4ACFB13     */
  /* Initial value   : 0xFFFFFFFF     */
  /* Final XOR       : 0xFFFFFFFF     */
  /* Test: '1'...'9' : 0x1697D06A     */
  /* See also AUTOSAR Version 4.3.    */

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef struct Crc32_Context_Type
  {
    uint32_t Crc32_Value;
  }
  Crc32_Context_Type;

  void Crc32_Initialize  (Crc32_Context_Type* Crc_Context);

  void Crc32_ProcessBytes(const uint8_t*      DataIn,
                          const size_t        DataLength,
                          Crc32_Context_Type* Crc_Context);

  void Crc32_Finalize    (Crc32_Context_Type* Crc_Context);

  #if defined(__cplusplus)
  }
  #endif

#endif // CRC32_2017_12_16_H_
