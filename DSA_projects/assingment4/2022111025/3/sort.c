#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

//comparator function
int Radcmp(ElementType str1, ElementType str2)//return -ve if str1<str2, 0 if str1==str2, +ve if str1>str2
{
    int indx = 0;
    while(str1[indx] == str2[indx] && str1[indx] != '\0' && str2[indx] != '\0')++indx;//find first point of difference
    
    if(str1[indx]=='\0' && str2[indx]=='\0')return 0;
    else if(str1[indx]=='\0')
    {
        int retVal = indx & 0x1 ? -1: 1;
        return retVal;
    }
    else if(str2[indx]=='\0')
    {
        int retVal = indx & 0x1 ? 1: -1;
        return retVal;
    }
    else
    {
        int retVal = (indx + 1) & 0x1 ? (int)(str1[indx] - str2[indx]): (int)(str2[indx] - str1[indx]);
        return retVal;
    }
}

//helper functions
void swap(ElementType* a, ElementType* b)
{
    ElementType temp = *a;
    *a = *b;
    *b = temp;
}
int ModifiedBinarySearch(ElementType* Arr, int left, int right, ElementType key, int (*cmp)(ElementType, ElementType), int Interval)
{
    if(left > right)
        return left;
    int mid = (((left/Interval) + (right/Interval)) / 2);
    mid *= Interval;
    mid += left%Interval;
    if(cmp(Arr[mid], key) > 0)
        return ModifiedBinarySearch(Arr, left, mid-Interval, key, cmp, Interval);
    else if(cmp(Arr[mid], key) < 0)
        return ModifiedBinarySearch(Arr, mid+Interval, right, key, cmp, Interval);
    else
        return mid;
}

float logApprox( float x, int terms){
    x = 1 - x;
    float log = 0;
    for(int i = terms; i > 0; --i){
        log = log*x + (x/i);
    }
    log=-1*log;
    return log;
}

float Log3(float num){
    int NUM;
    NUM=*(int*) &num;

    float mant=((float)(NUM&0x7FFFFF))/(1<<23)+1.0f;
    

    int exp=((NUM>>23)&0xFF)-127;

    float log = (logApprox(mant,100)*logbase3e +logbase32*((float) exp));

    return log;
}

void ModifiedInsertionSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType), int Interval, int start)
{
    for(int i=start+Interval; i<len; i+=Interval)
    {
        ElementType key = Arr[i];
        int InsertionIndex = ModifiedBinarySearch(Arr, start, i-Interval, Arr[i], cmp, Interval);
        for(int j=i; j>InsertionIndex; j-=Interval)
            Arr[j] = Arr[j-Interval];
        
        Arr[InsertionIndex] = key;
    }
}


void ShellSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType))
{
    //knuth interval array for given array length
    int IntervalLen = (int)Log3(2*len+1);
    int Intervals[IntervalLen];
    Intervals[0] = 1;
    for(int i=1; i<IntervalLen; ++i)
        Intervals[i] = (3*(2*Intervals[i-1] + 1)- 1)/2;
    
    for(int i=IntervalLen-1; i>=0; --i)//itterate over intervals from max to min(1)
        for(int j=0; j<Intervals[i]; ++j)//itterate over subarrays defined by starting index
            ModifiedInsertionSort(Arr, len, cmp, Intervals[i], j);
}

void FREE(ElementType Arr[], int len)
{
    for(int i =0; i<len; ++i)
    {
        free(Arr[i]);
    }
    free(Arr);
}