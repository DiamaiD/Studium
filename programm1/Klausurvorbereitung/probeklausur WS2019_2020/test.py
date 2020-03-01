

def count(ls):
    res = {}

    for item in ls:
        if item not in res:
            res[item] = 0
        res[item] += 1
    print (res)

ls = [1, 2, 2, 1, 'eggs', 'eggs']

count(ls)