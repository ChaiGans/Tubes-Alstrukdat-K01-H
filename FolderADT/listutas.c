#include <stdio.h>
#include <stdlib.h>
#include "listutas.h"

AddressListUtas newNodeListUtas(int idKicauBaru)
{
    AddressListUtas p = (AddressListUtas)malloc(sizeof(Node));
    if (p != NULL)
    {
        p->idKicau = idKicauBaru;
        p->next = NULL;
        p->utas = NULL;
    }
}
AddressUtas newNodeKicauanSambungan(KicauanSambungan x)
{
    AddressUtas p = (AddressUtas)malloc(sizeof(Utas));
    if (p != NULL)
    {
        p->info = x;
        p->next = NULL;
    }
}
/* Definisi ListUtas : */
/* ListUtas kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Alamat p dapat diacu UTAS(p), NEXT(p) */
/* Elemen terakhir list: jika Alamatnya Last, maka NEXT(Last)=NULL */

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateListUtas(AddressListUtas *l)
{
    /* I.S. sembarang             */
    /* F.S. Terbentuk list kosong */
    FIRST(*l) = NULL;
}

// /****************** TEST LIST KOSONG ******************/
boolean isEmptyListUtas(AddressListUtas l)
{
    /* Mengirim true jika list kosong */
    return (FIRST(l) == NULL);
}
boolean isEmptyKicauanSambungan(AddressUtas l)
{
    /* Mengirim true jika list kosong */
    return (FIRST(l) == NULL);
}

// /****************** GETTER SETTER ******************/
// Utas getElmtListUtas(ListUtas l, int idx) {
//     /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
//     /* F.S. Mengembalikan nilai elemen l pada indeks idx */
//     int currentIdx = 0;
//     Alamat p = FIRST(l);
//     while (currentIdx < idx) {
//         currentIdx += 1;
//         p = NEXT(p);
//     }
//     return UTAS(p);
// }

// void setElmtListUtas(ListUtas *l, int idx, Utas val) {
//     /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
//     /* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
//     int currentIdx = 0;
//     Alamat p = FIRST(*l);
//     while (currentIdx < idx) {
//         currentIdx += 1;
//         p = NEXT(p);
//     }
//     UTAS(p) = val;
// }

int indexOfListUtas(AddressListUtas l, int idKicauanUtama)
{
    /* I.S. l, val terdefinisi */
    /* F.S. Mencari apakah ada elemen list l yang bernilai val */
    /* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
    /* Mengembalikan IDX_UNDEF_UTAS jika tidak ditemukan */
    int currentIdx = 0;
    AddressListUtas p = FIRST(l);
    while (p != NULL && p->idKicau != idKicauanUtama)
    {
        currentIdx += 1;
        p = NEXT(p);
    }
    if (p == NULL)
    {
        return IDX_UNDEF_UTAS;
    }
    else
    {
        return currentIdx;
    }
}

// /****************** PRIMITIF BERDASARKAN NILAI ******************/
// /*** PENAMBAHAN ELEMEN ***/
void insertFirstListUtas(AddressListUtas *l, int idKicauanBaru)
{
    /* I.S. l mungkin kosong */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
    /* Jika alokasi gagal: I.S.= F.S. */
    AddressListUtas p = newNodeListUtas(idKicauanBaru);
    if (p != NULL)
    {
        p->next = FIRST(*l);
        FIRST(*l) = p;
    }
}
void insertFirstKicauanSambungan(AddressUtas *l, KicauanSambungan x)
{
    AddressUtas p = newNodeKicauanSambungan(x);
    if (p != NULL)
    {
        p->next = FIRST(*l);
        FIRST(*l) = p;
    }
}

