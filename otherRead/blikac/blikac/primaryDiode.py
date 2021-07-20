#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Aug 30 17:18:36 2019

@author: Dan
"""

from zarizeni import pyf429
from time import sleep

led = pyf429(dev='/dev/ttyACM0')

led.proud(5) # mA
led.perioda(0.02) # ms
led.sirkapulsu(10) # us
led.LED3(1)
led.LED2(0)
led.LED1(0)
