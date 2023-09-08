#ifndef heap
#define heap
//heap structure
typedef long HeadElementType;
typedef struct HeapSentinel
{
    int Capacity;
    int NumOfEle;
    HeadElementType* HeapArray;
}HeapSentinel;

//heap functions
HeapSentinel* CreateHeap(int capacity);
void DestroyHeap(HeapSentinel* H);

void Insert(HeapSentinel* H, HeadElementType X);
void Delete(HeapSentinel* H, int pos);
HeadElementType ExtractRoot(HeapSentinel* H);
HeadElementType FindRoot(HeapSentinel* H);
void Replace(HeapSentinel* H, HeadElementType X, int pos);

//hepler functions
void PrintHeap(HeapSentinel* H);
int Parent(int i);
int LeftChild(int i);
int RightChild(int i);
void siftup(HeapSentinel* H, int pos);
void siftdown(HeapSentinel* H, int pos);
HeapSentinel* BuildHeap(HeadElementType* A, int N);
#endif