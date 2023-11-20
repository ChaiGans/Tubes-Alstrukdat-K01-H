#include <stdio.h>
#include "stackdraf.h"

int main() {
    StackDraf stackDraf;
    ElTypeDraf currentDraf;

    CreateEmptyStackDraf(&stackDraf);

    if (IsEmptyStackDraf(stackDraf)) {
        printf("StackDraf kosong.\n");
    } else {
        printf("StackDraf tidak kosong.\n");
    }

    createDraf(stackDraf, &currentDraf, 1);
    PushStackDraf(&stackDraf, currentDraf);
    PushStackDraf(&stackDraf, currentDraf);
    PushStackDraf(&stackDraf, currentDraf);
    PushStackDraf(&stackDraf, currentDraf);
    PushStackDraf(&stackDraf, currentDraf);
    PushStackDraf(&stackDraf, currentDraf);
    PushStackDraf(&stackDraf, currentDraf);
    PushStackDraf(&stackDraf, currentDraf);
    PushStackDraf(&stackDraf, currentDraf);
    PushStackDraf(&stackDraf, currentDraf);

    if (IsFullStackDraf(stackDraf)) { // CAPACITY STACK DRAF 10
        printf("StackDraf penuh.\n");
    } else {
        printf("StackDraf tidak penuh.\n");
    }

    ElTypeDraf poppedDraf;
    PopStackDraf(&stackDraf, &poppedDraf);

    if (IsEmptyStackDraf(stackDraf)) {
        printf("StackDraf empty.\n");
    } else {
        printf("StackDraf tidak empty.\n");
    }

    return 0;
}
