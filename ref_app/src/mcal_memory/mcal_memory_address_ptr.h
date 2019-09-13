///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_ADDRESS_PTR_2019_09_08_H_
  #define MCAL_MEMORY_ADDRESS_PTR_2019_09_08_H_

  namespace mcal { namespace memory {

  template<typename PointerType>
  class address_ptr
  {
  public:
    using pointer      = PointerType;
    using value_type   = typename pointer::value_type;
    using address_type = typename pointer::address_type;
    using size_type    = typename pointer::address_type;

    address_ptr() { }

    explicit constexpr address_ptr(const address_type& addr) : my_ptr(addr) { }

    constexpr address_ptr(const pointer& ptr) : my_ptr(ptr) { }

    constexpr address_ptr(const address_ptr& x) : my_ptr(x.my_ptr) { }

    template<typename OtherPointerType>
    constexpr address_ptr(const OtherPointerType& other)
      : my_ptr(other.my_ptr) { }

    ~address_ptr() = default;

    address_ptr& operator=(const address_ptr& other)
    {
      if(this != &other)
      {
        my_ptr = other.my_ptr;
      }

      return *this;
    }

    constexpr value_type operator*() const
    {
      return *my_ptr;
    }

    address_ptr& operator++() { ++my_ptr; return *this; }
    address_ptr& operator--() { ++my_ptr; return *this; }

    address_ptr operator++(int) { address_ptr tmp = *this; ++my_ptr; return tmp; }
    address_ptr operator--(int) { address_ptr tmp = *this; ++my_ptr; return tmp; }

    address_ptr operator+(address_type n) const { return address_ptr(my_ptr + n); }
    address_ptr operator-(address_type n) const { return address_ptr(my_ptr - n); }

    address_ptr& operator+=(address_type n) { my_ptr += n; return *this; }
    address_ptr& operator-=(address_type n) { my_ptr -= n; return *this; }

  private:
    pointer my_ptr;

    friend inline address_type operator-(const address_ptr& x,
                                         const address_ptr& y)
    {
      return (x.my_ptr - y.my_ptr);
    }

    friend inline address_ptr operator+(address_type n,
                                            const address_ptr& x)
    {
      return address_ptr(x.my_ptr + n);
    }

    friend inline bool operator< (const address_ptr& x, const address_ptr& y) { return (x.my_ptr <  y.my_ptr); }
    friend inline bool operator<=(const address_ptr& x, const address_ptr& y) { return (x.my_ptr <= y.my_ptr); }
    friend inline bool operator==(const address_ptr& x, const address_ptr& y) { return (x.my_ptr == y.my_ptr); }
    friend inline bool operator!=(const address_ptr& x, const address_ptr& y) { return (x.my_ptr != y.my_ptr); }
    friend inline bool operator>=(const address_ptr& x, const address_ptr& y) { return (x.my_ptr >= y.my_ptr); }
    friend inline bool operator> (const address_ptr& x, const address_ptr& y) { return (x.my_ptr >  y.my_ptr); }
  };

  } } // namespace mcal::memory

#endif // MCAL_MEMORY_ADDRESS_PTR_2019_09_08_H_
