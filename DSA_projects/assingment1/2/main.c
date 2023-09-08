#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(){

    int t;
    scanf("%d",&t);
    
    char Operation[6];
    for(int _=0; _<t; _++){
        scanf("%s",Operation);

        if(STRCMP(Operation,"OPER1")){
            int n1,n2;
            scanf("%d %d",&n1,&n2);
            int A[n1],B[n2];
            for (int i = 0; i < n1; i++)
            {
                scanf("%d",&A[i]);
            }

            for (int j = 0; j < n2; j++)
            {
                scanf("%d",&B[j]);
            }

            int *sol=IntersectionArray(A,B,n1,n2),solLen=IntArrLen;
            
            for(int k=0; k<solLen; k++){
                printf("%d ",sol[k]);
            }
            printf("\n");
            
        }
        else if(STRCMP(Operation,"OPER2")){
            int len;
            scanf("%d",&len);

            char str[len];
            scanf("%s",str);

            char ch;
            scanf("\n%c",&ch);

            printf("%d\n",countCharOccurrences(str,len,ch));
        }
        else if(STRCMP(Operation,"OPER3")){
            int len;
            scanf("%d",&len);
            char str[len];
            scanf("%s",str);

            char ch=findFirstNonRepeatingChar(str,len);
            if(ch!='\0'){
            printf("%c\n",ch);
            }
            else{
                printf("%d\n",-1);
            }
        }
        else if(STRCMP(Operation,"OPER4")){
            int numStrs;
            scanf("%d",&numStrs);

            char **strs = (char**) calloc(numStrs,sizeof(char*));

            int maxLen=0;
            for(int i=0; i<numStrs; i++){
                int len;
                scanf("%d",&len);
                if(maxLen<len) maxLen=len;
                char* str= (char*) malloc(len*sizeof(char));
                scanf("%s",str);
                strs[i]=str;
            }
            char *sol =findLongestCommonPrefix(strs,numStrs,maxLen);
            if(sol[0]=='\0'){
                printf("%d\n",-1);
            }
            else{
                printf("%s\n",sol);
            }

        }
        else if(STRCMP(Operation,"OPER5")){
        int len;
        scanf("%d",&len);
        int Arr[len];
        for(int i=0; i<len; ++i){
            scanf("%d",&Arr[i]);
        }
        int *sol=MaxMin(Arr,len);
        
        for(int j=0; j<MxMnLen; ++j){
            printf("%d ",sol[j]);
        }
        printf("\n");
        }
        else if(STRCMP(Operation,"OPER6")){
            int strLen, substrLen;
            scanf("%d %d",&strLen,&substrLen);
            char str[strLen],substr[substrLen];
            scanf("%s",str);
            scanf("%s",substr);

            char *sol=removeSubstring(str,strLen,substr,substrLen);
            
            if(*sol=='\0'){
                printf("%d\n",-1);
            }
            else{
                printf("%s\n",sol);
            }

        }
    }

    return 0;
}
