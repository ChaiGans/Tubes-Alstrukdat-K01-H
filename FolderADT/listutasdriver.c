#include <stdio.h>
#include "listkicau.h"
#include "listutas.h"
#include "listpengguna.h"

int main()
{
    ListPengguna p;
    CreateListPengguna(&p);

    ListKicau l;
    CreateListKicau(&l, 3);
    Kicauan k1;
    k1.authorID = 1;
    k1.id = 1;
    k1.text[200] = "halo";
    insertLastListKicau(&l, k1);

    KicauanSambungan s;
    s.idAuthor = 1;
    s.indexKicauanSambungan = 1;
    s.text[200] = "tes";

    AddressListUtas u;
    CreateListUtas(&u);

    // Test isEmptyUtas
    printf("Apakah listUtas kosong? %d\n", isEmptyListUtas(u));
    // Test isEmptyKicauanSambungan
    printf("Apakah listutas penuh? %d\n", isEmptyKicauanSambungan(u->utas));

    // Test masukan
    insertLastListUtas(&u, 1);
    insertLastKicauanSambungan(&(u->utas), s);

    // Test jumlah utas
    printf("Jumlah utas? %d\n", ListUtaslength(u));
    // Test jumlah kicauan sambungan
    printf("Jumlah kicauan sambungan termasuk kicauan utama? %d\n", utasLength(u->utas));

    // Test menampilkan
    displayUtas(1, 1, &u, p);

    // Test delete
    KicauanSambungan temp;
    deleteAtKicauanSambungan(&u, 0, &temp);

    return 0;
}