
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
@rem cd "C:\Users\User\Documents\Ks\uC_Software\Boards\real-time-cpp\examples\chapter11_07"
@rem build.bat "C:\Users\User\Documents\Ks\uC_Software\Boards\real-time-cpp\examples\chapter11_07\tools\Util\msys64\usr\local\gcc-11.2.0-avr\bin" avr

@rem Usage example A1 (use a relative tool path),
@rem cd "C:\Users\User\Documents\Ks\uC_Software\Boards\real-time-cpp\examples\chapter11_07"
@rem build.bat ".\tools\Util\msys64\usr\local\gcc-11.2.0-avr\bin" avr

@rem Usage example B,
@rem cd "C:\Users\User\Documents\Ks\uC_Software\Boards\real-time-cpp\examples\chapter11_07"
@rem build.bat "C:\Program Files (x86)\gcc-11.2.0-avr\bin" avr


@set TOOL_PATH=%1
@set TOOL_PREFIX=%2

@set CFLAGS=-C -Wall -Wextra -pedantic -mmcu=atmega328p -fsigned-char -O2 -fno-exceptions -gdwarf-2 -ffunction-sections -fdata-sections
@set CPPFLAGS=-std=c++14 -fno-rtti -fstrict-enums -fno-use-cxa-atexit -fno-use-cxa-get-exception-ptr -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs
@set CINCLUDES=-Isrc/os/FreeRTOS/Source/include/cfg/GCC-ATMega328 -Isrc/os/FreeRTOS/Source/portable/GCC-ATMega328 -Isrc/os/FreeRTOS/Source/include -Isrc/util/STL -Isrc/mcal/avr -Isrc

@echo.
@echo.Building with        : build.bat
@echo.Using tool path      : %TOOL_PATH%
@echo.Using tool prefix    : %TOOL_PREFIX%
@echo.Create bin directory : bin\
@if not exist bin mkdir bin
@echo.Clean  bin directory : bin\*.o bin\chapter11_07*.*
@if exist bin\*.o del /Q bin\*.o
@if exist bin\chapter11_07*.* del /Q bin\chapter11_07*.*
@echo.

@echo.Compile  : app_led.cpp to bin/app_led.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/app/led/app_led.cpp -o bin/app_led.o

@echo.Compile  : mcal.cpp to bin/mcal.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/mcal.cpp -o bin/mcal.o

@echo.Compile  : mcal_gcc_cxx_completion.cpp to bin/mcal_gcc_cxx_completion.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/mcal_gcc_cxx_completion.cpp -o bin/mcal_gcc_cxx_completion.o

@echo.Compile  : mcal_cpu.cpp to bin/mcal_cpu.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/avr/mcal_cpu.cpp -o bin/mcal_cpu.o

@echo.Compile  : mcal_gpt.cpp to bin/mcal_gpt.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/avr/mcal_gpt.cpp -o bin/mcal_gpt.o

@echo.Compile  : mcal_irq.cpp to bin/mcal_irq.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/avr/mcal_irq.cpp -o bin/mcal_irq.o

@echo.Compile  : mcal_led.cpp to bin/mcal_led.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/avr/mcal_led.cpp -o bin/mcal_led.o

@echo.Compile  : mcal_osc.cpp to bin/mcal_osc.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/avr/mcal_osc.cpp -o bin/mcal_osc.o

@echo.Compile  : mcal_port.cpp to bin/mcal_port.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/avr/mcal_port.cpp -o bin/mcal_port.o

@echo.Compile  : mcal_wdg.cpp to bin/mcal_wdg.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/avr/mcal_wdg.cpp -o bin/mcal_wdg.o

@echo.Compile  : event_groups.c to bin/event_groups.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c %CFLAGS% -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast %CINCLUDES% -c src/os/FreeRTOS/Source/event_groups.c -o bin/event_groups.o

