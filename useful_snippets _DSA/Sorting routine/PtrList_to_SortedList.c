#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;
//Sort a given array from sorted list of indexs

//extra memory method
void SortOutOfPlace(ElementType Arr[], int* Sorted_indexs, int len)
{
    ElementType TempArr[len];
    for(int i=0; i<len; ++i)
    {
        TempArr[i] = Arr[Sorted_indexs[i]];
    }
    for(int i=0; i<len; ++i)
    {
        Arr[i] = TempArr[i];
    }
}

void SortInPlace(ElementType Arr[], int* Sorted_indexs, int len)
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

//driver for code

int main()
{
    int len =7;
    ElementType Arr[]={4,2,3,1,0,5,6};
    int Sorted_Indx[]={4,3,1,2,0,5,6};

    // SortOutOfPlace(Arr,Sorted_Indx, len);
    SortInPlace(Arr, Sorted_Indx, len);

    for(int i=0; i<len; ++i)
    {
        printf("%d ",Arr[i]);
    }
}