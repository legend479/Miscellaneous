#include<stdio.h>
#include<stdlib.h>

struct Element
{
    int row;
    int col;
    int Cost;
};

typedef struct Element* HeapElementType;
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
int cmp(HeapElementType a, HeapElementType b);

//hepler functions
void PrintHeap(HeapSentinel* H);
int Parent(int i);
int LeftChild(int i);
int RightChild(int i);
void siftup(HeapSentinel* H, int pos);
void siftdown(HeapSentinel* H, int pos);
HeapSentinel* BuildHeap(HeapElementType* A, int N);

//MIN_HEAP
//heap functions
int cmp(HeapElementType a, HeapElementType b)
{
    return a->Cost - b->Cost;
}
void Swap(HeapElementType* a, HeapElementType* b)
{
    HeapElementType temp = *a;
    *a = *b;
    *b = temp;
    return;
}
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
    Swap(&H->HeapArray[pos],&H->HeapArray[H->NumOfEle]);
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
    Swap(&H->HeapArray[0],&H->HeapArray[H->NumOfEle]);
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
    if(cmp(H->HeapArray[pos] , H->HeapArray[Parent(pos)]) < 0)
    {
        //swap
        Swap(&H->HeapArray[pos],&H->HeapArray[Parent(pos)]);

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
    else MinChild = cmp(H->HeapArray[LeftChild(pos)],H->HeapArray[RightChild(pos)])<0?LeftChild(pos):RightChild(pos);
    
    if(cmp(H->HeapArray[pos] , H->HeapArray[MinChild])>0)
    {
        //swap
        Swap(&H->HeapArray[pos],&H->HeapArray[MinChild]);

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
        printf("Row: %d, Col: %d, Cost: %d\n",H->HeapArray[i]->row, H->HeapArray[i]->col, H->HeapArray[i]->Cost);
    }
    printf("\n");
}

void Print2DArray(int N, int M, int A[N][M])
{
    for(int i = 0; i<N; ++i)
    {
        for(int j = 0; j<M; ++j)
        {
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int MinWallCost(int N, int M, int Fortress[N][M])
{
    int Found[N][M];
    for (int i = 0; i < N; ++i)for(int j = 0; j < M; ++j)Found[i][j] = 0;

    HeapSentinel* H = CreateHeap(N*M*2);
    
    for(int i = 0; i < N; ++i)
    {
        HeapElementType E = (HeapElementType) malloc(sizeof(struct Element));
        E->row = i;
        E->col = M-1;
        E->Cost = Fortress[i][M-1];
        Insert(H, E);
    }
    // PrintHeap(H);
    for(int i = 0; i < M-1; ++i)
    {
        HeapElementType E = (HeapElementType) malloc(sizeof(struct Element));
        E->row = 0;
        E->col = i;
        E->Cost = Fortress[0][i];
        Insert(H, E);
    } 
    // PrintHeap(H);

    int MinCost = 0x7fffffff;
    while(H->NumOfEle)
    {
        // printf("MinCost: %d\n", MinCost);
        // PrintHeap(H);
        // Print2DArray(N,M,Found);
        
        HeapElementType E = ExtractRoot(H);
        int row = E->row;
        int col = E->col;
        int cost = E->Cost;
        // free(E);
        if(Found[row][col])continue;
        Found[row][col] = 1;
        
        if(row == N-1 || col == 0)
        {
            MinCost =cost<MinCost?cost:MinCost;
            continue;
        }

        int NeighbourRow[8] = {row-1, row+1, row, row, row-1, row+1, row-1, row+1};
        int NeighbourCol[8] = {col, col, col-1, col+1, col-1, col+1, col+1, col-1};
        for (int i = 0; i < 8; ++i)
        {
            if(NeighbourRow[i] >= 0 && NeighbourRow[i] < N && NeighbourCol[i] >= 0 && NeighbourCol[i] < M && !Found[NeighbourRow[i]][NeighbourCol[i]])
            {
                HeapElementType E = (HeapElementType) malloc(sizeof(struct Element));
                E->row = NeighbourRow[i];
                E->col = NeighbourCol[i];
                E->Cost = cost + Fortress[NeighbourRow[i]][NeighbourCol[i]];
                Insert(H, E);
            }
        }
    }
    DestroyHeap(H);
    return MinCost;
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int i = 0; i < T; ++i)
    {
        int N, M;
        scanf("%d %d", &N, &M);

        int Fortress[N][M];
        for (int j = 0; j < N; ++j)for(int k = 0; k < M; ++k)scanf("%d", &Fortress[j][k]);

        printf("%d\n", MinWallCost(N, M, Fortress));        
    }
    

    return 0;
}