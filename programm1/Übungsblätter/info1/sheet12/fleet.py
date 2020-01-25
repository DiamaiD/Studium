#!/usr/bin/python3

class fahrzeug:
    """fahrzeug class"""
    def __init__(self, leergewicht: int):
        self.leergewicht = leergewicht
    def baum(self):
        print(self.leergewicht)

    

class kraftfahrzeug(fahrzeug):

    def __init__(self, leergewicht: int, leistung: int):
        super().__init__(leergewicht)
        self.leistung = leistung

class bus(kraftfahrzeug):
    
    def __init__(self, leergewicht: int, baujahr: int, leistung: int,
                       sitzplätze: int, stehplätze: int):
        super().__init__(leergewicht, leistung)
        self.baujahr = baujahr
        self.sitzplätze = sitzplätze
        self.stehplätze = stehplätze

testbus = bus(10,4,1999,12,13)

print(testbus.leergewicht)

