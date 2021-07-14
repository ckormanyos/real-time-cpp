///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OS_TASK_2020_10_08_H_
  #define OS_TASK_2020_10_08_H_

  #include <FreeRTOS.h>
  #include <task.h>

  #define OS_TASK_STATIC_RESOURCES(name, size) \
  StackType_t os_task_##name##_stack_buffer[size]; \
  StaticTask_t os_task_##name##_cb_buffer

  #define OS_TASK_CREATE(name, param, prio) \
  xTaskCreateStatic(name,                                                          \
                    #name,                                                         \
                    sizeof(os_task_##name##_stack_buffer) / sizeof(StackType_t),   \
                    (void*) param,                                                 \
                    prio,                                                          \
                    &os_task_##name##_stack_buffer[0U],                            \
                    &os_task_##name##_cb_buffer)

  #define OS_TASK_START_SCHEDULER() vTaskStartScheduler()

  #define OS_TASK_MSEC(x) pdMS_TO_TICKS((x))

  #define OS_TASK_WAIT_YIELD(x) vTaskDelay((x))

#endif // OS_TASK_2020_10_08_H_
