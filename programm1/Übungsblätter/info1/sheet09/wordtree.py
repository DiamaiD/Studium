#!/usr/bin/python3
                                                                  

def next_word(s: str) -> tuple:
    alphabet = "abcdefghijklmnopqrstuvwxyzäöüßABCDEFGHIJKLMNOPQRSTUVWXYZÄÖÜẞ"  
    index = 0
    newindex = 0
    for char in s:
        if char in alphabet:
            index = s.index(char)
            break
    if index == 0 and s[0] not in alphabet:
        return (None, '')
    else:
        for i in range(len(s[index:])):
            if s[index+i] not in alphabet:
                newindex = index+i
                return (s[index:newindex], s[newindex:])
        return (s[index:], "")
    return (s, "")                              

class Node():
    def __init__(self, mark, frequency, left, right):
        self.mark = mark
        self.frequency = frequency
        self.left = left
        self.right = right
    def __str__(self):
        return "Node('{mark}', {frequency}, {left}, {right})".format(**self.__dict__)

def tree_str(n: Node) -> str:
    return str(n)

def word_tree(s: str) -> Node:
    wordlist = []
    numberlist = []
    nodelist = []
    while s != "":
        word, s = next_word(s)
        if word in wordlist:
            numberlist[wordlist.index(word)] += 1
        else:
            wordlist.append(word)
            numberlist.append(1)
    for i in range(len(wordlist)):
        t = Node(wordlist[i], numberlist[i], None, None)
        nodelist.append(t)
        for j in range(len(nodelist)):
            if j == 0:
                continue
            if wordlist[i] < wordlist[i-j] and nodelist[i-j].left == None:
                nodelist[i-j].left = t
                nodelist[i-j+1].left = None
            elif wordlist[i] > wordlist[i-j] and nodelist[i-j].right == None:
                nodelist[i-j].right = t
                nodelist[i-j+1].right = None
    return nodelist[0]

def word_freq(tree: Node, word: str):
    if tree.mark == word:
        return tree.frequency
    elif tree.left != None or tree.right != None:
        return word_freq(tree.left, word) or word_freq(tree.right, word)
    else:
        return 0

def print_tree(tree: Node):
    if tree != None:
        print(tree.mark+":",tree.frequency)
    if tree != None and (tree.left != None or tree.right != None):
        return print_tree(tree.left) or print_tree(tree.right)


t = word_tree("spam eggs spam eggs ham spam hamham Spam")
# print (word_freq(t, 'spam'), word_freq(t, 'ham'))
print_tree(word_tree("spam eggs spam eggs ham spam hamham Spam"))