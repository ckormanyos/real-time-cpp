///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2021.
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
    template<typename ValueType,
             typename AllocatorType = std::allocator<ValueType>>
    class dynamic_array
    {
    public:
      // Type definitions.
      using allocator_type         =       AllocatorType;
      using value_type             =       ValueType;
      using reference              =       value_type&;
      using const_reference        = const value_type&;
      using iterator               =       value_type*;
      using const_iterator         = const value_type*;
      using pointer                =       value_type*;
      using const_pointer          = const value_type*;
      using size_type              =       std::uint_fast32_t;
      using difference_type        =       std::ptrdiff_t;
      using reverse_iterator       =       std::reverse_iterator<iterator>;
      using const_reverse_iterator =       std::reverse_iterator<const_iterator>;

      // Constructors.
      constexpr dynamic_array() : elem_count(0U),
                                  elems     (nullptr) { }

      dynamic_array(size_type count,
                    const_reference v = value_type(),
                    const allocator_type& a = allocator_type())
        : elem_count(count),
          elems     (elem_count > 0U ? allocator_type(a).allocate(elem_count) : nullptr)
      {
        iterator it = begin();

        while(it != end())
        {
          allocator_type my_a(a);

          std::allocator_traits<AllocatorType>::construct(my_a, it, v);

          ++it;
        }
      }

      dynamic_array(const dynamic_array& other)
        : elem_count(other.size()),
          elems     (elem_count > 0U ? allocator_type().allocate(elem_count) : nullptr)
      {
        std::copy(other.elems, other.elems + elem_count, elems);
      }

      template<typename input_iterator>
      dynamic_array(input_iterator first,
                    input_iterator last,
                    const allocator_type& a = allocator_type())
        : elem_count(static_cast<size_type>(std::distance(first, last))),
          elems     (elem_count > 0U ? allocator_type(a).allocate(elem_count) : nullptr)
      {
        std::copy(first, last, elems);
      }

      dynamic_array(std::initializer_list<value_type> lst,
                    const allocator_type& a = allocator_type())
        : elem_count(lst.size()),
          elems     (elem_count > 0U ? allocator_type(a).allocate(elem_count) : nullptr)
      {
        std::copy(lst.begin(), lst.end(), elems);
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
        pointer p = elems;

        while(p != elems + elem_count)
        {
          allocator_type a;

          std::allocator_traits<allocator_type>::destroy(a, p);

          ++p;
        }

        // Destroy the elements and deallocate the range.
        allocator_type().deallocate(elems, elem_count);
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
        pointer p = elems;

        while(p != elems + elem_count)
        {
          allocator_type a;

          std::allocator_traits<allocator_type>::destroy(a, p);

          ++p;
        }

        allocator_type().deallocate(elems, elem_count);

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
      pointer       data()       { return elems; }
      const_pointer data() const { return elems; }

      // Size and capacity.
      size_type size    () const { return  elem_count; }
      size_type max_size() const { return  elem_count; }
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
      void fill(const value_type& v)
      {
        std::fill_n(begin(), elem_count, v);
      }

      void swap(dynamic_array& other)
      {
        const size_type tmp_elem_count = elem_count;
        const pointer   tmp_elems      = elems;

        elem_count = other.elem_count;
        elems      = other.elems;

        other.elem_count = tmp_elem_count;
        other.elems      = tmp_elems;
      }

      void swap(dynamic_array&& other)
      {
        const size_type tmp_elem_count = elem_count;
        const pointer   tmp_elems      = elems;

        elem_count = other.elem_count;
        elems      = other.elems;

        other.elem_count = tmp_elem_count;
        other.elems      = tmp_elems;
      }

    protected:
      mutable size_type elem_count;
      pointer           elems;
    };

    template<typename ValueType, typename AllocatorType>
    bool operator==(const dynamic_array<ValueType, AllocatorType>& lhs,
                    const dynamic_array<ValueType, AllocatorType>& rhs)
    {
      bool left_and_right_are_equal;

      const bool sizes_are_equal = (lhs.size() == rhs.size());

      if(sizes_are_equal)
      {
        typedef typename dynamic_array<ValueType, AllocatorType>::size_type size_type;

        const bool size_of_left_is_zero = (lhs.size() == size_type(0U));

        left_and_right_are_equal =
          (size_of_left_is_zero || std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin()));
      }
      else
      {
        left_and_right_are_equal = false;
      }

      return left_and_right_are_equal;
    }

    template<typename ValueType, typename AllocatorType>
    bool operator<(const dynamic_array<ValueType, AllocatorType>& lhs,
                   const dynamic_array<ValueType, AllocatorType>& rhs)
    {
      typedef typename dynamic_array<ValueType, AllocatorType>::size_type size_type;

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

          return std::lexicographical_compare(lhs.cbegin(),
                                              lhs.cbegin() + count,
                                              rhs.cbegin(),
                                              rhs.cbegin() + count);
        }
      }
    }

    template<typename ValueType, typename AllocatorType>
    bool operator!=(const dynamic_array<ValueType, AllocatorType>& lhs,
                    const dynamic_array<ValueType, AllocatorType>& rhs)
    {
      return ((lhs == rhs) == false);
    }

    template<typename ValueType, typename AllocatorType>
    bool operator>(const dynamic_array<ValueType, AllocatorType>& lhs,
                   const dynamic_array<ValueType, AllocatorType>& rhs)
    {
      return (rhs < lhs);
    }

    template<typename ValueType, typename AllocatorType>
    bool operator>=(const dynamic_array<ValueType, AllocatorType>& lhs,
                    const dynamic_array<ValueType, AllocatorType>& rhs)
    {
      return ((lhs < rhs) == false);
    }

    template<typename ValueType, typename AllocatorType>
    bool operator<=(const dynamic_array<ValueType, AllocatorType>& lhs,
                    const dynamic_array<ValueType, AllocatorType>& rhs)
    {
      return ((rhs < lhs) == false);
    }

    template<typename ValueType, typename AllocatorType>
    void swap(dynamic_array<ValueType, AllocatorType>& x,
              dynamic_array<ValueType, AllocatorType>& y)
    {
      x.swap(y);
    }
  }

#endif // UTIL_DYNAMIC_ARRAY_2012_05_16_H_
