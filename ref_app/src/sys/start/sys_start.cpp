#include <mcal/mcal.h>
#include <os/os.h>

int main()
{
  // Initialize the Microcontroller Abstraction Layer.
  mcal::init();

  // Start the multitasking scheduler (and never return!).
  os::schedule();
}
