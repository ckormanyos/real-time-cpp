# Example chapter02_03a
# The LED program with cooperative multitasking scheduler

This example implements the LED program with
a tiny cooperative multitasking scheduler for the
target with the 8-bit microcontroller.
This example is similar to the previous example chapter02_03.
Example chapter02_03a, however, includes a tiny
cooperative multitasking scheduler for managing
the tasks that ultimately control the timing and delays
of the LED blinking. This example contains some techniques
that are described in later chapters of the book. It does,
however, provide intuitive insight at an early stage into
a more complete form of project.

Building the example can be done with GNUmake
in the command batch or shell script,
as is the case for all examples including and above
example chapter02_02. The results of the build will be stored
in the `bin` directory.

Project workspaces providing code visualization
and single-click build are provided for both
VC as well as Atmel Studio.

# Application Description

In the LED program with timing, the blinking is controlled
in the application task `app::led::task_func`
in the file `app_led.cpp`.

```cpp
void app::led::task_func()
{
  if(app_led_timer.timeout())
  {
    app_led_timer.start_interval(timer_type::seconds(1U));

    mcal::led::led0.toggle();
  }
}
```

The multitasking scheduler combined with utilities such as
timer and LED objects allow for convenient, intuitive
programming that is both straightforward to implement
as well as simple to comprehend. In this small snippet
from the application task, for instance it is intuitively
clear that Led0 is toggled once per second.

Cross development is also used. This means that
the application layer runs both on the PC as well
as in the embedded target. On the PC, the LED
toggle is expressed with text on the standard output
console, while the target system controls the actual
hardware used LED that is present on the board.
