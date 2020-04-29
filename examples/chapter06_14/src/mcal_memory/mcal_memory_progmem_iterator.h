///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_PROGMEM_ITERATOR_2019_05_04_H_
  #define MCAL_MEMORY_PROGMEM_ITERATOR_2019_05_04_H_

  #include <iterator>

  #include <mcal_memory/mcal_memory_const_address_ptr.h>
  #include <mcal_memory/mcal_memory_progmem_ptr.h>

  // Implement specialized iterator types for read-only program memory.

  namespace mcal { namespace memory { namespace progmem {

  struct input_iterator_tag                                             { };
  struct output_iterator_tag                                            { };
  struct forward_iterator_tag       : public input_iterator_tag         { };
  struct bidirectional_iterator_tag : public forward_iterator_tag       { };
  struct random_access_iterator_tag : public bidirectional_iterator_tag { };

  template<typename iterator_type>
  struct iterator_traits
  {
    using difference_type   = typename iterator_type::difference_type;
    using value_type        = typename iterator_type::value_type;
    using pointer           = typename iterator_type::pointer;
    using reference         = typename iterator_type::reference;
    using iterator_category = typename iterator_type::iterator_category;
  };

  template<typename ValueType,
           typename AddressType,
           typename AddressDifferenceType>
  struct iterator_traits<const mcal::memory::const_address_ptr<progmem_ptr<ValueType, AddressType, AddressDifferenceType>>>
  {
  private:
    using iterator_type =
      const mcal::memory::const_address_ptr<progmem_ptr<ValueType, AddressType, AddressDifferenceType>>;

  public:
    using difference_type   = typename iterator_type::difference_type;
    using value_type        = typename iterator_type::value_type;
    using pointer           = typename iterator_type::pointer;
    using reference         = typename iterator_type::reference;
    using iterator_category = typename iterator_type::iterator_category;
  };

  template<typename IteratorCategoryType,
           typename ValueType,
           typename AddressType,
           typename AddressDifferenceType>
  struct iterator
  {
    using pointer           = mcal::memory::const_address_ptr<progmem_ptr<ValueType, AddressType, AddressDifferenceType>>;
    using difference_type   = const typename pointer::difference_type;
    using value_type        = const typename pointer::value_type;
    using reference         = const typename pointer::value_type;
    using iterator_category = IteratorCategoryType;
  };

  template<typename ValueType,
           typename AddressType,
           typename AddressDifferenceType>
  class forward_iterator
    : public mcal::memory::progmem::iterator<random_access_iterator_tag,
                                             ValueType,
                                             AddressType,
                                             AddressDifferenceType>
  {
  private:
    using base_class_type =
      mcal::memory::progmem::iterator<random_access_iterator_tag,
                                      ValueType,
                                      AddressType,
                                      AddressDifferenceType>;

  public:
    using value_type        = typename base_class_type::value_type;
    using difference_type   = typename base_class_type::difference_type;
    using pointer           = typename base_class_type::pointer;
    using reference         = typename base_class_type::reference;
    using iterator_category = typename base_class_type::iterator_category;

    forward_iterator() noexcept : current(nullptr) { }

    explicit forward_iterator(const AddressType& addr) noexcept : current(addr) { }

    forward_iterator(const pointer x) noexcept : current(x) { }

    template<typename OtherIteratorType,
             typename OtherAddressType,
             typename OtherAddressDifferenceType>
    forward_iterator(const forward_iterator<OtherIteratorType, OtherAddressType, OtherAddressDifferenceType>& other) noexcept
      : current(static_cast<const pointer>(other.current)) { }

    forward_iterator(const forward_iterator& other) noexcept : current(other.current) { }

    ~forward_iterator() noexcept { }

    forward_iterator& operator=(const forward_iterator& other) noexcept
    {
      if(this != &other)
      {
        current = other.current;
      }

      return *this;
    }

    reference operator*() const noexcept
    {
      return reference(*current);
    }

    reference operator[](difference_type n) const noexcept
    {
      return reference(*(current + n));
    }

    const forward_iterator& operator++() noexcept { ++current; return *this; }
    const forward_iterator& operator--() noexcept { --current; return *this; }

    forward_iterator operator++(int) noexcept { const forward_iterator tmp = *this; ++current; return tmp; }
    forward_iterator operator--(int) noexcept { const forward_iterator tmp = *this; --current; return tmp; }

    forward_iterator operator+(difference_type n) const noexcept
    {
      return forward_iterator(current + n);
    }

    forward_iterator operator-(difference_type n) const noexcept
    {
      return forward_iterator(current - n);
    }

    const forward_iterator& operator+=(difference_type n) noexcept { current += n; return *this; }
    const forward_iterator& operator-=(difference_type n) noexcept { current -= n; return *this; }

  private:
    pointer current;

    friend inline bool operator< (const forward_iterator& x, const forward_iterator& y) noexcept { return (x.current <  y.current); }
    friend inline bool operator<=(const forward_iterator& x, const forward_iterator& y) noexcept { return (x.current <= y.current); }
    friend inline bool operator==(const forward_iterator& x, const forward_iterator& y) noexcept { return (x.current == y.current); }
    friend inline bool operator!=(const forward_iterator& x, const forward_iterator& y) noexcept { return (x.current != y.current); }
    friend inline bool operator>=(const forward_iterator& x, const forward_iterator& y) noexcept { return (x.current >= y.current); }
    friend inline bool operator> (const forward_iterator& x, const forward_iterator& y) noexcept { return (x.current >  y.current); }

    friend inline typename forward_iterator::difference_type
    operator-(const forward_iterator& x,
              const forward_iterator& y) noexcept
    {
      return (x.current.ptr - y.current.ptr);
    }

    friend inline forward_iterator
    operator+(typename forward_iterator::difference_type n,
              const forward_iterator& x) noexcept
    {
      return forward_iterator(x.current + n);
    }
  };

  template<typename input_iterator>
  typename mcal::memory::progmem::iterator_traits<input_iterator>::difference_type
  distance(input_iterator first, input_iterator last) noexcept
  {
    using local_difference_type =
      typename mcal::memory::progmem::iterator_traits<input_iterator>::difference_type;

    return local_difference_type(last - first);
  }

  template <typename container_type> inline auto cbegin (const container_type& c) -> decltype(c.cbegin())  { return c.cbegin(); }
  template <typename container_type> inline auto cend   (const container_type& c) -> decltype(c.cend())    { return c.cend(); }

  template <typename container_type> inline auto crbegin(const container_type& c) -> decltype(c.crbegin()) { return c.crbegin(); }
  template <typename container_type> inline auto crend  (const container_type& c) -> decltype(c.crend())   { return c.crend(); }

  template <typename value_type, const mcal_progmem_uintptr_t N> inline const forward_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t> cbegin (const value_type(&c_array)[N] MY_PROGMEM) { return forward_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>((mcal_progmem_uintptr_t) MCAL_PROGMEM_ADDRESSOF(c_array[0U])); }
  template <typename value_type, const mcal_progmem_uintptr_t N> inline const forward_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t> cend   (const value_type(&c_array)[N] MY_PROGMEM) { return forward_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>((mcal_progmem_uintptr_t) MCAL_PROGMEM_ADDRESSOF(c_array[N])); }

  template <typename value_type, const mcal_progmem_uintptr_t N> inline const std::reverse_iterator<forward_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>> crbegin(const value_type(&c_array)[N] MY_PROGMEM) { return std::reverse_iterator<forward_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>>((mcal_progmem_uintptr_t) MCAL_PROGMEM_ADDRESSOF(c_array[N])); }
  template <typename value_type, const mcal_progmem_uintptr_t N> inline const std::reverse_iterator<forward_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>> crend  (const value_type(&c_array)[N] MY_PROGMEM) { return std::reverse_iterator<forward_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>>((mcal_progmem_uintptr_t) MCAL_PROGMEM_ADDRESSOF(c_array[0U])); }

  } } } // namespace mcal::memory::progmem

#endif // MCAL_MEMORY_PROGMEM_ITERATOR_2019_05_04_H_
