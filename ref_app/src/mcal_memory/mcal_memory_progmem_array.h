///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_PROGMEM_ARRAY_2019_05_04_
  #define MCAL_CPU_PROGMEM_ARRAY_2019_05_04_

  #include <algorithm>
  #include <cstddef>
  #include <type_traits>

  #include <mcal_memory/mcal_memory_progmem_iterator.h>

  // Implement most of std::array for read-only program memory.
  // See ISO/IEC 14882:2011 Chapter 23.3.2.

  namespace mcal { namespace memory { namespace progmem {

  template<typename T, const mcal_progmem_uintptr_t N>
  class array
  {
  private:
    static constexpr mcal_progmem_uintptr_t static_size = N;

  public:
    // Standard container-local type definitions.
    using size_type              = mcal_progmem_uintptr_t;
    using const_iterator         = mcal::memory::progmem::forward_iterator<const T, size_type>;
    using const_reverse_iterator = mcal::memory::progmem::reverse_iterator<const_iterator>;
    using difference_type        = typename const_iterator::difference_type;
    using value_type             = typename const_iterator::value_type;
    using pointer                = typename const_iterator::pointer;
    using reference              = typename const_iterator::reference;

    const value_type elems[static_size];

    ~array() = default;

    const_iterator begin() const { return const_iterator(MCAL_PROGMEM_ADDRESSOF(elems[0U])); }
    const_iterator end  () const { return const_iterator(MCAL_PROGMEM_ADDRESSOF(elems[static_size])); }

    const_iterator cbegin() const { return begin(); }
    const_iterator cend  () const { return end(); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(MCAL_PROGMEM_ADDRESSOF(elems[static_size])); }
    const_reverse_iterator rend  () const { return const_reverse_iterator(MCAL_PROGMEM_ADDRESSOF(elems[0U])); }

    const_reverse_iterator crbegin() const { return rbegin(); }
    const_reverse_iterator crend  () const { return rend(); }

    const reference at(const size_type i) const
    {
      const bool index_is_in_range = ((empty() == false) && (i < static_size));

      const reference value_at_index =
        (index_is_in_range ? *(cbegin() + difference_type(i)) : value_type());

      return value_at_index;
    }

    const reference operator[](const size_type i) const
    {
      return at(i);
    }

    const reference front() const
    {
      return at(0U);
    }

    const reference back() const
    {
      return ((empty() == false) ? at(static_size - 1U) : value_type());
    }

    constexpr size_type size    () const { return  static_size; }
    constexpr bool      empty   () const { return (static_size == 0U); }
    constexpr size_type max_size() const { return  static_size; }

    const pointer data() const
    {
      return static_cast<const pointer>(MCAL_PROGMEM_ADDRESSOF(elems[0U]));
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
  class tuple_size;

  template<typename T, const mcal_progmem_uintptr_t N>
  class tuple_size<mcal::memory::progmem::array<T, N>>
    : public std::integral_constant<mcal_progmem_uintptr_t, N> { };

  template<const mcal_progmem_uintptr_t N, typename T>
  class tuple_element;

  template<const mcal_progmem_uintptr_t I,
           typename T,
           const mcal_progmem_uintptr_t N>
  class tuple_element<I, mcal::memory::progmem::array<T, N>>
  {
    static_assert(I < N, "Sorry, tuple_element index is out of bounds.");

    typedef T type;
  };

  } } } // namespace mcal::memory::progmem

#endif // MCAL_CPU_PROGMEM_ARRAY_2019_05_04_
