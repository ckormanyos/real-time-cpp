///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// appendix0a_15-004_type_traits.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <type_traits>

class integer_wrap
{
public:
  template
  <typename integral_type,
   typename std::enable_if
     <std::is_integral<integral_type>::value>::type* =
        nullptr>
  integer_wrap(const integral_type val = 0)
    : my_value(static_cast<long long>(val)) { }

  long long get_value() const
  {
    return my_value;
  }

private:
  long long my_value;
};

int main()
{
  integer_wrap a(char('a'));
  integer_wrap u(std::uint16_t(0x5555U));
  integer_wrap n(1234);

  std::cout << "a.get_value(): " << char(a.get_value()) << std::endl;
  std::cout << "u.get_value(): 0x" << std::hex << u.get_value() << std::endl;
  std::cout << "n.get_value(): " << std::dec << n.get_value() << std::endl;
}
