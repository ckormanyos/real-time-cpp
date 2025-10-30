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
#include <stdint.h> 
#include "BL602.h"
#include "riscv-csr.h"
#include "printf.h"

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
void __attribute__((interrupt)) Isr_TIMER_Interrupt (void);

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
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

  /* configure gpio function for uart tx and rx */
  glb->GPIO_CFGCTL8.bit.reg_gpio_16_func_sel = GPIO_FUN_UART;
  glb->GPIO_CFGCTL3.bit.reg_gpio_7_func_sel  = GPIO_FUN_UART;

  /* select uart function for each gpio pin */
  glb->UART_SIG_SEL_0.bit.uart_sig_0_sel=2u; /* gpio_16(SIG0) --> UART0_TXD (2) */
  glb->UART_SIG_SEL_0.bit.uart_sig_7_sel=3u; /* gpio_7(SIG7)  --> UART0_RXD (3) */

  /* set the uart clock freq to 160MHz */
  HBN->HBN_GLB.bit.hbn_uart_clk_sel = 1u;

  /* set uart baudrate to 115200 kbps */
  uart->uart_bit_prd.bit.cr_utx_bit_prd = 1389;
  uart->uart_bit_prd.bit.cr_urx_bit_prd = 1389;

  /* enable uart tx */
  uart->utx_config.bit.cr_utx_frm_en = 1u;
  uart->utx_config.bit.cr_utx_len = 1u;
  uart->utx_config.bit.cr_utx_en = 1u;

  /* output a text message on the uart console */
  printf("BareMetal BL602 SW is Alive!\n\r");

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
