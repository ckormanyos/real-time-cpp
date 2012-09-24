#include <mcal/mcal.h>

void mcal::init(void)
{
  mcal::mcu::init(nullptr);
  mcal::gpt::init(nullptr);
}
