//bubble sort
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
    if(a==b)return;
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}


void BubbleSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType))
{
    for(int i=len-1; i>=0; --i)
    {
        int flag = 1;
        for(int j=0; j<i; ++j)
        {
            if(cmp(Arr[j], Arr[j+1]) > 0)
            {
                swap(&Arr[j], &Arr[j+1]);
                flag = 0;
            }
        }
        if(flag) break;
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
    
    BubbleSort(Arr, n, cmp);
    
    for(int i=0; i<n; ++i)
        printf("%d ", Arr[i]);
    
    return 0;
}
