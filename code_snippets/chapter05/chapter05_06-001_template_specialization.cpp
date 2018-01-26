///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>

// chapter05_06-001_template_specialization.cpp

// The original add template function.
template<typename T>
T add(const T& a, const T& b)
{
  return a + b;
}

// Make template specializations of add() with
// easy-to-detect errors for float, double
// and long double.

template<>
float add<float>(const float&, const float&)
{
  // Explicitly create an erroneous result!
  return 0.0F;
}

template<>
double add<double>(const double&, const double&)
{
  // Explicitly create an erroneous result!
  return 0.0;
}

template<>
long double add<long double>(const long double&,
                             const long double&)
{
  // Explicitly create an erroneous result!
  return 0.0L;
}

int main()
{
  // 3
  std::cout << add(1, 2) << std::endl;

  // 0
  std::cout << add(1.0F, 2.0F) << std::endl;
}
