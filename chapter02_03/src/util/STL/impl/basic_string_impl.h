///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _BASIC_STRING_IMPL_2010_02_23_H_
  #define _BASIC_STRING_IMPL_2010_02_23_H_

  #if defined(__GNUC__)
  #pragma GCC system_header
  #endif

  #include "xallocator_impl.h"
  #include "xalgorithm_impl.h"
  #include "memory_impl.h"
  #include "char_traits_impl.h"
  #include "iterator_impl.h"
  #include "initializer_list_impl.h"

  // Implement some of std::basic_string for compilers that do not yet support it.

  namespace std
  {
    template<typename T,
             typename traits_type = std::char_traits<T>,
             typename alloc = std::allocator<T> >
    class basic_string
    {
    public:
      typedef alloc                                    allocator_type;
      typedef std::size_t                              size_type;
      typedef std::ptrdiff_t                           difference_type;
      typedef T                                        value_type;
      typedef typename allocator_type::pointer         pointer;
      typedef typename allocator_type::const_pointer   const_pointer;
      typedef typename allocator_type::reference       reference;
      typedef typename allocator_type::const_reference const_reference;
      typedef pointer                                  iterator;
      typedef const_pointer                            const_iterator;
      typedef std::reverse_iterator<iterator>          reverse_iterator;
      typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

      static constexpr size_type npos = static_cast<size_type>(-1);

      basic_string() : my_first(allocator_type().allocate(1U)),
                       my_last (my_first)
      {
        *my_last = static_cast<value_type>(0);
      }

      explicit basic_string(size_type count) : my_first(allocator_type().allocate(count + 1U)),
                                               my_last (my_first + count)
      {
        xalgorithm::xfill(my_first, my_last, value_type());
        *my_last = static_cast<value_type>(0);
      }

      basic_string(size_type count, const T& value) : my_first(allocator_type().allocate(count + 1U)),
                                                      my_last (my_first + count)
      {
        xalgorithm::xfill(my_first, my_last, value);
        *my_last = static_cast<value_type>(0);
      }

      basic_string(const_pointer p)
      {
        const size_type count = traits_type::length(p);
        my_first = allocator_type().allocate(count + 1U);
        my_last = my_first + count;
        xalgorithm::xcopy(p, p + count, my_first);
        *my_last = static_cast<value_type>(0);
      }

      basic_string(const basic_string& str)
      {
        const size_type count = str.length();
        my_first = allocator_type().allocate(count + 1U);
        my_last = my_first + count;
        xalgorithm::xcopy(str.begin(), str.end(), my_first);
        *my_last = static_cast<value_type>(0);
      }

      basic_string(std::initializer_list<T> lst)
      {
        const size_type count = lst.size();
        my_first = allocator_type().allocate(count + 1U);
        my_last = my_first + count;
        xalgorithm::xcopy(lst.begin(), lst.end(), my_first);
        *my_last = static_cast<value_type>(0);
      }

      basic_string(size_type count,
                   const T& value,
                   const allocator_type& a) : my_first((const_cast<allocator_type&>(a)).allocate(count + 1U)),
                                              my_last (my_first + count)
      {
        xalgorithm::xfill(my_first, my_last, value);
        *my_last = static_cast<value_type>(0);
      }

      template<class input_iterator>
      basic_string(input_iterator first,
                   input_iterator last,
                   const allocator_type& a = allocator_type())
      {
        const size_type count static_cast<size_type>(std::distance(first, last));
        my_first = (const_cast<allocator_type&>(a)).allocate(sz + 1U);
        my_last  = my_first + sz;
        xalgorithm::xcopy(first, last, my_first);
        *my_last = static_cast<value_type>(0);
      }

      basic_string(std::initializer_list<T> lst,
                   const allocator_type& a = allocator_type())
      {
        const size_type sz = (size_type) (lst.size());
        my_first = (const_cast<allocator_type&>(a)).allocate(sz + 1U);
        my_last  = my_first + sz;
        xalgorithm::xcopy(lst.begin(), lst.end(), my_first);
        *my_last = static_cast<value_type>(0);
      }

      ~basic_string()
      {
        xallocator::xdestroy_range   (my_first, my_last + 1U, allocator_type());
        xallocator::xdeallocate_range(my_first, my_last + 1U, allocator_type());
      }

      basic_string& operator=(const basic_string& str)
      {
        if(this == &str)
        {
        }
        else
        {
          const size_type sz = str.length();

          if(length() != sz)
          {
            xallocator::xdestroy_range   (my_first, my_last + 1U, allocator_type());
            xallocator::xdeallocate_range(my_first, my_last + 1U, allocator_type());

            my_first = allocator_type().allocate(sz + 1U);
            my_last  = my_first + sz;
          }

          xalgorithm::xcopy(str.begin(), str.end(), my_first);
          *my_last = static_cast<value_type>(0);
        }

        return *this;
      }

      basic_string& operator=(const_pointer p)
      {
        const size_type sz = traits_type::length(p);

        if(length() != sz)
        {
          xallocator::xdestroy_range   (my_first, my_last + 1U, allocator_type());
          xallocator::xdeallocate_range(my_first, my_last + 1U, allocator_type());

          my_first = allocator_type().allocate(sz + 1U);
          my_last  = my_first + sz;
        }

        xalgorithm::xcopy(p, p + sz, my_first);
        *my_last = static_cast<value_type>(0);

        return *this;
      }

      basic_string& operator=(std::initializer_list<T> lst)
      {
        const size_type sz = lst.size();

        if(length() != sz)
        {
          xallocator::xdestroy_range   (my_first, my_last + 1U, allocator_type());
          xallocator::xdeallocate_range(my_first, my_last + 1U, allocator_type());

          my_first = allocator_type().allocate(sz + 1U);
          my_last  = my_first + sz;
        }

        xalgorithm::xcopy(lst.begin(), lst.end(), my_first);
        *my_last = static_cast<value_type>(0);

        return *this;
      }

      iterator begin() { return my_first; }
      iterator end  () { return my_last; }

      const_iterator begin() const { return my_first; }
      const_iterator end  () const { return my_last; }

      const_iterator cbegin() const { return my_first; }
      const_iterator cend  () const { return my_last; }

      reverse_iterator rbegin() { return reverse_iterator(my_last); }
      reverse_iterator rend  () { return reverse_iterator(my_first); }

      const_reverse_iterator rbegin() const { return const_reverse_iterator(my_last); }
      const_reverse_iterator rend  () const { return const_reverse_iterator(my_first); }

      const_reverse_iterator crbegin() const { return const_reverse_iterator(my_last); }
      const_reverse_iterator crend  () const { return const_reverse_iterator(my_first); }

      reference operator[](const size_type i)             { return my_first[i]; }
      const_reference operator[](const size_type i) const { return my_first[i]; }

      reference at(const size_type i)             { return my_first[i]; }
      const_reference at(const size_type i) const { return my_first[i]; }

      bool      empty () const { return (my_first == my_last); }
      size_type length() const { return static_cast<size_type>(std::distance(first, last)); }

      const_pointer c_str() const { return my_first; }

      allocator_type get_allocator() const { return allocator_type(); }

      bool operator==(const basic_string& other) const
      {
        const bool the_lengths_are_equal = (length() == other.length());

        return (the_lengths_are_equal && xalgorithm::xequal(my_first, my_last, other.my_first));
      }

    private:
      iterator my_first;
      iterator my_last;
    };
  }

#endif // _BASIC_STRING_IMPL_2010_02_23_H_
