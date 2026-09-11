///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_ITERATOR_2020_04_27_H
  #define MCAL_MEMORY_SRAM_ITERATOR_2020_04_27_H

  #include <mcal_memory/mcal_memory_const_address_ptr.h>
  #include <mcal_memory/mcal_memory_nonconst_address_ptr.h>
  #include <mcal_memory/mcal_memory_random_access_iterator_operations.h>
  #include <mcal_memory/mcal_memory_sram_ptr.h>

  #include <iterator>
  #include <type_traits>

  // Implement specialized iterator types for read/write SRAM memory
  // (such as a serial SRAM chip or a parallel SRAM brick).

  namespace mcal { namespace memory { namespace sram {

  template<typename IteratorCategoryType,
           typename ValueType,
           typename AddressType,
           typename AddressDifferenceType>
  struct iterator
  {
    using pointer           = mcal::memory::nonconst_address_ptr<sram_ptr<ValueType, AddressType, AddressDifferenceType>>;
    using difference_type   = typename pointer::difference_type;
    using value_type        = typename pointer::value_type;
    using reference         = typename pointer::reference;
    using iterator_category = IteratorCategoryType;
  };

  template<typename ValueType,
           typename AddressType,
           typename AddressDifferenceType>
  class sram_iterator

  {
  public:
    using pointer           = mcal::memory::nonconst_address_ptr<sram_ptr<ValueType, AddressType, AddressDifferenceType>>;
    using difference_type   = typename pointer::difference_type;
    using value_type        = typename pointer::value_type;
    using const_pointer     = mcal::memory::const_address_ptr<
      sram_ptr<ValueType, AddressType, AddressDifferenceType>,
      sram_const_ref<ValueType, AddressType, AddressDifferenceType>>;
    using reference         = typename pointer::reference;
    using const_reference   = sram_const_ref<ValueType, AddressType, AddressDifferenceType>;
    using iterator_category = std::random_access_iterator_tag;
    using operations         = mcal::memory::random_access_iterator_operations<pointer>;

    sram_iterator() noexcept = default;

    explicit sram_iterator(const AddressType& addr) noexcept : current(addr) { }

    sram_iterator(const pointer x) noexcept : current(x) { }

    operator const_pointer() const noexcept
    {
      return const_pointer(current);
    }

    template<typename OtherIteratorType,
             typename OtherAddressType,
             typename OtherAddressDifferenceType,
             typename std::enable_if_t<
               std::is_convertible<OtherIteratorType, ValueType>::value &&
               std::is_convertible<OtherAddressType, AddressType>::value &&
               std::is_convertible<OtherAddressDifferenceType, AddressDifferenceType>::value
             >* = nullptr>
    sram_iterator(const sram_iterator<OtherIteratorType, OtherAddressType, OtherAddressDifferenceType>& other) noexcept
      : current(static_cast<const pointer>(other.current)) { }

    auto operator*() noexcept -> reference
    {
      return *current;
    }

    auto operator*() const noexcept -> const_reference
    {
      return *const_pointer(current);
    }

    auto operator[](difference_type n) noexcept -> reference
    {
      return *(current + n);
    }

    auto operator[](difference_type n) const noexcept -> const_reference
    {
      return *(const_pointer(current) + n);
    }

    auto operator++() noexcept -> sram_iterator& { operations::increment(current, difference_type(1)); return *this; }
    auto operator--() noexcept -> sram_iterator& { operations::increment(current, difference_type(-1)); return *this; }

    sram_iterator operator++(int) noexcept { const sram_iterator tmp = *this; ++(*this); return tmp; }
    sram_iterator operator--(int) noexcept { const sram_iterator tmp = *this; --(*this); return tmp; }

    auto operator+(difference_type n) const noexcept -> sram_iterator
    {
      return sram_iterator(operations::add(current, n));
    }

    auto operator-(difference_type n) const noexcept -> sram_iterator
    {
      return sram_iterator(operations::subtract(current, n));
    }

    auto operator+=(difference_type n) noexcept -> sram_iterator& { operations::increment(current, n); return *this; }
    auto operator-=(difference_type n) noexcept -> sram_iterator& { operations::increment(current, -n); return *this; }

  private:
    pointer current{};

    template<typename, typename, typename>
    friend class sram_iterator;

    friend inline bool operator< (const sram_iterator& x, const sram_iterator& y) noexcept { return operations::less(x.current, y.current); }
    friend inline bool operator<=(const sram_iterator& x, const sram_iterator& y) noexcept { return operations::less_equal(x.current, y.current); }
    friend inline bool operator==(const sram_iterator& x, const sram_iterator& y) noexcept { return operations::equal(x.current, y.current); }
    friend inline bool operator!=(const sram_iterator& x, const sram_iterator& y) noexcept { return operations::not_equal(x.current, y.current); }
    friend inline bool operator>=(const sram_iterator& x, const sram_iterator& y) noexcept { return operations::greater_equal(x.current, y.current); }
    friend inline bool operator> (const sram_iterator& x, const sram_iterator& y) noexcept { return operations::greater(x.current, y.current); }

    friend inline auto operator-(const sram_iterator& x,
                                 const sram_iterator& y) noexcept
      -> typename sram_iterator::difference_type
    {
      return operations::distance(x.current, y.current);
    }

    friend inline auto operator+(typename sram_iterator::difference_type n,
                                 const sram_iterator& x) noexcept
      -> sram_iterator
    {
      return sram_iterator(x.current + n);
    }
  };

  template <typename container_type> inline auto begin (const container_type& c) -> decltype(c.begin())  { return c.begin(); }
  template <typename container_type> inline auto end   (const container_type& c) -> decltype(c.end())    { return c.end(); }

  template <typename container_type> inline auto cbegin (const container_type& c) -> decltype(c.cbegin())  { return c.cbegin(); }
  template <typename container_type> inline auto cend   (const container_type& c) -> decltype(c.cend())    { return c.cend(); }

  template <typename container_type> inline auto crbegin(const container_type& c) -> decltype(c.crbegin()) { return c.crbegin(); }
  template <typename container_type> inline auto crend  (const container_type& c) -> decltype(c.crend())   { return c.crend(); }

  } } } // namespace mcal::memory::sram

#endif // MCAL_MEMORY_SRAM_ITERATOR_2020_04_27_H