@echo.Compile  : list.c to bin/list.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c %CFLAGS% -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast %CINCLUDES% -c src/os/FreeRTOS/Source/list.c -o bin/list.o

@echo.Compile  : queue.c to bin/queue.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c %CFLAGS% -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast %CINCLUDES% -c src/os/FreeRTOS/Source/queue.c -o bin/queue.o

@echo.Compile  : tasks.c to bin/tasks.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c %CFLAGS% -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast %CINCLUDES% -c src/os/FreeRTOS/Source/tasks.c -o bin/tasks.o

@echo.Compile  : application.c to bin/application.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c %CFLAGS% -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast %CINCLUDES% -c src/os/FreeRTOS/Source/application/application.c -o bin/application.o

@echo.Compile  : port.cpp to bin/port.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/os/FreeRTOS/Source/portable/GCC-ATMega328/port.cpp -o bin/port.o

@echo.Compile  : sys_start.cpp to bin/sys_start.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/sys/start/sys_start.cpp -o bin/sys_start.o

@echo.Compile  : crt0.cpp to bin/crt0.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c target/micros/avr/startup/crt0.cpp -o bin/crt0.o

@echo.Compile  : crt0_init_ram.cpp to bin/crt0_init_ram.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c target/micros/avr/startup/crt0_init_ram.cpp -o bin/crt0_init_ram.o

@echo.Compile  : crt1.cpp to bin/crt1.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c target/micros/avr/startup/crt1.cpp -o bin/crt1.o

@echo.Compile  : int_vect.cpp to bin/int_vect.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c target/micros/avr/startup/int_vect.cpp -o bin/int_vect.o

@echo.Link     : objects to bin/chapter11_07.elf
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x none -mrelax -nostartfiles %CFLAGS% %CPPFLAGS% %CINCLUDES% -Wl,--gc-sections -Wl,-Ttarget/micros/avr/make/avr.ld,-Map,bin/chapter11_07.map bin/app_led.o bin/mcal.o bin/mcal_gcc_cxx_completion.o bin/mcal_cpu.o bin/mcal_gpt.o bin/mcal_irq.o bin/mcal_led.o bin/mcal_osc.o bin/mcal_port.o bin/mcal_wdg.o bin/event_groups.o bin/list.o bin/queue.o bin/tasks.o bin/application.o bin/port.o bin/sys_start.o bin/crt0.o bin/crt0_init_ram.o bin/crt1.o bin/int_vect.o -o bin/chapter11_07.elf

@echo.
@echo.Extract  : executable hex file : from bin/chapter11_07.elf
@%TOOL_PATH%\%TOOL_PREFIX%-objcopy -O ihex bin/chapter11_07.elf bin/chapter11_07.hex

@echo.Extract  : assembly list file  : from bin/chapter11_07.elf
@%TOOL_PATH%\%TOOL_PREFIX%-objdump --disassemble bin/chapter11_07.elf > bin/chapter11_07.lss

@echo.Extract  : size information    : from bin/chapter11_07.elf
@%TOOL_PATH%\%TOOL_PREFIX%-size -A -t bin/chapter11_07.elf > bin\chapter11_07_size.txt

@echo.Extract  : name information    : from bin/chapter11_07.elf
@%TOOL_PATH%\%TOOL_PREFIX%-nm --numeric-sort --print-size bin/chapter11_07.elf > bin\chapter11_07_nm.txt

@echo.Extract  : demangled names     : from bin/chapter11_07.elf
@%TOOL_PATH%\%TOOL_PREFIX%-nm --numeric-sort --print-size bin/chapter11_07.elf | %TOOL_PATH%\%TOOL_PREFIX%-c++filt > bin\chapter11_07_cppfilt.txt

dir .\bin\chapter11_07.elf .\bin\chapter11_07.hex

if not exist .\bin\chapter11_07.elf exit 1
if not exist .\bin\chapter11_07.hex exit 1

exit 0