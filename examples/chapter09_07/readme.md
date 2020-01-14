# Example Chapter09_07
# Controlling a Seven Segment Display

Example chapter09_07 makes use of object oriented
programming methods to control a seven segment display.

# Controlling the Display

In this example, port pins are used to control a
seven segment single-character display. As in most other examples,
both a hardware version for the target system as well as a simlulated
PC version are available. The PC version writes its
character to the output console.

# Application Description

The sixteen hexadecimal digits <img src="https://render.githubusercontent.com/render/math?math=0123456789\text{AbCdEF}">
are displayed sequentially, one digit per second.
The dot (_i_._e_., period or decimal point) is toggled
on and off for successive groups of 16 hexadecimal digits.
The user LED is simultaneously toggled at the usual 1/2Hz.
