#include "data.h"
#include <stdio.h>

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

void cutWord(Word w, char *res)
{
    if (w.Length == 0)
    {
        res[0] = '\0';
        return;
    }

    int i;
    for (i = 0; i < w.Length; i++)
    {
        res[i] = w.TabWord[i];
    }
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
        listPengguna->contents[i].index = i;
        ADVWORD(true); // currentWord = username
        cutWord(currentWord, listPengguna->contents[i].username);

        ADVWORD(true); // currentWord = password
        cutWord(currentWord, listPengguna->contents[i].password);

        ADVWORD(true); // currentWord = bio
        cutWord(blankLineCheck(currentWord), listPengguna->contents[i].bio);

        ADVWORD(true); // currentWord = nomor HP
        listPengguna->contents[i].nomorHP = wordToInt(currentWord);
        // 0 kalo di int jadi ilang

        ADVWORD(true); // currentWord = weton
        cutWord(blankLineCheck(currentWord), listPengguna->contents[i].weton);

        ADVWORD(true); // currentWord = status
        cutWord(currentWord, listPengguna->contents[i].status);

        // baca profil
        FotoProfil foto;
        createFotoProfil(&foto);

        // looping untuk baca foto profil
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

        listPengguna->contents[i].fotoProfil = foto;
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

    ADVWORD(true); // read sampe pita ditutup
    if (EOF)
        printf("Pengguna berhasil dibaca.\n");
}

void readKicauanConfig(char *filename, ListKicau *listKicau, ListPengguna listPengguna)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    printf("file kicau terbuka");
    STARTWORD(file, true);

    int banyakKicau = wordToInt(currentWord);

    int i; for (i = 0; i < banyakKicau; i++){
        Kicauan tweet;

        ADVWORD(true); // current word = ID
        tweet.id = wordToInt(currentWord);
        
        ADVWORD(true); // current word = text
        int j; for (j = 0; j < currentWord.Length; j++){
            tweet.text[j] = currentWord.TabWord[j];
        }

        ADVWORD(true); // current word = like
        tweet.like = wordToInt(currentWord);

        ADVWORD(true); // current word = author
        boolean found = false; j = 0;
        while((listPengguna.contents[j].index != MARK_STATIK)&&(found == false)){

            int k = 0; boolean tidaksama = false;

            while ((k < currentWord.Length) && (tidaksama == false)){
                if (currentWord.TabWord[k] != listPengguna.contents[j].username[k]) tidaksama = true;
                else k++;
            }
            
            if (tidaksama) j++;
            else found = true;

            if (found) tweet.authorID = listPengguna.contents[j].index;
            else j++;
        }

        ADVWORD(true);
        // tweet.datetime = 

        insertLastListKicau(&*listKicau, tweet);
    }

    printf("Kicauan berhasil dibaca");
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

void readUtasConfig(char *filename, ListPengguna listPengguna, ListUtas *listUtas)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    STARTWORD(file, true);
    int banyakKicau = wordToInt(currentWord); // banyak kicau
    for (int i = 0 ; i < banyakKicau ; i++)
    {
        Utas temp; int index;

        temp.IDUtas = i+1;

        ADVWORD(true);
        temp.idKicau = wordToInt(currentWord); // ID kicau

        ADVWORD(true);
        int banyakUtas = wordToInt(currentWord); // jumlah utas (kicauam sambungan)
        
        for (int j = 0 ; j < banyakUtas ; j++)
        {
            ADVWORD(true); // text utas
            for (j = 0; j < currentWord.Length; j++)
            {
                temp.text[j] = currentWord.TabWord[j];
            }

            ADVWORD(true); // authorname
            // ubah authorname jadi authorid
            boolean found = false; j = 0;
            while((listPengguna.contents[j].index != MARK_STATIK)&&(found == false))
            {
                int k = 0; boolean tidaksama = false;

                while ((k < currentWord.Length) && (tidaksama == false)){
                    if (currentWord.TabWord[k] != listPengguna.contents[j].username[k]) tidaksama = true;
                    else k++;
                }
                
                if (tidaksama) j++;
                else found = true;

                if (found) temp.idAuthor = listPengguna.contents[j].index;
                else j++;
            }

            ADVWORD(true);
            //datetime
        }
        insertLastListUtas(&listUtas,temp);
    }
}

void initReadConfig(Word fileName, ListPengguna *listPengguna, ListKicau *listKicau)
{
    readPenggunaConfig("../config/pengguna.txt", &*listPengguna);
    readKicauanConfig("../config/kicauan.txt", &*listKicau, *listPengguna);
    //  readBalasanConfig("config/balasan.txt");
    //  readDrafConfig("config/draf.txt");
    //  readUtasConfig("config/utas.txt");
}