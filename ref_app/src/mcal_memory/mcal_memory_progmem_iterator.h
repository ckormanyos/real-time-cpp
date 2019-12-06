///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PROGMEM_ITERATOR_2019_05_04_
  #define MCAL_PROGMEM_ITERATOR_2019_05_04_

  #include <mcal_memory/mcal_memory_address_ptr.h>
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
           typename AddressType>
  struct iterator_traits<const mcal::memory::address_ptr<progmem_ptr<ValueType, AddressType>>>
  {
  private:
    using iterator_type =
      const mcal::memory::address_ptr<progmem_ptr<ValueType, AddressType>>;

  public:
    using difference_type   = typename iterator_type::difference_type;
    using value_type        = typename iterator_type::value_type;
    using pointer           = typename iterator_type::pointer;
    using reference         = typename iterator_type::reference;
    using iterator_category = typename iterator_type::iterator_category;
  };

  template<typename IteratorCategoryType,
           typename ValueType,
           typename AddressType>
  struct iterator
  {
    using pointer           = mcal::memory::address_ptr<progmem_ptr<ValueType, AddressType>>;
    using difference_type   = const typename pointer::size_type;
    using value_type        = const typename pointer::value_type;
    using reference         = const typename pointer::value_type;
    using iterator_category = IteratorCategoryType;
  };

  template<typename ValueType,
           typename AddressType>
  class forward_iterator
    : public mcal::memory::progmem::iterator<random_access_iterator_tag,
                                             ValueType,
                                             AddressType>
  {
  private:
    using base_class_type =
      mcal::memory::progmem::iterator<random_access_iterator_tag,
                                      ValueType,
                                      AddressType>;

  public:
    using value_type        = typename base_class_type::value_type;
    using difference_type   = typename base_class_type::difference_type;
    using pointer           = typename base_class_type::pointer;
    using reference         = typename base_class_type::reference;
    using iterator_category = typename base_class_type::iterator_category;

    forward_iterator() { }

    explicit forward_iterator(const AddressType& addr) : current(addr) { }

    forward_iterator(const pointer x) : current(x) { }

    template<typename OtherIteratorType, typename OtherValueType>
    forward_iterator(const forward_iterator<OtherIteratorType, OtherValueType>& other)
      : current(static_cast<const pointer>(other.current)) { }

    ~forward_iterator() = default;

    forward_iterator& operator=(forward_iterator&) = default;

    reference operator*() const
    {
      return operator[](0U);
    }

    reference operator[](difference_type n) const
    {
      const pointer const_pointer_to_current_plus_n = current + n;

      return reference(*const_pointer_to_current_plus_n);
    }

    const forward_iterator& operator++() { ++current; return *this; }
    const forward_iterator& operator--() { --current; return *this; }

    const forward_iterator operator++(int) { const forward_iterator tmp = *this; ++current; return tmp; }
    const forward_iterator operator--(int) { const forward_iterator tmp = *this; --current; return tmp; }

    const forward_iterator operator+(difference_type n) const { return forward_iterator(current + n); }
    const forward_iterator operator-(difference_type n) const { return forward_iterator(current - n); }

    const forward_iterator& operator+=(difference_type n) { current += n; return *this; }
    const forward_iterator& operator-=(difference_type n) { current -= n; return *this; }

  private:
    pointer current;

    friend inline bool operator< (const forward_iterator& x, const forward_iterator& y) { return (x.current <  y.current); }
    friend inline bool operator<=(const forward_iterator& x, const forward_iterator& y) { return (x.current <= y.current); }
    friend inline bool operator==(const forward_iterator& x, const forward_iterator& y) { return (x.current == y.current); }
    friend inline bool operator!=(const forward_iterator& x, const forward_iterator& y) { return (x.current != y.current); }
    friend inline bool operator>=(const forward_iterator& x, const forward_iterator& y) { return (x.current >= y.current); }
    friend inline bool operator> (const forward_iterator& x, const forward_iterator& y) { return (x.current >  y.current); }

    friend inline typename forward_iterator::difference_type
    operator-(const forward_iterator& x,
              const forward_iterator& y)
    {
      return (x.current.ptr - y.current.ptr);
    }

    friend inline forward_iterator
    operator+(typename forward_iterator::difference_type n,
              const forward_iterator& x)
    {
      return forward_iterator(x.current + n);
    }
  };

  template<typename iterator_type>
  using reverse_iterator = std::reverse_iterator<iterator_type>;

  template<typename input_iterator>
  typename mcal::memory::progmem::iterator_traits<input_iterator>::difference_type
  distance(input_iterator first, input_iterator last)
  {
    using local_difference_type =
      typename mcal::memory::progmem::iterator_traits<input_iterator>::difference_type;

    return local_difference_type(last - first);
  }

  template <typename container_type> inline auto cbegin (const container_type& c) -> decltype(c.cbegin())  { return c.cbegin(); }
  template <typename container_type> inline auto cend   (const container_type& c) -> decltype(c.cend())    { return c.cend(); }

  template <typename container_type> inline auto crbegin(const container_type& c) -> decltype(c.crbegin()) { return c.crbegin(); }
  template <typename container_type> inline auto crend  (const container_type& c) -> decltype(c.crend())   { return c.crend(); }

  template <typename value_type, const mcal_progmem_uintptr_t N> inline const forward_iterator<value_type, mcal_progmem_uintptr_t> cbegin (const value_type(&c_array)[N] MY_PROGMEM) { return forward_iterator<value_type, mcal_progmem_uintptr_t>((mcal_progmem_uintptr_t) MCAL_PROGMEM_ADDRESSOF(c_array[0U])); }
  template <typename value_type, const mcal_progmem_uintptr_t N> inline const forward_iterator<value_type, mcal_progmem_uintptr_t> cend   (const value_type(&c_array)[N] MY_PROGMEM) { return forward_iterator<value_type, mcal_progmem_uintptr_t>((mcal_progmem_uintptr_t) MCAL_PROGMEM_ADDRESSOF(c_array[N])); }

  template <typename value_type, const mcal_progmem_uintptr_t N> inline const reverse_iterator<forward_iterator<value_type, mcal_progmem_uintptr_t>> crbegin(const value_type(&c_array)[N] MY_PROGMEM) { return reverse_iterator<forward_iterator<value_type, mcal_progmem_uintptr_t>>((mcal_progmem_uintptr_t) MCAL_PROGMEM_ADDRESSOF(c_array[N])); }
  template <typename value_type, const mcal_progmem_uintptr_t N> inline const reverse_iterator<forward_iterator<value_type, mcal_progmem_uintptr_t>> crend  (const value_type(&c_array)[N] MY_PROGMEM) { return reverse_iterator<forward_iterator<value_type, mcal_progmem_uintptr_t>>((mcal_progmem_uintptr_t) MCAL_PROGMEM_ADDRESSOF(c_array[0U])); }

  } } } // namespace mcal::memory::progmem

#endif // MCAL_CPU_PROGMEM_ITERATOR_2019_05_04_
