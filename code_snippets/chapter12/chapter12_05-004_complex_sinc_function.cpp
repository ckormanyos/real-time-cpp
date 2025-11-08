///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_05-003_complex_sinc_function.cpp

#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace
{
  using local_complex_type = std::complex<float>;
}

auto sinc(const local_complex_type& z) -> local_complex_type
{
  if(std::abs(z) <
     std::numeric_limits<float>::epsilon())
  {
    return 1.0F;
  }
  else if(std::abs(z) < 0.03F)
  {
    const local_complex_type z2 { z * z };

    const local_complex_type sum
      = ((     - 1.984126984E-04F
          * z2 + 8.333333333E-03F)
          * z2 - 1.666666667E-01F)
          * z2;

    return 1.0F + sum;
  }
  else
  {
    return std::sin(z) / z;
  }
}

auto main() -> int;

auto main() -> int
{
  std::stringstream strm { };

  // (2.70868,-3.15559)
  strm << "sinc(local_complex_type(1.2F, 3.4F)): " << std::setprecision(std::numeric_limits<float>::digits10) << sinc(local_complex_type(1.2F, 3.4F)) << '\n';

  std::cout << strm.str() << std::endl;
}
