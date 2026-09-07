///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_PROGMEM_PTR_2019_09_08_H
  #define MCAL_MEMORY_PROGMEM_PTR_2019_09_08_H

  #include <mcal_memory/mcal_memory_progmem_ref.h>

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

    progmem_ptr() noexcept = default;

    explicit constexpr progmem_ptr(address_type addr) noexcept
      : my_address(addr) { }

    template<typename OtherValueType,
             typename OtherAddressType,
             typename OtherAddressDifferenceType>
    progmem_ptr(const progmem_ptr<OtherValueType, OtherAddressType, OtherAddressDifferenceType>& other) noexcept
      : my_address(other.my_address) { }

    auto operator*() const noexcept -> reference
    {
      return reference(my_address);
    }

    auto operator++() noexcept -> progmem_ptr& { my_address += sizeof(value_type); return *this; }
    auto operator--() noexcept -> progmem_ptr& { my_address -= sizeof(value_type); return *this; }

    progmem_ptr operator++(int) noexcept { const progmem_ptr tmp = *this; my_address += sizeof(value_type); return tmp; }
    progmem_ptr operator--(int) noexcept { const progmem_ptr tmp = *this; my_address -= sizeof(value_type); return tmp; }

    auto operator+(difference_type n) const noexcept -> progmem_ptr
    {
      const address_type addr = ((n < 0) ? my_address - ((size_type(0U) - size_type(n)) * sizeof(value_type))
                                         : my_address + (size_type(n) * sizeof(value_type)));

      return progmem_ptr(addr);
    }

    auto operator-(difference_type n) const noexcept -> progmem_ptr
    {
      const address_type addr = ((n < 0) ? my_address + ((size_type(0U) - size_type(n)) * sizeof(value_type))
                                         : my_address - (size_type(n) * sizeof(value_type)));

      return progmem_ptr(addr);
    }

    auto operator+=(difference_type n) noexcept -> progmem_ptr&
    {
      my_address = ((n < 0) ? my_address - ((size_type(0U) - size_type(n)) * sizeof(value_type))
                            : my_address + (size_type(n) * sizeof(value_type)));

      return *this;
    }

    auto operator-=(difference_type n) noexcept -> progmem_ptr&
    {
      my_address = ((n < 0) ? my_address + ((size_type(0U) - size_type(n)) * sizeof(value_type))
                            : my_address - (size_type(n) * sizeof(value_type)));

      return *this;
    }

  private:
    address_type my_address{};

    template<typename, typename, typename>
    friend class progmem_ptr;

    friend inline auto operator-(const progmem_ptr& x, const progmem_ptr& y) noexcept -> difference_type
    {
      if(x.my_address >= y.my_address)
      {
        return difference_type((x.my_address - y.my_address) / sizeof(value_type));
      }

      return -difference_type((y.my_address - x.my_address) / sizeof(value_type));
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

#endif // MCAL_MEMORY_PROGMEM_PTR_2019_09_08_H
