extern "C"
{
  void __cxa_pure_virtual() { }

  typedef void(*void_function_type)();

  int atexit(const void_function_type) { return 0; }

  int __errno;

  void _nmi_handler() { for(;;) { ; } }
}

void operator delete(void*) { }

namespace std
{
  void __throw_length_error(const char*) { }
  void __throw_out_of_range(const char*) { }
  void __throw_logic_error (const char*) { }
}
