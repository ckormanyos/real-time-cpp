# Example chapter02_02
## The LED program

<p align="center">
    <a href="https://godbolt.org/z/fxWzb6h6f" alt="godbolt">
        <img src="https://img.shields.io/badge/try%20it%20on-godbolt-green" /></a>
</p>

This example implements the LED program (blinky) for the
target with the 8-bit microcontroller. This example has
originally been presented in the book with a homemade
microcontroller board. The project also runs and blinks
the LED on an Arduino board or an Arduino-compatible board.

Building the example can be done with command batch
or shell script. There is also CMake support.

The build executes several straightforward actions in
a very clear sequence of steps.

Working through this build
is, in fact, a great way to gain introductory skills in manually
calling embedded tools. It is intended to help you learn how
to make more complicated builds on your own in the future.

The results of the build will be stored in the `bin`
directory. After successful build, files such as the HEX-file
`led.hex` and other associated useful _symbol_-_name_ and _map_ files
can be found in `bin`.

The steps of the build include the following.

- <code>Assemble : crt0.s  to bin/crt0.o</code>
- <code>Compile  : led.cpp to bin/led.o</code>
- <code>Link     : objects to the absolute object file bin/led.elf</code>
- <code>Extract  : executalbe hex file      : from bin/led.elf</code>
- <code>Extract  : assembly list file       : from bin/led.elf</code>
- <code>Extract  : size information         : from bin/led.elf</code>
- <code>Extract  : symbol name information  : from bin/led.elf</code>
- <code>Extract  : (demangled) c++ names    : from bin/led.elf</code>

## Blinking Frequency

In the LED program, the blinking is controlled directly
from the `main` subroutine of the program. The blinking
frequency will be as fast as the microcontroller can execute
the given toggle code, which will be too fast to resolve.

The core of the LED program is listed below.
  - Note: The program listing here has been slightly _modernized_ compared to the program listing in the book.

```cpp
#include <cstdint>

#include "mcal_reg.h"

class led
{
public:
  // Use convenient class-specific typedefs.
  using port_type = std::uint8_t;
  using bval_type = std::uint8_t;

  // The led class constructor.
  explicit led(const port_type p, const bval_type b)
    : port(p),
      bval(b)
  {
    // Set the port pin value to low.
    *reinterpret_cast<volatile bval_type*>(port) &= static_cast<bval_type>(~bval);

    // Set the port pin direction to output.

    // Note that the address of the port direction
    // register is one less than the address
    // of the port value register.
    const auto pdir = static_cast<port_type>(port - 1U);

    *reinterpret_cast<volatile bval_type*>(pdir) |= bval;
  }

  auto toggle() const -> void
  {
    // Toggle the LED via direct memory access.
    *reinterpret_cast<volatile bval_type*>(port) ^= bval;
  }

private:
  // Private member variables of the class.
  const port_type port;
  const bval_type bval;
};

namespace
{
  // Create led_b5 on portb.5.
  auto led_b5 =
    led
  {
    mcal::reg::portb,
    mcal::reg::bval5
  };
}
```

Use the commented out loop in the program to slow down
the blinking for easier observation. The commented out
loop is reproduced below within its contect in `main`.
It is the line starting with `for(volatile std::uint8_t delay`...).

```cpp
auto main() -> int
{
  // Toggle led_b5 in a loop forever.
  for (;;)
  {
    led_b5.toggle();

    // Some boards have a slower LED electrical
    // response on the port. Optionally activate
    // delay loop if LED toggle is not visible.
    //for(volatile std::uint8_t delay = UINT8_C(0); delay < UINT8_C(10); ++delay) { ; }
  }
}
```

## In `Win*`
The `Win*` batch file searches for a pre-installed instance
of the avr-g++ tool chain. 

When in `Win*`, building the Example chapter02_02 project can
accomplished in a cmd window. Use a command command such as
shown below, where the full path of the pre-installed 
gcc-avr is listed in its entirety.

```DOS
build.bat "C:\Program Files (x86)\gcc-11.2.0-avr\bin" avr
```

## In `*nix`

On `*nix`-like systems, gcc-avr can be installed from a package manager.
A common example is shown below.

```sh
apt-get install gcc-avr avr-libc
```

Building the Example chapter02_02 project can be done with a bash shell
such as:

```sh
## bash will typically use dirname, so this might be equivalent to: ./build.sh /usr/bin avr
./build.sh "$(dirname $(which avr-g++))" avr
```

## Try it at _godbolt_

Use the following [short link](https://godbolt.org/z/v5f45fMqq)
to [godbolt](https://godbolt.org) in order to further explore this program.

In the afore-mentioned link, the file [`led.cpp`](./led.cpp) is,
in fact, compiled with a modern `avr-gcc`.
Of course, the file can be compiled and linked there,
but not executed because there is no target hardware available.

### On the Metal: _Clear_ and _Set_ Bit

Consider the assembly output near the bottom of the page in the right-side tab
of the [short link](https://godbolt.org/z/v5f45fMqq)
to [godbolt](https://godbolt.org). Upon close investigation,
the bit-_clear_ and bit-_set_ opcodes (`cbi` and `sbi`)
can be recognized.

These opcodes are responsible for actually toggling the mocrocontroller's
port pin `portb.5`.
