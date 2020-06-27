///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_NONCONST_ADDRESS_PTR_2020_04_11_H_
  #define MCAL_MEMORY_NONCONST_ADDRESS_PTR_2020_04_11_H_

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
      reference value = *(my_ptr + difference_type(i * static_size));

      return value;
    }

    const_reference operator[](const size_type i) const noexcept
    {
      const_reference value = *(my_ptr + difference_type(i * static_size));

      return value;
    }

    nonconst_address_ptr& operator++() noexcept { my_ptr += static_size; return *this; }
    nonconst_address_ptr& operator--() noexcept { my_ptr -= static_size; return *this; }

    nonconst_address_ptr operator++(int) noexcept { const nonconst_address_ptr tmp = *this; my_ptr += static_size; return tmp; }
    nonconst_address_ptr operator--(int) noexcept { const nonconst_address_ptr tmp = *this; my_ptr -= static_size; return tmp; }

    nonconst_address_ptr operator+(difference_type n) const noexcept
    {
      const pointer ptr = ((n < 0) ? my_ptr - difference_type(size_type(-n) * static_size)
                                   : my_ptr + difference_type(size_type(n)  * static_size));

      return nonconst_address_ptr(ptr);
    }

    nonconst_address_ptr operator-(difference_type n) const noexcept
    {
      const pointer ptr = ((n < 0) ? my_ptr + difference_type(size_type(-n) * static_size)
                                   : my_ptr - difference_type(size_type(n)  * static_size));

      return nonconst_address_ptr(ptr);
    }

    nonconst_address_ptr& operator+=(difference_type n) noexcept
    {
      my_ptr = ((n < 0) ? my_ptr - difference_type(size_type(-n) * static_size)
                        : my_ptr + difference_type(size_type(n)  * static_size));

      return *this;
    }

    nonconst_address_ptr& operator-=(difference_type n) noexcept
    {
      my_ptr = ((n < 0) ? my_ptr + difference_type(size_type(-n) * static_size)
                        : my_ptr - difference_type(size_type(n)  * static_size));

      return *this;
    }

  private:
    pointer my_ptr;

    friend inline difference_type operator-(const nonconst_address_ptr& x,
                                            const nonconst_address_ptr& y) noexcept
    {
      return (x.my_ptr - y.my_ptr) / static_size;
    }

    friend inline nonconst_address_ptr operator+(difference_type n,
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

  namespace std
  {
    // Provide a template specialization of iterator_trats
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

#endif // MCAL_MEMORY_NONCONST_ADDRESS_PTR_2020_04_11_H_
