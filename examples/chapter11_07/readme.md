# Example Chapter11_07
## Preemptive Multitasking

This example makes straightforward use
of preemptive multitasking scheduling with a blinky-style application
that features a main task and a low-priority background task.

## Application Description

This example features two preemptive tasks within a multitasking envoronment.
The application task supports the _blinky_ functionality with LED on/off each 1s.
The application task has higher priority and also yields every $125~\text{ms}$.
The second task is a background task. It runs continuously,
without cooperative yield. The background task, however,
by virtue of having lower task priority will be interrupted
by the higher priority application task. The background task
toggles a second LED on `portd.3` every $50~\text{ms}$
resulting in a frequency of approximately $10~\text{Hz}$.

These days there are numerous choices available when selecting
OS-es and/or multitasking schedulers for embedded systems.
Choices include a variety of either commercially available,
free-ware or even self-written options. In this particular
expression of Example Chapter11_07, we select
[FreeRTOS](https://www.freertos.org).

The task setup, initialization and task functions
have been wrapped in convenient, OS-independent macros
and function calls. This provides a lightweight layer
of portability on top of otherwise potentially OS-specific
mechanisms and methods.

The tasks are summarized in the code snippet below.

```cpp
extern "C"
void app_led_task_background(void*)
{
  // This background task runs perpetually without pause, break or yield
  // This task has lowest priority and will be interrupted by any other
  // task having higher priority, such as the LED 1/2 Hz toggle task
  // (i.e., app_led_timer_toggle_led0).

  for(;;)
  {
    while((!app_led_timer_background.timeout()))
    {
      mcal::cpu::nop();
    }

    app_led_timer_background.start_interval(app_led_timer_type::milliseconds(app_led_tick_type { UINT8_C(50) }));

    // Toggle led1 every 50ms.

    mcal::led::led1().toggle();
  }
}

extern "C"
void app_led_task_toggle_led0(void*)
{
  // When using FreeRTOS, this task has higher priority than
  // the background task. Due to its higher task-priority,
  // this task is, in fact, intended to preemptively interrupt
  // the lower-priority background task.

  // If using the simulated host (such as _MSC_VER or GCC on x86_64),
  // FreeRTOS is not used, but rather the C++ <thread> and <chrono>
  // libraries are used for simulated task scheduling. The <thread>
  // library does not use adjustable priorities in this case, but the
  // thread scheduler supports preemptive scheduling and emulates
  // the desired timing quite well.

  for(;;)
  {
    mcal::wdg::secure::trigger();

    // Toggle led0 every 1s.

    if(app_led_timer_toggle_led0.timeout())
    {
      app_led_timer_toggle_led0.start_interval(app_led_timer_type::seconds(app_led_tick_type { UINT8_C(1) }));

      mcal::led::led0().toggle();
    }

    // This application task is programmed to yield every 125ms.

    OS_TASK_WAIT_YIELD(TickType_t { UINT8_C(125) });
  }
}
```

The OS requires minimal context-switching and timer portions.
These are typically ported in processor-specific C/C++/assembly sources.
The port for the ATmega328P target can be found in
[port.cpp](./src/os/FreeRTOS/Source/portable/GCC-ATMega328/port.cpp).
This OS-portable part has been modified for this example
via changes including switching from a C to a C++ file,
cleaning up spaces, tabs and alignment of typing.
The OS tick uses `compare-match-a` from `timer1` to generate
a tick interrupt at $100~\text{Hz}$ (i.e., approximately every $10~\text{ms}$)
using an undecorated ISR handle named `__vector_11`.

When using the simulated host (such as `_MSC_VER` or GCC on `x86_64`),
FreeRTOS is not used, but rather the C++ `<thread>` and `<chrono>` libraries
are used for simulated task scheduling. The `<thread>` library
does not use adjustable priorities in this case, but the thread scheduler
supports preemptive scheduling and emulates the desired timing quite well.

## Hardware Setup

An example of a simple, self-made target hardware running
Example Chapter11_07 is shown in the image below.
The blinky LED 1s on/off can be found on `portb.5`.
The background $10~\text{Hz}$ toggle pin can be found on `portd.3`.

![](./images/board11_07.jpg)

The oscilloscope image below captures the toggle cycle
of the LED in the background task at a frequency
of approximately $10~\text{Hz}$

![](./images/scope11_07.jpg)
