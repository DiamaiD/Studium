#!/usr/bin/python3

def to_binary(x: int, n: int) -> list:
    binary_list = []
    if (x > 2**(n)):
        x = x % 2**(n)
    for i in range(n):
        n -= 1
        if (x > (2**(n-1))):
            print(x)
            binary_list.append(1)
            x = x - 2**(n-1) 
            print(x)
        else:
            binary_list.append(0)
    return binary_list

print(to_binary(33,8))
