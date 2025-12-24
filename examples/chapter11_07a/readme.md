# Example Chapter11_07a (advanced level)
## Preemptive Multitasking Computes 100,001 Digits of Pi in Background Task

This example makes advanced use
of preemptive multitasking scheduling with a highly detailed
and exciting calculation of the mathematical constant $\pi$
to high precision. It uses a spigot-type calculation that is also
combined with a blinky application. The $\pi$ calculation
is performed perpetually and cyclically (and also numerically verified)
in a low-priority background task.

## Application Description

The background task exercises a calculation of many thousands
of digits of the mathematical constant $\pi$.
The spigot-type calculation that was introduced in earlier
examples is used.

The calculation requires significant RAM,
much more than is available on our target system with the $8$--bit microcontroller.
For this purpose, a $4~\text{MByte}$ external serial SRAM is used.
This simplifies the breadboard wiring significantly
(compared, for instance, with previo0us examples),
but does require level-shifting
to and from $3.3$_V_ and $5.0$_V_.
Level-shifting is carried out with a specialized
chip designed for this purpose.
An industry-standard display reports the
progress of the running calculation and the number of
completed computations in the current power-on cycle.


## Hardware Setup

TODO: The pin connections

TODO: The hardware setup with the $4~\text{MByte}$ serial SRAM
is pictured in the image below.
