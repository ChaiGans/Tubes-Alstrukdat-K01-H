#include "grafpertemanan.h"
#include <stdio.h>

void createGrafPertemanan(GrafPertemanan *G, int n)
{
    createMatrix(n, n, &G->matrixPertemanan);
    G->banyakOrang = n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ElmtGrafPertemanan(*G, i, j) = '0';
        }
    }
}

int getBanyakTeman(GrafPertemanan G, int i)
{
    int count = 0;
    for (int j = 0; j < G.banyakOrang; j++)
    {
        if (ElmtGrafPertemanan(G, i, j) == '1')
        {
            count++;
        }
    }
    return count;
}

boolean isTeman(GrafPertemanan G, int i, int j)
{
    return ElmtGrafPertemanan(G, i, j) == '1' && ElmtGrafPertemanan(G, j, i) == '1';
}

void hapusTeman(GrafPertemanan *G, int i, int j)
{
    ElmtGrafPertemanan(*G, i, j) = '0';
    ElmtGrafPertemanan(*G, j, i) = '0';
}

void displayGrafPertemanan(GrafPertemanan G)
{
    for (int i = 0; i < G.banyakOrang; i++)
    {
        for (int j = 0; j < G.banyakOrang; j++)
        {
            printf("%c", ElmtGrafPertemanan(G, i, j));
        }
        printf("\n");
    }
}