# Example Chapter10_08
# External SPI RAM and Computing 10,001 Digits of Pi

This advanced example extends available RAM via SPI SRAM chips
and uses a Pi Spigot algorithm to compute
<img src="https://render.githubusercontent.com/render/math?math=10,001">
decimal digits
of the mathematical
constant <img src="https://render.githubusercontent.com/render/math?math=\pi">,
showing fascinating memory management iterators,
containers and algorithms along the way.

This example depicts algorithmic complexity running in a real-world system
and highlights the real-time numeric expression of the detailed description
of algorithmic complexity in the corresponding book section.

# Application Description

The famous pi spigot algorithm is often used to compute
modestly small decimal digits of the mathematical constant
<img src="https://render.githubusercontent.com/render/math?math=\pi">.

A simple expression for a pi spigot algorithm for
<img src="https://render.githubusercontent.com/render/math?math=\pi">
is provided in Eq.~6.1, Sect.~6.1,
page 78 of Arndt and Haehnel [Pi Unleashed](https://www.springer.com/gp/book/9783642567353).

<img src="https://render.githubusercontent.com/render/math?math=\pi\,=\,2\,+\,\dfrac{1}{3}\Biggl(2\,+\,\dfrac{2}{5}\Biggl(2\,+\,\dfrac{3}{7}\Biggl(2\,+\,\ldots\Biggr)\Biggr)\Biggr)">,

This equation has been templated and extended in the pi spigot program
of our book. Consider, in particular, the code snippet
[chapter10_08-000_pi_spigot_single.cpp](../../code_snippets/chapter10/chapter10_08-000_pi_spigot_single.cpp).
Compiling and running this program as it stands produces the following output
(which may vary regarding timing of your system):

```
result_digit: 10001
result_test_pi_spigot_single_is_ok: true
elapsed time: 0.265s
operation_count: 19155868
input memory consumption: 137788

result_is_ok: true
```

Play around with this program. Switch from the default setting of
<img src="https://render.githubusercontent.com/render/math?math=10,001">
digits down to
<img src="https://render.githubusercontent.com/render/math?math=1,001">
digits or even up to
<img src="https://render.githubusercontent.com/render/math?math=100,001">
digits.
Watch the operation count and memory consumption vary with
size of the output digit count.

In this example, the pi spigot program has been adapted
to run on our target system with the 8-bit microcontroller.
In order to do so, two external serial SPI SRAM chips
have been used.

Memory allocation schemes and external SRAM iterators/containers
are described fully in the book. These have been used to
abstract memory access to the off-chip SRAMs
and allow the pi spigot program to run essentially out of the box.

For this particular example, a state-machine variation
of the single-state program is being used. The state-machine
variation divides the computation time of the individual
pi spigot operations among the time slices of the idle
task of the multitasking scheduler. The internal state
variables of the pi spigot calculation are stored
in static variables along the way as the state maching
consequently, iteratively and deliberately works its way
through the pi spigot calculation.

In the default release of this program, the pi spigot algorithm
is setup to compute
<img src="https://render.githubusercontent.com/render/math?math=10,001">
digits of
<img src="https://render.githubusercontent.com/render/math?math=\pi">.

# Hardware Setup

TBD
