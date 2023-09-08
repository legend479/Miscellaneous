#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int STRCMP(char*str1, char*str2){
    int i=0,f=1;
    while (!(str1[i]=='\0' || str2[i]=='\0')){
        if(str1[i]!=str2[i]){
            f=0;
            break;
        } 
        i++;
    }
    return f;
}

void Insert(PtrNode Head, int num){
    if (Head->nextNoode==NULL){
        PtrNode head= (PtrNode) malloc(sizeof(Node));
        head->Element=num;
        head->nextNoode=head;

       Head->nextNoode=head; 
    }
    else{
        PtrNode head= (PtrNode) malloc(sizeof(Node));
        head->Element=num;
        head->nextNoode=Head->nextNoode;

        PtrNode temp=Head->nextNoode;
        while (temp->nextNoode!=Head->nextNoode){
            temp=temp->nextNoode;
        }
        temp->nextNoode=head;

        Head->nextNoode=head;
    }
}

void Print( PtrNode Head){
    if(Head->nextNoode==NULL){
        printf("\n");
        return;
    }
    PtrNode temp=Head->nextNoode;
    while (temp->nextNoode!=Head->nextNoode){
        printf("%d ",temp->Element);
        temp=temp->nextNoode;
    }
    printf("%d\n",temp->Element);
}

PtrNode Find( PtrNode Head, int num ){
    if(Head->nextNoode==NULL) return NULL;

    PtrNode temp=Head->nextNoode;
    int found=1;

    while(temp->Element!=num){
        if(temp->nextNoode==Head->nextNoode){
            found=0;
            break;
        }
        temp=temp->nextNoode;
    }
    if(found){
        while(temp->nextNoode!=Head->nextNoode){
        temp->Element=temp->Element^temp->nextNoode->Element;
        temp->nextNoode->Element=temp->Element^temp->nextNoode->Element;
        temp->Element=temp->Element^temp->nextNoode->Element;
        temp = temp->nextNoode;
        }
        Head->nextNoode=temp;
        return Head->nextNoode;
    }
    else{
        return NULL;
    }

}
