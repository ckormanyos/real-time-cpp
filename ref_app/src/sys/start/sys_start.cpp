#include <mcal/mcal.h>
#include <os/os.h>

extern "C" int main()
{
  // Initialize the Microcontroller Abstraction Layer.
  mcal::init();

  // Start the multitasking scheduler (and never return!).
  os::schedule();
}
