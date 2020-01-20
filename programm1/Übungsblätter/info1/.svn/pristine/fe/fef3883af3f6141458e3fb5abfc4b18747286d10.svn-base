#!/usr/bin/python3

LETTERS = ("abcdefghijklmnopqrstuvwxyz"
           "ABCDEFGHIJKLMNOPQRSTUVWXYZÄÖÜäöüß")

def _next_word_helper(s: str) -> tuple:
    """Helper function for next_word."""
    if not s:
        return None, s
    if s[0] not in LETTERS:
        return None, s
    word = s[0]
    word_rest, s_rest = _next_word_helper(s[1:])
    #    word = word_rest
    # semantischer fehler, das ergebniss wird nicht aufaddiert.
    if word_rest:
        word += word_rest
    return word, s_rest

def next_word(s: str) -> tuple:
    """Return the first word of an input string s and the rest of it."""
    # while s[0] not in LETTERS
    # Syntax-Fehler, es fehlt der Doppelpunkt
    
    # while s[0] not in LETTERS:
    # Laufzeitfehler wenn man einen leeren String der funktion übergibt
    while s and s[0] not in LETTERS:
        s = s[1:]
    return _next_word_helper(s)

def test_next_word_1():
    """test function next_word with heading special characters"""
    assert next_word(" test") == ("test", "")

def test_next_word_2():
    """test function next_word with heading and trailing special characters"""
    assert next_word(" test ") == ("test", " ")

def test_next_word_3():
    """test function next_word with base case of two normal words"""
    assert next_word("test testtest") == ("test", " testtest")
    
def test_next_word_4():
    """test function next_word with empty String"""
    assert next_word("") == (None, "")