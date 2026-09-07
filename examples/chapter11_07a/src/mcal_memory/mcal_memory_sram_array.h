///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_ARRAY_2020_04_26_H
  #define MCAL_MEMORY_SRAM_ARRAY_2020_04_26_H

#include <mcal_memory/mcal_memory_sram_iterator.h>

  #include <algorithm>
  #include <cstddef>
  #include <iterator>
  #include <type_traits>

  // Implement most of std::array for external SRAM memory.
  // See ISO/IEC 14882:2011 Chapter 23.3.2.

  namespace mcal { namespace memory { namespace sram {

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  class array
  {
  private:
    static constexpr mcal_sram_uintptr_t static_size = N;

  public:
    // Standard container-local type definitions.
    using iterator               = mcal::memory::sram::sram_iterator<T, mcal_sram_uintptr_t, mcal_sram_ptrdiff_t>;
    using const_iterator         = mcal::memory::const_address_ptr<sram_ptr<T, mcal_sram_uintptr_t, mcal_sram_ptrdiff_t>,
                                                                   sram_const_ref<T, mcal_sram_uintptr_t, mcal_sram_ptrdiff_t>>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using size_type              = mcal_sram_uintptr_t;
    using difference_type        = typename iterator::difference_type;
    using value_type             = typename iterator::value_type;
    using pointer                = sram_ptr<T, mcal_sram_uintptr_t, mcal_sram_ptrdiff_t>;
    using const_pointer          = mcal::memory::const_address_ptr<
      sram_ptr<T, mcal_sram_uintptr_t, mcal_sram_ptrdiff_t>,
      sram_const_ref<T, mcal_sram_uintptr_t, mcal_sram_ptrdiff_t>>;
    using reference              = typename iterator::reference;
    using const_reference        = const reference;

    constexpr array() noexcept = default;

    array(const array& other) noexcept
    {
      std::copy(other.cbegin(), other.cend(), begin());
    }

    array(array&&) noexcept = default;

    ~array() noexcept = default;

    array& operator=(const array& other) noexcept
    {
      if(this != &other)
      {
        std::copy(other.cbegin(), other.cend(), begin());
      }

      return *this;
    }

    auto operator=(array&&) noexcept -> array&
    {
      return *this;
    }

    auto begin() noexcept -> iterator { return iterator(iterator(Address) + 0U); }
    auto end  () noexcept -> iterator { return iterator(iterator(Address) + static_size); }

    auto begin() const noexcept -> const_iterator { return const_iterator(Address); }
    auto end  () const noexcept -> const_iterator { return const_iterator(Address) + static_size; }

    auto cbegin() const noexcept -> const_iterator { return begin(); }
    auto cend  () const noexcept -> const_iterator { return end(); }

    auto rbegin() noexcept -> reverse_iterator { return reverse_iterator(iterator(Address) + static_size); }
    auto rend  () noexcept -> reverse_iterator { return reverse_iterator(iterator(Address) + 0U); }

    auto rbegin() const noexcept -> const_reverse_iterator { return const_reverse_iterator(const_iterator(Address) + static_size); }
    auto rend  () const noexcept -> const_reverse_iterator { return const_reverse_iterator(const_iterator(Address) + 0U); }

    auto crbegin() const noexcept -> const_reverse_iterator { return rbegin(); }
    auto crend  () const noexcept -> const_reverse_iterator { return rend(); }

    auto at(const size_type i) noexcept -> reference
    {
      return *(begin() + difference_type(i));
    }

    auto at(const size_type i) const noexcept -> const_reference
    {
      return *(cbegin() + difference_type(i));
    }

    auto operator[](const size_type i) noexcept -> reference
    {
      return at(i);
    }

    auto operator[](const size_type i) const noexcept -> const_reference
    {
      return at(i);
    }

    auto front() noexcept -> reference
    {
      return at(0U);
    }

    auto front() const noexcept -> const_reference
    {
      return at(0U);
    }

    auto back() noexcept -> reference
    {
      return at(static_size - 1U);
    }

    auto back() const noexcept -> const_reference
    {
      return at(static_size - 1U);
    }

    constexpr size_type size    () const  noexcept{ return static_size; }
    constexpr bool      empty   () const  noexcept{ return (static_size == 0U); }
    constexpr size_type max_size() const  noexcept{ return static_size; }

    auto data() noexcept -> pointer
    {
      return pointer(Address);
    }

    auto data() const noexcept -> const_pointer
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
  auto operator==(const array<T, N, Address>& left, const array<T, N, Address>& right) -> bool
  {
    return std::equal(left.cbegin(), left.cend(), right.cbegin(),
                      [](const auto& x, const auto& y)
                      {
                        return x.value() == y.value();
                      });
  }

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  auto operator<(const array<T, N, Address>& left, const array<T, N, Address>& right) -> bool
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

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  auto operator!=(const array<T, N, Address>& left, const array<T, N, Address>& right) -> bool
  {
    return (!(left == right));
  }

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  auto operator>(const array<T, N, Address>& left, const array<T, N, Address>& right) -> bool
  {
    return (right < left);
  }

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  auto operator>=(const array<T, N, Address>& left, const array<T, N, Address>& right) -> bool
  {
    return (!(left < right));
  }

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  auto operator<=(const array<T, N, Address>& left, const array<T, N, Address>& right) -> bool
  {
    return (!(right < left));
  }

  template<typename T>
  struct tuple_size;

  template<typename T,
           const mcal_sram_uintptr_t N,
           const mcal_sram_uintptr_t Address>
  struct tuple_size<mcal::memory::sram::array<T, N, Address>>
    : public std::integral_constant<mcal_sram_uintptr_t, N> { };

  } } } // namespace mcal::memory::sram

#endif // MCAL_MEMORY_SRAM_ARRAY_2020_04_26_H
