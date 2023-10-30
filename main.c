#include "FolderADT/charmachine.h"
#include "FolderADT/wordmachine.h"
#include "FolderADT/data.h"
#include "FolderADT/listpengguna.h"
#include <stdio.h>

// static FILE *pita; // Declare pita as a global variable
Word userInput;

void printASCIIART()
{
    printf("      _                     _            \n");
    printf("     | |___      _____  ___| |_ ___ _ __ \n");
    printf("     | __\\ \\ /\\ / / _ \\/ _ \\ __/ _ \\ '__|\n");
    printf("     | |_ \\ V  V /  __/  __/ ||  __/ |   \n");
    printf("      \\__| \\_/\\_/ \\___|\\___|\\__\\___|_|   \n");
    printf("                                         \n");
}

int main()
{
    // pesan selamat datang
    printASCIIART();
    printf("Selamat datang di tweeter.\n");

    // meminta input nama file config
    printf("Masukkan nama file config: ");
    STARTWORD(stdin, false);
    Word fileName = currentWord;
    ListPengguna listPengguna;
    CreateListPengguna(&listPengguna);
    initReadConfig(fileName, &listPengguna);
}
