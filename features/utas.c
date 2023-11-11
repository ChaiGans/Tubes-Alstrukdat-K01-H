#include <stdio.h>
#include "utas.h"

void buatUtas(int idKicau, int currentUserID, AddressListUtas *listUtas, ListKicau listKicau)
{
    if (!isIdKicauDefined(idKicau, listKicau)) // kicau tidak ada
    {
        printf("Kicauan tidak ditemukan!\n");
    }
    else
    {
        if ((listKicau).buffer[idKicau - 1].authorID == currentUserID) // kicaunya milik currentUser
        {
            if (!isIdUtasDefined(idKicau, listUtas)) // belum dibuat utas
            {
                insertLastListUtas(listUtas, idKicau);
                AddressListUtas s = *listUtas;
                while (s->idKicau != idKicau) // cari utas dengan idKicau
                {
                    s = NEXT(s); // address listutas
                }
                AddressUtas p = s->utas; // address utas
                printf("Utas berhasil dibuat!\n");
                Word masukanIsi;
                KicauanSambungan temp;
                temp.idAuthor = currentUserID; // kicauan utama
                temp.indexKicauanSambungan = 0;
                transferStringToString((listKicau).buffer[idKicau - 1].text, temp.text);
                getLocalTime(&temp.localtime);
                insertFirstKicauanSambungan(&p, temp);
                s->utas = p;

                Word masukanKicauanSambungan;
                Word masukanKonfirmasi;
                char konfirmasi[6];
                do // kicauan sambungan minimal sekali
                {
                    printf("Masukkan kicauan:\n");
                    masukanKicauanSambungan = ReadWord();
                    transferWordToString(temp.text, masukanKicauanSambungan);
                    temp.idAuthor = currentUserID;
                    temp.indexKicauanSambungan = utasLength(p);
                    getLocalTime(&temp.localtime);
                    insertLastKicauanSambungan(&p, temp);
                    printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK)\n");
                    masukanKonfirmasi = ReadWord();
                    transferWordToString(konfirmasi, masukanKonfirmasi);
                } while (!stringStringCompare(konfirmasi, "TIDAK"));
                printf("Utas selesai!\n");
            }
            else
            {
                printf("Kicauan sudah menjadi utas!\n");
            }
        }
        else
        {
            printf("Utas ini bukan milik anda!\n");
        }
    }
}

void sambungUtas(int idUtas, int index, int currentUserID, AddressListUtas *listUtas, ListKicau listKicau)
{
    if (idUtas > ListUtaslength(*listUtas)) // belum dibuat utas
    {
        printf("Utas tidak ditemukan!\n");
    }
    else
    {
        int i = 1; // idUtas dimulai dari idUtas 1
        AddressListUtas s = *listUtas;
        while (i != idUtas) // cari utas dengan idUtas
        {
            s = NEXT(s); // address listutas
            i += 1;
        }
        AddressUtas p = s->utas;
        s->utas = p;
        KicauanSambungan temp;
        Word masukanKicauanSambungan;
        if ((listKicau).buffer[s->idKicau - 1].authorID != currentUserID) // kicaunya bukan milik currentUser
        {
            printf("Anda tidak bisa menyambung utas ini!\n");
        }
        else if (index > utasLength(p)) // indeks terlalu tinggi
        {
            printf("Index terlalu tinggi!\n");
        }
        else // memenuhi semua kondisi
        {
            printf("Masukkan kicauan:\n");
            masukanKicauanSambungan = ReadWord();
            transferWordToString(temp.text, masukanKicauanSambungan);
            temp.indexKicauanSambungan = utasLength(p);
            temp.idAuthor = currentUserID;
            getLocalTime(&temp.localtime);
            insertLastKicauanSambungan(&p, temp);
        }
    }
}

void hapusUtas(int idUtas, int index, int currentUserID, AddressListUtas *listUtas, ListKicau listKicau)
{
    if (idUtas > ListUtaslength(*listUtas)) // utas tidak ada
    {
        printf("Utas tidak ditemukan!\n");
    }
    else
    {
        int i = 1; // idUtas mulai dari 1
        AddressListUtas s = *listUtas;
        while (i != idUtas) // cari utas dengan idUtas
        {
            s = NEXT(s); // address listutas
            i += 1;
        }
        AddressUtas p = s->utas;                                          // address utas
        if ((listKicau).buffer[s->idKicau - 1].authorID != currentUserID) // kicaunya bukan milik currentUser
        {
            // cek utas milik dia atau tidak
            printf("Anda tidak bisa menghapus kicauan dalam utas ini!\n");
        }
        else if (index == 0)
        {
            // cek indeks kicauan utama atau tidak
            printf("Anda tidak bisa menghapus kicauan utama!\n");
        }
        else if (index >= utasLength(p)) // indeks lebih besar dari seharusnya
        {
            // cek indeks kicauan sambungan ada atau tidak
            printf("Kicauan sambungan dengan index %d tidak ditemukan pada utas!\n", index);
        }
        else // memenuhi semua kondisi
        {
            KicauanSambungan temp;
            deleteAtKicauanSambungan(&p, index, &temp);
            printf("Kicauan sambungan berhasil dihapus!\n");
        }
    }
}

void cetakUtas(int idUtas, int currentUserID, AddressListUtas *listUtas, ListPengguna listPengguna, ListKicau listKicau, GrafPertemanan grafPertemanan)
{
    if (idUtas > ListUtaslength(*listUtas))
    {
        printf("Utas tidak ditemukan!\n");
    }
    else
    {
        int i = 1; // idUtas mulai dari 1
        AddressListUtas s = *listUtas;
        while (i != idUtas) // cari utas dengan idUtas
        {
            s = NEXT(s); // address listutas
            i += 1;
        }
        AddressUtas p = s->utas; // address utas
        s->utas = p;
        if (!isAuthorAccountPublic((listKicau).buffer[s->idKicau - 1].authorID, listPengguna) && !isTeman(grafPertemanan, (listKicau).buffer[s->idKicau - 1].authorID, currentUserID))
        {
            // cek privat atau tidak dan berteman atau tidak
            printf("Akun yang membuat utas ini adalah akun privat! Ikuti dahulu akun ini untuk melihat utasnya!\n");
        }
        else
        {
            printf("|   ID = %d\n", s->idKicau);
            printf("|   ");
            displayNameFromID(p->info.idAuthor, listPengguna);
            printf("\n");
            printf("|   ");
            displayDATETIME(p->info.localtime);
            printf("\n");
            printf("|   ");
            displayArrayOfChar(p->info.text);
            printf("\n");
            printf("\n");
            for (int i = 1; i < utasLength(p) + 1; i++)
            {
                p = NEXT(p); // dari kicauan index 1 (bukan kicauan utama)
                printf("    |   INDEX = %d\n", i);
                printf("    |   ");
                displayNameFromID(p->info.idAuthor, listPengguna);
                printf("\n");
                printf("    |   ");
                displayDATETIME(p->info.localtime);
                printf("\n");
                printf("    |   ");
                displayArrayOfChar(p->info.text);
                printf("\n");
                printf("\n");
            }
        }
    }
}