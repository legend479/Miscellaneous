#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int main()
{
    int T;
    scanf("%d",&T);
    for(int _ = 0; _ < T; ++_)
    {
        int K, M;
        scanf("%d %d",&K,&M);

        int Arr[K*M];
        for(int i = 0; i < K*M; ++i)scanf("%d",&Arr[i]);
        int J;
        scanf("%d",&J);

        int J_Arr[M];
        int Possible_Winners[M];
        int PW_itterrator = 0;
        int J_itterrator =0;

        int Winner;
        for(int j =0; j < K*M; ++j)
        {   
            if(j%K == 0)Winner = -666;
            if(Winner < Arr[j] && j%K != J-1)Winner = Arr[j];
            if(j%K == K-1)Possible_Winners[PW_itterrator++] = Winner;
            if(j%K == J-1)J_Arr[J_itterrator++] = Arr[j];
        }
        //TEST
        // PRINTARR(Possible_Winners,M);
        // PRINTARR(J_Arr,M);
        MergeSort(J_Arr,M,cmp);
        MergeSort(Possible_Winners,M,cmp);

        int Wins = 0;
        for(int k=0; k<M; ++k) if(J_Arr[k] > Possible_Winners[Wins]) ++Wins;

        printf("%d\n",Wins);
    }
    return 0;
}
