#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int main()
{
    int t;
    scanf("%d",&t);

    for(int i =0; i < t; ++i)
    {
        int N,K;
        scanf("%d %d",&N,&K);
        int Arr[N];
        for(int j =0; j < N; ++j)
        {
            scanf("%d",&Arr[j]);
        }
        QuickSort(Arr,N,cmp);
        long long int Happiness = WatchMovies(Arr, N, K);
        printf("%lld\n",Happiness);
    }
    return 0;
}
