///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_DYNAMIC_ARRAY_2012_05_16_H_
  #define _UTIL_DYNAMIC_ARRAY_2012_05_16_H_

  #include <memory>
  #include <iterator>
//  #include <initializer_list>
  #include <algorithm>

  namespace util
  {
    template<typename T, typename alloc = std::allocator<T> >
    class dynamic_array
    {
    public:
      // Type definitions:
      typedef alloc allocator_type;
      typedef T& reference;
      typedef const T& const_reference;
      typedef T* iterator;
      typedef const T* const_iterator;
      typedef std::size_t size_type;
      typedef std::ptrdiff_t difference_type;
      typedef T value_type;
      typedef T* pointer;
      typedef const T* const_pointer;
      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

      // Constructors:
      explicit dynamic_array(size_type count) : N(count),
                                                elems(allocator_type().allocate(N))
      {
        std::fill_n(begin(), N, T());
      }

      dynamic_array(size_type count, const T& val) : N(count),
                                                     elems(allocator_type().allocate(N))
      {
        std::fill_n(begin(), N, val);
      }

      dynamic_array(const dynamic_array& other) : N(other.size()),
                                                  elems(allocator_type().allocate(N))
      {
        std::copy(other.begin(), other.end(), begin());
      }

/*
      template<typename input_iterator>
      dynamic_array(input_iterator first, input_iterator last) : N(std::distance(first, last)),
                                                                 elems(allocator_type().allocate(N))
      {
        std::copy(first, last, begin());
      }

      dynamic_array(std::initializer_list<T> lst) : N(lst.size()),
                                                    elems(allocator_type().allocate(N))
      {
        std::copy(lst.begin(), lst.end(), begin());
      }
*/

      // Destructor:
      ~dynamic_array()
      {
        iterator first = begin();

        // Destroy the range.
        while(first != end())
        {
          allocator_type().destroy(first);
          ++first;
        }

        // Deallocate the range.
        allocator_type().deallocate(elems, N);
      }

      // Iterator members:
      iterator               begin()         { return elems; }
      iterator               end()           { return elems + N; }
      const_iterator         begin() const   { return elems; }
      const_iterator         end() const     { return elems + N; }
      const_iterator         cbegin() const  { return elems; }
      const_iterator         cend() const    { return elems + N; }
      reverse_iterator       rbegin()        { return reverse_iterator(elems + N); }
      reverse_iterator       rend()          { return reverse_iterator(elems); }
      const_reverse_iterator rbegin() const  { return const_reverse_iterator(elems + N); }
      const_reverse_iterator rend() const    { return const_reverse_iterator(elems); }
      const_reverse_iterator crbegin() const { return const_reverse_iterator(elems + N); }
      const_reverse_iterator crend() const   { return const_reverse_iterator(elems); }

      // Size and capacity:
      size_type size() const { return N; }
      size_type max_size() const { return N; }
      bool empty() const { return false; }

      // Element access members:
      reference       operator[](const size_type i)       { return elems[i]; }
      const_reference operator[](const size_type i) const { return elems[i]; }

      reference       at(const size_type i)       { return elems[i]; }
      const_reference at(const size_type i) const { return elems[i]; }

      reference       front()       { return elems[0U]; }
      const_reference front() const { return elems[0U]; }

      reference       back()        { return elems[N - 1U]; }
      const_reference back() const  { return elems[N - 1U]; }

      // Element manipulation members:
      void fill(const T& u) { std::fill_n(begin(), N, u); }
      void swap(dynamic_array<T>& u) { std::swap_ranges(u.begin(), u.end, elems); }

    private:
      // Data members:
      const size_type N;
      pointer elems;
    };
  }

#endif // _UTIL_DYNAMIC_ARRAY_2012_05_16_H_
