///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_08-003_std_for_each.cpp

#include <iostream>

namespace std
{
  template<typename iterator_type,
           typename function_type>
  function_type for_each(iterator_type first,
                         iterator_type last,
                         function_type function)
  {
    while(first != last)
    {
      function(*first);

      ++first;
    }

    return function;
  }
}

int main()
{
  const unsigned a[3U] = { 1U, 2U, 3U };

  std::for_each(a,
                a + 3U,
                [](const unsigned & u)
                {
                  std::cout << u << std::endl;
                });
}
