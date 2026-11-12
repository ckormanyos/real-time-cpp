@echo off

rem ///////////////////////////////////////////////////////////////////////////////
rem //  Copyright Christopher Kormanyos 2007 - 2026.
rem //  Distributed under the Boost Software License,
rem //  Version 1.0. (See accompanying file LICENSE_1_0.txt
rem //  or copy at http://www.boost.org/LICENSE_1_0.txt)
rem //

set AVRDUDE=.\avrdude.exe

set HEX=../../../../bin/ref_app.hex

echo.
echo Erase the chip.
%AVRDUDE% -c avrispmkII -p m328p -P usb -e
echo.

echo Flash the HEX-file.
%AVRDUDE% -c avrispmkII -p m328p -P usb -U flash:w:%HEX%:i
echo.

echo Verify the flash.
%AVRDUDE% -c avrispmkII -p m328p -P usb -U flash:v:%HEX%:i
echo.
