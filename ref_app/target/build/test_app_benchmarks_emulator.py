#-------------------------------------------------------------------------------
# Name:        test_app_benchmarks_emulator.py
# Purpose:
#
# Author:      Christopher Kormanyos
#
# Created:     02/04/2021
#
# Copyright:   Copyright Christopher Kormanyos 2007 - 2022
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

def execute(command, from_tty = False, to_string = False):
    gdb.execute('{}'.format(command), from_tty, to_string)


#-------------------------------------------------------------------------------
# --- class: benchmarks_emulator
#-------------------------------------------------------------------------------
class benchmarks_emulator:
    def __init__(self, tcp_port, iterations):
        self.connect_to_server(tcp_port)
        self.create_log_file()
        self.load_elf()

    # Create log file
    def create_log_file():
        logging.basicConfig(filename='emu-target.log',level=logging.DEBUG, filemode='w')
        logging.info('------- Running GDB Test -----')

    # Connect to server
    def connect_to_server(self, tcp_port):
        execute('target remote localhost:{}'.format(tcp_port))
        execute('monitor reset')
        execute('set confirm off')

    # Load object data base
    def load_elf():
        execute('load')

    # Run the benchmark
    def run():
        execute('continue')

    def next():
        execute('next')

    def set_gdb_break_point():
        return gdb.Breakpoint('app_benchmark_get_standalone_result')

    def get_gdb_result():
        return gdb.parse_and_eval("app_benchmark_standalone_result")

    # Check the gdb return value
    def check_ret_val_and_quit_gdb(ret_val):
        val_as_str = str(ret_val)
        val_as_hex = hex(int(val_as_str))

        # print the return value
        print ("Value as hex: " + str(val_as_hex))

        if val_as_hex == "0xf00dcafa":
            sys.exit(0)
        else:
            sys.exit(-1)


#-------------------------------------------------------------------------------
# --- GDB Script starts here
# See also https://embeddedartistry.com/blog/2020/11/09/metal-gdb-controlling-gdb-through-python-scripts-with-the-gdb-python-api/
#-------------------------------------------------------------------------------

# Script Config
tcp_port   = 9999
iterations = 64

# Initialize
benchmarks_emulator(tcp_port, iterations)

# Set break point and run the benchmark
bp1 = benchmarks_emulator.set_gdb_break_point()
benchmarks_emulator.run()

# Get gdb result
my_value = benchmarks_emulator.get_gdb_result()
time.sleep(0.5)
bp1.delete()

# Check the return value and quit gdb
check_ret_val_and_quit_gdb(my_value)
