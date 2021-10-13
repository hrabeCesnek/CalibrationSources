import pyb,micropython,machine
"""
PA1 pwm tim2 ch4 pwmled
"""
MHz = micropython.const(48000000) # zakladni frekvence
prescal2 = micropython.const(48) # hodnota pro nastaveni preddelice
perioda2 = micropython.const(1000000)
casovac2 = pyb.Timer(2,prescaler=prescal2-1,period=perioda2-1) # casovac na 1Hz
kanal2 = casovac2.channel(2,pyb.Timer.PWM,pin=pyb.Pin.board.PA1) # kanal na PWM
kanal2.pulse_width(100) # 100 us

def perioda(hodnota=1000):
    """
    perioda casovace v ms
    """
    casovac2.period(int(hodnota*1000)-1)

def sirkapulsu(hodnota=100):
    """
    sirka pulsu v us
    """
    kanal2.pulse_width(hodnota-1)

