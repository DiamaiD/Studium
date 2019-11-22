#!/usr/bin/python3

def primes(n: int) -> list:
    """ Primes berechnen. """
    primzahlen = []
    for x in range(n):
        x += 1
        notprime = 0
        for prime in primzahlen:
            if (x % prime) == 0 and prime != 1:
                notprime = 1
                break
        if notprime == 0 and x != 1:
            primzahlen.append(x)
    return primzahlen
