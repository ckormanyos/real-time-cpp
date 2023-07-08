///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_PROGMEM_2019_08_17_H_
  #define MCAL_MEMORY_PROGMEM_2019_08_17_H_

  #include <stddef.h>
  #include <stdint.h>

  #include <avr/pgmspace.h>

  #define MY_PROGMEM PROGMEM

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef uintptr_t mcal_progmem_uintptr_t;
  typedef ptrdiff_t mcal_progmem_ptrdiff_t;

  #define MCAL_PROGMEM_ADDRESSOF(x) ((mcal_progmem_uintptr_t) (&(x)))

  static inline uint8_t mcal_memory_progmem_read_byte(const mcal_progmem_uintptr_t src)
  {
    return pgm_read_byte(src);
  }

  static inline uint16_t mcal_memory_progmem_read_word(const mcal_progmem_uintptr_t src)
  {
    return pgm_read_word(src);
  }

  static inline uint32_t mcal_memory_progmem_read_dword(const mcal_progmem_uintptr_t src)
  {
    return pgm_read_dword(src);
  }

  static inline uint64_t mcal_memory_progmem_read_qword(const mcal_progmem_uintptr_t src)
  {
    uint64_t dest;

    *(((uint8_t*) &dest) + 0U) = pgm_read_byte(src + 0U);
    *(((uint8_t*) &dest) + 1U) = pgm_read_byte(src + 1U);
    *(((uint8_t*) &dest) + 2U) = pgm_read_byte(src + 2U);
    *(((uint8_t*) &dest) + 3U) = pgm_read_byte(src + 3U);
    *(((uint8_t*) &dest) + 4U) = pgm_read_byte(src + 4U);
    *(((uint8_t*) &dest) + 5U) = pgm_read_byte(src + 5U);
    *(((uint8_t*) &dest) + 6U) = pgm_read_byte(src + 6U);
    *(((uint8_t*) &dest) + 7U) = pgm_read_byte(src + 7U);

    return dest;
  }

  #if defined(__cplusplus)
  }
  #endif

#endif // MCAL_MEMORY_PROGMEM_2019_08_17_H_
