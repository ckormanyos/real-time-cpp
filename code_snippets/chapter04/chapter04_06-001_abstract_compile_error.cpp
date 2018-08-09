///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter04_06-001_abstract_compile_error.cpp

#include <cstdint>
#include <iostream>

class led_base
{
public:
  virtual void toggle() = 0; // Pure abstract.
  virtual ~led_base() { }    // Virtual destructor.

  // Interface for querying the LED state.
  bool state_is_on() const { return is_on; }

protected:
  bool is_on;

  // A protected default constructor.
  led_base() : is_on(false) { }

private:
  // Private non-implemented copy constructor.
  led_base(const led_base&) = delete;

  // Private non-implemented copy assignment operator.
  const led_base& operator=(const led_base&) = delete;
};

class led_no_toggle : public led_base
{
public:
  led_no_toggle()
  {
    // ...
  }

  // Does not have a toggle function.
  // Uncomment the toggle() function
  // to remove the compile error.

  //virtual void toggle()
  //{
  //  // Toggle the is_on indication flag.
  //  is_on = (!is_on);
  //
  //  // Show the PC simulated port LED.
  //  std::cout << "LED no toggle: ";
  //
  //  std::cout << (is_on ? "is on" : "is off") << std::endl;
  //}
};

namespace
{
  led_no_toggle led_no; // Compilation error!
}


void do_something()
{
  led_no.toggle();
}

int main()
{
  for(;;)
  {
    do_something();
  }
}
