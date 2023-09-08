//quick k select
#include<stdio.h>
#include<stdlib.h>

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

int MedianOfThree(ElementType Arr[], int len)
{
    int mid = len/2;
    int median = 0;
    if(cmp(Arr[0],Arr[mid])<0)
    {
        if(cmp(Arr[mid],Arr[len-1])<0)
            median = mid;
        else if(cmp(Arr[0],Arr[len-1])<0)
            median = len-1;
        else
            median = 0;
    }
    else
    {
        if(cmp(Arr[0],Arr[len-1])<0)
            median = 0;
        else if(cmp(Arr[mid],Arr[len-1])<0)
            median = len-1;
        else
            median = mid;
    }

    return median;
}

void Partion(ElementType Arr[], int len, int* pivotIndex)
{
    swap(&Arr[*pivotIndex],&Arr[len -1]);
    int LeftItterator = 0;
    int RightItterator = len-2;

    while(1)
    {
        while(Arr[LeftItterator]<=Arr[len-1] && LeftItterator<len-1)++LeftItterator;
        while(Arr[RightItterator]>Arr[len-1] && RightItterator>-1)--RightItterator;
        if(LeftItterator < RightItterator)
            swap(&Arr[LeftItterator],&Arr[RightItterator]);
        else 
            break;
    }
    swap(&Arr[LeftItterator],&Arr[len-1]);
    *pivotIndex = LeftItterator;
}


ElementType QuickSearch(int k, ElementType Arr[], int len, int (*cmp)(ElementType,ElementType))
{
    if(len==1)return Arr[0];
    int pivotIndex = MedianOfThree(Arr, len);
    // int pivotIndex = len-1;
    Partion(Arr, len, &pivotIndex);
    if(pivotIndex > k-1)return QuickSearch(k, Arr, pivotIndex, cmp);
    else if(k-1==pivotIndex) return Arr[pivotIndex];
    else return QuickSearch(k-pivotIndex-1, Arr+pivotIndex+1, len-pivotIndex-1, cmp);
}

//driver to test code
int main()
{
    int n;
    scanf("%d", &n);
    ElementType Arr[n];
    for(int i=0; i<n; ++i)
        scanf("%d", &Arr[i]);
    int k;

    scanf("%d", &k);
    printf("%d\n", QuickSearch(k, Arr, n, cmp));
    

    return 0;
}