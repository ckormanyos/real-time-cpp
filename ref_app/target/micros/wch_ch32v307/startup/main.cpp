
#include <mcal_gpt.h>
#include <mcal_led.h>

#include <util/utility/util_time.h>


// cd /mnt/c/Users/ckorm/Documents/Ks/uC_Software/Boards/WCH_V307_RISC-V
// wget --no-check-certificate https://buildbot.embecosm.com/job/riscv32-gcc-ubuntu2204-release/10/artifact/riscv32-embecosm-ubuntu2204-gcc13.2.0.tar.gz
// tar -xzf riscv32-embecosm-ubuntu2204-gcc13.2.0.tar.gz -C /mnt/c/Users/ckorm/Documents/Ks/uC_Software/Boards/WCH_V307_RISC-V
// PATH="/mnt/c/Users/ckorm/Documents/Ks/uC_Software/Boards/WCH_V307_RISC-V/riscv32-embecosm-ubuntu2204-gcc13.2.0/bin:$PATH"
// cd Build
// bash ./Rebuild.sh

extern "C" int main(void)
{
  mcal::gpt::init(nullptr);

  mcal::led::led0().toggle();

  using local_timer_type = util::timer<std::uint32_t>;

  local_timer_type led_timer(local_timer_type::seconds(1U));

  for(;;)
  {
    if(led_timer.timeout())
    {
      mcal::led::led0().toggle();

      led_timer.start_interval(local_timer_type::seconds(1U));
    }
  }
}
