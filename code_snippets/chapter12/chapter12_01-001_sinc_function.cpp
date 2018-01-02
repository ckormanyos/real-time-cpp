///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_01-001_sinc_function.cpp

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

float sinc(const float& x)
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

int main()
{
  // 1
  std::cout << std::setprecision(std::numeric_limits<float>::digits10)
            << sinc(1.0E-10F)
            << std::endl;

  // 0.999904
  std::cout << std::setprecision(std::numeric_limits<float>::digits10)
            << sinc(0.024F)
            << std::endl;

  // 0.664997
  std::cout << std::setprecision(std::numeric_limits<float>::digits10)
            << sinc(1.5F)
            << std::endl;
}
