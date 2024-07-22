/******************************************************************************************
  Filename    : SysTickTimer.c
  
  Core        : ARM Cortex-M0+
  
  MCU         : RP2040
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 07.02.2023
  
  Description : System timer driver implementation
  
******************************************************************************************/

#include "SysTickTimer.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"

//=========================================================================================
// Functions
//=========================================================================================

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
extern "C"
void SysTickTimer_Init(void)
{
  pSTK_CTRL->u32Register     = 0;
  pSTK_VAL->u32Register      = 0;
  pSTK_CTRL->bits.u1CLOCKSRC = SYS_TICK_CLKSRC_PROCESSOR_CLOCK;
  pSTK_CTRL->bits.u1TICKINT  = SYS_TICK_ENABLE_INT;
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
extern "C"
void SysTickTimer_Start(uint32 timeout)
{
  pSTK_LOAD->u32Register   = timeout;
  pSTK_CTRL->bits.u1ENABLE = SYS_TICK_ENABLE_TIMER;
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
extern "C"
void SysTickTimer_Stop(void)
{
  pSTK_CTRL->bits.u1ENABLE = 0U;
}

#pragma GCC diagnostic pop
