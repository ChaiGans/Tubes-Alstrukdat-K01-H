#include "prioqueuechar.h"
#include <stdio.h>

int main()
{
    PrioQueueChar Q;
    infotype X;

    MakeEmptyQueue(&Q, 5);

    // Test IsEmptyQueue
    printf("Apakah PrioQueueChar kosong? %s\n", IsEmptyQueue(Q) ? "Yes" : "No");

    // Test IsFullQueue
    infotype X1 = {10, 1};
    infotype X2 = {20, 2};
    Enqueue(&Q, X1);
    Enqueue(&Q, X2);
    printf("Apakah PrioQueueChar Sudah Penuh? %s\n", IsFullQueue(Q) ? "Yes" : "No");

    // Test NBElmtQueue
    printf("Banyak elemen di PrioQueueChar: %d\n", NBElmtQueue(Q));

    // Test Enqueue and Dequeue
    Enqueue(&Q, (infotype){15, 3});
    printf("Queue setelah Enqueue {15, 3}: \n");
    PrintPrioQueueChar(Q);

    Dequeue(&Q, &X);
    printf("Elemen yang di Dequeue: %d - %d\n", Popularity(X), ID(X));

    printf("Queue setelah dequeue: \n");
    PrintPrioQueueChar(Q);

    return 0;
}
