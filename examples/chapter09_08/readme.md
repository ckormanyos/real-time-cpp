# Example Chapter09_08
# Controlling an RGB LED

Example chapter09_08 utilizes object oriented programming techniques
to control an RGB LED.

# Controlling the RGB LED

In this example, three PWM signals are used to vary the duty cycles
of the red, green and blue hues of an RGB LED.
Current is drawn directly from the microcontroller ports.
The PWM signals are realized entirely in software with
an underlying tick derived from a timer interrupt that
runs every 50 microseconds.

In this example (as in most other examples), both a hardware
version for the target system as well as a simlulated PC
version are available. For this exercise, it was
decided to implement a rather detailed PC simulation
using old-school traditional Win32-API programming.

# Application Description

Color hues of RGB blend in a smooth fashion around the entire
spectrum to produce the appearance of slowly varying colors.
The user LED is simultaneously toggled at the usual 1/2Hz.

The chapter09_08 Win32-API simulation in its Windows-based
application is shown in action in the image below.

![](./images/rgb_led_wnd_09_08.jpg)
