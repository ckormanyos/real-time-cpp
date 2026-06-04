///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2012 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_DYNAMIC_ARRAY_2012_05_16_H // NOLINT(llvm-header-guard)
  #define UTIL_DYNAMIC_ARRAY_2012_05_16_H

  #include <algorithm>
  #include <cstddef>
  #include <cstdint>
  #include <initializer_list>
  #include <iterator>
  #include <memory>
  #include <utility>

  namespace util {

  template<typename ValueType,
           typename AllocatorType = ::std::allocator<ValueType>,
           typename SizeType      = ::std::size_t,
           typename DiffType      = ::std::ptrdiff_t>
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
    explicit constexpr dynamic_array(size_type count_in = size_type(),
                                     const_reference value_in = value_type(),
                                     const allocator_type& alloc_in = allocator_type())
      : elem_count(count_in),
        my_alloc(alloc_in)
    {
      if(elem_count > static_cast<size_type>(UINT8_C(0)))
      {
        elems = std::allocator_traits<allocator_type>::allocate(my_alloc, elem_count);

        iterator it = begin();

        while(it != end())
        {
          *it++ = value_in;
        }
      }
    }

    constexpr dynamic_array(const dynamic_array& other)
      : elem_count(other.elem_count),
        my_alloc(other.my_alloc)
    {
      if(elem_count > static_cast<size_type>(UINT8_C(0)))
      {
        elems = std::allocator_traits<allocator_type>::allocate(my_alloc, elem_count);

        std::copy(other.elems, other.elems + elem_count, elems);
      }
    }

    template<typename InputIterator>
    constexpr dynamic_array(InputIterator first,
                            InputIterator last,
                            const allocator_type& alloc_in = allocator_type())
      : elem_count(static_cast<size_type>(std::distance(first, last))),
        my_alloc(alloc_in)
    {
      if(elem_count > static_cast<size_type>(UINT8_C(0)))
      {
        elems = std::allocator_traits<allocator_type>::allocate(my_alloc, elem_count);

        std::copy(first, last, elems);
      }
    }

    constexpr dynamic_array(std::initializer_list<value_type> lst,
                            const allocator_type& alloc_in = allocator_type())
      : elem_count(lst.size()),
        my_alloc(alloc_in)
    {
      if(elem_count > static_cast<size_type>(UINT8_C(0)))
      {
        elems = std::allocator_traits<allocator_type>::allocate(my_alloc, elem_count);

        std::copy(lst.begin(), lst.end(), elems);
      }
    }

    // Move constructor.
    constexpr dynamic_array(dynamic_array&& other) noexcept : elem_count(other.elem_count),
                                                              elems     (other.elems),
                                                              my_alloc  (std::move(static_cast<allocator_type&&>(other.my_alloc)))
    {
      other.elem_count = static_cast<size_type>(UINT8_C(0));
      other.elems      = nullptr;
    }

    // Destructor.
    virtual ~dynamic_array()
    {
      if(!empty())
      {
        // The destructors of the elements are called (in unspecified order)
        // and the dynamically allocated storage (if any) is deallocated.

        for(auto* itr { begin() }; itr != end(); ++itr) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        {
          itr->~value_type();
        }

        using local_allocator_traits_type = std::allocator_traits<allocator_type>;

        local_allocator_traits_type::deallocate(my_alloc, elems, elem_count);

        elem_count = static_cast<size_type>(UINT8_C(0));
        elems      = nullptr;
      }
    }

    // Assignment operator.
    constexpr auto operator=(const dynamic_array& other) -> dynamic_array&
    {
      if(this != &other)
      {
        std::copy
        (
          other.elems,
          other.elems + (std::min)
                        (
                          elem_count, other.elem_count
                        ),
          elems
        );
      }

      return *this;
    }

    // Move assignment operator.
    constexpr auto operator=(dynamic_array&& other) noexcept -> dynamic_array&
    {
      if(this != &other)
      {
        if(!empty())
        {
          using local_allocator_traits_type = std::allocator_traits<allocator_type>;

          // Deallocate the range of *this.
          local_allocator_traits_type::deallocate(my_alloc, elems, elem_count);
        }

        elem_count = other.elem_count;
        elems      = other.elems;

        other.elem_count = static_cast<size_type>(UINT8_C(0));
        other.elems      = nullptr;
      }

      return *this;
    }

    // Iterator members:
    [[nodiscard]] constexpr auto begin  ()       noexcept -> iterator               { return elems; }
    [[nodiscard]] constexpr auto end    ()       noexcept -> iterator               { return elems + elem_count; }
    [[nodiscard]] constexpr auto begin  () const noexcept -> const_iterator         { return elems; }
    [[nodiscard]] constexpr auto end    () const noexcept -> const_iterator         { return elems + elem_count; }
    [[nodiscard]] constexpr auto cbegin () const noexcept -> const_iterator         { return elems; }
    [[nodiscard]] constexpr auto cend   () const noexcept -> const_iterator         { return elems + elem_count; }
    [[nodiscard]] constexpr auto rbegin ()       noexcept -> reverse_iterator       { return reverse_iterator(elems + elem_count); }
    [[nodiscard]] constexpr auto rend   ()       noexcept -> reverse_iterator       { return reverse_iterator(elems); }
    [[nodiscard]] constexpr auto rbegin () const noexcept -> const_reverse_iterator { return const_reverse_iterator(elems + elem_count); }
    [[nodiscard]] constexpr auto rend   () const noexcept -> const_reverse_iterator { return const_reverse_iterator(elems); }
    [[nodiscard]] constexpr auto crbegin() const noexcept -> const_reverse_iterator { return const_reverse_iterator(elems + elem_count); }
    [[nodiscard]] constexpr auto crend  () const noexcept -> const_reverse_iterator { return const_reverse_iterator(elems); }

    // Raw pointer access.
    [[nodiscard]] constexpr auto data()       noexcept -> pointer       { return elems; }
    [[nodiscard]] constexpr auto data() const noexcept -> const_pointer { return elems; }

    // Size and capacity.
    [[nodiscard]] constexpr auto size    () const noexcept -> size_type { return  elem_count; }
    [[nodiscard]] constexpr auto max_size() const noexcept -> size_type { return  elem_count; }
    [[nodiscard]] constexpr auto empty   () const noexcept -> bool      { return (elem_count == static_cast<size_type>(UINT8_C(0))); }

    // Element access members.
    [[nodiscard]] constexpr auto operator[](const size_type i)       noexcept -> reference       { return elems[i]; }
    [[nodiscard]] constexpr auto operator[](const size_type i) const noexcept -> const_reference { return elems[i]; }

    [[nodiscard]] constexpr auto front()       noexcept -> reference       { return elems[static_cast<size_type>(UINT8_C(0))]; }
    [[nodiscard]] constexpr auto front() const noexcept -> const_reference { return elems[static_cast<size_type>(UINT8_C(0))]; }

    [[nodiscard]] constexpr auto back()       noexcept -> reference       { return ((elem_count > static_cast<size_type>(UINT8_C(0))) ? elems[static_cast<size_type>(elem_count - static_cast<size_type>(UINT8_C(1)))] : elems[static_cast<size_type>(UINT8_C(0))]); }
    [[nodiscard]] constexpr auto back() const noexcept -> const_reference { return ((elem_count > static_cast<size_type>(UINT8_C(0))) ? elems[static_cast<size_type>(elem_count - static_cast<size_type>(UINT8_C(1)))] : elems[static_cast<size_type>(UINT8_C(0))]); }

    [[nodiscard]] constexpr auto at(const size_type i)       noexcept -> reference       { return ((i < elem_count) ? elems[i] : elems[static_cast<size_type>(UINT8_C(0))]); }
    [[nodiscard]] constexpr auto at(const size_type i) const noexcept -> const_reference { return ((i < elem_count) ? elems[i] : elems[static_cast<size_type>(UINT8_C(0))]); }

    // Element manipulation members.
    constexpr auto fill(const value_type& value_in) -> void
    {
      std::fill(begin(), begin() + elem_count, value_in);
    }

    constexpr auto swap(dynamic_array& other) noexcept -> void
    {
      if(this != &other)
      {
        std::swap(elems, other.elems);
        std::swap(elem_count, other.elem_count);
        std::swap(my_alloc, other.my_alloc);
      }
    }

  private:
    size_type      elem_count { static_cast<size_type>(UINT8_C(0)) }; // NOLINT(readability-identifier-naming)
    pointer        elems      { nullptr };                            // NOLINT(readability-identifier-naming,altera-id-dependent-backward-branch)
    allocator_type my_alloc;                                          // NOLINT(readability-identifier-naming)

    friend constexpr auto operator==(const dynamic_array& lhs, const dynamic_array& rhs) -> bool
    {
      bool b_result { };

      if(lhs.empty())
      {
        b_result = rhs.empty();
      }
      else if(lhs.size() == rhs.size())
      {
        b_result = std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
      }
      // else b_result remains false

      return b_result;
    }

    friend constexpr auto operator<(const dynamic_array& lhs, const dynamic_array& rhs) -> bool
    {
      return
        std::lexicographical_compare
        (
          lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend()
        );
    }

    friend constexpr auto operator!=(const dynamic_array& lhs, const dynamic_array& rhs) -> bool { return (!(lhs == rhs)); }
    friend constexpr auto operator> (const dynamic_array& lhs, const dynamic_array& rhs) -> bool { return (rhs < lhs); }
    friend constexpr auto operator>=(const dynamic_array& lhs, const dynamic_array& rhs) -> bool { return (!(lhs < rhs)); }
    friend constexpr auto operator<=(const dynamic_array& lhs, const dynamic_array& rhs) -> bool { return (!(rhs < lhs)); }

    friend constexpr auto swap(dynamic_array& x, dynamic_array& y) noexcept -> void { x.swap(y); }
  };

  template<typename ValueType,
           const size_t MySize,
           typename AllocatorType = ::std::allocator<ValueType>>
  class fixed_dynamic_array;

  template<typename ValueType,
           const size_t MySize,
           typename AllocatorType>
  class fixed_dynamic_array final : public dynamic_array<ValueType, AllocatorType, size_t, ptrdiff_t> // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  private:
    using base_class_type = dynamic_array<ValueType, AllocatorType, size_t, ptrdiff_t>;

  public:
    // Type definitions.
    using typename base_class_type::allocator_type;
    using typename base_class_type::value_type;
    using typename base_class_type::reference;
    using typename base_class_type::const_reference;
    using typename base_class_type::iterator;
    using typename base_class_type::const_iterator;
    using typename base_class_type::pointer;
    using typename base_class_type::const_pointer;
    using typename base_class_type::size_type;
    using typename base_class_type::difference_type;
    using typename base_class_type::reverse_iterator;
    using typename base_class_type::const_reverse_iterator;

    static constexpr auto static_size() -> size_type { return MySize; }

    explicit constexpr fixed_dynamic_array(const size_type       size_in  = static_size(),
                                           const value_type&     value_in = value_type(),
                                           const allocator_type& alloc_in = allocator_type())
      : base_class_type(static_size(), value_in, alloc_in)
    {
      // This parameter is explicitly and purposely ignored.
      static_cast<void>(size_in);
    }

    constexpr fixed_dynamic_array(const fixed_dynamic_array&) = default;

    constexpr fixed_dynamic_array(fixed_dynamic_array&&) noexcept = default;

    constexpr fixed_dynamic_array(std::initializer_list<value_type> lst, const allocator_type& alloc_in  = allocator_type())
      : base_class_type(static_size(), size_type(), alloc_in)
    {
      std::copy
      (
        lst.begin(),
        lst.begin() + (std::min)(static_cast<size_type>(lst.size()), static_size()),
        base_class_type::data()
      );
    }

    template<typename InputIterator>
    constexpr fixed_dynamic_array(InputIterator first,
                                  InputIterator last,
                                  const allocator_type& alloc_in = allocator_type())
      : base_class_type(first, last, alloc_in) { }

    ~fixed_dynamic_array() override = default;

    constexpr auto operator=(const fixed_dynamic_array&) -> fixed_dynamic_array& = default;

    constexpr auto operator=(fixed_dynamic_array&& other) noexcept -> fixed_dynamic_array&
    {
      base_class_type::operator=(static_cast<base_class_type&&>(other));

      return *this;
    }
  };

  template<typename T>
  class tuple_size;

  template<typename ValueType,
           const size_t MySize,
           typename AllocatorType>
  class tuple_size<fixed_dynamic_array<ValueType, MySize, AllocatorType>> : public ::std::integral_constant<size_t, MySize> { };

  } // namespace util

#endif // UTIL_DYNAMIC_ARRAY_2012_05_16_H
