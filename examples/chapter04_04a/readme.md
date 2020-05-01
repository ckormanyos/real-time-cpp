# Example Chapter04_04a
# LED Objects and Polymorphism via References

Example chapter04_04a implements the same basic functionality
as does example chapter04_04. Example chapter04_04a, however,
uses an `std::array` of LED base class references instead
of base class pointers in order to exercise object oriented polymorphism.

# Application Description

The LED base class references are stored within template
instances of `std::reference_wrapper` from the `<functional>` library.
This is because C++ can not store references in STL containers such as
`std::array`.

The container of wrapped LED base class references looks
like this:

```
#include <functional>

// ...

using app_led_ref_type = std::reference_wrapper<mcal::led::led_base>;

std::array<app_led_ref_type, 5U> app_led_base_class_refs =
{{
  mcal::led::led0(),
  mcal::led::led1(),
  mcal::led::led2(),
  mcal::led::led3(),
  mcal::led::led4()
}};
```

The elements in the array of LED base class references
are toggled in the application task each second in the following
fashion.

```
void app::led::task_func()
{
  if(app_led_timer.timeout())
  {
    app_led_timer.start_interval(app_led_one_sec);

    for(typename app_led_ref_type::type& led : app_led_base_class_refs)
    {
      led.toggle();
    }

    app_led_state_is_on = (!app_led_state_is_on);
  }
}
```

# Hardware Setup

The hardware setup for example chapter04_04a is the same as that of
example chapter04_04.
