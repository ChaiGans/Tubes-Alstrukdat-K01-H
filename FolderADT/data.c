#include "data.h"
#include <stdio.h>
#include <stdlib.h>

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
    int sign = 1;
    if (w.TabWord[0] == '-')
    {
        sign = -1;
        i = 1;
    }
    else
    {
        i = 0;
    }
    for (; i < w.Length; i++)
    {
        res *= 10;
        res += w.TabWord[i] - '0';
    }
    return res * sign;
}

int charToInt(char w)
{
    return w - '0';
}

void makeUpperCase(Word *w)
{
    int i;
    for (i = 0; i < w->Length; i++)
    {
        if (w->TabWord[i] >= 'a' && w->TabWord[i] <= 'z')
        {
            // Ubah karakter menjadi huruf kapital
            w->TabWord[i] = w->TabWord[i] - 'a' + 'A';
        }
    }
}

void drafAuthorParser(Word w, int *authorID, int *banyakDraf, ListPengguna l)
{
    char username[20];
    int i = 0;
    while (w.TabWord[i] && (w.TabWord[i] < '0' || w.TabWord[i] > '9'))
    {
        username[i] = w.TabWord[i];
        i += 1;
    }
    if (i > 0 && username[i - 1] == ' ')
    {
        i -= 1;
    }
    username[i] = '\0';
    while (w.TabWord[i] == ' ')
    {
        i += 1;
    }
    int res = 0;
    while (w.TabWord[i] >= '0' && w.TabWord[i] <= '9')
    {
        res = res * 10 + (w.TabWord[i] - '0');
        i += 1;
    }
    boolean usernameexist;
    findUsernameIDbyString(username, l, authorID, &usernameexist);
    *banyakDraf = res;
}

