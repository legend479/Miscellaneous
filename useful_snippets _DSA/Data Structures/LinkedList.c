#ifndef LL
#define LL

//LinkedList
typedef struct ListNode{
    int elem;
    struct ListNode* next;
}ListNode;
typedef struct ListSentinal{
    ListNode* Head;
    ListNode* Tail;
}ListSentinal;

//LinkedListFunctions
ListSentinal* ListINIT();
ListNode* ListNodeINIT(int elem);
void Append(ListSentinal* L, int elem);
void Print(ListSentinal* L);
void DeleteList(ListSentinal* L);

#endif

#include<stdlib.h>
//LinkedListFunctions
ListSentinal* ListINIT(){
    ListSentinal* L = (ListSentinal*) malloc(sizeof(ListSentinal));
    L->Head = NULL;
    L->Tail = NULL;
    return L;
}
ListNode* ListNodeINIT(int elem){
    ListNode* L = (ListNode*) malloc(sizeof(ListNode));
    L->elem = elem;
    L->next = NULL;
    return L;
}
void Append(ListSentinal* L, int elem){
    ListNode* N = ListNodeINIT(elem);
    if(L->Head == NULL){
        L->Head = N;
        L->Tail = N;
    }
    else{
        L->Tail->next = N;
        L->Tail = N;
    }
}
void Print(ListSentinal* L){
    ListNode* curNode = L->Head;
    while(curNode != NULL){
        printf("%d ",curNode->elem);
        curNode = curNode->next;
    }
}
void DeleteList(ListSentinal* L){
    if(L->Head == NULL) return;
    ListNode* curNode = L->Head;
    L->Head = curNode->next;
    free(curNode);
    DeleteList(L);
}
