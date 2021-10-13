import pyboard
class pyf429():
    def __init__(self,dev='/dev/ttyACM0'):
        self.dev=dev
        self.pyb = pyboard.Pyboard(self.dev)
        self.pyb.enter_raw_repl()
        self.prikaz('import ovlhw')
        print('pripojeno {}'.format(self.dev))

    def prikaz(self,text):
        return self.pyb.exec(text)

    def dotaz(self,text):
        return self.pyb.exec('print('+text+')').rstrip()

    def proud(self,hodnota):
        self.prikaz('ovlhw.proud({})'.format(hodnota))

    def perioda(self,hodnota):
        self.prikaz('ovlhw.perioda({})'.format(hodnota))

    def sirkapulsu(self,hodnota):
        self.prikaz('ovlhw.sirkapulsu({})'.format(hodnota))

    def LED1(self,hodnota):
        self.prikaz('ovlhw.LED1.value({})'.format(hodnota))

    def LED2(self,hodnota):
        self.prikaz('ovlhw.LED2.value({})'.format(hodnota))

    def LED3(self,hodnota):
        self.prikaz('ovlhw.LED3.value({})'.format(hodnota))

    def teplota(self):
        return float(self.dotaz('ovlhw.teplotaC()').decode())

    def __del__(self):
        self.pyb.exit_raw_repl()
        print('odpojeno {}'.format(self.dev))

class pyf411():
    def __init__(self,dev='/dev/ttyACM0'):
        self.dev=dev
        self.pyb = pyboard.Pyboard(self.dev)
        self.pyb.enter_raw_repl()
        self.prikaz('import ovlhw411')
        print('pripojeno {}'.format(self.dev))

    def prikaz(self,text):
        return self.pyb.exec(text)

    def dotaz(self,text):
        return self.pyb.exec('print('+text+')').rstrip()

    def perioda(self,hodnota):
        self.prikaz('ovlhw411.perioda({})'.format(hodnota))

    def sirkapulsu(self,hodnota):
        self.prikaz('ovlhw411.sirkapulsu({})'.format(hodnota))
        
    def vypni(self):
        self.perioda(0)

    def __del__(self):
        self.pyb.exit_raw_repl()
        print('odpojeno {}'.format(self.dev))
