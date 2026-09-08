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
  #include <type_traits>

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

    static constexpr size_type value_size = sizeof(value_type);

    sram_ptr() noexcept = default;

    explicit constexpr sram_ptr(address_type addr) noexcept : my_address(addr) { }

    template<typename OtherValueType,
             typename OtherAddressType,
             typename OtherAddressDifferenceType,
             typename std::enable_if<
               std::is_convertible<OtherValueType, ValueType>::value &&
               std::is_convertible<OtherAddressType, address_type>::value &&
               std::is_convertible<OtherAddressDifferenceType, AddressDifferenceType>::value
             >::type* = nullptr>
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

    auto operator++() noexcept -> sram_ptr& { my_address += value_size; return *this; }
    auto operator--() noexcept -> sram_ptr& { my_address -= value_size; return *this; }

    sram_ptr operator++(int) noexcept { const sram_ptr tmp = *this; my_address += value_size; return tmp; }
    sram_ptr operator--(int) noexcept { const sram_ptr tmp = *this; my_address -= value_size; return tmp; }

    auto operator[](difference_type n) const noexcept -> reference
    {
      return *(*this + n);
    }

    auto operator+(difference_type n) const noexcept -> sram_ptr
    {
      return sram_ptr(offset_address(my_address, n));
    }

    auto operator-(difference_type n) const noexcept -> sram_ptr
    {
      return sram_ptr(offset_address(my_address, n, true));
    }

    auto operator+=(difference_type n) noexcept -> sram_ptr&
    {
      my_address = offset_address(my_address, n);

      return *this;
    }

    auto operator-=(difference_type n) noexcept -> sram_ptr&
    {
      my_address = offset_address(my_address, n, true);

      return *this;
    }

  private:
    static constexpr address_type offset_address(address_type address,
                                                 difference_type n,
                                                 bool subtract = false) noexcept
    {
      return ((n < 0) ? (subtract ? address + ((size_type(0U) - size_type(n)) * value_size)
                                  : address - ((size_type(0U) - size_type(n)) * value_size))
                      : (subtract ? address - (size_type(n) * value_size)
                                  : address + (size_type(n) * value_size)));
    }

    address_type my_address{};

    template<typename, typename, typename>
    friend class sram_ptr;

    friend inline auto operator-(const sram_ptr& x, const sram_ptr& y) noexcept -> difference_type
    {
      if(x.my_address >= y.my_address)
      {
        return difference_type((x.my_address - y.my_address) / value_size);
      }

      return -difference_type((y.my_address - x.my_address) / value_size);
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

  template<typename ValueType, typename AddressType, typename AddressDifferenceType>
  constexpr typename mcal::memory::sram::sram_ptr<ValueType, AddressType, AddressDifferenceType>::size_type
    mcal::memory::sram::sram_ptr<ValueType, AddressType, AddressDifferenceType>::value_size;

#endif // MCAL_MEMORY_SRAM_PTR_2020_04_09_H
