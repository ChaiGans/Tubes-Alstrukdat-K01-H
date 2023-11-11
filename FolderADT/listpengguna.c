#include <stdio.h>
#include "listpengguna.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListPengguna(ListPengguna *l)
{
    /* I.S. l sembarang */
    /* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
    /* Proses: Inisialisasi semua elemen List l dengan MARK */
    int i;
    for (i = IDX_MIN_STATIK; i < CAPACITY_STATIK; i++)
    {
        (*l).contents[i].index = MARK_STATIK;
    }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int ListPenggunaLength(ListPengguna l)
{
    /* Mengirimkan banyaknya elemen efektif List */
    /* Mengirimkan nol jika List kosong */
    int i, length;
    length = 0;
    for (i = IDX_MIN_STATIK; i < CAPACITY_STATIK; i++)
    {
        if (l.contents[i].index != MARK_STATIK)
        {
            length += 1;
        }
    }
    return length;
}

/* *** Selektor INDEKS *** */
IdxType getFirstIdxListPengguna(ListPengguna l)
{
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l pertama */
    return IDX_MIN_STATIK;
}

IdxType getLastIdxListPengguna(ListPengguna l)
{
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l terakhir */
    return ListPenggunaLength(l) - 1;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValidListPengguna(ListPengguna l, IdxType i)
{
    /* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
    /* yaitu antara indeks yang terdefinisi utk container*/
    return i < CAPACITY_STATIK && i >= IDX_MIN_STATIK;
}

boolean isIdxEffListPengguna(ListPengguna l, IdxType i)
{
    /* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
    /* yaitu antara 0..length(l)-1 */
    return i >= IDX_MIN_STATIK && i < ListPenggunaLength(l);
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmptyListPengguna(ListPengguna l)
{
    /* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
    return (ListPenggunaLength(l) == 0);
}

/* *** Test List penuh *** */
boolean isFullListPengguna(ListPengguna l)
{
    /* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
    return ListPenggunaLength(l) == CAPACITY_STATIK;
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */

void printListPengguna(ListPengguna l)
{
    /* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
    /* I.S. l boleh kosong */
    /* F.S. Jika l tidak kosong: [e1,e2,...,en] */
    /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
    /* Jika List kosong : menulis [] */
    int i;
    if (isEmptyListPengguna(l))
    {
        printf("[]");
    }
    else
    {
        printf("[");
        for (i = 0; i < ListPenggunaLength(l); i++)
        {
            if (i == ListPenggunaLength(l) - 1)
            {
                printf("%d", l.contents[i].index);
            }
            else
            {
                printf("%d,", l.contents[i].index);
            }
        }
        printf("]");
    }
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOfListPengguna(ListPengguna l, Profile val)
{
    /* Search apakah ada elemen List l yang bernilai val */
    /* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
    /* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
    /* Skema Searching yang digunakan bebas */
    if (isEmptyListPengguna(l))
    {
        return IDX_UNDEF_STATIK;
    }
    else
    {
        int i;
        for (i = IDX_MIN_STATIK; i < ListPenggunaLength(l); i++)
        {
            if (l.contents[i].index == val.index)
            {
                return i;
            }
        }
        return IDX_UNDEF_STATIK;
    }
}

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void insertFirstListPengguna(ListPengguna *l, Profile val)
{
    /* Proses: Menambahkan val sebagai elemen pertama List */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen pertama l yang baru */
    /* *** Menambahkan elemen pada index tertentu *** */
    int i;
    for (i = ListPenggunaLength(*l) - 1; i >= 0; i--)
    {
        (*l).contents[i + 1] = (*l).contents[i];
    }
    (*l).contents[0] = val;
}

void insertAtListPengguna(ListPengguna *l, Profile val, IdxType idx)
{
    /* Proses: Menambahkan val sebagai elemen pada index idx List */
    /* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l */
    /* F.S. val adalah elemen yang disisipkan pada index idx l */
    int i;
    for (i = ListPenggunaLength(*l) - 1; i >= idx; i--)
    {
        (*l).contents[i + 1] = (*l).contents[i];
    }
    (*l).contents[idx] = val;
}

/* *** Menambahkan elemen terakhir *** */
void insertLastListPengguna(ListPengguna *l, Profile val)
{
    /* Proses: Menambahkan val sebagai elemen terakhir List */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen terakhir l yang baru */
    (*l).contents[ListPenggunaLength(*l)] = val;
}

/* ********** MENGHAPUS ELEMEN ********** */
/* *** Menghapus elemen pertama *** */
void deleteFirstListPengguna(ListPengguna *l, Profile *val)
{
    /* Proses : Menghapus elemen pertama List */
    /* I.S. List tidak kosong */
    /* F.S. val adalah nilai elemen pertama l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    int i;
    *val = (*l).contents[0];
    for (i = 0; i < ListPenggunaLength(*l) - 1; i++)
    {
        (*l).contents[i] = (*l).contents[i + 1];
    }
    (*l).contents[getLastIdxListPengguna(*l)].index = MARK_STATIK;
}

/* *** Menghapus elemen pada index tertentu *** */
void deleteAtListPengguna(ListPengguna *l, Profile *val, IdxType idx)
{
    /* Proses : Menghapus elemen pada index idx List */
    /* I.S. List tidak kosong, idx adalah index yang valid di l */
    /* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    int i;
    *val = (*l).contents[idx];
    for (i = idx; i < ListPenggunaLength(*l) - 1; i++)
    {
        (*l).contents[i] = (*l).contents[i + 1];
    }
    (*l).contents[getLastIdxListPengguna(*l)].index = MARK_STATIK;
}

/* *** Menghapus elemen terakhir *** */
void deleteLastListPengguna(ListPengguna *l, Profile *val)
{
    /* Proses : Menghapus elemen terakhir List */
    /* I.S. List tidak kosong */
    /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    *val = (*l).contents[getLastIdxListPengguna(*l)];
    (*l).contents[getLastIdxListPengguna(*l)].index = MARK_STATIK;
}

boolean isUserAlreadyExist(ListPengguna l, Word username)
{
    int i;
    for (i = 0; i < ListPenggunaLength(l); i++)
    {
        if (wordStringCompare(username, l.contents[i].username))
        {
            return true;
        }
    }
    return false;
}

void findUsernameID(Word usernameInput, ListPengguna l, int *userID, boolean *usernameExist)
{
    int i;
    *usernameExist = false;
    *userID = IDX_UNDEF_STATIK;
    for (i = 0; i < ListPenggunaLength(l); i++)
    {
        if (wordStringCompare(usernameInput, l.contents[i].username))
        {
            *usernameExist = true;
            *userID = i;
        }
    }
}

boolean passwordChecker(int userID, ListPengguna l, Word passwordInput)
{
    return (wordStringCompare(passwordInput, l.contents[userID].password));
}

void displayNameFromID(int userID, ListPengguna l)
{
    int i = 0;
    while (l.contents[userID].username[i] != '\0')
    {
        printf("%c", l.contents[userID].username[i]);
        i += 1;
    }
}

boolean isAuthorAccountPublic(int authorID, ListPengguna listpengguna)
{
    return stringStringCompare(listpengguna.contents[authorID].status, "PUBLIK");
}

int findIDFromUsername(ListPengguna l, Word username)
{
    int i;
    for (i = 0; i < ListPenggunaLength(l); i++)
    {
        if (wordStringCompare(username, l.contents[i].username))
        {
            return i;
        }
    }
    return IDX_UNDEF_STATIK;
}