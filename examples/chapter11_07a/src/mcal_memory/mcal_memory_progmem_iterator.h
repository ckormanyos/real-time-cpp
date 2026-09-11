///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_PROGMEM_ITERATOR_2019_05_04_H
  #define MCAL_MEMORY_PROGMEM_ITERATOR_2019_05_04_H

  #include <mcal_memory/mcal_memory_const_address_ptr.h>
  #include <mcal_memory/mcal_memory_progmem_ptr.h>
  #include <mcal_memory/mcal_memory_random_access_iterator_operations.h>

  #include <iterator>
  #include <type_traits>

  // Implement specialized iterator types for read-only program memory.

  namespace mcal { namespace memory { namespace progmem {

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

  {
  public:
    using pointer           = mcal::memory::const_address_ptr<progmem_ptr<ValueType, AddressType, AddressDifferenceType>>;
    using difference_type   = typename pointer::difference_type;
    using value_type        = typename pointer::value_type;
    using reference         = typename pointer::reference;
    using iterator_category = std::random_access_iterator_tag;
    using operations         = mcal::memory::random_access_iterator_operations<pointer>;

    progmem_iterator() noexcept = default;

    explicit progmem_iterator(const AddressType& addr) noexcept : current(addr) { }

    progmem_iterator(const pointer x) noexcept : current(x) { }

    template<typename OtherValueType,
             typename OtherAddressType,
             typename OtherAddressDifferenceType,
             typename std::enable_if_t<
                std::is_convertible<OtherValueType, ValueType>::value &&
               std::is_convertible<OtherAddressType, AddressType>::value &&
               std::is_convertible<OtherAddressDifferenceType, AddressDifferenceType>::value
             >* = nullptr>
    progmem_iterator(const progmem_iterator<OtherValueType, OtherAddressType, OtherAddressDifferenceType>& other) noexcept
      : current(static_cast<const pointer>(other.current)) { }

    auto operator*() const noexcept -> reference
    {
      return *current;
    }

    auto operator[](difference_type n) const noexcept -> reference
    {
      return *(current + n);
    }

    auto operator++() noexcept -> progmem_iterator& { operations::increment(current, difference_type(1)); return *this; }
    auto operator--() noexcept -> progmem_iterator& { operations::increment(current, difference_type(-1)); return *this; }

    progmem_iterator operator++(int) noexcept { const progmem_iterator tmp = *this; ++(*this); return tmp; }
    progmem_iterator operator--(int) noexcept { const progmem_iterator tmp = *this; --(*this); return tmp; }

    auto operator+(difference_type n) const noexcept -> progmem_iterator
    {
      return progmem_iterator(operations::add(current, n));
    }

    auto operator-(difference_type n) const noexcept -> progmem_iterator
    {
      return progmem_iterator(operations::subtract(current, n));
    }

    auto operator+=(difference_type n) noexcept -> progmem_iterator& { operations::increment(current, n); return *this; }
    auto operator-=(difference_type n) noexcept -> progmem_iterator& { operations::increment(current, -n); return *this; }

    template<typename OtherValueType, typename OtherAddressType, typename OtherAddressDifferenceType>
    auto operator==(const progmem_iterator<OtherValueType, OtherAddressType, OtherAddressDifferenceType>& other) const noexcept -> bool
    {
      return (const_pointer(current) == const_pointer(other.current));
    }

    template<typename OtherValueType, typename OtherAddressType, typename OtherAddressDifferenceType>
    auto operator!=(const progmem_iterator<OtherValueType, OtherAddressType, OtherAddressDifferenceType>& other) const noexcept -> bool
    {
      return !(*this == other);
    }

    template<typename OtherValueType, typename OtherAddressType, typename OtherAddressDifferenceType>
    auto operator-(const progmem_iterator<OtherValueType, OtherAddressType, OtherAddressDifferenceType>& other) const noexcept
      -> difference_type
    {
      return const_pointer(current) - const_pointer(other.current);
    }

    template<typename OtherValueType, typename OtherAddressType, typename OtherAddressDifferenceType>
    auto operator<(const progmem_iterator<OtherValueType, OtherAddressType, OtherAddressDifferenceType>& other) const noexcept -> bool
    {
      return const_pointer(current) < const_pointer(other.current);
    }

    template<typename OtherValueType, typename OtherAddressType, typename OtherAddressDifferenceType>
    auto operator<=(const progmem_iterator<OtherValueType, OtherAddressType, OtherAddressDifferenceType>& other) const noexcept -> bool
    {
      return const_pointer(current) <= const_pointer(other.current);
    }

    template<typename OtherValueType, typename OtherAddressType, typename OtherAddressDifferenceType>
    auto operator>(const progmem_iterator<OtherValueType, OtherAddressType, OtherAddressDifferenceType>& other) const noexcept -> bool
    {
      return const_pointer(current) > const_pointer(other.current);
    }

    template<typename OtherValueType, typename OtherAddressType, typename OtherAddressDifferenceType>
    auto operator>=(const progmem_iterator<OtherValueType, OtherAddressType, OtherAddressDifferenceType>& other) const noexcept -> bool
    {
      return const_pointer(current) >= const_pointer(other.current);
    }

  private:
    pointer current{};

    template<typename, typename, typename>
    friend class progmem_iterator;

    friend inline bool operator< (const progmem_iterator& x, const progmem_iterator& y) noexcept { return operations::less(x.current, y.current); }
    friend inline bool operator<=(const progmem_iterator& x, const progmem_iterator& y) noexcept { return operations::less_equal(x.current, y.current); }
    friend inline bool operator==(const progmem_iterator& x, const progmem_iterator& y) noexcept { return operations::equal(x.current, y.current); }
    friend inline bool operator!=(const progmem_iterator& x, const progmem_iterator& y) noexcept { return operations::not_equal(x.current, y.current); }
    friend inline bool operator>=(const progmem_iterator& x, const progmem_iterator& y) noexcept { return operations::greater_equal(x.current, y.current); }
    friend inline bool operator> (const progmem_iterator& x, const progmem_iterator& y) noexcept { return operations::greater(x.current, y.current); }

    friend inline auto operator-(const progmem_iterator& x,
                                 const progmem_iterator& y) noexcept
      -> typename progmem_iterator::difference_type
    {
      return operations::distance(x.current, y.current);
    }

    friend inline auto operator+(typename progmem_iterator::difference_type n,
                                 const progmem_iterator& x) noexcept
      -> progmem_iterator
    {
      return progmem_iterator(x.current + n);
    }
  };

  template <typename container_type> inline auto cbegin (const container_type& c) -> decltype(c.cbegin())  { return c.cbegin(); }
  template <typename container_type> inline auto cend   (const container_type& c) -> decltype(c.cend())    { return c.cend(); }

  template <typename container_type> inline auto crbegin(const container_type& c) -> decltype(c.crbegin()) { return c.crbegin(); }
  template <typename container_type> inline auto crend  (const container_type& c) -> decltype(c.crend())   { return c.crend(); }

  template <typename value_type, mcal_progmem_uintptr_t N>
  inline auto cbegin(const value_type(&c_array)[N] MY_PROGMEM)
    -> const progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>
  {
    return progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>(
      static_cast<mcal_progmem_uintptr_t>(MCAL_PROGMEM_ADDRESSOF(c_array[0U])));
  }

  template <typename value_type, mcal_progmem_uintptr_t N>
  inline auto cend(const value_type(&c_array)[N] MY_PROGMEM)
    -> const progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>
  {
    return progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>(
      static_cast<mcal_progmem_uintptr_t>(MCAL_PROGMEM_ADDRESSOF(c_array[0U]))
        + (static_cast<mcal_progmem_uintptr_t>(N) * sizeof(value_type)));
  }

  template <typename value_type, mcal_progmem_uintptr_t N>
  inline auto crbegin(const value_type(&c_array)[N] MY_PROGMEM)
    -> const std::reverse_iterator<progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>>
  {
    using iterator_type = progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>;
    return std::reverse_iterator<iterator_type>(
      iterator_type(
        static_cast<mcal_progmem_uintptr_t>(MCAL_PROGMEM_ADDRESSOF(c_array[0U]))
          + (static_cast<mcal_progmem_uintptr_t>(N) * sizeof(value_type))));
  }

  template <typename value_type, mcal_progmem_uintptr_t N>
  inline auto crend(const value_type(&c_array)[N] MY_PROGMEM)
    -> const std::reverse_iterator<progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>>
  {
    using iterator_type = progmem_iterator<value_type, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>;
    return std::reverse_iterator<iterator_type>(
      iterator_type(static_cast<mcal_progmem_uintptr_t>(MCAL_PROGMEM_ADDRESSOF(c_array[0U]))));
  }

  } } } // namespace mcal::memory::progmem

#endif // MCAL_MEMORY_PROGMEM_ITERATOR_2019_05_04_H
