﻿# Example Chapter04_04
## LED Objects and Polymorphism

Example chapter04_04 uses an intuitive LED class hierarchy
to exemplify object oriented design and polymorphism.
In this example, five LEDs in total having three individual kinds
of port control are toggled in near unison with a frequency
of approximately $\frac{1}{2}~\text{Hz}$.

## LED Classes

The class hierarchy consists of an LED base class called
[`led_base`](https://github.com/ckormanyos/real-time-cpp/blob/master/examples/chapter04_04/src/mcal_led/mcal_led_base.h#L15).
It is located in namespace `mcal::led`. Two additional LED classes,
[`led_port`](https://github.com/ckormanyos/real-time-cpp/blob/master/examples/chapter04_04/src/mcal_led/mcal_led_port.h#L17)
and
[`led_pwm`](https://github.com/ckormanyos/real-time-cpp/blob/master/examples/chapter04_04/src/mcal_led/mcal_led_pwm.h#L16),
are derived from the LED base class.
These are used for the application's functionality.

The
[`led_port`](https://github.com/ckormanyos/real-time-cpp/blob/master/examples/chapter04_04/src/mcal_led/mcal_led_port.h#L17)
class itself utilizes two kinds of digital I/O-ports.
These include one microcontroller port and three other ports
located on an external
serial SPI port expander chip of type MICROCHIP(R) MCP23S17.

The port expander chip is controlled with SPI.
In this particular example, an all-software bus has been
developed using four microcontroller port pins toggled
manually. The SPI communication class
is derived from a
[`communication`](https://github.com/ckormanyos/real-time-cpp/blob/master/examples/chapter04_04/src/util/utility/util_communication.h#L20)
base class. It provides a uniform interface
for rudimentary byte-read and byte-write functions.

The PWM-based LED class controls its LED via dimming
its associated PWM duty cycle. Toggling is done by
adjusting the PWM duty cycle, switching
back-and-forth between $0\\%$ and $100\\%$.
There is one instantiation of this type of PWM-based LED class.

## Application Description

The application places five LED base class pointers in an
`std::array` and subsequently toggles them in a range-based
`for`-loop in the application task.
The array of LED base class pointers is shown in pseudo-code
below. It is a singleton-object found in the `app_led_base_class_array()`
subroutine.

```cpp
// ...

using app_led_type = mcal::led::led_base;

using app_led_array_type = std::array<app_led_type*, static_cast<std::size_t>(UINT8_C(5))>;

// ...

app_led_array_type& app_led_base_class_array()
{
  using namespace mcal::led;

  static app_led_array_type local_base_class_array
  {
    led0(), led1(), led2(), led3(), led4()
  };

  return local_base_class_array;
}
```

The application task performs the toggle functionality
at a frequency of approximately $\frac{1}{2}~\text{Hz}$ using
dynamic polymorphism on the elements stored
in the base class pointer container, as shown below.

```cpp
void app::led::task_func()
{
  if(app_led_timer.timeout())
  {
    app_led_timer.start_interval(app_led_one_sec);

    auto& local_base_class_array = app_led_base_class_array();

    for(app_led_type* p_led : local_base_class_array)
    {
      if(p_led != nullptr) { p_led->toggle(); }
    }

    app_led_state_is_on = (!app_led_state_is_on);
  }
}
```

## Hardware Setup

The five discrete LEDs in this example are fitted and setup
as shown in the following table.

| LED        | Port                        | Details                                                  |
| ---------- | --------------------------- | -------------------------------------------------------- |
| LED0       | microcontroller `portb.5`   | port toggle high/low, $750~\Omega$                       |
| LED1       | microcontroller `portb.1`   | `timer a`, PWM duty cycle $0~{\ldots}~100{\\%}$          |
| LED2       | port expander pin `GPA0`    | port toggle high/low, SPI software drive, $750~\Omega$   |
| LED3       | port expander pin `GPA1`    | port toggle high/low, SPI software drive, $750~\Omega$   |
| LED4       | port expander pin `GPA2`    | port toggle high/low, SPI software drive, $750~\Omega$   |

In this example, we use ports from both the microcontroller as well
as an external port expander chip. Hardware adressing is used
on the port expander chip. The port expander address is
hard-wired to the value 7 via connecting each of the three
pins `A0` ... `A2` to $+{5}~\text{V}$.

The connections of the port expander chip are tabulated below.

| Port Expander Pin | Expander Function | Connection                   |
| ----------------- | ----------------- | ---------------------------- |
|    9              | VDD               | $+{5}~\text{V}$              |
|    10             | VSS               | GND                          |
|    11             | CS (NOT)          | `portc.4`                    |
|    12             | SCK               | `portc.3`                    |
|    13             | SI                | `portc.1`                    |
|    14             | SO                | `portc.2`                    |
|    15             | A0                | $+{5}~\text{V}$              |
|    16             | A1                | $+{5}~\text{V}$              |
|    17             | A2                | $+{5}~\text{V}$              |
|    18             | RESET (NOT)       | $15~\text{k}\Omega$ to pullup over switch to GND |
|    21             | GPA0              | $750~\Omega$ to LED2         |
|    22             | GPA1              | $750~\Omega$ to LED3         |
|    23             | GPA2              | $750~\Omega$ to LED4         |

The hardware setup is pictured in the image below.

![](./images/board4.jpg)
