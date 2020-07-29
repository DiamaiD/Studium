"""
Design sketch for QuickSort Algorithm.

"""

import random
from time import monotonic
import sys
sys.setrecursionlimit(5500)



def quicksort(array, if_randomized = True):
    """
    Sort array in ascending order.
    Wrapper for the sorting method.

    Args:
        int[] array:    integer array
        bool if_randomized:    method how to pick pivot. True if randomized.
        
    Testexamples:
    1:
    >>> ls1=[]
    >>> quicksort(ls1,True)
    >>> ls1
    []
    >>> quicksort(ls1,False)
    >>> ls1
    []
    
    2:
    >>> import random, copy
    >>> random.seed(30)
    >>> array = [random.randint(-1000, 1000) for _ in range(1000,-1, -1)]
    >>> array_copy = copy.deepcopy(array)
    >>> quicksort(array,True)
    >>> sorted(array_copy)==array
    True

    >>> array2= [random.randint(-1000, 1000) for _ in range(1000,-1, -1)]
    >>> array2_copy = copy.deepcopy(array2)
    >>> quicksort(array2,False)
    >>> sorted(array2_copy)==array2
    True
    """
    
    n = len(array)-1
    if n>0:
        quicksort_recursive( array , 0, n, if_randomized )
 
  


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
    
    >>> lst1 = [4, 3, 2, 1]
    >>> quicksort_recursive(lst1, 0, 3, False)
    >>> lst1
    [1, 2, 3, 4]


    """
    if left >= right:
        return
    p = quicksort_divide( array, left, right, if_randomized)
    
    quicksort_recursive( array, left, p-1, if_randomized)
    quicksort_recursive(array, p+1, right,if_randomized)
   
    


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
    case 1: with True
    
    
    """
    if left==right == 0:
        return 
 
    if if_randomized == True:
        i = random.randint(left,right)
        array[i],array[left]=array[left],array[i]
   
    pivotindex = left
         
    pivot =  array[pivotindex]
         
    # with 2 pointer :left and right
    while left <right:
        
        # compare the number from right-side until the pointed number < Pivot,jump up
        while left < right and array[right] >=pivot:
            
            right-=1
        # then left-side, until the numer > pivot , jump up
        while left < right and array[left] <=pivot:
            left+=1
        # exchange both of them 
        array[left],array[right] = array[right], array[left]
    #now left = right in the mitte, place the pivot here   
    array[pivotindex],array[left] = array[left],array[pivotindex]
   
 
    # get p index, left or right
 
    return right



def quicksort_random_performance():
    """Perform  timing test for quicksort"""
    number_of_iterations = 5
    for i in range(100, 5001, 100):
        timing = 0.0
        for _ in range(number_of_iterations):
            random.seed(30)
            array = [random.randint(-1000, 1000) for _ in range(i,-1, -1)]
            start = monotonic() * 1000
            quicksort(array,True)
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
            array = [random.randint(-1000, 1000) for _ in range(i,-1, -1)]
            start = monotonic() * 1000
            quicksort(array,False)
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
            array = [j for j in range(i,-1, -1)]
            start = monotonic() * 1000
            quicksort(array,True)
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
            array = [j for j in range(i,-1, -1)]
            start = monotonic() * 1000
            quicksort(array,False)
            timing += (monotonic() * 1000) - start
        print("{size}\t{runtime}".format(
            size=i, runtime=timing/number_of_iterations))
        sys.stdout.flush()

if __name__ == '__main__':
    quicksort_reverse_random_performance()
        



        
    
  
