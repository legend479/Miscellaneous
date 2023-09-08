#ifndef FUNCTIONS
#define FUNCTIONS

typedef struct Node{
    int elem;
    int row;
    int col;
    struct Node* next;
}Node;

typedef struct Matrix{
    int NumEle;
    int NumRow;
    int NumCol;
    Node* NodeListHead;
    Node* NodeListTail;
} Matrix;

typedef struct Row{
    Node* Rowhead;
    int row;
    struct Row* next;
}Row;

Matrix* Init(int NumRow, int NumCol, int NumEle);

void Insert(Matrix* M,Node* N);

Matrix* Trans(const Matrix* M);

Matrix* Add(const Matrix* M1, const Matrix* M2);

Matrix* Mul(const Matrix* M1, const Matrix* M2);

void Print(const Matrix* M);

Node* Sort(Node* Head);

void CopyNode(const Node* Src, Node* Des);

#endif
