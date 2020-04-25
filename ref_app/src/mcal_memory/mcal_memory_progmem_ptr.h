///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_PROGMEM_PTR_2019_09_08_H_
  #define MCAL_MEMORY_PROGMEM_PTR_2019_09_08_H_

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

    progmem_ptr() noexcept : my_address() { }

    explicit constexpr progmem_ptr(address_type addr) noexcept
      : my_address(addr) { }

    progmem_ptr(const progmem_ptr& other) noexcept
      : my_address(other.my_address) { }

    progmem_ptr(progmem_ptr&& other) noexcept
      : my_address(other.my_address) { }

    template<typename OtherValueType,
             typename OtherAddressType,
             typename OtherAddressDifferenceType>
    progmem_ptr(const progmem_ptr<OtherValueType, OtherAddressType, OtherAddressDifferenceType>& other) noexcept
      : my_address(other.my_address) { }

    ~progmem_ptr() noexcept { }

    progmem_ptr& operator=(const progmem_ptr& other) noexcept
    {
      my_address = other.my_address;

      return *this;
    }

    progmem_ptr& operator=(progmem_ptr&& other) noexcept
    {
      my_address = other.my_address;

      return *this;
    }

    const reference operator*() const noexcept
    {
      return reference(my_address);
    }

    const progmem_ptr& operator++() noexcept { ++my_address; return *this; }
    const progmem_ptr& operator--() noexcept { --my_address; return *this; }

    const progmem_ptr operator++(int) noexcept { const progmem_ptr tmp = *this; ++my_address; return tmp; }
    const progmem_ptr operator--(int) noexcept { const progmem_ptr tmp = *this; --my_address; return tmp; }

    const progmem_ptr operator+(difference_type n) const noexcept
    {
      const address_type addr = ((n < 0) ? my_address - size_type(-n)
                                         : my_address + size_type(n));

      return progmem_ptr(addr);
    }

    const progmem_ptr operator-(difference_type n) const noexcept
    {
      const address_type addr = ((n < 0) ? my_address + size_type(-n)
                                         : my_address - size_type(n));

      return progmem_ptr(addr);
    }

    const progmem_ptr& operator+=(difference_type n) noexcept
    {
      my_address = ((n < 0) ? my_address - size_type(-n)
                            : my_address + size_type(n));

      return *this;
    }

    const progmem_ptr& operator-=(difference_type n) noexcept
    {
      my_address = ((n < 0) ? my_address + size_type(-n)
                            : my_address - size_type(n));

      return *this;
    }

  private:
    address_type my_address;

    friend inline difference_type operator-(const progmem_ptr& x, const progmem_ptr& y) noexcept
    {
      return (x.my_address - y.my_address);
    }

    friend inline progmem_ptr operator+(difference_type n, const progmem_ptr& x) noexcept
    {
      return progmem_ptr(x.my_address + n);
    }

    friend inline bool operator< (const progmem_ptr& x, const progmem_ptr& y) noexcept { return (x.my_address <  y.my_address); }
    friend inline bool operator<=(const progmem_ptr& x, const progmem_ptr& y) noexcept { return (x.my_address <= y.my_address); }
    friend inline bool operator==(const progmem_ptr& x, const progmem_ptr& y) noexcept { return (x.my_address == y.my_address); }
    friend inline bool operator!=(const progmem_ptr& x, const progmem_ptr& y) noexcept { return (x.my_address != y.my_address); }
    friend inline bool operator>=(const progmem_ptr& x, const progmem_ptr& y) noexcept { return (x.my_address >= y.my_address); }
    friend inline bool operator> (const progmem_ptr& x, const progmem_ptr& y) noexcept { return (x.my_address >  y.my_address); }
  };

  } } } // namespace mcal::memory::progmem

#endif // MCAL_MEMORY_PROGMEM_PTR_2019_09_08_H_
