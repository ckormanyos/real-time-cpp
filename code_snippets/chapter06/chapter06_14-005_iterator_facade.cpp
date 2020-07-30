///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_14-005_iterator_facade.cpp

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <numeric>

#define MY_PROGMEM

#include <boost/iterator/iterator_facade.hpp>

namespace mcal::cpu::progmem_boost {

template<class T>
class iterator
  : public boost::iterator_facade<typename iterator<T>,
                                  T,
                                  boost::random_access_traversal_tag,
                                  T,
                                  const std::ptrdiff_t>
{
private:
  using base_class_type = boost::iterator_facade<typename iterator<T>,
                                                 T,
                                                 boost::random_access_traversal_tag,
                                                 T,
                                                 const std::ptrdiff_t>;

  friend class boost::iterator_core_access;

public:
  explicit iterator(const typename base_class_type::value_type* p = nullptr)
    : current(p) { }

  iterator(const iterator& other)
    : current(other.current) { }

  virtual ~iterator() = default;

  iterator& operator=(const iterator& other)
  {
    if(this != &other)
    {
      current = other.current;
    }

    return *this;
  }

private:
  const typename base_class_type::value_type* current;

  void increment() { ++current; }

  void decrement() { --current; }

  void advance(const typename base_class_type::difference_type n)
  {
    current += n;
  }

  bool equal(const iterator& other) const
  {
    return (this->current == other.current);
  }

  typename base_class_type::value_type dereference() const
  {
    const typename base_class_type::value_type x = *current;

    return x;
  }
};

template <typename container_type> inline auto cbegin (const container_type& c) -> decltype(c.cbegin())  { return c.cbegin(); }
template <typename container_type> inline auto cend   (const container_type& c) -> decltype(c.cend())    { return c.cend(); }

template <typename container_type> inline auto crbegin(const container_type& c) -> decltype(c.crbegin()) { return c.crbegin(); }
template <typename container_type> inline auto crend  (const container_type& c) -> decltype(c.crend())   { return c.crend(); }

template <typename value_type, std::size_t N> inline const mcal::cpu::progmem_boost::iterator<value_type> cbegin (const value_type(&c_array)[N] MY_PROGMEM) { return mcal::cpu::progmem_boost::iterator<value_type>(&c_array[0U]); }
template <typename value_type, std::size_t N> inline const mcal::cpu::progmem_boost::iterator<value_type> cend   (const value_type(&c_array)[N] MY_PROGMEM) { return mcal::cpu::progmem_boost::iterator<value_type>(&c_array[N]); }

template <typename value_type, std::size_t N> inline const std::reverse_iterator<mcal::cpu::progmem_boost::iterator<value_type>> crbegin(const value_type(&c_array)[N] MY_PROGMEM) { return std::reverse_iterator<mcal::cpu::progmem_boost::iterator<value_type>>(&c_array[N]); }
template <typename value_type, std::size_t N> inline const std::reverse_iterator<mcal::cpu::progmem_boost::iterator<value_type>> crend  (const value_type(&c_array)[N] MY_PROGMEM) { return std::reverse_iterator<mcal::cpu::progmem_boost::iterator<value_type>>(&c_array[0U]); }

template<typename T, size_t N>
class array
{
public:
  // Standard container-local type definitions.
  using size_type              = std::size_t;
  using value_type             = T;
  using const_pointer          = const value_type*;
  using const_reference        = const value_type;
  using const_iterator         = progmem_boost::iterator<const_reference>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using difference_type        = typename const_iterator::difference_type;

  static constexpr size_type static_size = N;

  const value_type elems[static_size];

  ~array() = default;

  constexpr const_iterator begin() const { return const_iterator(elems); }
  constexpr const_iterator end  () const { return const_iterator(elems + static_size); }

  constexpr const_iterator cbegin() const { return begin(); }
  constexpr const_iterator cend  () const { return end(); }

  constexpr const_reverse_iterator rbegin() const { return const_reverse_iterator(elems + static_size); }
  constexpr const_reverse_iterator rend  () const { return const_reverse_iterator(elems); }

  constexpr const_reverse_iterator crbegin() const { return rbegin(); }
  constexpr const_reverse_iterator crend  () const { return rend(); }

  constexpr const_reference at(const size_type i) const
  {
    const bool index_is_in_range = ((static_size > 0U) && (i < static_size));

    const_reference value_at_index =
      (index_is_in_range ? *(cbegin() + difference_type(i)) : value_type());

    return value_at_index;
  }

  constexpr const_reference operator[](const size_type i) const
  {
    return at(i);
  }

  constexpr const_reference front() const
  {
    return at(0U);
  }

  constexpr const_reference back() const
  {
    return ((static_size > 0U) ? at(static_size - 1U) : value_type());
  }

  constexpr size_type size    () const { return   static_size; }
  constexpr bool      empty   () const { return ((static_size > 0U) == false); }
  constexpr size_type max_size() const { return   static_size; }

  constexpr const_iterator data() const
  {
    return const_iterator(elems);
  }
};

} // namespace mcal::cpu::progmem_boost

const std::uint8_t a[3U] MY_PROGMEM = { 1U, 2U, 3U };

int main()
{
  const std::uint8_t sum = std::accumulate(mcal::cpu::progmem_boost::cbegin(a),
                                           mcal::cpu::progmem_boost::cend  (a),
                                           UINT8_C(0));

  // 6
  std::cout << std::uint32_t(sum) << std::endl;
}
