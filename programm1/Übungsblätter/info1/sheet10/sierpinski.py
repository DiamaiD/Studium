#!/usr/bin/python3

from tkinter import *

def setup(fg, bg):
    reset()
    speed(0)
    color(fg, bg)
    hideturtle()

def dreieckzeichnen(size):
    forward(size)
    left(120)
    forward(size)
    left(120)
    forward(size)
    left(120)

def sierpinski(size: int, n: int):
    if n == 0:
        dreieckzeichnen(size)
    else:
        sierpinski(size/3, n-1)

sierpinski(100,1)