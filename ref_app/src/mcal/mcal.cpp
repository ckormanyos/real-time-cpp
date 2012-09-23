#include <mcal/mcal.h>

void mcal::init()
{
  mcal::port::init(nullptr);
  mcal::irq::init(nullptr);
  mcal::mcu::init(nullptr);
  mcal::gpt::init(nullptr);
  mcal::ser::init(nullptr);
  mcal::spi::init(nullptr);
}
