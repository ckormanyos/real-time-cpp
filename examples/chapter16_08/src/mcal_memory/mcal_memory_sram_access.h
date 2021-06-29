///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_ACCESS_2020_04_10_H_
  #define MCAL_MEMORY_SRAM_ACCESS_2020_04_10_H_

  #include <cstddef>
  #include <cstdint>
  #include <type_traits>

  #include <mcal_memory_sram.h>

  namespace mcal { namespace memory { namespace sram {

  template<typename ValueType>
  ValueType read(
    const mcal_sram_uintptr_t src_addr,
    const typename std::enable_if<(   (sizeof(ValueType) != 1U)
                                   && (sizeof(ValueType) != 2U)
                                   && (sizeof(ValueType) != 4U)
                                   && (sizeof(ValueType) != 8U))>::type* = nullptr) noexcept
  {
    using local_value_type = ValueType;

    local_value_type dest;

    for(std::size_t i = 0U; i < sizeof(ValueType); ++i)
    {
      const uint8_t by = mcal_memory_sram_read_byte(mcal_sram_uintptr_t(src_addr + i));

      *(((std::uint8_t*) &dest) + i) = by;
    }

    return dest;
  }

  template<typename ValueType>
  ValueType read(
    const mcal_sram_uintptr_t src_addr,
    const typename std::enable_if<(sizeof(ValueType) == 1U)>::type* = nullptr) noexcept
  {
    return mcal_memory_sram_read_byte(src_addr);
  }

  template<typename ValueType>
  ValueType read(
    const mcal_sram_uintptr_t src_addr,
    const typename std::enable_if<(sizeof(ValueType) == 2U)>::type* = nullptr) noexcept
  {
    return mcal_memory_sram_read_word(src_addr);
  }

  template<typename ValueType>
  ValueType read(
    const mcal_sram_uintptr_t src_addr,
    const typename std::enable_if<(sizeof(ValueType) == 4U)>::type* = nullptr) noexcept
  {
    return mcal_memory_sram_read_dword(src_addr);
  }

  template<typename ValueType>
  ValueType read(
    const mcal_sram_uintptr_t src_addr,
    const typename std::enable_if<(sizeof(ValueType) == 8U)>::type* = nullptr) noexcept
  {
    return mcal_memory_sram_read_qword(src_addr);
  }

  template<typename ValueType>
  void write(
    const ValueType src_value,
    const mcal_sram_uintptr_t dest_addr,
    const typename std::enable_if<(   (sizeof(ValueType) != 1U)
                                   && (sizeof(ValueType) != 2U)
                                   && (sizeof(ValueType) != 4U)
                                   && (sizeof(ValueType) != 8U))>::type* = nullptr) noexcept
  {
    using local_value_type = ValueType;

    local_value_type local_src_value = src_value;

    for(std::size_t i = 0U; i < sizeof(local_value_type); ++i)
    {
      const uint8_t by = *(((const uint8_t*) &local_src_value) + i);

      mcal_memory_sram_write_byte(by, dest_addr + i);
    }
  }

  template<typename ValueType>
  void write(
    const uint8_t src_value,
    const mcal_sram_uintptr_t dest_addr,
    const typename std::enable_if<(sizeof(ValueType) == 1U)>::type* = nullptr) noexcept
  {
    mcal_memory_sram_write_byte(src_value, dest_addr);
  }

  template<typename ValueType>
  void write(
    const uint16_t src_value,
    const mcal_sram_uintptr_t dest_addr,
    const typename std::enable_if<(sizeof(ValueType) == 2U)>::type* = nullptr) noexcept
  {
    mcal_memory_sram_write_word(src_value, dest_addr);
  }

  template<typename ValueType>
  void write(
    const uint32_t src_value,
    const mcal_sram_uintptr_t dest_addr,
    const typename std::enable_if<(sizeof(ValueType) == 4U)>::type* = nullptr) noexcept
  {
    mcal_memory_sram_write_dword(src_value, dest_addr);
  }

  template<typename ValueType>
  void write(
    const uint64_t src_value,
    const mcal_sram_uintptr_t dest_addr,
    const typename std::enable_if<(sizeof(ValueType) == 8U)>::type* = nullptr) noexcept
  {
    mcal_memory_sram_write_qword(src_value, dest_addr);
  }

  } } } // namespace mcal::memory::progmem

#endif // MCAL_MEMORY_SRAM_ACCESS_2020_04_10_H_
