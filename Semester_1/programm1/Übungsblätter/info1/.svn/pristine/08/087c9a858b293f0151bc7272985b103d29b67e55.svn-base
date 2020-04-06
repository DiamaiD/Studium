#!/usr/bin/python3
                                                                    

def next_word(s: str) -> tuple:
    index = 0
    newindex = 0
    if s == '':
        return (None, '')
    for char in s:
        if char in "abcdefghijklmnopqrstuvwxyzäöüßABCDEFGHIJKLMNOPQRSTUVWXYZÄÖÜẞ":
            index = s.index(char)
            break
    for i in range(len(s[index:])):
        if s[index+i] not in "abcdefghijklmnopqrstuvwxyzäöüßABCDEFGHIJKLMNOPQRSTUVWXYZÄÖÜẞ":
            newindex = index+i
            return (s[index:newindex], s[newindex:])                           
    return (s, '')      

class Node():
    __init__(self, mark: str, frequency: int, left: Node, right: Node):
        self.mark = mark
        self.frequency = frequency
        self.left = left
        self.right = right

print(next_word('asdfasdfasfdasdf'))

t = Node('spam', 3, Node('eggs', 2, None, None), None)