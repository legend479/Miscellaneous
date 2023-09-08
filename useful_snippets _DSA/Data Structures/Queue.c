#ifndef Que
#define Que

//Queue
typedef void* QElemType;
typedef struct QueueNode{
    struct QueueNode* next;
    struct QueueNode* preq;
    QElemType elem;
}QueueNode;
typedef struct QueueSentinal{
    long long int NumOfElem;
    QueueNode* Head;
    QueueNode* Tail;
}QueueSentinal;

//queueFunction
QueueNode* QueueNodeINIT(QElemType elem);
QueueSentinal* QueueINIT();
void Enqueue(QueueSentinal* Q, QElemType elem);
QElemType Dequeue(QueueSentinal* Q);
void DeleteQueue(QueueSentinal* Q);

#endif

// queueFunctions
#include<stdlib.h>
#define FlagQ NULL
QueueNode *QueueNodeINIT(QElemType elem){
    QueueNode *Q = (QueueNode *)malloc(sizeof(QueueNode));
    Q->elem = elem;
    Q->next = NULL;
    Q->preq = NULL;
    return Q;
}
QueueSentinal *QueueINIT(){
    QueueSentinal *Qs = (QueueSentinal *)malloc(sizeof(QueueSentinal));
    Qs->Head = NULL;
    Qs->Tail = NULL;
    Qs->NumOfElem = 0;

    return Qs;
}
void Enqueue(QueueSentinal *Q, QElemType elem){
    QueueNode *N = QueueNodeINIT(elem);  
    if(Q->NumOfElem == 0){
        Q->Head = N;
        Q->Tail = N;
        ++Q->NumOfElem;
        return;
    }
    N->next = Q->Head;
    Q->Head->preq = N;
    Q->Head = N;
    Q->Head->preq = NULL;
    ++Q->NumOfElem;
    return;
}
QElemType Dequeue(QueueSentinal *Q){
    if(Q->NumOfElem == 0){
        return FlagQ;
    }
    else if(Q->NumOfElem == 1){
        QElemType key = Q->Tail->elem;
        free(Q->Head);
        Q->Head = NULL;
        Q->Tail = NULL;
        --Q->NumOfElem;
        return key;
    }
    QueueNode* temp = Q->Tail;
    QElemType key = Q->Tail->elem;
    Q->Tail = temp->preq;
    free(temp);
    Q->Tail->next = NULL;
    --Q->NumOfElem;
    return key;
}
void DeleteQueue(QueueSentinal* Q){
    for(long long int _ = 0; _ < Q->NumOfElem; ++_){
        Dequeue(Q);
    }
    free(Q);
    return;
}