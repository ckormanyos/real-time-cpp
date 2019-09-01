///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_PROGMEM_ITERATOR_2019_05_04_
  #define MCAL_PROGMEM_ITERATOR_2019_05_04_

  #include <mcal_memory/mcal_memory_progmem_access.h>

  // Implement specialized iterator types for read-only program memory.

  namespace mcal { namespace memory { namespace progmem {

  template<typename ValueType,
           typename AddressType>
  class progmem_ptr
  {
  private:
    using value_type   = ValueType;
    using address_type = AddressType;

  public:
    progmem_ptr() { }

    explicit constexpr progmem_ptr(const address_type& addr) : my_address(addr) { }

    constexpr progmem_ptr(progmem_ptr& x) : my_address(x.my_address) { }

    template<typename OtherValueType, typename OtherAddressType>
    constexpr progmem_ptr(const progmem_ptr<OtherValueType, OtherAddressType>& other)
      : my_address(other.my_address) { }

    ~progmem_ptr() = default;

    progmem_ptr& operator=(const progmem_ptr& other)
    {
      if(this != &other)
      {
        my_address = other.my_address;
      }

      return *this;
    }

    constexpr value_type operator*() const
    {
      return mcal::memory::progmem::read<value_type>(my_address);
    }

    progmem_ptr& operator++() { my_address += sizeof(value_type); return *this; }
    progmem_ptr& operator--() { my_address -= sizeof(value_type); return *this; }

    progmem_ptr operator++(int) { progmem_ptr tmp = *this; my_address += sizeof(value_type); return tmp; }
    progmem_ptr operator--(int) { progmem_ptr tmp = *this; my_address -= sizeof(value_type); return tmp; }

    progmem_ptr operator+(address_type n) const { return progmem_ptr(my_address + (n * sizeof(value_type))); }
    progmem_ptr operator-(address_type n) const { return progmem_ptr(my_address - (n * sizeof(value_type))); }

    progmem_ptr& operator+=(address_type n) { my_address += (n * sizeof(value_type)); return *this; }
    progmem_ptr& operator-=(address_type n) { my_address -= (n * sizeof(value_type)); return *this; }

  private:
    address_type my_address;

    friend inline address_type operator-(const progmem_ptr& x, const progmem_ptr& y)
    {
      return (x.my_address - y.my_address) / sizeof(value_type);
    }

    friend inline progmem_ptr operator+(address_type n, const progmem_ptr& x)
    {
      return progmem_ptr(x.my_address + (n * sizeof(value_type)));
    }

    friend inline bool operator< (const progmem_ptr& x, const progmem_ptr& y) { return (x.my_address <  y.my_address); }
    friend inline bool operator<=(const progmem_ptr& x, const progmem_ptr& y) { return (x.my_address <= y.my_address); }
    friend inline bool operator==(const progmem_ptr& x, const progmem_ptr& y) { return (x.my_address == y.my_address); }
    friend inline bool operator!=(const progmem_ptr& x, const progmem_ptr& y) { return (x.my_address != y.my_address); }
    friend inline bool operator>=(const progmem_ptr& x, const progmem_ptr& y) { return (x.my_address >= y.my_address); }
    friend inline bool operator> (const progmem_ptr& x, const progmem_ptr& y) { return (x.my_address >  y.my_address); }
  };

  template<typename ValueType,
           typename AddressType>
  class pointer_wrapper
  {
  public:
    using value_type   = ValueType;
    using address_type = AddressType;

    using pointer = progmem_ptr<value_type, address_type>;

    pointer_wrapper() { }

    explicit constexpr pointer_wrapper(const address_type& addr) : my_ptr(addr) { }

    constexpr pointer_wrapper(const pointer& ptr) : my_ptr(ptr) { }

    constexpr pointer_wrapper(const pointer_wrapper& x) : my_ptr(x.my_ptr) { }

    template<typename OtherPointerType,
             typename OtherAddressType>
    constexpr pointer_wrapper(const pointer_wrapper<OtherPointerType, OtherAddressType>& other)
      : my_ptr(other.my_ptr) { }

    ~pointer_wrapper() = default;

    pointer_wrapper& operator=(const pointer_wrapper& other)
    {
      if(this != &other)
      {
        my_ptr = other.my_ptr;
      }

      return *this;
    }

    constexpr value_type operator*() const
    {
      return *my_ptr;
    }

    pointer_wrapper& operator++() { ++my_ptr; return *this; }
    pointer_wrapper& operator--() { ++my_ptr; return *this; }

    pointer_wrapper operator++(int) { pointer_wrapper tmp = *this; ++my_ptr; return tmp; }
    pointer_wrapper operator--(int) { pointer_wrapper tmp = *this; ++my_ptr; return tmp; }

    pointer_wrapper operator+(address_type n) const { return pointer_wrapper(my_ptr + n); }
    pointer_wrapper operator-(address_type n) const { return pointer_wrapper(my_ptr - n); }

    pointer_wrapper& operator+=(address_type n) { my_ptr += n; return *this; }
    pointer_wrapper& operator-=(address_type n) { my_ptr -= n; return *this; }

  private:
    pointer my_ptr;

    friend inline address_type operator-(const pointer_wrapper& x,
                                         const pointer_wrapper& y)
    {
      return (x.my_ptr - y.my_ptr);
    }

    friend inline pointer_wrapper operator+(address_type n,
                                            const pointer_wrapper& x)
    {
      return progmem_ptr(x.my_ptr + n);
    }

    friend inline bool operator< (const pointer_wrapper& x, const pointer_wrapper& y) { return (x.my_ptr <  y.my_ptr); }
    friend inline bool operator<=(const pointer_wrapper& x, const pointer_wrapper& y) { return (x.my_ptr <= y.my_ptr); }
    friend inline bool operator==(const pointer_wrapper& x, const pointer_wrapper& y) { return (x.my_ptr == y.my_ptr); }
    friend inline bool operator!=(const pointer_wrapper& x, const pointer_wrapper& y) { return (x.my_ptr != y.my_ptr); }
    friend inline bool operator>=(const pointer_wrapper& x, const pointer_wrapper& y) { return (x.my_ptr >= y.my_ptr); }
    friend inline bool operator> (const pointer_wrapper& x, const pointer_wrapper& y) { return (x.my_ptr >  y.my_ptr); }
  };

  struct input_iterator_tag                                             { };
  struct output_iterator_tag                                            { };
  struct forward_iterator_tag       : public input_iterator_tag         { };
  struct bidirectional_iterator_tag : public forward_iterator_tag       { };
  struct random_access_iterator_tag : public bidirectional_iterator_tag { };

  template<typename iterator_type>
  struct iterator_traits
  {
    typedef typename iterator_type::difference_type   difference_type;
    typedef typename iterator_type::value_type        value_type;
    typedef typename iterator_type::const_pointer     const_pointer;
    typedef typename iterator_type::const_reference   const_reference;
    typedef typename iterator_type::iterator_category iterator_category;
  };

  template<typename ValueType,
           typename AddressType>
  struct iterator_traits<const pointer_wrapper<ValueType, AddressType>>
  {
    using difference_type   = std::size_t;
    using address_type      = AddressType;
    using value_type        = ValueType;
    using const_pointer     = pointer_wrapper<value_type, address_type>;
    using const_reference   = value_type;
    using iterator_category = random_access_iterator_tag;
  };

  template<typename IteratorCategoryType,
           typename IteratorValueType,
           typename IteratorDifferenceType = std::size_t,
           typename address_type           = std::uintptr_t,
           typename IteratorPointerType    = pointer_wrapper<IteratorValueType, address_type>,
           typename IteratorReferenceType  = IteratorValueType>
  struct iterator
  {
    using iterator_category = IteratorCategoryType;
    using value_type        = IteratorValueType;
    using difference_type   = IteratorDifferenceType;
    using pointer           = pointer_wrapper<IteratorValueType, address_type>;
    using reference         = IteratorReferenceType;
  };

  template<typename ValueType,
           typename AddressType>
  class forward_iterator
    : public mcal::memory::progmem::iterator<std::random_access_iterator_tag,
                                             ValueType,
                                             std::size_t,
                                             AddressType,
                                             pointer_wrapper<ValueType, AddressType>,
                                             ValueType>
  {
  private:
    using base_class_type =
      mcal::memory::progmem::iterator<std::random_access_iterator_tag,
                                      ValueType,
                                      std::size_t,
                                      AddressType,
                                      pointer_wrapper<ValueType, AddressType>,
                                      ValueType>;

  public:
    using value_type        = typename base_class_type::value_type;
    using difference_type   = typename base_class_type::difference_type;
    using pointer           = typename base_class_type::pointer;
    using reference         = typename base_class_type::reference;
    using iterator_category = typename base_class_type::iterator_category;

    forward_iterator() { }

    explicit constexpr forward_iterator(const AddressType& addr) : current(addr) { }

    constexpr forward_iterator(const pointer& x) : current(x) { }

    template<typename OtherIteratorType, typename OtherValueType>
    constexpr forward_iterator(const forward_iterator<OtherIteratorType, OtherValueType>& other)
      : current(static_cast<pointer>(other.current)) { }

    ~forward_iterator() = default;

    forward_iterator& operator=(forward_iterator& other)
    {
      if(this != &other)
      {
        current = other.current;
      }

      return *this;
    }

    constexpr reference operator*() const
    {
      return operator[](0U);
    }

    constexpr reference operator[](difference_type n) const
    {
      return *pointer(current + n);
    }

    forward_iterator& operator++() { ++current; return *this; }
    forward_iterator& operator--() { --current; return *this; }

    forward_iterator operator++(int) { forward_iterator tmp = *this; ++current; return tmp; }
    forward_iterator operator--(int) { forward_iterator tmp = *this; --current; return tmp; }

    forward_iterator operator+(difference_type n) const { return forward_iterator(current + n); }
    forward_iterator operator-(difference_type n) const { return forward_iterator(current - n); }

    forward_iterator& operator+=(difference_type n) { current += n; return *this; }
    forward_iterator& operator-=(difference_type n) { current -= n; return *this; }

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

  template <typename value_type, std::size_t N, typename address_type> inline const mcal::memory::progmem::forward_iterator<value_type, address_type> cbegin (const value_type(&c_array)[N] MY_PROGMEM) { return mcal::memory::progmem::forward_iterator<value_type, address_type>((address_type) &c_array[0U]); }
  template <typename value_type, std::size_t N, typename address_type> inline const mcal::memory::progmem::forward_iterator<value_type, address_type> cend   (const value_type(&c_array)[N] MY_PROGMEM) { return mcal::memory::progmem::forward_iterator<value_type, address_type>((address_type) &c_array[N]); }

  template <typename value_type, std::size_t N, typename address_type> inline const mcal::memory::progmem::reverse_iterator<mcal::memory::progmem::forward_iterator<value_type, address_type>> crbegin(const value_type(&c_array)[N] MY_PROGMEM) { return mcal::memory::progmem::reverse_iterator<mcal::memory::progmem::forward_iterator<value_type, address_type>>((address_type) &c_array[N]); }
  template <typename value_type, std::size_t N, typename address_type> inline const mcal::memory::progmem::reverse_iterator<mcal::memory::progmem::forward_iterator<value_type, address_type>> crend  (const value_type(&c_array)[N] MY_PROGMEM) { return mcal::memory::progmem::reverse_iterator<mcal::memory::progmem::forward_iterator<value_type, address_type>>((address_type) &c_array[0U]); }

  } } } // namespace mcal::memory::progmem

#endif // MCAL_CPU_PROGMEM_ITERATOR_2019_05_04_
