///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
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
                        elems     (nullptr) { }

      dynamic_array(size_type count) : elem_count(count),
                                       elems     (elem_count > 0U ? allocator_type().allocate(elem_count) : nullptr)
      {
        for(auto it_self = begin(); it_self != end(); ++it_self)
        {
          allocator_type().construct(it_self, value_type());
        }
      }

      dynamic_array(size_type count,
                    const value_type& v,
                    const allocator_type& a = allocator_type())
        : elem_count(count),
          elems     (elem_count > 0U ? allocator_type(a).allocate(elem_count) : nullptr)
      {
        for(auto it_self = begin(); it_self != end(); ++it_self)
        {
          allocator_type(a).construct(it_self, v);
        }
      }

      dynamic_array(const dynamic_array& other)
        : elem_count(other.size()),
          elems     (elem_count > 0U ? allocator_type().allocate(elem_count) : nullptr)
      {
        auto it_other = other.cbegin();

        for(auto it_self = begin(); it_self != end(); ++it_self)
        {
          allocator_type().construct(it_self, *it_other++);
        }
      }

      template<typename input_iterator>
      dynamic_array(input_iterator first,
                    input_iterator last,
                    const allocator_type& a = allocator_type())
        : elem_count(static_cast<size_type>(std::distance(first, last))),
          elems     (elem_count > 0U ? allocator_type(a).allocate(elem_count) : nullptr)
      {
        for(auto it_self = begin(); it_self != end(); ++it_self)
        {
          allocator_type(a).construct(it_self, *first++);
        }
      }

      dynamic_array(std::initializer_list<T> lst,
                    const allocator_type& a = allocator_type())
        : elem_count(lst.size()),
          elems     (elem_count > 0U ? allocator_type(a).allocate(elem_count) : nullptr)
      {
        auto it_lst = lst.begin();

        for(auto it_self = begin(); it_self != end(); ++it_self)
        {
          allocator_type(a).construct(it_self, *it_lst++);
        }
      }

      // Move constructor.
      dynamic_array(dynamic_array&& other) : elem_count(other.elem_count),
                                             elems     (other.elems)
      {
        other.elem_count = 0U;
        other.elems      = nullptr;
      }

      // Destructor.
      virtual ~dynamic_array()
      {
        // Destroy the elements and deallocate the range.
        if(elem_count > size_type(0U))
        {
          for(pointer p = elems; p != (elems + elem_count); ++p)
          {
            allocator_type().destroy(p);
          }

          allocator_type().deallocate(elems, elem_count);
        }
      }

      // Assignment operator.
      dynamic_array& operator=(const dynamic_array& other)
      {
        if(this != &other)
        {
          std::copy(other.elems,
                    other.elems + (std::min)(elem_count, other.elem_count),
                    elems);
        }

        return *this;
      }

      // Move assignment operator.
      dynamic_array& operator=(dynamic_array&& other)
      {
        // Destroy the elements and deallocate the range.
        if(elem_count > size_type(0U))
        {
          for(pointer p = elems; p != (elems + elem_count); ++p)
          {
            allocator_type().destroy(p);
          }

          allocator_type().deallocate(elems, elem_count);
        }

        elem_count = other.elem_count;
        elems      = other.elems;

        other.elem_count = 0U;
        other.elems      = nullptr;

        return *this;
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

      // Raw pointer access.
      pointer data()
      {
        return elems;
      }

      // Size and capacity.
      size_type size    () const { return elem_count; }
      size_type max_size() const { return elem_count; }
      bool      empty   () const { return (elem_count == 0U); }

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
        const size_type tmp_elem_count = elem_count;
        const pointer   tmp_elems      = elems;

        elem_count = other.elem_count;
        elems      = other.elems;

        other.elem_count = tmp_elem_count;
        other.elems      = tmp_elems;
      }

    private:
      mutable size_type elem_count;
      pointer           elems;
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

#endif // UTIL_DYNAMIC_ARRAY_2012_05_16_H_
