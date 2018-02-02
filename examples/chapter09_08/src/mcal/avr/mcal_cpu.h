///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_2009_02_14_H_
  #define MCAL_CPU_2009_02_14_H_

  #if defined(__cplusplus)
  #include <cstdint>
  #else
  #include <stdint.h>
  #endif

  #include <avr/pgmspace.h>

  #if defined(__cplusplus)
  namespace mcal
  {
    namespace cpu
    {
      void init();

      inline void post_init() { }

      inline void nop() { asm volatile("nop"); }
    }
  }
  #endif

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  inline uint8_t  mcal_cpu_read_program_memory_byte(const uint8_t* pointer_to_program_memory)
  {
    const uint16_t memory_address = (uint16_t) pointer_to_program_memory;

    return pgm_read_byte(memory_address);
  }

  inline uint16_t mcal_cpu_read_program_memory_word (const uint8_t* pointer_to_program_memory)
  {
    const uint16_t memory_address = (uint16_t) pointer_to_program_memory;

    return pgm_read_word(memory_address);
  }

  inline uint32_t mcal_cpu_read_program_memory_dword(const uint8_t* pointer_to_program_memory)
  {
    const uint16_t memory_address = (uint16_t) pointer_to_program_memory;

    return pgm_read_dword(memory_address);
  }

  inline uint64_t mcal_cpu_read_program_memory_qword(const uint8_t* pointer_to_program_memory)
  {
    const uint16_t memory_address = (uint16_t) pointer_to_program_memory;

    uint64_t result_of_read;

    *(((uint8_t*) &result_of_read) + 0U) = pgm_read_byte(memory_address + 0U);
    *(((uint8_t*) &result_of_read) + 1U) = pgm_read_byte(memory_address + 1U);
    *(((uint8_t*) &result_of_read) + 2U) = pgm_read_byte(memory_address + 2U);
    *(((uint8_t*) &result_of_read) + 3U) = pgm_read_byte(memory_address + 3U);
    *(((uint8_t*) &result_of_read) + 4U) = pgm_read_byte(memory_address + 4U);
    *(((uint8_t*) &result_of_read) + 5U) = pgm_read_byte(memory_address + 5U);
    *(((uint8_t*) &result_of_read) + 6U) = pgm_read_byte(memory_address + 6U);
    *(((uint8_t*) &result_of_read) + 7U) = pgm_read_byte(memory_address + 7U);

    return result_of_read;
  }

  #if defined(__cplusplus)
  }
  #endif

#endif // MCAL_CPU_2009_02_14_H_
