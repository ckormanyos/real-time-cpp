# Example Chapter04_04
# LED Objects and Polymorphism

Example chapter04_04 uses an intuitive LED class hierarchy
to exemplify object oriented design and polymorphism.
In this example, five LEDs in total havind three individual kinds
of port control are toggled in near unison with a frequency
of approximately 1/2Hz.

# LED Classes

The class hierarchy consists of an LED base class called `pwm_base`
from which two LED classes are derived, `led_port` and `led_pwm`.
The port class `led_port` itself uses two kinds of ports,
one microcontroller port and three other ports on an external
serial SPI(TM) port axpander chip of type MICROCHIP(R) MCP23S17.
The PWM based LED is toggled via the dimming of the PWM duty cycle.

# Application Description

The application places five LED base class pointers in an
`std::array` and subsequently toggles them in a range-based
`for`-loop in the application task.

The LED base class pointers, for instance, are shown below.

```
std::array<mcal::led::led_base*, 5U> app_led_base_class_pointers =
{{
  mcal::led::led0(),
  mcal::led::led1(),
  mcal::led::led2(),
  mcal::led::led3(),
  mcal::led::led4()
}};
```

The application task performs the toggle functionality
at a frequency of approximately 1/2Hz using
dynamic polymorphism on the base class pointer list.

```
void app::led::task_func()
{
  if(app_led_timer.timeout())
  {
    app_led_timer.start_interval(app_led_one_sec);

    for(auto& p_led : app_led_base_class_pointers)
    {
      p_led->toggle();
    }

    app_led_state_is_on = (!app_led_state_is_on);
  }
}
```

# Hardware Setup

Here is the ![hardware setup](./images/board4.jpg).

In this example, we use ports from both the microcontroller as well
as an external port expaneder chip.

Some of the port connections are listed below:


