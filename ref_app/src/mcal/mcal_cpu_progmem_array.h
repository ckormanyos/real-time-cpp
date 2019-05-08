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

  #include <mcal/mcal_cpu_progmem_iterator.h>

  #if defined(__GNUC__) || (defined(_MSC_VER) && (_MSC_VER >= 1900))
    #define MCAL_CPU_PROGMEM_CONSTEXPR constexpr
  #else
    #define MCAL_CPU_PROGMEM_CONSTEXPR const
  #endif

  // Implement most of std::array for compilers that do not yet support it.
  // See ISO/IEC 14882:2011 Chapter 23.3.2.

  namespace mcal { namespace cpu { namespace progmem {

  template<typename T, size_t N>
  class array
  {
  public:
    // Standard container-local type definitions.
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using value_type             = T;
    using const_pointer          = const value_type*;
    using const_reference        = const value_type;
    using const_iterator         = mcal::cpu::progmem::forward_iterator<const_pointer>;
    using const_reverse_iterator = mcal::cpu::progmem::reverse_iterator<const_pointer>;

    static MCAL_CPU_PROGMEM_CONSTEXPR size_type static_size = N;

    const value_type elems[static_size];

    ~array() = default;

    MCAL_CPU_PROGMEM_CONSTEXPR const_iterator begin() const { return const_iterator(elems); }
    MCAL_CPU_PROGMEM_CONSTEXPR const_iterator end  () const { return const_iterator(elems + static_size); }

    MCAL_CPU_PROGMEM_CONSTEXPR const_iterator cbegin() const { return begin(); }
    MCAL_CPU_PROGMEM_CONSTEXPR const_iterator cend  () const { return end(); }

    MCAL_CPU_PROGMEM_CONSTEXPR const_reverse_iterator rbegin() const { return const_reverse_iterator(elems + static_size); }
    MCAL_CPU_PROGMEM_CONSTEXPR const_reverse_iterator rend  () const { return const_reverse_iterator(elems); }

    MCAL_CPU_PROGMEM_CONSTEXPR const_reverse_iterator crbegin() const { return rbegin(); }
    MCAL_CPU_PROGMEM_CONSTEXPR const_reverse_iterator crend  () const { return rend(); }

    MCAL_CPU_PROGMEM_CONSTEXPR const_reference at(const size_type i) const
    {
      const bool index_is_in_range = ((empty() == false) && (i < static_size));

      const_reference value_at_index =
        (index_is_in_range ? *(cbegin() + difference_type(i)) : value_type());

      return value_at_index;
    }

    MCAL_CPU_PROGMEM_CONSTEXPR const_reference operator[](const size_type i) const
    {
      return at(i);
    }

    MCAL_CPU_PROGMEM_CONSTEXPR const_reference front() const
    {
      return at(0U);
    }

    MCAL_CPU_PROGMEM_CONSTEXPR const_reference back() const
    {
      return ((empty() == false) ? at(static_size - 1U) : value_type());
    }

    MCAL_CPU_PROGMEM_CONSTEXPR size_type size    () const { return  static_size; }
    MCAL_CPU_PROGMEM_CONSTEXPR bool      empty   () const { return (static_size == 0U); }
    MCAL_CPU_PROGMEM_CONSTEXPR size_type max_size() const { return  static_size; }

    MCAL_CPU_PROGMEM_CONSTEXPR const_iterator data() const
    {
      return const_iterator(elems);
    }

  private:
    array() = delete;
    array(const array&) = delete;
    array& operator=(const array&) = delete;
  };

  template<typename T, size_t N>
  bool operator==(const array<T, N>& left, const array<T, N>& right)
  {
    return std::equal(left.cbegin(), left.cend(), right.cbegin());
  }

  template<typename T, size_t N>
  bool operator<(const array<T, N>& left, const array<T, N>& right)
  {
    return std::lexicographical_compare(left.cbegin(),
                                        left.cend(),
                                        right.cbegin(),
                                        right.end());
  }

  template<typename T, size_t N>
  bool operator!=(const array<T, N>& left, const array<T, N>& right)
  {
    return ((left == right) == false);
  }

  template<typename T, size_t N>
  bool operator>(const array<T, N>& left, const array<T, N>& right)
  {
    return (right < left);
  }

  template<typename T, size_t N>
  bool operator>=(const array<T, N>& left, const array<T, N>& right)
  {
    return ((left < right) == false);
  }

  template<typename T, size_t N>
  bool operator<=(const array<T, N>& left, const array<T, N>& right)
  {
    return ((right < left) == false);
  }

  template<typename T>
  class tuple_size;

  template<typename T, typename std::size_t N>
  class tuple_size<mcal::cpu::progmem::array<T, N>>
    : public std::integral_constant<std::size_t, N> { };

  template<const std::size_t N, typename T>
  class tuple_element;

  template<const std::size_t I,
           typename T,
           const std::size_t N>
  class tuple_element<I, mcal::cpu::progmem::array<T, N>>
  {
    static_assert(I < N, "Sorry, tuple_element index is out of bounds.");

    typedef T type;
  };

  } } } // namespace mcal::cpu::progmem

#endif // MCAL_CPU_PROGMEM_ARRAY_2019_05_04_