void wordToIDParentParser(Word w, int *parentRoot, int *idBalasan)
{
    int i = 0;
    int save = 1;
    int currentNumber = 0;
    while (w.TabWord[i] != ' ')
    {
        if (w.TabWord[i] == '-')
        {
            save = -1;
        }
        else
        {
            currentNumber *= 10;
            currentNumber += charToInt(w.TabWord[i]);
        }
        i += 1;
    }
    *parentRoot = save * currentNumber;
    i += 1;
    save = 1;
    currentNumber = 0;
    while (i < w.Length)
    {
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

void readPenggunaConfig(char *filename, ListPengguna *listPengguna, GrafPertemanan *pertemanan)
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
        createProfile(&((*listPengguna).contents[i]));
        CreateEmptyStackDraf(&((*listPengguna).contents[i].stackdraf));
        listPengguna->contents[i].index = i;
        ADVWORD(true); // currentWord = username
        cutWord(currentWord, listPengguna->contents[i].username);

        ADVWORD(true); // currentWord = password
        cutWord(currentWord, listPengguna->contents[i].password);

        ADVWORD(true); // currentWord = bio
        cutWord(blankLineCheck(currentWord), listPengguna->contents[i].bio);

        ADVWORD(true);
        if (currentWord.Length > 10)
        {
            listPengguna->contents[i].nomorHP = realloc(listPengguna->contents[i].nomorHP, currentWord.Length * sizeof(char) + 1);
        }
        transferWordToString(listPengguna->contents[i].nomorHP, currentWord);
        ADVWORD(true); // currentWord = weton
        cutWord(blankLineCheck(currentWord), listPengguna->contents[i].weton);

        ADVWORD(true); // currentWord = status
        makeUpperCase(&currentWord);
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

    createGrafPertemanan(pertemanan, banyakProfile);
    for (int i = 0; i < banyakProfile; i++)
    {
        ADVWORD(true); // currentWord = baris pertama
        for (int j = 0; j < banyakProfile * 2; j += 2)
        {
            ElmtGrafPertemanan(*pertemanan, i, j / 2) = currentWord.TabWord[j];
        }
    }

    for (int i = 0; i < banyakProfile; i++)
    {
        MakeEmptyQueue(&((*listPengguna).contents[i].permintaanTeman), 20);
    }

    ADVWORD(true);
    int banyakPermintaanPertemenan = wordToInt(currentWord);
    for (int i = 0; i < banyakPermintaanPertemenan; i++)
    {
        ADVWORD(true); // currentWord = username pengirim
        int j = 0;
        // mendapatkan id pengirim
        int idPengirim = 0;
        while (currentWord.TabWord[j] != BLANK)
        {
            idPengirim *= 10;
            idPengirim += charToInt(currentWord.TabWord[j]);
            j++;
        } // idPengirim terdefinisi, j ada di ' '

        // mendapatkan id penerima
        int idPenerima = 0;
        j++;
        while (currentWord.TabWord[j] != BLANK)
        {
            idPenerima *= 10;
            idPenerima += charToInt(currentWord.TabWord[j]);
            j++;
        } // idPenerima terdefinisi, j ada di ' '

        // mendefinisikan bahwa idPengirim mengirimkan permintaan pertemanan ke idPenerima
        ElmtGrafPertemanan(*pertemanan, idPengirim, idPenerima) = '1';

        // mendapatkan popularitas
        int popularitas = 0;
        j++;
        while (j < currentWord.Length)
        {
            popularitas *= 10;
            popularitas += charToInt(currentWord.TabWord[j]);
            j++;
        } // popularitas terdefinisi

        infotype adjInfo;
        adjInfo.id = idPengirim;
        adjInfo.popularity = popularitas;

        // enqueue adjInfo
        Enqueue(&((*listPengguna).contents[idPenerima].permintaanTeman), adjInfo);
    }

    ADVWORD(true); // read sampe pita ditutup
    if (EOF)
        printf("Config pengguna berhasil dibaca... \n");
}

Profile cariPengguna(Word uname, ListPengguna listPengguna)
{
    boolean found = false, sama;
    int i = 0, j;

    while ((listPengguna.contents[i].index != MARK_STATIK) && (found == false))
    {

        j = 0;
        sama = true;

        while ((j < uname.Length) && (sama))
        {
            if (uname.TabWord[j] != listPengguna.contents[i].username[j])
                sama = false;
            else
                j++;
        }

        if ((sama) && listPengguna.contents[i].username[j] == '\0')
            found = true;
        else
            i++;
    }

    return listPengguna.contents[i];
}

Profile cariPenggunaID(int ID, ListPengguna lp)
{
    boolean found = false;
    int i = 0;

    while ((lp.contents[i].index != MARK_STATIK) && (found == false))
    {
        if (lp.contents[i].index == ID)
            found = true;
        else
            i++;
    }

    return lp.contents[i];
}

void readKicauanConfig(char *filename, ListKicau *listKicau, ListPengguna listPengguna)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    STARTWORD(file, true);

    int banyakKicau = wordToInt(currentWord);

    int i;
    for (i = 0; i < banyakKicau; i++)
    {
        Kicauan tweet;

        ADVWORD(true); // current word = ID
        tweet.id = wordToInt(currentWord);

        ADVWORD(true); // current word = text
        int j;
        for (j = 0; j < currentWord.Length; j++)
        {
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
    printf("Config kicauan berhasil dibaca... \n");
}

void readBalasanConfig(char *filename, ListKicau *l, ListPengguna listpengguna)
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
    for (i = 0; i < banyakKicauan; i++)
    {
        int currentIDKicauan = wordToInt(currentWord);
        ADVWORD(true);
        int banyakBalasan = wordToInt(currentWord);
        ADVWORD(true);
        int j;
        for (j = 0; j < banyakBalasan; j++)
        {
            Balasan balasanBacaan;
            wordToIDParentParser(currentWord, &parentRoot, &idBalasan);
            ADVWORD(true);
            transferWordToString(balasanBacaan.text, currentWord);
            ADVWORD(true);
            int userID;
            boolean usernameExist;
            findUsernameID(currentWord, listpengguna, &userID, &usernameExist);
            balasanBacaan.authorID = userID;
            ADVWORD(true);
            DATETIMEparser(currentWord.TabWord, &balasanBacaan.time);
            ADVWORD(true);
            if (parentRoot == -1)
            {
                balasanBacaan.id = idBalasan;
                (*l).buffer[currentIDKicauan].balasan = newTreeNode(balasanBacaan);
            }
            else
            {
                balasanBacaan.id = idBalasan;
                addChildrenAt(parentRoot, &(*l).buffer[currentIDKicauan].balasan, balasanBacaan);
            }
        }
    }
    printf("Config balasan berhasil dibaca... \n");
}

void readDrafConfig(char *filename, ListPengguna *listpengguna)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    STARTWORD(file, true);
    Draf drafBaru;
    int banyakPengguna = wordToInt(currentWord);
    ADVWORD(true);
    int i, j, banyakDrafPengguna, authorID;
    for (i = 0; i < banyakPengguna; i++)
    {
        drafAuthorParser(currentWord, &authorID, &banyakDrafPengguna, *listpengguna);
        ADVWORD(true);
        for (j = 0; j < banyakDrafPengguna; j++)
        {
            transferWordToString(drafBaru.text, currentWord);
            ADVWORD(true);
            DATETIMEparser(currentWord.TabWord, &drafBaru.localtime);
            ADVWORD(true);
            drafBaru.authorID = authorID;
            PushStackDraf(&(*listpengguna).contents[authorID].stackdraf, drafBaru);
            ADVWORD(true);
        }
    }
    printf("Config draf berhasil dibaca... \n");
}

