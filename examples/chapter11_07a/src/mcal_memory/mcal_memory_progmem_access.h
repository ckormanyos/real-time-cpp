///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_PROGMEM_ACCESS_2019_08_17_H
  #define MCAL_MEMORY_PROGMEM_ACCESS_2019_08_17_H

  #include <mcal_memory_progmem.h>

  #include <cstddef>
  #include <cstdint>
  #include <type_traits>

  namespace mcal { namespace memory { namespace progmem {

  template<typename ValueType>
  auto read(
    const mcal_progmem_uintptr_t src_addr,
    const typename std::enable_if<(   (sizeof(ValueType) != 1U)
                                   && (sizeof(ValueType) != 2U)
                                   && (sizeof(ValueType) != 4U)
    && (sizeof(ValueType) != 8U))>::type* = nullptr) noexcept -> ValueType
  {
    using local_value_type = ValueType;

    local_value_type dest;

    for(std::size_t i = 0U; i < sizeof(ValueType); ++i)
    {
      const std::uint8_t by = mcal_memory_progmem_read_byte(static_cast<mcal_progmem_uintptr_t>(src_addr + i));

      *(reinterpret_cast<std::uint8_t*>(MCAL_PROGMEM_ADDRESSOF(dest)) + i) = by;
    }

    return dest;
  }

  template<typename ValueType>
  auto read(
    const mcal_progmem_uintptr_t src_addr,
    const typename std::enable_if<(sizeof(ValueType) == 1U)>::type* = nullptr) noexcept -> ValueType
  {
    return mcal_memory_progmem_read_byte(src_addr);
  }

  template<typename ValueType>
  auto read(
    const mcal_progmem_uintptr_t src_addr,
    const typename std::enable_if<(sizeof(ValueType) == 2U)>::type* = nullptr) noexcept -> ValueType
  {
    return mcal_memory_progmem_read_word(src_addr);
  }

  template<typename ValueType>
  auto read(
    const mcal_progmem_uintptr_t src_addr,
    const typename std::enable_if<(sizeof(ValueType) == 4U)>::type* = nullptr) noexcept -> ValueType
  {
    return mcal_memory_progmem_read_dword(src_addr);
  }

  template<typename ValueType>
  auto read(
    const mcal_progmem_uintptr_t src_addr,
    const typename std::enable_if<(sizeof(ValueType) == 8U)>::type* = nullptr) noexcept -> ValueType
  {
    return mcal_memory_progmem_read_qword(src_addr);
  }

  } } } // namespace mcal::memory::progmem

#endif // MCAL_MEMORY_PROGMEM_ACCESS_2019_08_17_H
