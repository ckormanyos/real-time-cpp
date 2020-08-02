#include <mcal_reg.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

extern "C"
void mcal_reg_access32_write(uint32_t address, uint32_t value)
{
  asm
  (
    "mov r2, #0                  \t\n\
     mcr p15, 0, r2, c7, c10, 5  \t\n\
     str r1, [r0]                \t\n\
     bx lr"
  );
}

extern "C"
uint32_t mcal_reg_access32_read(uint32_t address)
{
  asm
  (
    "mov r2, #0                  \t\n\
     mcr p15, 0, r2, c7, c10, 5  \t\n\
     ldr r0, [r0]                \t\n\
     bx lr"
  );
}

#pragma GCC diagnostic pop
