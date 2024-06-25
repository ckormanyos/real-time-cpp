
#include <Port.h>
#include <SysTick.h>

// cd /mnt/c/Users/ckorm/Documents/Ks/uC_Software/Boards/WCH_V307_RISC-V
// wget --no-check-certificate https://buildbot.embecosm.com/job/riscv32-gcc-ubuntu2204-release/10/artifact/riscv32-embecosm-ubuntu2204-gcc13.2.0.tar.gz
// tar -xzf riscv32-embecosm-ubuntu2204-gcc13.2.0.tar.gz -C /mnt/c/Users/ckorm/Documents/Ks/uC_Software/Boards/WCH_V307_RISC-V
// PATH="/mnt/c/Users/ckorm/Documents/Ks/uC_Software/Boards/WCH_V307_RISC-V/riscv32-embecosm-ubuntu2204-gcc13.2.0/bin:$PATH"
// cd Build
// bash ./Rebuild.sh

int main(void)
{
  Port_Init();

  SysTick_Init();

  SysTick_Start(SYSTICK_TIMEOUT_SEC(1));

  for(;;)
  {
    ;
  }
}
