///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_14-005_iterator_facade.cpp

// See also https://godbolt.org/z/PndaEn9de

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
  : public boost::iterator_facade<iterator<T>,
                                  T,
                                  boost::random_access_traversal_tag,
                                  T,
                                  const std::ptrdiff_t>
{
private:
  using base_class_type = boost::iterator_facade<iterator<T>,
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


} // namespace mcal::cpu::progmem_boost

const std::uint8_t a[static_cast<std::size_t>(UINT8_C(3))] MY_PROGMEM =
{
  static_cast<std::uint8_t>(UINT8_C(1)),
  static_cast<std::uint8_t>(UINT8_C(2)),
  static_cast<std::uint8_t>(UINT8_C(3))
};

auto main() -> int;

auto main() -> int
{
  const auto sum = std::accumulate(mcal::cpu::progmem_boost::cbegin(a),
                                   mcal::cpu::progmem_boost::cend  (a),
                                   static_cast<std::uint8_t>(UINT8_C(0)));

  // 6
  std::cout << static_cast<unsigned>(sum) << std::endl;
}
