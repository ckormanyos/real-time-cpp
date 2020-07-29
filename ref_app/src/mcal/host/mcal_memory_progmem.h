///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_PROGMEM_2019_08_17_H_
  #define MCAL_MEMORY_PROGMEM_2019_08_17_H_

  #include <stdint.h>

  #define MY_PROGMEM

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef uintptr_t mcal_progmem_uintptr_t;
  typedef ptrdiff_t mcal_progmem_ptrdiff_t;

  #define MCAL_PROGMEM_ADDRESSOF(x) ((mcal_progmem_uintptr_t) (&(x)))

  #define MCAL_PROGMEM_ADDRESSOF(x) ((mcal_progmem_uintptr_t) (&(x)))

  static inline uint8_t mcal_memory_progmem_read_byte(const mcal_progmem_uintptr_t src_addr)
  {
    return *(const uint8_t*) src_addr;
  }

  static inline uint16_t mcal_memory_progmem_read_word(const mcal_progmem_uintptr_t src_addr)
  {
    uint16_t dest;

    *(((uint8_t*) &dest) + 0U) = *((const uint8_t*) (src_addr + 0U));
    *(((uint8_t*) &dest) + 1U) = *((const uint8_t*) (src_addr + 1U));

    return dest;
  }

  static inline uint32_t mcal_memory_progmem_read_dword(const mcal_progmem_uintptr_t src_addr)
  {
    uint32_t dest;

    *(((uint8_t*) &dest) + 0U) = *((const uint8_t*) (src_addr + 0U));
    *(((uint8_t*) &dest) + 1U) = *((const uint8_t*) (src_addr + 1U));
    *(((uint8_t*) &dest) + 2U) = *((const uint8_t*) (src_addr + 2U));
    *(((uint8_t*) &dest) + 3U) = *((const uint8_t*) (src_addr + 3U));

    return dest;
  }

  static inline uint64_t mcal_memory_progmem_read_qword(const mcal_progmem_uintptr_t src_addr)
  {
    uint64_t dest;

    *(((uint8_t*) &dest) + 0U) = *((const uint8_t*) (src_addr + 0U));
    *(((uint8_t*) &dest) + 1U) = *((const uint8_t*) (src_addr + 1U));
    *(((uint8_t*) &dest) + 2U) = *((const uint8_t*) (src_addr + 2U));
    *(((uint8_t*) &dest) + 3U) = *((const uint8_t*) (src_addr + 3U));
    *(((uint8_t*) &dest) + 4U) = *((const uint8_t*) (src_addr + 4U));
    *(((uint8_t*) &dest) + 5U) = *((const uint8_t*) (src_addr + 5U));
    *(((uint8_t*) &dest) + 6U) = *((const uint8_t*) (src_addr + 6U));
    *(((uint8_t*) &dest) + 7U) = *((const uint8_t*) (src_addr + 7U));

    return dest;
  }

  #if defined(__cplusplus)
  }
  #endif

#endif // MCAL_MEMORY_PROGMEM_2019_08_17_H_
