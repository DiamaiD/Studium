#!/usr/bin/python3

def powerset(s: list) -> list:
    """produce a powerset of a list

        Args:
            s (list): list of an arbitrary length
        returns:
            powerlist (list): powerset of the given list
        example:
            >>> powerset([1,2])
            [[], [1], [2], [1, 2]]
    """
    powerlist = []
    if len(s) != 0:
        for i in powerset(s[1:]):
            powerlist.append(i)
            powerlist.append([s[0]]+i)
    else:
        powerlist.append([])
    
    return powerlist



if __name__ == '__main__':
    print(powerset([1,2]))