#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Aug  9 09:25:32 2019

@author: Dan
read Keysight multimeter
"""

import sys


from ThorlabsPM100 import ThorlabsPM100, USBTMC
import matplotlib.pyplot as plt
from time import sleep
from datetime import datetime
import os
import glob
import time
import usbtmc


#from zarizeni2 import pyf429



#keysigh voltmeter init 
instr = usbtmc.Instrument(0x2a8d, 0x1301) #address from usbtmc.list_devices()




# PM init -- needs RW rights set for the device
inst = USBTMC(device="/dev/usbtmc0")
power_meter = ThorlabsPM100(inst=inst)
power_meter.sense.correction.wavelength = 380








filename = datetime.utcnow().strftime("../AllData/diodeTest/read_%Y%m%d_%H%M.csv")
with open(filename,"a") as file:
    file.write("# Voltmeter measurement log\n")
    file.write("\n######################################\n")
    file.write("#source voltage [V] \n")

for i in range(30): 
    
    voltage = instr.ask("READ?")
    
    
    with open(filename,"a") as file:
        file.write(str(voltage) + "\n")
    print("source voltage:" + str(voltage))
    sleep(1)