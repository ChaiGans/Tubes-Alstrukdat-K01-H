#include <stdio.h>
#include <stdlib.h>
#include "listutas.h"

Address newNodeListUtas(Utas val) {
    Address p = (Address) malloc (sizeof (Node));
    if (p != NULL) {
        UTAS(p) = val;
        NEXT(p) = NULL;
    }
    return p;
}

/* Definisi ListUtas : */
/* ListUtas kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu UTAS(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateListUtasUtas(ListUtas *l) {
    /* I.S. sembarang             */
    /* F.S. Terbentuk list kosong */
    FIRST(*l) = NULL;
}

/****************** TEST LIST KOSONG ******************/
boolean isEmptyListUtas(ListUtas l) {
    /* Mengirim true jika list kosong */
    return (FIRST(l) == NULL);
}

/****************** GETTER SETTER ******************/
Utas getElmtListUtas(ListUtas l, int idx) {
    /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. Mengembalikan nilai elemen l pada indeks idx */
    int currentIdx = 0;
    Address p = FIRST(l);
    while (currentIdx < idx) {
        currentIdx += 1;
        p = NEXT(p);
    }
    return UTAS(p);
}

void setElmtListUtas(ListUtas *l, int idx, Utas val) {
    /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
    int currentIdx = 0;
    Address p = FIRST(*l);
    while (currentIdx < idx) {
        currentIdx += 1;
        p = NEXT(p); 
    }
    UTAS(p) = val;
}

int indexOfListUtas(ListUtas l, Utas val) {
    /* I.S. l, val terdefinisi */
    /* F.S. Mencari apakah ada elemen list l yang bernilai val */
    /* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
    /* Mengembalikan IDX_UNDEF jika tidak ditemukan */
    int currentIdx = 0;
    Address p = FIRST(l);
    while (p != NULL && UTAS(p).IDUtas != val.IDUtas) {
        currentIdx += 1;
        p = NEXT(p);
    }
    if (p == NULL) {
        return IDX_UNDEF;
    } else {
        return currentIdx;
    }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirstListUtas(ListUtas *l, Utas val) {
    /* I.S. l mungkin kosong */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
    /* Jika alokasi gagal: I.S.= F.S. */
    Address p = newNodeListUtas(val);
    if (p != NULL){
        NEXT(p) = FIRST(*l);
        FIRST(*l) = p;
    }
 
}
void insertLastListUtas(ListUtas *l, Utas val) {
    /* I.S. l mungkin kosong */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menambahkan elemen list di akhir: elemen terakhir yang baru */
    /* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
    if (isEmptyListUtas(*l)) {
        insertFirstListUtas(l, val);
    } else {
        Address p = newNodeListUtas(val);
        if (p != NULL) {
            Address last = FIRST(*l);
            while (NEXT(last) != NULL) {
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }
}

void insertAtListUtas(ListUtas *l, Utas val, int idx) {
    /* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
    /* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
    Address insertElement = newNodeListUtas(val);
    if (insertElement != NULL) {
        if (idx == 0) {
            insertFirstListUtas(l ,val);
        } else {
            Address p = FIRST(*l);
            int currentIdx = 0;
            while (currentIdx < idx-1) { // currentIdx < 3
                currentIdx += 1;
                p = NEXT(p);
            }
            NEXT(insertElement) = NEXT(p);
            NEXT(p) = insertElement;
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirstListUtas(ListUtas *l, Utas *val) {
    /* I.S. List l tidak kosong  */
    /* F.S. Elemen pertama list dihapus: nilai UTAS disimpan pada x */
    /*      dan alamat elemen pertama di-dealokasi */
    Address p = FIRST(*l);
    *val = UTAS(p);
    FIRST(*l) = NEXT(p);
    free(p);

}
void deleteLastListUtas(ListUtas *l, Utas *val) {
    /* I.S. list tidak kosong */
    /* F.S. Elemen terakhir list dihapus: nilai UTAS disimpan pada x */
    /*      dan alamat elemen terakhir di-dealokasi */
    Address p = FIRST(*l);
    Address prev = NULL;
    while (NEXT(p) != NULL) {
        prev = p;
        p = NEXT(p);
    }
    if (prev == NULL) {
        FIRST(*l) = NULL;
    } else {
        NEXT(prev) = NULL;
    }
    *val = UTAS(p);
    free(p);
}

void deleteAtListUtas(ListUtas *l, int idx, Utas *val) {
    /* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. val diset dengan elemen l pada indeks ke-idx. */
    /*      Elemen l pada indeks ke-idx dihapus dari l */
    if (idx == 0){
        deleteFirstListUtas(l,val);
    } else{
        int currentIdx = 0;
        Address p = FIRST(*l);
        Address prev;
        while (currentIdx < idx) { 
            currentIdx += 1;
            prev = p;
            p = NEXT(p);
        }
        *val = UTAS(p);
        NEXT(prev) = NEXT(p);
        free(p);
    }
}


/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayListUtas(ListUtas l) {
    // void printUTAS(ListUtas l);
    /* I.S. ListUtas mungkin kosong */
    /* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
    /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
    /* Jika list kosong : menulis [] */
    /* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
    if (isEmpty(l)) { 
        printf("[]");
    } else {
        Address p = FIRST(l);
        printf("[");
        while (NEXT(p) != NULL) {
            printf("%d,", UTAS(p).IDUtas);
            p = NEXT(p);
        }
        if (NEXT(p) == NULL) {
            printf("%d]", UTAS(p).IDUtas);
        }
    }
}

int ListUtaslength(ListUtas l) {
    /* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
    if (isEmpty(l)) {
        return 0;
    } else {
        int currentIdx = 0;
        Address p = FIRST(l);
        while (p != NULL) {
            currentIdx += 1;
            p = NEXT(p);
        }
        return (currentIdx);
    }
}

/****************** PROSES TERHADAP LIST ******************/
ListUtas concatListUtas(ListUtas l1, ListUtas l2)  {
    /* I.S. l1 dan l2 sembarang */
    /* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
    /* Konkatenasi dua buah list : l1 dan l2    */
    /* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
    /* Tidak ada alokasi/dealokasi pada prosedur ini */
    ListUtas l3;
    CreateListUtas(&l3);
    Address p;
    int val;
    p = FIRST(l1);
    while (p != NULL) {
        insertLastListUtas(&l3,UTAS(p));
        p = NEXT(p);
    }
    p = FIRST(l2);
    while (p != NULL) {
        insertLastListUtas(&l3,UTAS(p));
        p = NEXT(p);
    }
    return l3;
}