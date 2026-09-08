///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_NONCONST_ADDRESS_PTR_2020_04_11_H
  #define MCAL_MEMORY_NONCONST_ADDRESS_PTR_2020_04_11_H

  #include <iterator>

  namespace mcal { namespace memory {

  template<typename PointerType>
  class nonconst_address_ptr
  {
  private:
    using address_type = typename PointerType::size_type;

  public:
    using pointer           = PointerType;
    using value_type        = typename pointer::value_type;
    using const_reference   = const typename pointer::reference;
    using reference         = typename pointer::reference;
    using size_type         = typename pointer::size_type;
    using difference_type   = typename pointer::difference_type;
    using iterator_category = std::random_access_iterator_tag;

    static constexpr size_type static_size = 1U;

    constexpr nonconst_address_ptr() noexcept = default;

    explicit constexpr nonconst_address_ptr(address_type addr) noexcept
      : my_ptr(addr) { }

    constexpr nonconst_address_ptr(pointer ptr) noexcept
      : my_ptr(ptr) { }

    auto operator*() noexcept -> reference
    {
      reference value = *my_ptr;

      return value;
    }

    auto operator*() const noexcept -> const_reference
    {
      const_reference value = *my_ptr;

      return value;
    }

    auto operator[](const difference_type i) noexcept -> reference
    {
      reference value = *(my_ptr + (i * difference_type(static_size)));

      return value;
    }

    auto operator[](const difference_type i) const noexcept -> const_reference
    {
      const_reference value = *(my_ptr + (i * difference_type(static_size)));

      return value;
    }

    auto operator++() noexcept -> nonconst_address_ptr& { my_ptr += static_size; return *this; }
    auto operator--() noexcept -> nonconst_address_ptr& { my_ptr -= static_size; return *this; }

    nonconst_address_ptr operator++(int) noexcept { const nonconst_address_ptr tmp = *this; my_ptr += static_size; return tmp; }
    nonconst_address_ptr operator--(int) noexcept { const nonconst_address_ptr tmp = *this; my_ptr -= static_size; return tmp; }

    auto operator+(difference_type n) const noexcept -> nonconst_address_ptr
    {
      return nonconst_address_ptr(offset_pointer(my_ptr, n));
    }

    auto operator-(difference_type n) const noexcept -> nonconst_address_ptr
    {
      return nonconst_address_ptr(offset_pointer(my_ptr, n, true));
    }

    auto operator+=(difference_type n) noexcept -> nonconst_address_ptr&
    {
      my_ptr = offset_pointer(my_ptr, n);

      return *this;
    }

    auto operator-=(difference_type n) noexcept -> nonconst_address_ptr&
    {
      my_ptr = offset_pointer(my_ptr, n, true);

      return *this;
    }

  private:
    static constexpr pointer offset_pointer(pointer ptr,
                                             difference_type n,
                                             bool subtract = false) noexcept
    {
      return ((n < 0) ? (subtract ? ptr + difference_type((size_type(0U) - size_type(n)) * static_size)
                                  : ptr - difference_type((size_type(0U) - size_type(n)) * static_size))
                      : (subtract ? ptr - difference_type(size_type(n) * static_size)
                                  : ptr + difference_type(size_type(n) * static_size)));
    }

    pointer my_ptr{};

    template<typename, typename>
    friend class const_address_ptr;

    friend inline auto operator-(const nonconst_address_ptr& x,
                                 const nonconst_address_ptr& y) noexcept -> difference_type
    {
      return x.my_ptr - y.my_ptr;
    }

    friend inline auto operator+(difference_type n,
                                 const nonconst_address_ptr& x) noexcept -> nonconst_address_ptr
    {
      return nonconst_address_ptr(x.my_ptr + n);
    }

    friend inline bool operator< (const nonconst_address_ptr& x, const nonconst_address_ptr& y) noexcept { return (x.my_ptr <  y.my_ptr); }
    friend inline bool operator<=(const nonconst_address_ptr& x, const nonconst_address_ptr& y) noexcept { return (x.my_ptr <= y.my_ptr); }
    friend inline bool operator==(const nonconst_address_ptr& x, const nonconst_address_ptr& y) noexcept { return (x.my_ptr == y.my_ptr); }
    friend inline bool operator!=(const nonconst_address_ptr& x, const nonconst_address_ptr& y) noexcept { return (x.my_ptr != y.my_ptr); }
    friend inline bool operator>=(const nonconst_address_ptr& x, const nonconst_address_ptr& y) noexcept { return (x.my_ptr >= y.my_ptr); }
    friend inline bool operator> (const nonconst_address_ptr& x, const nonconst_address_ptr& y) noexcept { return (x.my_ptr >  y.my_ptr); }
  };

  } } // namespace mcal::memory

  template<typename PointerType>
  constexpr typename mcal::memory::nonconst_address_ptr<PointerType>::size_type
    mcal::memory::nonconst_address_ptr<PointerType>::static_size;

  namespace std
  {
    // Provide a template specialization of iterator_traits
    // for mcal::memory::nonconst_address_ptr<>.

    template<typename PointerType>
    struct iterator_traits<mcal::memory::nonconst_address_ptr<PointerType>>
    {
    private:
      using pointer_type = mcal::memory::nonconst_address_ptr<PointerType>;

    public:
      using difference_type   = typename pointer_type::difference_type;
      using value_type        = typename pointer_type::value_type;
      using pointer           = typename pointer_type::pointer;
      using reference         = typename pointer_type::reference;
      using iterator_category = typename pointer_type::iterator_category;
    };
  }

#endif // MCAL_MEMORY_NONCONST_ADDRESS_PTR_2020_04_11_H
