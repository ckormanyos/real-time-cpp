///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_21-001_rtti_typeinfo.cpp

#include <cstring>
#include <iostream>
#include <typeinfo>

// Invent a simple, yet non-trivial
// structure for testing typeid().

struct test_typeid
{
  explicit test_typeid(const unsigned u)
    : my_u(u) { }

  ~test_typeid() = default;

private:
  unsigned my_u;
};

bool verify_typeid(const char* pn);

void do_something()
{
  // Create an instance of the struct.
  const test_typeid a(7U);

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

int main()
{
  do_something();
}

// Put this subroutine in a file that
// differs from the file calling it.
bool verify_typeid(const char* pn)
{
  std::cout << "pn: "
            << pn
            << ", compared with \"struct test_typeid\" (depending on compiler)"
            << std::endl;

  // Here, the actual text could be
  // "struct test_typeid" or similar,
  // depending on the compiler.

  const bool type_id_name_is_ok =
    (strcmp(pn, "struct test_typeid") == 0);

  return type_id_name_is_ok;
}
