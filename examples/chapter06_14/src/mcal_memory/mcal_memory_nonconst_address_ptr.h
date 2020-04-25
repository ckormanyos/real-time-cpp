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

    static constexpr size_type static_size = sizeof(value_type);

    constexpr nonconst_address_ptr() noexcept = default;

    explicit constexpr nonconst_address_ptr(address_type addr) noexcept
      : my_ptr(addr) { }

    constexpr nonconst_address_ptr(pointer ptr) noexcept
      : my_ptr(ptr) { }

    nonconst_address_ptr(const nonconst_address_ptr& other) noexcept
      : my_ptr(other.my_ptr) { }

    nonconst_address_ptr(nonconst_address_ptr&& other) noexcept
      : my_ptr(other.my_ptr) { }

    ~nonconst_address_ptr() = default;

    nonconst_address_ptr& operator=(const nonconst_address_ptr& other) noexcept
    {
      my_ptr = other.my_ptr;

      return *this;
    }

    nonconst_address_ptr& operator=(nonconst_address_ptr&& other) noexcept
    {
      my_ptr = other.my_ptr;

      return *this;
    }

    reference operator*() noexcept
    {
      reference value = *my_ptr;

      return value;
    }

    const_reference operator*() const noexcept
    {
      const_reference value = *my_ptr;

      return value;
    }

    reference operator[](const size_type i) noexcept
    {
      reference value = *(my_ptr + (i * static_size));

      return value;
    }

    const_reference operator[](const size_type i) const noexcept
    {
      const_reference value = *(my_ptr + (i * static_size));

      return value;
    }

    nonconst_address_ptr& operator++() noexcept { my_ptr += static_size; return *this; }
    nonconst_address_ptr& operator--() noexcept { my_ptr -= static_size; return *this; }

    nonconst_address_ptr operator++(int) noexcept { const nonconst_address_ptr tmp = *this; my_ptr += static_size; return tmp; }
    nonconst_address_ptr operator--(int) noexcept { const nonconst_address_ptr tmp = *this; my_ptr -= static_size; return tmp; }

    nonconst_address_ptr operator+(address_type n) const noexcept { return (my_ptr + (n * static_size)); }
    nonconst_address_ptr operator-(address_type n) const noexcept { return (my_ptr - (n * static_size)); }

    nonconst_address_ptr& operator+=(address_type n) noexcept { my_ptr += (n * static_size); return *this; }
    nonconst_address_ptr& operator-=(address_type n) noexcept { my_ptr -= (n * static_size); return *this; }

  private:
    pointer my_ptr;

    friend inline address_type operator-(const nonconst_address_ptr& x,
                                         const nonconst_address_ptr& y) noexcept
    {
      return (x.my_ptr - y.my_ptr) / static_size;
    }

    friend inline nonconst_address_ptr operator+(address_type n,
                                        const nonconst_address_ptr& x) noexcept
    {
      return nonconst_address_ptr(x.my_ptr + (n * static_size));
    }

    friend inline bool operator< (const nonconst_address_ptr& x, const nonconst_address_ptr& y) noexcept { return (x.my_ptr <  y.my_ptr); }
    friend inline bool operator<=(const nonconst_address_ptr& x, const nonconst_address_ptr& y) noexcept { return (x.my_ptr <= y.my_ptr); }
    friend inline bool operator==(const nonconst_address_ptr& x, const nonconst_address_ptr& y) noexcept { return (x.my_ptr == y.my_ptr); }
    friend inline bool operator!=(const nonconst_address_ptr& x, const nonconst_address_ptr& y) noexcept { return (x.my_ptr != y.my_ptr); }
    friend inline bool operator>=(const nonconst_address_ptr& x, const nonconst_address_ptr& y) noexcept { return (x.my_ptr >= y.my_ptr); }
    friend inline bool operator> (const nonconst_address_ptr& x, const nonconst_address_ptr& y) noexcept { return (x.my_ptr >  y.my_ptr); }
  };

  } } // namespace mcal::memory

#endif // MCAL_MEMORY_ADDRESS_NONCONST_PTR_2020_04_11_H_
