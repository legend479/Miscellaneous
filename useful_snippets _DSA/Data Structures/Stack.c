#ifndef Stk
#define Stk

//Stack
typedef struct StackNode{   
    int elem;
    struct StackNode* next;
}StackNode;
typedef struct StackSentinal{
    StackNode* Head;
    int NumOfElem;
}StackSentinal;

//stackFunction
StackNode* StackNodeINIT(int elem);
StackSentinal* StackINIT();
void Push(StackSentinal* S, int elem);
int Pop(StackSentinal* S);
int Peek(StackSentinal* S);

#endif

//function implementation
#include<stdlib.h>
#define FlagS -1

// stackFunction
StackNode *StackNodeINIT(int elem){
    StackNode *S = (StackNode *)malloc(sizeof(StackNode));
    S->elem = elem;
    S->next = NULL;
    return S;
}
StackSentinal *StackINIT(){
    StackSentinal *sS = (StackSentinal *)malloc(sizeof(StackSentinal));
    sS->Head = NULL;
    sS->NumOfElem = 0;

    return sS;
}
void Push(StackSentinal *S, int elem){
    StackNode *N = StackNodeINIT(elem);
    N->next = S->Head;
    S->Head = N;
    ++S->NumOfElem;
    return;
}
int Pop(StackSentinal *S){
    if (S->NumOfElem > 0){
        StackNode *temp = S->Head;
        int key = temp->elem;
        S->Head = S->Head->next;
        free(temp);
        --S->NumOfElem;
        return key;
    }
    return FlagS;
}
int Peek(StackSentinal *S){
    if (S->Head == NULL)
        return FlagS;
    return S->Head->elem;
}