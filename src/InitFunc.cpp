#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "InitFunc.h"
#include "TwoAxisArray.h"
InitFunc::InitFunc() {}
InitFunc::InitFunc(int n, int k, int *Sol, bool **graph)
{
    this->n = n;
    this->k = k;
    this->Sol = Sol;
    this->graph = graph;
}

void InitFunc::DSATUR_dataInit(int *degree)
{
    newArray(VCAvail, n, k);
    initArray(VCAvail, true, n, k);
    NAColors = new int[n];
    VUDegree = new int[n];
    memset(Sol, -1, n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        NAColors[i] = k;
        VUDegree[i] = degree[i];
    }
}

void InitFunc::DSATUR_datadel()
{
    deleteArray(VCAvail, n, k);
    delete[] NAColors;
    delete[] VUDegree;
}

void InitFunc::colorDot(int vi, int color)
{
    Sol[vi] = color;
    for (int i = 0; i < n; i++)
        if (graph[vi][i])
        {
            VUDegree[i]--;
            if (VCAvail[i][color])
            {
                NAColors[i]--;
                VCAvail[i][color] = false;
            }
        }
}

void InitFunc::DSATUR_Init(int *degree)
{
    DSATUR_dataInit(degree);
    printf("DSATUR Initial...\n");
    int index = 0;
    for (int i = 0; i < n; i++)
        if (degree[i] > degree[index])
            index = i;
    colorDot(index, 0);
    for (int i = 1; i < n; i++)
    {
        int index = -1;
        while (Sol[++index] != -1)
            ;
        for (int vi = 0; vi < n; vi++)
            if (Sol[vi] == -1)
                if (NAColors[vi] < NAColors[index] || NAColors[vi] == NAColors[index] && VUDegree[vi] > VUDegree[index])
                    index = vi;
        int sc = -9999, ci = -1;
        for (int c = 0; c < k; c++)
        {
            if (VCAvail[index][c])
            {
                int cnt = 0;
                for (int vi = 0; vi < n; vi++)
                    if (VCAvail[vi][c])
                        cnt++;
                if (cnt > sc)
                    ci = c;
            }
        }
        if (ci != -1)
            colorDot(index, ci);
        else
            colorDot(index, rand() * k / (RAND_MAX + 1));
    }
    DSATUR_datadel();
}

void InitFunc::random_Init()
{
    printf("Random Initial...\n");
    for (int i = 0; i < n; i++)
        Sol[i] = (rand() * k) / (RAND_MAX + 1);
}

InitFunc::~InitFunc()
{
    //dtor
}
