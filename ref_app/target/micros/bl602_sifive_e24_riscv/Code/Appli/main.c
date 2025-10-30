/******************************************************************************************
  Filename    : main.c
  
  Core        : RV32IMAFCB (SiFive E24 RISC-V)
  
  MCU         : BL602
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 21.10.2025
  
  Description : Application main function
  
******************************************************************************************/


// Build in WSL with old GCC 10 from SiFive
// cd /mnt/c/Users/ckorm/Documents/Ks/uC_Software/Boards/Baremetal_BL602_SiFive_E24_RISC-V/Build
// PATH=/mnt/c/Users/ckorm/Documents/Ks/uC_Software/Boards/Baremetal_BL602_SiFive_E24_RISC-V/riscv64-unknown-elf-toolchain/bin:$PATH
// ./Rebuild.sh


// Build in WSL with GCC 15.2 from xPack
// cd /mnt/c/Users/ckorm/Documents/Ks/uC_Software/Boards/Baremetal_BL602_SiFive_E24_RISC-V/Build
// PATH=/mnt/c/Users/ckorm/Documents/Ks/uC_Software/Boards/Baremetal_BL602_SiFive_E24_RISC-V/xpack-riscv-none-elf-gcc-15.2.0-1/bin:$PATH
// ./Rebuild.sh

// cd C:\Users\ckorm\Documents\Ks\uC_Software\Boards\Baremetal_BL602_SiFive_E24_RISC-V\Build
// ..\Tools\flasher\blflash.exe flash C:/Users/ckorm/Documents/Ks/uC_Software/Boards/Baremetal_BL602_SiFive_E24_RISC-V/Output/baremetal_bl602_sifive_e24_risc-v.img --baud-rate 230400 --initial-baud-rate 230400 --port COM3



//-----------------------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------------------

#include "BL602.h"

#include "riscv-csr.h"

#include <stdint.h>

//-----------------------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------------------
#define TIMEOUT_500MS  (uint64_t)5000000
#define TIMEOUT_1S  (uint64_t)10000000

//-----------------------------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------------------
void __attribute__((interrupt,used,noinline)) Isr_TIMER_Interrupt (void);

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
int main(void) __attribute__((used,noinline));

int main(void)
{
  /* configure IO3 as output */
  glb->GPIO_CFGCTL1.bit.reg_gpio_3_func_sel = GPIO_FUN_SWGPIO;
  glb->GPIO_CFGCTL1.bit.reg_gpio_3_ie       = 0ul;
  glb->GPIO_CFGCTL1.bit.reg_gpio_3_drv      = 0ul;
  glb->GPIO_CFGCTL1.bit.reg_gpio_3_smt      = 0ul;
  glb->GPIO_CFGCTL34.bit.reg_gpio_3_oe      = 1ul;

  /* enabled selective hardware vectoring */
  CLIC_CFG |= 1ul;

  /* enable timer interrupt in CLIC vectored mode */
  CLIC_INTIE[7] = 1u;

  /* set the timeout to 500ms */
  CLIC_MTIMECMP = (uint64_t)(CLIC_MTIME + TIMEOUT_500MS);

  /* endless loop */
  while(1);

  return 0;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void Isr_TIMER_Interrupt (void)
{
  /* toggle the IO3 pin */
  glb->GPIO_CFGCTL32.bit.reg_gpio_3_o ^= 1ul;

  /* set the next timer timeout timeout */
  CLIC_MTIMECMP = (uint64_t)(CLIC_MTIME + TIMEOUT_1S);
}
