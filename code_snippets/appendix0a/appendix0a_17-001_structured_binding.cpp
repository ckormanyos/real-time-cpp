///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_17-001_structured_binding.cpp

#include <algorithm>
#include <iostream>
#include <iterator>

// my_array is initialized to {0,1,2}.
unsigned int my_array[3U] = { 0U, 1U, 2U };

auto& [x0, x1, x2] = my_array;

// x0 is 0 and refers to my_array[0U].
// x1 is 1 and refers to my_array[1U].
// x2 is 2 and refers to my_array[2U].

void do_something()
{
  x0 += 5U;
  x1 += 5U;
  x2 += 5U;

  // x0, x1 and x2 have been incremented by 5.
  // In addition, my_array is now {5,6,7}.
}

int main()
{
  do_something();

  std::copy(std::cbegin(my_array),
            std::cend  (my_array),
            std::ostream_iterator<unsigned int>(std::cout, ","));

  std::cout << std::endl;
}
