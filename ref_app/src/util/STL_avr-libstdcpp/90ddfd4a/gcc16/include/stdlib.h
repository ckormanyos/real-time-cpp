// avr-libstdcpp: removes the abs() and labs() macros of avr-libc
#pragma GCC system_header
#include_next <stdlib.h>
#undef abs
#undef labs
