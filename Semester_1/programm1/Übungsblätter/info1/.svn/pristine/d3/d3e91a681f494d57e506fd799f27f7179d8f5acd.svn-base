#!/usr/bin/python3
import sys, os


def fgrep(subject: str, filename: str, v: bool, i: bool):
    """ Search for a given string in a file."""
    with open(os.path.join(sys.path[0], filename), mode="r", encoding="utf-8") as file:
        n = 0
        for line in file:
            n += 1
            if v and i:
                if subject.lower() not in line.lower():
                    yield (n, line)
            elif i and not v:
                if subject.lower() in line.lower():
                    yield (n, line)
            elif not i and v:
                 if subject not in line:
                    yield (n, line)
            else:
                if subject in line:
                    yield (n, line)