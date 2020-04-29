///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_CONST_ADDRESS_PTR_2019_09_08_H_
  #define MCAL_MEMORY_CONST_ADDRESS_PTR_2019_09_08_H_

  #include <iterator>

  namespace mcal { namespace memory {

  template<typename PointerType>
  class const_address_ptr
  {
  private:
    using address_type = typename PointerType::size_type;

  public:
    using pointer           = PointerType;
    using value_type        = typename pointer::value_type;
    using reference         = const typename pointer::reference;
    using size_type         = typename pointer::size_type;
    using difference_type   = typename pointer::difference_type;
    using iterator_category = std::random_access_iterator_tag;

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
      return *(my_ptr + difference_type(i * static_size));
    }

    const const_address_ptr& operator++() noexcept { my_ptr += static_size; return *this; }
    const const_address_ptr& operator--() noexcept { my_ptr -= static_size; return *this; }

    const_address_ptr operator++(int) noexcept { const const_address_ptr tmp = *this; my_ptr += static_size; return tmp; }
    const_address_ptr operator--(int) noexcept { const const_address_ptr tmp = *this; my_ptr -= static_size; return tmp; }

    const_address_ptr operator+(difference_type n) const noexcept
    {
      const pointer ptr = ((n < 0) ? my_ptr - difference_type(size_type(-n) * static_size)
                                   : my_ptr + difference_type(size_type(n)  * static_size));

      return const_address_ptr(ptr);
    }

    const_address_ptr operator-(difference_type n) const noexcept
    {
      const pointer ptr = ((n < 0) ? my_ptr + difference_type(size_type(-n) * static_size)
                                   : my_ptr - difference_type(size_type(n)  * static_size));

      return const_address_ptr(ptr);
    }

    const const_address_ptr& operator+=(difference_type n) noexcept
    {
      my_ptr = ((n < 0) ? my_ptr - difference_type(size_type(-n) * static_size)
                        : my_ptr + difference_type(size_type(n)  * static_size));

      return *this;
    }

    const const_address_ptr& operator-=(difference_type n) noexcept
    {
      my_ptr = ((n < 0) ? my_ptr + difference_type(size_type(-n) * static_size)
                        : my_ptr - difference_type(size_type(n)  * static_size));

      return *this;
    }

  private:
    pointer my_ptr;

    friend inline difference_type operator-(const const_address_ptr& x,
                                            const const_address_ptr& y) noexcept
    {
      return (x.my_ptr - y.my_ptr) / static_size;
    }

    friend inline const_address_ptr operator+(difference_type n,
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

  namespace std
  {
    // Provide a template specialization of iterator_trats
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

#endif // MCAL_MEMORY_CONST_ADDRESS_PTR_2019_09_08_H_
