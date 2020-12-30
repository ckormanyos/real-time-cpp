// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#define tskNO_AFFINITY INT_MAX

typedef void(*TaskFunction_t)(void*);

typedef void* TaskHandle_t;

#define portBASE_TYPE int

typedef portBASE_TYPE          BaseType_t;
typedef unsigned portBASE_TYPE UBaseType_t;

void main_loop(void*);
void app_main(void);

BaseType_t xTaskCreatePinnedToCore(TaskFunction_t pvTaskCode,
                                   const char * const pcName,
                                   const uint32_t usStackDepth,
                                   void * const pvParameters,
                                   UBaseType_t uxPriority,
                                   TaskHandle_t * const pvCreatedTask,
                                   const BaseType_t xCoreID);

static inline BaseType_t xTaskCreate(TaskFunction_t pvTaskCode,
                                     const char * const pcName,
                                     const uint32_t usStackDepth,
                                     void * const pvParameters,
                                     UBaseType_t uxPriority,
                                     TaskHandle_t * const pvCreatedTask)
{
  return xTaskCreatePinnedToCore( pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pvCreatedTask, tskNO_AFFINITY );
}

BaseType_t xTaskCreateUniversal( TaskFunction_t pxTaskCode,
                        const char * const pcName,
                        const uint32_t usStackDepth,
                        void * const pvParameters,
                        UBaseType_t uxPriority,
                        TaskHandle_t * const pxCreatedTask,
                        const BaseType_t xCoreID )
{
  if(xCoreID >= 0 && xCoreID < 2)
  {
    return xTaskCreatePinnedToCore(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask, xCoreID);
  }
  else
  {
    return xTaskCreate(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask);
  }
}

void app_main(void)
{
  const uint32_t config_arduino_loop_stack_size = UINT32_C(8192);
  const BaseType_t    config_arduino_running_core    = 1U;

  TaskHandle_t main_loop_task_handle;

  xTaskCreateUniversal(main_loop,
                       "main_loop",
                       config_arduino_loop_stack_size,
                       NULL,
                       1,
                       &main_loop_task_handle,
                       config_arduino_running_core);
}
