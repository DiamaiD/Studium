
import math # noqa
import random # noqa
import time # noqa

from Queue import Queue # noqa

from ListElement import ListElement # noqa


def bucket_sort(array, k, key=lambda x: x):
    '''
    Implements the bucket sort algorithm to sort
        data elements using a key function to
        assign sorting keys to data elements

    Args:
        array: array of data elements
        k: largest key
        key: a function mapping data elements to values
        in range(k+1) (idendity function as default)
    eg:
    >>> bucket_sort([],0)
    []
    >>> bucket_sort([11,22,1122,3501],3501)
    [11, 22, 1122, 3501]
    >>> bucket_sort([11,11,11,11],11)
    [11, 11, 11, 11]
    >>> bucket_sort([121,311,141,15],311)
    [15, 121, 141, 311]
    '''

    # prepare the Queue array
    queuearray = []
    for i in range(k+1):
        queuearray.append(Queue())

    # fill the Queue array with ListElements
    for j in array:
        elementkey = int(key(j))
        element = ListElement(j)
        queuearray[elementkey].enqueue(element)

    # empty the buckets
    array = []
    for m in queuearray:
        for i in range(m.get_length()):
            nextqueueelement = m.dequeue()
            array.append(nextqueueelement.get_key())

    return array


def bucket_sort_performance():
    for k in range(10**4, (5*(10**5))+1, 10**4):
        array = [random.randint(0, k) for i in range(10**4)]
        start_time = time.time()
        bucket_sort(array, k)
        run_time = (time.time() - start_time) * 1000
        print("%d\t%.1f" % (k, run_time))


if __name__ == "__main__":
    bucket_sort_performance()
