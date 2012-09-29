#include <mcal_irq.h>

void mcal::irq::init(const config_type*)
{
  // Enable all global interrupts.
  enable_all();
}
