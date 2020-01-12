# Example Chapter06_01a
# A CRC Benchmark with ROM-based Table and Data

Example chapter06_01a has essentially the same functionality
as example chapter06_01. The checksum table and
benchmark data, however, are ROM-able.

# ROM-ing the Table and Data

Close examination of map files created in the
previous example06_01 reveals that both the benchmark data
<img src="https://render.githubusercontent.com/render/math?math=1{\ldots}9">
as well as the CRC32/MPEG2 `table` are stored in
static RAM.

The present example chapter06_01a purposely places
these objects in program ROM code and uses a specialized
"ROM iterator" to access their data.

A complete rebuild of this project and subsequent analysis
of the map files reveals that the data objects
have been successfully placed in ROM program code.
In other words, they have been _ROM_'ed.

# Application Description

The same standard CRC checksum and verification
is carried out in the `app::benchmark::task_func`
function. Slight sylistic differences between the algorithms in
example06_01 and example06_01a reflect no functional change.
