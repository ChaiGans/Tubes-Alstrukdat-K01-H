#include "listkicau.h"
#include <stdio.h>
#include <stdlib.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListKicau(ListKicau *l, int capacity)
{
    (*l).capacity = capacity;
    (*l).nEff = 0;
    (*l).buffer = (ElTypeKicau *)malloc(capacity * sizeof(ElTypeKicau));
}
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */

void dealocateListKicau(ListKicau *l)
{
    (*l).capacity = 0;
    (*l).nEff = 0;
    free((*l).buffer);
}
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listKicauLength(ListKicau l)
{
    return l.nEff;
}
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */
/* *** Daya tampung container *** */

/* *** Selektor INDEKS *** */
IdxType getFirstIdxListKicau(ListKicau l)
{
    return IDX_MIN_LISTDIN;
}
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l pertama */
IdxType getLastIdxListKicau(ListKicau l)
{
    return l.nEff - 1;
}
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */

/* ********** Test Indeks yang valid ********** */
boolean isIdxValidListKicau(ListKicau l, IdxType i)
{
    return (i < l.capacity && i >= IDX_MIN_LISTDIN);
}
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean isIdxEffListKicau(ListKicau l, IdxType i)
{
    return (i < l.nEff && i >= IDX_MIN_LISTDIN);
}
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..NEFF(l) */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmptyListKicau(ListKicau l)
{
    return (l.nEff == 0);
}
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
/* *** Test list penuh *** */
boolean isFullListKicau(ListKicau l)
{
    return (l.nEff == l.capacity);
}
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOfListKicau(ListKicau l, ElTypeKicau val)
{
    // int i; for (i = 0; i < l.nEff; i++){
    //     if (ELMT_DIN(l, i) == val) return i;
    // } return IDX_UNDEF_LISTDIN;

    // note : yang ini perlu handling dulu gegara struct gabisa di equal
}
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
/* Jika tidak ada, mengirimkan IDX_UNDEF */
/* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
/* Skema Searching yang digunakan bebas */

/* ********** OPERASI LAIN ********** */
void copyListKicau(ListKicau lIn, ListKicau *lOut)
{
    CreateListKicau(&*lOut, lIn.capacity);
    int i;
    for (i = 0; i < lIn.nEff; i++)
    {
        (*lOut).buffer[i] = lIn.buffer[i];
    }
    (*lOut).nEff = lIn.nEff;
}
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLastListKicau(ListKicau *l, ElTypeKicau val)
{
    val.id = listKicauLength(*l)+1;
    (*l).buffer[(*l).nEff] = val;
    (*l).nEff++;
    if (isFullListKicau(*l))
        expandListKicau(&*l, (*l).capacity);
}
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
/* ********** MENGHAPUS ELEMEN ********** */
void deleteLastListKicau(ListKicau *l, ElTypeKicau *val)
{
    *val = (*l).buffer[(*l).nEff - 1];
    (*l).nEff--;
}
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */

/* ********* MENGUBAH UKURAN ARRAY ********* */
void expandListKicau(ListKicau *l, int num)
{
    (*l).capacity += num;
    (*l).buffer = realloc((*l).buffer, ((*l).capacity * sizeof(ElTypeKicau)));
}
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */

void shrinkListKicau(ListKicau *l, int num)
{
    (*l).capacity -= num;
    (*l).buffer = realloc((*l).buffer, ((*l).capacity * sizeof(ElTypeKicau)));
}
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */

void compressListKicau(ListKicau *l)
{
    (*l).capacity = (*l).nEff;
    (*l).buffer = realloc((*l).buffer, ((*l).capacity * sizeof(ElTypeKicau)));
}
/* Proses : Mengubah capacity sehingga capacity = nEff */
/* I.S. List tidak kosong */
/* F.S. Ukuran capacity = nEff */
void drafKicauToKicauan (Draf drafKicau, Kicauan* kicauBaru) {
    (*kicauBaru).authorID = drafKicau.authorID;
    transferStringToString(drafKicau.text, kicauBaru->text);
    (*kicauBaru).like = 0;
    (*kicauBaru).localtime = drafKicau.localtime;
    (*kicauBaru).balasan = NULL;
}

