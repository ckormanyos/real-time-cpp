///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_ARRAY_2020_04_26_H_
  #define MCAL_MEMORY_SRAM_ARRAY_2020_04_26_H_

  #include <algorithm>
  #include <cstddef>
  #include <iterator>
  #include <type_traits>

  #include <mcal_memory/mcal_memroy_sram_iterator.h>

  // Implement most of std::array for read-only program memory.
  // See ISO/IEC 14882:2011 Chapter 23.3.2.

  namespace mcal { namespace memory { namespace sram {

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  class array
  {
  private:
    static_assert(N > 0U, "error: Number of elements must exceed zero");

    static constexpr mcal_sram_uintptr_t static_size = N;

  public:
    // Standard container-local type definitions.
    using iterator               = mcal::memory::sram::sram_iterator<T, mcal_sram_uintptr_t, mcal_sram_ptrdiff_t>;
    using const_iterator         = const iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = const reverse_iterator;
    using size_type              = mcal_sram_uintptr_t;
    using difference_type        = typename iterator::difference_type;
    using value_type             = typename iterator::value_type;
    using pointer                = typename iterator::pointer;
    using const_pointer          = const pointer;
    using reference              = typename iterator::reference;
    using const_reference        = const reference;

    constexpr array() noexcept = default;

    array(const array& other) noexcept
    {
      std::copy(other.cbegin(), other.cend(), begin());
    }

    array(array&& other) noexcept
    {
      std::copy(other.cbegin(), other.cend(), begin());
    }

    ~array() noexcept = default;

    array& operator=(const array& other) noexcept
    {
      if(this != &other)
      {
        std::copy(other.cbegin(), other.cend(), begin());
      }

      return *this;
    }

    array& operator=(array&& other) noexcept
    {
      std::copy(other.cbegin(), other.cend(), begin());

      return *this;
    }

    iterator begin() noexcept { return iterator(iterator(Address) + 0U); }
    iterator end  () noexcept { return iterator(iterator(Address) + static_size); }

    const_iterator begin() const noexcept { return const_iterator(iterator(Address) + 0U); }
    const_iterator end  () const noexcept { return const_iterator(iterator(Address) + static_size); }

    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend  () const noexcept { return end(); }

    reverse_iterator rbegin() noexcept { return reverse_iterator(iterator(Address) + static_size); }
    reverse_iterator rend  () noexcept { return reverse_iterator(iterator(Address) + 0U); }

    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(const_iterator(Address) + static_size); }
    const_reverse_iterator rend  () const noexcept { return const_reverse_iterator(const_iterator(Address) + 0U); }

    const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    const_reverse_iterator crend  () const noexcept { return rend(); }

    reference at(const size_type i) noexcept
    {
      return *(begin() + difference_type(i));
    }

    const_reference at(const size_type i) const noexcept
    {
      *(cbegin() + difference_type(i));
    }

    reference operator[](const size_type i) noexcept
    {
      return at(i);
    }

    const_reference operator[](const size_type i) const noexcept
    {
      return at(i);
    }

    reference front() noexcept
    {
      return at(0U);
    }

    const_reference front() const noexcept
    {
      return at(0U);
    }

    reference back() noexcept
    {
      return at(static_size - 1U);
    }

    const_reference back() const noexcept
    {
      return at(static_size - 1U);
    }

    constexpr size_type size    () const  noexcept{ return static_size; }
    constexpr bool      empty   () const  noexcept{ return false; }
    constexpr size_type max_size() const  noexcept{ return static_size; }

    pointer data() noexcept
    {
      return pointer(Address);
    }

    const_pointer data() const noexcept
    {
      return const_pointer(Address);
    }

    void fill(const T& value)
    {
      std::fill(begin(), end(), value);
    }
  };

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  bool operator==(const array<T, N, Address>& left, const array<T, N, Address>& right)
  {
    return std::equal(left.cbegin(), left.cend(), right.cbegin());
  }

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  bool operator<(const array<T, N, Address>& left, const array<T, N, Address>& right)
  {
    return std::lexicographical_compare(left.cbegin(),
                                        left.cend(),
                                        right.cbegin(),
                                        right.end());
  }

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  bool operator!=(const array<T, N, Address>& left, const array<T, N, Address>& right)
  {
    return ((left == right) == false);
  }

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  bool operator>(const array<T, N, Address>& left, const array<T, N, Address>& right)
  {
    return (right < left);
  }

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  bool operator>=(const array<T, N, Address>& left, const array<T, N, Address>& right)
  {
    return ((left < right) == false);
  }

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  bool operator<=(const array<T, N, Address>& left, const array<T, N, Address>& right)
  {
    return ((right < left) == false);
  }

  template<typename T>
  struct tuple_size;

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  struct tuple_size<mcal::memory::sram::array<T, N, Address>>
    : public std::integral_constant<mcal_sram_uintptr_t, N> { };

  } } } // namespace mcal::memory::sram

#endif // MCAL_MEMORY_SRAM_ARRAY_2020_04_26_H_
