#include "FolderADT/charmachine.h"
#include "FolderADT/wordmachine.h"
#include "FolderADT/data.h"
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
    ReadWord();
    Word fileName = currentWord;

    // inisiasi list yang akan digunakan
    ListPengguna listPengguna;
    CreateListPengguna(&listPengguna);
    ListKicau listKicau;
    CreateListKicau(&listKicau, 10); // eh gatau ini capacity tuh gimane

    // membaca file config
    initReadConfig(fileName, &listPengguna, &listKicau);

    // skema command line interface
    while (true)
    {
        printf("\n>> ");
        Word command = ReadWord();
        printf("command : ");
        for (int i = 1; i < command.Length; i++)
        {
            printf("%c", command.TabWord[i]);
        }
    }
}
