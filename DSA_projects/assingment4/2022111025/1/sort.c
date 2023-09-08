#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

//comparator function
int cmp(ElementType a, ElementType b)//return -ve if a<b, 0 if a==b, +ve if a>b
{
    return (b - a);
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
        while(cmp(Arr[LeftItterator],Arr[len-1])<0 && LeftItterator<len-1)++LeftItterator;
        while(cmp(Arr[RightItterator],Arr[len-1])>=0 && RightItterator>-1)--RightItterator;
        if(LeftItterator < RightItterator)
            swap(&Arr[LeftItterator],&Arr[RightItterator]);
        else 
            break;
    }
    swap(&Arr[LeftItterator],&Arr[len-1]);
    *pivotIndex = LeftItterator;
}

void QuickSort(ElementType Arr[], int len, int (*cmp)(ElementType,ElementType))
{   
    if(len < 2)return;//base case 

    int pivotIndex = MedianOfThree(Arr, len);
    if(len < 4)return;//2nd base case 
    Partion(Arr, len, &pivotIndex);
    QuickSort(Arr, pivotIndex, cmp);
    QuickSort(Arr+pivotIndex+1, len-pivotIndex-1, cmp);
}

//Solution function
long long int WatchMovies(int Arr[], int N, int K)
{
    long long int Happiness = 0;
    for (int i = 0; i < K; ++i)
    {
        if(Arr[0] < 0)break;
        Happiness += Arr[0]--;

        ElementType key = Arr[0];
        int InsertionIndex = 1;
        while(Arr[InsertionIndex] > key && InsertionIndex < N)
        {
            Arr[InsertionIndex - 1] = Arr[InsertionIndex];
            ++InsertionIndex;
        }
        Arr[InsertionIndex - 1] = key;
    }
    return Happiness;
}