#ifndef MCAL_LED_CONSOLE_2020_04_23_H_
  #define MCAL_LED_CONSOLE_2020_04_23_H_

  #include <cstdint>
  #include <iostream>

  #include <mcal_led/mcal_led_base.h>

  namespace mcal { namespace led {

  class led_console final : public mcal::led::led_base
  {
  public:
    led_console(const std::uint_fast8_t i = 0)
      : index(i),
        is_on(false) { }

    virtual ~led_console() = default;

    virtual void toggle()
    {
      // Toggle the LED state.
      is_on = (!is_on);

      // Print the LED state.
      std::cout << "LED"
                << unsigned(index)
                << " is "
                << (is_on ? "on" : "off")
                << std::endl;
    }

  private:
    const std::uint_fast8_t index;
    bool is_on;

    virtual bool state_is_on() const { return is_on; }
  };

  } } // namespace mcal::led

#endif // MCAL_LED_CONSOLE_2020_04_23_H_
