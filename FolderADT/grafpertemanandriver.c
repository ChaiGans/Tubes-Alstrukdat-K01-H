#include "grafpertemanan.h"
#include <stdio.h>

int main()
{
    printf("=== Test Create Graf Pertemanan ===\n");
    GrafPertemanan G;
    createGrafPertemanan(&G, 5);
    displayGrafPertemanan(G);

    printf("\n=== Test Add Teman ===\n");
    printf("tambah teman 0 dan 1\n");
    addTeman(&G, 0, 1);
    printf("tambah teman 0 dan 2\n");
    addTeman(&G, 0, 2);
    printf("tambah teman 1 dan 3\n");
    addTeman(&G, 1, 3);
    displayGrafPertemanan(G);

    printf("\n=== Test Hapus Hubungan Teman ===\n");
    printf("hapus hubungan teman 0 dan 1\n");
    hapusHubunganTeman(&G, 0, 1);
    displayGrafPertemanan(G);

    return 0;
}
