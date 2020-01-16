
## These are the code snippets from the book "Real-Time C++".

See : C.M. Kormanyos, Real-Time C++: Efficient Object-Oriented
and Template Microcontroller Programming, Third Edition
(Springer, Heidelberg, 2018). ISBN 9783662567173

## Code Snippets

The code snippets are organized according to chapter
and section.

Each code snippet in intended to be a complete standalone
C++ project that compiles and runs on a PC. The code
snippets correspond to individual code samples in the
book but extend these in rudimentary ways to include
a main subroutine and usually some sensible short messages
to the output console.

Consider, for instance, the code snippet `chapter03_11-001_array.cpp`.

```
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_11-001_array.cpp

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <iterator>

// A login key stored in an std::array.
constexpr std::array<std::uint8_t, 3U> login_key
{
  {
    UINT8_C(0x01),
    UINT8_C(0x02),
    UINT8_C(0x03)
  }
};

int main()
{
  std::cout.unsetf(std::ios::dec);
  std::cout.setf(std::ios::hex);
  std::cout.setf(std::ios::showbase);

  std::cout << "login_key is ";
  std::copy(login_key.cbegin(), login_key.cend(), std::ostream_iterator<unsigned int>(std::cout, ","));
  std::cout << std::endl;
}
```

This code snippet portrays simple use of `std::array`.
An array named `login_key` is created and initialized
with the data bytes `1,2,3`. The bytes are printed to the
output console.

The expected message text is


```
login_key is 0x1,0x2,0x3,
```
