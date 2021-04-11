//フォードファルカーソン法

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 6 //頂点数
#define TRUE 1
#define FALSE 0
#define S 0 //ソース
#define T 5 //シンク
#define INF 10000000

int flag[N];

int C[N][N] = {0}; //容量行列

// 引数の小さい方を返す
int min(int a, int b);

//sからtへ移動可能ならそのルートの最大流量を返し、不可能なら0を返す。
int DFS(int v, int t, int f);

//sからtへの最大流量を返す。
int max_flow(int s, int t);

int main()
{
    // int edge = 0;
    unsigned int seed;

    /* 現在時刻を元に seed を決定*/
    seed = (unsigned)time(NULL);
    srand(seed);

    //頂点間の流量を決定する
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (rand() % 2 == 1) //ネットワークGの辺ijを繋ぐか決める
            {
                C[i][j] = rand() % 10 + 1;
                // edge++;
            }
        }
    }

    // printf("辺：%d\n", edge);
    // clock_t start, end;
    // start = clock();
    printf("最大流量：%d\n", max_flow(S, T));
    // end = clock();
    // printf("%.2f秒かかりました\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int min(int a, int b)
{
    return a < b ? a : b;
}

//sからtへ移動可能ならそのルートの最大流量を返し、不可能なら0を返す。
int DFS(int v, int t, int f)
{
    printf("%d ", v);

    if (v == t) //ソースとシンクが一致したら
        return f;

    printf("→ ");
    flag[v] = TRUE;
    for (int i = 0; i < N; i++)
    {
        if (flag[i] == FALSE && C[v][i] > 0)
        {
            int d = DFS(i, t, min(f, C[v][i]));
            if (d > 0)
            {
                //容量行列を更新(残余ネットワークを作成)
                C[v][i] -= d;
                C[i][v] += d;
                return d;
            }
        }
    }
    return 0;
}

//sからtへの最大流量を返す。
int max_flow(int s, int t)
{
    int flow = 0;
    for (;;)
    {
        // flagを初期化
        memset(flag, FALSE, sizeof(flag));
        int f = DFS(s, t, INF);
        printf("流量：%d\n", f);
        if (f == 0)
            return flow;
        flow += f;
    }
}

// http://even-eko.hatenablog.com/entry/2013/08/08/195120