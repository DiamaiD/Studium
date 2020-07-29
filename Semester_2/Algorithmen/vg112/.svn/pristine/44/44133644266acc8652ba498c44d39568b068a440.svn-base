
import math # noqa
import random # noqa
import time # noqa

from Queue import Queue # noqa

from ListElement import ListElement # noqa

from BucketSort import bucket_sort


def radix_sort(array, k):
    '''
    Implements the radix sort algorithm to sort
        data elements with keys in range(k+1)

    Args:
        array: array of data elements
        k: largest key
        key: a function mapping data elements to values
        in range(k+1) (idendity function as default)
    eg:
    >>> radix_sort([], 0)
    []
    >>> A = radix_sort([121,311,141,15], 311)
    >>> A == [15, 121, 141, 311]
    True
    >>> B = radix_sort([121,311,141,15], 0)
    >>> B!= A
    True
    >>> C = radix_sort([121,311,141,15], 121)
    >>> C== A
    True
    '''

    # count the iterations for bucketSort
    niter = 1
    while(True):
        niter += 1
        k = k / 10
        if k / 10 < 1:
            break

    # do the niter iterations via bucketSort
    for i in range(niter):
        array = bucket_sort(array, 9, lambda x: x / 10**i % 10)

    return array


def radix_sort_performance():
    for k in range(10**4, (5*(10**5))+1, 10**4):
        array = [random.randint(0, k) for i in range(10**4)]
        start_time = time.time()
        radix_sort(array, k)
        run_time = (time.time() - start_time) * 1000
        print("%d\t%.1f" % (k, run_time))


if __name__ == "__main__":
    radix_sort_performance()
