#include "data.h"
#include <stdio.h>
// #include "profile.h"

// Profile tabProfile[20];
// ListDinamic listKicauan;
// Stack drafKicauan;

// Tree?? Balasan;          // yang dikasih tanda tanya nih aing blm ngerti
// Graf?? matrixTeman;

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
    printf("nama pengguna = ");
    ADVWORD(true);
    printf("%s\n", currentWord.TabWord);
    int banyakPengguna = wordToInt(currentWord);

    // Membaca semua profil pengguna. Tapi ini cape dulu wkwkwk.
    // for (int i = 0; i < banyakPengguna; i++)
    // {
    //     createProfileFromFile(&tabProfil[i]);
    //     ADVWORD();
    // }
}

void readKicauanConfig(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    STARTWORD(file, true);
    // lanjut
}

void readBalasanConfig(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    STARTWORD(file, true);
    // lanjut
}

void readDrafConfig(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    STARTWORD(file, true);
    // lanjut
}

void readUtasConfig(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    STARTWORD(file, true);
    // lanjut
}

void initReadConfig()
{
    readPenggunaConfig("config/pengguna.txt");
    // readKicauanConfig("config/kicauan.txt");
    //  readBalasanConfig("config/balasan.txt");
    //  readDrafConfig("config/draf.txt");
    //  readUtasConfig("config/utas.txt");
}
