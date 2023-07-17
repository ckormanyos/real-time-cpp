# Example Chapter09_08a
## Controlling an RGB LED of type WS2812

Example chapter09_08a utilizes object oriented programming techniques
to control a sequential chain of eight industry-standard RGB LEDs of type ws2812

This example controls an RGB LED using programming techniques similar to those used in the previous example.
There are, however, several differences such as the refactored, modernized LED-class hierarchy.
The main difference, however, is that a _digitally_-controlled industry-standard
RGB LED of type WS2812 is used. In addition, the color transitions at (and around) $255~\text{bits}$-RGB
are slowed down providing emphasized, longer-lasting RGB hues near these points.

## Controlling the WS2812

The WS2812 RGB LED is controlled by a very specifically timed,
novel digital signal. In this signal, each of the $24$ RGB
color bits is set to the value $1$ or $0$ depending on the
half-width of a low/high signal pair.

In this example (as in most other examples), both a hardware
version for the target system as well as a simlulated PC
version are available. For this exercise, it was
decided to implement a rather detailed PC simulation
using old-school traditional Win32-API programming.

## Application Description

Color hues of RGB blend in a smooth fashion around the entire
spectrum to produce the appearance of slowly varying colors.
The user LED is simultaneously toggled at the usual $\frac{1}{2}~\text{Hz}$.

The full template signature of the `led_rgb_ws2812` class is shown below.

```cpp
  namespace mcal { namespace led {

  template<const std::uint8_t PortAddr,
           const std::uint8_t PortBpos,
           const unsigned LedCount = static_cast<unsigned>(UINT8_C(1))>
  class led_rgb_ws2812;
} } // namespace mcal::led
```

The first two template parameters `PortAddr` and `PortBpos`
are used to set the port address and bit position of the digital I/O port
used to generate the WS2812 control signal.

The third template parameter `LedCount` provides the ability
to link multiple WS2812 devices seqentially and control them
in an LED chain, as is common for this particular device.

In example chapter09_98a, a chain of eight WS2812 LED devices is used.

### Enhanced RGB-Color-Light-Show

The RGB-color-light-show in example chapter09_08a (this example)
differs slightly from the one in example chapter09_08 (the previous example).

In this example the color transitions are a bit lenghtier in time
($30~\text{ms}$ as opposed to $20~\text{ms}$). Also the color transitions
at and around $255~\text{bits}$-RGB
have been lengthened for color emphasis near the turning points.

This enhanced RGB-color-light-show can be found in the file
[`app_led.cpp`](./src/app/led/app_led.cpp).

### Windows Simulation

The chapter09_08a Win32-API simulation in its Windows-based
application is shown in action in the image below.

![](./images/rgb_led_wnd_09_08a.jpg)

## Hardware Setup

In this particular example, we have simply used a commercially-available
Arduino-Nano placed on a breadboard. The wiring is straightforward.

The hardware setup is pictured in the image below in action.
There picture shows a colorful aqua-blue hue eminating
from the sequential chain of bright RGB LEDs of type WS2812.

![](./images/board09_08a_green.jpg)
![](./images/board09_08a_blue.jpg)
