//quicksort
#include<stdio.h>
#include<stdlib.h>

#define threshold 10//threshold for insertion sort, -1 for no optimization
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
    if(cmp(Arr[0], Arr[mid]) > 0)
        swap(&Arr[0], &Arr[mid]);
    if(cmp(Arr[0], Arr[len-1]) > 0)
        swap(&Arr[0], &Arr[len-1]);
    if(cmp(Arr[mid], Arr[len-1]) > 0)
        swap(&Arr[mid], &Arr[len-1]);
    return mid;
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

int HelperBinarySearch(ElementType* Arr, int left, int right, ElementType key, int (*cmp)(ElementType, ElementType))
{
    if(left > right)
        return left;
    int mid = (left + right) / 2;
    if(cmp(Arr[mid], key) > 0)
        return HelperBinarySearch(Arr, left, mid-1, key, cmp);
    else if(cmp(Arr[mid], key) < 0)
        return HelperBinarySearch(Arr, mid+1, right, key, cmp);
    else
        return mid;
}

void HelperInsertionSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType))
{
   for(int i=1; i<len; ++i)
   {
    ElementType key = Arr[i];
    int InsertionIndex = HelperBinarySearch(Arr, 0, i-1, Arr[i], cmp);
    for(int j=i; j>InsertionIndex; --j)
        Arr[j] = Arr[j-1];
    
    Arr[InsertionIndex] = key;
   }
}

void QuickSort(ElementType Arr[], int len, int (*cmp)(ElementType,ElementType))
{
    if(len < threshold)//optimization 
    {
        HelperInsertionSort(Arr, len, cmp);
        return;
    }
   
    else if(len < 2)return;//base case 

    int pivotIndex = MedianOfThree(Arr, len);
    if(len < 4)return;//2nd base case 
    Partion(Arr, len, &pivotIndex);
    QuickSort(Arr, pivotIndex, cmp);
    QuickSort(Arr+pivotIndex+1, len-pivotIndex-1, cmp);
}

//driver to test code
int main()
{
    int n;
    scanf("%d", &n);
    ElementType Arr[n];
    for(int i=0; i<n; ++i)
        scanf("%d", &Arr[i]);
    
    QuickSort(Arr, n, cmp);
    //HelperInsertionSort(Arr, n, cmp);
    
    for(int i=0; i<n; ++i)
        printf("%d ", Arr[i]);
    
    return 0;
}
