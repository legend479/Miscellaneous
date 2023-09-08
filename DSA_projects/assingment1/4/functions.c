#include <stdio.h>
#include <stdlib.h>
#include "FUNCTIONS.h"

//Helper
Matrix* Init(int NumRow, int NumCol, int NumEle){
    Matrix* M = (Matrix*) malloc(sizeof(Matrix));
    M->NumRow=NumRow;
    M->NumCol=NumCol;
    M->NumEle=NumEle;

    M->NodeListHead=NULL;
    M->NodeListTail=NULL;

    return M;
}

Node* NODE(int elem, int row, int col){
    Node* N=(Node*) malloc(sizeof(Node));
    N->col=col;
    N->row=row;
    N->elem=elem;
    N->next=NULL;

    return N;
}

void CopyNode(const Node* Src, Node* Des){
    Des->col=Src->col;
    Des->elem=Src->elem;
    Des->row=Src->row;
    Des->next=NULL;
}

void Insert(Matrix* M,Node* N){
    if(M->NodeListHead!=NULL){
        M->NodeListTail->next=N;
        M->NodeListTail=N;
    }
    else{
        M->NodeListHead=N;
        M->NodeListTail=N;
    }    
}

void Print(const Matrix* M){
    printf("%d\n",M->NumEle);
    Node* temp = M->NodeListHead;
    while(temp!=NULL){
        printf("%d %d %d\n",temp->row,temp->col,temp->elem);
        temp=temp->next;
    }
}

Node* Mid(Node* Head){
    //Traverse the list at two speeds one half of other
    Node* ptr1=Head;
    Node* ptr2=Head->next;

    while(!(ptr2==NULL || ptr2->next==NULL)){
        ptr1=ptr1->next;
        ptr2=ptr2->next->next;
    }
    return ptr1;
}

Node* Merge(Node* Left, Node* Right){
    Node* sorted = (Node*)malloc(sizeof(Node));
    Node* head =(Node*)malloc(sizeof(Node));
    head = sorted;

    while(!(Left==NULL && Right==NULL)){
        if (Left == NULL){
            sorted->next=Right;
            Right=Right->next;
            sorted=sorted->next;
            continue;
        }
        else if(Right == NULL){
            sorted->next=Left;
            Left=Left->next;
            sorted=sorted->next;
            continue;
        }
        else if(Left->row < Right->row || (Left->row == Right->row && Left->col < Right->col)){
            sorted->next=Left;
            Left=Left->next;
            sorted=sorted->next;
            continue;
        }
        else{
            sorted->next=Right;
            Right=Right->next;
            sorted=sorted->next;
            continue;
        }

    }
    //free(sorted);
    return head->next;
}

Node* Sort(Node* Head){
    if(Head==NULL || Head->next==NULL)return Head;
    // left list defined by head and right list defined by rhead
    Node* mid = Mid(Head);
    Node* RHead = mid->next;
    mid->next=NULL;

    return Merge(Sort(Head),Sort(RHead));
}

Row* ROWHEAD( const Matrix* M){
    Row* RowHeads = (Row*) malloc(sizeof(Row));
    Row* RowHEAD = RowHeads;
    Node* temp = M->NodeListHead;

    RowHeads->row=temp->row;
    RowHeads->next=NULL;
    RowHeads->Rowhead=temp;
    Node* t;

    while(temp->next!=NULL){
        if(temp->next->row!=temp->row){
            Row* R = (Row*) malloc(sizeof(Row));
            R->row=temp->next->row;
            R->Rowhead=temp->next;
            R->next=NULL;

            RowHeads->next=R;
            RowHeads=R;

            t=temp;
            temp=temp->next;
            t->next=NULL;
            continue;
        }

        temp=temp->next;
    }
    return RowHEAD;
}

//Questions
Matrix* Trans(const Matrix* M){
    Matrix* Transpose=Init(M->NumCol,M->NumRow,M->NumEle);
    Node* temp=M->NodeListHead;

    while(temp!=NULL){
        Node* N = NODE(temp->elem,temp->col,temp->row);
        Insert(Transpose,N);
        temp=temp->next;
    }

    Transpose->NodeListHead=Sort(Transpose->NodeListHead);

    return Transpose;
}

Matrix* Add(const Matrix* M1, const Matrix* M2){
    Matrix* Sum = Init(M1->NumRow, M2->NumCol,0);
    Node* temp1=M1->NodeListHead;
    Node* temp2=M2->NodeListHead;

    while(!(temp1==NULL && temp2==NULL)){
        Node* sumEle = (Node*) malloc(sizeof(Node));

        if(temp1==NULL){
            CopyNode(temp2,sumEle);
            temp2=temp2->next;

            Insert(Sum,sumEle);
            ++Sum->NumEle;
            continue;
        }
        else if(temp2==NULL){
            CopyNode(temp1,sumEle);
            temp1=temp1->next;

            Insert(Sum,sumEle);
            ++Sum->NumEle;
            continue;
        }
        else if((temp1->row > temp2->row) || (temp1->row==temp2->row && temp1->col > temp2->col)){
            CopyNode(temp2,sumEle);
            temp2=temp2->next;

            Insert(Sum,sumEle);
            ++Sum->NumEle;
            continue;
        }        
        else if((temp1->row < temp2->row) || (temp1->row==temp2->row && temp1->col < temp2->col)){
            CopyNode(temp1,sumEle);
            temp1=temp1->next;

            Insert(Sum,sumEle);
            ++Sum->NumEle;
            continue;
        }
        else{
            if(temp1->elem+temp2->elem){
                sumEle->col=temp1->col;
                sumEle->row=temp2->row;
                sumEle->elem=temp1->elem + temp2->elem;
                sumEle->next=NULL;

                Insert(Sum,sumEle);
                ++Sum->NumEle;
            }
            else{
                free(sumEle);
            }
            temp1=temp1->next;
            temp2=temp2->next;
            continue;

        }
    }
    return Sum;
}

Matrix* Mul(const Matrix* M1, const Matrix* M2){
    Matrix* Product = Init(M1->NumRow,M2->NumCol,0);

    Matrix* M2T= Trans(M2);

    Row* curRow2=ROWHEAD(M2T);
    Row* RowHead2=curRow2;
    Row* curRow1=ROWHEAD(M1);

    int mulEle=0;

    while(curRow1!=NULL){
        Node* temp1=curRow1->Rowhead;
        while(curRow2!=NULL){
            mulEle=0;

            temp1 = curRow1->Rowhead;
            Node* temp2=curRow2->Rowhead;

            while(temp1!=NULL && temp2!=NULL){
                if(temp1->col==temp2->col){
                    mulEle+=(temp1->elem*temp2->elem);
                    temp1=temp1->next;
                    temp2=temp2->next;
                }
                else if(temp1->col < temp2->col){
                    temp1=temp1->next;
                }
                else{
                    temp2=temp2->next;
                }
            }
            if(mulEle!=0){
                Node* N =NODE(mulEle,curRow1->row,curRow2->row);
                Insert(Product,N);
                ++Product->NumEle;
            }
            curRow2=curRow2->next;
        }
        curRow2=RowHead2;
        curRow1=curRow1->next;
    }

    return Product;
}
