///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_21-001_rtti_typeinfo.cpp

#include <cstdint>
#include <cstring>
#include <iostream>
#include <typeinfo>

// Invent a simple, yet non-trivial
// structure for testing typeid().

struct test_typeid
{
  explicit test_typeid(const unsigned u = static_cast<unsigned>(UINT8_C(0)))
    : my_u(u) { static_cast<void>(my_u); }

  ~test_typeid() = default;

private:
  unsigned my_u { };
};

auto verify_typeid(const char* pn) -> bool;
auto do_something() -> void;

auto do_something() -> void
{
  // Create an instance of the struct.
  const test_typeid a(static_cast<unsigned>(UINT8_C(7)));

  // Obtain a const ref to the typeid of a.
  const std::type_info& tia = typeid(a);
  
  if(verify_typeid(tia.name()))
  {
    // tia.name() should be a constant
    // character string such as
    // "struct test_typeid" or similar,
    // depending on the compiler.
    
    // Do something that will not be
    // optimized away.
    ;
  }
}

auto main() -> int;

auto main() -> int
{
  do_something();
}

// Put this subroutine in a file that
// differs from the file calling it.
auto verify_typeid(const char* pn) -> bool
{
  std::cout << "pn: "
            << pn
            << ", compared with \"struct test_typeid\" (depending on compiler)"
            << std::endl;

  // Here, the actual text could be
  // "struct test_typeid" or similar,
  // depending on the compiler.

  const bool type_id_name_is_ok = (strcmp(pn, "struct test_typeid") == static_cast<int>(INT8_C(0)));

  return type_id_name_is_ok;
}
