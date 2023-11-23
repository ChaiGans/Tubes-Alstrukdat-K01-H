#include <stdio.h>
#include "listkicau.h"
#include "listutas.h"
#include "listpengguna.h"

int main()
{
    ListPengguna p;
    CreateListPengguna(&p);
    p.contents[0].index = 1;
    char *username = "Tuan Hak";
    int i = 0;
    while (username[i] != '\0')
    {
        p.contents[0].username[i] = username[i];
        i++;
    }
    p.contents[0].username[i] = '\0';

    ListKicau l;
    CreateListKicau(&l, 3);
    Kicauan k1;
    k1.authorID = 1;
    k1.id = 1;
    k1.localtime.DD = 17;
    k1.localtime.MM = 8;
    k1.localtime.YYYY = 1945;
    k1.localtime.T.HH = 10;
    k1.localtime.T.MM = 10;
    k1.localtime.T.SS = 10;
    char *halo = "halo halo bandung";
    i = 0;
    while (halo[i] != '\0')
    {
        k1.text[i] = halo[i];
        i++;
    }
    k1.text[i] = '\0';
    insertLastListKicau(&l, k1);

    KicauanSambungan kicauanUtama;
    kicauanUtama.idAuthor = k1.authorID;
    kicauanUtama.indexKicauanSambungan = 0; // awal
    kicauanUtama.localtime = k1.localtime;
    i = 0;
    while (k1.text[i] != '\0')
    {
        kicauanUtama.text[i] = k1.text[i];
        i++;
    }

    KicauanSambungan s;
    s.idAuthor = 1;
    s.indexKicauanSambungan = 1;
    s.localtime.DD = 17;
    s.localtime.MM = 8;
    s.localtime.YYYY = 1945;
    s.localtime.T.HH = 10;
    s.localtime.T.MM = 10;
    s.localtime.T.SS = 10;
    char *halo2 = "halo halo bandung";
    i = 0;
    while (halo2[i] != '\0')
    {
        s.text[i] = halo2[i];
        i++;
    }
    s.text[i] = '\0';

    AddressListUtas m;
    CreateListUtas(&m);

    // Sebelum dimasukkan
    printf("Sebelum ada masukan!\n");
    // Test isEmptyUtas
    printf("Apakah listUtas kosong? %d\n", isEmptyListUtas(m));
    // Test jumlah utas
    printf("Jumlah utas? %d\n", ListUtaslength(m));
    printf("\n");

    // Test masukan
    insertLastListUtas(&m, 1);
    AddressListUtas u = m; // salin
    insertLastKicauanSambungan(&(m->utas), kicauanUtama);

    printf("Setelah memasukkan kicauan utama!\n");
    // Test isEmptyUtas
    printf("Apakah listUtas kosong? %d\n", isEmptyListUtas(m));
    // Test isEmptyKicauanSambungan
    printf("Apakah kicauan sambungan kosong? %d\n", isEmptyKicauanSambungan(m->utas));

    // Test jumlah utas
    printf("Jumlah utas? %d\n", ListUtaslength(m));
    // Test jumlah kicauan sambungan
    printf("Jumlah kicauan sambungan termasuk kicauan utama? %d\n", utasLength(m->utas));

    // Test menampilkan
    i = 1;
    int idUtas = s.indexKicauanSambungan;
    while (i != idUtas) // cari utas dengan idUtas
    {
        u = NEXT(u); // address listutas
        i += 1;
    }
    AddressUtas temp = u->utas; // address utas
    AddressUtas copy = temp;    // duplicate address utas untuk traversing
    printf("|   ID = %d\n", u->idKicau);
    printf("|   ");
    i = 0;
    while (p.contents[i].index != k1.authorID)
    {
        i += 1;
    }
    int indeks = i;
    printf("%s\n", p.contents[i].username);
    printf("|   ");
    printf("%2d/%2d/%4d %2d/%2d/%2d\n", copy->info.localtime.DD, copy->info.localtime.MM, copy->info.localtime.YYYY, copy->info.localtime.T.HH, copy->info.localtime.T.MM, copy->info.localtime.T.SS);
    printf("|   ");
    int j = 0;
    while (copy->info.text[j] != '\0')
    {
        printf("%c", copy->info.text[j]);
        j++;
    }
    printf("\n");
    for (int i = 1; i < utasLength(temp); i++)
    {
        copy = copy->next; // dimulai dari kicauan sambungan pertama bukan kicauan utama
        printf("    |   INDEX = %d\n", i);
        printf("    |   ");
        printf("%s\n", p.contents[indeks].username);
        printf("    |   ");
        printf("%2d/%2d/%4d %2d/%2d/%2d\n", copy->info.localtime.DD, copy->info.localtime.MM, copy->info.localtime.YYYY, copy->info.localtime.T.HH, copy->info.localtime.T.MM, copy->info.localtime.T.SS);
        printf("    |   ");
        int j = 0;
        while (copy->info.text[j] != '\0')
        {
            printf("%c", copy->info.text[j]);
            j++;
        }
        printf("\n");
    }
    printf("\n");

    printf("Setelah memasukkan kicauan sambungan pertama!\n");
    insertLastKicauanSambungan(&(m->utas), s);
    u = m;
    // Test isEmptyUtas
    printf("Apakah listUtas kosong? %d\n", isEmptyListUtas(m));
    // Test isEmptyKicauanSambungan
    printf("Apakah kicauan sambungan kosong? %d\n", isEmptyKicauanSambungan(m->utas));

    // Test jumlah utas
    printf("Jumlah utas? %d\n", ListUtaslength(m));
    // Test jumlah kicauan sambungan
    printf("Jumlah kicauan sambungan termasuk kicauan utama? %d\n", utasLength(m->utas));

    // Test menampilkan
    i = 1;
    idUtas = s.indexKicauanSambungan;
    while (i != idUtas) // cari utas dengan idUtas
    {
        u = NEXT(u); // address listutas
        i += 1;
    }
    temp = u->utas; // address utas
    copy = temp;    // duplicate address utas untuk traversing
    printf("|   ID = %d\n", u->idKicau);
    printf("|   ");
    i = 0;
    while (p.contents[i].index != k1.authorID)
    {
        i += 1;
    }
    indeks = i;
    printf("%s\n", p.contents[i].username);
    printf("|   ");
    printf("%2d/%2d/%4d %2d/%2d/%2d\n", copy->info.localtime.DD, copy->info.localtime.MM, copy->info.localtime.YYYY, copy->info.localtime.T.HH, copy->info.localtime.T.MM, copy->info.localtime.T.SS);
    printf("|   ");
    j = 0;
    while (copy->info.text[j] != '\0')
    {
        printf("%c", copy->info.text[j]);
        j++;
    }
    printf("\n");
    for (int i = 1; i < utasLength(temp); i++)
    {
        copy = copy->next; // dimulai dari kicauan sambungan pertama bukan kicauan utama
        printf("    |   INDEX = %d\n", i);
        printf("    |   ");
        printf("%s\n", p.contents[indeks].username);
        printf("    |   ");
        printf("%2d/%2d/%4d %2d/%2d/%2d\n", copy->info.localtime.DD, copy->info.localtime.MM, copy->info.localtime.YYYY, copy->info.localtime.T.HH, copy->info.localtime.T.MM, copy->info.localtime.T.SS);
        printf("    |   ");
        int j = 0;
        while (copy->info.text[j] != '\0')
        {
            printf("%c", copy->info.text[j]);
            j++;
        }
        printf("\n");
    }
    printf("\n");

    // Test delete
    printf("Setelah delete!\n");
    KicauanSambungan asal;
    deleteAtKicauanSambungan(&temp, 1, &asal);
    u = m;
    // Test isEmptyUtas
    printf("Apakah listUtas kosong? %d\n", isEmptyListUtas(m));
    // Test isEmptyKicauanSambungan
    printf("Apakah kicauan sambungan kosong? %d\n", isEmptyKicauanSambungan(m->utas));

    // Test jumlah utas
    printf("Jumlah utas? %d\n", ListUtaslength(m));
    // Test jumlah kicauan sambungan
    printf("Jumlah kicauan sambungan termasuk kicauan utama? %d\n", utasLength(m->utas));

    i = 1;
    idUtas = s.indexKicauanSambungan;
    while (i != idUtas) // cari utas dengan idUtas
    {
        u = NEXT(u); // address listutas
        i += 1;
    }
    temp = u->utas; // address utas
    copy = temp;    // duplicate address utas untuk traversing
    printf("|   ID = %d\n", u->idKicau);
    printf("|   ");
    i = 0;
    while (p.contents[i].index != k1.authorID)
    {
        i += 1;
    }
    indeks = i;
    printf("%s\n", p.contents[i].username);
    printf("|   ");
    printf("%2d/%2d/%4d %2d/%2d/%2d\n", copy->info.localtime.DD, copy->info.localtime.MM, copy->info.localtime.YYYY, copy->info.localtime.T.HH, copy->info.localtime.T.MM, copy->info.localtime.T.SS);
    printf("|   ");
    j = 0;
    while (copy->info.text[j] != '\0')
    {
        printf("%c", copy->info.text[j]);
        j++;
    }
    printf("\n");
    for (int i = 1; i < utasLength(temp); i++)
    {
        copy = copy->next; // dimulai dari kicauan sambungan pertama bukan kicauan utama
        printf("    |   INDEX = %d\n", i);
        printf("    |   ");
        printf("%s\n", p.contents[indeks].username);
        printf("    |   ");
        printf("%2d/%2d/%4d %2d/%2d/%2d\n", copy->info.localtime.DD, copy->info.localtime.MM, copy->info.localtime.YYYY, copy->info.localtime.T.HH, copy->info.localtime.T.MM, copy->info.localtime.T.SS);
        printf("    |   ");
        int j = 0;
        while (copy->info.text[j] != '\0')
        {
            printf("%c", copy->info.text[j]);
            j++;
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}