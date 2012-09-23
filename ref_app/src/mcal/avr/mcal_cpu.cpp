#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_wdg.h>

extern "C" void mcal_cpu_init()
{
  mcal::port::init(nullptr);
  mcal::wdg::init(nullptr);
  mcal::osc::init(nullptr);
}
