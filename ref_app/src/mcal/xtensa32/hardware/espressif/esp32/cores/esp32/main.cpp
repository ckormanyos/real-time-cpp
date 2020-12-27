#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <Arduino.h>

#ifndef CONFIG_ARDUINO_LOOP_STACK_SIZE
#define CONFIG_ARDUINO_LOOP_STACK_SIZE 8192
#endif

TaskHandle_t main_loop_task_handle;

extern "C" void main_loop(void*);

extern "C" void app_main()
{
  initArduino();

  xTaskCreateUniversal(main_loop,
                       "main_loop",
                       CONFIG_ARDUINO_LOOP_STACK_SIZE,
                       nullptr,
                       1,
                       &main_loop_task_handle,
                       CONFIG_ARDUINO_RUNNING_CORE);
}

extern "C"
{
  int atexit (void (*)(void)) noexcept;

  int atexit (void (*)(void))
  {
    return 0;
  }
}
