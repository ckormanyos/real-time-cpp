@echo off

rem ///////////////////////////////////////////////////////////////////////////////
rem //  Copyright Christopher Kormanyos 2007 - 2026.
rem //  Distributed under the Boost Software License,
rem //  Version 1.0. (See accompanying file LICENSE_1_0.txt
rem //  or copy at http://www.boost.org/LICENSE_1_0.txt)
rem //

rem see also https://www.conrad.de/de/p/econ-connect-ws6g-stiftleiste-gesamtpolzahl-6-anzahl-reihen-2-1-st-1303916.html
rem for an unrelated topic, the 2-by-3 connector: shrouded PCB header with a 2.54 mm pitch and keying notch

set AVRDUDE=.\avrdude.exe

set HEX=../../../../bin/ref_app.hex

echo.
echo Erase the chip.
%AVRDUDE% -c stk500v2 -p m328p -P COM6 -e
echo.

echo Flash the HEX-file.
%AVRDUDE% -c stk500v2 -p m328p -P COM6 -U flash:w:%HEX%:i
echo.

echo Verify the flash.
%AVRDUDE% -c stk500v2 -p m328p -P COM6 -U flash:v:%HEX%:i
echo.
