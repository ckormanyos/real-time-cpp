# Programming the ARDUINO with `avrdude`

In this section, we will program the ARDUINO boards with `avrdude`.

Consider the flash file `ref_app.hex` which, after
building the reference application `ref_app`, will be found in the `bin` directory.
These instructions are for modern `Win*`.

The programming device being used is the AVRISP mkII, which is an older USB-based
programmer. Drivers can be installed along with with ATMEL(R) Studio.
Also alternative open source USB driver-options are available.

## Getting Started

Get a modern version of `avrdude` for `Win*` such as `avrdude-v8.0-windows-x64.zip` which can
be found within `avrdude`'s release, such as
[avrdude-v8.0](https://github.com/avrdudes/avrdude/releases).
Of course, occasional newer releases may also become available.

Using commands or command files, we can program the ARDUINO UNO with the ATMEGA328P chip
or the ARDUINO MEGA 2560 with the ATMEGA2560 chip.

### Programming the ARDUINO UNO with ATMEGA328P Chip

See also the batch file [328p.bat](./328p.bat).

```cmd
echo off

set AVRDUDE=.\avrdude.exe

set HEX=../../../../bin/ref_app.hex

rem Erase the chip.
echo "Erase the chip."
%AVRDUDE% -c avrisp2 -p m328p -P usb -e

rem Flash the HEX-file.
echo "Flash the HEX-file."
%AVRDUDE% -c avrisp2 -p m328p -P usb -U flash:w:%HEX%:i

rem Verify the flash.
echo "Verify the flash."
%AVRDUDE% -c avrisp2 -p m328p -P usb -U flash:v:%HEX%:i
```

### Programming the ARDUINO MEGA 2560 with ATMEGA2560 Chip

See also the batch file [2560.bat](./2560.bat).

```cmd
echo off

set AVRDUDE=.\avrdude.exe

set HEX=../../../../bin/ref_app.hex

rem Erase the chip.
echo "Erase the chip."
%AVRDUDE% -c avrisp2 -p m328p -P usb -e

rem Flash the HEX-file.
echo "Flash the HEX-file."
%AVRDUDE% -c avrisp2 -p m328p -P usb -U flash:w:%HEX%:i

rem Verify the flash.
echo "Verify the flash."
%AVRDUDE% -c avrisp2 -p m328p -P usb -U flash:v:%HEX%:i
```
