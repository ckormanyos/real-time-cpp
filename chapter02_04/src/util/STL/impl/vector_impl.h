#ifndef _VECTOR_IMPL_2010_02_23_H_
  #define _VECTOR_IMPL_2010_02_23_H_

  #include "xalgorithm_impl.h"
  #include "xallocator_impl.h"
  #include "memory_impl.h"
  #include "iterator_impl.h"
  #include "initializer_list_impl.h"

  // Implement some of std::vector for compilers that do not yet support it.

  namespace std
  {
    template<typename T,
             typename Allocator = std::allocator<T> >
    class vector
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

      vector() : my_first(iterator(0U)),
                 my_last (iterator(0U)),
                 my_end  (iterator(0U)) { }

      explicit vector(size_type count) : my_first(allocator_type().allocate(count)),
                                         my_last (my_first + count),
                                         my_end  (my_last)
      {
        xalgorithm::xfill(my_first, my_last, value_type());
      }

      vector(size_type count, const T& value) : my_first(allocator_type().allocate(count)),
                                                my_last (my_first + count),
                                                my_end  (my_last)
      {
        xalgorithm::xfill(my_first, my_last, value);
      }

      vector(size_type count,
             const T& value,
             const allocator_type& a) : my_first((const_cast<allocator_type&>(a)).allocate(count)),
                                        my_last (my_first + count),
                                        my_end  (my_last)
      {
        xalgorithm::xfill(my_first, my_last, value);
      }

      template<class InputIterator>
      vector(InputIterator first,
             InputIterator last,
             const allocator_type& a = allocator_type()) : my_first(a.allocate(last - first)),
                                                           my_last (my_first + (last - first)),
                                                           my_end  (my_last)
      {
        xalgorithm::xcopy(first, last, my_first);
      }

      vector(const vector& other) : my_first(allocator_type().allocate(other.size())),
                                    my_last (my_first + other.size()),
                                    my_end  (my_last)
      {
        xalgorithm::xcopy(other.my_first, other.my_last, my_first);
      }

      vector(std::initializer_list<T> lst,
             const allocator_type& a = allocator_type()) : my_first(a.allocate(lst.size())),
                                                           my_last (my_first + lst.size()),
                                                           my_end  (my_last)
      {
        xalgorithm::xcopy(lst.begin(), lst.end(), my_first);
      }

      ~vector()
      {
        xallocator::xdestroy_range(my_first, my_last, allocator_type());
        xallocator::xdeallocate_range(my_first, my_end, allocator_type());
      }

      vector& operator=(const vector& other)
      {
        const size_type sz = other.size();

        if(size() != sz)
        {
          clear();
          my_first = allocator_type().allocate(sz);
          my_last  = my_first + sz;
          my_end   = my_first + sz;
        }

        xalgorithm::xcopy(other.begin(), other.end(), my_first);

        return *this;
      }

      vector& operator=(std::initializer_list<T> lst)
      {
        const size_type sz = lst.size();

        if(size() != sz)
        {
          clear();
          my_first = allocator_type().allocate(sz);
          my_last  = my_first + sz;
          my_end   = my_first + sz;
        }

        xalgorithm::xcopy(lst.begin(), lst.end(), my_first);

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

      reference       operator[](const size_type i)       { return my_first[i]; }
      const_reference operator[](const size_type i) const { return my_first[i]; }

      const_pointer data(void) const { return my_first; }
      pointer       data(void)       { return my_first; }

      reference       at(const size_type i)       { return my_first[i]; }
      const_reference at(const size_type i) const { return my_first[i]; }

      reference       front(void)       { return *my_first; }
      const_reference front(void) const { return *my_first; }

      reference       back(void)       { return *(my_last - 1U); }
      const_reference back(void) const { return *(my_last - 1U); }

      bool empty(void) const { return (my_first == my_last); }
      size_type size(void) const { return (size_type) (my_last - my_first); }
      size_type capacity(void) const { return (size_type) (my_end - my_first); }

      void reserve(size_type count)
      {
        if(count > capacity())
        {
          iterator new_first = allocator_type().allocate(count);

          xalgorithm::xcopy(my_first, my_last, new_first);
          xallocator::xdestroy_range(my_first, my_last, allocator_type());
          xallocator::xdeallocate_range(my_first, my_end, allocator_type());

          my_last  = new_first + size();
          my_first = new_first;
          my_end   = new_first + count;
        }
      }

      void resize(size_type count, const value_type& value = value_type())
      {
        if     (count == size()) { }
        else if(count <  size())
        {
          xallocator::xdestroy_range(my_first + count, my_last, allocator_type());
          my_last = my_first + count;
        }
        else
        {
          if(count > capacity())
          {
            reserve(count);
          }

          xalgorithm::xfill(my_last, my_first + count, value);
          my_last = my_first + count;
        }
      }

      void assign(size_type count, const T& value)
      {
        resize(count);
        xalgorithm::xfill(my_first, my_last, value);
      }

      template<typename InputIterator>
      void assign(InputIterator first, InputIterator last)
      {
        resize((size_type) (last - first));
        xalgorithm::xcopy(first, last, my_first);
      }

      void push_back(const value_type& value)
      {
        const size_type the_size = size();

        if(capacity() <= the_size)
        {
          const size_type count = the_size * 2U;
          reserve(xalgorithm::xmax(count, 4U));
        }

        *my_last = value;
        ++my_last;
      }

      void clear(void)
      {
        xallocator::xdestroy_range(my_first, my_last, allocator_type());
        xallocator::xdeallocate_range(my_first, my_last, allocator_type());
        my_last = my_first;
      }

    private:
      iterator my_first; // begin()
      iterator my_last;  // end()
      iterator my_end;   // capacity()

      static allocator_type get_allocator(void) { return allocator_type(); }
    };
  }

#endif // _VECTOR_IMPL_2010_02_23_H_
