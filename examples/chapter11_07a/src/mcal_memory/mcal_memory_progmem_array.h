///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_PROGMEM_ARRAY_2019_05_04_H
  #define MCAL_MEMORY_PROGMEM_ARRAY_2019_05_04_H

  #include <algorithm>
  #include <cstddef>
  #include <iterator>
  #include <type_traits>

  #include <mcal_memory/mcal_memory_progmem_iterator.h>

  // Implement most an std::array-like container for read-only program memory.
  // See ISO/IEC 14882:2011 Chapter 23.3.2.

  namespace mcal { namespace memory { namespace progmem {

  template<typename T,
           mcal_progmem_uintptr_t N>
  class array
  {
  private:
    static constexpr mcal_progmem_uintptr_t static_size = N;
    static constexpr mcal_progmem_uintptr_t storage_size = (N > 0U) ? N : 1U;

  public:
    // Standard container-local type definitions.
    using const_iterator         = mcal::memory::progmem::progmem_iterator<T, mcal_progmem_uintptr_t, mcal_progmem_ptrdiff_t>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using size_type              = mcal_progmem_uintptr_t;
    using difference_type        = typename const_iterator::difference_type;
    using value_type             = typename const_iterator::value_type;
    using const_pointer          = typename const_iterator::pointer;
    using const_reference        = typename const_iterator::reference;

    const value_type elems[storage_size];

    auto begin() const noexcept -> const_iterator { return const_iterator(MCAL_PROGMEM_ADDRESSOF(elems[0U])); }
    auto end  () const noexcept -> const_iterator { return begin() + difference_type(static_size); }

    auto cbegin() const noexcept -> const_iterator { return begin(); }
    auto cend  () const noexcept -> const_iterator { return end(); }

    auto rbegin() const noexcept -> const_reverse_iterator
    {
      return const_reverse_iterator(end());
    }

    auto rend() const noexcept -> const_reverse_iterator
    {
      return const_reverse_iterator(const_iterator(MCAL_PROGMEM_ADDRESSOF(elems[0U])));
    }

    auto crbegin() const noexcept -> const_reverse_iterator { return rbegin(); }
    auto crend  () const noexcept -> const_reverse_iterator { return rend(); }

    auto at(const size_type i) const noexcept -> const_reference
    {
      return *(cbegin() + difference_type(i));
    }

    auto operator[](const size_type i) const noexcept -> const_reference
    {
      return at(i);
    }

    auto front() const noexcept -> const_reference
    {
      return at(0U);
    }

    auto back() const noexcept -> const_reference
    {
      return at(static_size - 1U);
    }

    constexpr size_type size    () const noexcept { return static_size; }
    constexpr bool      empty   () const noexcept { return (static_size == 0U); }
    constexpr size_type max_size() const noexcept { return static_size; }

    auto data() const noexcept -> const_pointer
    {
      return const_pointer(MCAL_PROGMEM_ADDRESSOF(elems[0U]));
    }
  };

  template<typename T, mcal_progmem_uintptr_t N>
  auto operator==(const array<T, N>& left, const array<T, N>& right) noexcept -> bool
  {
    return std::equal(left.cbegin(), left.cend(), right.cbegin(),
                      [](const auto& x, const auto& y)
                      {
                        return x.value() == y.value();
                      });
  }

  template<typename T, mcal_progmem_uintptr_t N>
  auto operator<(const array<T, N>& left, const array<T, N>& right) noexcept -> bool
  {
    return std::lexicographical_compare(left.cbegin(),
                                        left.cend(),
                                        right.cbegin(),
                                         right.cend(),
                                        [](const auto& x, const auto& y)
                                        {
                                          return x.value() < y.value();
                                        });
  }

  template<typename T, const mcal_progmem_uintptr_t N>
  auto operator!=(const array<T, N>& left, const array<T, N>& right) noexcept -> bool
  {
    return (!(left == right));
  }

  template<typename T, const mcal_progmem_uintptr_t N>
  auto operator>(const array<T, N>& left, const array<T, N>& right) noexcept -> bool
  {
    return (right < left);
  }

  template<typename T, const mcal_progmem_uintptr_t N>
  auto operator>=(const array<T, N>& left, const array<T, N>& right) noexcept -> bool
  {
    return (!(left < right));
  }

  template<typename T, const mcal_progmem_uintptr_t N>
  auto operator<=(const array<T, N>& left, const array<T, N>& right) noexcept -> bool
  {
    return (!(right < left));
  }

  template<typename T>
  struct tuple_size;

  template<typename T, const mcal_progmem_uintptr_t N>
  struct tuple_size<mcal::memory::progmem::array<T, N>>
    : public std::integral_constant<mcal_progmem_uintptr_t, N> { };

  template<mcal_progmem_uintptr_t N, typename T>
  struct tuple_element;

  template<mcal_progmem_uintptr_t I,
           typename T,
           mcal_progmem_uintptr_t N>
  struct tuple_element<I, mcal::memory::progmem::array<T, N>>
  {
    static_assert(I < N, "Sorry, tuple_element index is out of bounds.");

    typedef T type;
  };

  } } } // namespace mcal::memory::progmem

  template<typename T, mcal_progmem_uintptr_t N>
  constexpr mcal_progmem_uintptr_t mcal::memory::progmem::array<T, N>::static_size;

  template<typename T, mcal_progmem_uintptr_t N>
  constexpr mcal_progmem_uintptr_t mcal::memory::progmem::array<T, N>::storage_size;

#endif // MCAL_MEMORY_PROGMEM_ARRAY_2019_05_04_H
