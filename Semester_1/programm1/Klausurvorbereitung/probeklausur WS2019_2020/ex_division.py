#!/usr/bin/python

def divide(a: int, b: int) -> int:
    x = 0
    while a > b:
        a = a - b
        x += 1
    return x