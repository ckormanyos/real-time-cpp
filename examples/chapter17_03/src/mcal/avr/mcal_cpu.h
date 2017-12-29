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

  uint8_t  mcal_cpu_read_program_memory_byte (const uint8_t* pointer_to_program_memory);
  uint16_t mcal_cpu_read_program_memory_word (const uint8_t* pointer_to_program_memory);
  uint32_t mcal_cpu_read_program_memory_dword(const uint8_t* pointer_to_program_memory);
  uint64_t mcal_cpu_read_program_memory_qword(const uint8_t* pointer_to_program_memory);

  #if defined(__cplusplus)
  }
  #endif

#endif // MCAL_CPU_2009_02_14_H_
