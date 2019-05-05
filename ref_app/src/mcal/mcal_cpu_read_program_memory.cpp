///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal/mcal_cpu_read_program_memory.h>

extern "C"
uint8_t mcal_cpu_read_program_memory_byte(const uint8_t* pointer_to_program_memory)
{
  return mcal::cpu::read_program_memory(pointer_to_program_memory);
}

extern "C"
uint16_t mcal_cpu_read_program_memory_word(const uint16_t* pointer_to_program_memory)
{
  return mcal::cpu::read_program_memory(pointer_to_program_memory);
}

extern "C"
uint32_t mcal_cpu_read_program_memory_dword(const uint32_t* pointer_to_program_memory)
{
  return mcal::cpu::read_program_memory(pointer_to_program_memory);
}

extern "C"
uint64_t mcal_cpu_read_program_memory_qword(const uint64_t* pointer_to_program_memory)
{
  return mcal::cpu::read_program_memory(pointer_to_program_memory);
}
