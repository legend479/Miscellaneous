#include <stdio.h>
#include <stdlib.h>
#include "FUNCTIONS.h"

int main(){
    char operation[4];
    scanf("%s",operation);

    if(operation[0]=='A'){

        int Nrow,Ncol,Nele1,Nele2;
        scanf("%d %d %d %d",&Nrow, &Ncol, &Nele1, &Nele2);

        Matrix* M1=Init(Nrow,Ncol,Nele1);
        Matrix* M2=Init(Nrow,Ncol,Nele2);

        for(int i=0; i<Nele1; i++){
            int Row,Col,Ele;
            scanf("%d %d %d",&Row,&Col,&Ele);
            Node *N= (Node*) malloc(sizeof(Node));
            N->col=Col;
            N->elem=Ele;
            N->row=Row;
            N->next=NULL;
            Insert(M1,N);
        }
        for(int i=0; i<Nele2; i++){
            int Row,Col,Ele;
            scanf("%d %d %d",&Row, &Col, &Ele);
           Node *N= (Node*) malloc(sizeof(Node));
            N->col=Col;
            N->elem=Ele;
            N->row=Row;
            N->next=NULL;
            Insert(M2,N);
        }
        Matrix* Sum = Add(M1,M2);
        Print(Sum);
    }
    else if(operation[0]=='T'){
        int Nrow,Ncol,Nele;
        scanf("%d %d %d",&Nrow, &Ncol, &Nele);

        Matrix* M = Init(Nrow,Ncol,Nele);
        for(int i=0; i<Nele; i++){
            int Row,Col,Ele;
            scanf("%d %d %d",&Row,&Col,&Ele);
            Node *N= (Node*) malloc(sizeof(Node));
            N->col=Col;
            N->elem=Ele;
            N->row=Row;
            N->next=NULL;
            Insert(M,N);
        }

        Matrix* Transpose= Trans(M);
        Print(Transpose);
    }
    else if(operation[0]=='M'){
        int N,M,L,K1,K2;
        scanf("%d %d %d %d %d",&N, &M, &L, &K1,&K2);

        Matrix* M1=Init(N,M,K1);
        Matrix* M2=Init(M,L,K2);

        for(int i=0; i<K1; i++){
            int Row,Col,Ele;
            scanf("%d %d %d",&Row,&Col,&Ele);
            Node *N= (Node*) malloc(sizeof(Node));
            N->col=Col;
            N->elem=Ele;
            N->row=Row;
            N->next=NULL;
            Insert(M1,N);
        }
        for(int i=0; i<K2; i++){
            int Row,Col,Ele;
            scanf("%d %d %d",&Row, &Col, &Ele);
           Node *N= (Node*) malloc(sizeof(Node));
            N->col=Col;
            N->elem=Ele;
            N->row=Row;
            N->next=NULL;
            Insert(M2,N);
        }
        Matrix* Prod = Mul(M1,M2);
        Print(Prod);
    }
}