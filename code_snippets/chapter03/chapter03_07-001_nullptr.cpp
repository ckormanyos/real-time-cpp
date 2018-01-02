///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_07-001_nullptr.cpp

#include <iostream>

class something
{
public:
  something()
  {
    std::cout << "in ctor of something" << std::endl;
  }
};

namespace
{
  // Default initialized to nullptr (i.e., 0).
  something* ps;
}

void do_something()
{
  // Any kind of zero pointer equals nullptr.
  if(ps == nullptr)
  {
    // Initialize ps.
    ps = new something();
  }

  // Do something with ps.
  const bool initialization_is_ok = (ps != nullptr);

  static_cast<void>(initialization_is_ok);
}

int main()
{
  do_something();
}
