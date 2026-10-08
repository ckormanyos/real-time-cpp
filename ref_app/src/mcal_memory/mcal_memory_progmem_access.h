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
  #include <cstring>
  #include <type_traits>

  namespace mcal { namespace memory { namespace progmem {

  namespace detail {

  template<typename ValueType, typename RepresentationType>
  auto read_value(const RepresentationType representation) noexcept -> ValueType
  {
    static_assert(std::is_trivially_copyable<ValueType>::value,
                  "Program-memory values must be trivially copyable.");
    static_assert(sizeof(ValueType) == sizeof(RepresentationType),
                  "Program-memory representations must have matching sizes.");

    ValueType value { };
    std::memcpy(&value, &representation, sizeof(value));

    return value;
  }

  } // namespace detail

  template<typename ValueType>
  auto read(const mcal_progmem_uintptr_t src_addr) noexcept
    -> typename std::enable_if_t<(   (sizeof(ValueType) != 1U)
                                  && (sizeof(ValueType) != 2U)
                                  && (sizeof(ValueType) != 4U)
                                  && (sizeof(ValueType) != 8U)), ValueType>
  {
    static_assert(std::is_trivially_copyable<ValueType>::value,
                  "Program-memory values must be trivially copyable.");

    using local_value_type = ValueType;

    local_value_type dest { };

    for(std::size_t i = 0U; i < sizeof(ValueType); ++i)
    {
      const std::uint8_t by = mcal_memory_progmem_read_byte(static_cast<mcal_progmem_uintptr_t>(src_addr + i));

      *(reinterpret_cast<std::uint8_t*>(MCAL_PROGMEM_ADDRESSOF(dest)) + i) = by;
    }

    return dest;
  }

  template<typename ValueType>
  auto read(const mcal_progmem_uintptr_t src_addr) noexcept
    -> typename std::enable_if_t<(sizeof(ValueType) == 1U), ValueType>
  {
    return detail::read_value<ValueType>(mcal_memory_progmem_read_byte(src_addr));
  }

  template<typename ValueType>
  auto read(const mcal_progmem_uintptr_t src_addr) noexcept
    -> typename std::enable_if_t<(sizeof(ValueType) == 2U), ValueType>
  {
    return detail::read_value<ValueType>(mcal_memory_progmem_read_word(src_addr));
  }

  template<typename ValueType>
  auto read(const mcal_progmem_uintptr_t src_addr) noexcept
    -> typename std::enable_if_t<(sizeof(ValueType) == 4U), ValueType>
  {
    return detail::read_value<ValueType>(mcal_memory_progmem_read_dword(src_addr));
  }

  template<typename ValueType>
  auto read(const mcal_progmem_uintptr_t src_addr) noexcept
    -> typename std::enable_if_t<(sizeof(ValueType) == 8U), ValueType>
  {
    return detail::read_value<ValueType>(mcal_memory_progmem_read_qword(src_addr));
  }

  } } } // namespace mcal::memory::progmem

#endif // MCAL_MEMORY_PROGMEM_ACCESS_2019_08_17_H
