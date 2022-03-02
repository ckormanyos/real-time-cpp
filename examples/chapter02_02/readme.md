# Example chapter02_02
# The LED program

This example implements the LED program (blinky) for the
target with the 8-bit microcontroller. This example has
originally been presented in the book with a homemade
microcontroller board. The project also runs and blinks
the LED on an Arduino board or an Arduino-compatible board.

Building the example can be done with command batch
or shell script. There is also CMake support.

The build executes several straightforward actions in
a very clear sequence of steps. In fact, to study this build
is a great way to gain introductory skills in manually
calling embedded tools and making more complicated builds
on your own in the future.

The results of the build will be stored in the `bin`
directory. After successful build, files such as the HEX-file
`led.hex` and othe name and map files can be found in `bin`.

The steps of the build include the following.

- Assemble : crt0.s  to bin/crt0.o
- Compile  : led.cpp to bin/led.o
- Link     : objects to bin/led.elf
- Extract  : executalbe hex file : from bin/led.elf
- Extract  : assembly list file  : from bin/led.elf
- Extract  : size information    : from bin/led.elf
- Extract  : name information    : from bin/led.elf
- Extract  : demangled names     : from bin/led.elf

# Blinking Frequency

In the LED program, the blinking is controlled directly
from the `main` subroutine of the program. The blinking
frequency will be as fast as the microcontroller can execute
the given toggle code, which will be too fast to resolve.

Use the commented out loop in the program to slow down
the blinking for easier observation. The commented out
loop is reproduced below within its contect in `main`.
It is the line starting with `for(volatile std::uint8_t delay`...).

```cpp
int main()
{
  // Toggle led_b5 in a loop forever.
  for(;;)
  {
    led_b5.toggle();

    // Some boards have a slower LED electrical
    // response on the port. Optionally activate
    // delay loop if LED toggle is not visible.
    //for(volatile std::uint8_t delay = UINT8_C(0); delay < UINT8_C(10); ++delay) { ; }
  }
}
```

# In `Win*`
The `Win*` batch file searches for a pre-installed instance
of the avr-g++ tool chain. 

When in `Win*`, building the Example chapter02_02 project can
accomplished in a cmd window. Use a command command such as
shown below, where the full path of the pre-installed 
gcc-avr is listed in its entirety.

```sh
build.bat "C:\Program Files (x86)\gcc-7.2.0-avr\bin" avr
```

# In `*nix`

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
