#!/usr/bin/python3

def powerset(s: list) -> list:
    powerlist = []
    for i in range(len(s)):
        powerlist += powerhelp(s[i:])
    print(powerlist)

def powerhelp(left):
    for i in range(len(left)):
        if i == 0:
            helplist = [left[0]]
        else:
            for j in left[i:-1]:
                if i != j:
                    helplist.append(j)
    print(helplist)
    return helplist


if __name__ == '__main__':
    powerset([1,2,3])