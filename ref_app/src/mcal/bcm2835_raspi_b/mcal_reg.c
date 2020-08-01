#include <mcal_reg.h>

void mcal_reg_access32_write(uint32_t address, uint32_t value)
{
  (void) address;
  (void) value;

  __asm volatile("mov r2, #0");
  __asm volatile("mcr p15,0,r2,c7,c10,5"); /* Data Memory Barrier Operation */
  __asm volatile("str r1, [r0]");
  __asm volatile("bx lr");
}

uint32_t mcal_reg_access32_read(uint32_t address)
{
  (void) address;

  __asm volatile("mov r2, #0");
  __asm volatile("ldr r0, [r0]");
  __asm volatile("mcr p15,0,r2,c7,c10,5"); /* Data Memory Barrier Operation */
  __asm volatile("bx lr");
}
