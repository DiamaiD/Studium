
A = [3,20,5,800,1]
hashtable = []

def algorithm(A):
    for i in range(len(A)):                     # n
        for j in range(i):                      # n
            hashtable.append(abs(A[i]-A[j]))    # 1

    for i in A:                                 # n
        if A in hashtable:                      # 1
            return True

    return False


def algorithm2(A):
    sorted(A)

    for i in range(len(A)): # n 
        for j in range(i): # n
            if binarysearch(A, abs(A[i]-A[j])): # log n
                return True
    return False

def binarysearch(A, k):
    # search for k in A
    # if k in A return True, otherwise False

