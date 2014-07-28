///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _ARRAY_IMPL_2010_02_23_H_
  #define _ARRAY_IMPL_2010_02_23_H_

  #include "xalgorithm_impl.h"
  #include "iterator_impl.h"

  // Implement most of std::array for compilers that do not yet support it.
  // See ISO/IEC 14882:2011 Chapter 23.3.2.

  namespace std
  {
    template<typename T, const std::size_t N>
    class array
    {
    public:
      // Standard container-local type definitions.
      typedef std::size_t                           size_type;
      typedef std::ptrdiff_t                        difference_type;
      typedef T                                     value_type;
      typedef T*                                    pointer;
      typedef const T*                              const_pointer;
      typedef T&                                    reference;
      typedef const T&                              const_reference;
      typedef pointer                               iterator;
      typedef const_pointer                         const_iterator;
      typedef std::reverse_iterator<iterator>       reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

      value_type elems[N];

      static constexpr size_type static_size = N;

      iterator begin() { return elems; }
      iterator end  () { return elems + N; }

      const_iterator begin() const { return elems; }
      const_iterator end  () const { return elems + N; }

      const_iterator cbegin() const { return elems; }
      const_iterator cend  () const { return elems + N; }

      reverse_iterator rbegin() { return reverse_iterator(elems + N); }
      reverse_iterator rend  () { return reverse_iterator(elems); }

      const_reverse_iterator rbegin() const { return const_reverse_iterator(elems + N); }
      const_reverse_iterator rend  () const { return const_reverse_iterator(elems); }

      const_reverse_iterator crbegin() const { return const_reverse_iterator(elems + N); }
      const_reverse_iterator crend  () const { return const_reverse_iterator(elems); }

      reference operator[](const size_type i)             { return elems[i]; }
      const_reference operator[](const size_type i) const { return elems[i]; }

      reference at(const size_type i)             { rangecheck(i); return elems[i]; }
      const_reference at(const size_type i) const { rangecheck(i); return elems[i]; }

      reference front()             { return elems[0U]; }
      const_reference front() const { return elems[0U]; }

      reference back()             { return elems[N - 1U]; }
      const_reference back() const { return elems[N - 1U]; }

      static size_type size()     { return N; }
      static bool empty()         { return false; }
      static size_type max_size() { return N; }

      template<typename T2>
      void swap(array<T2, N>& y)
      {
        xalgorithm::xswap_ranges(begin(), end(), y.begin());
      }

      const_pointer data() const { return elems; }
      pointer data()             { return elems; }

      pointer c_array() { return elems; }

      template<typename T2>
      array& operator=(const array<T2, N>& y)
      {
        xalgorithm::xcopy(y.begin(), y.end(), begin());
        return *this;
      }

      void assign(const value_type& value)
      {
        xalgorithm::xfill_n(elems, N, value);
      }

      void fill(const value_type& value)
      {
        xalgorithm::xfill_n(elems, N, value);
      }

    private:
      static void rangecheck(const size_type) { }
    };
  }

#endif // _ARRAY_IMPL_2010_02_23_H_
