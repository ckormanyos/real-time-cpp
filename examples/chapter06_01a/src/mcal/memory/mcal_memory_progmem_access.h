///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_PROGMEM_ACCESS_2019_08_17_H_
  #define MCAL_MEMORY_PROGMEM_ACCESS_2019_08_17_H_

  #include <mcal_memory_progmem.h>

  #include <type_traits>

  namespace mcal { namespace memory { namespace progmem {

  template<typename ProgramMemoryType>
  ProgramMemoryType read(
    const ProgramMemoryType* src,
    const typename std::enable_if<(   (std::is_fundamental<ProgramMemoryType>::value == false)
                                   && (sizeof(ProgramMemoryType) != 1U)
                                   && (sizeof(ProgramMemoryType) != 2U)
                                   && (sizeof(ProgramMemoryType) != 4U)
                                   && (sizeof(ProgramMemoryType) != 8U))>::type* = nullptr)
  {
    using local_programmemory_type = ProgramMemoryType;

    local_programmemory_type dest;

    for(size_t i = 0U; i < sizeof(ProgramMemoryType); ++i)
    {
      *(((uint8_t*) dest) + i) =
        mcal_memory_progmem_read_byte(((const uint8_t*) src) + i);
    }

    return dest;
  }

  template<typename ProgramMemoryType>
  ProgramMemoryType read(
    const ProgramMemoryType* src,
    const typename std::enable_if<(   (std::is_fundamental<ProgramMemoryType>::value == true)
                                   && (sizeof(ProgramMemoryType) == 1U))>::type* = nullptr)
  {
    return mcal_memory_progmem_read_byte(src);
  }

  template<typename ProgramMemoryType>
  ProgramMemoryType read(
    const ProgramMemoryType* src,
    const typename std::enable_if<(   (std::is_fundamental<ProgramMemoryType>::value == true)
                                   && (sizeof(ProgramMemoryType) == 2U))>::type* = nullptr)
  {
    return mcal_memory_progmem_read_word(src);
  }

  template<typename ProgramMemoryType>
  ProgramMemoryType read(
    const ProgramMemoryType* src,
    const typename std::enable_if<(   (std::is_fundamental<ProgramMemoryType>::value == true)
                                   && (sizeof(ProgramMemoryType) == 4U))>::type* = nullptr)
  {
    return mcal_memory_progmem_read_dword(src);
  }

  template<typename ProgramMemoryType>
  ProgramMemoryType read(
    const ProgramMemoryType* src,
    const typename std::enable_if<(   (std::is_fundamental<ProgramMemoryType>::value == true)
                                   && (sizeof(ProgramMemoryType) == 8U))>::type* = nullptr)
  {
    return mcal_memory_progmem_read_qword(src);
  }

  } } } // namespace mcal::memory::progmem

#endif // MCAL_MEMORY_PROGMEM_ACCESS_2019_08_17_H_
