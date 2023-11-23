#include <stdio.h>
#include "listpengguna.h"

int main () {
    ListPengguna l;
    CreateListPengguna(&l);
    printListPengguna(l);
    printf("%d\n", ListPenggunaLength(l));
    
    return 0;
}