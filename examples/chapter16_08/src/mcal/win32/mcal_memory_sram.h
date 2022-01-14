///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_2020_04_09_H_
  #define MCAL_MEMORY_SRAM_2020_04_09_H_

  #include <stddef.h>
  #include <stdint.h>

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef uint32_t mcal_sram_uintptr_t;
  typedef  int32_t mcal_sram_ptrdiff_t;

  uint8_t  mcal_memory_sram_read_byte (const mcal_sram_uintptr_t src_addr);
  uint16_t mcal_memory_sram_read_word (const mcal_sram_uintptr_t src_addr);
  uint32_t mcal_memory_sram_read_dword(const mcal_sram_uintptr_t src_addr);
  uint64_t mcal_memory_sram_read_qword(const mcal_sram_uintptr_t src_addr);

  void mcal_memory_sram_write_byte (const uint8_t src_value,  const mcal_sram_uintptr_t dest_addr);
  void mcal_memory_sram_write_word (const uint16_t src_value, const mcal_sram_uintptr_t dest_addr);
  void mcal_memory_sram_write_dword(const uint32_t src_value, const mcal_sram_uintptr_t dest_addr);
  void mcal_memory_sram_write_qword(const uint64_t src_value, const mcal_sram_uintptr_t dest_addr);

  #if defined(__cplusplus)
  }
  #endif

#endif // MCAL_MEMORY_SRAM_2020_04_09_H_
