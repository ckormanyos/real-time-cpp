# Example chapter02_06
# The Led Program (with template LED class)

This example implements the LED program with a template
LED class for the target with the 8-bit microcontroller.
This example is similar to Example chapter02_02,
but uses a template representation of the LED class
object that might be easier for the compiler to optimize.

Building the example can be done with the same commands
and batch file as example_02_02.

# Blinking Frequency

In the LED program with template LED class,
The blinking frequency will be as fast as the microcontroller
can execute the given toggle code, which will be too fast
to resolve.

The images below show the the template-based blinky LED
class running on a homemade target system.
A manually executed digital oscilloscope measurement is used
to capture the runtime of the port toggle.
The measurement shows a toggle runtime of approximately
310ns, which agrees with the claim in the book.

![Template -based blinky running on a homemade system](./images/measurement.pdf)

![Digital measurement](./images/2020-01-12.pdf)
