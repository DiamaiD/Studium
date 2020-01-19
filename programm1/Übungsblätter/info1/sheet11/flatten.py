#!/usr/bin/python3

def flatten(xs: list) -> list:
    """a function to flatten a list to its sub components"""
    flatlist = []
    for i in xs:
        if isinstance(i, list):
            flatlist += flatten(i)
        else:
            flatlist += [i]
    return flatlist

def test_flaten_1():
    """test recursion of deepth over 2"""
    assert flatten([1,2,[3,[4,[5]]]]) == [1,2,3,4,5]

def test_flaten_2():
    """test if boolean is handled right"""
    assert flatten([True,2,[3,[False,[5]]]]) == [True,2,3,False,5]

def test_flaten_3():
    """test if tupel is untouched"""
    assert flatten([(1,[10]),2,[3,[4,[5]]]]) == [(1,[10]),2,3,4,5]

def test_flaten_4():
    """test if strings are handled right"""
    assert flatten([1,2,[3,[4,["test"]]]]) == [1,2,3,4,"test"]