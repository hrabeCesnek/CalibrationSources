#!/usr/bin/env python
# coding: utf-8
import time
import zarizeni
import matplotlib.pyplot as plt
plt.figure()
deska=zarizeni.pyf429(dev='/dev/ttyACM4')
deska.prikaz('ovlhw.pid.Kp=0.5')
deska.prikaz('ovlhw.pid.K1=0')
deska.prikaz('ovlhw.pid.Kd=0')
deska.prikaz('ovlhw.pid.setpoint=4000')
pocet=30
x = [a+1 for a in range(pocet)]
y=[]
while(pocet):
    y+=[[int(deska.dotaz('ovlhw.teplota.read()'))/81.92 - 10,float(deska.dotaz('ovlhw.kanal2.pulse_width_percent()'))]]
    time.sleep(1)
    pocet-=1
    #print(pocet)
plt.plot(x,y)
plt.show()
print(y)
#deska.LED1(1)
#deska.LED1(0)
#deska.proud(10)
#deska.perioda(1000)
#deska.sirkapulsu(500000)
#del(deska)
