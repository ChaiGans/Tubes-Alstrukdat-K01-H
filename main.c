#include "FolderADT/charmachine.h"
#include "FolderADT/wordmachine.h"
#include "FolderADT/data.h"
#include "features/user.h"
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
    int currentLoginID = -1;
    // inisiasi list yang akan digunakan
    ListPengguna listPengguna;
    CreateListPengguna(&listPengguna);
    ListKicau listKicau;
    CreateListKicau(&listKicau, 10); // eh gatau ini capacity tuh gimane

    // membaca file config
    initReadConfig(fileName, &listPengguna, &listKicau);
    printListPengguna(listPengguna);
    // skema command line interface
    while (true)
    {
        printf("\n>> ");
        Word command = ReadWord();
        if (wordStringCompare(command, "DAFTAR")) {
            daftarPengguna(&listPengguna);
            printListPengguna(listPengguna);
        } else if (wordStringCompare(command, "MASUK")) {
            masukPengguna(&currentLoginID, listPengguna);
            displayNameFromID(currentLoginID, listPengguna);
        }
    }
}
