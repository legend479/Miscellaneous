//mergesort
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

//comparator function
int cmp(ElementType a, ElementType b)//return -ve if a<b, 0 if a==b, +ve if a>b
{
    return (a - b);
}

//helper functions
void Merge(ElementType Arr[], int left, int right, int mid, int (*cmp)(ElementType,ElementType))
{
    ElementType TempArr[right-left+1];
    int LeftIterrator = 0;
    int RightIterrator = 0;
    for(int i=0; i<right-left+1; ++i)
    {

        if(LeftIterrator > (mid - left))TempArr[i] = Arr[(mid+1) + RightIterrator++];
        else if(RightIterrator > (right - (mid+1)))TempArr[i] = Arr[left + LeftIterrator++];
        else if(Arr[left + LeftIterrator]>Arr[(mid+1) + RightIterrator])
        {
            TempArr[i] = Arr[(mid+1) + RightIterrator++];
        }
        else
        {
            TempArr[i] = Arr[left + LeftIterrator++];
        }
    }
    for(int i=0; i<right-left+1; ++i)
    {
        Arr[left + i] = TempArr[i];
    }
}
void sort(ElementType Arr[], int left, int right, int (*cmp)(ElementType, ElementType))
{
    if(left >= right)return;
    int mid=(left+right)/2;
    sort(Arr, left, mid, cmp);
    sort(Arr, mid+1, right, cmp);
    Merge(Arr, left, right, mid, cmp);
}


void MergeSort(ElementType Arr[], int len, int (*cmp)(ElementType, ElementType))
{
    sort(Arr, 0, len-1, cmp);
}

//driver to test code
int main()
{
    int n;
    scanf("%d", &n);
    ElementType Arr[n];
    for(int i=0; i<n; ++i)
        scanf("%d", &Arr[i]);
    
    MergeSort(Arr, n, cmp);
    
    for(int i=0; i<n; ++i)
        printf("%d ", Arr[i]);
    
    return 0;
}