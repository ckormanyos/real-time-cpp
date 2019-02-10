///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_15-003_type_traits.cpp

#include <iostream>
#include <type_traits>

class integer_wrap
{
public:
  integer_wrap(const long long val = 0LL)
    : my_value(val) { }

  long long get_value() const
  {
    return my_value;
  }

private:
  long long my_value;
};

int main()
{
  integer_wrap iw(123LL);

  std::cout << "iw.get_value(): " << iw.get_value() << std::endl;
}
