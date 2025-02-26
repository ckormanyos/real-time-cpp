///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

///////////////////////////////////////////////////////////////////////////////
// Original copyright:
//

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

#include <cstdint>

extern "C"
{
  using TaskFunction_t = void(*)(void*);

  using TaskHandle_t   = void*;

  using BaseType_t     = int;
  using UBaseType_t    = unsigned int;

  extern int app_main_loop() __attribute__((used));
  void app_main_loop_wrapper(void*);

  void app_main();

  extern BaseType_t xTaskCreatePinnedToCore(      TaskFunction_t       pvTaskCode,
                                            const char*          const pcName,
                                            const uint32_t             usStackDepth,
                                                  void*          const pvParameters,
                                                  UBaseType_t          uxPriority,
                                                  TaskHandle_t*  const pvCreatedTask,
                                            const BaseType_t           xCoreID);
}

extern "C" void app_main_loop_wrapper(void*)
{
  const int nm = app_main_loop();

  static_cast<void>(nm);
}

extern "C" void app_main()
{
  // The subroutine app_main() is called from the Espressif SDK framework.
  // From the perspective of this particular implementation, this is the
  // starting point of the application.

  static TaskHandle_t app_main_loop_task_handle;

  constexpr uint32_t    app_main_loop_stack_size   = UINT32_C(8192);
  constexpr UBaseType_t app_main_loop_prio         = 2U;
  constexpr BaseType_t  app_main_loop_running_core = 1;

  // Create the main loop task.
  const BaseType_t create_result = ::xTaskCreatePinnedToCore( app_main_loop_wrapper,
                                                             "app_main_loop_wrapper",
                                                              app_main_loop_stack_size,
                                                              nullptr,
                                                              app_main_loop_prio,
                                                             &app_main_loop_task_handle,
                                                              app_main_loop_running_core);

  static_cast<void>(create_result);
}
