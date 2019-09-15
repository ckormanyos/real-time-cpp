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
  private:
    using pointer      = PointerType;
    using address_type = typename pointer::address_type;

  public:
    using value_type   = typename pointer::value_type;
    using reference    = typename pointer::reference;
    using size_type    = address_type;

    static const size_type static_size = sizeof(value_type);

    address_ptr() = default;

    explicit address_ptr(const address_type addr) : my_ptr(addr) { }

    address_ptr(const pointer& ptr) : my_ptr(ptr) { }

    address_ptr(const address_ptr& x) : my_ptr(x.my_ptr) { }

    ~address_ptr() = default;

    address_ptr& operator=(const address_ptr& other)
    {
      if(this != &other)
      {
        my_ptr = other.my_ptr;
      }
    
      return *this;
    }

    reference operator*()
    {
      return *my_ptr;
    }

    const reference operator*() const
    {
      return *my_ptr;
    }

    const address_ptr& operator++() { my_ptr += static_size; return *this; }
    const address_ptr& operator--() { my_ptr -= static_size; return *this; }

    address_ptr operator++(int) { const address_ptr tmp = *this; my_ptr += static_size; return tmp; }
    address_ptr operator--(int) { const address_ptr tmp = *this; my_ptr -= static_size; return tmp; }

    address_ptr operator+(address_type n) const { return (my_ptr + (n * static_size)); }
    address_ptr operator-(address_type n) const { return (my_ptr - (n * static_size)); }

    const address_ptr& operator+=(address_type n) { my_ptr += (n * static_size); return *this; }
    const address_ptr& operator-=(address_type n) { my_ptr -= (n * static_size); return *this; }

  private:
    pointer my_ptr;

    friend inline address_type operator-(const address_ptr& x,
                                         const address_ptr& y)
    {
      return (x.my_ptr - y.my_ptr) / static_size;
    }

    friend inline address_ptr operator+(address_type n,
                                        const address_ptr& x)
    {
      return address_ptr(x.my_ptr + (n * static_size));
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
