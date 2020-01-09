#!/usr/bin/python3

def powerset(s: list) -> list:
    n = 0
    powerlist = []
    while n < len(s):
        if n == 0:
            for i in s:
                powerlist.append([i])
        else:
            for i in s:
                for j in s[1:]:
                    if i != j and [i,j] not in powerlist and []:
                        powerlist.append([i,j])
        n += 1
    print (powerlist)

if __name__ == '__main__':
    powerset([1,2,3,4])