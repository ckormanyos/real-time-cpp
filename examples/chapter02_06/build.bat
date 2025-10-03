
@rem
@rem Copyright Christopher Kormanyos 2014 - 2025.
@rem Distributed under the Boost Software License,
@rem Version 1.0. (See accompanying file LICENSE_1_0.txt
@rem or copy at http://www.boost.org/LICENSE_1_0.txt)
@rem


@rem
@rem Usage:
@rem build.bat directory_of_gcc_bin prefix_of_avr_gcc

@rem Usage example A,
@rem cd "C:\Users\User\Documents\Ks\uC_Software\Boards\real-time-cpp\examples\chapter02_06"
@rem build.bat "C:\Users\User\Documents\Ks\uC_Software\Boards\real-time-cpp\examples\chapter02_06\tools\Util\msys64\usr\local\gcc-11.2.0-avr\bin" avr

@rem Usage example A1 (use a relative tool path),
@rem cd "C:\Users\User\Documents\Ks\uC_Software\Boards\real-time-cpp\examples\chapter02_06"
@rem build.bat ".\tools\Util\msys64\usr\local\gcc-11.2.0-avr\bin" avr

@rem Usage example B,
@rem cd "C:\Users\User\Documents\Ks\uC_Software\Boards\real-time-cpp\examples\chapter02_06"
@rem build.bat "C:\Program Files (x86)\gcc-11.2.0-avr\bin" avr


@set TOOL_PATH=%1
@set TOOL_PREFIX=%2

@echo.
@echo.Building with       : build.bat
@echo.Using tool path     : %TOOL_PATH%
@echo.Using tool prefix   : %TOOL_PREFIX%
@echo.Clean bin directory : bin\led*.*
if exist bin\led*.* del /Q bin\led*.*

@echo.
@echo.Assemble : crt0.s  to bin/crt0.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -mmcu=atmega328p -fsigned-char -x assembler crt0.s -c -o bin/crt0.o

@echo.Compile  : led.cpp to bin/led.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -mmcu=atmega328p -fsigned-char -O2 -std=c++0x -I. -c led.cpp -o bin/led.o

@echo.Link     : objects to bin/led.elf
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -mmcu=atmega328p -nostartfiles -nostdlib -Wl,-Tavr.ld,-Map,bin/led.map bin/led.o bin/crt0.o -o bin/led.elf

@echo.
@echo.Extract  : executalbe hex file : from bin/led.elf
@%TOOL_PATH%\%TOOL_PREFIX%-objcopy -O ihex bin/led.elf bin/led.hex

@echo.Extract  : assembly list file  : from bin/led.elf
@%TOOL_PATH%\%TOOL_PREFIX%-objdump --disassemble bin/led.elf > bin/led.lss

@echo.Extract  : size information    : from bin/led.elf
@%TOOL_PATH%\%TOOL_PREFIX%-size -A -t bin/led.elf > bin\led_size.txt

@echo.Extract  : name information    : from bin/led.elf
@%TOOL_PATH%\%TOOL_PREFIX%-nm --numeric-sort --print-size bin/led.elf > bin\led_nm.txt

@echo.Extract  : demangled names     : from bin/led.elf
@%TOOL_PATH%\%TOOL_PREFIX%-nm --numeric-sort --print-size bin/led.elf | %TOOL_PATH%\%TOOL_PREFIX%-c++filt > bin\led_cppfilt.txt

dir .\bin\led.elf
dir .\bin\led.hex

if not exist .\bin\led.elf exit 1
if not exist .\bin\led.hex exit 1

exit 0
