# Example Chapter06_14
## A CRC Benchmark with ROM-based Table and Data

Example chapter06_14 has essentially the same functionality
as example chapter06_01. The checksum table and
benchmark data, however, are ROM-able.

## ROM-ing the Table and Data

Close examination of map files created in the
previous example chapter06_01 reveals that both the benchmark data
$1~{\ldots}~9$ as well as the CRC32/MPEG2 `table` are stored in
static RAM.

The present example chapter06_14 purposely places
these objects in program ROM code and uses a specialized
_ROM_-_iterator_ to access their data.

A complete rebuild of this project and subsequent analysis
of the map files reveals that the data objects
have been successfully placed in ROM program code.
In other words, they have been _ROM_'ed.

As it turns out, _ROM_-ing constant data can at times require
somewhat intricate programming. In particular, this is the case
for the gcc-avr tool chain. Example chapter06_14 puts some
semi-formal structure (in C++11-style) around this architectural
characteristic.

## Examine the Map File

Examination of the map file can lead to insightful understanding
of what objects get placed in which parts of the memory of a microcontroller
project. How much memory do objects and subroutines require?
Where are they located? Answers to these questions can often
(at least partly) be found in the map file.

The partial image of a memory map file from example chapter06_14 for
the 8-bit target shows us that the data objects mentioned above have,
in fact, been _ROM_'ed.

![](./images/romdata.jpg)

The objects in the map-snippet above are in ROM.

## Application Description

The same standard CRC checksum and verification
is carried out in the `app::benchmark::task_func`
function. Slight sylistic differences between the algorithms in
example06_01 and example06_14 reflect no functional change.
