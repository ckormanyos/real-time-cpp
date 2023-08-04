Real-Time-C++ - Code Snippets
==================

<p align="center">
    <a href="https://github.com/ckormanyos/real-time-cpp/actions">
        <img src="https://github.com/ckormanyos/real-time-cpp/actions/workflows/real-time-cpp-snippets.yml/badge.svg" alt="Build Snippets"></a>
    <a href="https://github.com/ckormanyos/real-time-cpp/blob/master/LICENSE_1_0.txt">
        <img src="https://img.shields.io/badge/license-BSL%201.0-blue.svg" alt="Boost Software License 1.0"></a>
    <a href="https://godbolt.org/z/qfafePavo" alt="godbolt">
        <img src="https://img.shields.io/badge/try%20it%20on-godbolt-green" /></a>
</p>

These are the code snippets from the chapters of the book
C.M. Kormanyos,
[Real-Time C++](https://www.springer.com/de/book/9783662629956):
Efficient Object-Oriented
and Template Microcontroller Programming, Fourth Edition
(Springer, Heidelberg, 2021) ISBN 9783662629956.

## Summary of the Code Snippets

The code snippets are organized according to chapter
and section.

Each code snippet in intended to be a complete standalone
C++ project that compiles and runs on a PC host using
the host's compiler system such as MSVC on `Win*` or GCC on `*nix`.

The code snippets correspond to individual code samples in the
book but extend these in rudimentary ways to include
a main subroutine and usually some sensible short messages
to the output console.

Consider, for instance, the code snippet
[`chapter03_11-001_array.cpp`](https://github.com/ckormanyos/real-time-cpp/blob/master/code_snippets/chapter03/chapter03_11-001_array.cpp).

```cpp
// chapter03_11-001_array.cpp

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <iterator>

using login_key_array_type = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(3))>;

// A login key stored in an std::array.

constexpr auto login_key =
  login_key_array_type
  {
    static_cast<std::uint8_t>(UINT8_C(0x01)),
    static_cast<std::uint8_t>(UINT8_C(0x02)),
    static_cast<std::uint8_t>(UINT8_C(0x03))
  };

auto main() -> int
{
  const auto flg = std::cout.flags();

  std::cout.unsetf(std::ios::dec);
  std::cout.setf(std::ios::hex);
  std::cout.setf(std::ios::showbase);

  std::cout << "login_key is ";
  std::copy(login_key.cbegin(), login_key.cend(), std::ostream_iterator<unsigned int>(std::cout, ","));
  std::cout << std::endl;

  std::cout.flags(flg);
}
```

This code snippet portrays simple use of `std::array`.
An array named `login_key` is created and initialized
with the data bytes `1,2,3`. The bytes are printed to the
output console.

The expected output message text is

```sh
login_key is 0x1,0x2,0x3,
```

## Testing and CI

The code snippets have been tested locally on GCC, clang and MSVC.
CI for the code snippets runs with GCC and clang on `*nix`
using (at the moment) build-only.

## Try it at _godbolt_

<p align="center">
    <a href="https://godbolt.org/z/qfafePavo" alt="godbolt">
        <img src="https://img.shields.io/badge/try%20it%20on-godbolt-green" /></a>
</p>

Use this [short link](https://godbolt.org/z/qfafePavo)
to [godbolt](https://godbolt.org) in order to further explore this program.

In the afore-mentioned link, the file
[`chapter03_11-001_array.cpp`](https://github.com/ckormanyos/real-time-cpp/blob/master/code_snippets/chapter03/chapter03_11-001_array.cpp)
is, in fact, compiled with a modern GCC host-compiler.

This is an example of compiling, linking and running on a PC host.

To clearly reiterate: The file is actually compiled, linked and also executed.
This provides keen insight into both this particular code-snippet
as well as potential code and compiler exploration in your own domain(s).

In todays fast-paced, modern coding world,
it is fun, educational, exciting and effective to try out and share
code-snippets at [godbolt](https://godbolt.org)
