#!/usr/bin/python3

from turtle import *

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
    """A function to draw a sierpinski triangle

        Args:
            size (int): size of the outer triangle
            n (int): depth of the sierpinski triangle
        returns:
            None
    """
    if n == 0:
        dreieckzeichnen(size)
    else:
        sierpinski(size/2, n-1)
        forward(size/2)
        sierpinski(size/2, n-1)
        forward(size/2)
        left(120)
        forward(size/2)
        sierpinski(size/2, n-1)
        forward(size/2)
        left(120)
        forward(size)
        left(120)