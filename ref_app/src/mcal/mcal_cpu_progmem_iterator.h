///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_PROGMEM_ITERATOR_2019_05_04_
  #define MCAL_PROGMEM_ITERATOR_2019_05_04_

  #include <cstdint>

  #include <mcal_cpu.h>

  // Implement a specialized iterator type for read-only program memory.

  namespace mcal { namespace cpu { namespace progmem {

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
    typedef typename iterator_type::pointer           pointer;
    typedef typename iterator_type::reference         reference;
    typedef typename iterator_type::iterator_category iterator_category;
  };

  template<typename iterator_type>
  class iterator_traits<const iterator_type*>
  {
  public:
    typedef std::ptrdiff_t             difference_type;
    typedef iterator_type              value_type;
    typedef const value_type*          pointer;
    typedef const value_type           reference;
    typedef random_access_iterator_tag iterator_category;
  };

  template<typename IteratorCategoryType,
           typename IteratorValueType,
           typename IteratorDifferenceType = std::ptrdiff_t,
           typename IteratorPointerType    = IteratorValueType*,
           typename IteratorReferenceType  = IteratorValueType>
  class iterator
  {
  public:
    using iterator_category = IteratorCategoryType;
    using value_type        = IteratorValueType;
    using difference_type   = IteratorDifferenceType;
    using pointer           = IteratorPointerType;
    using reference         = IteratorReferenceType;

    iterator() = default;
    iterator(const iterator&) = default;
    ~iterator() = default;
    iterator& operator=(const iterator&) = default;
  };

  template <typename iterator_type>
  class forward_iterator
    : public iterator<typename iterator_traits<iterator_type>::iterator_category,
                      typename iterator_traits<iterator_type>::value_type,
                      std::size_t,
                      typename iterator_traits<iterator_type>::pointer,
                      typename iterator_traits<iterator_type>::reference>
  {
  private:
    using base_class_type =
      iterator<typename iterator_traits<iterator_type>::iterator_category,
               typename iterator_traits<iterator_type>::value_type,
               std::size_t,
               typename iterator_traits<iterator_type>::pointer,
               typename iterator_traits<iterator_type>::reference>;

  public:
    using value_type        = typename base_class_type::value_type;
    using difference_type   = typename base_class_type::difference_type;
    using pointer           = typename base_class_type::pointer;
    using reference         = typename base_class_type::reference;
    using iterator_category = typename base_class_type::iterator_category;

    explicit forward_iterator(const iterator_type x = iterator_type())
      : current(x) { }

    template<typename OtherIteratorType>
    forward_iterator(const forward_iterator<OtherIteratorType>& other)
      : current(other.current) { }

    ~forward_iterator() = default;

    forward_iterator& operator=(forward_iterator& other)
    {
      if(this != &other)
      {
        current = other.current;
      }

      return *this;
    }

    reference operator*() const
    {
      return mcal::cpu::read_program_memory(current);
    }

    const reference operator[](difference_type n) const
    {
      return mcal::cpu::read_program_memory(&current[n]);
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
    iterator_type current;

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
      return (x.current - y.current);
    }

    friend inline forward_iterator
    operator+(typename forward_iterator::difference_type n,
              const forward_iterator& x)
    {
      return forward_iterator(x.current + n);
    }
  };

  template <typename iterator_type>
  class reverse_iterator
    : public iterator<typename iterator_traits<iterator_type>::iterator_category,
                      typename iterator_traits<iterator_type>::value_type,
                      typename iterator_traits<iterator_type>::difference_type,
                      typename iterator_traits<iterator_type>::pointer,
                      typename iterator_traits<iterator_type>::reference>
  {
  public:
    typedef typename iterator_traits<iterator_type>::value_type        value_type;
    typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
    typedef typename iterator_traits<iterator_type>::pointer           pointer;
    typedef typename iterator_traits<iterator_type>::reference         reference;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

    explicit reverse_iterator(iterator_type x = iterator_type())
      : current(x) { }

    template<typename OtherIteratorType>
    reverse_iterator(const reverse_iterator<OtherIteratorType>& other)
      : current(other.current) { }

    ~reverse_iterator() = default;

    reverse_iterator& operator=(reverse_iterator& other)
    {
      if(this != &other)
      {
        current = other.current;
      }

      return *this;
    }

    reference operator*() const { iterator_type tmp = current; return *--tmp; }
    pointer operator->() const  { return &(operator*()); }

    reverse_iterator& operator++() { --current; return *this; }
    reverse_iterator& operator--() { ++current; return *this; }

    reverse_iterator operator++(int) { reverse_iterator tmp = *this; --current; return tmp; }
    reverse_iterator operator--(int) { reverse_iterator tmp = *this; ++current; return tmp; }

    reverse_iterator operator+(typename reverse_iterator<iterator_type>::difference_type n) const { return reverse_iterator(current - n); }
    reverse_iterator operator-(typename reverse_iterator<iterator_type>::difference_type n) const { return reverse_iterator(current + n); }

    reverse_iterator& operator+=(typename reverse_iterator<iterator_type>::difference_type n) { current -= n; return *this; }
    reverse_iterator& operator-=(typename reverse_iterator<iterator_type>::difference_type n) { current += n; return *this; }

    reference operator[](typename reverse_iterator<iterator_type>::difference_type n) const { return current[-n - 1]; }

  private:
    iterator_type current;

    friend inline bool operator< (const reverse_iterator& x, const reverse_iterator& y) { return (x.current  > y.current); }
    friend inline bool operator<=(const reverse_iterator& x, const reverse_iterator& y) { return (x.current >= y.current); }
    friend inline bool operator==(const reverse_iterator& x, const reverse_iterator& y) { return (x.current == y.current); }
    friend inline bool operator!=(const reverse_iterator& x, const reverse_iterator& y) { return (x.current != y.current); }
    friend inline bool operator>=(const reverse_iterator& x, const reverse_iterator& y) { return (x.current <= y.current); }
    friend inline bool operator> (const reverse_iterator& x, const reverse_iterator& y) { return (x.current <  y.current); }

    friend inline typename reverse_iterator::difference_type
    operator-(const reverse_iterator& x,
              const reverse_iterator& y)
    {
      return (y.current - x.current);
    }

    friend inline reverse_iterator
    operator+(typename reverse_iterator::difference_type n,
              const reverse_iterator& x)
    {
      return reverse_iterator(x.current - n);
    }
  };

  template<typename input_iterator>
  typename iterator_traits<input_iterator>::difference_type distance(input_iterator first, input_iterator last)
  {
    typedef typename iterator_traits<input_iterator>::difference_type distance_type;

    distance_type the_distance(0);

    while(first != last)
    {
      ++the_distance;

      ++first;
    }

    return the_distance;
  }

  // See ISO/IEC 14882:2011, near the end of Section 24.3.
  template <typename container_type> inline auto  begin (const container_type& c) -> decltype(c.begin())   { return c.begin(); }
  template <typename container_type> inline auto cbegin (const container_type& c) -> decltype(c.cbegin())  { return c.cbegin(); }
  template <typename container_type> inline auto  end   (const container_type& c) -> decltype(c.end())     { return c.end(); }
  template <typename container_type> inline auto cend   (const container_type& c) -> decltype(c.cend())    { return c.cend(); }

  template <typename container_type> inline auto  rbegin(const container_type& c) -> decltype(c.rbegin())  { return c.rbegin(); }
  template <typename container_type> inline auto crbegin(const container_type& c) -> decltype(c.crbegin()) { return c.crbegin(); }
  template <typename container_type> inline auto  rend  (const container_type& c) -> decltype(c.rend())    { return c.rend(); }
  template <typename container_type> inline auto crend  (const container_type& c) -> decltype(c.crend())   { return c.crend(); }

  template <typename value_type, size_t N> inline const mcal::cpu::progmem::forward_iterator<const value_type*> cbegin (value_type(&c_array)[N] MY_PROGMEM) { return mcal::cpu::progmem::forward_iterator<const value_type*>(&c_array[0U]); }
  template <typename value_type, size_t N> inline const mcal::cpu::progmem::forward_iterator<const value_type*> cend   (value_type(&c_array)[N] MY_PROGMEM) { return mcal::cpu::progmem::forward_iterator<const value_type*>(&c_array[N]); }

  template <typename value_type, size_t N> inline const mcal::cpu::progmem::reverse_iterator<const value_type*> crbegin(value_type(&c_array)[N] MY_PROGMEM) { return mcal::cpu::progmem::reverse_iterator<const value_type*>(&c_array[N]); }
  template <typename value_type, size_t N> inline const mcal::cpu::progmem::reverse_iterator<const value_type*> crend  (value_type(&c_array)[N] MY_PROGMEM) { return mcal::cpu::progmem::reverse_iterator<const value_type*>(&c_array[0U]); }

  } } } // namespace mcal::cpu::progmem

#endif // MCAL_CPU_PROGMEM_ITERATOR_2019_05_04_
