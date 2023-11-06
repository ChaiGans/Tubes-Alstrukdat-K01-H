# include <stdio.h>
# include "utas.h"

void buatUtas (int idKicau, int currentUserID, AddressListUtas *listUtas, ListPengguna listPengguna, ListKicau *listKicau)
{
    if (!isIdKicauDefined(idKicau,*listKicau)) // kicau tidak ada
    {
        printf("Kicauan tidak ditemukan\n");
    }
    else
    {
        if (!isIdUtasDefined(idKicau,*listUtas)) // belum dibuat utas tapi tidak handle jika kicau sudah jadi kicauan utama
        {
            if ((*listKicau).buffer[idKicau].authorID == currentUserID) // kicaunya milik currentUser
            {
                insertLastListUtas(&listUtas,idKicau);
                AddressListUtas p = *listUtas;
                while (p->idKicau != idKicau) // cari utas dengan idKicau
                {
                    p = NEXT(p); // address utas
                }
                printf("Utas berhasil dibuat!\n");
                printf("Masukkan kicauan:\n");
                char isi[280];
                scanf("%s",&isi);
                if (stringStringCompare(isi,(*listKicau).buffer[idKicau].text)) // melihat apakah tulisan manual sama dengan kicauan, tidak handle kalau beda
                {
                    printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK)\n");
                    char konfirmasi[5];
                    scanf("%s",&konfirmasi);
                    while (konfirmasi != "TIDAK")
                    {
                        printf("Masukkan kicauan:\n");
                        KicauanSambungan temp; Word masukanKicauanSambungan;
                        temp.idAuthor = currentUserID;
                        temp.indexKicauanSambungan = KicauanSambunganLength(p);
                        getLocalTime(&temp.localtime);
                        masukanKicauanSambungan = ReadWord();
                        transferWordToString(temp.text,masukanKicauanSambungan);
                        insertLastKicauanSambungan(&p,temp);
                        scanf("%s",&konfirmasi);
                        printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK)\n");
                    }
                    printf("Utas selesai!\n");
                }
            }
            else
            {
                printf("Utas ini bukan milik anda!\n");
            }
        }
    }
}

void sambungUtas (int idKicau, int currentUserID, int index, AddressListUtas *listUtas, ListPengguna listPengguna, ListKicau *listKicau)
{
    if (!isIdUtasDefined(idKicau,*listUtas)) // belum dibuat utas
    {
        printf("Utas tidak ditemukan!\n");
    }
    else
    {
        AddressListUtas p = *listUtas;
        while (p->idKicau != idKicau) // cari utas dengan idKicau
        {
            p = NEXT(p); // address utas
        }
        if ((*listKicau).buffer[idKicau].authorID == currentUserID) // kicaunya bukan milik currentUser
        {
            printf("Anda tidak bisa menyambung utas ini!\n");
        }
        else if (index > KicauanSambunganLength(p)) // indeks terlalu tinggi
        {
            printf("Index terlalu tinggi!\n");
        }
        else // memenuhi semua kondisi
        {
            printf("Masukkan kicauan:\n");
            KicauanSambungan temp; Word masukanKicauanSambungan;
            masukanKicauanSambungan = ReadWord();
            temp.idAuthor = currentUserID;
            temp.indexKicauanSambungan = KicauanSambunganLength(p);
            getLocalTime(&temp.localtime);
            transferWordToString(temp.text,masukanKicauanSambungan);
            insertLastKicauanSambungan(&p,temp);    
        }
    }
}

void hapusUtas (int idKicau, int index , int currentUserID, AddressListUtas *listUtas, ListPengguna listPengguna, ListKicau *listKicau)
{
    if (!isIdUtasDefined(idKicau,*listUtas)) // utas tidak ada
    {
        printf("Utas tidak ditemukan!\n");
    }
    else
    {
        AddressListUtas p = *listUtas;
        while (p->idKicau != idKicau) // cari utas dengan idKicau
        {
            p = NEXT(p); // address utas
        }
        if ((*listKicau).buffer[idKicau].authorID == currentUserID) // kicaunya bukan milik currentUser
        {
            // cek utas milik dia atau tidak
            printf("Anda tidak bisa menghapus kicauan dalam utas ini!\n");
        }
        else if (index > KicauanSambunganLength(p)-1) // indeks lebih besar dari seharusnya
        {
            // cek indeks kicauan sambungan ada atau tidak
            printf("Kicauan sambungan dengan index %d tidak ditemukan pada utas!\n",index);
        }
        else if (index == 0)
        {
            // cek indeks kicauan utama atau tidak
            printf("Anda tidak bisa menghapus kicauan utama!\n");
        }
        else // memenuhi semua kondisi
        {
            KicauanSambungan temp;
            deleteAtKicauanSambungan(&p,index,&temp);
        }
    }
}

void cetakUtas (int idKicau, int currentUserID, AddressListUtas *listUtas, ListPengguna listPengguna)
{
    if (!isIdUtasDefined(idKicau,*listUtas))
    {
        printf("Utas tidak ditemukan!\n");
    }
    else
    {
        // cek privat atau tidak dan berteman atau tidak
        printf("Akun yang membuat utas ini adalah akun privat! Ikuti dahulu akun ini untuk melihat utasnya!\n");

        AddressListUtas p = *listUtas;
        while (p->idKicau != idKicau) // cari utas dengan idKicau
        {
            p = NEXT(p); // address utas
        }
        printf("|   ID = %d\n",idKicau);
        printf("|   ");
        displayNameFromID(p->utas->info.idAuthor,listPengguna);
        printf("\n");
        printf("|   ");
        displayDATETIME(p->utas->info.localtime);
        printf("\n");
        displayArrayOfChar(p->utas->info.text);
        printf("\n");
        for (int i = 1 ; i<KicauanSambunganLength(p)+1 ; i++)
        {
            p = NEXT(p);
            printf("    |   INDEX = %d\n",i);
            printf("    |   ");
            displayNameFromID(p->utas->info.idAuthor,listPengguna);
            printf("\n");
            printf("    |   ");
            displayDATETIME(p->utas->info.localtime);
            printf("\n");
            printf("    |   ");
            displayArrayOfChar(p->utas->info.text);
            printf("\n");
        }
    }
}