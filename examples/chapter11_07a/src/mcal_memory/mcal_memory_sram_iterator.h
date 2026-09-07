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
  #include <mcal_memory/mcal_memory_sram_ptr.h>

  #include <iterator>

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
    : public mcal::memory::sram::iterator<std::random_access_iterator_tag,
                                          ValueType,
                                          AddressType,
                                          AddressDifferenceType>
  {
  private:
    using base_class_type =
      mcal::memory::sram::iterator<std::random_access_iterator_tag,
                                   ValueType,
                                   AddressType,
                                   AddressDifferenceType>;

  public:
    using value_type        = typename base_class_type::value_type;
    using difference_type   = typename base_class_type::difference_type;
    using pointer           = typename base_class_type::pointer;
    using reference         = typename base_class_type::reference;
    using iterator_category = typename base_class_type::iterator_category;

    sram_iterator() noexcept = default;

    explicit sram_iterator(const AddressType& addr) noexcept : current(addr) { }

    sram_iterator(const pointer x) noexcept : current(x) { }

    template<typename OtherIteratorType,
             typename OtherAddressType,
             typename OtherAddressDifferenceType>
    sram_iterator(const sram_iterator<OtherIteratorType, OtherAddressType, OtherAddressDifferenceType>& other) noexcept
      : current(static_cast<const pointer>(other.current)) { }

    auto operator*() noexcept -> reference
    {
      return *current;
    }

    auto operator*() const noexcept -> const reference
    {
      return *current;
    }

    auto operator[](difference_type n) noexcept -> reference
    {
      return *(current + n);
    }

    auto operator[](difference_type n) const noexcept -> const reference
    {
      return *(current + n);
    }

    auto operator++() noexcept -> sram_iterator& { ++current; return *this; }
    auto operator--() noexcept -> sram_iterator& { --current; return *this; }

    sram_iterator operator++(int) noexcept { const sram_iterator tmp = *this; ++current; return tmp; }
    sram_iterator operator--(int) noexcept { const sram_iterator tmp = *this; --current; return tmp; }

    auto operator+(difference_type n) const noexcept -> sram_iterator
    {
      return sram_iterator(current + n);
    }

    auto operator-(difference_type n) const noexcept -> sram_iterator
    {
      return sram_iterator(current - n);
    }

    auto operator+=(difference_type n) noexcept -> sram_iterator& { current += n; return *this; }
    auto operator-=(difference_type n) noexcept -> sram_iterator& { current -= n; return *this; }

  private:
    pointer current{};

    template<typename, typename, typename>
    friend class sram_iterator;

    friend inline bool operator< (const sram_iterator& x, const sram_iterator& y) noexcept { return (x.current <  y.current); }
    friend inline bool operator<=(const sram_iterator& x, const sram_iterator& y) noexcept { return (x.current <= y.current); }
    friend inline bool operator==(const sram_iterator& x, const sram_iterator& y) noexcept { return (x.current == y.current); }
    friend inline bool operator!=(const sram_iterator& x, const sram_iterator& y) noexcept { return (x.current != y.current); }
    friend inline bool operator>=(const sram_iterator& x, const sram_iterator& y) noexcept { return (x.current >= y.current); }
    friend inline bool operator> (const sram_iterator& x, const sram_iterator& y) noexcept { return (x.current >  y.current); }

    friend inline auto operator-(const sram_iterator& x,
                                 const sram_iterator& y) noexcept
      -> typename sram_iterator::difference_type
    {
      return (x.current - y.current);
    }

    friend inline auto operator+(typename sram_iterator::difference_type n,
                                 const sram_iterator& x) noexcept
      -> sram_iterator
    {
      return sram_iterator(x.current + n);
    }
  };

  template<typename input_iterator>
  typename std::iterator_traits<input_iterator>::difference_type
  distance(input_iterator first, input_iterator last) noexcept
  {
    using local_difference_type =
      typename std::iterator_traits<input_iterator>::difference_type;

    return local_difference_type(last - first);
  }

  template <typename container_type> inline auto begin (const container_type& c) -> decltype(c.begin())  { return c.begin(); }
  template <typename container_type> inline auto end   (const container_type& c) -> decltype(c.end())    { return c.end(); }

  template <typename container_type> inline auto cbegin (const container_type& c) -> decltype(c.cbegin())  { return c.cbegin(); }
  template <typename container_type> inline auto cend   (const container_type& c) -> decltype(c.cend())    { return c.cend(); }

  template <typename container_type> inline auto crbegin(const container_type& c) -> decltype(c.crbegin()) { return c.crbegin(); }
  template <typename container_type> inline auto crend  (const container_type& c) -> decltype(c.crend())   { return c.crend(); }

  } } } // namespace mcal::memory::sram

#endif // MCAL_MEMORY_SRAM_ITERATOR_2020_04_27_H