boolean isIdKicauDefined (int idSearch, ListKicau l) {
    int i;
    for (i = 0; i < listKicauLength(l); i++) {
        if (l.buffer[i].id == idSearch) {
            return true;
        }
    }
    return false;
}

char makeLowerCase(char A){
    int ascii = (int) A;
    if ((ascii >= 65)&&(ascii <= 90)) ascii+=32;
    return (char)ascii;
}

int hashTagar(char karakter[]){
    int total = 0, i = 0;
    while (karakter[i] != '\0'){
        total += ((int) makeLowerCase(karakter[i])); i++;
    } return (total % 200);
}

boolean isTagarValid(int nilaiHashtagar, DatabaseTagar databaseTagar){
    return (databaseTagar.keyAndValue[nilaiHashtagar] != NULL);
}

void createDatabaseTagar(DatabaseTagar *databaseTagar){
    int i; for(i = 0; i < 200; i++){
        (*databaseTagar).keyAndValue[i] = NULL;
    } (*databaseTagar).length = 0;
}

PointerAddressKicau newPointerKicauNode(Kicauan *kicauan){
    PointerAddressKicau new = (PointerAddressKicau) malloc(sizeof(PointerAddressKicau)+sizeof(PointerKicauan)); 
    (new)->nextKicau = NULL; 
    (new)->currKicau = kicauan;
    return (new);
}

void insertTagar(DatabaseTagar *databaseTagar, char tagar[], Kicauan *kicauan){
    int hash = hashTagar(tagar); 
    char tagarlowercase[30];
    int curLen = 0;
    while((curLen < 29)&&(tagar[curLen] != '\0')){
        tagarlowercase[curLen] = makeLowerCase(tagar[curLen]); curLen++;
    } tagarlowercase[curLen] = '\0';
    if (!isTagarValid(hash, *databaseTagar)){
        PointerMapTagar tagarbaru = (PointerMapTagar) malloc(30*sizeof(char));  
        int i = 0; while ((i < 30)&&(tagarlowercase[i] != '\0')){
            tagarbaru->Tagar[i] = tagarlowercase[i]; i++;
        } tagarbaru->Tagar[i] = '\0';
        tagarbaru->listKicauTagar = newPointerKicauNode(kicauan);
        (*databaseTagar).keyAndValue[hash] = tagarbaru;
        printf("\n\ndata tag belum ada\n\n");
        (*databaseTagar).length++;
    } else{
        int i = hash;
        while(((*databaseTagar).keyAndValue[i] != NULL) && (!stringStringCompare((*databaseTagar).keyAndValue[i]->Tagar, tagarlowercase))) i = (i + 1)%200;
        if ((*databaseTagar).keyAndValue[i] == NULL){
            PointerMapTagar tagarbaru = (PointerMapTagar) malloc(30*sizeof(char) + sizeof(PointerAddressKicau));  
            int j = 0; while ((j < 30)&&(tagarlowercase[j] != '\0')){
                tagarbaru->Tagar[j] = tagarlowercase[j]; j++;
            } tagarbaru->Tagar[j] = '\0';
            tagarbaru->listKicauTagar = newPointerKicauNode(kicauan);
            (*databaseTagar).keyAndValue[hash] = tagarbaru;
            printf("\n\ndata tag geser hash\n\n");
            (*databaseTagar).length++;
        } else{
            printf("\n\ndata tag udah ada");
            PointerAddressKicau p = (*databaseTagar).keyAndValue[i]->listKicauTagar;
            
            while(p->nextKicau != NULL){
                p = p->nextKicau;
            }
            PointerAddressKicau baru = newPointerKicauNode(kicauan);
            p->nextKicau = baru;
        }
    }
}
