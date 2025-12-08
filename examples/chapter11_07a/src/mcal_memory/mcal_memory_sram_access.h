///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_ACCESS_2020_04_10_H
  #define MCAL_MEMORY_SRAM_ACCESS_2020_04_10_H

  #include <mcal_memory_sram.h>

  #include <cstdint>
  #include <type_traits>

  namespace mcal { namespace memory { namespace sram {

  template<typename ValueType>
  ValueType read(const mcal_sram_uintptr_t src_addr,
                 const typename std::enable_if<(sizeof(ValueType) == 1U)>::type* = nullptr) noexcept
  {
    auto byte_to_read = std::uint8_t { };

    const auto result_read_is_ok = mcal_memory_sram_device().read(src_addr, &byte_to_read);

    static_cast<void>(result_read_is_ok);

    return byte_to_read;
  }

  template<typename ValueType>
  ValueType read(const mcal_sram_uintptr_t src_addr,
                 const typename std::enable_if<(sizeof(ValueType) != 1U)>::type* = nullptr) noexcept
  {
    using local_value_type = ValueType;

    auto value_to_read = local_value_type { };

    const auto result_read_is_ok =
      mcal_memory_sram_device().read_n(src_addr, reinterpret_cast<std::uint8_t*>(&value_to_read), sizeof(local_value_type));

    static_cast<void>(result_read_is_ok);

    return value_to_read;
  }

  template<typename ValueType>
  void write(const ValueType src_value,
             const mcal_sram_uintptr_t dest_addr,
             const typename std::enable_if<(sizeof(ValueType) == 1U)>::type* = nullptr) noexcept
  {
    const auto result_write_is_ok = mcal_memory_sram_device().write(dest_addr, &src_value);

    static_cast<void>(result_write_is_ok);
  }

  template<typename ValueType>
  void write(const ValueType src_value,
             const mcal_sram_uintptr_t dest_addr,
             const typename std::enable_if<(sizeof(ValueType) != 1U)>::type* = nullptr) noexcept
  {
    using local_value_type = ValueType;

    const auto result_write_is_ok = mcal_memory_sram_device().write_n(dest_addr, reinterpret_cast<const std::uint8_t*>(&src_value), sizeof(local_value_type));

    static_cast<void>(result_write_is_ok);
  }

  } } } // namespace mcal::memory::progmem

#endif // MCAL_MEMORY_SRAM_ACCESS_2020_04_10_H