void insertLastListUtas(AddressListUtas *l, int idKicauanBaru)
{
    /* I.S. l mungkin kosong */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menambahkan elemen list di akhir: elemen terakhir yang baru */
    /* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
    if (isEmptyListUtas(*l))
    {
        insertFirstListUtas(l, idKicauanBaru);
    }
    else
    {
        AddressListUtas p = newNodeListUtas(idKicauanBaru);
        if (p != NULL)
        {
            AddressListUtas last = FIRST(*l);
            while (NEXT(last) != NULL)
            {
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }
}

void insertLastKicauanSambungan(AddressUtas *l, KicauanSambungan x)
{
    /* I.S. l mungkin kosong */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menambahkan elemen list di akhir: elemen terakhir yang baru */
    /* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
    if (isEmptyKicauanSambungan(*l))
    {
        insertFirstKicauanSambungan(l, x);
    }
    else
    {
        AddressUtas p = newNodeKicauanSambungan(x);
        if (p != NULL)
        {
            AddressUtas last = FIRST(*l);
            while (NEXT(last) != NULL)
            {
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }
}

// void insertAtListUtas(ListUtas *l, Utas val, int idx) {
//     /* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
//     /* F.S. Melakukan alokasi sebuah elemen dan */
//     /* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
//     /* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
//     Alamat insertElement = newNodeListUtas(val);
//     if (insertElement != NULL) {
//         if (idx == 0) {
//             insertFirstListUtas(l ,val);
//         } else {
//             Alamat p = FIRST(*l);
//             int currentIdx = 0;
//             while (currentIdx < idx-1) { // currentIdx < 3
//                 currentIdx += 1;
//                 p = NEXT(p);
//             }
//             NEXT(insertElement) = NEXT(p);
//             NEXT(p) = insertElement;
//         }
//     }
// }

// /*** PENGHAPUSAN ELEMEN ***/
void deleteFirstListUtas(AddressListUtas *l, int *idKicauanTarget)
{
    /* I.S. List l tidak kosong  */
    /* F.S. Elemen pertama list dihapus: nilai UTAS disimpan pada x */
    /*      dan alamat elemen pertama di-dealokasi */
    AddressListUtas p = FIRST(*l);
    *idKicauanTarget = p->idKicau;
    FIRST(*l) = NEXT(p);
    free(p);
}

void deleteFirstKicauanSambungan(AddressUtas *l, KicauanSambungan *saveKicauan)
{
    AddressUtas p = FIRST(*l);
    *saveKicauan = p->info;
    FIRST(*l) = NEXT(p);
    free(p);
}

// void deleteLastListUtas(ListUtas *l, Utas *val) {
//     /* I.S. list tidak kosong */
//     /* F.S. Elemen terakhir list dihapus: nilai UTAS disimpan pada x */
//     /*      dan alamat elemen terakhir di-dealokasi */
//     Alamat p = FIRST(*l);
//     Alamat prev = NULL;
//     while (NEXT(p) != NULL) {
//         prev = p;
//         p = NEXT(p);
//     }
//     if (prev == NULL) {
//         FIRST(*l) = NULL;
//     } else {
//         NEXT(prev) = NULL;
//     }
//     *val = UTAS(p);
//     free(p);
// }

void deleteAtListUtas(AddressListUtas *l, int idx, int *idKicauanTarget)
{
    /* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. val diset dengan elemen l pada indeks ke-idx. */
    /*      Elemen l pada indeks ke-idx dihapus dari l */
    if (idx == 0)
    {
        deleteFirstListUtas(l, idKicauanTarget);
    }
    else
    {
        int currentIdx = 0;
        AddressListUtas p = FIRST(*l);
        AddressListUtas prev;
        while (currentIdx < idx)
        {
            currentIdx += 1;
            prev = p;
            p = NEXT(p);
        }
        *idKicauanTarget = p->idKicau;
        NEXT(prev) = NEXT(p);
        free(p);
    }
}

void deleteAtKicauanSambungan(AddressUtas *l, int idx, KicauanSambungan *saveKicauanSambungan)
{
    /* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. val diset dengan elemen l pada indeks ke-idx. */
    /*      Elemen l pada indeks ke-idx dihapus dari l */
    if (idx == 0)
    {
        deleteFirstKicauanSambungan(l, saveKicauanSambungan);
    }
    else
    {
        int currentIdx = 0;
        AddressUtas p = FIRST(*l);
        AddressUtas prev;
        while (currentIdx < idx)
        {
            currentIdx += 1;
            prev = p;
            p = NEXT(p);
        }
        *saveKicauanSambungan = p->info;
        NEXT(prev) = NEXT(p);
        free(p);
    }
}

// /****************** PROSES SEMUA ELEMEN LIST ******************/
// void displayListUtas(ListUtas l) {
//     // void printUTAS(ListUtas l);
//     /* I.S. ListUtas mungkin kosong */
//     /* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
//     /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
//     /* Jika list kosong : menulis [] */
//     /* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
//     if (isEmptyListUtas(l)) {
//         printf("[]");
//     } else {
//         Alamat p = FIRST(l);
//         printf("[");
//         while (NEXT(p) != NULL) {
//             printf("%d,", UTAS(p).IDUtas);
//             p = NEXT(p);
//         }
//         if (NEXT(p) == NULL) {
//             printf("%d]", UTAS(p).IDUtas);
//         }
//     }
// }

int ListUtaslength(AddressListUtas l)
{
    /* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
    if (isEmptyListUtas(l))
    {
        return 0;
    }
    else
    {
        int currentIdx = 0;
        AddressListUtas p = FIRST(l);
        while (p != NULL)
        {
            currentIdx += 1;
            p = NEXT(p);
        }
        return (currentIdx);
    }
}

int KicauanSambunganLength(AddressUtas l)
{
    /* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
    if (isEmptyKicauanSambungan(l))
    {
        return 0;
    }
    else
    {
        int currentIdx = 0;
        AddressUtas p = FIRST(l);
        while (p != NULL)
        {
            currentIdx += 1;
            p = NEXT(p);
        }
        return (currentIdx);
    }
}

boolean isIdUtasDefined(int idSearch, AddressListUtas *listUtas)
{
    AddressListUtas p = *listUtas;
    while (p->idKicau != idSearch && NEXT(p) != NULL)
    {
        p = NEXT(p);
    }
    return (p->idKicau == idSearch);
}

int utaslength(AddressUtas au){
    int i = 0; AddressUtas p = au; while(p != NULL){
        p = p->next; i++;
    } return i;
}

// /****************** PROSES TERHADAP LIST ******************/
// ListUtas concatListUtas(ListUtas l1, ListUtas l2)  {
//     /* I.S. l1 dan l2 sembarang */
//     /* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
//     /* Konkatenasi dua buah list : l1 dan l2    */
//     /* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
//     /* Tidak ada alokasi/dealokasi pada prosedur ini */
//     ListUtas l3;
//     CreateListUtas(&l3);
//     Alamat p;
//     int val;
//     p = FIRST(l1);
//     while (p != NULL) {
//         insertLastListUtas(&l3,UTAS(p));
//         p = NEXT(p);
//     }
//     p = FIRST(l2);
//     while (p != NULL) {
//         insertLastListUtas(&l3,UTAS(p));
//         p = NEXT(p);
//     }
//     return l3;
// }