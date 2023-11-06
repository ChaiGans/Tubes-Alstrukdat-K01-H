#include <stdio.h>
#include "profile.h"

/* pcolor */
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

/* FOTO PROFIL */
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
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            ELMT(SIMBOLPROFIL(*F), i, j) = '*';
        }
    }
}

void displayFotoProfil(FotoProfil F)
{
    /* I.S. F terdefinisi */
    /* F.S. F ditampilkan di layar sesuai dengan warna dan simbolnya */
    int i, j;
    char warna, simbol;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
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


void createProfile(Profile *p)
{
    transferStringToString("", p->bio);
    (*p).nomorHP = 0;
    transferStringToString("", p->weton);
    transferStringToString("PUBLIK", p->status);
    p->status[6] = '\0';
    p->weton[6] = '\0';
    p->bio[135] = '\0';
    p->username[20] = '\0';
    p->password[20] = '\0';


    FotoProfil foto;
    createFotoProfil(&foto);
    (*p).fotoProfil = foto;
}

void displayNomorHP(Profile p)
{
    if (p.nomorHP != 0)
    {
        printf("0%d", p.nomorHP);
    }
    else
    {
        printf("");
    }
}

void displayStatusAKun(Profile p)
{
    if (stringStringCompare(p.status, "PUBLIK"))
    {
        printf("PUBLIK");
    }
    else
    {
        printf("PRIVAT");
    }
}

void displayProfileInformation(Profile p)
{
    printf("| Nama: ");
    displayArrayOfChar(p.username);
    putchar('\n');
    printf("| Bio Akun: ");
    displayArrayOfChar(p.bio);
    putchar('\n');
    printf("| No HP: ");
    displayNomorHP(p);
    putchar('\n');
    printf("| Weton: ");
    displayArrayOfChar(p.weton);
    putchar('\n');
    putchar('\n');
    printf("Foto profil akun %s\n", p.username);
    displayFotoProfil(p.fotoProfil);
    putchar('\n');
}

void toLowerCase(const char original[], char lowercaseCopy[])
{
    int i;
    for (i = 0; original[i] != '\0'; i++)
    {
        if (original[i] >= 'A' && original[i] <= 'Z')
        {
            lowercaseCopy[i] = original[i] + 32;
        }
        else
        {
            lowercaseCopy[i] = original[i];
        }
    }
    lowercaseCopy[i] = '\0';
}

boolean isWetonValid(Word w)
{
    int i;
    char lowercase[w.Length];
    toLowerCase(w.TabWord, lowercase);
    if (stringStringCompare(lowercase, "pahing") || stringStringCompare(lowercase, "kliwon") || stringStringCompare(lowercase, "wage") || stringStringCompare(lowercase, "pon") || stringStringCompare(lowercase, "legi"))
    {
        return true;
    }
    else
    {
        return false;
    }
}