///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_10-003_metaprogram_inner_product.cpp

#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>

template<const std::size_t N,
         const std::size_t M = 0U>
struct inner_product
{
  template<typename iterator_left,
           typename iterator_right,
           typename result_type>
  static result_type sum(iterator_left u,
                         iterator_right v,
                         const result_type& init)
  {
    // Add (u[M] * v[M]) recursively.
    const result_type uvm
      = *(u + M) * result_type(*(v + M));

    return uvm
      + inner_product<N, M + 1U>::sum(u, v, init);
  }
};

template<const std::size_t N>
struct inner_product<N, N>
{
  template<typename iterator_left,
           typename iterator_right,
           typename result_type>
  static result_type sum(iterator_left,
                         iterator_right,
                         const result_type&)
  {
    // N'th specialization terminates the recursion.
    return result_type(0);
  }
};

int main()
{
  constexpr std::array<unsigned, 3U> u
  {
    { 1U, 2U, 3U }
  };

  constexpr std::array<unsigned, 3U> v
  {
    { 4U, 5U, 6U }
  };

  // The result is 32.
  const unsigned w =
    inner_product<3U>::sum(u.cbegin(),
                           v.cbegin(),
                           0U);

  std::cout << "Result of inner product is: " << w << std::endl;
}
