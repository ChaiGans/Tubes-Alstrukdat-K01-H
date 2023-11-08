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

int getBanyakTeman(GrafPertemanan G, int idProfil)
{
    int count = 0;
    for (int j = 0; j < G.banyakOrang; j++)
    {
        if (ElmtGrafPertemanan(G, idProfil, j) == '1' && idProfil != j)
        {
            count++;
        }
    }
    return count;
}

boolean isTeman(GrafPertemanan G, int i, int j)
{
    return ElmtGrafPertemanan(G, i, j) == '1' && ElmtGrafPertemanan(G, j, i) == '1' && i != j;
}

void hapusHubunganTeman(GrafPertemanan *G, int i, int j)
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

boolean isMengirimPermintaan(GrafPertemanan G, int idPengirim, int idPenerima)
{
    return ElmtGrafPertemanan(G, idPengirim, idPenerima) == '1' && ElmtGrafPertemanan(G, idPenerima, idPengirim) == '0';
}

int getBanyakPermintaanTeman(GrafPertemanan G, int idPenerima)
{
    int count = 0;
    for (int j = 0; j < G.banyakOrang; j++)
    {
        if (ElmtGrafPertemanan(G, idPenerima, j) == '1' && ElmtGrafPertemanan(G, j, idPenerima) == '0' && idPenerima != j)
        {
            count++;
        }
    }
    return count;
}