#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int main()
{
    int T;
    scanf("%d",&T);
    for(int _=0; _ < T; ++_)
    {
        int N;
        scanf("%d",&N);
        int* Arr[N];//Arr[0]->A;Arr[1]->B
        int Index[N];

        for (int i = 0; i < N; ++i)
        {
            Arr[i] = (int*) malloc(sizeof(int)*2);
            scanf("%d",&Arr[i][0]);
        }

        for (int j = 0; j < N; ++j)
        {
            scanf("%d",&Arr[j][1]);
            Index[j]=j;
        }

        QuickSort(Arr, N, cmp, Index);
        
        SortInPlace(Arr,Index,N);

        // Test Print    
        // for (int x = 0; x < N; ++x) printf("A[%d]:%d B[%d]:%d\n",x,Arr[x][0],x,Arr[x][1]);
        
        int J2[N];
        int J1[N];
        J1[0] = Arr[0][0];
        J2[0] = Arr[0][0] < Arr[0][1]? Arr[0][0]: Arr[0][1];

        for (int MinIndx = 1; MinIndx < N; ++MinIndx)
        {
            J1[MinIndx] = Arr[MinIndx][0];
            J2[MinIndx] = Arr[MinIndx][0];
            if(Arr[MinIndx][1] < Arr[MinIndx][0] && Arr[MinIndx][1] >= J2[MinIndx -1]) J2[MinIndx] = Arr[MinIndx][1];
        }

        printf("%d %d\n",J1[N-1],J2[N-1]);        

        FreeArr(Arr,N);


    }
    return 0;
}
