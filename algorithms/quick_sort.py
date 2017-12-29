def quickSort(array, beg, end):
    pivot = array[(beg+end)//2]
    left = beg
    right = end
    while(left <= right):
        while(array[left] < pivot):
            left+=1
        while(array[right] > pivot):
            right-=1
        if(left <= right):
            array[left],array[right] = array[right],array[left]
            left+=1
            right-=1
    if(beg < right):
        quickSort(array, beg, right)
    if(end > left):
        quickSort(array, left, end)

l = [1,2,3,2,2,10,3,3,-1,-100,-500]
quickSort(l,0,len(l)-1)
print(l)