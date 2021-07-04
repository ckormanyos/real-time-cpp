# Example Chapter10_08 (advanced level):
# External SPI RAM and Computing 10,001 Digits of Pi

This advanced example extends available RAM via SPI SRAM chips
and uses a Pi Spigot algorithm to compute up to approximately
<img src="https://render.githubusercontent.com/render/math?math=10,001">
decimal digits of the mathematical
constant <img src="https://render.githubusercontent.com/render/math?math=\pi">,
showing fascinating memory management iterators,
containers and algorithms along the way.

This example depicts algorithmic complexity running in a real-world system.
It simultaneously highlights the real-time numeric expression
of the very detailed description of algorithmic complexity
in the corresponding book section.

# Application Description

The famous Pi Spigot algorithm is often used to compute
modestly small numbers of decimal digits of the mathematical constant
<img src="https://render.githubusercontent.com/render/math?math=\pi">.

A simple expression for a Spigot algorithm for
<img src="https://render.githubusercontent.com/render/math?math=\pi">
is provided in Eq. 6.1, Sect. 6.1,
page 78 of Arndt and Haenel's [Pi Unleashed](https://www.springer.com/gp/book/9783642567353).

<img src="https://render.githubusercontent.com/render/math?math=\pi\,=\,2\,+\,\dfrac{1}{3}\Biggl(2\,+\,\dfrac{2}{5}\Biggl(2\,+\,\dfrac{3}{7}\Biggl(2\,+\,\ldots\Biggr)\Biggr)\Biggr)">

This equation has been templated and extended in the Pi Spigot program
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

In the default release of this program, the Pi Spigot algorithm
is setup to compute
<img src="https://render.githubusercontent.com/render/math?math=10,001">
digits of
<img src="https://render.githubusercontent.com/render/math?math=\pi">.
Play around with this program. Switch from the default setting of
<img src="https://render.githubusercontent.com/render/math?math=10,001">
digits down to
<img src="https://render.githubusercontent.com/render/math?math=1,001">
digits or even up to
<img src="https://render.githubusercontent.com/render/math?math=100,001">
digits.
Watch the operation count and memory consumption vary with
size of the output digit count.

# 8-Bit MCU Adaptions

In this example, the Pi Spigot program has been adapted
to run on our target system with the 8-bit microcontroller.
In order to do so, two external serial SPI SRAM chips
have been used.

Memory allocation schemes and external SRAM iterators/containers
are described fully in the book. These have been used to
abstract memory access to the off-chip SRAMs
and allow the Pi Spigot program to run essentially out of the box.

For this particular example, a state-machine variation
of the single-state program is being used. The state-machine
variation divides the computation time of the individual
Pi Spigot operations among the time slices of the idle
task of the multitasking scheduler. The internal state
variables of the Pi Spigot calculation are stored
in static variables along the way as the state machine
consequently, iteratively and deliberately works its way
through the Pi Spigot calculation.

The program runs continuously, performing successive back-to-back
calculations, the subsequent one beginning when the previous one finishes.
Simultaneously, the well-known _blinky_ application with
1s blinking on/off is handled in the LED task.

Progress of the Pi Spigot calculation is reported in the
form of the duty cycle of a PWM signal, requiring an oscilloscope
to actually verify the calculation progress. A possible program extension
could mount an additional resistor/LED series combination
in order to view the calculation progress as LED brighness.

The default release of this example adapted to the 8-bit MCU
is set up for
<img src="https://render.githubusercontent.com/render/math?math=1,001">
decimal digits of
<img src="https://render.githubusercontent.com/render/math?math=\pi">.
The calculation requires approximately 100s in this configuration.

# Hardware Setup

Memory extension uses two serial SPI SRAM chips of type Microchip(R) 23LC1024.
Each chip has 1 Mbit (128 kByte) of asynchronous SRAM.
These 8-pin SRAM chips are straightforward to use.
They are controlled with easy-to-understand commands
that execute read/write operations in either single byte sequences
or small page bursts.

The <img src="https://render.githubusercontent.com/render/math?math=10,001">
decimal digit
The <img src="https://render.githubusercontent.com/render/math?math=\pi">
calculation requires approximately 140 kByte RAM.
Thus two 128 kByte chips are required
for the full
<img src="https://render.githubusercontent.com/render/math?math=10,001">
digit range intended for this example.

A tabulated, known control value containing
<img src="https://render.githubusercontent.com/render/math?math=\gtrsim\,10,011">
decimal digits of
<img src="https://render.githubusercontent.com/render/math?math=\pi">
is stored in the constant-valued, ROM-stored array variable
`local::control::sys_idle_pi_spigot_cntrl`. This control value
is used to check the calculated digits of
<img src="https://render.githubusercontent.com/render/math?math=\pi">
in this example.

The [all-software SPI driver](./src/mcal_spi/mcal_spi_software_port_driver.h)
communicates directly with the off-chip SRAM devices
via standard protocol described in the SRAM chip's manual(s).

Pinning in this example is summarized in the table below.

| Pin SRAM_0,1   |  SRAM Function | MCU Function | MCU Pin            |
| -------------- | -------------- | ------------ | ------------------ |
| 1 (SRAM_0)     |    CS_0        | `portc.4`    |       27           |
| 6 (SRAM_0)     |    SCK_0       | `portc.3`    |       26           |
| 2 (SRAM_0)     |    SO_0        | `portc.2`    |       25           |
| 5 (SRAM_0)     |    SI_0        | `portc.1`    |       24           |
| 1 (SRAM_1)     |    CS_1        | `portc.5`    |       28           |
| 6 (SRAM_1)     |    SCK_1       | `portc.3`    |  shared with SCK_0 |
| 2 (SRAM_1)     |    SO_1        | `portc.2`    |  shared with SO_0  |
| 5 (SRAM_1)     |    SI_1        | `portc.1`    |  shared with SI_0  |

The hardware setup is pictured in the image below.

![](./images/board10_08.jpg)