void readUtasConfig(char *filename, ListPengguna listPengguna, ListKicau *listKicau, AddressListUtas *listUtas)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File %s tidak ditemukan.\n", filename);
        return;
    }
    STARTWORD(file, true); // banyak kicauan yang jadi utas
    int banyakUtas = wordToInt(currentWord);
    for (int i = 0; i < banyakUtas; i++)
    {
        KicauanSambungan temp;

        ADVWORD(true); // idKicau
        int idKicau = wordToInt(currentWord);
        insertLastListUtas(listUtas, idKicau);

        AddressListUtas s = *listUtas; // Address utas
        while (s->idKicau != idKicau)
        {
            s = NEXT(s);
        }
        AddressUtas p = s->utas;

        int i = 0;
        while ((*listKicau).buffer[i].id != idKicau && i != listKicauLength(*listKicau))
        {
            i += 1;
        }
        if (i == listKicauLength(*listKicau)) // belum ada kicaunya
        {
            printf("Belum ada kicauan dengan ID ini!\n"); // handle kalau kicauan belum ada
        }
        else
        {
            temp.idAuthor = (*listKicau).buffer[i].authorID;
            temp.indexKicauanSambungan = 0;
            DATETIMEparser(currentWord.TabWord, &temp.localtime);
            transferStringToString((*listKicau).buffer[idKicau].text, temp.text);
            insertLastKicauanSambungan(&p, temp);

            ADVWORD(true); // jumlah kicauan sambungan
            int banyakKicauanSambungan = wordToInt(currentWord);

            for (int j = 1; j < banyakKicauanSambungan + 1; j++)
            {
                ADVWORD(true); // text
                for (j = 0; j < currentWord.Length; j++)
                {
                    temp.text[j] = currentWord.TabWord[j];
                }

                ADVWORD(true); // authorname
                // ubah authorname jadi authorid
                temp.idAuthor = cariPengguna(currentWord, listPengguna).index;

                ADVWORD(true);
                // datetime
                DATETIMEparser(currentWord.TabWord, &temp.localtime);

                temp.indexKicauanSambungan = KicauanSambunganLength(p);
                printf("%d\n", temp.idAuthor);

                insertLastKicauanSambungan(&p, temp);
            }
        }
    }
    printf("Config utas berhasil dibaca... \n");
}

void initReadConfig(Word fileName, ListPengguna *listPengguna, GrafPertemanan *pertemanan, ListKicau *listKicau, AddressListUtas *listUtas)
{
    readPenggunaConfig("config/pengguna.txt", listPengguna, pertemanan);
    readKicauanConfig("config/kicauan.txt", listKicau, *listPengguna);
    readBalasanConfig("config/balasan.txt", listKicau, *listPengguna);
    // readDrafConfig("config/draf.txt");
    readUtasConfig("config/utas.txt", *listPengguna, listKicau, listUtas);
}
