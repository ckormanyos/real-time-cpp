///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _ITERATOR_IMPL_2010_02_23_H_
  #define _ITERATOR_IMPL_2010_02_23_H_

  #include "xiterator_impl.h"

  // Implement some of std::iterator for compilers that do not yet support it.

  namespace std
  {
    typedef xiterator::xinput_iterator_tag         input_iterator_tag;
    typedef xiterator::xoutput_iterator_tag        output_iterator_tag;
    typedef xiterator::xforward_iterator_tag       forward_iterator_tag;
    typedef xiterator::xbidirectional_iterator_tag bidirectional_iterator_tag;
    typedef xiterator::xrandom_access_iterator_tag random_access_iterator_tag;

    template<typename iterator_type>
    class iterator_traits : public xiterator::xiterator_traits<iterator_type> { };

    template<typename my_category,
             typename my_value_type,
             typename my_difference_type = std::ptrdiff_t,
             typename my_pointer_type    = my_value_type*,
             typename my_reference_type  = my_value_type&>
    struct iterator
    {
      typedef my_category        iterator_category;
      typedef my_value_type      value_type;
      typedef my_difference_type difference_type;
      typedef my_pointer_type    pointer;
      typedef my_reference_type  reference;

      iterator() { }
    };

    template <typename iterator_type>
    class reverse_iterator : public iterator<typename iterator_traits<iterator_type>::iterator_category,
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

      reverse_iterator() { }

      explicit reverse_iterator(iterator_type x) : current(x) { }

      template<class Other>
      reverse_iterator(const reverse_iterator<Other>& u) : current(u.current) { }

      iterator_type base() const { return current; }

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

    protected:
      iterator_type current;

      friend inline bool operator< (const reverse_iterator& x, const reverse_iterator& y) { return (x.current  > y.current); }
      friend inline bool operator<=(const reverse_iterator& x, const reverse_iterator& y) { return (x.current >= y.current); }
      friend inline bool operator==(const reverse_iterator& x, const reverse_iterator& y) { return (x.current == y.current); }
      friend inline bool operator!=(const reverse_iterator& x, const reverse_iterator& y) { return (x.current != y.current); }
      friend inline bool operator>=(const reverse_iterator& x, const reverse_iterator& y) { return (x.current <= y.current); }
      friend inline bool operator> (const reverse_iterator& x, const reverse_iterator& y) { return (x.current <  y.current); }

      friend inline typename reverse_iterator::difference_type operator-(const reverse_iterator& x,
                                                                         const reverse_iterator& y)
      {
        return (y.current - x.current);
      }

      friend inline reverse_iterator operator+(typename reverse_iterator::difference_type n,
                                               const reverse_iterator& x)
      {
        return reverse_iterator(x.current - n);
      }
    };

    template<class input_iterator>
    typename iterator_traits<input_iterator>::difference_type distance(input_iterator first, input_iterator last)
    {
      typedef typename iterator_traits<input_iterator>::difference_type distance_type;

      distance_type the_distance = static_cast<distance_type>(0);

      while(first != last)
      {
        ++the_distance;

        ++first;
      }

      return the_distance;
    }

    // See ISO/IEC 14882:2011, near the end of Section 24.3.
    template <class C> inline auto  begin(      C& c) -> decltype(c.begin())  { return c.begin(); }
    template <class C> inline auto  begin(const C& c) -> decltype(c.begin())  { return c.begin(); }
    template <class C> inline auto cbegin(const C& c) -> decltype(c.cbegin()) { return c.cbegin(); }
    template <class C> inline auto  end  (      C& c) -> decltype(c.end())    { return c.end(); }
    template <class C> inline auto  end  (const C& c) -> decltype(c.end())    { return c.end(); }
    template <class C> inline auto cend  (const C& c) -> decltype(c.cend())   { return c.cend(); }
    template <class T, size_t N> inline T* begin(T (&c_array)[N]) { return &c_array[0U]; }
    template <class T, size_t N> inline T* end  (T (&c_array)[N]) { return &c_array[N]; }
  }

#endif // _ITERATOR_IMPL_2010_02_23_H_
