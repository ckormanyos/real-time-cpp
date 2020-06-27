///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_PROGMEM_ARRAY_2019_05_04_H_
  #define MCAL_MEMORY_PROGMEM_ARRAY_2019_05_04_H_

  #include <algorithm>
  #include <cstddef>
  #include <iterator>
  #include <type_traits>

  #include <mcal_memory/mcal_memory_progmem_iterator.h>

  // Implement most an std::array-like container for read-only program memory.
  // See ISO/IEC 14882:2011 Chapter 23.3.2.

  namespace mcal { namespace memory { namespace progmem {

  template<typename T,
           const mcal_progmem_uintptr_t N>
  class array
  {
  private:
    static_assert(N > 0U, "error: Number of elements must exceed zero");

    static constexpr mcal_progmem_uintptr_t static_size = N;

  public:
    // Standard container-local type definitions.
    using const_iterator         = mcal::memory::progmem::progmem_iterator<T, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using size_type              = mcal_progmem_uintptr_t;
    using difference_type        = typename const_iterator::difference_type;
    using value_type             = typename const_iterator::value_type;
    using const_pointer          = typename const_iterator::pointer;
    using const_reference        = typename const_iterator::reference;

    const value_type elems[static_size];

    ~array() noexcept = default;

    const_iterator begin() const noexcept { return const_iterator(MCAL_PROGMEM_ADDRESSOF(elems[0U])); }
    const_iterator end  () const noexcept { return const_iterator(MCAL_PROGMEM_ADDRESSOF(elems[static_size])); }

    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend  () const noexcept { return end(); }

    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(MCAL_PROGMEM_ADDRESSOF(elems[static_size])); }
    const_reverse_iterator rend  () const noexcept { return const_reverse_iterator(MCAL_PROGMEM_ADDRESSOF(elems[0U])); }

    const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    const_reverse_iterator crend  () const noexcept { return rend(); }

    const_reference at(const size_type i) const noexcept
    {
      return *(cbegin() + difference_type(i));
    }

    const_reference operator[](const size_type i) const noexcept
    {
      return at(i);
    }

    const_reference front() const noexcept
    {
      return at(0U);
    }

    const_reference back() const noexcept
    {
      return at(static_size - 1U);
    }

    constexpr size_type size    () const noexcept { return static_size; }
    constexpr bool      empty   () const noexcept { return false; }
    constexpr size_type max_size() const noexcept { return static_size; }

    const_pointer data() const noexcept
    {
      return const_pointer(MCAL_PROGMEM_ADDRESSOF(elems[0U]));
    }
  };

  template<typename T, const mcal_progmem_uintptr_t N>
  bool operator==(const array<T, N>& left, const array<T, N>& right)
  {
    return std::equal(left.cbegin(), left.cend(), right.cbegin());
  }

  template<typename T, mcal_progmem_uintptr_t N>
  bool operator<(const array<T, N>& left, const array<T, N>& right)
  {
    return std::lexicographical_compare(left.cbegin(),
                                        left.cend(),
                                        right.cbegin(),
                                        right.end());
  }

  template<typename T, const mcal_progmem_uintptr_t N>
  bool operator!=(const array<T, N>& left, const array<T, N>& right)
  {
    return ((left == right) == false);
  }

  template<typename T, const mcal_progmem_uintptr_t N>
  bool operator>(const array<T, N>& left, const array<T, N>& right)
  {
    return (right < left);
  }

  template<typename T, const mcal_progmem_uintptr_t N>
  bool operator>=(const array<T, N>& left, const array<T, N>& right)
  {
    return ((left < right) == false);
  }

  template<typename T, const mcal_progmem_uintptr_t N>
  bool operator<=(const array<T, N>& left, const array<T, N>& right)
  {
    return ((right < left) == false);
  }

  template<typename T>
  struct tuple_size;

  template<typename T, const mcal_progmem_uintptr_t N>
  struct tuple_size<mcal::memory::progmem::array<T, N>>
    : public std::integral_constant<mcal_progmem_uintptr_t, N> { };

  template<const mcal_progmem_uintptr_t N, typename T>
  struct tuple_element;

  template<const mcal_progmem_uintptr_t I,
           typename T,
           const mcal_progmem_uintptr_t N>
  struct tuple_element<I, mcal::memory::progmem::array<T, N>>
  {
    static_assert(I < N, "Sorry, tuple_element index is out of bounds.");

    typedef T type;
  };

  } } } // namespace mcal::memory::progmem

#endif // MCAL_MEMORY_PROGMEM_ARRAY_2019_05_04_H_
