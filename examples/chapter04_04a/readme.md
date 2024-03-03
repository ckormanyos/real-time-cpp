# Example Chapter04_04a
## LED Objects and Polymorphism via References

Example chapter04_04a implements the same basic functionality
as does example chapter04_04. Example chapter04_04a, however,
uses an `std::array` of LED base class references instead
of base class pointers in order to exercise object oriented polymorphism.

## Application Description

The LED base class references are stored within template
instances of `std::reference_wrapper` from the `<functional>` library.
This is because C++ can not store references in STL containers such as
`std::array`.

The container of wrapped LED base class references is shown in pseudo-code
below. It is a singleton-object in the `app_led_base_class_array()`
subroutine.

```cpp
// ...

  using app_led_type = mcal::led::led_base;

  using app_led_array_type = std::array<std::reference_wrapper<app_led_type>, static_cast<std::size_t>(UINT8_C(5))>;

// ...

app_led_array_type& app_led_base_class_array()
{
  static app_led_array_type local_base_class_array
  {
    mcal::led::led0(),
    mcal::led::led1(),
    mcal::led::led2(),
    mcal::led::led3(),
    mcal::led::led4()
  };

  return local_base_class_array;
}
```

The elements in the array of LED base class references
are toggled in the application task each second in the following
fashion.

```cpp
void app::led::task_func()
{
  if(app_led_timer.timeout())
  {
    app_led_timer.start_interval(app_led_one_sec);

    auto& local_base_class_array = app_led_base_class_array();

    for(app_led_type& led : local_base_class_array)
    {
      led.toggle();
    }

    app_led_state_is_on = (!app_led_state_is_on);
  }
}
```

## Hardware Setup

The hardware setup used here in example chapter04_04a can be
exactly the same as that used in example
[chapter04_04](https://github.com/ckormanyos/real-time-cpp/tree/master/examples/chapter04_04).
