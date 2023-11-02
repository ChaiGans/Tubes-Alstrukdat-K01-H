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
    (*X).id = InfoTop(currentDraf).id + 1;
    getLocalTime(&((*X).localtime));
    transferStringToString("", X->text);
}

void drafKicauToKicauan (Draf drafKicau, Kicauan* kicauBaru) {
    (*kicauBaru).authorID = drafKicau.authorID;
    transferStringToString(drafKicau.text, kicauBaru->text);
    (*kicauBaru).id = drafKicau.id;
    (*kicauBaru).like = 0;
    (*kicauBaru).localtime = drafKicau.localtime;
    (*kicauBaru).balasan = NULL;
}

void searchLastDraf (StackDraf stackDraf, int currentUserID, Draf* lastDraf, boolean* found) {
    ElTypeDraf currentDraf;
    *found = false;
    while (!IsEmptyStackDraf(stackDraf) && *found == false) {
        PopStackDraf(&stackDraf, &currentDraf);
        if (currentDraf.id == currentUserID) {
            *lastDraf = currentDraf;
            *found = true;
        }
    }
    *found = false;
}