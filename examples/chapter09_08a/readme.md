# Example Chapter09_08a
# Controlling an RGB LED of type WS2812

Example chapter09_08a utilizes object oriented programming techniques
to control an RGB LED.

# Controlling the WS2812 RGB LED

This RGB LED is controlled by a very specifically timed,
novel digital signal. In this signal, each of the 24 RGB
color bits is set to the value 1 or zero depending on the
half-width of a low/high signal pair.

In this example (as in most other examples), both a hardware
version for the target system as well as a simlulated PC
version are available. For this exercise, it was
decided to implement a rather detailed PC simulation
using old-school traditional Win32-API programming.

# Application Description

Color hues of RGB blend in a smooth fashion around the entire
spectrum to produce the appearance of slowly varying colors.
The user LED is simultaneously toggled at the usual 1/2Hz.

The chapter09_08a Win32-API simulation in its Windows-based
application is shown in action in the image below.

![](./images/rgb_led_wnd_09_08a.jpg)

# Hardware Setup

In this particular example, we have simply used a commercially-available
Arduino-Nano placed on a breadboard. The wiring to the industry-standard
WS2812 RGB breakout board is simple and shown in the image below.

The hardware setup is pictured in the image below in action.
There are two pictures showing two different colors eminating
from the bright RGB LED of type WS2812.

![](./images/board09_08a_green.jpg)
![](./images/board09_08a_blue.jpg)
