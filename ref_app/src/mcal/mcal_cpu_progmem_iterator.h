///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_PROGMEM_ITERATOR_2019_05_04_
  #define MCAL_PROGMEM_ITERATOR_2019_05_04_

  #include <cstddef>

  #include <mcal_cpu.h>

  // Implement specialized iterator types for read-only program memory.

  namespace mcal { namespace cpu { namespace progmem {

  template<typename T>
  struct pointer_wrapper
  {
    using value_type = T;
    using pointer    = const value_type*;

    explicit pointer_wrapper(pointer x = nullptr) : ptr(x) { }

    template<typename OtherPointerType>
    constexpr pointer_wrapper(const pointer_wrapper<OtherPointerType>& other)
      : ptr(static_cast<pointer>(other.ptr)) { }

    ~pointer_wrapper() = default;

    pointer_wrapper& operator=(const pointer_wrapper& other)
    {
      if(this != &other)
      {
        ptr = other.ptr;
      }

      return *this;
    }

    constexpr value_type operator*() const
    {
      return get();
    }

    constexpr value_type get() const
    {
      return mcal::cpu::read_program_memory(ptr);
    }

    pointer_wrapper& operator++() { ++ptr; return *this; }
    pointer_wrapper& operator--() { --ptr; return *this; }

    pointer_wrapper operator++(int) { pointer_wrapper tmp = *this; ++ptr; return tmp; }
    pointer_wrapper operator--(int) { pointer_wrapper tmp = *this; --ptr; return tmp; }

    pointer_wrapper operator+(std::size_t n) const { return pointer_wrapper(ptr + n); }
    pointer_wrapper operator-(std::size_t n) const { return pointer_wrapper(ptr - n); }

    pointer_wrapper& operator+=(std::size_t n) { ptr += n; return *this; }
    pointer_wrapper& operator-=(std::size_t n) { ptr -= n; return *this; }

    pointer ptr;
  };

  class input_iterator_tag                                             { };
  class output_iterator_tag                                            { };
  class forward_iterator_tag       : public input_iterator_tag         { };
  class bidirectional_iterator_tag : public forward_iterator_tag       { };
  class random_access_iterator_tag : public bidirectional_iterator_tag { };

  template<typename iterator_type>
  class iterator_traits
  {
  public:
    typedef typename iterator_type::difference_type   difference_type;
    typedef typename iterator_type::value_type        value_type;
    typedef typename iterator_type::const_pointer     const_pointer;
    typedef typename iterator_type::const_reference   const_reference;
    typedef typename iterator_type::iterator_category iterator_category;
  };

  template<typename T>
  class iterator_traits<const T*>
  {
  public:
    typedef std::size_t                 difference_type;
    typedef T                           value_type;
    typedef pointer_wrapper<value_type> const_pointer;
    typedef value_type                  const_reference;
    typedef random_access_iterator_tag  iterator_category;
  };

  template<typename IteratorCategoryType,
           typename IteratorValueType,
           typename IteratorDifferenceType = std::size_t,
           typename IteratorPointerType    = pointer_wrapper<IteratorValueType>,
           typename IteratorReferenceType  = IteratorValueType>
  struct iterator
  {
    using iterator_category = IteratorCategoryType;
    using value_type        = IteratorValueType;
    using difference_type   = IteratorDifferenceType;
    using pointer           = IteratorPointerType;
    using reference         = IteratorReferenceType;
  };

  template<typename T>
  class forward_iterator
    : public mcal::cpu::progmem::iterator<std::random_access_iterator_tag,
                                          T,
                                          std::size_t,
                                          pointer_wrapper<T>,
                                          T>
  {
  private:
    using base_class_type =
      mcal::cpu::progmem::iterator<std::random_access_iterator_tag,
                                   T,
                                   std::size_t,
                                   pointer_wrapper<T>,
                                   T>;

  public:
    using value_type        = typename base_class_type::value_type;
    using difference_type   = typename base_class_type::difference_type;
    using pointer           = typename base_class_type::pointer;
    using reference         = typename base_class_type::reference;
    using iterator_category = typename base_class_type::iterator_category;

    explicit constexpr forward_iterator(typename pointer::pointer x = nullptr)
      : current(x) { }

    template<typename OtherIteratorType>
    constexpr forward_iterator(const forward_iterator<OtherIteratorType>& other)
      : current(static_cast<typename pointer::pointer>(other.current)) { }

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
      return *pointer(current.ptr + n);
    }

    forward_iterator& operator++() { ++current; return *this; }
    forward_iterator& operator--() { --current; return *this; }

    forward_iterator operator++(int) { forward_iterator tmp = *this; ++current; return tmp; }
    forward_iterator operator--(int) { forward_iterator tmp = *this; --current; return tmp; }

    forward_iterator operator+(difference_type n) const { return forward_iterator(current.ptr + n); }
    forward_iterator operator-(difference_type n) const { return forward_iterator(current.ptr - n); }

    forward_iterator& operator+=(difference_type n) { current += n; return *this; }
    forward_iterator& operator-=(difference_type n) { current -= n; return *this; }

  private:
    pointer current;

    friend inline bool operator< (const forward_iterator& x, const forward_iterator& y) { return (x.current.ptr <  y.current.ptr); }
    friend inline bool operator<=(const forward_iterator& x, const forward_iterator& y) { return (x.current.ptr <= y.current.ptr); }
    friend inline bool operator==(const forward_iterator& x, const forward_iterator& y) { return (x.current.ptr == y.current.ptr); }
    friend inline bool operator!=(const forward_iterator& x, const forward_iterator& y) { return (x.current.ptr != y.current.ptr); }
    friend inline bool operator>=(const forward_iterator& x, const forward_iterator& y) { return (x.current.ptr >= y.current.ptr); }
    friend inline bool operator> (const forward_iterator& x, const forward_iterator& y) { return (x.current.ptr >  y.current.ptr); }

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
  typename mcal::cpu::progmem::iterator_traits<input_iterator>::difference_type
  distance(input_iterator first, input_iterator last)
  {
    using distance_type =
      typename mcal::cpu::progmem::iterator_traits<input_iterator>::difference_type;

    const distance_type the_distance(last - first);

    return the_distance;
  }

  template <typename container_type> inline auto cbegin (const container_type& c) -> decltype(c.cbegin())  { return c.cbegin(); }
  template <typename container_type> inline auto cend   (const container_type& c) -> decltype(c.cend())    { return c.cend(); }

  template <typename container_type> inline auto crbegin(const container_type& c) -> decltype(c.crbegin()) { return c.crbegin(); }
  template <typename container_type> inline auto crend  (const container_type& c) -> decltype(c.crend())   { return c.crend(); }

  template <typename value_type, std::size_t N> inline const mcal::cpu::progmem::forward_iterator<value_type> cbegin (const value_type(&c_array)[N] MY_PROGMEM) { return mcal::cpu::progmem::forward_iterator<value_type>(&c_array[0U]); }
  template <typename value_type, std::size_t N> inline const mcal::cpu::progmem::forward_iterator<value_type> cend   (const value_type(&c_array)[N] MY_PROGMEM) { return mcal::cpu::progmem::forward_iterator<value_type>(&c_array[N]); }

  template <typename value_type, std::size_t N> inline const mcal::cpu::progmem::reverse_iterator<mcal::cpu::progmem::forward_iterator<value_type>> crbegin(const value_type(&c_array)[N] MY_PROGMEM) { return mcal::cpu::progmem::reverse_iterator<mcal::cpu::progmem::forward_iterator<value_type>>(&c_array[N]); }
  template <typename value_type, std::size_t N> inline const mcal::cpu::progmem::reverse_iterator<mcal::cpu::progmem::forward_iterator<value_type>> crend  (const value_type(&c_array)[N] MY_PROGMEM) { return mcal::cpu::progmem::reverse_iterator<mcal::cpu::progmem::forward_iterator<value_type>>(&c_array[0U]); }

  } } } // namespace mcal::cpu::progmem

#endif // MCAL_CPU_PROGMEM_ITERATOR_2019_05_04_
