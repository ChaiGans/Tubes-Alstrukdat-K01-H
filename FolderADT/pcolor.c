/**
Filename: pcolor.c (implementation of pcolor.h)
Description: Print character with some color in terminal
Prepared by: Asisten IF2110
Created at: 17/10/2019
Modified at: 23/10/2023
**/

#include <stdio.h>
#include "pcolor.h"

void print_red(char c)
{
    printf("%s%c", RED, c);
    printf("%s", NORMAL);
}

void print_green(char c)
{
    printf("%s%c", GREEN, c);
    printf("%s", NORMAL);
}

void print_blue(char c)
{
    printf("%s%c", BLUE, c);
    printf("%s", NORMAL);
}

/* ******* FOTO PROFIL ******* */
void createFotoProfil(FotoProfil *F)
{
    /* Membentuk dua Matrix warnaProfil dan simbolProfil "kosong" berukuran 5 x 5 */
    createMatrix(SIZE, SIZE, &F->WarnaProfil);
    createMatrix(SIZE, SIZE, &F->SimbolProfil);
    // Mengisi Matrix WarnaProfil dengan default FotoProfil (R)
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            ELMT(WARNAPROFIL(*F), i, j) = 'R';
        }
    }
    // Mengisi Matrix SimbolProfil dengan default FotoProfil (*)
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            ELMT(SIMBOLPROFIL(*F), i, j) = '*';
        }
    }
}

void printFotoProfil(FotoProfil F)
{
    /* I.S. F terdefinisi */
    /* F.S. F ditampilkan di layar sesuai dengan warna dan simbolnya */
    int i, j;
    char warna, simbol;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            warna = ELMT(WARNAPROFIL(F), i, j);
            simbol = ELMT(SIMBOLPROFIL(F), i, j);
            if (warna == 'R')
            {
                print_red(simbol);
            }
            else if (warna == 'G')
            {
                print_green(simbol);
            }
            else if (warna == 'B')
            {
                print_blue(simbol);
            }
            else
            {
                printf("%c", simbol);
            }
        }
        printf("\n");
    }
}

void ubahFotoProfil(FotoProfil *F)
{
    /* I.S. F terdefinisi */
    /* F.S. Warna dan simbol pada F terubah sesuai dengan input pengguna */
    int i, baris, kolom;
    char warna, simbol;
    printf("Masukkan Foto Profil yang baru: \n");
    Word userInput = ReadWord();

    baris = 0;
    kolom = 0;
    for (i = 0; i < 100; i++)
    {
        if (i % 4 == 0)
        {
            warna = userInput.TabWord[i];
            ELMT(WARNAPROFIL(*F), baris, kolom) = warna;
        }
        else if (i % 4 == 2)
        {
            simbol = userInput.TabWord[i];
            ELMT(SIMBOLPROFIL(*F), baris, kolom) = simbol;
        }

        if (i % 4 == 3)
        {
            kolom++;
            if (kolom == 5)
            {
                kolom = 0;
            }
        }
        if (i % 20 == 19)
        {
            baris++;
        }
    }
}