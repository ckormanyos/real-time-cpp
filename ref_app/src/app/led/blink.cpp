#include <Arduino.h>

// Blink
// Turns an LED on for one second, then off for one second, repeatedly.

// the setup function runs once when you press reset or power the board
void setup(void);

void loop(void);

namespace
{
  constexpr int LED_BUILTIN = 2;
}

void setup(void)
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop(void)
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
