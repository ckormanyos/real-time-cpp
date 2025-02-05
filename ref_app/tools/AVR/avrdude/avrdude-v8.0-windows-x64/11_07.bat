echo off

set AVRDUDE=.\avrdude.exe

set HEX=../../../../../examples/chapter11_07/bin/chapter11_07.hex


rem Erase the chip.
echo "Erase the chip."
%AVRDUDE% -c avrisp2 -p m328p -P usb -e
echo.

rem Flash the HEX-file.
echo "Flash the HEX-file."
%AVRDUDE% -c avrisp2 -p m328p -P usb -U flash:w:%HEX%:i
echo.

rem Verify the flash.
echo "Verify the flash."
%AVRDUDE% -c avrisp2 -p m328p -P usb -U flash:v:%HEX%:i
echo.
