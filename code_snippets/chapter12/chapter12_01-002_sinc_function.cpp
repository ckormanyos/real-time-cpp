///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_01-002_sinc_function.cpp

#include <cmath>
#include <limits>
#include <iomanip>
#include <iostream>
#include <sstream>

auto sinc(const float& x) -> float
{
  if(std::fabs(x) <
     std::numeric_limits<float>::epsilon())
  {
    return 1.0F;
  }
  else if(std::fabs(x) < 0.03F)
  {
    const float x2 = x * x;
    
    const float sum = ((     - 1.984126984E-04F
                        * x2 + 8.333333333E-03F)
                        * x2 - 1.666666667E-01F)
                        * x2;

    return 1.0F + sum;
  }
  else
  {
    return std::sin(x) / x;
  }
}

auto main() -> int;

auto main() -> int
{
  std::stringstream strm { };

  // N[Sin[1/64]/(1/64), 12]
  // N[Sin[1/8]/(1/8), 12]
  // N[Sin[5/4]/(5/4), 12]

  strm << "sinc(0.015625F): " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10) << sinc(0.0078125F) << '\n';
  strm << "sinc(0.125F)   : " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10) << sinc(0.125F) << '\n';
  strm << "sinc(1.25F)    : " << std::fixed << std::setprecision(std::numeric_limits<float>::digits10) << sinc(1.25F) << '\n';

  std::cout << strm.str() << std::endl;
}
