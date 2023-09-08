#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int t;

    scanf("%d",&t);

    char Operation[6];
    for(int _=0; _<t; _++){
        scanf("%s",Operation);

        if(STRCMP(Operation,"OPER1")){
            int n;
            scanf("%d",&n);
            char str[n];
            scanf("%s",str);
            reverseString(str,n);
            printf("%s\n",str);
        }
        else if(STRCMP(Operation,"OPER2")){
            int n;
            scanf("%d",&n);
            char str[n];
            scanf("%s",str);
            printf("%s\n",compressString(str,n));
        }
        else if(STRCMP(Operation,"OPER3")){
            int n;
            scanf("%d",&n);
            int Arr[n],*sol;
            for(int i=0; i<n; i++){
                scanf("%d",&Arr[i]);
            }


            sol=uniqueElements(Arr,n);

            for(int j=0; j<(NumUniEle); j++){
                printf("%d ",sol[j]);
            }
            printf("\n");
            free(sol);
        }
        else if(STRCMP(Operation,"OPER4")){
            int r,c;
            scanf("%d %d",&r,&c);

            int **M= (int **) malloc(sizeof(int*)*r);
            for(int x=0; x<r; x++){
                M[x]=(int *) malloc(sizeof(int)*c);
            }

            int **sol;

            for(int i=0; i<r; i++){
                for(int j=0; j<c; j++){
                    scanf("%d",&M[i][j]);
                }
            }

            sol=transpose(M,r,c);

            for(int k=0; k<r; k++){
                free(M[k]);
            }
            free(M);

            for(int i=0; i<c; i++){
                for(int j=0; j<r; j++){
                    printf("%d ",sol[i][j]);
                }
                printf("\n");
            }    
            printf("\n");
            for(int t=0; t<c; t++){
                free(sol[t]);
            }
            free(sol);
        }
    }

    return 0;
}