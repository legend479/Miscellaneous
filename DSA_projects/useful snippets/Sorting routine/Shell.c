#include <stdio.h>
#include <stdlib.h>

//shell sort
typedef int ElementType;

//comparator function
int cmp(ElementType a, ElementType b)//return -ve if a<b, 0 if a==b, +ve if a>b
{
    return (a - b);
}

//helper functions
//Recursive binary search(returns the index of the first element in the array that is greater than or equal to key)
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

#define logbase3e 0.9102392266
#define logbase32 0.6309297536

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

//driver to test code
int main()
{
    int n;
    scanf("%d", &n);
    ElementType Arr[n];
    for(int i=0; i<n; ++i)
        scanf("%d", &Arr[i]);
    
    ShellSort(Arr, n, cmp);
    
    for(int i=0; i<n; ++i)
        printf("%d ", Arr[i]);
    
    return 0;
}