//quicksort
#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;

//comparator function
int cmp(const void* a, const void* b)//return -ve if a<b, 0 if a==b, +ve if a>b
{
    return (*((ElementType*)a) - *((ElementType*)b));
}

void SystemQuickSort(ElementType Arr[], int len, int (*cmp)(const void*,const void*))
{
    qsort(Arr, len, sizeof(ElementType), cmp);
}

//driver to test code
int main()
{
    int n;
    scanf("%d", &n);
    ElementType Arr[n];
    for(int i=0; i<n; ++i)
        scanf("%d", &Arr[i]);
    
    SystemQuickSort(Arr, n, cmp);
    
    for(int i=0; i<n; ++i)
        printf("%d ", Arr[i]);
    
    return 0;
}