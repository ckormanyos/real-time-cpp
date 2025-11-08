///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter12_05-003_complex.cpp

#include <complex>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

auto main() -> int;

auto main() -> int
{
  std::complex<float> z { }; // (0 + 0 I)

  z.real(1.23F); // Set the real part.
  z.imag(3.45F); // Set the imag part.

  const float zr { z.real() }; // Get the real part, 1.23.
  const float zi { z.imag() }; // Get the imag part, 3.45.

  static_cast<void>(zr);
  static_cast<void>(zi);

  const float nz { std::norm(z) }; // 13.4154

  std::stringstream strm { };

  strm << "nz: " << std::setprecision(std::numeric_limits<float>::digits10) << nz << '\n';

  std::cout << strm.str() << std::endl;
}
