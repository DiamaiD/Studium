
def keywords(c: str, s: str) -> list:
    indexes = []
    x = 0
    passages = []
    for char in s:
        if char == c:
            indexes.append(x)
        x += 1

    for i in range(len(indexes)):
        if i % 2 == 0:
            passages.append(s[indexes[i]+1:indexes[i+1]])
    return passages
