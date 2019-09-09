///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_PROGMEM_ACCESS_2019_08_17_H_
  #define MCAL_MEMORY_PROGMEM_ACCESS_2019_08_17_H_

  #include <cstddef>
  #include <cstdint>
  #include <type_traits>

  #include <mcal_progmem.h>

  namespace mcal { namespace memory { namespace progmem {

  template<typename ValueType>
  ValueType read(
    const mcal_progmem_uintptr_t src_addr,
    const typename std::enable_if<(   (std::is_fundamental<ValueType>::value == false)
                                   && (sizeof(ValueType) != 1U)
                                   && (sizeof(ValueType) != 2U)
                                   && (sizeof(ValueType) != 4U)
                                   && (sizeof(ValueType) != 8U))>::type* = nullptr)
  {
    using local_value_type = ValueType;

    local_value_type dest;

    for(std::size_t i = 0U; i < sizeof(ValueType); ++i)
    {
      *(((std::uint8_t*) MCAL_PROGMEM_ADDRESSOF(dest)) + i) =
        mcal_memory_progmem_read_byte(mcal_progmem_uintptr_t(src_addr + i));
    }

    return dest;
  }

  template<typename ValueType>
  ValueType read(
    const mcal_progmem_uintptr_t src_addr,
    const typename std::enable_if<(   (std::is_fundamental<ValueType>::value == true)
                                   && (sizeof(ValueType) == 1U))>::type* = nullptr)
  {
    return mcal_memory_progmem_read_byte(src_addr);
  }

  template<typename ValueType>
  ValueType read(
    const mcal_progmem_uintptr_t src_addr,
    const typename std::enable_if<(   (std::is_fundamental<ValueType>::value == true)
                                   && (sizeof(ValueType) == 2U))>::type* = nullptr)
  {
    return mcal_memory_progmem_read_word(src_addr);
  }

  template<typename ValueType>
  ValueType read(
    const mcal_progmem_uintptr_t src_addr,
    const typename std::enable_if<(   (std::is_fundamental<ValueType>::value == true)
                                   && (sizeof(ValueType) == 4U))>::type* = nullptr)
  {
    return mcal_memory_progmem_read_dword(src_addr);
  }

  template<typename ValueType>
  ValueType read(
    const mcal_progmem_uintptr_t src_addr,
    const typename std::enable_if<(   (std::is_fundamental<ValueType>::value == true)
                                   && (sizeof(ValueType) == 8U))>::type* = nullptr)
  {
    return mcal_memory_progmem_read_qword(src_addr);
  }

  } } } // namespace mcal::memory::progmem

#endif // MCAL_MEMORY_PROGMEM_ACCESS_2019_08_17_H_
