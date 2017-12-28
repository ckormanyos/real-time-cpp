/*/////////////////////////////////////////////////////////*/
/*  Copyright Christopher Kormanyos 2017 - 2018.           */
/*  Distributed under the Boost Software License,          */
/*  Version 1.0. (See accompanying file LICENSE_1_0.txt    */
/*  or copy at http://www.boost.org/LICENSE_1_0.txt)       */
/*/////////////////////////////////////////////////////////*/

#ifndef CRC16_CCITT_FALSE_2017_12_16_H_
  #define CRC16_CCITT_FALSE_2017_12_16_H_

  #include <stddef.h>
  #include <stdint.h>

  // The interface to Crc16_CcittFalse can be used in both C as well as C++.

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef struct Crc16_CcittFalse_Context_Type
  {
    uint16_t Crc_Value;
  }
  Crc16_CcittFalse_Context_Type;

  void Crc16_CcittFalse_Initialize  (Crc16_CcittFalse_Context_Type* Crc_Context);
  void Crc16_CcittFalse_ProcessBytes(const uint8_t*                 DataIn,
                                     const size_t                   DataLength,
                                     Crc16_CcittFalse_Context_Type* Crc_Context);
  void Crc16_CcittFalse_Finalize    (Crc16_CcittFalse_Context_Type* Crc_Context);

  #if defined(__cplusplus)
  }
  #endif

#endif // CRC16_CCITT_FALSE_2017_12_16_H_
