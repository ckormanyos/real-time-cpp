rem ///////////////////////////////////////////////////////////////////////////////
rem //  Copyright Christopher Kormanyos 2007 - 2025.
rem //  Distributed under the Boost Software License,
rem //  Version 1.0. (See accompanying file LICENSE_1_0.txt
rem //  or copy at http://www.boost.org/LICENSE_1_0.txt)
rem //

echo off

set AVRDUDE=.\avrdude.exe

set HEX=../../../../../examples/chapter09_08a/bin/chapter09_08a.hex

rem Erase the chip.
echo "Erase the chip."
%AVRDUDE% -c arduino -p m328p -P COM5 -b 115200 -e
echo.

rem Flash the HEX-file.
echo "Flash the HEX-file."
%AVRDUDE% -c arduino -p m328p -P COM5 -b 115200 -U flash:w:%HEX%:i
echo.

rem Verify the flash.
echo "Verify the flash."
%AVRDUDE% -c arduino -p m328p -P COM5 -b 115200 -U flash:v:%HEX%:i
echo.
