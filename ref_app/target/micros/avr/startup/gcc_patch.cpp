extern "C"
{
  void __cxa_pure_virtual() { }

  typedef void(*void_function_type)();

  int atexit(const void_function_type) { return 0; }

  int __errno;
}

void operator delete(void*) { }
