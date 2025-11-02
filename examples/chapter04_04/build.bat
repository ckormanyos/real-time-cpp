
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
@rem cd "C:\Users\User\Documents\Ks\uC_Software\Boards\real-time-cpp\examples\chapter04_04"
@rem build.bat "C:\Users\User\Documents\Ks\uC_Software\Boards\real-time-cpp\examples\chapter04_04\tools\Util\msys64\usr\local\gcc-11.2.0-avr\bin" avr

@rem Usage example A1 (use a relative tool path),
@rem cd "C:\Users\User\Documents\Ks\uC_Software\Boards\real-time-cpp\examples\chapter04_04"
@rem build.bat ".\tools\Util\msys64\usr\local\gcc-11.2.0-avr\bin" avr

@rem Usage example B,
@rem cd "C:\Users\User\Documents\Ks\uC_Software\Boards\real-time-cpp\examples\chapter04_04"
@rem build.bat "C:\Program Files (x86)\gcc-11.2.0-avr\bin" avr


@set TOOL_PATH=%1
@set TOOL_PREFIX=%2

@set CFLAGS=-Wall -Wextra -Wpedantic -mmcu=atmega328p -fsigned-char -O2 -fno-exceptions
@set CPPFLAGS=-std=c++14 -fno-rtti -fstrict-enums -fno-use-cxa-atexit -fno-use-cxa-get-exception-ptr -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs
@set CINCLUDES=-Isrc/util/STL -Isrc/mcal/avr -Isrc

@echo.
@echo.Building with        : build.bat
@echo.Using tool path      : %TOOL_PATH%
@echo.Using tool prefix    : %TOOL_PREFIX%
@echo.Create bin directory : bin\
@if not exist bin mkdir bin
@echo.Clean  bin directory : bin\*.o bin\chapter04_04*.*
@if exist bin\*.o del /Q bin\*.o
@if exist bin\chapter04_04*.* del /Q bin\chapter04_04*.*
@echo.

@echo.Compile  : app_benchmark.cpp to bin/app_benchmark.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/app/benchmark/app_benchmark.cpp -o bin/app_benchmark.o

@echo.Compile  : app_led.cpp to bin/app_led.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/app/led/app_led.cpp -o bin/app_led.o

@echo.Compile  : mcal.cpp to bin/mcal.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/mcal.cpp -o bin/mcal.o

@echo.Compile  : mcal_gcc_cxx_completion.cpp to bin/mcal_gcc_cxx_completion.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/mcal_gcc_cxx_completion.cpp -o bin/mcal_gcc_cxx_completion.o

@echo.Compile  : mcal_cpu.cpp to bin/mcal_cpu.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/avr/mcal_cpu.cpp -o bin/mcal_cpu.o

@echo.Compile  : mcal_eep.cpp to bin/mcal_eep.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/avr/mcal_eep.cpp -o bin/mcal_eep.o

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

@echo.Compile  : mcal_pwm.cpp to bin/mcal_pwm.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/avr/mcal_pwm.cpp -o bin/mcal_pwm.o

@echo.Compile  : mcal_spi.cpp to bin/mcal_spi.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/avr/mcal_spi.cpp -o bin/mcal_spi.o

@echo.Compile  : mcal_wdg.cpp to bin/mcal_wdg.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/mcal/avr/mcal_wdg.cpp -o bin/mcal_wdg.o

@echo.Compile  : os.cpp to bin/os.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/os/os.cpp -o bin/os.o

@echo.Compile  : os.cpp to bin/os_task_control_block.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/os/os_task_control_block.cpp -o bin/os_task_control_block.o

@echo.Compile  : sys_idle.cpp to bin/sys_idle.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x c++ %CFLAGS% %CPPFLAGS% %CINCLUDES% -c src/sys/idle/sys_idle.cpp -o bin/sys_idle.o

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

@echo.Link     : objects to bin/chapter04_04.elf
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -x none -mrelax -nostartfiles %CFLAGS% %CPPFLAGS% %CINCLUDES% -Wl,--gc-sections -Wl,-Ttarget/micros/avr/make/avr.ld,-Map,bin/chapter04_04.map bin/app_benchmark.o bin/app_led.o bin/mcal.o bin/mcal_gcc_cxx_completion.o bin/mcal_cpu.o bin/mcal_eep.o bin/mcal_gpt.o bin/mcal_irq.o bin/mcal_led.o bin/mcal_osc.o bin/mcal_port.o bin/mcal_pwm.o bin/mcal_spi.o bin/mcal_wdg.o bin/os.o bin/os_task_control_block.o bin/sys_idle.o bin/sys_start.o bin/crt0.o bin/crt0_init_ram.o bin/crt1.o bin/int_vect.o -o bin/chapter04_04.elf

@echo.
@echo.Extract  : executable hex file : from bin/chapter04_04.elf
@%TOOL_PATH%\%TOOL_PREFIX%-objcopy -O ihex bin/chapter04_04.elf bin/chapter04_04.hex

@echo.Extract  : assembly list file  : from bin/chapter04_04.elf
@%TOOL_PATH%\%TOOL_PREFIX%-objdump --disassemble bin/chapter04_04.elf > bin/chapter04_04.lss

@echo.Extract  : size information    : from bin/chapter04_04.elf
@%TOOL_PATH%\%TOOL_PREFIX%-size -A -t bin/chapter04_04.elf > bin\chapter04_04_size.txt

@echo.Extract  : name information    : from bin/chapter04_04.elf
@%TOOL_PATH%\%TOOL_PREFIX%-nm --numeric-sort --print-size bin/chapter04_04.elf > bin\chapter04_04_nm.txt

@echo.Extract  : demangled names     : from bin/chapter04_04.elf
@%TOOL_PATH%\%TOOL_PREFIX%-nm --numeric-sort --print-size bin/chapter04_04.elf | %TOOL_PATH%\%TOOL_PREFIX%-c++filt > bin\chapter04_04_cppfilt.txt

dir .\bin\chapter04_04.elf .\bin\chapter04_04.hex

if not exist .\bin\chapter04_04.elf exit 1
if not exist .\bin\chapter04_04.hex exit 1

exit 0
