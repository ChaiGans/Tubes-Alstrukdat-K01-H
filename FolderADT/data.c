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

int charToInt (char w) {
    return w - '0';
}

void wordToIDParentParser (Word w, int* parentRoot, int* idBalasan) {
    int i = 0;
    int save = 1;
    int currentNumber = 0;
    while (w.TabWord[i] != ' ') {
        if (w.TabWord[i] == '-') {
            save = -1;
        } else {
            currentNumber *= 10;
            currentNumber += charToInt(w.TabWord[i]);
        }
        i+=1;
    }
    *parentRoot = save*currentNumber;
    i+=1;
    save = 1;
    currentNumber = 0;
    while (i < w.Length) {
        currentNumber *= 10;
        currentNumber += charToInt(w.TabWord[i]);
        i += 1;
    }
    *idBalasan = currentNumber;
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

Profile cariPengguna(Word uname, ListPengguna listPengguna){
    boolean found = false; int i = 0;

    while((listPengguna.contents[i].index != MARK_STATIK)&&(found == false)){

        int j = 0; boolean tidaksama = false;
        
        while((j < uname.Length)&&(tidaksama == false)){
            if (uname.TabWord[j] != listPengguna.contents[i].username[j]) tidaksama = true;
            else j++;
        } 

        if (tidaksama) i++;
        else found = true;

        if (found == false) i++;
    } 
    
    return listPengguna.contents[i];
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
        tweet.authorID = cariPengguna(currentWord, listPengguna).index;

        ADVWORD(true);
        // tweet.datetime = 

        insertLastListKicau(&*listKicau, tweet);
    }

    printf("Kicauan berhasil dibaca");
}

void readBalasanConfig(char *filename, ListKicau *l)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    STARTWORD(file, true);
    int banyakKicauan = wordToInt(currentWord);
    ADVWORD(true);
    int parentRoot, idBalasan;
    int i;
    for (i = 0; i < banyakKicauan; i++) {
        int currentIDKicauan = wordToInt(currentWord);
        ADVWORD(true);
        int banyakBalasan = wordToInt(currentWord);
        ADVWORD(true);
        int j; 
        for (j = 0; j < banyakBalasan; j++) {
            wordToIDParentParser(currentWord, &parentRoot, &idBalasan);
            ADVWORD(true);
            int k;
            if (parentRoot == -1) {
                for (k = 0; k < currentWord.Length; k++) {
                    (*l).buffer[currentIDKicauan].balasan->info.text[k] = currentWord.TabWord[k];
                }
                (*l).buffer[currentIDKicauan].balasan->info.id = idBalasan;
            } else {

            }
            ADVWORD(true);
            int authorID;
            // Parse authorID
            (*l).buffer[currentIDKicauan].balasan->info.authorID = authorID;
            ADVWORD(true);
            // Parse local time
        }
    }
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

            insertLastListUtas(listUtas,temp);
        }
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