"""
Design sketch for QuickSort Algorithm.

"""

import random
import sys
from time import monotonic


def quicksort(array, if_randomized=True):
    """
    Sort array in ascending order.
    Wrapper for the sorting method.

    Args:
        int[] array:    integer array
        bool if_randomized:    method how to pick pivot. True if randomized.

    Testexamples:
    1 with []:
    >>> ls1=[]
    >>> quicksort(ls1,True)
    >>> ls1
    []
    >>> quicksort(ls1,False)
    >>> ls1
    []

    2 :
    >>> lss = [1,29,-8,4,78]
    >>> quicksort(lss,True)
    >>> lss
    [-8, 1, 4, 29, 78]

    3:
    >>> lss = [1,29,-8,4,78]
    >>> quicksort(lss,False)
    >>> lss
    [-8, 1, 4, 29, 78]
    """
    n = len(array)-1
    if n > 0:
        quicksort_recursive(array, 0, n, if_randomized)


def quicksort_recursive(array, left, right, if_randomized):
    """
    Method that recursively divides array on parts and calls the
    rearrangement procedure on each part.

    Args:
        int[] array:    integer array that has to be sorted
        int left:    left index from which the rearrangement starts.
        int right:    right index till which the rearrangement goes.
        bool if_randomized:    method how to pick pivot. True if randomized.

    Testexamples:

    case1: with True
    >>> lst1 = [4, 5, 2, 7,3]
    >>> quicksort_recursive(lst1, 1, 3, True)
    >>> lst1
    [4, 2, 5, 7, 3]
    >>> quicksort_recursive(lst1, 2, 4, True)
    >>> lst1
    [4, 2, 3, 5, 7]
    >>> quicksort_recursive(lst1, 0, 4, True)
    >>> lst1
    [2, 3, 4, 5, 7]

    case 2: With False
    >>> lst2 = [4, 5, 2, 7,3]
    >>> quicksort_recursive(lst1, 1, 3, False)
    >>> lst2
    [4, 5, 2, 7, 3]
    >>> quicksort_recursive(lst2, 2, 4, False)
    >>> lst2
    [4, 5, 2, 3, 7]
    >>> quicksort_recursive(lst2, 0, 4, False)
    >>> lst2
    [2, 3, 4, 5, 7]
    """
    if left >= right:
        return
    p = quicksort_divide(array, left, right, if_randomized)
    quicksort_recursive(array, left, p-1, if_randomized)
    quicksort_recursive(array, p+1, right, if_randomized)


def quicksort_divide(array, left, right, if_randomized):
    """
    Method that executes the divide step of the algorithm. Method chooses
    pivot element and  performs rearrangement of the elements inside of
    the array in such a way, that elements that are smaller than pivot are
    placed to the left of it, and elements that are larger than pivot are
    placed the the right of pivot.

    Args:
        int[] array:    integer array that has to be rearranged.
        int left:    left index from which the rearrangement starts.
        int right:    right index till which the rearrangement goes.
        bool if_randomized:    method how to pick pivot. True if randomized.
    Returns:
        int:    index where the pivot after the split is.

    Testexamples:
    case 1: with Random can only get the different value,no need to test
    >>> ls = [ 88,-1, 12,56,-10 ]
    >>> a = quicksort_divide(ls, 3, 4, True)
    >>> a in [3, 4]
    True

    case 2: with  False
    >>> ls = [ 88,-1, 12,56,-10 ]
    >>> quicksort_divide(ls, 3, 4, False)
    4
    >>> ls
    [88, -1, 12, -10, 56]
    >>> quicksort_divide(ls, 1, 3, False)
    2
    >>> ls
    [88, -10, -1, 12, 56]
    >>> quicksort_divide(ls, 0, 3, False)
    3
    >>> ls
    [12, -10, -1, 88, 56]
    >>> quicksort_divide(ls, 0, 4, False)
    2
    >>> ls
    [-1, -10, 12, 88, 56]
    """
    if if_randomized is True:
        i = random.randint(left, right)
        array[i], array[left] = array[left], array[i]
    pivotindex = left
    pivot = array[pivotindex]
    # with 2 pointers :left and right
    while left < right:
        # compare until the pointed number < Pivot,jump up
        while left < right and array[right] >= pivot:
            right -= 1
        # then left-side, until the numer > pivot , jump up
        while left < right and array[left] <= pivot:
            left += 1
        # exchange both of them
        array[left], array[right] = array[right], array[left]
    # now left = right in the mitte, place the pivot here
    array[pivotindex], array[left] = array[left], array[pivotindex]
    # get p index, left or right
    return right


def quicksort_random_performance():
    """Perform  timing test for quicksort"""
    number_of_iterations = 5
    for i in range(100, 5001, 100):
        timing = 0.0
        for _ in range(number_of_iterations):
            random.seed(30)
            array = [random.randint(-1000, 1000) for _ in range(i, -1, -1)]
            start = monotonic() * 1000
            quicksort(array, True)
            timing += (monotonic() * 1000) - start
        print("{size}\t{runtime}".format(
            size=i, runtime=timing/number_of_iterations))
        sys.stdout.flush()


def quicksort_performance():
    """Perform  timing test for quicksort"""
    number_of_iterations = 5
    for i in range(100, 5001, 100):
        timing = 0.0
        for _ in range(number_of_iterations):
            random.seed(30)
            array = [random.randint(-1000, 1000) for _ in range(i, -1, -1)]
            start = monotonic() * 1000
            quicksort(array, False)
            timing += (monotonic() * 1000) - start
        print("{size}\t{runtime}".format(
            size=i, runtime=timing/number_of_iterations))
        sys.stdout.flush()


def quicksort_reverse_random_performance():
    """Perform  timing test for quicksort"""
    number_of_iterations = 5
    for i in range(100, 5001, 100):
        timing = 0.0
        for _ in range(number_of_iterations):
            random.seed(30)
            array = [j for j in range(i, -1, -1)]
            start = monotonic() * 1000
            quicksort(array, True)
            timing += (monotonic() * 1000) - start
        print("{size}\t{runtime}".format(
            size=i, runtime=timing/number_of_iterations))
        sys.stdout.flush()


def quicksort_reverse_performance():
    """Perform  timing test for quicksort"""
    number_of_iterations = 5
    for i in range(100, 5001, 100):
        timing = 0.0
        for _ in range(number_of_iterations):
            random.seed(30)
            array = [j for j in range(i, -1, -1)]
            start = monotonic() * 1000
            quicksort(array, False)
            timing += (monotonic() * 1000) - start
        print("{size}\t{runtime}".format(
            size=i, runtime=timing/number_of_iterations))
        sys.stdout.flush()


if __name__ == '__main__':
    quicksort_reverse_random_performance()
