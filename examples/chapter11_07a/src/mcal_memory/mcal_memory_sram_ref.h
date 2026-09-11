///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_REF_2020_04_11_H
  #define MCAL_MEMORY_SRAM_REF_2020_04_11_H

  #include <mcal_memory/mcal_memory_sram_access.h>

  // Implement specialized reference types for read/write SRAM memory.

  namespace mcal { namespace memory { namespace sram {

  template<typename ValueType, typename AddressType, typename AddressDifferenceType>
  class sram_const_ref;

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

    sram_ref(const sram_ref&) noexcept = default;

    auto operator=(const sram_ref& other) noexcept -> sram_ref&
    {
      return operator=(static_cast<value_type>(other));
    }

    auto operator=(const value_type& other_value) noexcept -> sram_ref&
    {
      write<value_type>(other_value, my_address);

      return *this;
    }

    template<typename OtherValueType,
             typename OtherAddressType,
             typename OtherAddressDifferenceType>
    auto operator=(const sram_const_ref<OtherValueType,
                                        OtherAddressType,
                                        OtherAddressDifferenceType>& other) noexcept -> sram_ref&
    {
      return operator=(static_cast<value_type>(other));
    }

    explicit operator value_type() const noexcept
    {
      return value();
    }

    auto value() const noexcept -> value_type
    {
      return read<value_type>(my_address);
    }

  private:
    address_type my_address;
  };

  template<typename ValueType,
           typename AddressType,
           typename AddressDifferenceType>
  class sram_const_ref
  {
  private:
    using address_type = AddressType;

  public:
    using value_type      = ValueType;
    using size_type       = address_type;
    using difference_type = AddressDifferenceType;

    explicit constexpr sram_const_ref(address_type address = 0U) noexcept
      : my_address(address) { }

    sram_const_ref(const sram_const_ref&) noexcept = default;
    ~sram_const_ref() noexcept = default;

    explicit operator value_type() const noexcept
    {
      return value();
    }

    auto value() const noexcept -> value_type
    {
      return read<value_type>(my_address);
    }

  private:
    address_type my_address;
  };

  } } } // namespace mcal::memory::sram

#endif // MCAL_MEMORY_SRAM_REF_2020_04_11_H
