#include <stdio.h>
#include <stdlib.h>
#include"heap.h"


int main()
{
    int N;
    scanf("%d",&N);
    HeapSentinel* Heap = CreateHeap(N);
    int CurSum=0;
    for(int i = 0; i<N; ++i)
    {
        long CurKnob;
        scanf("%ld",&CurKnob);

        //Add elem to heap
        Insert(Heap,CurKnob);
        if(CurSum + CurKnob < 0)
        {
            CurSum += CurKnob - ExtractRoot(Heap);
        }
        else
        {
            CurSum += CurKnob;
        }
    }
    printf("%d\n",Heap->NumOfEle);
    return 0;
}