# Example chapter02_02
# The LED program with timing

This example implements the LED program (with timing) for the
target with the 8-bit microcontroller.
This example builds on the previous example02_02
by including a small subset of a microcontroller
abstraction layer, enough to provide functions
for approximate timing and delays.

Building the example can be done with GNUmake
in the command batch or shell script.
The results of the build will be stored in the `bin`
directory. After successful build, files such as the HEX-file
`led.hex` and othe name and map files can be found in `bin`.

# With `GNUmake`

The classic `GNUmake` facility is used to support the build.
The user needs to supply (or modify) the `Win*` path to gcc-avr
On a `*nix` system, the tool chain should be pre-installed,
such as might be done via package management.
In `Win*`, the `GNUmake` command is executed from
`Build.bat`. The exact `Win*` command including command line
parameters is shown below.

```
Target\Build\Build.bat avr rebuild
```


# With VC or Atmel Studio

Project workspaces providing code visualization
and single-click build are provided for both
VC as well as Atmel Studio.

