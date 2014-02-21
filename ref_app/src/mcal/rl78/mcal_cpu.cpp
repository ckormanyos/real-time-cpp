///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_wdg.h>

void mcal::cpu::init()
{
  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}

std::uint8_t mcal::cpu::read_program_memory(volatile std::uint8_t* pointer_to_program_memory)
{
  return pgm_read_byte(reinterpret_cast<std::uint16_t>(pointer_to_program_memory));
}

