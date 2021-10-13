#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Aug 30 17:18:36 2019

@author: lada
"""

from zarizeni import pyf411
from time import sleep

led = pyf411(dev='/dev/ttyACM0')

led.perioda(20) # ms
led.sirkapulsu(20000) # us
