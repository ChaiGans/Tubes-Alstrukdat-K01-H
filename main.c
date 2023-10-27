#include "FolderADT/charmachine.h"
#include "FolderADT/wordmachine.h"
#include <stdio.h>

static FILE *pita; // Declare pita as a global variable
Word userInput;
int main() {
    userInput = ReadWord();
    printf("%s", userInput.TabWord);
    userInput = ReadWord();
    printf("%s", userInput.TabWord);
    return 0;
}
