#!/usr/bin/python3

def is_palindromic(n: int) -> bool:
    """check if a number is a palindrom"""
    stringzahl = str(n)
    length = len(stringzahl)
    stringlist = list(stringzahl)
    for x in range(int(length/2)):
        if stringlist[x] != stringlist[-(x+1)]:
            return False
    return True

def max_palindrome() -> int:
    """calculates the highest palindrom from two 3 digit numbers"""
    max_palindrome = []
    for x in range(100,1000):
        for y in range(100,1000):
            if is_palindromic(x*y):
                max_palindrome.append(x*y)
    return max(max_palindrome)
