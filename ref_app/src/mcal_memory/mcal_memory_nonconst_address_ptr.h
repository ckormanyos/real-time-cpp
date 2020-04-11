///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_ADDRESS_NONCONST_PTR_2020_04_11_H_
  #define MCAL_MEMORY_ADDRESS_NONCONST_PTR_2020_04_11_H_

  namespace mcal { namespace memory {

  template<typename PointerType>
  class nonconst_address_ptr
  {
  private:
    using pointer      = PointerType;
    using address_type = typename pointer::address_type;

  public:
    using value_type      = typename pointer::value_type;
    using const_reference = const typename pointer::reference;
    using reference       = typename pointer::reference;
    using size_type       = address_type;

    static const size_type static_size = sizeof(value_type);

    explicit nonconst_address_ptr(const address_type addr = 0U)
      : my_ptr(addr) { }

    nonconst_address_ptr(const pointer& ptr) : my_ptr(ptr) { }

    nonconst_address_ptr(const nonconst_address_ptr& other)
      : my_ptr(other.my_ptr) { }

    ~nonconst_address_ptr() = default;

    nonconst_address_ptr& operator=(const nonconst_address_ptr& other)
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

    const_reference operator*() const
    {
      return *my_ptr;
    }

    reference operator[](const size_type i)
    {
      return *(my_ptr + (i * static_size));
    }

    const_reference operator[](const size_type i) const
    {
      return *(my_ptr + (i * static_size));
    }

    nonconst_address_ptr& operator++() { my_ptr += static_size; return *this; }
    nonconst_address_ptr& operator--() { my_ptr -= static_size; return *this; }

    nonconst_address_ptr operator++(int) { const nonconst_address_ptr tmp = *this; my_ptr += static_size; return tmp; }
    nonconst_address_ptr operator--(int) { const nonconst_address_ptr tmp = *this; my_ptr -= static_size; return tmp; }

    nonconst_address_ptr operator+(address_type n) const { return (my_ptr + (n * static_size)); }
    nonconst_address_ptr operator-(address_type n) const { return (my_ptr - (n * static_size)); }

    nonconst_address_ptr& operator+=(address_type n) { my_ptr += (n * static_size); return *this; }
    nonconst_address_ptr& operator-=(address_type n) { my_ptr -= (n * static_size); return *this; }

  private:
    pointer my_ptr;

    friend inline address_type operator-(const nonconst_address_ptr& x,
                                         const nonconst_address_ptr& y)
    {
      return (x.my_ptr - y.my_ptr) / static_size;
    }

    friend inline nonconst_address_ptr operator+(address_type n,
                                        const nonconst_address_ptr& x)
    {
      return nonconst_address_ptr(x.my_ptr + (n * static_size));
    }

    friend inline bool operator< (const nonconst_address_ptr& x, const nonconst_address_ptr& y) { return (x.my_ptr <  y.my_ptr); }
    friend inline bool operator<=(const nonconst_address_ptr& x, const nonconst_address_ptr& y) { return (x.my_ptr <= y.my_ptr); }
    friend inline bool operator==(const nonconst_address_ptr& x, const nonconst_address_ptr& y) { return (x.my_ptr == y.my_ptr); }
    friend inline bool operator!=(const nonconst_address_ptr& x, const nonconst_address_ptr& y) { return (x.my_ptr != y.my_ptr); }
    friend inline bool operator>=(const nonconst_address_ptr& x, const nonconst_address_ptr& y) { return (x.my_ptr >= y.my_ptr); }
    friend inline bool operator> (const nonconst_address_ptr& x, const nonconst_address_ptr& y) { return (x.my_ptr >  y.my_ptr); }
  };

  } } // namespace mcal::memory

#endif // MCAL_MEMORY_ADDRESS_NONCONST_PTR_2020_04_11_H_
