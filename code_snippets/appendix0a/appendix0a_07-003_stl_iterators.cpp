///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_07-003_stl_iterators.cpp

#include <array>
#include <iostream>

void do_something()
{
  using container_type = std::array<int, 3U>;

  using const_iterator_type =
    typename container_type::const_iterator;

  using iterator_type =
    typename container_type::iterator;

  container_type cnt = {{ 1, 2, 3 }};

        iterator_type nonconst_iterator  = cnt.begin();
  const_iterator_type    const_iterator1 = cnt.begin();
  const_iterator_type    const_iterator2 = cnt.cbegin();

  // Write of non-constant iterator is OK.
  *(nonconst_iterator) = 5;

  // Read of constant iterator is OK.
  int five_1 = *const_iterator1; // OK.
  int five_2 = *const_iterator2; // OK.

  // Write of constant iterator is not OK.
  //*(const_iterator1) = 5; // Error!

  // Write of constant iterator is not OK.
  //*(const_iterator2) = 5; // Error!

  std::cout << "five_1: " << five_1 << std::endl;
  std::cout << "five_2: " << five_2 << std::endl;
}

int main()
{
  do_something();
}
