///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_DETAIL_2019_09_08_H_
  #define MCAL_MEMORY_DETAIL_2019_09_08_H_

  namespace mcal { namespace memory { namespace detail {

  template<typename PointerType>
  class wrapped_ptr
  {
  public:
    using pointer      = PointerType;
    using value_type   = typename pointer::value_type;
    using address_type = typename pointer::address_type;
    using size_type    = typename pointer::address_type;

    wrapped_ptr() { }

    explicit constexpr wrapped_ptr(const address_type& addr) : my_ptr(addr) { }

    constexpr wrapped_ptr(const pointer& ptr) : my_ptr(ptr) { }

    constexpr wrapped_ptr(const wrapped_ptr& x) : my_ptr(x.my_ptr) { }

    template<typename OtherPointerType>
    constexpr wrapped_ptr(const OtherPointerType& other)
      : my_ptr(other.my_ptr) { }

    ~wrapped_ptr() = default;

    wrapped_ptr& operator=(const wrapped_ptr& other)
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

    wrapped_ptr& operator++() { ++my_ptr; return *this; }
    wrapped_ptr& operator--() { ++my_ptr; return *this; }

    wrapped_ptr operator++(int) { wrapped_ptr tmp = *this; ++my_ptr; return tmp; }
    wrapped_ptr operator--(int) { wrapped_ptr tmp = *this; ++my_ptr; return tmp; }

    wrapped_ptr operator+(address_type n) const { return wrapped_ptr(my_ptr + n); }
    wrapped_ptr operator-(address_type n) const { return wrapped_ptr(my_ptr - n); }

    wrapped_ptr& operator+=(address_type n) { my_ptr += n; return *this; }
    wrapped_ptr& operator-=(address_type n) { my_ptr -= n; return *this; }

  private:
    pointer my_ptr;

    friend inline address_type operator-(const wrapped_ptr& x,
                                         const wrapped_ptr& y)
    {
      return (x.my_ptr - y.my_ptr);
    }

    friend inline wrapped_ptr operator+(address_type n,
                                            const wrapped_ptr& x)
    {
      return progmem_ptr(x.my_ptr + n);
    }

    friend inline bool operator< (const wrapped_ptr& x, const wrapped_ptr& y) { return (x.my_ptr <  y.my_ptr); }
    friend inline bool operator<=(const wrapped_ptr& x, const wrapped_ptr& y) { return (x.my_ptr <= y.my_ptr); }
    friend inline bool operator==(const wrapped_ptr& x, const wrapped_ptr& y) { return (x.my_ptr == y.my_ptr); }
    friend inline bool operator!=(const wrapped_ptr& x, const wrapped_ptr& y) { return (x.my_ptr != y.my_ptr); }
    friend inline bool operator>=(const wrapped_ptr& x, const wrapped_ptr& y) { return (x.my_ptr >= y.my_ptr); }
    friend inline bool operator> (const wrapped_ptr& x, const wrapped_ptr& y) { return (x.my_ptr >  y.my_ptr); }
  };

  } } } // namespace mcal::memory::detail

#endif // MCAL_MEMORY_DETAIL_2019_09_08_H_
