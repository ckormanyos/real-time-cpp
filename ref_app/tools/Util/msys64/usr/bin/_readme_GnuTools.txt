Update 2024-01-31

- Simply use tools from "UnxUtils" including
  echo, mkdir, rm, sed. See also:
  https://sourceforge.net/projects/unxutils

- The make.exe stays the same as the one below.

- Begin building cross-compilers on msys2
  with a completely standalone, static MinGW
  (from nuwen). These do not require and DLLs.

-------------------------------------------------------

- The source of echo, mkdir, rm, sed is mingw64/msys2.
- Their associated DLLs msys-2.0, msys-iconv-2 and
  msys-intl-8 are taken from mingw64/msys2.

- GCC toolchains are in the "local" directory and
  its subdirectories. The DLL libwinpthread-1
  is needed for these GCC ports. This DLL has
  also been taken from mingw64/msys2.

- The make.exe program GNUmake 4.2.1 built for Windows
  with MSVC 14.2. See also the repository for this ar:
  https://github.com/ckormanyos/real-time-cpp-toolchains
