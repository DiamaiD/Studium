
def selection_sort(array):
    n = len(array)
    for i in range(n-1):
        # find the minimum in array[i .. n-1]
        min_value = array[i]
        min_index = i

        for j in range(i + 1, n):
            print("left element: ",min_value, "right element: ",array[j],"\nindex of left: ", min_index, "index of right: ", j)
            if array[j] < min_value:
                print("swap\n")
                min_value = array[j]
                min_index = j
            elif array[j] == min_value:
                if j < min_index:
                    print("swap\n")
                    min_value = array[j]
                    min_index = j
            
            print("\n")

        # swap array[i] with array[min_index]
        array[i], array[min_index] = array[min_index], array[i]

    return array

selection_sort([2,1,4,6,4,3])


