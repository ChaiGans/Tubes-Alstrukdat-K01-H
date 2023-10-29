#include <stdio.h>
#include "liststatik.h"
#include <math.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListStatik(ListStatik *l) {
    /* I.S. l sembarang */
    /* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
    /* Proses: Inisialisasi semua elemen List l dengan MARK */
    int i;
    for (i=IDX_MIN_STATIK;i<CAPACITY_STATIK;i++) {
        ELMT(*l, i) = MARK_STATIK;
    }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listStatikLength(ListStatik l) {
    /* Mengirimkan banyaknya elemen efektif List */
    /* Mengirimkan nol jika List kosong */  
    int i, length;
    length = 0;
    for (i=IDX_MIN_STATIK; i<CAPACITY_STATIK; i++) {
        if (ELMT(l, i) != MARK_STATIK) {
            length += 1;
        }
    }
    return length;
}

/* *** Selektor INDEKS *** */
IdxType getFirstIdxListStatik(ListStatik l) {
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l pertama */
    return IDX_MIN_STATIK;
}

IdxType getLastIdxListStatik(ListStatik l) {
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l terakhir */
    return listStatikLength(l)-1;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValidListStatik(ListStatik l, IdxType i) {
    /* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
    /* yaitu antara indeks yang terdefinisi utk container*/
    return i<CAPACITY_STATIK && i>=IDX_MIN_STATIK;
}

boolean isIdxEffListStatik(ListStatik l, IdxType i) {
    /* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
    /* yaitu antara 0..length(l)-1 */
    return i>=IDX_MIN_STATIK && i<listStatikLength(l);
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmptyListStatik(ListStatik l) {
    /* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
    return (listStatikLength(l) == 0);
}

/* *** Test List penuh *** */
boolean isFullListStatik(ListStatik l) {
    /* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
    return listStatikLength(l) == CAPACITY_STATIK;
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
void readListStatik(ListStatik *l) {
    /* I.S. l sembarang */
    /* F.S. List l terdefinisi */
    /* Proses: membaca banyaknya elemen l dan mengisi nilainya */
    /* 1. Baca banyaknya elemen diakhiri enter, misalnya n */
    /*    Pembacaan diulangi sampai didapat n yang benar yaitu 0 <= n <= CAPACITY */
    /*    Jika n tidak valid, tidak diberikan pesan kesalahan */
    /* 2. Jika 0 < n <= CAPACITY; Lakukan n kali: 
            Baca elemen mulai dari indeks 0 satu per satu diakhiri enter */
    /*    Jika n = 0; hanya terbentuk List kosong */
    int n, i, j;
    do {
        scanf("%d", &n);
    }
    while(n<0 || n>CAPACITY_STATIK);
    CreateListStatik(l);
    for (i=0; i<n; i++) {
        scanf("%d", &j);
        ELMT(*l, i) = j;
    }
}

void printListStatik(ListStatik l) {
    /* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung 
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
    /* I.S. l boleh kosong */
    /* F.S. Jika l tidak kosong: [e1,e2,...,en] */
    /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
    /* Jika List kosong : menulis [] */
    int i;
    if (isEmptyListStatik(l)) {
        printf("[]");
    }
    else {
        printf("[");
        for (i=0; i<listStatikLength(l); i++) {
            if (i==listStatikLength(l)-1) {
                printf("%d", ELMT(l,i));
            } else {
                printf("%d,", ELMT(l,i));
            }
        }
        printf("]");
    }
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika List : Penjumlahan, pengurangan, perkalian, ... *** */
ListStatik plusMinusListStatik(ListStatik l1, ListStatik l2, boolean plus) {
    /* Prekondisi : l1 dan l2 berukuran sama dan tidak kosong */
    /* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada 
        indeks yang sama dijumlahkan */
    /* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi 
        elemen l2 pada indeks yang sama */
    int i;
    if (plus) {
        for (i=0; i<listStatikLength(l1); i++) {
            ELMT(l1, i) += ELMT(l2, i);
        }
    } else {
        for (i=0; i<listStatikLength(l1); i++) {
            ELMT(l1, i) -= ELMT(l2, i);
        }
    }
    return l1;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan List: *** */
boolean isListStatikEqual(ListStatik l1, ListStatik l2) {
    /* Mengirimkan true jika l1 sama dengan l2 yaitu jika ukuran l1 = l2 dan semua 
   elemennya sama */
    if (listStatikLength(l1) != listStatikLength(l2)) {
        return false;
    } else {
        int i;
        for (i=0; i<listStatikLength(l1); i++) {
            if (ELMT(l1,i) != ELMT(l2,i)) {
                return false;
            }
        }
    }
    return true;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOfListStatik(ListStatik l, ElType val) {
    /* Search apakah ada elemen List l yang bernilai val */
    /* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
    /* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
    /* Skema Searching yang digunakan bebas */
    if (isEmptyListStatik(l)) {
        return IDX_UNDEF_STATIK;
    } else {
        int i;
        for (i=IDX_MIN_STATIK; i<listStatikLength(l); i++) {
            if (ELMT(l,i) == val) {
                return i;
            }
        }
        return IDX_UNDEF_STATIK;
    }
}

/* ********** NILAI EKSTREM ********** */
void extremeValuesListStatik(ListStatik l, ElType *max, ElType *min) {
    /* I.S. List l tidak kosong */
    /* F.S. Max berisi nilai terbesar dalam l;
            Min berisi nilai terkecil dalam l */
    int maximum = ELMT(l, getFirstIdxListStatik(l));
    int minimum = ELMT(l, getFirstIdxListStatik(l));
    int i;
    if (listStatikLength(l) > 1) {
        for (i=1; i<listStatikLength(l); i++) {
            if (maximum < ELMT(l,i)) {
                maximum = ELMT(l,i);
            }
            if (minimum > ELMT(l,i)) {
                minimum = ELMT(l,i);
            }
        }
    }
    *max = maximum;
    *min = minimum;
}

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void insertFirstListStatik(ListStatik *l, ElType val) {
    /* Proses: Menambahkan val sebagai elemen pertama List */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen pertama l yang baru */
    /* *** Menambahkan elemen pada index tertentu *** */
    int i;
    for (i=listStatikLength(*l)-1; i>=0; i--){
        ELMT(*l, i + 1) = ELMT(*l, i);
    }
    ELMT(*l, 0) = val;
}

void insertAtListStatik(ListStatik *l, ElType val, IdxType idx) {
    /* Proses: Menambahkan val sebagai elemen pada index idx List */
    /* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l */
    /* F.S. val adalah elemen yang disisipkan pada index idx l */
    int i;
    for (i = listStatikLength(*l) - 1; i>=idx; i--){
        ELMT(*l, i + 1) = ELMT(*l, i);
    }
    ELMT(*l, idx) = val;
}

/* *** Menambahkan elemen terakhir *** */
void insertLastListStatik(ListStatik *l, ElType val) {
    /* Proses: Menambahkan val sebagai elemen terakhir List */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen terakhir l yang baru */
    ELMT(*l, listStatikLength(*l)) = val;
}

/* ********** MENGHAPUS ELEMEN ********** */
/* *** Menghapus elemen pertama *** */
void deleteFirstListStatik(ListStatik *l, ElType *val) {
    /* Proses : Menghapus elemen pertama List */
    /* I.S. List tidak kosong */
    /* F.S. val adalah nilai elemen pertama l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    int i;
    *val = ELMT(*l, 0);
    for (i=0; i<listStatikLength(*l)-1; i++) {
        ELMT(*l, i) = ELMT(*l, i+1);
    }
    ELMT(*l, getLastIdxListStatik(*l)) = MARK_STATIK;
}

/* *** Menghapus elemen pada index tertentu *** */
void deleteAtListStatik(ListStatik *l, ElType *val, IdxType idx) {
    /* Proses : Menghapus elemen pada index idx List */
    /* I.S. List tidak kosong, idx adalah index yang valid di l */
    /* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    int i;
    *val = ELMT(*l, idx);
    for (i=idx; i<listStatikLength(*l)-1; i++) {
        ELMT(*l, i) = ELMT(*l, i+1);
    }
    ELMT(*l,getLastIdxListStatik(*l)) = MARK_STATIK;
}

/* *** Menghapus elemen terakhir *** */
void deleteLastListStatik(ListStatik *l, ElType *val) {
    /* Proses : Menghapus elemen terakhir List */
    /* I.S. List tidak kosong */
    /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    *val = ELMT(*l,getLastIdxListStatik(*l));
    ELMT(*l, getLastIdxListStatik(*l)) = MARK_STATIK;
}

/* ********** SORTING ********** */
void sortListStatik(ListStatik *l, boolean asc) {
    /* I.S. l boleh kosong */
    /* F.S. Jika asc = true, l terurut membesar */
    /*      Jika asc = false, l terurut mengecil */
    /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
    algoritma bebas */
    int temp;
    int i, j;
    if (asc) {
        for (i=0; i<listStatikLength(*l); i++) {
            for (j=0; j<listStatikLength(*l)-1; j++) {
                if (ELMT(*l, j)>ELMT(*l, j+1)) {
                    temp = ELMT(*l, j);
                    ELMT(*l, j) = ELMT(*l, j+1);
                    ELMT(*l, j+1) = temp;
                }
            }
        }
    } else {
        for (i=0; i<listStatikLength(*l); i++) {
            for (j=0; j<listStatikLength(*l)-1; j++) {
                if (ELMT(*l, j)<ELMT(*l, j+1)) {
                    temp = ELMT(*l, j);
                    ELMT(*l, j) = ELMT(*l, j+1);
                    ELMT(*l, j+1) = temp;
                }
            }
        }
    }
}