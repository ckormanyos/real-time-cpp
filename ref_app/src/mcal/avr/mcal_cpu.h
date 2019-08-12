///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_2009_02_14_H_
  #define MCAL_CPU_2009_02_14_H_

  #include <cstdint>
  #include <type_traits>

  #include <avr/pgmspace.h>

  #define MY_PROGMEM PROGMEM

  namespace mcal { namespace cpu {

  void init();

  inline void post_init() { }

  inline void nop() { asm volatile("nop"); }

  template<typename ProgramMemoryType>
  ProgramMemoryType read_program_memory(
    const ProgramMemoryType* pointer_to_program_memory,
    const typename std::enable_if<(   (std::is_fundamental<ProgramMemoryType>::value == false)
                                   && (sizeof(ProgramMemoryType) != 1U)
                                   && (sizeof(ProgramMemoryType) != 2U)
                                   && (sizeof(ProgramMemoryType) != 4U)
                                   && (sizeof(ProgramMemoryType) != 8U))>::type* = nullptr)
  {
    using local_programmemory_type = ProgramMemoryType;

    local_programmemory_type x;

    for(std::size_t i = 0U; i < sizeof(local_programmemory_type); ++i)
    {
      const std::uint8_t next_memory_byte =
        pgm_read_byte(reinterpret_cast<const std::uint8_t*>(pointer_to_program_memory) + i);

      *(reinterpret_cast<std::uint8_t*>(&x) + i) = next_memory_byte;
    }

    return x;
  }

  template<typename ProgramMemoryType>
  ProgramMemoryType read_program_memory(
    const ProgramMemoryType* pointer_to_program_memory,
    const typename std::enable_if<(   (std::is_fundamental<ProgramMemoryType>::value == true)
                                   && (sizeof(ProgramMemoryType) == 1U))>::type* = nullptr)
  {
    using local_programmemory_type = ProgramMemoryType;

    const local_programmemory_type x =
      pgm_read_byte(reinterpret_cast<std::uint16_t>(pointer_to_program_memory));

    return x;
  }

  template<typename ProgramMemoryType>
  ProgramMemoryType read_program_memory(
    const ProgramMemoryType* pointer_to_program_memory,
    const typename std::enable_if<(   (std::is_fundamental<ProgramMemoryType>::value == true)
                                   && (sizeof(ProgramMemoryType) == 2U))>::type* = nullptr)
  {
    using local_programmemory_type = ProgramMemoryType;

    const local_programmemory_type x =
      pgm_read_word(reinterpret_cast<std::uint16_t>(pointer_to_program_memory));

    return x;
  }

  template<typename ProgramMemoryType>
  ProgramMemoryType read_program_memory(
    const ProgramMemoryType* pointer_to_program_memory,
    const typename std::enable_if<(   (std::is_fundamental<ProgramMemoryType>::value == true)
                                   && (sizeof(ProgramMemoryType) == 4U))>::type* = nullptr)
  {
    using local_programmemory_type = ProgramMemoryType;

    const local_programmemory_type x =
      pgm_read_dword(reinterpret_cast<std::uint16_t>(pointer_to_program_memory));

    return x;
  }

  template<typename ProgramMemoryType>
  ProgramMemoryType read_program_memory(
    const ProgramMemoryType* pointer_to_program_memory,
    const typename std::enable_if<(   (std::is_fundamental<ProgramMemoryType>::value == true)
                                   && (sizeof(ProgramMemoryType) == 8U))>::type* = nullptr)
  {
    using local_programmemory_type = ProgramMemoryType;

    local_programmemory_type x;
    *(reinterpret_cast<std::uint8_t*>(&x) + 0U) = pgm_read_byte(reinterpret_cast<std::uint16_t>(reinterpret_cast<const std::uint8_t*>(pointer_to_program_memory) + 0U));
    *(reinterpret_cast<std::uint8_t*>(&x) + 1U) = pgm_read_byte(reinterpret_cast<std::uint16_t>(reinterpret_cast<const std::uint8_t*>(pointer_to_program_memory) + 1U));
    *(reinterpret_cast<std::uint8_t*>(&x) + 2U) = pgm_read_byte(reinterpret_cast<std::uint16_t>(reinterpret_cast<const std::uint8_t*>(pointer_to_program_memory) + 2U));
    *(reinterpret_cast<std::uint8_t*>(&x) + 3U) = pgm_read_byte(reinterpret_cast<std::uint16_t>(reinterpret_cast<const std::uint8_t*>(pointer_to_program_memory) + 3U));
    *(reinterpret_cast<std::uint8_t*>(&x) + 4U) = pgm_read_byte(reinterpret_cast<std::uint16_t>(reinterpret_cast<const std::uint8_t*>(pointer_to_program_memory) + 4U));
    *(reinterpret_cast<std::uint8_t*>(&x) + 5U) = pgm_read_byte(reinterpret_cast<std::uint16_t>(reinterpret_cast<const std::uint8_t*>(pointer_to_program_memory) + 5U));
    *(reinterpret_cast<std::uint8_t*>(&x) + 6U) = pgm_read_byte(reinterpret_cast<std::uint16_t>(reinterpret_cast<const std::uint8_t*>(pointer_to_program_memory) + 6U));
    *(reinterpret_cast<std::uint8_t*>(&x) + 7U) = pgm_read_byte(reinterpret_cast<std::uint16_t>(reinterpret_cast<const std::uint8_t*>(pointer_to_program_memory) + 7U));

    return x;
  }

  } } // namespace mcal::cpu

#endif // MCAL_CPU_2009_02_14_H_
