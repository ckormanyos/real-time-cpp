///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_PROGMEM_PTR_2019_09_08_H
  #define MCAL_MEMORY_PROGMEM_PTR_2019_09_08_H

  #include <mcal_memory/mcal_memory_progmem_ref.h>

  #include <iterator>
  #include <type_traits>

  // Implement a specialized pointer type for read-only program memory.

  namespace mcal { namespace memory { namespace progmem {

  template<typename ValueType,
           typename AddressType,
           typename AddressDifferenceType>
  class progmem_ptr
  {
  private:
    using address_type = AddressType;

  public:
    using reference       = progmem_ref<ValueType, AddressType, AddressDifferenceType>;
    using value_type      = typename reference::value_type;
    using size_type       = typename reference::size_type;
    using difference_type = typename reference::difference_type;
    using iterator_category = std::random_access_iterator_tag;

    static constexpr size_type value_size = sizeof(value_type);

    constexpr progmem_ptr() noexcept = default;

    explicit constexpr progmem_ptr(address_type addr) noexcept
      : my_address(addr) { }

    template<typename OtherValueType,
             typename OtherAddressType,
             typename OtherAddressDifferenceType,
             typename std::enable_if_t<
               std::is_convertible<OtherValueType, ValueType>::value &&
               std::is_convertible<OtherAddressType, address_type>::value &&
               std::is_convertible<OtherAddressDifferenceType, AddressDifferenceType>::value
             >* = nullptr>
    progmem_ptr(const progmem_ptr<OtherValueType, OtherAddressType, OtherAddressDifferenceType>& other) noexcept
      : my_address(other.my_address) { }

    auto operator*() const noexcept -> reference
    {
      return reference(my_address);
    }

    auto operator++() noexcept -> progmem_ptr& { my_address += value_size; return *this; }
    auto operator--() noexcept -> progmem_ptr& { my_address -= value_size; return *this; }

    progmem_ptr operator++(int) noexcept { const progmem_ptr tmp = *this; my_address += value_size; return tmp; }
    progmem_ptr operator--(int) noexcept { const progmem_ptr tmp = *this; my_address -= value_size; return tmp; }

    auto operator[](difference_type n) const noexcept -> reference
    {
      return *(*this + n);
    }

    auto operator+(difference_type n) const noexcept -> progmem_ptr
    {
      return progmem_ptr(offset_address(my_address, n));
    }

    auto operator-(difference_type n) const noexcept -> progmem_ptr
    {
      return progmem_ptr(offset_address(my_address, n, true));
    }

    auto operator+=(difference_type n) noexcept -> progmem_ptr&
    {
      my_address = offset_address(my_address, n);

      return *this;
    }

    auto operator-=(difference_type n) noexcept -> progmem_ptr&
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
    friend class progmem_ptr;

    friend inline auto operator-(const progmem_ptr& x, const progmem_ptr& y) noexcept -> difference_type
    {
      if(x.my_address >= y.my_address)
      {
        return difference_type((x.my_address - y.my_address) / value_size);
      }

      return -difference_type((y.my_address - x.my_address) / value_size);
    }

    friend inline auto operator+(difference_type n, const progmem_ptr& x) noexcept -> progmem_ptr
    {
      return progmem_ptr(x + n);
    }

    friend inline bool operator< (const progmem_ptr& x, const progmem_ptr& y) noexcept { return (x.my_address <  y.my_address); }
    friend inline bool operator<=(const progmem_ptr& x, const progmem_ptr& y) noexcept { return (x.my_address <= y.my_address); }
    friend inline bool operator==(const progmem_ptr& x, const progmem_ptr& y) noexcept { return (x.my_address == y.my_address); }
    friend inline bool operator!=(const progmem_ptr& x, const progmem_ptr& y) noexcept { return (x.my_address != y.my_address); }
    friend inline bool operator>=(const progmem_ptr& x, const progmem_ptr& y) noexcept { return (x.my_address >= y.my_address); }
    friend inline bool operator> (const progmem_ptr& x, const progmem_ptr& y) noexcept { return (x.my_address >  y.my_address); }
  };

  } } } // namespace mcal::memory::progmem

  template<typename ValueType, typename AddressType, typename AddressDifferenceType>
  constexpr typename mcal::memory::progmem::progmem_ptr<ValueType, AddressType, AddressDifferenceType>::size_type
    mcal::memory::progmem::progmem_ptr<ValueType, AddressType, AddressDifferenceType>::value_size;

#endif // MCAL_MEMORY_PROGMEM_PTR_2019_09_08_H
