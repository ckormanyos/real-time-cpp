///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_08-003_std_for_each.cpp

#include <array>
#include <iostream>

namespace non_std
{
  template<typename IteratorType,
           typename FunctionType>
  FunctionType for_each(IteratorType first,
                        IteratorType last,
                        FunctionType function)
  {
    while(first != last)
    {
      function(*first);

      ++first;
    }

    return function;
  }
}

auto main() -> int;

auto main() -> int
{
  const auto a =
    std::array<unsigned, static_cast<std::size_t>(UINT8_C(3))>
    {
      static_cast<unsigned>(UINT8_C(1)),
      static_cast<unsigned>(UINT8_C(2)),
      static_cast<unsigned>(UINT8_C(3))
    };

  using non_std::for_each;

  for_each(a.cbegin(),
           a.cend(),
           [](const unsigned & u)
           {
             std::cout << u << std::endl;
           });
}
