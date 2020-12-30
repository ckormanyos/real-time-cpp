#include <cstdint>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Taken from esp32-hal.h

// If xCoreID < 0 or CPU is unicore, it will use xTaskCreate, else xTaskCreatePinnedToCore
// allows to easily handle all possible situations without repetitive code
extern "C"
BaseType_t xTaskCreateUniversal(TaskFunction_t pxTaskCode,
                                const char * const pcName,
                                const uint32_t usStackDepth,
                                void * const pvParameters,
                                UBaseType_t uxPriority,
                                TaskHandle_t * const pxCreatedTask,
                                const BaseType_t xCoreID);

namespace
{
  constexpr std::uint32_t config_arduino_loop_stack_size = UINT32_C(8192);
  constexpr BaseType_t    config_arduino_running_core    = 1U;
}

extern "C" void main_loop(void*);

extern "C" void app_main()
{
  TaskHandle_t main_loop_task_handle;

  xTaskCreateUniversal(main_loop,
                       "main_loop",
                       config_arduino_loop_stack_size,
                       nullptr,
                       1,
                       &main_loop_task_handle,
                       config_arduino_running_core);
}
