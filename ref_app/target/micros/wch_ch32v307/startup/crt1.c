
extern unsigned long __CTOR_LIST__[];

#define __STARTUP_RUNTIME_CTORS       (unsigned long*)(&__CTOR_LIST__[0])

void Startup_InitCtors(void)
{
  unsigned long CtorIdx = 0U;
  
  while((__STARTUP_RUNTIME_CTORS)[CtorIdx] != ((unsigned long)-1))
  {
    ((void (*)(void))((__STARTUP_RUNTIME_CTORS)[CtorIdx++]))();
  }
}
