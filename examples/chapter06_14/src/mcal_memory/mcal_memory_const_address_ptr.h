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

    static constexpr size_type static_size = sizeof(value_type);

    explicit constexpr const_address_ptr(address_type addr = 0U) noexcept
      : my_ptr(addr) { }

    constexpr const_address_ptr(pointer ptr) noexcept : my_ptr(ptr) { }

    const_address_ptr(const const_address_ptr& other) noexcept
      : my_ptr(other.my_ptr) { }

    const_address_ptr(const_address_ptr&& other) noexcept
      : my_ptr(other.my_ptr) { }

    ~const_address_ptr() noexcept { }

    const_address_ptr& operator=(const const_address_ptr& other)
    {
      my_ptr = other.my_ptr;

      return *this;
    }

    const_address_ptr& operator=(const_address_ptr&& other)
    {
      my_ptr = other.my_ptr;

      return *this;
    }

    const reference operator*() const noexcept
    {
      const reference value = *my_ptr;

      return value;
    }

    const reference operator[](const size_type i) const noexcept
    {
      return *(my_ptr + (i * static_size));
    }

    const const_address_ptr& operator++() noexcept { my_ptr += static_size; return *this; }
    const const_address_ptr& operator--() noexcept { my_ptr -= static_size; return *this; }

    const_address_ptr operator++(int) noexcept { const const_address_ptr tmp = *this; my_ptr += static_size; return tmp; }
    const_address_ptr operator--(int) noexcept { const const_address_ptr tmp = *this; my_ptr -= static_size; return tmp; }

    const_address_ptr operator+(address_type n) const noexcept { return (my_ptr + (n * static_size)); }
    const_address_ptr operator-(address_type n) const noexcept { return (my_ptr - (n * static_size)); }

    const const_address_ptr& operator+=(address_type n) noexcept { my_ptr += (n * static_size); return *this; }
    const const_address_ptr& operator-=(address_type n) noexcept { my_ptr -= (n * static_size); return *this; }

  private:
    pointer my_ptr;

    friend inline address_type operator-(const const_address_ptr& x,
                                         const const_address_ptr& y) noexcept
    {
      return (x.my_ptr - y.my_ptr) / static_size;
    }

    friend inline const_address_ptr operator+(address_type n,
                                        const const_address_ptr& x) noexcept
    {
      return const_address_ptr(x.my_ptr + (n * static_size));
    }

    friend inline bool operator< (const const_address_ptr& x, const const_address_ptr& y) noexcept { return (x.my_ptr <  y.my_ptr); }
    friend inline bool operator<=(const const_address_ptr& x, const const_address_ptr& y) noexcept { return (x.my_ptr <= y.my_ptr); }
    friend inline bool operator==(const const_address_ptr& x, const const_address_ptr& y) noexcept { return (x.my_ptr == y.my_ptr); }
    friend inline bool operator!=(const const_address_ptr& x, const const_address_ptr& y) noexcept { return (x.my_ptr != y.my_ptr); }
    friend inline bool operator>=(const const_address_ptr& x, const const_address_ptr& y) noexcept { return (x.my_ptr >= y.my_ptr); }
    friend inline bool operator> (const const_address_ptr& x, const const_address_ptr& y) noexcept { return (x.my_ptr >  y.my_ptr); }
  };

  } } // namespace mcal::memory

#endif // MCAL_MEMORY_ADDRESS_CONST_PTR_2019_09_08_H_
