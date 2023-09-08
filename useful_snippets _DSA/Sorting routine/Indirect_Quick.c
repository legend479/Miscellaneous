//quicksort
#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;

//comparator function
int cmp(ElementType a, ElementType b)//return -ve if a<b, 0 if a==b, +ve if a>b
{
    return (a - b);
}

//helper functions
void swap(int* a, int* b)
{
    if(a==b)return;
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int MedianOfThree(ElementType Arr[], int len, int Indexs[])
{
    int mid = len/2;
    if(cmp(Arr[Indexs[0]], Arr[Indexs[mid]]) > 0)
        swap(&Indexs[0], &Indexs[mid]);
    if(cmp(Arr[Indexs[0]], Arr[Indexs[len-1]]) > 0)
        swap(&Indexs[0], &Indexs[len-1]);
    if(cmp(Arr[Indexs[mid]], Arr[Indexs[len-1]]) > 0)
        swap(&Indexs[mid], &Indexs[len-1]);
    return mid;
}

void Partion(ElementType Arr[], int len, int* pivotIndex, int Indexs[])
{
    swap(&Indexs[*pivotIndex],&Indexs[len -1]);
    int LeftItterator = 0;
    int RightItterator = len-2;

    while(1)
    {
        while(LeftItterator<len-2 && cmp(Arr[Indexs[LeftItterator]],Arr[Indexs[len-1]])<0)++LeftItterator;
        while(RightItterator>0 && cmp(Arr[Indexs[RightItterator]],Arr[Indexs[len-1]])>=0)--RightItterator;
        if(LeftItterator < RightItterator)
            swap(&Indexs[LeftItterator],&Indexs[RightItterator]);
        else 
            break;
    }
    swap(&Indexs[LeftItterator],&Indexs[len-1]);
    *pivotIndex = LeftItterator;
}

void QuickSort(ElementType Arr[], int len, int (*cmp)(ElementType,ElementType), int Indexs[])
{
    if(len < 2)return;//base case 

    int pivotIndex = MedianOfThree(Arr, len, Indexs);
    if(len < 4)return;//2nd base case 

    Partion(Arr, len, &pivotIndex, Indexs);
    QuickSort(Arr, pivotIndex, cmp, Indexs);
    QuickSort(Arr, len-pivotIndex-1, cmp, Indexs+pivotIndex+1);
}

//Insite Perm Sort
void SortInPlace(ElementType Arr[], int Sorted_indexs[], int len)
{
    for(int i=0; i<len; ++i)
    {
        if(i == Sorted_indexs[i])continue;
        ElementType hole = Arr[i];
        int holeIndx = i;
        do
        {
            Arr[holeIndx] = Arr[Sorted_indexs[holeIndx]];
            int temp = holeIndx;
            holeIndx = Sorted_indexs[holeIndx];
            Sorted_indexs[temp] = temp;

        }while(Sorted_indexs[holeIndx]!=i);
        Arr[holeIndx] = hole;
        Sorted_indexs[holeIndx] = holeIndx;
        
    }
}

//driver to test code
int main()
{
    int n;
    scanf("%d", &n);
    ElementType Arr[n];
    int Indexs[n];
    for(int i=0; i<n; ++i)
    {
        scanf("%d", &Arr[i]);
        Indexs[i]=i;
    }
        
    
    QuickSort(Arr, n, cmp, Indexs);
    SortInPlace(Arr, Indexs, n);

    for(int i=0; i<n; ++i)
        printf("%d ", Arr[i]);
    printf("\n");
    
    return 0;
}
