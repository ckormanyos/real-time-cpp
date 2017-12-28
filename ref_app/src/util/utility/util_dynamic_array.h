///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_DYNAMIC_ARRAY_2012_05_16_H_
  #define UTIL_DYNAMIC_ARRAY_2012_05_16_H_

  #include <algorithm>
  #include <initializer_list>
  #include <iterator>
  #include <memory>
  #include <utility>

  namespace util
  {
    template<typename T,
             typename alloc = std::allocator<T>>
    class dynamic_array
    {
    public:
      // Type definitions.
      typedef       alloc                                 allocator_type;
      typedef       T                                     value_type;
      typedef       T&                                    reference;
      typedef const T&                                    const_reference;
      typedef       T*                                    iterator;
      typedef const T*                                    const_iterator;
      typedef       T*                                    pointer;
      typedef const T*                                    const_pointer;
      typedef       std::size_t                           size_type;
      typedef       std::ptrdiff_t                        difference_type;
      typedef       std::reverse_iterator<iterator>       reverse_iterator;
      typedef       std::reverse_iterator<const_iterator> const_reverse_iterator;

      // Constructors.
      dynamic_array() : elem_count(0U),
                        elems     (allocator_type().allocate(1U))
      {
        elems[0U] = value_type();
      }

      dynamic_array(size_type count) : elem_count(count),
                                       elems     (allocator_type().allocate((std::max)(size_type(1U), elem_count)))
      {
        if(elem_count > size_type(0U))
        {
          std::fill_n(begin(), elem_count, value_type());
        }
        else
        {
          elems[0U] = value_type();
        }
      }

      dynamic_array(size_type count,
                    const value_type& v,
                    const allocator_type& a = allocator_type()) : elem_count(count),
                                                                  elems     (allocator_type(a).allocate((std::max)(size_type(1U), elem_count)))
      {
        if(elem_count > size_type(0U))
        {
          std::fill_n(begin(), elem_count, v);
        }
        else
        {
          elems[0U] = value_type();
        }
      }

      dynamic_array(const dynamic_array& other) : elem_count(other.size()),
                                                  elems     (allocator_type().allocate((std::max)(size_type(1U), elem_count)))
      {
        if(elem_count > size_type(0U))
        {
          std::copy(other.begin(), other.end(), begin());
        }
        else
        {
          elems[0U] = value_type();
        }
      }

      template<typename input_iterator>
      dynamic_array(input_iterator first,
                    input_iterator last,
                    const allocator_type& a = allocator_type()) : elem_count(static_cast<size_type>(std::distance(first, last))),
                                                                  elems     (allocator_type(a).allocate((std::max)(size_type(1U), elem_count)))
      {
        if(elem_count > size_type(0U))
        {
          std::copy(first, last, begin());
        }
        else
        {
          elems[0U] = value_type();
        }
      }

      dynamic_array(std::initializer_list<T> lst,
                    const allocator_type& a = allocator_type()) : elem_count(lst.size()),
                                                                  elems     (allocator_type(a).allocate((std::max)(size_type(1U), elem_count)))
      {
        if(elem_count > size_type(0U))
        {
          std::copy(lst.begin(), lst.end(), begin());
        }
        else
        {
          elems[0U] = value_type();
        }
      }

      // Destructor.
      ~dynamic_array()
      {
        // Destroy the elements and deallocate the range.
        if(elem_count > size_type(0U))
        {
          for(pointer p = elems; p != (elems + size()); ++p)
          {
            allocator_type().destroy(p);
          }

          allocator_type().deallocate(elems, elem_count);
        }
        else
        {
          allocator_type().deallocate(elems, size_type(1U));
        }
      }

      // Iterator members:
      iterator               begin  ()       { return elems; }
      iterator               end    ()       { return elems + elem_count; }
      const_iterator         begin  () const { return elems; }
      const_iterator         end    () const { return elems + elem_count; }
      const_iterator         cbegin () const { return elems; }
      const_iterator         cend   () const { return elems + elem_count; }
      reverse_iterator       rbegin ()       { return reverse_iterator(elems + elem_count); }
      reverse_iterator       rend   ()       { return reverse_iterator(elems); }
      const_reverse_iterator rbegin () const { return const_reverse_iterator(elems + elem_count); }
      const_reverse_iterator rend   () const { return const_reverse_iterator(elems); }
      const_reverse_iterator crbegin() const { return const_reverse_iterator(elems + elem_count); }
      const_reverse_iterator crend  () const { return const_reverse_iterator(elems); }

      // Size and capacity.
      size_type size    () const { return elem_count; }
      size_type max_size() const { return elem_count; }
      bool      empty   () const { return false; }

      // Element access members.
      reference       operator[](const size_type i)       { return elems[i]; }
      const_reference operator[](const size_type i) const { return elems[i]; }

      reference       front()       { return elems[0U]; }
      const_reference front() const { return elems[0U]; }

      reference       back()        { return ((elem_count > size_type(0U)) ? elems[elem_count - 1U] : elems[0U]); }
      const_reference back() const  { return ((elem_count > size_type(0U)) ? elems[elem_count - 1U] : elems[0U]); }

      reference       at(const size_type i)       { return ((i < elem_count) ? elems[i] : elems[0U]); }
      const_reference at(const size_type i) const { return ((i < elem_count) ? elems[i] : elems[0U]); }

      // Element manipulation members.
      void fill(const value_type& v) { std::fill_n(begin(), elem_count, v); }

      void swap(dynamic_array& other)
      {
        const size_type count = (std::min)(elem_count, other.size());

        std::swap_ranges(begin(), begin() + count, other.begin());

        if(count < elem_count)
        {
          std::fill(begin() + count, end(), value_type());
        }
      }

    private:
      const size_type elem_count;
      pointer         elems;

      // dynamic_array can not be copied with operator=().
      dynamic_array& operator=(const dynamic_array&);
    };

    template<typename T, typename alloc>
    bool operator==(const dynamic_array<T, alloc>& lhs, const dynamic_array<T, alloc>& rhs)
    {
      const bool sizes_are_equal = (lhs.size() == rhs.size());

      typedef typename dynamic_array<T, alloc>::size_type size_type;

      const bool size_of_left_is_zero = (lhs.size() == size_type(0U));

      return (sizes_are_equal && (size_of_left_is_zero || std::equal(lhs.begin(), lhs.end(), rhs.begin())));
    }

    template<typename T, typename alloc>
    bool operator<(const dynamic_array<T, alloc>& lhs, const dynamic_array<T, alloc>& rhs)
    {
      typedef typename dynamic_array<T, alloc>::size_type size_type;

      const bool size_of_left_is_zero = (lhs.size() == size_type(0U));

      if(size_of_left_is_zero)
      {
        const bool size_of_right_is_zero = (rhs.size() == size_type(0U));

        return (size_of_right_is_zero ? false : true);
      }
      else
      {
        if(size_of_left_is_zero)
        {
          const bool size_of_right_is_zero = (rhs.size() == size_type(0U));

          return (size_of_right_is_zero == false);
        }
        else
        {
          const size_type count = (std::min)(lhs.size(), rhs.size());

          return std::lexicographical_compare(lhs.begin(),
                                              lhs.begin() + count,
                                              rhs.begin(),
                                              rhs.begin() + count);
        }
      }
    }

    template<typename T, typename alloc>
    bool operator!=(const dynamic_array<T, alloc>& lhs, const dynamic_array<T, alloc>& rhs)
    {
      return ((lhs == rhs) == false);
    }

    template<typename T, typename alloc>
    bool operator>(const dynamic_array<T, alloc>& lhs, const dynamic_array<T, alloc>& rhs)
    {
      return (rhs < lhs);
    }

    template<typename T, typename alloc>
    bool operator>=(const dynamic_array<T, alloc>& lhs, const dynamic_array<T, alloc>& rhs)
    {
      return ((lhs < rhs) == false);
    }

    template<typename T, typename alloc>
    bool operator<=(const dynamic_array<T, alloc>& lhs, const dynamic_array<T, alloc>& rhs)
    {
      return ((rhs < lhs) == false);
    }

    template<typename T, typename alloc>
    void swap(dynamic_array<T, alloc>& x, dynamic_array<T, alloc>& y)
    {
      x.swap(y);
    }
  }

  /*
  #include <util/memory/util_ring_allocator.h>
  #include <util/utility/util_dynamic_array.h>

  typedef util::dynamic_array<int, util::ring_allocator<int>> dynamic_array_type;

  const dynamic_array_type a1( { 1, 2, 3 } );
  const dynamic_array_type a2( { 1, 2, 4 } );

  const bool b_test = (a1 < a2);
  */

#endif // UTIL_DYNAMIC_ARRAY_2012_05_16_H_
