///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019- 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_13-002_array_to_tuple.cpp

#include <array>
#include <iostream>
#include <sstream>
#include <tuple>
#include <utility>

template<typename array_type,
         unsigned... I>
constexpr auto array_to_tuple_helper(
  const array_type& a,
  std::index_sequence<I...>)
    -> decltype(auto)
{
  return std::make_tuple(1.0F * a[I]...);
}

template<typename T,
         const unsigned N,
         typename indices =
           std::make_index_sequence<N>>
constexpr auto
  array_to_tuple(const std::array<T, N>& a)
    -> decltype(auto)
{
  return array_to_tuple_helper(a, indices());
}

std::array<int, 4> a =
{{
  1, 2, 3, 4
}};

// Convert int array to float tuple.
// Here, the type of t is
// std::tuple<float, float, float, float>.
auto t = array_to_tuple(a);

auto main() -> int;

auto main() -> int
{
  std::stringstream strm { };

  strm << std::fixed << std::get<0>(t) << '\n';
  strm << std::fixed << std::get<1>(t) << '\n';
  strm << std::fixed << std::get<2>(t) << '\n';
  strm << std::fixed << std::get<3>(t) << '\n';

  std::cout << strm.str() << std::endl;
}
