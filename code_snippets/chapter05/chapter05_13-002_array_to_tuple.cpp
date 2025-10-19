///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019- 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_13-002_array_to_tuple.cpp

#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <tuple>
#include <utility>

template<typename array_type,
         std::size_t... I>
constexpr auto array_to_tuple_helper(
  const array_type& a,
  std::index_sequence<I...>)
    -> decltype(auto)
{
  return
    std::make_tuple(1.0F * static_cast<float>(a[I])...);
}

template<typename T,
         const std::size_t N,
         typename indices =
           std::make_index_sequence<N>>
constexpr auto
  array_to_tuple(const std::array<T, N>& a)
    -> decltype(auto)
{
  return array_to_tuple_helper(a, indices());
}

std::array<int, std::size_t { UINT8_C(4) }> a =
{{
  1, 2, 3, 4
}};

// Convert int array to float tuple.
// Here, the type of tpl is
// std::tuple<float, float, float, float>.
auto tpl { array_to_tuple(a) };

auto main() -> int;

auto main() -> int
{
  std::stringstream strm { };

  strm << std::fixed << std::get<0>(tpl) << '\n';
  strm << std::fixed << std::get<1>(tpl) << '\n';
  strm << std::fixed << std::get<2>(tpl) << '\n';
  strm << std::fixed << std::get<3>(tpl) << '\n';

  std::cout << strm.str() << std::endl;
}
