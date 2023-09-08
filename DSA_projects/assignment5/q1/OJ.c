#include<stdio.h>
#include<stdlib.h>

//Adjacency List Represenation of a Graph
typedef struct Edge
{
    int FromVetexIndx;
    int ToVertexIndx;
    int Weight;
    struct Edge *NextNeighbour;
}Edge;

typedef struct Vertex
{
    int VertexIndx;
    Edge *FirstNeighbour;
}Vertex;

typedef struct Graph
{
    int VertexNum;
    int EdgeNum;
    Vertex *VertexList;
}Graph;

Graph* GraphINIT(int VertexNum);
void GraphInsertEdge(Graph *G, int FromVertexIndx, int ToVertexIndx, int Weight);
void GraphDeleteEdge(Graph *G, int FromVertexIndx, int ToVertexIndx);
void GraphDestroy(Graph *G);
void GraphPrint(Graph *G);


//heap structure
typedef int HeapElementType;
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

Graph* GraphINIT(int VertexNum)
{
    Graph *G = (Graph*)malloc(sizeof(Graph));
    G->VertexNum = VertexNum;
    G->EdgeNum = 0;
    G->VertexList = (Vertex*)malloc(sizeof(Vertex)*VertexNum);
    for(int i = 0; i < VertexNum; i++)
    {
        G->VertexList[i].VertexIndx = i;
        G->VertexList[i].FirstNeighbour = NULL;
    }
    return G;
}
void GraphInsertEdge(Graph *G, int FromVertexIndx, int ToVertexIndx, int Weight)
{
    Edge *NewEdge = (Edge*)malloc(sizeof(Edge));
    NewEdge->FromVetexIndx = FromVertexIndx;
    NewEdge->ToVertexIndx = ToVertexIndx;
    NewEdge->Weight = Weight;
    //Adding New Edge at head of the list of neighbours
    NewEdge->NextNeighbour = G->VertexList[FromVertexIndx].FirstNeighbour;
    G->VertexList[FromVertexIndx].FirstNeighbour = NewEdge;
    G->EdgeNum++;
}
void GraphDeleteEdge(Graph *G, int FromVertexIndx, int ToVertexIndx)
{
    Edge *CurrentEdge = G->VertexList[FromVertexIndx].FirstNeighbour;
    Edge *PreviousEdge = NULL;
    while(CurrentEdge != NULL)
    {
        if(CurrentEdge->ToVertexIndx == ToVertexIndx)
        {
            if(PreviousEdge == NULL)
            {
                G->VertexList[FromVertexIndx].FirstNeighbour = CurrentEdge->NextNeighbour;
            }
            else
            {
                PreviousEdge->NextNeighbour = CurrentEdge->NextNeighbour;
            }
            free(CurrentEdge);
            G->EdgeNum--;
            return;
        }
        PreviousEdge = CurrentEdge;
        CurrentEdge = CurrentEdge->NextNeighbour;
    }
    printf("Edge not found\n");
}
void GraphDestroy(Graph *G)
{
    Edge *CurrentEdge = NULL;
    Edge *NextEdge = NULL;
    for(int i = 0; i < G->VertexNum; i++)
    {
        CurrentEdge = G->VertexList[i].FirstNeighbour;
        while(CurrentEdge != NULL)
        {
            NextEdge = CurrentEdge->NextNeighbour;
            free(CurrentEdge);
            CurrentEdge = NextEdge;
        }
    }
    free(G->VertexList);
    free(G);
}
void GraphPrint(Graph *G)
{
    Edge *CurrentEdge = NULL;
    for(int i = 0; i < G->VertexNum; i++)
    {
        printf("Vertex %d: ", G->VertexList[i].VertexIndx);
        CurrentEdge = G->VertexList[i].FirstNeighbour;
        while(CurrentEdge != NULL)
        {
            printf("%d(%d) ", CurrentEdge->ToVertexIndx, CurrentEdge->Weight);
            CurrentEdge = CurrentEdge->NextNeighbour;
        }
        printf("\n");
    }
}

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
        printf("%d ",H->HeapArray[i]);
    }
    printf("\n");
}

void TraverseAndUpddateHeaap(const Graph* G, HeapSentinel* H, int Current, int* Visited, int* InHeap)
{
    Edge* CurrentEdge = G->VertexList[Current].FirstNeighbour;
    while(CurrentEdge)
    {
        if(!Visited[CurrentEdge->ToVertexIndx] && !InHeap[CurrentEdge->ToVertexIndx])
        {
            Insert(H, CurrentEdge->ToVertexIndx);
            InHeap[CurrentEdge->ToVertexIndx] = 1;
        }
        CurrentEdge = CurrentEdge->NextNeighbour;
    }
}

int* VisitPlanet(const Graph* G)
{
    int* Seq = (int*) malloc(sizeof(int) * G->VertexNum);
    int* Visited = (int*) calloc( G->VertexNum, sizeof(int));
    // Seq[0] = 0;
    // Visited[0] = 1;

    HeapSentinel* H = CreateHeap(G->VertexNum);
    int* InHeap = (int*) calloc( G->VertexNum, sizeof(int));
    Insert(H, 0);
    InHeap[0] = 1;

    int Seq_i = 0;
    while(H->NumOfEle)
    {
        int Current = ExtractRoot(H);
        InHeap[Current] = 0;
        Seq[Seq_i++] = Current;
        Visited[Current] = 1;
        
        TraverseAndUpddateHeaap(G, H, Current, Visited, InHeap);
    }
    DestroyHeap(H);
    free(Visited);
    return Seq;
}

int main()
{
    int V,E;
    scanf("%d %d", &V, &E);
    Graph* G = GraphINIT(V);

    for (int i = 0; i < E; i++)
    {
        int V1,V2;
        scanf("%d %d", &V1, &V2);
        V1--;
        V2--;
        GraphInsertEdge(G, V1, V2, 1);
        GraphInsertEdge(G, V2, V1, 1);
    }
    // visualizeGraph(G);

    int* Seq = VisitPlanet(G);
    
    for (int i = 0; i < V; i++)
    {
        printf("%d ", Seq[i]+1);
    }
    printf("\n");
    free(Seq);
    return 0;
}