import pyb,micropython,machine
import uPID
micropython.alloc_emergency_exception_buf(100)
"""
PA1 pwm tim5 ch2 teplota vykon
PA3 pwm tim2 ch4 pwmled
PA5 DAC 2 Iled
PA7 AD PT1000 teplota [-10 - 40C]-> 0-2V
"""
miliamper = micropython.const(20.0) # max proud v mA
prevod = micropython.const(miliamper/4096.0)
dacproud = pyb.DAC(2, bits=12) # zapnuti DAC s 12 bity

pinLED1 = micropython.const(pyb.Pin.board.PF6) #F6 pin pro zapnuti led
pinLED2 = micropython.const(pyb.Pin.board.PG3) #G3
pinLED3 = micropython.const(pyb.Pin.board.PG2) #G2
LED1 = pyb.Pin(pinLED1,pyb.Pin.OUT_PP) # konfigurace vystupu led
LED2 = pyb.Pin(pinLED2,pyb.Pin.OUT_PP)
LED3 = pyb.Pin(pinLED3,pyb.Pin.OUT_PP)
#LED1.value(1) # priklad zapnuti led

MHz = micropython.const(84000000) # zakladni frekvence
prescal2 = micropython.const(84) # hodnota pro nastaveni preddelice
perioda2 = micropython.const(1000000)
casovac2 = pyb.Timer(2,prescaler=prescal2-1,period=perioda2-1) # casovac na 1Hz
kanal4 = casovac2.channel(4,pyb.Timer.PWM,pin=pyb.Pin.board.PA3) # kanal na PWM
kanal4.pulse_width(100) # 100 us

prescal5 = micropython.const(4) # hodnota pro nastaveni preddelice
perioda5 = micropython.const(1050)
casovac5 = pyb.Timer(5,prescaler=prescal5-1,period=perioda5-1) # casovac na 20kHz
kanal2 = casovac5.channel(2,pyb.Timer.PWM,pin=pyb.Pin.board.PA1) # kanal na PWM
kanal2.pulse_width_percent(0)

teplota = pyb.ADC(pyb.Pin.board.PA7)
#teplota.read()

def proud(hodnota=0):
    """
    nastaveni proudu led v mA 0.0-20.0
    """
    dacproud.write(int(hodnota/prevod))

def perioda(hodnota=1000):
    """
    perioda casovace v ms
    """
    casovac2.period(int(hodnota*1000)-1)

def sirkapulsu(hodnota=100):
    """
    sirka pulsu v us
    """
    kanal4.pulse_width(hodnota-1)

def teplotaC():
    """
    teplota pt1000 v C
    """
    return teplota.read()/81.92 - 10

pid = uPID.PID(0.5, 0, 0, setpoint=4000 , sample_time=0.1, output_limits=(0,100))

def regulator(_):
    kanal2.pulse_width_percent(pid(teplota.read()))

regtim=pyb.Timer(1,freq=10)
regtim.callback(lambda t:micropython.schedule(regulator,1))
