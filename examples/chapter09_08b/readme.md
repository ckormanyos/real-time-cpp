# Example Chapter09_08b (variation 32-bit microcontroller)
## Controlling an RGB LED of type ws2812

Example chapter09_08b utilizes essentially the same techniques
to control its ws2812 RGB LED as were used in Example Chapter09_08a.
In variation 09_08b, however, a 32-bit, single-core ARM(R) Cortex(R)-M3
microcontroller is used.

## Hardware Setup

In this particular example, we have simply used
the commercially-available, open-platform
[STM32F100 Value Line Discovery Kit](https://www.st.com/en/evaluation-tools/stm32vldiscovery.html)
with soldered-on pins fitted on a breadboard.

The wiring is straightforward. The blinking LED uses the blue colored
user LED controlled by pin `portc.8`. The LED digital control signal
is on `portb.9`. The microcontroller is clocked at $24~\text{MHz}$.
