#ifndef BST
#define BST

//BStree
typedef struct BSTreeNode{
    int key;
    int Level;
    struct BSTreeNode* LeftSubTree;
    struct BSTreeNode* RightSubTree;
}BSTreeNode;

//treeFunction
BSTreeNode* BSTreeNodeINIT(int elem, int lvl);
void Insert(BSTreeNode* Root, int elem);
void PrintTreeLvl(BSTreeNode* Root);
void PrintTreeInor(BSTreeNode* Root);

#endif

// treeFunction
#include<stdlib.h>
#include"Queue.c"

BSTreeNode *BSTreeNodeINIT(int elem, int lvl){
    BSTreeNode *N = (BSTreeNode *)malloc(sizeof(BSTreeNode));
    N->key = elem;
    N->Level = lvl;
    N->LeftSubTree = NULL;
    N->RightSubTree = NULL;

    return N;
}
void Insert(BSTreeNode *Root, int elem){
    if (Root->key > elem)
    {
        if (Root->LeftSubTree == NULL)
        {
            BSTreeNode *N = BSTreeNodeINIT(elem, Root->Level + 1);
            Root->LeftSubTree = N;
            return;
        }
        Insert(Root->LeftSubTree, elem);
    }
    else
    {
        if (Root->RightSubTree == NULL)
        {
            BSTreeNode *N = BSTreeNodeINIT(elem, Root->Level + 1);
            Root->RightSubTree = N;
            return;
        }
        Insert(Root->RightSubTree, elem);
    }
    return;
}
void PrintTreeLvl(BSTreeNode *Root){
    QueueSentinal *Q = QueueINIT();
    QueueNode* N = QueueNodeINIT(Root);
    Q->NumOfElem = 1;
    Q->Head = N;
    Q->Tail = N;

    while(Q->NumOfElem != 0){
        BSTreeNode* CurNode = Dequeue(Q);
        Enqueue(Q, CurNode->LeftSubTree);
        Enqueue(Q, CurNode->RightSubTree);

        printf("%d ",CurNode->key);
    }
    return;
}
void PrintTreeInor(BSTreeNode* Root){
    if(Root == NULL)return;
    PrintTreeInor(Root->LeftSubTree);
    printf("%d ",Root->key);
    PrintTreeInor(Root->RightSubTree);
}
