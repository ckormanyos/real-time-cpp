#-------------------------------------------------------------------------------
# Name:        test_app_benchmarks_emulator.py
# Purpose:
#
# Author:      Christopher Kormanyos
#
# Created:     02/04/2021
#
# Copyright:   Copyright Christopher Kormanyos 2020 - 2022
#
# Licence:     Distributed under the Boost Software License,
#              Version 1.0. (See accompanying file LICENSE_1_0.txt
#              or copy at http://www.boost.org/LICENSE_1_0.txt)
#-------------------------------------------------------------------------------

#!/usr/bin/env python2

# import python packages
import gdb
import time
import logging
import sys

#-------------------------------------------------------------------------------
# --- class: qemu_emulator
#-------------------------------------------------------------------------------
class qemu_emulator:
    def __init__(self, tcp_port, iterations):
        self.tcp_port   = tcp_port
        self.iterations = iterations

    # qemu initialization
    def initialize(self):
        self.connect_to_server(self.tcp_port)
        self.create_log_file()
        self.load_elf()

    # Excute gdb commands
    def execute(self, command, from_tty = False, to_string = False):
        gdb.execute('{}'.format(command), from_tty, to_string)

    # Create log file
    def create_log_file(self):
        logging.basicConfig(filename='emu-target.log',level=logging.DEBUG, filemode='w')
        logging.info('------- Running GDB Test -----')

    # Connect to server
    def connect_to_server(self, tcp_port):
        self.execute('target remote localhost:{}'.format(tcp_port))
        self.execute('monitor reset')
        self.execute('set confirm off')

    # Load object data base
    def load_elf(self):
        self.execute('load')

    # Run the benchmark
    def run(self):
        self.execute('continue')

    def next(self):
        self.execute('next')

    # Set gdb Bp
    def set_gdb_break_point(self):
        my_bp = gdb.Breakpoint('app_benchmark_get_standalone_result')
        return my_bp

    # Delete gdb Bp
    def delete_gdb_break_point(self, bp):
        bp.delete()

    # Get gdb result
    def get_gdb_result(self):
       my_result = gdb.parse_and_eval("app_benchmark_standalone_result")
       return my_result

    # Convert from gdb type to hex
    def convert_to_hex(self, gdb_value):
        val_as_str = str(gdb_value)
        val_as_hex = hex(int(val_as_str))
        return val_as_hex

    # Check the gdb return value
    def check_gdb_result(self, result_as_hex):
       if result_as_hex == "0xf00dcafe":
          return True
       else:
          return False

#-------------------------------------------------------------------------------
# --- GDB Script starts here
# See also https://embeddedartistry.com/blog/2020/11/09/metal-gdb-controlling-gdb-through-python-scripts-with-the-gdb-python-api/
#-------------------------------------------------------------------------------

# Script Config
tcp_port   = 9999
iterations = 64

# Create a qemu object
obj = qemu_emulator(tcp_port, iterations)

# Initialize
obj.initialize()

# Set break point
bp1 = obj.set_gdb_break_point()

# Run the benchmark
obj.run()

# Get gdb result
my_value = obj.get_gdb_result()
time.sleep(0.5)

# Delete break point
obj.delete_gdb_break_point(bp1)

# Convert gdb result to hex
value_as_hex = obj.convert_to_hex(my_value)

# Print the return value
print("Result value as hex: " + value_as_hex)

# Check the gdb result and quit
result_is_ok = obj.check_gdb_result(value_as_hex)

if result_is_ok == True:
    sys.exit(0)
else:
    sys.exit(-1)
