#!/usr/bin/python3
import timeit

def poly_eval (p: list, x: float) -> float :
    result = 0
    i = 0
    for a in p :
        result = result + a * x ** i
        i = i + 1
    return result

def poly_eval_faster (p: list, x: float) -> float :
    result = 0
    for a in p :
        fasterbase = 0
        for i in range(p.index(a)+1):
            if i == 0:
                fasterbase = 1
            else:
                fasterbase = fasterbase * x
        result = result + a * fasterbase
    return result

def poly_eval_horner(p: list, x: float) -> float:
    result = 0
    umkehrliste = p[::-1]
    for a in umkehrliste:
        if (umkehrliste.index(a)+1) == len(p):
            result = result + a
        else:
            result = (result + a)*x
    return result 

def time_poly_eval(name: str):
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
        print(timeit.timeit(teststring, 
            setup = s, number = 1000))
    if name == "poly_eval_faster":
        teststring = "poly_eval_faster("+testliste+",2)"
        print(timeit.timeit(teststring, 
            setup = s, number = 1000))
    if name == "poly_eval_horner":
        teststring = "poly_eval_horner("+testliste+",2)"
        print(timeit.timeit(teststring, 
            setup = s, number = 1000))

time_poly_eval("poly_eval")
time_poly_eval("poly_eval_faster")
time_poly_eval("poly_eval_horner")
