#include<stdio.h>
#include<stdlib.h>
#define CAPACITY 10000000
// int callede = 0;
// int callede2 = 0;
//Queue
typedef struct QElemType
{
    short row;
    short col;
    // int Depth;
}QElemType;
typedef struct QueueSentinal
{
    long long int NumOfElem;
    int Head;
    int Tail;
    QElemType* Q;
}QueueSentinal;

//queueFunction
QueueSentinal* QueueINIT();
void Enqueue(QueueSentinal* Q, QElemType elem);
void EnqueFront(QueueSentinal* Q, QElemType elem);
QElemType Dequeue(QueueSentinal* Q);
void DeleteQueue(QueueSentinal* Q);

// queueFunctions
#define FlagQ NULL

QueueSentinal *QueueINIT(){
    QueueSentinal *Qs = (QueueSentinal *)malloc(sizeof(QueueSentinal));
    Qs->Head = -1;
    Qs->Tail = 0;
    Qs->NumOfElem = 0;
    Qs->Q = (QElemType *)malloc(sizeof(QElemType) * CAPACITY);

    return Qs;
}
void Enqueue(QueueSentinal *Q, QElemType elem){
    Q->Q[Q->Tail] = elem;
    Q->Tail = (Q->Tail + 1) % CAPACITY;
    ++Q->NumOfElem;
    return;
}
void EnqueFront(QueueSentinal *Q, QElemType elem){
    Q->Head = (Q->Head - 1 + CAPACITY) % CAPACITY;
    Q->Q[Q->Head] = elem;
    ++Q->NumOfElem;
    return;
}

QElemType Dequeue(QueueSentinal *Q){
    if(Q->NumOfElem == 0){
        return ;//FlagQ;
    }
    QElemType elem = Q->Q[Q->Head];
    Q->Head = (Q->Head + 1) % CAPACITY;
    --Q->NumOfElem;
    return elem;
}
void DeleteQueue(QueueSentinal* Q){
    free(Q->Q);
    return;
}

int MinWeightPath(short N, short M, short Vindhiya[N][M])
{
    short Visited[N][M],depth[N][M];
    for(short i=0; i<N; ++i)for(short j=0; j<M; ++j){Visited[i][j] = 0;depth[i][j]=N+M;}//

    // Print2DArray(N, M, depth);
    // Print2DArray(N, M, Visited);

    QueueSentinal* Q1 = QueueINIT();
    // QueueSentinal* Q2 = QueueINIT();
    depth[0][0] = 0;
    QElemType StartCell;
    StartCell.col = 0;
    StartCell.row = 0;
    // StartCell.Depth = 0;

    Enqueue(Q1, StartCell);

    while(Q1->NumOfElem)
        {
            QElemType CurrentCell = Dequeue(Q1);
            // callede2++;
            if(Visited[CurrentCell.row][CurrentCell.col]) continue;
            Visited[CurrentCell.row][CurrentCell.col] = 1;
            // printf("CurrentCell: %d %d\n", CurrentCell.row, CurrentCell.col);
            // Print2DArray(N, M, Visited);
            // printf("\n");
            if(CurrentCell.col == M-1 && CurrentCell.row == N-1){
                DeleteQueue(Q1);
                // DeleteQueue(Q2);
                return depth[CurrentCell.row][CurrentCell.col];
            }            //use 4 if statements to check if the neighbour is valid
            short NeighbourRow[4] = {CurrentCell.row-1, CurrentCell.row+1, CurrentCell.row, CurrentCell.row};
            short NeighbourCol[4] = {CurrentCell.col, CurrentCell.col, CurrentCell.col-1, CurrentCell.col+1};
            for (short i = 0; i < 4; ++i)
            {
                if(!Visited[NeighbourRow[i]][NeighbourCol[i]] && NeighbourRow[i] >= 0 && NeighbourRow[i] < N && NeighbourCol[i] >= 0 && NeighbourCol[i] < M)
                {
                    QElemType NeighbourCell;
                    NeighbourCell.row = NeighbourRow[i];
                    NeighbourCell.col = NeighbourCol[i];
                    if(Vindhiya[NeighbourCell.row][NeighbourCell.col] == Vindhiya[CurrentCell.row][CurrentCell.col])
                    {
                        // callede++;
                        depth[NeighbourCell.row][NeighbourCell.col] = depth[CurrentCell.row][CurrentCell.col];
                        EnqueFront(Q1, NeighbourCell);
                        // Visited[NeighbourCell.row][NeighbourCell.col] = 1;
                    }
                    else if(depth[NeighbourCell.row][NeighbourCell.col] > depth[CurrentCell.row][CurrentCell.col]+1)
                    {   
                        // callede++;
                        depth[NeighbourCell.row][NeighbourCell.col] = depth[CurrentCell.row][CurrentCell.col]+1;
                        // NeighbourCell.Depth=CurrentCell.Depth+1;
                        Enqueue(Q1, NeighbourCell);
                        // Visited[NeighbourCell.row][NeighbourCell.col] = 1;
                    }
                }
            }
            // Print2DArray(N, M, depth);               
        }
        return depth[N-1][M-1];
}

void Print2DArray(short R, short C, short M[R][C])
{
    printf("\n");
    for(int i = 0; i < R; ++i)
    {
        for(int j = 0; j < C; ++j) printf("%hd ", M[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main()
{
    short int T;
    scanf("%hd", &T);

    for (short i = 0; i < T; ++i)
    {                short N ,M;
        scanf("%hd %hd", &N, &M);

        short Vindhiya[N][M];
        for (short j = 0; j < N; ++j)
        {
            for (short k = 0; k < M; ++k)
            {
                scanf("%hd", &Vindhiya[j][k]);
            }
        }

        printf("%d\n", MinWeightPath(N, M, Vindhiya));
        
    }
    // printf("enqueued: %d\n", callede);
    // printf("dequequed: %d\n", callede2);
    return 0;
}

