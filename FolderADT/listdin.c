#include <stdio.h>
#include "listdin.h"
#include <stdlib.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDin(ListDin *l, int capacity) {
    /* I.S. l sembarang, capacity > 0 */
    /* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */
    CAPACITY(*l) = capacity;
    NEFF(*l) = 0;
    BUFFER(*l) = (ElType *) malloc (capacity * sizeof (ElType));
}

void dealocateListDin(ListDin *l) {
    /* I.S. l terdefinisi; */
    /* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */
    CAPACITY(*l) = 0;
    NEFF(*l) = 0;
    free(BUFFER(*l));
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listDinLength(ListDin l) {
    /* Mengirimkan banyaknya elemen efektif list */
    /* Mengirimkan nol jika list l kosong */
    /* *** Daya tampung container *** */
    return NEFF(l);
}

/* *** Selektor INDEKS *** */
IdxType getFirstIdxListDin(ListDin l) { 
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l pertama */
    return IDX_MIN_LISTDIN;
}
IdxType getLastIdxListDin(ListDin l) {
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l terakhir */
    return NEFF(l)-1;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValidListDin(ListDin l, IdxType i) {
    /* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
    /* yaitu antara indeks yang terdefinisi utk container*/
    return i<CAPACITY(l) && i>=IDX_MIN_LISTDIN;
}
boolean isIdxEffListDin(ListDin l, IdxType i) {
    /* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
    /* yaitu antara 0..NEFF(l) */
    return i<NEFF(l) && i>=IDX_MIN_LISTDIN;
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmptyListDin(ListDin l) {
    /* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
    return listDinLength(l)==0;
}
/* *** Test list penuh *** */
boolean isFullListDin(ListDin l) {
    /* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
    return listDinLength(l) == CAPACITY(l);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi list dari pembacaan *** */
void readListDin(ListDin *l) {
    /* I.S. l sembarang dan sudah dialokasikan sebelumnya */
    /* F.S. List l terdefinisi */
    /* Proses : membaca banyaknya elemen l dan mengisi nilainya */
    /* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
    /*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= CAPACITY(l) */
    /*    Jika N tidak valid, tidak diberikan pesan kesalahan */
    /* 2. Jika 0 < N <= CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
        0 satu per satu diakhiri enter */
    /*    Jika N = 0; hanya terbentuk l kosong */
    int N, i;
    do {
        scanf("%d", &N);
    } while (N<0 || N>CAPACITY(*l));
    CreateListDin(l, N);
    int temp;
    for (i=0; i<N; i++) {
        scanf("%d", &temp);
        ELMT_DIN(*l, i) = temp;
    }
    NEFF(*l) = N;
}

void printListDin(ListDin l) { 
    /* Proses : Menuliskan isi list dengan traversal, list ditulis di antara kurung siku;
    antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
    di tengah, atau di belakang, termasuk spasi dan enter */
    /* I.S. l boleh kosong */
    /* F.S. Jika l tidak kosong: [e1,e2,...,en] */
    /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
    /* Jika list kosong : menulis [] */
    int i;
    if (isEmptyListDin(l)) {
        printf("[]");
    }
    else {
        printf("[");
        for (i=0; i<listDinLength(l); i++) {
            if (i==getLastIdxListDin(l)) {
                printf("%d", ELMT_DIN(l,i));
            } else {
                printf("%d,", ELMT_DIN(l,i));
            }
        }
        printf("]");
    }
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika list : Penjumlahan, pengurangan, perkalian, ... *** */
ListDin plusMinusListDin(ListDin l1, ListDin l2, boolean plus) {
    /* Prekondisi : l1 dan l2 memiliki Neff sama dan tidak kosong */
    /* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada indeks yang sama dijumlahkan */
    /* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi elemen l2 pada indeks yang sama */
    int i;
    ListDin lresult;
    CreateListDin(&lresult, CAPACITY(l1));
    NEFF(lresult) = NEFF(l1);
    if (plus) {
        for (i=0; i<NEFF(l1); i++) {
            ELMT_DIN(lresult,i) = ELMT_DIN(l1,i) + ELMT_DIN(l2,i);
        }
    } else {
        for (i=0; i<NEFF(l1); i++) {
            ELMT_DIN(lresult,i) = ELMT_DIN(l1,i) - ELMT_DIN(l2,i);
        }
    }
    return lresult;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan list : < =, > *** */
boolean isListDinEqual(ListDin l1, ListDin l2) {
    /* Mengirimkan true jika l1 sama dengan l2 yaitu jika nEff l1 = l2 dan semua elemennya sama */
    if (listDinLength(l1) == listDinLength(l2)) {
        int i;
        for (i=0; i<listDinLength(l1); i++) {
            if (ELMT_DIN(l1,i) != ELMT_DIN(l2,i)) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOfListDin(ListDin l, ElType val) {
    /* Search apakah ada elemen List l yang bernilai val */
    /* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
    /* Jika tidak ada, mengirimkan IDX_UNDEF */
    /* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
    /* Skema Searching yang digunakan bebas */
    int i;
    if (isEmptyListDin(l)) {
        return IDX_UNDEF_LISTDIN;
    } 
    else {
        for (i=0; i<listDinLength(l); i++) {
            if (ELMT_DIN(l,i) == val) {
                return i;
            }
        }
    }
    return IDX_UNDEF_LISTDIN;
}

/* ********** NILAI EKSTREM ********** */
void extremeValuesListDin(ListDin l, ElType *max, ElType *min) {
    /* I.S. List l tidak kosong */
    /* F.S. max berisi nilai maksimum l;
            min berisi nilai minimum l */
    int maximum = ELMT_DIN(l, getFirstIdxListDin(l));
    int minimum = ELMT_DIN(l, getFirstIdxListDin(l));
    int i;
    if (listDinLength(l) > 1) {
        for (i=1; i<listDinLength(l); i++) {
            if (maximum < ELMT_DIN(l,i)) {
                maximum = ELMT_DIN(l,i);
            }
            if (minimum > ELMT_DIN(l,i)) {
                minimum = ELMT_DIN(l,i);
            }
        }
    }
    *max = maximum;
    *min = minimum;
}

/* ********** OPERASI LAIN ********** */
void copyListDin(ListDin lIn, ListDin *lOut) {
    /* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
    /* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
    /* Proses : Menyalin isi lIn ke lOut */ 
    CreateListDin(lOut, CAPACITY(lIn));
    int i;
    for (i=0; i<NEFF(lIn); i++) {
        ELMT_DIN(*lOut, i) = ELMT_DIN(lIn, i);
    };
    NEFF(*lOut) = NEFF(lIn);
}

ElType sumListDin(ListDin l) {
    /* Menghasilkan hasil penjumlahan semua elemen l */
    /* Jika l kosong menghasilkan 0 */  
    int sum, i;
    sum = 0;
    for (i=0; i<listDinLength(l); i++) {
        sum += ELMT_DIN(l, i);
    }
    return sum;
}
int countValListDin(ListDin l, ElType val) {
    /* Menghasilkan berapa banyak kemunculan val di l */
    /* Jika l kosong menghasilkan 0 */
    int cnt, i;
    cnt = 0;
    for (i=0; i<listDinLength(l); i++) {
        if (ELMT_DIN(l, i) == val) {
            cnt += 1;
        }
    }
    return cnt;
}

/* ********** SORTING ********** */
void sortListDin(ListDin *l, boolean asc) {
    /* I.S. l boleh kosong */
    /* F.S. Jika asc = true, l terurut membesar */
    /*      Jika asc = false, l terurut mengecil */
    /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
    algoritma bebas */
    int temp;
    int i, j;
    if (asc) {
        for (i=0; i<listDinLength(*l); i++) {
            for (j=0; j<listDinLength(*l)-1; j++) {
                if (ELMT_DIN(*l, j)>ELMT_DIN(*l, j+1)) {
                    temp = ELMT_DIN(*l, j);
                    ELMT_DIN(*l, j) = ELMT_DIN(*l, j+1);
                    ELMT_DIN(*l, j+1) = temp;
                }
            }
        }
    } else {
        for (i=0; i<listDinLength(*l); i++) {
            for (j=0; j<listDinLength(*l)-1; j++) {
                if (ELMT_DIN(*l, j)<ELMT_DIN(*l, j+1)) {
                    temp = ELMT_DIN(*l, j);
                    ELMT_DIN(*l, j) = ELMT_DIN(*l, j+1);
                    ELMT_DIN(*l, j+1) = temp;
                }
            }
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLastListDin(ListDin *l, ElType val) {
    /* Proses: Menambahkan val sebagai elemen terakhir list */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen terakhir l yang baru */
    if (isEmptyListDin(*l)) {
        ELMT_DIN(*l, 0) = val;
    } else {
        ELMT_DIN(*l, getLastIdxListDin(*l)+1) = val;
    }
    NEFF(*l) += 1;
}
/* ********** MENGHAPUS ELEMEN ********** */
void deleteLastListDin(ListDin *l, ElType *val) {
    /* Proses : Menghapus elemen terakhir list */
    /* I.S. List tidak kosong */
    /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
    /*      Banyaknya elemen list berkurang satu */
    /*      List l mungkin menjadi kosong */
    *val = ELMT_DIN(*l, getLastIdxListDin(*l));
    NEFF(*l) -= 1;
}

/* ********* MENGUBAH UKURAN ARRAY ********* */
void expandListDin(ListDin *l, int num) {
    /* Proses : Menambahkan capacity l sebanyak num */
    /* I.S. List sudah terdefinisi */
    /* F.S. Ukuran list bertambah sebanyak num */
    CAPACITY(*l) += num;
    BUFFER(*l) = realloc(BUFFER(*l), (CAPACITY(*l)) * sizeof(ElType));
}

void shrinkListDin(ListDin *l, int num) {
    /* Proses : Mengurangi capacity sebanyak num */
    /* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
    /* F.S. Ukuran list berkurang sebanyak num. */
    CAPACITY(*l) -= num;
    BUFFER(*l) = realloc(BUFFER(*l), (CAPACITY(*l)) * sizeof(ElType));
}

void compressListDin(ListDin *l) {
    /* Proses : Mengubah capacity sehingga capacity = nEff */
    /* I.S. List tidak kosong */
    /* F.S. Ukuran capacity = nEff */
    CAPACITY(*l) = NEFF(*l);
    BUFFER(*l) = realloc(BUFFER(*l), (CAPACITY(*l)) * sizeof(ElType));
}