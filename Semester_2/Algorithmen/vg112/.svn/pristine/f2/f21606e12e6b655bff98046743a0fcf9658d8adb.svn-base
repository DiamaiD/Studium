"""
Hash table with open addressing.

Copyright 2020, University of Freiburg.
Philipp Schneider <philipp.schneider@cs.uni-freiburg.de>
"""

import math
import random
import time


class HashTable:
    '''
    Hash table open adressing.
    '''

    def __init__(self, size, lin_prob=True):
        '''
        Constructor

        Attributes:
            lin_prob - whether to use linear probing
                or double hasing
            size - size of table
            table - initialized to appropriate size
        '''

        assert size > 1, "hashtable too small!"

        self.lin_prob = lin_prob
        self.size = size
        self.table = [None for i in range(size)]

    def hash(self, x, i=0):
        '''
        Method returns a hash value of a given key

        Args:
            x - key to be hashed
            i - number of collissions
        Unit-Tests (add more but leave existing tests):
            >>> ht = HashTable(103)
            >>> ht.hash(10)
            15
            >>> ht.hash(10, 2)
            17
            >>> ht = HashTable(103, False)
            >>> ht.hash(10, 0)
            15
            >>> ht.hash(10, 2)
            37
        '''
        if self.lin_prob is True:
            return (53 * x + i) % self.size
        else:
            return ((53 * x) + i * (1 + (x % (self.size - 1)))) % self.size

    def insert(self, key):
        '''
        Method inserts key into hash table
        according to the hash value of the key.

        Args:
            key - key to insert
        Unit-Tests (add more but leave existing tests):
            >>> ht = HashTable(11)
            >>> ht.insert(1); ht.insert(2); ht.insert(3)
            >>> print(ht)
            [None, None, None, None, None, 3, None, 2, None, 1, None]
        '''
        i = 0
        while(True):
            hashvalue = self.hash(key, i)
            if self.find(hashvalue) is None:
                self.table[hashvalue] = key
                break
            else:
                if i >= self.size:
                    print("Tabelle voll!")
                    break
                i += 1
                continue

    def find(self, key):
        '''
        Method finds key if it is present in the hash table.

        Args:
            key - key to find
        Returns:
            key, if present in hash table or None otherwise
        Unit-Tests:
        '''
        return self.table[key]

    def __str__(self):
        '''
        Return string representation of the hash table
        '''
        return str(self.table)


def performance(lin_prob=True, rand_input=True):
    '''
    Prints the average runtime of k insert operations
    for different sizes of key

    Args:
        lin_prob - whether linear probing or
            double hashing should be used
        rand_input - whether input should be randomized
            or a predefined (worst case) input
    '''

    m = 1009  # first prime bigger than 1000

    # repeat for increasing number of keys
    sizes = [math.floor((m * i) / 50) for i in range(1, 50)]
    for k in sizes:

        ht = HashTable(m, lin_prob)

        if rand_input:
            inputs = random.sample(range(10 * m + 1), k)
        else:
            inputs = [m * i for i in range(k + 1)]

        start_time = time.time()
        for key in inputs:
            ht.insert(key)

        total_runtime = (time.time() - start_time) * 1000000
        avg_runtime = total_runtime/k  # average time in nano sec

        print("%d\t%.2f" % (k, avg_runtime))


if __name__ == "__main__":
    performance(False, False)
