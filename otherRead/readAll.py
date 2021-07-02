#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Aug  9 09:25:32 2019

@author: Dan
read Thorlabs along with temperatures of PMT and diode

Prerequisities:
sudo -H pip3 install pyvisa pyvisa-py ThorlabsPM100 pyusb
sudo apt install python3-tk
"""

from ThorlabsPM100 import ThorlabsPM100, USBTMC
import matplotlib.pyplot as plt
from time import sleep
from datetime import datetime
import os
import glob
import time

# PM init -- needs RW rights set for the device
inst = USBTMC(device="/dev/usbtmc0")
power_meter = ThorlabsPM100(inst=inst)
power_meter.sense.correction.wavelength = 380


# dallas init
base_dir = '/sys/bus/w1/devices/'
device_folder = glob.glob(base_dir + '28*')[0]
device_file = device_folder + '/w1_slave'

def read_temp_raw():
    f = open(device_file, 'r')
    lines = f.readlines()
    f.close()
    return lines
 
def read_temp():
    lines = read_temp_raw()
    while lines[0].strip()[-3:] != 'YES':
        time.sleep(0.2)
        lines = read_temp_raw()
    equals_pos = lines[1].find('t=')
    if equals_pos != -1:
        temp_string = lines[1][equals_pos+2:]
        temp_c = float(temp_string) / 1000.0
        return temp_c







filename = datetime.utcnow().strftime("read_%Y%m%d_%H%M.csv")
with open(filename,"a") as file:
    file.write("# Thorlabs Power Meter measurement log\n")
    file.write("# Preset wavelength: "+str(power_meter.sense.correction.wavelength))
    file.write("\n######################################\n")
    file.write("# Date and time,\tPM value [W],\t PMT Temp [°] \n")

for i in range(30): 
    time = datetime.utcnow().strftime("%Y/%m/%d %H:%M:%S")
    meas = power_meter.read
    temp = read_temp()
    with open(filename,"a") as file:
        file.write(time+",\t"+str(meas)+",\t" + str(temp) +"\n")
    print(time+": "+str(meas))
    sleep(1)
