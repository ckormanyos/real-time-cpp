#include <mcal/mcal.h>

extern "C" void mcal_cpu_init();

void mcal::init()
{
  ::mcal_cpu_init();
  mcal::irq::init(nullptr);
  mcal::mcu::init(nullptr);
  mcal::gpt::init(nullptr);
}
