#include <stdio.h>
#include <stdlib.h>
#include"heap.h"


int main()
{
    int N;
    scanf("%d",&N);
    long A[N],smallest_D[N];
    for(int i =0; i< N; ++i)
    {
        scanf("%ld",&A[i]);
    }
    if(N != 1)
    {
        HeapSentinel* MinHeap = BuildHeap(A,N);

        for(int j =0; j<N-1; ++j)
        {
            long CurMin = ExtractRoot(MinHeap);
            if(A[j] != CurMin)
            {
                smallest_D[j] = CurMin;
            }
            else
            {
                smallest_D[j] = ExtractRoot(MinHeap);
                Insert(MinHeap,CurMin);
            }
        }

        if(FindRoot(MinHeap) != A[N-1])
        {
            smallest_D[N-1] = ExtractRoot(MinHeap);
        }
        else
    {
        long temp = smallest_D[N-2];
        smallest_D[N-2] = ExtractRoot(MinHeap);
        smallest_D[N-1] = temp;
    }

        // PrintHeap(MinHeap);
        for(int k =0; k<N; ++k)
        {
            printf("%ld ",smallest_D[k]);
        }
        printf("\n");
    }
    else{
        printf("%ld",A[0]);
    }
    return 0;
}