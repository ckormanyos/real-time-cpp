///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_PTR_2020_04_09_H_
  #define MCAL_MEMORY_SRAM_PTR_2020_04_09_H_

  #include <iterator>

  #include <mcal_memory/mcal_memory_sram_ref.h>

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
    using reference         = sram_ref<ValueType,
                                       AddressType,
                                       AddressDifferenceType>;
    using value_type        = typename reference::value_type;
    using size_type         = typename reference::size_type;
    using difference_type   = typename reference::difference_type;
    using iterator_category = std::bidirectional_iterator_tag;

    sram_ptr() noexcept : my_address() { }

    explicit constexpr sram_ptr(address_type addr) noexcept : my_address(addr) { }

    sram_ptr(const sram_ptr& other) noexcept : my_address(other.my_address) { }

    sram_ptr(sram_ptr&& other) noexcept : my_address(other.my_address) { }

    template<typename OtherValueType,
             typename OtherAddressType,
             typename OtherAddressDifferenceType>
    sram_ptr(const sram_ptr<OtherValueType, OtherAddressType, OtherAddressDifferenceType>& other) noexcept
      : my_address(other.my_address) { }

    ~sram_ptr() { }

    sram_ptr& operator=(const sram_ptr& other) noexcept
    {
      if(this != &other)
      {
        my_address = other.my_address;
      }

      return *this;
    }

    sram_ptr& operator=(sram_ptr&& other) noexcept
    {
      my_address = other.my_address;

      return *this;
    }

    reference operator*() noexcept
    {
      return reference(my_address);
    }

    const reference operator*() const noexcept
    {
      return reference(my_address);
    }

    sram_ptr& operator++() noexcept { ++my_address; return *this; }
    sram_ptr& operator--() noexcept { --my_address; return *this; }

    sram_ptr operator++(int) noexcept { const sram_ptr tmp = *this; ++my_address; return tmp; }
    sram_ptr operator--(int) noexcept { const sram_ptr tmp = *this; --my_address; return tmp; }

    sram_ptr operator+(difference_type n) const noexcept
    {
      const address_type addr = ((n < 0) ? my_address - size_type(-n)
                                         : my_address + size_type(n));

      return sram_ptr(addr);
    }

    sram_ptr operator-(difference_type n) const noexcept
    {
      const address_type addr = ((n < 0) ? my_address + size_type(-n)
                                         : my_address - size_type(n));

      return sram_ptr(addr);
    }

    sram_ptr& operator+=(difference_type n) noexcept
    {
      my_address = ((n < 0) ? my_address - size_type(-n)
                            : my_address + size_type(n));

      return *this;
    }

    sram_ptr& operator-=(difference_type n) noexcept
    {
      my_address = ((n < 0) ? my_address + size_type(-n)
                            : my_address - size_type(n));

      return *this;
    }

  private:
    address_type my_address;

    friend inline difference_type operator-(const sram_ptr& x, const sram_ptr& y) noexcept
    {
      return (x.my_address - y.my_address);
    }

    friend inline sram_ptr operator+(difference_type n, const sram_ptr& x) noexcept
    {
      return sram_ptr(x.my_address + n);
    }

    friend inline bool operator< (const sram_ptr& x, const sram_ptr& y) noexcept { return (x.my_address <  y.my_address); }
    friend inline bool operator<=(const sram_ptr& x, const sram_ptr& y) noexcept { return (x.my_address <= y.my_address); }
    friend inline bool operator==(const sram_ptr& x, const sram_ptr& y) noexcept { return (x.my_address == y.my_address); }
    friend inline bool operator!=(const sram_ptr& x, const sram_ptr& y) noexcept { return (x.my_address != y.my_address); }
    friend inline bool operator>=(const sram_ptr& x, const sram_ptr& y) noexcept { return (x.my_address >= y.my_address); }
    friend inline bool operator> (const sram_ptr& x, const sram_ptr& y) noexcept { return (x.my_address >  y.my_address); }
  };

  } } } // namespace mcal::memory::sram

#endif // MCAL_MEMORY_SRAM_PTR_2020_04_09_H_
