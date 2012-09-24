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
             typename Traits = std::char_traits<T>,
             typename Allocator = std::allocator<T> >
    class basic_string
    {
    public:
      typedef std::size_t                           size_type;
      typedef std::ptrdiff_t                        difference_type;
      typedef T                                     value_type;
      typedef typename Allocator::pointer           pointer;
      typedef typename Allocator::const_pointer     const_pointer;
      typedef typename Allocator::reference         reference;
      typedef typename Allocator::const_reference   const_reference;
      typedef pointer                               iterator;
      typedef const_pointer                         const_iterator;
      typedef std::reverse_iterator<iterator>       reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
      typedef Allocator                             allocator_type;

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
        const size_type count = Traits::length(p);
        my_first = allocator_type().allocate(count + 1U);
        my_last = my_first + count;
        xalgorithm::xcopy(p, p + count, my_first);
        *my_last = static_cast<value_type>(0);
      }

      basic_string(const basic_string& str)
      {
        const size_type sz = str.length();
        my_first = allocator_type().allocate(count + 1U);
        my_last = my_first + sz;
        xalgorithm::xcopy(str.begin(), str.end(), my_first);
        *my_last = static_cast<value_type>(0);
      }

      basic_string(std::initializer_list<T> lst)
      {
        const size_type sz = lst.size();
        my_first = allocator_type().allocate(count + 1U);
        my_last = my_first + sz;
        xalgorithm::xcopy(lst.begin(), lst.end(), my_first);
        *my_last = static_cast<value_type>(0);
      }

      basic_string(size_type count,
                   const T& value,
                   const allocator_type& a) : my_first(a.allocate(count + 1U)),
                                              my_last (my_first + count)
      {
        xalgorithm::xfill(my_first, my_last, value);
        *my_last = static_cast<value_type>(0);
      }

      template<class InputIterator>
      basic_string(InputIterator first,
                   InputIterator last,
                   const allocator_type& a = allocator_type())
      {
        const size_type sz = (size_type) (last - first);
        my_first = a.allocate(sz + 1U);
        my_last  = my_first + sz;
        xalgorithm::xcopy(first, last, my_first);
        *my_last = static_cast<value_type>(0);
      }

      basic_string(std::initializer_list<T> lst,
                   const allocator_type& a = allocator_type())
      {
        const size_type sz = (size_type) (lst.size());
        my_first = a.allocate(sz + 1U);
        my_last  = my_first + sz;
        xalgorithm::xcopy(lst.begin(), lst.end(), my_first);
        *my_last = static_cast<value_type>(0);
      }

      ~basic_string()
      {
        xallocator::xdestroy_range(my_first, my_last + 1U, allocator_type());
        xallocator::xdeallocate_range(my_first, my_last + 1U, allocator_type());
      }

      basic_string& operator=(const basic_string& str)
      {
        if(this == str.this)
        {
        }
        else
        {
          const size_type sz = str.length();

          if(length() != sz)
          {
            xallocator::xdestroy_range(my_first, my_last + 1U, allocator_type());
            xallocator::xdeallocate_range(my_first, my_last + 1U, allocator_type());

            my_first = a.allocate(sz + 1U);
            my_last  = my_first + sz;
          }

          xalgorithm::xcopy(str.begin(), str.end(), my_first);
          *my_last = static_cast<value_type>(0);
        }

        return *this;
      }

      basic_string& operator=(const_pointer p)
      {
        const size_type sz = Traits::length(p);

        if(length() != sz)
        {
          xallocator::xdestroy_range(my_first, my_last + 1U, allocator_type());
          xallocator::xdeallocate_range(my_first, my_last + 1U, allocator_type());

          my_first = a.allocate(sz + 1U);
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
          xallocator::xdestroy_range(my_first, my_last + 1U, allocator_type());
          xallocator::xdeallocate_range(my_first, my_last + 1U, allocator_type());

          my_first = a.allocate(sz + 1U);
          my_last  = my_first + sz;
        }

        xalgorithm::xcopy(lst.begin(), lst.end(), my_first);
        *my_last = static_cast<value_type>(0);

        return *this;
      }

      iterator begin(void) { return my_first; }
      iterator end  (void) { return my_last; }

      const_iterator begin(void) const { return my_first; }
      const_iterator end  (void) const { return my_last; }

      const_iterator cbegin(void) const { return my_first; }
      const_iterator cend  (void) const { return my_last; }

      reverse_iterator rbegin(void) { return reverse_iterator(my_last); }
      reverse_iterator rend  (void) { return reverse_iterator(my_first); }

      const_reverse_iterator rbegin(void) const { return const_reverse_iterator(my_last); }
      const_reverse_iterator rend  (void) const { return const_reverse_iterator(my_first); }

      const_reverse_iterator crbegin(void) const { return const_reverse_iterator(my_last); }
      const_reverse_iterator crend  (void) const { return const_reverse_iterator(my_first); }

      reference operator[](const size_type i)             { return my_first[i]; }
      const_reference operator[](const size_type i) const { return my_first[i]; }

      reference at(const size_type i)             { return my_first[i]; }
      const_reference at(const size_type i) const { return my_first[i]; }

      bool empty(void) const { return (my_first == my_last); }
      size_type length(void) const { return (size_type) (my_last - my_first); }

      const_pointer c_str(void) const { return my_first; }

      allocator_type get_allocator() const { return allocator_type(); }

    private:
      iterator my_first;
      iterator my_last;
    };
  }

#endif // _BASIC_STRING_IMPL_2010_02_23_H_
