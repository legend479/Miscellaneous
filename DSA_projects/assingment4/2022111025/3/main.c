#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int main()
{
    int T;
    scanf("%d",&T);
    for(int _ =0; _ < T; ++_)
    {
        int N;
        scanf("%d",&N);
        char** Arr = (char**)malloc(sizeof(char*)*N);
        for(int i=0; i < N; ++i)
        {
            int len;
            scanf("%d",&len);
            Arr[i] = (char*)malloc(sizeof(char)*(len+1));
            scanf("%s",Arr[i]);
            Arr[i][len]='\0';
        }

        ShellSort(Arr,N,Radcmp);

        for(int j=0; j < N; ++j)
        {
            printf("%s\n",Arr[j]);
        }
        FREE(Arr,N);
    }
    return 0;
}
