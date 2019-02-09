///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_08-001_stl_algorithms.cpp

#include <iostream>

namespace std
{
  // Declaration of template function std::for_each().
  template<typename iterator_type,
           typename function_type>
  function_type for_each(iterator_type first,
                         iterator_type last,
                         function_type function);
}

// Implementation of template function std::for_each().
template<typename iterator_type,
         typename function_type>
function_type std::for_each(iterator_type first,
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

int main()
{
  const int n3[] = { 1, 2, 3 };

  // Print each element of n3 using for_each
  // in combination with a lambda function.
  // Lambda functions are described in Sect. A9.
  std::for_each(n3,
                n3 + 3U,
                [](const int& n)
                {
                  std::cout << n << ",";
                });

  std::cout << std::endl;
}
