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

    auto operator*() const noexcept -> reference
    {
      const reference value = *my_ptr;

      return value;
    }

    auto operator[](const difference_type i) const noexcept -> reference
    {
      return *(my_ptr + (i * difference_type(static_size)));
    }

    auto operator++() noexcept -> const_address_ptr& { my_ptr += static_size; return *this; }
    auto operator--() noexcept -> const_address_ptr& { my_ptr -= static_size; return *this; }

    const_address_ptr operator++(int) noexcept { const const_address_ptr tmp = *this; my_ptr += static_size; return tmp; }
    const_address_ptr operator--(int) noexcept { const const_address_ptr tmp = *this; my_ptr -= static_size; return tmp; }

    auto operator+(difference_type n) const noexcept -> const_address_ptr
    {
      const pointer ptr = ((n < 0) ? my_ptr - difference_type((size_type(0U) - size_type(n)) * static_size)
                                   : my_ptr + difference_type(size_type(n)  * static_size));

      return const_address_ptr(ptr);
    }

    auto operator-(difference_type n) const noexcept -> const_address_ptr
    {
      const pointer ptr = ((n < 0) ? my_ptr + difference_type((size_type(0U) - size_type(n)) * static_size)
                                   : my_ptr - difference_type(size_type(n)  * static_size));

      return const_address_ptr(ptr);
    }

    auto operator+=(difference_type n) noexcept -> const_address_ptr&
    {
      my_ptr = ((n < 0) ? my_ptr - difference_type((size_type(0U) - size_type(n)) * static_size)
                        : my_ptr + difference_type(size_type(n)  * static_size));

      return *this;
    }

    auto operator-=(difference_type n) noexcept -> const_address_ptr&
    {
      my_ptr = ((n < 0) ? my_ptr + difference_type((size_type(0U) - size_type(n)) * static_size)
                        : my_ptr - difference_type(size_type(n)  * static_size));

      return *this;
    }

  private:
    pointer my_ptr{};

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

  namespace std
  {
    // Provide a template specialization of iterator_traits
    // for mcal::memory::const_address_ptr<>.

    template<typename PointerType>
    struct iterator_traits<mcal::memory::const_address_ptr<PointerType>>
    {
    private:
      using pointer_type = mcal::memory::const_address_ptr<PointerType>;

    public:
      using difference_type   = typename pointer_type::difference_type;
      using value_type        = typename pointer_type::value_type;
      using pointer           = typename pointer_type::pointer;
      using reference         = typename pointer_type::reference;
      using iterator_category = typename pointer_type::iterator_category;
    };
  }

#endif // MCAL_MEMORY_CONST_ADDRESS_PTR_2019_09_08_H
