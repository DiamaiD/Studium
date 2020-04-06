#!/usr/bin/python3

from turtle import *

class LSystem:
    def __init__ (self, axiom, rules):
        self.axiom = axiom
        self.rules = rules

    def applyrules (self, w):
        rules = self.rules
        r = ""
        for c in w:
            r += rules.get(c,c)
        return r

    def generate (self, n : int):
        w = self.axiom
        for i in range(n):
            w = self.applyrules (w)
        return w

def sierpinski(size: int, n: int):
    """A function to draw a sierpinski triangle with the LSystem

        Args:
            size (int): size of the outer triangle
            n (int): depth of the sierpinski triangle
        returns:
            None
    """
    ls = LSystem("F-G-G", {'F':'F-G+F+G-F','G':'GG'})
    w = ls.generate(n)
    for i in w:
        if i == 'F':
            forward(size)
        elif i == 'G':
            forward(size)
        elif i == '-':
            right(120)
        elif i == '+':
            left(120)