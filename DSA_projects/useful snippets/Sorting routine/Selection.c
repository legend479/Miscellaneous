//selection sort(optimised)
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

//comparator function
int cmp(ElementType a, ElementType b)//return -ve if a<b, 0 if a==b, +ve if a>b
{
    return (a - b);
}

//helper functions
void swap(ElementType* a, ElementType* b)
{
    if(a == b) return;
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}


void SelectionSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType))
{
    for(int i=0,j=len; i<j-1; ++i,--j)
    {
        int min = i;
        int max = i;
        for(int k=i; k<j; ++k)
        {
            if(cmp(Arr[k], Arr[min]) < 0)
                min = k;
            if(cmp(Arr[k], Arr[max]) > 0)
                max = k;
        }
        swap(&Arr[i], &Arr[min]);
        if(i == max)//check if max moved
            swap(&Arr[j-1], &Arr[min]);
        else
            swap(&Arr[j-1], &Arr[max]);
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
    
    SelectionSort(Arr, n, cmp);
    
    for(int i=0; i<n; ++i)
        printf("%d ", Arr[i]);
    
    return 0;
}