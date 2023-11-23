#include <stdio.h>
#include "stackdraf.h"

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStackDraf(StackDraf *S) {
    /* I.S. sembarang; */
    /* F.S. Membuat sebuah StackDraf S yang kosong berkapasitas MaxElStack */
    /* jadi indeksnya antara 0.. MaxElStack */
    /* Ciri StackDraf kosong : TOP bernilai Nil */
    Top(*S) = Nil;
}
/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStackDraf(StackDraf S) {
    /* Mengirim true jika StackDraf kosong: lihat definisi di atas */
    return (Top(S) == Nil);
}
boolean IsFullStackDraf(StackDraf S) {
    /* Mengirim true jika tabel penampung nilai elemen StackDraf penuh */
    return Top(S) == MaxElStack-1;
}

int LengthStackDraf(StackDraf S){
    int i = 0; ElTypeDraf tumbal;
    while (!IsEmptyStackDraf(S)){
        PopStackDraf(&S, &tumbal);
        i++;
    } return i;
}

/* ************ Menambahkan sebuah elemen ke StackDraf ************ */
void PushStackDraf(StackDraf * S, ElTypeDraf X) {
    /* Menambahkan X sebagai elemen StackDraf S. */
    /* I.S. S mungkin kosong, tabel penampung elemen StackDraf TIDAK penuh */
    /* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
    Top(*S) += 1;
    InfoTop(*S) = X;
}

/* ************ Menghapus sebuah elemen StackDraf ************ */
void PopStackDraf(StackDraf * S, ElTypeDraf* X) {
    /* Menghapus X dari StackDraf S. */
    /* I.S. S  tidak mungkin kosong */
    /* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
    *X = InfoTop(*S);
    Top(*S) -= 1;
}

void createDraf (StackDraf currentDraf, ElTypeDraf* X, int currentUserID) {
    (*X).authorID = currentUserID;
    getLocalTime(&((*X).localtime));
    transferStringToString("", X->text);
}