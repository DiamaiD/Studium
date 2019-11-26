#!/usr/bin/python3

def poly_eval (p: list, x: float) -> float :
    result = 0
    i = 0
    for a in p :
        result = result + a * x ** i
        i = i + 1
    return result

def poly_eval_faster (p: list, x: float) -> float :
    result = 0
    i = 0
    for a in p :
        fasterbase = 0
        for i in range(p.index(a)+1):
            if i == 0:
                fasterbase = 1
            else:
                fasterbase = fasterbase * x
        result = result + a * fasterbase
    return result
print(poly_eval_faster([1,2,3],-0.1))