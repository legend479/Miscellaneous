#include <stdio.h>
#include <stdlib.h>

int comp(const void *a, const void *b)
{
    int A = *((int *)a);
    int B = *((int *)b);
    if (A > B)
        return 1;
    else if (A == B)
        return 0;
    else
        return -1;
}

void swap(int *a, int *b)
{
    *a = *a + *b - (*b = *a);
}

int Median3(int *arr, int l, int r)
{
    int m = (l + r) / 2;
    int a = arr[l], b = arr[m], c = arr[r];
    if (a > b)
    {
        if (b > c)
            return m;
        else if (c > a)
            return l;
        else
            return r;
    }
    else
    {
        if (c > b)
            return m;
        else if (a > c)
            return l;
        else
            return r;
    }
}

void QPart(int *arr, int l, int r, int pval,int* p)
{
    if (l < r)
    {
        int i = l;
        int j = r-1;
        while (i<=j)
        {
            while (i<r && arr[i] <= pval)
                i++;
            while (j>0 &&arr[j] >= pval)
                j--;
            if(i<j)
            {
                swap(arr+i,arr+j);
            }
        }
        swap(arr+i,arr+r);
        *p=i;
    }
}

void QuickSortDriver(int *arr, int l, int r, int comp(const void *a, const void *b))
{
    if (l < r)
    {
        int p = Median3(arr, l, r);
        int pval = arr[p];
        swap(arr + p, arr + r);
        QPart(arr, l, r, pval,&p);
        QuickSortDriver(arr, l, p - 1, comp);
        QuickSortDriver(arr, p + 1, r, comp);
    }
}

void QuickSort(int *arr, int numElems, int comp(const void *a, const void *b))
{
    QuickSortDriver(arr, 0, numElems - 1, comp);
}

typedef int ElementType;
//driver to test code
int main()
{
    int n;
    scanf("%d", &n);
    ElementType Arr[n];
    for(int i=0; i<n; ++i)
        scanf("%d", &Arr[i]);

    QuickSort(Arr, n, comp);
    
    for(int i=0; i<n; ++i)
        printf("%d ", Arr[i]);
    
    return 0;
}