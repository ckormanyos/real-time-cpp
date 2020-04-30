///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_REF_2020_04_11_H_
  #define MCAL_MEMORY_SRAM_REF_2020_04_11_H_

  #include <mcal_memory/mcal_memory_sram_access.h>

  // Implement a specialized reference type for read-only program memory.

  namespace mcal { namespace memory { namespace sram {

  template<typename ValueType,
           typename AddressType,
           typename AddressDifferenceType>
  class sram_ref
  {
  private:
    using address_type = AddressType;

  public:
    using value_type      = ValueType;
    using size_type       = address_type;
    using difference_type = AddressDifferenceType;

    explicit sram_ref(address_type address = 0U) noexcept : my_address(address) { }

    sram_ref(const sram_ref& other) noexcept : my_address(other.my_address) { }

    sram_ref(sram_ref&& other) noexcept : my_address(other.my_address) { }

    ~sram_ref() noexcept { }

    sram_ref& operator=(const sram_ref& other) noexcept
    {
      my_address = other.my_address;

      return *this;
    }

    sram_ref& operator=(sram_ref&& other) noexcept
    {
      my_address = other.my_address;

      return *this;
    }

    sram_ref& operator=(value_type other_value) noexcept
    {
      write<value_type>(other_value, my_address);

      return *this;
    }

    operator value_type() noexcept
    {
      return read<value_type>(my_address);
    }

    operator value_type() const noexcept
    {
      return read<value_type>(my_address);
    }

  private:
    const address_type my_address;
  };

  } } } // namespace mcal::memory::sram

#endif // MCAL_MEMORY_SRAM_REF_2020_04_11_H_
