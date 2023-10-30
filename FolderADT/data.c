#include "data.h"
#include <stdio.h>
#include "wordmachine.h"

Word blankLineCheck(Word w)
{
    Word newLineWORD;
    newLineWORD.Length = 0;
    newLineWORD.TabWord[0] = '\0';

    if (w.Length == 0)
    {
        return newLineWORD;
    }
    else
    {
        return w;
    }
}

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

Word cutWord(Word w)
{
    Word res;
    if (w.Length == 0)
    {
        res.Length = 0;
        res.TabWord[0] = '\0';
        return w;
    }

    int i;
    for (i = 0; i < w.Length; i++)
    {
        res.TabWord[i] = w.TabWord[i];
    }
    res.Length = w.Length;
    return res;
}

void readPenggunaConfig(char *filename, ListPengguna *listPengguna)
{

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    STARTWORD(file, true); // currentWord = banyak profile
    int banyakProfile = wordToInt(currentWord);

    for (int i = 0; i < banyakProfile; i++)
    {
        Profile p;

        p.index = i;
        ADVWORD(true); // currentWord = username
        p.username = cutWord(currentWord);

        ADVWORD(true); // currentWord = password
        p.password = cutWord(currentWord);

        ADVWORD(true); // currentWord = bio
        p.bio = blankLineCheck(cutWord(currentWord));

        ADVWORD(true); // currentWord = nomor HP
        p.nomorHP = wordToInt(blankLineCheck(cutWord(currentWord)));
        // 0 kalo di int jadi ilang

        ADVWORD(true); // currentWord = weton
        p.weton = blankLineCheck(cutWord(currentWord));

        ADVWORD(true); // currentWord = status
        p.status = blankLineCheck(cutWord(currentWord));

        // baca profil
        FotoProfil foto;
        createFotoProfil(&foto);

        int i, baris, kolom;
        char warna, simbol;

        for (baris = 0; baris < 5; baris++)
        {
            kolom = 0;
            ADVWORD(true);
            for (i = 0; i < 18; i++)
            {
                if (i % 4 == 0)
                {
                    warna = currentWord.TabWord[i];
                    ELMT(WARNAPROFIL(foto), baris, kolom) = warna;
                }
                else if (i % 4 == 2)
                {
                    simbol = currentWord.TabWord[i];
                    ELMT(SIMBOLPROFIL(foto), baris, kolom) = simbol;
                }
                if (i % 4 == 3)
                    kolom++;
            }
        }

        listPengguna->contents[i] = p;
    }

    Matrix pertemanan;
    createMatrix(banyakProfile, banyakProfile, &pertemanan);

    for (int i = 0; i < banyakProfile; i++)
    {
        ADVWORD(true); // currentWord = baris pertama
        for (int j = 0; j < banyakProfile; j += 2)
        {

            ELMT(pertemanan, i, j) = currentWord.TabWord[j] - '0';
        }
    }

    ADVWORD(true);
    int banyakPermintaanPertemenan = wordToInt(currentWord);
    for (int i = 0; i < banyakPermintaanPertemenan; i++)
    {
        ADVWORD(true); // currentWord = username pengirim
        // proses permintaan pertemanan, tapi belum dikerjain karena gatau ADT graf hihi
    }

    printf("Pengguna berhasil dibaca.\n");
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

void initReadConfig(Word fileName, ListPengguna *listPengguna)
{
    readPenggunaConfig("config/pengguna.txt", listPengguna);
    // readKicauanConfig("config/kicauan.txt");
    //  readBalasanConfig("config/balasan.txt");
    //  readDrafConfig("config/draf.txt");
    //  readUtasConfig("config/utas.txt");
}
