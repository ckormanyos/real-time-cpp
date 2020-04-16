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
           typename AddressType>
  class progmem_ptr
  {
  public:
    using reference    = progmem_ref<ValueType, AddressType>;
    using value_type   = typename reference::value_type;
    using address_type = AddressType;

    progmem_ptr() = delete;

    explicit progmem_ptr(const address_type& addr) : my_address(addr) { }

    progmem_ptr(progmem_ptr& x) : my_address(x.my_address) { }

    template<typename OtherValueType, typename OtherAddressType>
    progmem_ptr(const progmem_ptr<OtherValueType, OtherAddressType>& other)
      : my_address(other.my_address) { }

    ~progmem_ptr() = default;

    progmem_ptr& operator=(const progmem_ptr& other)
    {
      if(this != &other)
      {
        my_address = other.my_address;
      }

      return *this;
    }

    const reference operator*() const
    {
      return reference(my_address);
    }

    const progmem_ptr& operator++() { ++my_address; return *this; }
    const progmem_ptr& operator--() { --my_address; return *this; }

    const progmem_ptr operator++(int) { const progmem_ptr tmp = *this; ++my_address; return tmp; }
    const progmem_ptr operator--(int) { const progmem_ptr tmp = *this; --my_address; return tmp; }

    const progmem_ptr operator+(address_type n) const { return progmem_ptr(my_address + n); }
    const progmem_ptr operator-(address_type n) const { return progmem_ptr(my_address - n); }

    const progmem_ptr& operator+=(address_type n) { my_address += n; return *this; }
    const progmem_ptr& operator-=(address_type n) { my_address -= n; return *this; }

  private:
    address_type my_address;

    friend inline address_type operator-(const progmem_ptr& x, const progmem_ptr& y)
    {
      return (x.my_address - y.my_address);
    }

    friend inline progmem_ptr operator+(address_type n, const progmem_ptr& x)
    {
      return progmem_ptr(x.my_address + n);
    }

    friend inline bool operator< (const progmem_ptr& x, const progmem_ptr& y) { return (x.my_address <  y.my_address); }
    friend inline bool operator<=(const progmem_ptr& x, const progmem_ptr& y) { return (x.my_address <= y.my_address); }
    friend inline bool operator==(const progmem_ptr& x, const progmem_ptr& y) { return (x.my_address == y.my_address); }
    friend inline bool operator!=(const progmem_ptr& x, const progmem_ptr& y) { return (x.my_address != y.my_address); }
    friend inline bool operator>=(const progmem_ptr& x, const progmem_ptr& y) { return (x.my_address >= y.my_address); }
    friend inline bool operator> (const progmem_ptr& x, const progmem_ptr& y) { return (x.my_address >  y.my_address); }
  };

  } } } // namespace mcal::memory::progmem

#endif // MCAL_MEMORY_PROGMEM_PTR_2019_09_08_H_
