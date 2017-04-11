# select No.k small ele
import random

def search(lst,k):
    i, j = 0, len(lst)-1
    pivot = lst[0]
    if i == j:
        return pivot
    while i < j:
        while i < j and lst[j] >= pivot:
            j -= 1
        if i < j:
            lst[i] = lst[j]

        while i < j and lst[i] <= pivot:
            i += 1
        if i < j:
            lst[j] = lst[i]
    else:
        lst[i] = pivot

    if i == k - 1:
        return lst[i]
    elif i > k - 1:
        return (search(lst[:i],k))
    else:
        return (search(lst[i+1:],k-i-1))

a = [random.randint(1,30) for i in range(10)]
print(sorted(a))
print(search(a,6))
