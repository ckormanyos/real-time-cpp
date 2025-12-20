///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_GENERIC_HOST_2025_12_14_H
  #define MCAL_MEMORY_SRAM_GENERIC_HOST_2025_12_14_H

  #include <mcal_memory/mcal_memory_sram_types.h>

  #include <vector>

  namespace mcal { namespace memory { namespace sram {

  template<const mcal_sram_uintptr_t ByteSizeTotal>
  class mcal_memory_sram_generic_host
  {
  public:
    mcal_memory_sram_generic_host() : my_buffer(static_cast<std::size_t>(byte_size_total())) { }

    auto read(const std::uint32_t address, std::uint8_t* p_byte_to_read) -> bool
    {
      // Read one byte from the class memory buffer.

      *p_byte_to_read = *reinterpret_cast<std::uint8_t*>(my_buffer.data() + static_cast<std::ptrdiff_t>(address));

      return true;
    }

    auto read_n(const std::uint32_t address, std::uint8_t* p_data_to_read, const std::size_t count) -> bool
    {
      // Read count bytes from the class memory buffer.

      if((count == static_cast<std::size_t>(UINT8_C(0))) || (p_data_to_read == nullptr))
      {
        static_cast<void>(address);
        static_cast<void>(p_data_to_read);
        static_cast<void>(count);
      }
      else
      {
        for(std::size_t index { UINT8_C(0) }; index < count; ++index)
        {
          read(address + static_cast<std::uint32_t>(index), p_data_to_read);

          ++p_data_to_read;
        }
      }

      return true;
    }

    auto write(const std::uint32_t address, const std::uint8_t* p_byte_to_write) -> bool
    {
      // Write one byte to the class memory buffer.

      *reinterpret_cast<std::uint8_t*>(my_buffer.data() + static_cast<std::ptrdiff_t>(address)) = *p_byte_to_write;

      return true;
    }

    auto write_n(const std::uint32_t address, const std::uint8_t* p_data_to_write, const std::size_t count) -> bool
    {
      // Write count bytes to the class memory buffer.

      if((count == static_cast<std::size_t>(UINT8_C(0))) || (p_data_to_write == nullptr))
      {
        static_cast<void>(address);
        static_cast<void>(p_data_to_write);
        static_cast<void>(count);
      }
      else
      {
        for(std::size_t index { UINT8_C(0) }; index < count; ++index)
        {
          write(address + static_cast<std::uint32_t>(index), p_data_to_write);

          ++p_data_to_write;
        }
      }

      return true;
    }

  private:
    std::vector<std::uint8_t> my_buffer { static_cast<std::size_t>(byte_size_total()) };

    static constexpr auto byte_size_total() noexcept -> mcal_sram_uintptr_t { return static_cast<mcal_sram_uintptr_t>(ByteSizeTotal); }
  };

  } } } // namespace mcal::memory::sram

#endif // MCAL_MEMORY_SRAM_GENERIC_HOST_2025_12_14_H
