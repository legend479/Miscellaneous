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

void visualizeGraph(Graph* G) {
    FILE* file = fopen("graph.dot", "w");
    if (file == NULL) {
        printf("Failed to create graph.dot file.\n");
        return;
    }
    
    fprintf(file, "digraph G {\n");

    for (int i = 0; i < G->VertexNum; ++i) {
        Vertex currentVertex = G->VertexList[i];
        
        fprintf(file, "  %d;\n", currentVertex.VertexIndx);
        
        Edge* currentEdge = currentVertex.FirstNeighbour;
        while (currentEdge) {
            fprintf(file, "  %d -> %d [label=\"%d\"];\n", currentEdge->FromVetexIndx, currentEdge->ToVertexIndx, currentEdge->Weight);
            currentEdge = currentEdge->NextNeighbour;
        }
    }
    
    fprintf(file, "}\n");
    fclose(file);

    system("dot -Tpng graph.dot -o graph.png");
    system("rm graph.dot");
    printf("Graph visualization saved to 'graph.png'.\n");
}