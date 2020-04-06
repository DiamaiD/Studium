

def fib(n: int) -> int:
    fibliste = [0,1]
    if n == 1:
        return 0
    elif n == 2:
        return 1
    for i in range(n-2):
        fibliste.append(fibliste[-1]+fibliste[-2])
    return fibliste[-1]