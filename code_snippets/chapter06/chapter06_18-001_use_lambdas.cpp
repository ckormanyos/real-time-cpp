///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_18-001_use_lambdas.cpp

#include <algorithm>
#include <iostream>

using function_type = void(*)();

extern function_type ctors_begin[];
extern function_type ctors_end  [];

void init_ctors()
{
  std::for_each(ctors_begin,
                ctors_begin + 3U,
                [](const function_type& pf)
                {
                  pf();
                });
}

int main()
{
  init_ctors();
}

void simulated_constructor1() { std::cout << "simulated_constructor1()" << std::endl; }
void simulated_constructor2() { std::cout << "simulated_constructor2()" << std::endl; }
void simulated_constructor3() { std::cout << "simulated_constructor3()" << std::endl; }

function_type ctors_begin[3U] =
{
  simulated_constructor1,
  simulated_constructor2,
  simulated_constructor3
};
