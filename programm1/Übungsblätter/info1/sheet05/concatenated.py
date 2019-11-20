#!/usr/bin/python3

def concatenated(xs: list) -> list:
    flat_list = []
    for sublist in xs:
        for item in sublist:
            flat_list.append(item)
    return flat_list

print(concatenated([[1,2],[],[3],[4,5]]))
print(concatenated([[],[],[],[]]))
