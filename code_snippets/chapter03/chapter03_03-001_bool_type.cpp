///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_03-001_bool_type.cpp

#include <iomanip>
#include <iostream>

auto valid() -> bool { return true; }
auto login() -> bool { return true; }

auto start_session() -> void { }

auto do_something() -> void
{
  // This Boolean test yields true or false.
  const bool session_is_ok { valid() && login() };

  // This tests if (session_is_ok == true).
  if(session_is_ok)
  {
    std::cout << "session_is_ok = " << std::boolalpha << session_is_ok << std::endl;

    start_session();

    std::cout << "start_session()" << std::endl;
  }
}

auto main() -> int
{
  do_something();
}
