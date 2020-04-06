#!/usr/bin/python

def search(key, wb: list):
    for i in wb:
        if i[0] == key:
            return i[1]

def remove(key, wb: list):
    index = 0
    for i in wb:
        if i[0] == key:
            wb.remove(i)
            return wb
        index += 1

def insert(key, value, wb: list) -> list:
    if search(key, wb):
        print("key is already inside of the list")
    else:
        wb.append((key, value))
        return wb