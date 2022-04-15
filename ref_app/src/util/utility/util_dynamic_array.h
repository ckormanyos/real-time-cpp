///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_DYNAMIC_ARRAY_2012_05_16_H // NOLINT(llvm-header-guard)
  #define UTIL_DYNAMIC_ARRAY_2012_05_16_H

  #include <algorithm>
  #include <initializer_list>
  #include <iterator>
  #include <memory>
  #include <utility>

  namespace util {

  template<typename ValueType,
           typename AllocatorType = std::allocator<ValueType>,
           typename SizeType      = std::size_t,
           typename DiffType      = std::ptrdiff_t>
  class dynamic_array;

  template<typename ValueType,
           typename AllocatorType,
           typename SizeType,
           typename DiffType>
  class dynamic_array
  {
  public:
    // Type definitions.
    using allocator_type         = typename std::allocator_traits<AllocatorType>::template rebind_alloc<ValueType>;
    using value_type             = typename allocator_type::value_type;
    using reference              =       value_type&;
    using const_reference        = const value_type&;
    using iterator               =       value_type*;
    using const_iterator         = const value_type*;
    using pointer                =       value_type*;
    using const_pointer          = const value_type*;
    using size_type              =       SizeType;
    using difference_type        =       DiffType;
    using reverse_iterator       =       std::reverse_iterator<iterator>;
    using const_reverse_iterator =       std::reverse_iterator<const_iterator>;

    // Constructors.
    explicit dynamic_array(      size_type       count = static_cast<size_type>(0U),
                                 const_reference v     = value_type(),
                           const allocator_type& a     = allocator_type())
      : elem_count(count),
        elems     (nullptr)
    {
      if(elem_count > 0U)
      {
        allocator_type my_a(a);

        elems = std::allocator_traits<allocator_type>::allocate(my_a, elem_count);

        iterator it = begin();

        while(it != end())
        {
          std::allocator_traits<allocator_type>::construct(my_a, it, v);

          ++it;
        }
      }
    }

    dynamic_array(const dynamic_array& other)
      : elem_count(other.size()),
        elems     (nullptr)
    {
      allocator_type my_a;

      if(elem_count > 0U)
      {
        elems = std::allocator_traits<allocator_type>::allocate(my_a, elem_count);
      }

      std::copy(other.elems, other.elems + elem_count, elems);
    }

    template<typename input_iterator>
    dynamic_array(input_iterator first,
                  input_iterator last,
                  const allocator_type& a = allocator_type())
      : elem_count(static_cast<size_type>(std::distance(first, last))),
        elems     (nullptr)
    {
      allocator_type my_a(a);

      if(elem_count > 0U)
      {
        elems = std::allocator_traits<allocator_type>::allocate(my_a, elem_count);
      }

      std::copy(first, last, elems);
    }

    dynamic_array(std::initializer_list<value_type> lst,
                  const allocator_type& a = allocator_type())
      : elem_count(lst.size()),
        elems     (nullptr)
    {
      allocator_type my_a(a);

      if(elem_count > 0U)
      {
        elems = std::allocator_traits<allocator_type>::allocate(my_a, elem_count);
      }

      std::copy(lst.begin(), lst.end(), elems);
    }

    // Move constructor.
    dynamic_array(dynamic_array&& other) noexcept : elem_count(other.elem_count),
                                                    elems     (other.elems)
    {
      other.elem_count = 0U;
      other.elems      = nullptr;
    }

    // Destructor.
    virtual ~dynamic_array()
    {
      pointer p = elems; // NOLINT(altera-id-dependent-backward-branch)

      using local_allocator_traits_type = std::allocator_traits<allocator_type>;

      allocator_type my_a;

      while(p != elems + elem_count) // NOLINT(altera-id-dependent-backward-branch)
      {
        local_allocator_traits_type::destroy(my_a, p);

        ++p;
      }

      // Destroy the elements and deallocate the range.
      local_allocator_traits_type::deallocate(my_a, elems, elem_count);
    }

    // Assignment operator.
    auto operator=(const dynamic_array& other) -> dynamic_array&
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
    auto operator=(dynamic_array&& other) noexcept -> dynamic_array&
    {
      std::swap(elem_count, other.elem_count);
      std::swap(elems,      other.elems);

      return *this;
    }

    // Iterator members:
    auto begin  ()       -> iterator               { return elems; }
    auto end    ()       -> iterator               { return elems + elem_count; }
    auto begin  () const -> const_iterator         { return elems; }
    auto end    () const -> const_iterator         { return elems + elem_count; }
    auto cbegin () const -> const_iterator         { return elems; }
    auto cend   () const -> const_iterator         { return elems + elem_count; }
    auto rbegin ()       -> reverse_iterator       { return reverse_iterator(elems + elem_count); }
    auto rend   ()       -> reverse_iterator       { return reverse_iterator(elems); }
    auto rbegin () const -> const_reverse_iterator { return const_reverse_iterator(elems + elem_count); }
    auto rend   () const -> const_reverse_iterator { return const_reverse_iterator(elems); }
    auto crbegin() const -> const_reverse_iterator { return const_reverse_iterator(elems + elem_count); }
    auto crend  () const -> const_reverse_iterator { return const_reverse_iterator(elems); }

    // Raw pointer access.
    auto data()       -> pointer       { return elems; }
    auto data() const -> const_pointer { return elems; }

    // Size and capacity.
    constexpr auto size    () const -> size_type { return  elem_count; }
    constexpr auto max_size() const -> size_type { return  elem_count; }
    constexpr auto empty   () const -> bool      { return (elem_count == 0U); }

    // Element access members.
    auto operator[](const size_type i)       -> reference       { return elems[i]; }
    auto operator[](const size_type i) const -> const_reference { return elems[i]; }

    auto front()       -> reference       { return elems[0U]; }
    auto front() const -> const_reference { return elems[0U]; }

    auto back()       -> reference       { return ((elem_count > static_cast<size_type>(0U)) ? elems[elem_count - 1U] : elems[0U]); }
    auto back() const -> const_reference { return ((elem_count > static_cast<size_type>(0U)) ? elems[elem_count - 1U] : elems[0U]); }

    auto at(const size_type i)       -> reference       { return ((i < elem_count) ? elems[i] : elems[0U]); }
    auto at(const size_type i) const -> const_reference { return ((i < elem_count) ? elems[i] : elems[0U]); }

    // Element manipulation members.
    auto fill(const value_type& v) -> void
    {
      std::fill_n(begin(), elem_count, v);
    }

    auto swap(dynamic_array& other) noexcept -> void
    {
      if(this != &other)
      {
        std::swap(elems,      other.elems);
        std::swap(elem_count, other.elem_count);
      }
    }

    auto swap(dynamic_array&& other) noexcept -> void
    {
      auto tmp = std::move(*this);

      *this = std::move(other);
      other = std::move(tmp);
    }

  private:
    mutable size_type elem_count; // NOLINT(readability-identifier-naming)
    pointer           elems;      // NOLINT(readability-identifier-naming,altera-id-dependent-backward-branch)
  };

  template<typename ValueType, typename AllocatorType>
  auto operator==(const dynamic_array<ValueType, AllocatorType>& lhs,
                  const dynamic_array<ValueType, AllocatorType>& rhs) -> bool
  {
    bool left_and_right_are_equal = false;

    const bool sizes_are_equal = (lhs.size() == rhs.size());

    if(sizes_are_equal)
    {
      using size_type = typename dynamic_array<ValueType, AllocatorType>::size_type;

      const bool size_of_left_is_zero = (lhs.size() == static_cast<size_type>(0U));

      left_and_right_are_equal =
        (size_of_left_is_zero || std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin()));
    }

    return left_and_right_are_equal;
  }

  template<typename ValueType, typename AllocatorType>
  auto operator<(const dynamic_array<ValueType, AllocatorType>& lhs,
                 const dynamic_array<ValueType, AllocatorType>& rhs) -> bool
  {
    using size_type = typename dynamic_array<ValueType, AllocatorType>::size_type;

    const bool size_of_left_is_zero = (lhs.size() == static_cast<size_type>(0U));

    bool b_result { };

    if(size_of_left_is_zero)
    {
      const bool size_of_right_is_zero = (rhs.size() == static_cast<size_type>(0U));

      b_result = (!size_of_right_is_zero);
    }
    else
    {
      if(size_of_left_is_zero)
      {
        const bool size_of_right_is_zero = (rhs.size() == static_cast<size_type>(0U));

        b_result = (!size_of_right_is_zero);
      }
      else
      {
        const size_type count = (std::min)(lhs.size(), rhs.size());

        b_result= std::lexicographical_compare(lhs.cbegin(),
                                               lhs.cbegin() + count,
                                               rhs.cbegin(),
                                               rhs.cbegin() + count);
      }
    }

    return b_result;
  }

  template<typename ValueType, typename AllocatorType>
  auto operator!=(const dynamic_array<ValueType, AllocatorType>& lhs,
                  const dynamic_array<ValueType, AllocatorType>& rhs) -> bool
  {
    return (!(lhs == rhs));
  }

  template<typename ValueType, typename AllocatorType>
  auto operator>(const dynamic_array<ValueType, AllocatorType>& lhs,
                 const dynamic_array<ValueType, AllocatorType>& rhs) -> bool
  {
    return (rhs < lhs);
  }

  template<typename ValueType, typename AllocatorType>
  auto operator>=(const dynamic_array<ValueType, AllocatorType>& lhs,
                  const dynamic_array<ValueType, AllocatorType>& rhs) -> bool
  {
    return (!(lhs < rhs));
  }

  template<typename ValueType, typename AllocatorType>
  auto operator<=(const dynamic_array<ValueType, AllocatorType>& lhs,
                  const dynamic_array<ValueType, AllocatorType>& rhs) -> bool
  {
    return (!(rhs < lhs));
  }

  template<typename ValueType, typename AllocatorType>
  auto swap(dynamic_array<ValueType, AllocatorType>& x,
            dynamic_array<ValueType, AllocatorType>& y) noexcept -> void
  {
    x.swap(y);
  }

  } // namespace util

#endif // UTIL_DYNAMIC_ARRAY_2012_05_16_H_
