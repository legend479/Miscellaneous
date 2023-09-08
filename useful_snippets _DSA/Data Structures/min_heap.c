//heap structure
typedef long HeapElementType;
typedef struct HeapSentinel
{
    int Capacity;
    int NumOfEle;
    HeapElementType* HeapArray;
}HeapSentinel;

//heap functions
HeapSentinel* CreateHeap(int capacity);
void DestroyHeap(HeapSentinel* H);

void Insert(HeapSentinel* H, HeapElementType X);
void Delete(HeapSentinel* H, int pos);
HeapElementType ExtractRoot(HeapSentinel* H);
HeapElementType FindRoot(HeapSentinel* H);
void Replace(HeapSentinel* H, HeapElementType X, int pos);

//hepler functions
void PrintHeap(HeapSentinel* H);
int Parent(int i);
int LeftChild(int i);
int RightChild(int i);
void siftup(HeapSentinel* H, int pos);
void siftdown(HeapSentinel* H, int pos);
HeapSentinel* BuildHeap(HeapElementType* A, int N);

#include <stdio.h>
#include <stdlib.h>

//MIN_HEAP
//heap functions
HeapSentinel* CreateHeap(int capacity)
{
    HeapSentinel* H = (HeapSentinel*)malloc(sizeof(HeapSentinel));
    H->Capacity = capacity;
    H->NumOfEle = 0;
    H->HeapArray = (HeapElementType*)malloc(sizeof(HeapElementType) * (capacity)); 
    return H;
}
void DestroyHeap(HeapSentinel* H)
{
    free(H->HeapArray);
    free(H);
    return;    
}
void Insert(HeapSentinel* H, HeapElementType X)
{
    H->HeapArray[H->NumOfEle] = X;
    siftup(H, H->NumOfEle);
    ++H->NumOfEle;
    return;
}
void Delete(HeapSentinel* H, int pos)
{
    //delete the node
    --H->NumOfEle; 
    //swap with leaf
    H->HeapArray[pos] = H->HeapArray[H->NumOfEle] ^ H->HeapArray[pos];
    H->HeapArray[H->NumOfEle] = H->HeapArray[H->NumOfEle] ^ H->HeapArray[pos];
    H->HeapArray[pos] = H->HeapArray[H->NumOfEle] ^ H->HeapArray[pos];
    //siftdown the leaf node
    siftdown(H,pos);
    return;
}
HeapElementType ExtractRoot(HeapSentinel* H)
{   
    //adjusting size of heap
    --H->NumOfEle;
    if(H->NumOfEle==0)return H->HeapArray[0];
    //swap with leaf
    H->HeapArray[0] = H->HeapArray[0] ^ H->HeapArray[H->NumOfEle];
    H->HeapArray[H->NumOfEle] = H->HeapArray[0] ^ H->HeapArray[H->NumOfEle];
    H->HeapArray[0] = H->HeapArray[0] ^ H->HeapArray[H->NumOfEle];
    //siftdown leaf node
    siftdown(H,0);
    //returning root
    return H->HeapArray[H->NumOfEle];
}
HeapElementType FindRoot(HeapSentinel* H)
{
    return H->HeapArray[0];
}
void Replace(HeapSentinel* H, HeapElementType X, int pos)//Heap dependent
{
    if(H->HeapArray[pos] > X)
    {
        H->HeapArray[pos] = X;
        siftup(H,pos);
    }
    else
    {
        H->HeapArray[pos] = X;
        siftdown(H,pos);
    }
    return;
}

//helper functions
int Parent(int i)
{
    return (i-1)/2;
}
int LeftChild(int i)
{
    return (2*i + 1);
}
int RightChild(int i)
{
    return (2*i +2);
}
void siftup(HeapSentinel* H, int pos)//Heap dependent
{
    if(H->HeapArray[pos] < H->HeapArray[Parent(pos)])
    {
        //swap
        H->HeapArray[pos] = H->HeapArray[pos] ^ H->HeapArray[Parent(pos)];
        H->HeapArray[Parent(pos)] = H->HeapArray[pos] ^ H->HeapArray[Parent(pos)];
        H->HeapArray[pos] = H->HeapArray[pos] ^ H->HeapArray[Parent(pos)];

        //recursion op
        siftup(H,Parent(pos));
    }
    return;
}
void siftdown(HeapSentinel* H, int pos)//Heap dependent
{
    int MinChild;
    if(LeftChild(pos)>=H->NumOfEle)return;
    else if(RightChild(pos)>=H->NumOfEle)MinChild = LeftChild(pos);
    else MinChild = H->HeapArray[LeftChild(pos)]<H->HeapArray[RightChild(pos)]?LeftChild(pos):RightChild(pos);
    
    if(H->HeapArray[pos] > H->HeapArray[MinChild])
    {
        //swap
        H->HeapArray[pos] = H->HeapArray[pos] ^ H->HeapArray[MinChild];
        H->HeapArray[MinChild] = H->HeapArray[pos] ^ H->HeapArray[MinChild];
        H->HeapArray[pos] = H->HeapArray[pos] ^ H->HeapArray[MinChild];

        //recursion op
        siftdown(H,MinChild);
    }
    return;
}
HeapSentinel* BuildHeap(HeapElementType* A, int N)
{
    HeapSentinel* H = CreateHeap(N);
    for(int i=0; i<N; ++i)
    {
        H->HeapArray[i]=A[i];
    }
    H->NumOfEle = N;
    for(int i = (N-2)/2; i >= 0; --i)
    {
        siftdown(H,i);
    }
    return H;
}

//public helper
void PrintHeap(HeapSentinel* H)
{
    for(int i = 0; i<H->NumOfEle; ++i)
    {
        printf("%ld ",H->HeapArray[i]);
    }
    printf("\n");
}