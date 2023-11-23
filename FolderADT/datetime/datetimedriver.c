#include <stdio.h>
#include "datetime.h"

int main () {
    DATETIME liveTime;
    getLocalTime(&liveTime);
    displayDATETIME(liveTime);
    putchar('\n');
    return 0;
}