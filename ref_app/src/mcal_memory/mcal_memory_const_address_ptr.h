///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_ADDRESS_CONST_PTR_2019_09_08_H_
  #define MCAL_MEMORY_ADDRESS_CONST_PTR_2019_09_08_H_

  namespace mcal { namespace memory {

  template<typename PointerType>
  class const_address_ptr
  {
  private:
    using pointer      = PointerType;
    using address_type = typename pointer::address_type;

  public:
    using value_type   = typename pointer::value_type;
    using reference    = typename pointer::reference;
    using size_type    = address_type;

    static const size_type static_size = sizeof(value_type);

    const_address_ptr() = default;

    explicit const_address_ptr(const address_type addr) : my_ptr(addr) { }

    const_address_ptr(const pointer& ptr) : my_ptr(ptr) { }

    const_address_ptr(const const_address_ptr& other) : my_ptr(other.my_ptr) { }

    ~const_address_ptr() = default;

    const reference operator*() const
    {
      return *my_ptr;
    }

    const const_address_ptr& operator++() { my_ptr += static_size; return *this; }
    const const_address_ptr& operator--() { my_ptr -= static_size; return *this; }

    const_address_ptr operator++(int) { const const_address_ptr tmp = *this; my_ptr += static_size; return tmp; }
    const_address_ptr operator--(int) { const const_address_ptr tmp = *this; my_ptr -= static_size; return tmp; }

    const_address_ptr operator+(address_type n) const { return (my_ptr + (n * static_size)); }
    const_address_ptr operator-(address_type n) const { return (my_ptr - (n * static_size)); }

    const const_address_ptr& operator+=(address_type n) { my_ptr += (n * static_size); return *this; }
    const const_address_ptr& operator-=(address_type n) { my_ptr -= (n * static_size); return *this; }

  private:
    pointer my_ptr;

    const_address_ptr& operator=(const const_address_ptr&) = delete;

    friend inline address_type operator-(const const_address_ptr& x,
                                         const const_address_ptr& y)
    {
      return (x.my_ptr - y.my_ptr) / static_size;
    }

    friend inline const_address_ptr operator+(address_type n,
                                        const const_address_ptr& x)
    {
      return const_address_ptr(x.my_ptr + (n * static_size));
    }

    friend inline bool operator< (const const_address_ptr& x, const const_address_ptr& y) { return (x.my_ptr <  y.my_ptr); }
    friend inline bool operator<=(const const_address_ptr& x, const const_address_ptr& y) { return (x.my_ptr <= y.my_ptr); }
    friend inline bool operator==(const const_address_ptr& x, const const_address_ptr& y) { return (x.my_ptr == y.my_ptr); }
    friend inline bool operator!=(const const_address_ptr& x, const const_address_ptr& y) { return (x.my_ptr != y.my_ptr); }
    friend inline bool operator>=(const const_address_ptr& x, const const_address_ptr& y) { return (x.my_ptr >= y.my_ptr); }
    friend inline bool operator> (const const_address_ptr& x, const const_address_ptr& y) { return (x.my_ptr >  y.my_ptr); }
  };

  } } // namespace mcal::memory

#endif // MCAL_MEMORY_ADDRESS_CONST_PTR_2019_09_08_H_
