#include <stdint.h>
#include "SysTickTimer.h"


void SysTickTimer(void);

volatile uint64_t ticks = 0;

//----------------------------------------------------------------------------------------
/// \brief  
///
/// \descr 
///
/// \param  
///
/// \return 
//----------------------------------------------------------------------------------------
void main(void)
{
  SysTickTimer_Init();
  SysTickTimer_Start(SYS_TICK_MS(1));
  while(1);
}

//----------------------------------------------------------------------------------------
/// \brief  
///
/// \descr 
///
/// \param  
///
/// \return 
//----------------------------------------------------------------------------------------
void SysTickTimer(void)
{
  static uint32_t tick = 0;

  if(++tick >= 1000)
  {
    tick = 0;
    ticks++;
  }

  SysTickTimer_Reload(SYS_TICK_MS(1));
}