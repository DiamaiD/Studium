"""
Copyright 2018, University of Freiburg.

Fabian Kuhn <kuhn@cs.uni-freiburg.de>
"""

import time
from random import randint


def selection_sort(array):
    """ Sort array using the selection sort algorithm.

    >>> selection_sort([4, 6, 1, 10, 12, 1])
    [1, 1, 4, 6, 10, 12]

    >>> selection_sort([])
    []
    """

    n = len(array)
    for i in range(n-1):
        # find the minimum in array[i .. n-1]
        min_value = array[i]
        min_index = i

        for j in range(i + 1, n):
            if array[j] < min_value:
                min_value = array[j]
                min_index = j

        # swap array[i] with array[min_index]
        array[i], array[min_index] = array[min_index], array[i]

    return array


def selection_sort_performance(rand_values=True):
    for n in range(100, 5001, 100):
        if rand_values:
            array = [randint(0, 5000) for i in range(n)]
        else:
            array = [k for k in range(n, 0, -1)]

        start_time = time.time()
        selection_sort(array)
        run_time = (time.time() - start_time) * 1000
        print("%d\t%.1f" % (n, run_time))


if __name__ == "__main__":
    selection_sort_performance()