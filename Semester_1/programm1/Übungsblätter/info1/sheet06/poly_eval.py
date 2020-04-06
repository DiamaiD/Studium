#!/usr/bin/python3
import timeit

def poly_eval (p: list, x: float) -> float :
    """langsammer polynom Rechner"""
    result = 0
    i = 0
    for a in p :
        result = result + a * x ** i
        i = i + 1
    return result

def poly_eval_faster (p: list, x: float) -> float :
    """etwas schnellerer polynom Rechner"""
    result = 0
    fasterbase = 1
    for a in p :
        result = result + a * fasterbase
        fasterbase = fasterbase * x
    return result

def poly_eval_horner(p: list, x: float) -> float:
    """schneller polynom Rechner"""
    result = 0
    umkehrliste = p[::-1]
    for a in umkehrliste[:-1]:
        result = (result + a)*x
    result = result + umkehrliste[-1]
    return result 

def time_poly_eval(name: str):
    """funktion um die geschwindigkeit der polynom Rechner zu messen"""
    s = "from __main__ import "+name
    testliste = "["
    for i in range(2000):
        if i == 0:
            testliste = testliste+str(i)
        else:
            testliste = testliste+","+str(i)
    testliste = testliste+"]"
    if name == "poly_eval":
        teststring = "poly_eval("+testliste+",2)"
        print("Laufzeit von popy_eval:",timeit.timeit(teststring, 
            setup = s, number = 1000),"Sekunden")
    if name == "poly_eval_faster":
        teststring = "poly_eval_faster("+testliste+",2)"
        print("Laufzeit von popy_eval_faster:",timeit.timeit(teststring, 
            setup = s, number = 1000),"Sekunden")
    if name == "poly_eval_horner":
        teststring = "poly_eval_horner("+testliste+",2)"
        print("Laufzeit von popy_eval_horner:",timeit.timeit(teststring, 
            setup = s, number = 1000),"Sekunden")
