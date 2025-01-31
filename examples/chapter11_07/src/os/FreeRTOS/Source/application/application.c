#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>

// If the buffers to be provided to the Idle task are declared inside this
// function then they must be declared static - otherwise they will be allocated on
// the stack and so not exists after this function exits.
StaticTask_t xIdleTaskTCB;
StackType_t  uxIdleTaskStack[configMINIMAL_STACK_SIZE];

// configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
// implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
// used by the Idle task.
void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer,
                                   StackType_t**  ppxIdleTaskStackBuffer,
                                   uint32_t*      pulIdleTaskStackSize)
{
  // Pass out a pointer to the StaticTask_t structure in which the Idle task's
  // state will be stored.
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

  // Pass out the array that will be used as the Idle task's stack.
  *ppxIdleTaskStackBuffer = uxIdleTaskStack;

  // Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
  // Note that, as the array is necessarily of type StackType_t,
  // configMINIMAL_STACK_SIZE is specified in words, not bytes.
  *pulIdleTaskStackSize = sizeof(uxIdleTaskStack) / sizeof(StackType_t);
}

// If the buffers to be provided to the Timer task are declared inside this
// function then they must be declared static - otherwise they will be allocated on
// the stack and so not exists after this function exits.
StaticTask_t xTimerTaskTCB;
StackType_t  uxTimerTaskStack[configMINIMAL_STACK_SIZE];
