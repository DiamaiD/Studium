#!/usr/bin/python3

def leap_year(year: int) -> bool:
    """Returns whether `year` is a leap year."""
    if year % 4 != 0:
        return False
    elif year % 400 == 0:
        return True
    elif year % 100 == 0:
        return False
    else:
        return True

def test_leap_year_1():
    """test of 'elif year % 400 == 0' in the function leap_year"""
    assert leap_year(2000) == True

def test_leap_year_2():
    """test the combination of 'year % 4 != 0' and 'elif year % 100 == 0'
    in the function leap_year"""
    assert leap_year(1900) == False

def test_leap_year_3():
    """test of 'if year % 4 != 0' in the function leap_year"""
    assert leap_year(1903) == False

def test_leap_year_4():
    """test of 'default else' in the function leap_year"""
    assert leap_year(1904) == True