#!/usr/bin/python3

class Fahrzeug:
    """Fahrzeug class"""
    def __init__(self, leergewicht: int):
        self.leergewicht = leergewicht
    def __str__(self):
        return "Fahrzeug Leergewicht: {leergewicht}".format(**self.__dict__)
    

class Kraftfahrzeug(Fahrzeug):
    """Kraftfahrzeug class"""
    def __init__(self, leergewicht: int, leistung: int):
        super().__init__(leergewicht)
        self.leistung = leistung
    def __str__(self):
        return "Kraftfahrzeug Leergewicht: {leergewicht}kg \
Leistung: {leistung}kW".format(**self.__dict__)

class Bus(Kraftfahrzeug):
    """Bus class"""
    def __init__(self, leergewicht: int, baujahr: int, leistung: int,
                       sitzplaetze: int, stehplaetze: int):
        super().__init__(leergewicht, leistung)
        self.baujahr = baujahr
        self.sitzplaetze = sitzplaetze
        self.stehplaetze = stehplaetze
    def __str__(self):
        return "Bus Leergewicht: {leergewicht}kg Baujahr: {baujahr} \
Leistung: {leistung}kW Sitzplaetze: {sitzplaetze} Stehplaetze: \
{stehplaetze}".format(**self.__dict__)

class Fahrrad(Fahrzeug):
    """Fahrrad class"""
    def __init__(self, leergewicht: int, baujahr: int, rahmengroesse: int):
        super().__init__(leergewicht)
        self.baujahr = baujahr
        self.rahmengroesse = rahmengroesse
    def __str__(self):
        return "Fahrrad Leergewicht: {leergewicht}kg \
Baujahr: {baujahr} Rahmengroesse: {rahmengroesse}cm".format(**self.__dict__)

class PKW(Kraftfahrzeug):
    """PKW class"""
    def __init__(self, leergewicht: int, baujahr: int, leistung: int,
                       sitzplaetze: int):
        super().__init__(leergewicht, leistung)
        self.baujahr = baujahr
        self.sitzplaetze = sitzplaetze
    def __str__(self):
        return "PKW Leergewicht: {leergewicht}kg Baujahr: {baujahr} \
Leistung: {leistung}kW Sitzplaetze: {sitzplaetze}".format(**self.__dict__)

class LKW(Kraftfahrzeug):
    """LKW class"""
    def __init__(self, leergewicht: int, baujahr: int, leistung: int,
                       sitzplaetze: int, zuladung: int):
        super().__init__(leergewicht, leistung)
        self.baujahr = baujahr
        self.sitzplaetze = sitzplaetze
        self.zuladung = zuladung
    def __str__(self):
        return "LKW Leergewicht: {leergewicht}kg Baujahr: {baujahr} \
Leistung: {leistung}kW Sitzplaetze: {sitzplaetze} Zuladung: {zuladung}kg\
".format(**self.__dict__)

def maut(fzg: Fahrzeug) -> int:
    """Calculate the cost of toll for the given vehicle type."""
    if isinstance(fzg, Fahrrad):
        return 0
    elif isinstance(fzg, LKW):
        return int(((fzg.leergewicht+fzg.zuladung)/10))
    elif isinstance(fzg, Bus):
        return int(fzg.leergewicht/10+(fzg.sitzplaetze+fzg.stehplaetze)*20)
    elif isinstance(fzg, PKW):
        return int(fzg.leergewicht/10+(fzg.sitzplaetze)*20)
    else:
        return int(fzg.leergewicht/10)