
@rem Usage:
@rem build.bat "W:\ksc2rt_snapshot\User\Ks\uC_Software\Boards\cpp_board\tools\Util\MinGW\msys\1.0\local\gcc-4.8.1-avr\bin" avr

@set TOOL_PATH=%1
@set TOOL_PREFIX=%2

@echo.
@echo.Building with       : build.bat

@echo.
@echo.Using tool path     : %TOOL_PATH%

@echo.
@echo.Using tool prefix   : %TOOL_PREFIX%

@echo.
@echo.Clean bin directory : bin\*.*
del /Q bin\*.*

@echo.
@echo.Assemble : crt0.s  to bin/crt0.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -mmcu=atmega328p -fsigned-char -x assembler crt0.s -c -o bin/crt0.o

@echo.Compile  : led.cpp to bin/led.o
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -mmcu=atmega328p -fsigned-char -O3 -std=c++0x -I. -c led.cpp -o bin/led.o

@echo.Link     : objects to led.elf
@%TOOL_PATH%\%TOOL_PREFIX%-g++ -mmcu=atmega328p -nostartfiles -Wl,-Tavr.ld,-Map,bin/led.map bin/led.o bin/crt0.o -o bin/led.elf

@echo.
@echo.Extract  : executalbe hex file : from bin/led.elf
@%TOOL_PATH%\%TOOL_PREFIX%-objcopy -O ihex bin/led.elf bin/led.hex

@echo.Extract  : size information    : from bin/led.elf
@%TOOL_PATH%\%TOOL_PREFIX%-size -A -t bin/led.elf > bin\led_size.txt

@echo.Extract  : name information    : from bin/led.elf
@%TOOL_PATH%\%TOOL_PREFIX%-nm --numeric-sort --print-size bin/led.elf > bin\led_nm.txt

@echo.Extract  : demangled names     : from bin/led.elf
@%TOOL_PATH%\%TOOL_PREFIX%-nm --numeric-sort --print-size bin/led.elf | %TOOL_PATH%\%TOOL_PREFIX%-c++filt > bin\led_cppfilt.txt
