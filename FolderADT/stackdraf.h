/* File : StackDraf.h */
/* deklarasi StackDraf yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#ifndef StackDraft_H
#define StackDraft_H

#include "boolean.h"
#include "datetime.h"
#include "wordmachine.h"
#include "listkicau.h"

#define Nil -1
#define MaxElStack 100
/* Nil adalah StackDraf dengan elemen kosong . */

// StackDraf dari draf kicauan
typedef struct
{
    int id;
    char text[280];
    int authorID;
    DATETIME localtime;
} Draf;

typedef Draf ElTypeDraf;
typedef int address;   /* indeks tabel */

/* Contoh deklarasi variabel bertype StackDraf dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct { 
  ElTypeDraf T[MaxElStack]; /* tabel penyimpan elemen */
  address TOP;  /* alamat TOP: elemen puncak */
} StackDraf;
/* Definisi StackDraf S kosong : S.TOP = Nil */
/* Elemen yang dipakai menyimpan nilai StackDraf T[0]..T[MaxElStack-1] */
/* Jika S adalah StackDraf maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStackDraf(StackDraf *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah StackDraf S yang kosong berkapasitas MaxElStack */
/* jadi indeksnya antara 0.. MaxElStack */
/* Ciri StackDraf kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStackDraf(StackDraf S);
/* Mengirim true jika StackDraf kosong: lihat definisi di atas */
boolean IsFullStackDraf(StackDraf S);
/* Mengirim true jika tabel penampung nilai elemen StackDraf penuh */

/* ************ Menambahkan sebuah elemen ke StackDraf ************ */
void PushStackDraf(StackDraf * S, ElTypeDraf X);
/* Menambahkan X sebagai elemen StackDraf S. */
/* I.S. S mungkin kosong, tabel penampung elemen StackDraf TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen StackDraf ************ */
void PopStackDraf(StackDraf * S, ElTypeDraf* X);
/* Menghapus X dari StackDraf S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

void createDraf (StackDraf currentDraf, ElTypeDraf* X, int currentUserID);
void drafKicauToKicauan (Draf drafKicau, Kicauan* kicauBaru);
void searchLastDraf (StackDraf stackDraf, int currentUserID, Draf* lastDraf, boolean* found);
#endif