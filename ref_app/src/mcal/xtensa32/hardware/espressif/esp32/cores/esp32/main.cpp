#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_task_wdt.h>
#include <Arduino.h>

#ifndef CONFIG_ARDUINO_LOOP_STACK_SIZE
#define CONFIG_ARDUINO_LOOP_STACK_SIZE 8192
#endif

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

TaskHandle_t loopTaskHandle = nullptr;

bool loopTaskWDTEnabled;

void loopTask(void *pvParameters)
{
  setup();

  for(;;)
  {
    if(loopTaskWDTEnabled)
    {
      esp_task_wdt_reset();
    }

    loop();
  }
}

extern "C" void app_main()
{
  loopTaskWDTEnabled = false;
  initArduino();

  xTaskCreateUniversal(loopTask,
                       "loopTask",
                       CONFIG_ARDUINO_LOOP_STACK_SIZE,
                       nullptr,
                       1,
                       &loopTaskHandle,
                       CONFIG_ARDUINO_RUNNING_CORE);
}
