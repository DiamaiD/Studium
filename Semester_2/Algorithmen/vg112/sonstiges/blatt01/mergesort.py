"""
Copyright 2018, University of Freiburg.

Fabian Kuhn <kuhn@cs.uni-freiburg.de>
"""

import time
from random import randint


def mergesort_recursive(array, left, right, tmp):
    """ Sorts array[left .. right-1] by using the merge sort algorithm.

        tmp is an array that is used as temporary array for the merging
        (array tmp needs to be of at least the same size as array)

    >>> array = [3, 6, 1, 7, 9, 5, 2, 6, 0, 8]
    >>> tmp = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    >>> mergesort_recursive(array, 4, 5, tmp)
    >>> array
    [3, 6, 1, 7, 9, 5, 2, 6, 0, 8]
    >>> mergesort_recursive(array, 3, 8, tmp)
    >>> array
    [3, 6, 1, 2, 5, 6, 7, 9, 0, 8]

    """

    if right - left > 1:
        middle = (left + right) // 2
        mergesort_recursive(array, left, middle, tmp)
        mergesort_recursive(array, middle, right, tmp)

        # Merging array[left .. middle-1] and array[middle .. right-1] into tmp
        i = left
        j = middle
        pos = i
        while pos < right:
            if i < middle and (j >= right or array[i] <= array[j]):
                tmp[pos] = array[i]
                pos += 1
                i += 1
            else:
                tmp[pos] = array[j]
                pos += 1
                j += 1
        for i in range(left, right):
            array[i] = tmp[i]


def merge_sort(array):
    """ Sort array using the SelectionSort algorithm from the lecture.

    >>> merge_sort([5, 1, 3, 8])
    [1, 3, 5, 8]

    >>> merge_sort([])
    []

    >>> array = [5, 1, 8, 3, 4, 0]
    >>> merge_sort(array)
    [0, 1, 3, 4, 5, 8]

    >>> array = [2, 2, 2, 2, 1]
    >>> merge_sort(array)
    [1, 2, 2, 2, 2]

    """

    tmp = [None] * len(array)
    mergesort_recursive(array, 0, len(array), tmp)
    return array


def merge_sort_performance(rand_values=True):
    for n in range(100, 5001, 100):
        if rand_values:
            array = [randint(0, 5000) for i in range(n)]
        else:
            array = [k for k in range(n, 0, -1)]

        start_time = time.time()
        merge_sort(array)
        run_time = (time.time() - start_time) * 1000
        print("%d\t%.1f" % (n, run_time))


if __name__ == "__main__":
    merge_sort_performance(False)