#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iterator>


namespace crt
{
  void init_ram();
}

namespace crt
{
  void init_ctors();
}

extern "C" void __my_startup(void) __attribute__((used, noinline));

void __my_startup(void)
{
  // Load the stack pointer.
  // The stack pointer is automatically loaded from
  // the base position of the interrupt vector table.
  // So we do nothing here.

  // TBD: Chip init: Watchdog, port, and oscillator, if any needed.

  // Initialize statics from ROM to RAM.
  // Zero-clear default-initialized static RAM.
  crt::init_ram();

  // Call all ctor initializations.
  crt::init_ctors();

  // Jump to main (and never return).
  asm volatile("ldr r3, =main");
  asm volatile("blx r3");

  exit(EXIT_SUCCESS);

  // TBD: Nothing on return from main.
}

extern "C" void _exit (int);

extern "C" void _exit (int) { }

extern "C"
{
  extern std::uintptr_t _rom_data_begin; // Start address for the initialization values of the rom-to-ram section.
  extern std::uintptr_t _data_begin;     // Start address for the .data section.
  extern std::uintptr_t _data_end;       // End address for the .data section.
  extern std::uintptr_t _bss_begin;      // Start address for the .bss section.
  extern std::uintptr_t _bss_end;        // End address for the .bss section.
}

void crt::init_ram()
{
  typedef std::uint32_t memory_aligned_type;

  // Copy the data segment initializers from ROM to RAM.
  // Note that all data segments are aligned by 4.
  const std::size_t size_data =
    std::size_t(  static_cast<const memory_aligned_type*>(static_cast<const void*>(&_data_end))
                - static_cast<const memory_aligned_type*>(static_cast<const void*>(&_data_begin)));

  std::copy(static_cast<const memory_aligned_type*>(static_cast<const void*>(&_rom_data_begin)),
            static_cast<const memory_aligned_type*>(static_cast<const void*>(&_rom_data_begin)) + size_data,
            static_cast<      memory_aligned_type*>(static_cast<      void*>(&_data_begin)));

  // Clear the bss segment.
  // Note that the bss segment is aligned by 4.
  std::fill(static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_begin)),
            static_cast<memory_aligned_type*>(static_cast<void*>(&_bss_end)),
            static_cast<memory_aligned_type>(0U));
}

extern "C"
{
  struct ctor_type
  {
    typedef void(*function_type)();
    typedef std::reverse_iterator<const function_type*> const_reverse_iterator;
  };

  extern ctor_type::function_type _ctors_end[];
  extern ctor_type::function_type _ctors_begin[];
}

void crt::init_ctors()
{
  std::for_each(ctor_type::const_reverse_iterator(_ctors_end),
                ctor_type::const_reverse_iterator(_ctors_begin),
                [](const ctor_type::function_type pf)
                {
                  pf();
                });
}
