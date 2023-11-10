/* File : ListUtas.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi Alamat dengan pointer */
/* Utas adalah integer */

#ifndef ListUtas_H
#define ListUtas_H

#include "boolean.h"
#include "datetime.h"

/* Definisi Node : */
typedef struct KicauanSambungan {
    int idAuthor;
    int indexKicauanSambungan;
    char text[280];
    DATETIME localtime;
} KicauanSambungan;

typedef struct Utas* AddressUtas;
typedef struct Utas {
    KicauanSambungan info;
    AddressUtas next;
} Utas;

typedef struct Node* AddressListUtas;
typedef struct Node {
    int idKicau;
    AddressUtas utas;
    AddressListUtas next;
} Node;

AddressListUtas newNodeListUtas(int idKicau);
AddressUtas newNodeKicauanSambungan (KicauanSambungan x);
/* Definisi ListUtas : */
/* ListUtas kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Alamat p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika Alamatnya Last, maka NEXT(Last)=NULL */


#define IDX_UNDEF_UTAS (-1)
#define FIRST(l) (l)
#define NEXT(l) (l->next)

// /* PROTOTYPE */
// /****************** PEMBUATAN LIST KOSONG ******************/
// void CreateListUtas(ListUtas *l);
// /* I.S. sembarang             */
// /* F.S. Terbentuk list kosong */

// /****************** TEST LIST KOSONG ******************/
// boolean isEmptyListUtas(ListUtas l);
// /* Mengirim true jika list kosong */

// /****************** GETTER SETTER ******************/
// Utas getElmtListUtas(ListUtas l, int idx);
// /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
// /* F.S. Mengembalikan nilai elemen l pada indeks idx */

// void setElmtListUtas(ListUtas *l, int idx, Utas val);
// /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
// /* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */

// int indexOfListUtas(ListUtas l, Utas val);
// /* I.S. l, val terdefinisi */
// /* F.S. Mencari apakah ada elemen list l yang bernilai val */
// /* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
// /* Mengembalikan IDX_UNDEF jika tidak ditemukan */

// /****************** PRIMITIF BERDASARKAN NILAI ******************/
// /*** PENAMBAHAN ELEMEN ***/
// void insertFirstListUtas(ListUtas *l, Utas val);
// /* I.S. l mungkin kosong */
// /* F.S. Melakukan alokasi sebuah elemen dan */
// /* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
// /* Jika alokasi gagal: I.S.= F.S. */

// void insertLastListUtas(ListUtas *l, Utas val);
// /* I.S. l mungkin kosong */
// /* F.S. Melakukan alokasi sebuah elemen dan */
// /* menambahkan elemen list di akhir: elemen terakhir yang baru */
// /* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

// void insertAtListUtas(ListUtas *l, Utas val, int idx);
// /* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
// /* F.S. Melakukan alokasi sebuah elemen dan */
// /* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
// /* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

// /*** PENGHAPUSAN ELEMEN ***/
// void deleteFirstListUtas(ListUtas *l, Utas *val);
// /* I.S. ListUtas l tidak kosong  */
// /* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
// /*      dan alamat elemen pertama di-dealokasi */
// void deleteLastListUtas(ListUtas *l, Utas *val);
// /* I.S. list tidak kosong */
// /* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
// /*      dan alamat elemen terakhir di-dealokasi */

// void deleteAtListUtas(ListUtas *l, int idx, Utas *val);
// /* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
// /* F.S. val diset dengan elemen l pada indeks ke-idx. */
// /*      Elemen l pada indeks ke-idx dihapus dari l */


// /****************** PROSES SEMUA ELEMEN LIST ******************/
// void displayListUtas(ListUtas l);
// // void printInfo(ListUtas l);
// /* I.S. ListUtas mungkin kosong */
// /* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
// /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
// /* Jika list kosong : menulis [] */
// /* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

// int ListUtaslength(ListUtas l);
// /* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

// /****************** PROSES TERHADAP LIST ******************/
// ListUtas concatListUtas(ListUtas l1, ListUtas l2) ;
// /* I.S. l1 dan l2 sembarang */
// /* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
// /* Konkatenasi dua buah list : l1 dan l2    */
// /* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
// /* Tidak ada alokasi/dealokasi pada prosedur ini */
AddressListUtas newNodeListUtas(int idKicauBaru);
AddressUtas newNodeKicauanSambungan (KicauanSambungan x);
void CreateListUtas(AddressListUtas *l);
boolean isEmptyListUtas(AddressListUtas l);
boolean isEmptyKicauanSambungan(AddressUtas l);
int indexOfListUtas(AddressListUtas l, int idKicauanUtama);
void insertFirstListUtas(AddressListUtas *l, int idKicauanBaru);
void insertFirstKicauanSambungan (AddressUtas *l, KicauanSambungan x);
void insertLastListUtas(AddressListUtas *l, int idKicauanBaru);
void insertLastKicauanSambungan(AddressUtas *l, KicauanSambungan x);
void deleteFirstListUtas(AddressListUtas *l, int* idKicauanTarget);
void deleteFirstKicauanSambungan(AddressUtas *l, KicauanSambungan* saveKicauan);
void deleteAtListUtas(AddressListUtas *l, int idx, int* idKicauanTarget);
void deleteAtKicauanSambungan(AddressUtas *l, int idx, KicauanSambungan* saveKicauanSambungan);
int ListUtaslength(AddressListUtas l);
int KicauanSambunganLength(AddressUtas l);
boolean isIdUtasDefined (int idSearch, AddressListUtas *listUtas);
int utaslength(AddressUtas au);
#endif