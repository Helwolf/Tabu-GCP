#include "Gcp.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "TwoAxisArray.h"
#include "InitFunc.h"
#include <ctime>
Gcp::Gcp()
{
    //srand((int)time(0));
}

void Gcp::date_Init()
{
    newArray(Table, n, MK);   //存储tabu列表的数组
    newArray(ACTable, n, MK); //存储各颜色相邻节点数的数组
    newArray(graph, n, n);
    initArray(graph, false, n, n); //初始化图
    degree = new int[n];
    memset(degree, 0, n * sizeof(int)); //初始化每个节点的度
    initArray(ACTable, 0, n, MK);
    initArray(Table, 0, n, MK);
}

void Gcp::readGraph(const char *filename) //读取.col文件 获取图信息
{
    char tmp[500];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Read File %s Error...\n", filename);
        return;
    }
    printf("Read File %s ...\n", filename);
    int a, b;
    while (fgets(tmp, 500, fp) && tmp[0] == 'c')
        ;
    sscanf(tmp, "%*s%*s%d%d", &n, &edgeNum);
    date_Init();
    while (edgeNum--)
    {
        fscanf(fp, "%*s%d%d", &a, &b);
        a--;
        b--;
        graph[a][b] = graph[b][a] = true;
        degree[a]++;
        degree[b]++;
    }
    fclose(fp);
}

void Gcp::setParameter(float alpha, int A, int m_max)
{
    this->alpha = alpha;
    this->A = A;
    this->m_max = m_max;
}

void Gcp::Init()
{
    f = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (graph[i][j])
            {
                ACTable[i][Sol[j]]++;
                if (Sol[i] == Sol[j])
                    f++;
            }
    f >>= 1;
    bestf = f;
    m = 0;
    MaxIter = 1000;
    printf("K=%d,f=%d\tMaxIter=%d\n", K, f, MaxIter);
}

void Gcp::SetMove(Move *move, int u, int i, int j, int delt)
{
    move->delt = delt;
    move->i = Sol[i];
    move->j = j;
    move->u = u;
}

Move Gcp::FindMove()
{
    Move tMove, ntMove;
    memset(&ntMove, 0, sizeof(tMove));
    bool tv = false, ntv = false;
    int tdelt = INF, ntdelt = INF;
    int tk = INF, ntk = INF;
    for (int i = 0; i < n; i++)
        if (ACTable[i][Sol[i]] > 0)
        {
            for (int k = 0; k < K; k++)
                if (k != Sol[i])
                {
                    Move *tmp = NULL;
                    int delt = ACTable[i][k] - ACTable[i][Sol[i]];

                    // find the best tabu moves, if there are multiple best moves, a random one is selected. P=0.7
                    if (Table[i][k] > iter && (delt < tdelt || delt == tdelt && rand() * 2 / (RAND_MAX + 1.0) > 1.4))
                    {
                        SetMove(&tMove, i, Sol[i], k, delt);
                        tdelt = delt;
                        tk = ACTable[i][k];
                        tv = true;
                    }

                    // find the best no-tabu moves.
                    if (Table[i][k] <= iter && (delt < ntdelt || delt == ntdelt && rand() * 2 / (RAND_MAX + 1.0) > 1.4))
                    {
                        SetMove(&ntMove, i, Sol[i], k, delt);
                        ntdelt = delt;
                        ntk = ACTable[i][k];
                        ntv = true;
                    }
                }
        }
    //the best tabu move is better than the previous best known solution
    //the best tabu move is better than the best non-tabu move in the current neighborhood.
    if (tv && tMove.delt < ntMove.delt && tMove.delt + f < bestf || !ntv)
        return tMove;
    else
        return ntMove;
}

void Gcp::Update_ACTable(int a, int vi, int vj)
{
    for (int i = 0; i < n; i++)
        if (graph[i][a])
        {
            ACTable[i][vi]--;
            ACTable[i][vj]++;
        }
}

void Gcp::MakeMove(Move a)
{
    Sol[a.u] = a.j;
    if (a.delt >= 0)
        m++;
    else
        m = 0;
    f = f + a.delt;
    if (f < bestf)
        printf("f=%d\n", bestf = f);
    Table[a.u][a.i] = iter + alpha * f + (rand() * A) / (RAND_MAX + 1) + m / m_max;
    Update_ACTable(a.u, a.i, a.j);
}

void Gcp::TabuSearch()
{
    bool hasFind = false;
    InitFunc func(n, K, Sol, graph);
    func.random_Init();
    Init();
    for (int i = K; i < n; i++)
    {
        hasFind = false;
        while (iter >= 0)
        {
            iter++;
            MakeMove(FindMove());
            if (f <= 0)
            {
                hasFind = true;
                break;
            }
        }
        if (hasFind)
            break;
    }
    printf("Minim K=%d,f=%d,iter=%d\n", K, f, iter);
}
Gcp::~Gcp()
{
    //dtor
}
