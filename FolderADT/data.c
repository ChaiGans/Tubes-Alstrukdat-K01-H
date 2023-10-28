#include "boolean.h"
#include "wordmachine.h"
#include "charmachine.h"
#include "data.h"
#include <stdio.h>

int wordToInt(Word w)
{
    int res = 0;
    int i;
    for (i = 0; i < w.Length; i++)
    {
        res *= 10;
        res += w.TabWord[i] - '0';
    }
    return res;
}

void readPenggunaConfig(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    STARTWORD(file, true);
    printf("banyak pengguna = %d\n", wordToInt(currentWord));
    int banyakPengguna = wordToInt(currentWord);

    // Membaca semua profil pengguna. Tapi ini cape dulu wkwkwk.
    // for (int i = 0; i < banyakPengguna; i++)
    // {
    //     createProfil(&tabProfil[i]);
    //     ADVWORD();
    // }
}

void initReadConfig()
{
    readPenggunaConfig("config/pengguna.txt");
}
