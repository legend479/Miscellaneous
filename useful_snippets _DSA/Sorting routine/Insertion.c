#include <stdio.h>
#include <stdlib.h>

//binary insertion sort
typedef int ElementType;

//comparator function
int cmp(ElementType a, ElementType b)//return -ve if a<b, 0 if a==b, +ve if a>b
{
    return (a - b);
}

//Recursive binary search(returns the index of the first element in the array that is greater than or equal to key)
int BinarySearch(ElementType* Arr, int left, int right, ElementType key, int (*cmp)(ElementType, ElementType))
{
    if(left > right)
        return left;
    int mid = (left + right) / 2;
    if(cmp(Arr[mid], key) > 0)
        return BinarySearch(Arr, left, mid-1, key, cmp);
    else if(cmp(Arr[mid], key) < 0)
        return BinarySearch(Arr, mid+1, right, key, cmp);
    else
        return mid;
}


void InsertionSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType))
{
   for(int i=1; i<len; ++i)
   {
    ElementType key = Arr[i];
    int InsertionIndex = BinarySearch(Arr, 0, i-1, Arr[i], cmp);
    for(int j=i; j>InsertionIndex; --j)
        Arr[j] = Arr[j-1];
    
    Arr[InsertionIndex] = key;
   }
}

//driver to test code
int main()
{
    int n;
    scanf("%d", &n);
    ElementType Arr[n];
    for(int i=0; i<n; ++i)
        scanf("%d", &Arr[i]);
    
    InsertionSort(Arr, n, cmp);
    
    for(int i=0; i<n; ++i)
        printf("%d ", Arr[i]);
    
    return 0;
}