extern "C" void unhandled_exception(void) __attribute__((interrupt, used, noinline));

extern "C"
void unhandled_exception(void)
{
  for(;;)
  {
    asm volatile("nop");
  }
}
