#!/usr/bin/env python2
import gdb
import time
import logging

def execute(command, from_tty = False, to_string = False):
    gdb.execute('{}'.format(command), from_tty, to_string)

def connect_to_server(tcp_port):
    execute('target remote localhost:{}'.format(tcp_port))
    execute('monitor reset')
    execute('set confirm off')

def load_elf():
    execute('load')

def run():
    execute('continue')

def next():
    execute('next')

def terminate():
    execute('quit')


########################################################################################
#Config
tcp_port   = 9999
iterations = 64


#GDB script
#Connect to server
connect_to_server(tcp_port)

#Create log file
logging.basicConfig(filename='emu-target.log',level=logging.DEBUG, filemode='w')
logging.info('------- Running GDB Test -----')

#Load object data base
load_elf()

#Dummy sequence
bp1 = gdb.Breakpoint('main')
run()
time.sleep(0.5)
bp1.delete()
terminate()
