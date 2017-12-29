///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <avr/pgmspace.h>

#include <mcal_cpu.h>

void mcal::cpu::init()
{
}

std::uint8_t mcal::cpu::read_program_memory(volatile std::uint8_t* pointer_to_program_memory)
{
  const std::uint16_t memory_address = reinterpret_cast<std::uint16_t>(pointer_to_program_memory);

  return pgm_read_byte(memory_address);
}
