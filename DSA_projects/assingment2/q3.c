#include<stdio.h>
#include<stdlib.h>

void Print2D(int R, int C, int M[R][C])
{
    for(int i = 0; i < R; ++i)
    {
        for(int j = 0; j < C; ++j) printf("%d ", M[i][j]);
        printf("\n");
    }
    printf("\n");
}

void DFS(int N, int M, int Land[N][M], int Visited[N][M], int i, int j, int* Perimeter, int* Area)
{
    Visited[i][j] = 1;
    // Print2D(N, M, Visited);
    *Area += 1;
    if(i == 0 || Land[i-1][j] == 0) *Perimeter += 1;
    if(i == N-1 || Land[i+1][j] == 0) *Perimeter += 1;
    if(j == 0 || Land[i][j-1] == 0) *Perimeter += 1;
    if(j == M-1 || Land[i][j+1] == 0) *Perimeter += 1;

    if(i > 0 && Land[i-1][j] == 1 && Visited[i-1][j] == 0) DFS(N, M, Land, Visited, i-1, j, Perimeter, Area);
    if(i < N-1 && Land[i+1][j] == 1 && Visited[i+1][j] == 0) DFS(N, M, Land, Visited, i+1, j, Perimeter, Area);
    if(j > 0 && Land[i][j-1] == 1 && Visited[i][j-1] == 0) DFS(N, M, Land, Visited, i, j-1, Perimeter, Area);
    if(j < M-1 && Land[i][j+1] == 1 && Visited[i][j+1] == 0) DFS(N, M, Land, Visited, i, j+1, Perimeter, Area);

    return;
}

int MaxProfit(int N, int M, int Land[N][M])
{
    int MaxProfit = 0;
    int Visited[N][M];
    for(int i = 0; i < N; ++i) for(int j = 0; j < M; ++j) Visited[i][j] = 0;

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < M; ++j)
        {
            if(Land[i][j] == 1 && Visited[i][j] == 0)
                {
                    int Perimeter = 0;
                    int Area = 0;
                    DFS(N, M, Land, Visited, i, j, &Perimeter, &Area);
                    int Profit = Area<<2;
                    Profit -= Perimeter;
                    // printf("%d %d %d\n", i, j, Profit);
                    if(Profit > MaxProfit) MaxProfit = Profit;
                }
        }
    }
    return MaxProfit;
}

int main()
{
    int N, M, R;
    scanf("%d %d %d", &N, &M, &R);

    int Land[N][M];
    for(int i = 0; i < N; ++i) for(int j = 0; j < M; ++j) Land[i][j] = 0;

    for(int i = 0; i < R; ++i)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        Land[x-1][y-1] = 1;
    }
    // printf("\n");
    // Print2D(N, M, Land);

    printf("%d\n", MaxProfit(N, M, Land));
    return 0;
}

