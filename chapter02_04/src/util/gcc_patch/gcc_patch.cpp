
void operator delete(void*) { }

extern "C"
{
  void __cxa_pure_virtual(void) { }

  typedef void(*void_function_type)(void);

  int atexit(const void_function_type) { return 0; }

  void exit(int) __attribute__ ((noreturn));
  void exit(int) { for(;;) { ; } }
}
