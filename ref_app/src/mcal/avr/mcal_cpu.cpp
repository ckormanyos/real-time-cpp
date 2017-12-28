///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

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

extern "C"
uint8_t mcal_cpu_read_program_memory_byte(const uint8_t* pointer_to_program_memory)
{
  const uint16_t memory_address = reinterpret_cast<uint16_t>(pointer_to_program_memory);

  return pgm_read_byte(memory_address);
}

extern "C"
uint16_t mcal_cpu_read_program_memory_word(const uint8_t* pointer_to_program_memory)
{
  const uint16_t memory_address = reinterpret_cast<uint16_t>(pointer_to_program_memory);

  uint16_t result_of_read;

  *(reinterpret_cast<uint8_t*>(&result_of_read) + 0U) = pgm_read_byte(memory_address + 0U);
  *(reinterpret_cast<uint8_t*>(&result_of_read) + 1U) = pgm_read_byte(memory_address + 1U);

  return result_of_read;
}

extern "C"
uint32_t mcal_cpu_read_program_memory_dword(const uint8_t* pointer_to_program_memory)
{
  const uint16_t memory_address = reinterpret_cast<uint16_t>(pointer_to_program_memory);

  uint32_t result_of_read;

  *(reinterpret_cast<uint8_t*>(&result_of_read) + 0U) = pgm_read_byte(memory_address + 0U);
  *(reinterpret_cast<uint8_t*>(&result_of_read) + 1U) = pgm_read_byte(memory_address + 1U);
  *(reinterpret_cast<uint8_t*>(&result_of_read) + 2U) = pgm_read_byte(memory_address + 2U);
  *(reinterpret_cast<uint8_t*>(&result_of_read) + 3U) = pgm_read_byte(memory_address + 3U);

  return result_of_read;
}

extern "C"
uint64_t mcal_cpu_read_program_memory_qword(const uint8_t* pointer_to_program_memory)
{
  const uint16_t memory_address = reinterpret_cast<uint16_t>(pointer_to_program_memory);

  uint64_t result_of_read;

  *(reinterpret_cast<uint8_t*>(&result_of_read) + 0U) = pgm_read_byte(memory_address + 0U);
  *(reinterpret_cast<uint8_t*>(&result_of_read) + 1U) = pgm_read_byte(memory_address + 1U);
  *(reinterpret_cast<uint8_t*>(&result_of_read) + 2U) = pgm_read_byte(memory_address + 2U);
  *(reinterpret_cast<uint8_t*>(&result_of_read) + 3U) = pgm_read_byte(memory_address + 3U);
  *(reinterpret_cast<uint8_t*>(&result_of_read) + 4U) = pgm_read_byte(memory_address + 4U);
  *(reinterpret_cast<uint8_t*>(&result_of_read) + 5U) = pgm_read_byte(memory_address + 5U);
  *(reinterpret_cast<uint8_t*>(&result_of_read) + 6U) = pgm_read_byte(memory_address + 6U);
  *(reinterpret_cast<uint8_t*>(&result_of_read) + 7U) = pgm_read_byte(memory_address + 7U);

  return result_of_read;
}
