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
    using difference_type   = typename pointer::difference_type;
    using value_type        = typename pointer::value_type;
    using reference         = typename pointer::reference;
    using iterator_category = IteratorCategoryType;
  };

  template<typename ValueType,
           typename AddressType,
           typename AddressDifferenceType>
  class progmem_iterator
    : public mcal::memory::progmem::iterator<std::random_access_iterator_tag,
                                             ValueType,
                                             AddressType,
                                             AddressDifferenceType>
  {
  private:
    using base_class_type =
      mcal::memory::progmem::iterator<std::random_access_iterator_tag,
                                      ValueType,
                                      AddressType,
                                      AddressDifferenceType>;

  public:
    using value_type        = typename base_class_type::value_type;
    using difference_type   = typename base_class_type::difference_type;
    using pointer           = typename base_class_type::pointer;
    using reference         = typename base_class_type::reference;
    using iterator_category = typename base_class_type::iterator_category;

    progmem_iterator() noexcept : current(nullptr) { }

    explicit progmem_iterator(const AddressType& addr) noexcept : current(addr) { }

    progmem_iterator(const pointer x) noexcept : current(x) { }

    template<typename OtherIteratorType,
             typename OtherAddressType,
             typename OtherAddressDifferenceType>
    progmem_iterator(const progmem_iterator<OtherIteratorType, OtherAddressType, OtherAddressDifferenceType>& other) noexcept
      : current(static_cast<const pointer>(other.current)) { }

    progmem_iterator(const progmem_iterator& other) noexcept : current(other.current) { }

    ~progmem_iterator() noexcept { }

    progmem_iterator& operator=(const progmem_iterator& other) noexcept
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

    const progmem_iterator& operator++() noexcept { ++current; return *this; }
    const progmem_iterator& operator--() noexcept { --current; return *this; }

    progmem_iterator operator++(int) noexcept { const progmem_iterator tmp = *this; ++current; return tmp; }
    progmem_iterator operator--(int) noexcept { const progmem_iterator tmp = *this; --current; return tmp; }

    progmem_iterator operator+(difference_type n) const noexcept
    {
      return progmem_iterator(current + n);
    }

    progmem_iterator operator-(difference_type n) const noexcept
    {
      return progmem_iterator(current - n);
    }

    const progmem_iterator& operator+=(difference_type n) noexcept { current += n; return *this; }
    const progmem_iterator& operator-=(difference_type n) noexcept { current -= n; return *this; }

  private:
    pointer current;

    friend inline bool operator< (const progmem_iterator& x, const progmem_iterator& y) noexcept { return (x.current <  y.current); }
    friend inline bool operator<=(const progmem_iterator& x, const progmem_iterator& y) noexcept { return (x.current <= y.current); }
    friend inline bool operator==(const progmem_iterator& x, const progmem_iterator& y) noexcept { return (x.current == y.current); }
    friend inline bool operator!=(const progmem_iterator& x, const progmem_iterator& y) noexcept { return (x.current != y.current); }
    friend inline bool operator>=(const progmem_iterator& x, const progmem_iterator& y) noexcept { return (x.current >= y.current); }
    friend inline bool operator> (const progmem_iterator& x, const progmem_iterator& y) noexcept { return (x.current >  y.current); }

    friend inline typename progmem_iterator::difference_type
    operator-(const progmem_iterator& x,
              const progmem_iterator& y) noexcept
    {
      return (x.current - y.current);
    }

    friend inline progmem_iterator
    operator+(typename progmem_iterator::difference_type n,
              const progmem_iterator& x) noexcept
    {
      return progmem_iterator(x.current + n);
    }
  };

  template<typename input_iterator>
  typename iterator_traits<input_iterator>::difference_type
  distance(input_iterator first, input_iterator last) noexcept
  {
    using local_difference_type =
      typename iterator_traits<input_iterator>::difference_type;

    return local_difference_type(last - first);
  }

  template <typename container_type> inline auto cbegin (const container_type& c) -> decltype(c.cbegin())  { return c.cbegin(); }
  template <typename container_type> inline auto cend   (const container_type& c) -> decltype(c.cend())    { return c.cend(); }

  template <typename container_type> inline auto crbegin(const container_type& c) -> decltype(c.crbegin()) { return c.crbegin(); }
  template <typename container_type> inline auto crend  (const container_type& c) -> decltype(c.crend())   { return c.crend(); }

  template <typename value_type, const mcal_progmem_uintptr_t N> inline const progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t> cbegin (const value_type(&c_array)[N] MY_PROGMEM) { return progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>((mcal_progmem_uintptr_t) MCAL_PROGMEM_ADDRESSOF(c_array[0U])); }
  template <typename value_type, const mcal_progmem_uintptr_t N> inline const progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t> cend   (const value_type(&c_array)[N] MY_PROGMEM) { return progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>((mcal_progmem_uintptr_t) MCAL_PROGMEM_ADDRESSOF(c_array[N])); }

  template <typename value_type, const mcal_progmem_uintptr_t N> inline const std::reverse_iterator<progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>> crbegin(const value_type(&c_array)[N] MY_PROGMEM) { return std::reverse_iterator<progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>>((mcal_progmem_uintptr_t) MCAL_PROGMEM_ADDRESSOF(c_array[N])); }
  template <typename value_type, const mcal_progmem_uintptr_t N> inline const std::reverse_iterator<progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>> crend  (const value_type(&c_array)[N] MY_PROGMEM) { return std::reverse_iterator<progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>>((mcal_progmem_uintptr_t) MCAL_PROGMEM_ADDRESSOF(c_array[0U])); }

  } } } // namespace mcal::memory::progmem

#endif // MCAL_MEMORY_PROGMEM_ITERATOR_2019_05_04_H_
