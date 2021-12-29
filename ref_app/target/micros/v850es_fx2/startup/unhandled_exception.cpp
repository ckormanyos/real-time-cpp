extern "C" void unhandled_exception(void) __attribute__((interrupt_handler, used, noinline));

extern "C"
void unhandled_exception(void)
{
  for(;;)
  {
    asm volatile("nop");
  }
}
