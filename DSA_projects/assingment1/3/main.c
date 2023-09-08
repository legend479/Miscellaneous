#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(){
    PtrNode Head= (PtrNode) malloc(sizeof(Node));
    Head->Element=0;
    Head->nextNoode=NULL;
    int t;
    scanf("%d",&t);
    
    char Operation[6];
    for(int _=0; _<t; _++){
        scanf("%s",Operation);

        if(STRCMP(Operation,"OPER1")){
            int ele;
            scanf("%d",&ele);
            Insert(Head,ele);
        }
        else if(STRCMP(Operation,"OPER2")){
            int ele;
            scanf("%d",&ele);
            Find(Head, ele);
        }
        else if(STRCMP(Operation,"OPER3")){
            Print(Head);
        }  
    }
    return 0; 
}