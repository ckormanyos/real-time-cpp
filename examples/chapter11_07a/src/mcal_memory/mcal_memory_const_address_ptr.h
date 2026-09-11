///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_CONST_ADDRESS_PTR_2019_09_08_H
  #define MCAL_MEMORY_CONST_ADDRESS_PTR_2019_09_08_H

  #include <iterator>

  namespace mcal { namespace memory {

  template<typename PointerType>
  class nonconst_address_ptr;

  template<typename PointerType,
           typename ReferenceType = const typename PointerType::reference>
  class const_address_ptr
  {
  private:
    using address_type = typename PointerType::size_type;

  public:
    using pointer           = PointerType;
    using value_type        = typename pointer::value_type;
    using reference         = ReferenceType;
    using size_type         = typename pointer::size_type;
    using difference_type   = typename pointer::difference_type;
    using iterator_category = std::random_access_iterator_tag;

    static constexpr size_type static_size = 1U;

    explicit constexpr const_address_ptr(address_type addr = 0U) noexcept
      : my_ptr(addr) { }

    constexpr const_address_ptr(pointer ptr) noexcept : my_ptr(ptr) { }

    template<typename OtherPointerType>
    constexpr const_address_ptr(const nonconst_address_ptr<OtherPointerType>& other) noexcept
      : my_ptr(other.my_ptr) { }

    auto operator*() const noexcept -> reference
    {
      const reference value = *my_ptr;

      return value;
    }

    auto operator[](const difference_type i) const noexcept -> reference
    {
      return *offset_ptr(my_ptr, i);
    }

    auto operator++() noexcept -> const_address_ptr& { my_ptr += static_size; return *this; }
    auto operator--() noexcept -> const_address_ptr& { my_ptr -= static_size; return *this; }

    const_address_ptr operator++(int) noexcept { const const_address_ptr tmp = *this; my_ptr += static_size; return tmp; }
    const_address_ptr operator--(int) noexcept { const const_address_ptr tmp = *this; my_ptr -= static_size; return tmp; }

    auto operator+(difference_type n) const noexcept -> const_address_ptr
    {
      return const_address_ptr(offset_pointer(my_ptr, n));
    }

    auto operator-(difference_type n) const noexcept -> const_address_ptr
    {
      return const_address_ptr(offset_pointer(my_ptr, n, true));
    }

    auto operator+=(difference_type n) noexcept -> const_address_ptr&
    {
      my_ptr = offset_pointer(my_ptr, n);

      return *this;
    }

    auto operator-=(difference_type n) noexcept -> const_address_ptr&
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

    template<typename>
    friend class nonconst_address_ptr;

    friend inline auto operator-(const const_address_ptr& x,
                                 const const_address_ptr& y) noexcept -> difference_type
    {
      return x.my_ptr - y.my_ptr;
    }

    friend inline auto operator+(difference_type n,
                                 const const_address_ptr& x) noexcept -> const_address_ptr
    {
      return const_address_ptr(x.my_ptr + n);
    }

    friend inline bool operator< (const const_address_ptr& x, const const_address_ptr& y) noexcept { return (x.my_ptr <  y.my_ptr); }
    friend inline bool operator<=(const const_address_ptr& x, const const_address_ptr& y) noexcept { return (x.my_ptr <= y.my_ptr); }
    friend inline bool operator==(const const_address_ptr& x, const const_address_ptr& y) noexcept { return (x.my_ptr == y.my_ptr); }
    friend inline bool operator!=(const const_address_ptr& x, const const_address_ptr& y) noexcept { return (x.my_ptr != y.my_ptr); }
    friend inline bool operator>=(const const_address_ptr& x, const const_address_ptr& y) noexcept { return (x.my_ptr >= y.my_ptr); }
    friend inline bool operator> (const const_address_ptr& x, const const_address_ptr& y) noexcept { return (x.my_ptr >  y.my_ptr); }
  };

  } } // namespace mcal::memory

  template<typename PointerType, typename ReferenceType>
  constexpr typename mcal::memory::const_address_ptr<PointerType, ReferenceType>::size_type
    mcal::memory::const_address_ptr<PointerType, ReferenceType>::static_size;

  namespace std
  {
    // Provide a template specialization of iterator_traits
    // for mcal::memory::const_address_ptr<>.

    template<typename PointerType, typename ReferenceType>
    struct iterator_traits<mcal::memory::const_address_ptr<PointerType, ReferenceType>>
    {
    private:
      using pointer_type = mcal::memory::const_address_ptr<PointerType, ReferenceType>;

    public:
      using difference_type   = typename pointer_type::difference_type;
      using value_type        = typename pointer_type::value_type;
      using pointer           = typename pointer_type::pointer;
      using reference         = typename pointer_type::reference;
      using iterator_category = typename pointer_type::iterator_category;
    };
  }

#endif // MCAL_MEMORY_CONST_ADDRESS_PTR_2019_09_08_H
