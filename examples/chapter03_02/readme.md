# Example chapter03_02
# Integer types having fixed widths and prime numbers

Example chapter03_02 focuses on integer types having fixed widths.
The example uses a fascinating calculation of prime numbers in order
to emphasize the use and portability of fixed-width integer types.

# Fixed-width integer types

The code below asserts that the 664,999th prime number is
10,006,721. THis integer is stored in a fixed width
unsigned integer variable having 32 bits. The storage
is of type constexpr, which is compile-time constant.

```
#include <cstdint>

// Initialize the 664,999th prime number.

constexpr std::uint32_t prime_664999 = UINT32_C(10’006’721);
```
# Blinking Frequency
