///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_PTR_2020_04_09_H
  #define MCAL_MEMORY_SRAM_PTR_2020_04_09_H

  #include <mcal_memory/mcal_memory_sram_ref.h>

  #include <iterator>

  // Implement a specialized pointer type for sram memory.

  namespace mcal { namespace memory { namespace sram {

  template<typename ValueType,
           typename AddressType,
           typename AddressDifferenceType>
  class sram_ptr
  {
  private:
    using address_type      = AddressType;

  public:
    using pointer           = sram_ptr;
    using reference         = sram_ref<ValueType,
                                       AddressType,
                                       AddressDifferenceType>;
    using value_type        = typename reference::value_type;
    using size_type         = typename reference::size_type;
    using difference_type   = typename reference::difference_type;
    using iterator_category = std::random_access_iterator_tag;

    sram_ptr() noexcept = default;

    explicit constexpr sram_ptr(address_type addr) noexcept : my_address(addr) { }

    template<typename OtherValueType,
             typename OtherAddressType,
             typename OtherAddressDifferenceType>
    sram_ptr(const sram_ptr<OtherValueType, OtherAddressType, OtherAddressDifferenceType>& other) noexcept
      : my_address(other.my_address) { }

    auto operator*() noexcept -> reference
    {
      return reference(my_address);
    }

    auto operator*() const noexcept -> const reference
    {
      return reference(my_address);
    }

    auto operator++() noexcept -> sram_ptr& { my_address += sizeof(value_type); return *this; }
    auto operator--() noexcept -> sram_ptr& { my_address -= sizeof(value_type); return *this; }

    sram_ptr operator++(int) noexcept { const sram_ptr tmp = *this; my_address += sizeof(value_type); return tmp; }
    sram_ptr operator--(int) noexcept { const sram_ptr tmp = *this; my_address -= sizeof(value_type); return tmp; }

    auto operator+(difference_type n) const noexcept -> sram_ptr
    {
      const address_type addr = ((n < 0) ? my_address - ((size_type(0U) - size_type(n)) * sizeof(value_type))
                                         : my_address + (size_type(n) * sizeof(value_type)));

      return sram_ptr(addr);
    }

    auto operator-(difference_type n) const noexcept -> sram_ptr
    {
      const address_type addr = ((n < 0) ? my_address + ((size_type(0U) - size_type(n)) * sizeof(value_type))
                                         : my_address - (size_type(n) * sizeof(value_type)));

      return sram_ptr(addr);
    }

    auto operator+=(difference_type n) noexcept -> sram_ptr&
    {
      my_address = ((n < 0) ? my_address - ((size_type(0U) - size_type(n)) * sizeof(value_type))
                            : my_address + (size_type(n) * sizeof(value_type)));

      return *this;
    }

    auto operator-=(difference_type n) noexcept -> sram_ptr&
    {
      my_address = ((n < 0) ? my_address + ((size_type(0U) - size_type(n)) * sizeof(value_type))
                            : my_address - (size_type(n) * sizeof(value_type)));

      return *this;
    }

  private:
    address_type my_address{};

    template<typename, typename, typename>
    friend class sram_ptr;

    friend inline auto operator-(const sram_ptr& x, const sram_ptr& y) noexcept -> difference_type
    {
      if(x.my_address >= y.my_address)
      {
        return difference_type((x.my_address - y.my_address) / sizeof(value_type));
      }

      return -difference_type((y.my_address - x.my_address) / sizeof(value_type));
    }

    friend inline auto operator+(difference_type n, const sram_ptr& x) noexcept -> sram_ptr
    {
      return sram_ptr(x + n);
    }

    friend inline bool operator< (const sram_ptr& x, const sram_ptr& y) noexcept { return (x.my_address <  y.my_address); }
    friend inline bool operator<=(const sram_ptr& x, const sram_ptr& y) noexcept { return (x.my_address <= y.my_address); }
    friend inline bool operator==(const sram_ptr& x, const sram_ptr& y) noexcept { return (x.my_address == y.my_address); }
    friend inline bool operator!=(const sram_ptr& x, const sram_ptr& y) noexcept { return (x.my_address != y.my_address); }
    friend inline bool operator>=(const sram_ptr& x, const sram_ptr& y) noexcept { return (x.my_address >= y.my_address); }
    friend inline bool operator> (const sram_ptr& x, const sram_ptr& y) noexcept { return (x.my_address >  y.my_address); }
  };

  } } } // namespace mcal::memory::sram

#endif // MCAL_MEMORY_SRAM_PTR_2020_04_09_H
