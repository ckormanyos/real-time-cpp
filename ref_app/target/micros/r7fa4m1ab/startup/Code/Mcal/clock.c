/******************************************************************************************
  Filename    : clock.c
  
  Core        : ARM Cortex-M4
  
  MCU         : Renesas R7FA4M1AB
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.01.2026
  
  Description : clock driver implementation
  
******************************************************************************************/

//-----------------------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------------------
#include "R7FA4M1AB.h"

//-----------------------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------------------
void clock_init(void);

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void clock_init(void)
{
  #define HOCOCR2   (*((volatile uint8_t*)(0x4001E037)))

  /* disable register write protection for clock module */
  SYSTEM->PRCR.reg = (uint16_t)((0xA5 << 8) | 1);

  /*set system clock division to 1*/
  SYSTEM->SCKDIVCR.reg = 0;

  /* set the HOCO clock frequency to 48 MHz */
  HOCOCR2 = (4 << 3);

  /* switch sysclk to HOCO clock (48 MHz) */
  SYSTEM->OPCCR.bit.OPCM = 0;
  while(SYSTEM->OPCCR.bit.OPCMTSF);

  /* switch power operation mode to high-speed mode */
  SYSTEM->HOCOCR.bit.HCSTP = 0;
  while(!SYSTEM->OSCSF.bit.HOCOSF);

  /* enable memory wait cycle */
  SYSTEM->MEMWAIT.bit.MEMWAIT = 1;
 
  /* switch sysclk to HOCO clock (48 MHz) */
  SYSTEM->SCKSCR.reg = 0;
}
