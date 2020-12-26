#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"
#include "Arduino.h"

#ifndef CONFIG_ARDUINO_LOOP_STACK_SIZE
#define CONFIG_ARDUINO_LOOP_STACK_SIZE 8192
#endif

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
