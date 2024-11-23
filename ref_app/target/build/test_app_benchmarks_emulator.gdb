# ///////////////////////////////////////////////////////////////////
# //  Copyright Christopher Kormanyos 2020 - 2024.
# //  Distributed under the Boost Software License,
# //  Version 1.0. (See accompanying file LICENSE_1_0.txt
# //  or copy at http://www.boost.org/LICENSE_1_0.txt)
# //

# Connect to the target (e.g., OpenOCD or another GDB server).
target remote localhost:9999
monitor halt

# Ensure that the program is loaded.
load

# Set a breakpoint at the specified subroutine.
break app_benchmark_get_standalone_result

# Start or continue program execution.
continue

# Format and print the value of a variable.
printf "value 0x%X\n\n", app_benchmark_standalone_result

# Delete (all) breakpoint(s).
delete

# Perform a non-elegant quit of the GDB session.
quit
