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
                char isi[280]; Word masukanIsi;
                masukanIsi = ReadWord();
                transferWordToString(isi,masukanIsi);
                if (stringStringCompare(isi,(*listKicau).buffer[idKicau].text)) // melihat apakah tulisan manual sama dengan kicauan, tidak handle kalau beda
                {
                    KicauanSambungan temp;
                    temp.idAuthor = currentUserID; // kicauan utama
                    transferWordToString(temp.text,masukanIsi);
                    temp.indexKicauanSambungan = 0;
                    getLocalTime(&temp.localtime);
                    insertLastKicauanSambungan(&p,temp);
                    printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK)\n");
                    char konfirmasi[5]; Word masukanKonfirmasi;
                    masukanKonfirmasi = ReadWord();
                    transferWordToString(konfirmasi,masukanKonfirmasi);
                    while (konfirmasi != "TIDAK") // kicauan sambungan
                    {
                        Word masukanKicauanSambungan;
                        printf("Masukkan kicauan:\n");
                        masukanKicauanSambungan = ReadWord();
                        transferWordToString(temp.text,masukanKicauanSambungan);
                        temp.idAuthor = currentUserID;
                        temp.indexKicauanSambungan = KicauanSambunganLength(p);
                        getLocalTime(&temp.localtime);
                        insertLastKicauanSambungan(&p,temp);
                        printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK)\n");
                        masukanKonfirmasi = ReadWord();
                        transferWordToString(konfirmasi,masukanKonfirmasi);
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

void sambungUtas (int idUtas, int index, int currentUserID, AddressListUtas *listUtas, ListPengguna listPengguna, ListKicau *listKicau)
{
    if (idUtas >= ListUtaslength(*listUtas)) // belum dibuat utas
    {
        printf("Utas tidak ditemukan!\n");
    }
    else
    {
        int i = 0;
        AddressListUtas p = *listUtas;
        while (i != idUtas) // cari utas dengan idKicau
        {
            p = NEXT(p); // address utas
            i += 1;
        }
        if (p->utas->info.idAuthor != currentUserID) // kicaunya bukan milik currentUser
        {
            printf("Anda tidak bisa menyambung utas ini!\n");
        }
        else if (index > KicauanSambunganLength(p)) // indeks terlalu tinggi
        {
            printf("Index terlalu tinggi!\n");
        }
        else // memenuhi semua kondisi
        {
            KicauanSambungan temp; Word masukanKicauanSambungan;
            printf("Masukkan kicauan:\n");
            masukanKicauanSambungan = ReadWord();
            transferWordToString(temp.text,masukanKicauanSambungan);
            temp.idAuthor = currentUserID;
            temp.indexKicauanSambungan = KicauanSambunganLength(p);
            getLocalTime(&temp.localtime);
            insertLastKicauanSambungan(&p,temp);    
        }
    }
}

void hapusUtas (int idUtas, int index , int currentUserID, AddressListUtas *listUtas, ListPengguna listPengguna, ListKicau *listKicau)
{
    if (idUtas >= ListUtaslength(*listUtas)) // utas tidak ada
    {
        printf("Utas tidak ditemukan!\n");
    }
    else
    {
        int i = 0;
        AddressListUtas p = *listUtas;
        while (i != idUtas) // cari utas dengan idKicau
        {
            p = NEXT(p); // address utas
            i += 1;
        }
        if (p->utas->info.idAuthor != currentUserID) // kicaunya bukan milik currentUser
        {
            // cek utas milik dia atau tidak
            printf("Anda tidak bisa menghapus kicauan dalam utas ini!\n");
        }
        else if (index >= KicauanSambunganLength(p)) // indeks lebih besar dari seharusnya
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

void cetakUtas (int idUtas, int currentUserID, AddressListUtas *listUtas, ListPengguna listPengguna)
{
    if (idUtas >= ListUtaslength(*listUtas))
    {
        printf("Utas tidak ditemukan!\n");
    }
    else
    {
        int i = 0;
        AddressListUtas p = *listUtas;
        while (i != idUtas) // cari utas dengan idKicau
        {
            p = NEXT(p); // address utas
            i += 1;
        }
        if (!isAuthorAccountPublic(p->utas->info.idAuthor,listPengguna))
        {
            // cek privat atau tidak dan berteman atau tidak
            printf("Akun yang membuat utas ini adalah akun privat! Ikuti dahulu akun ini untuk melihat utasnya!\n");
        }
        else
        {
            printf("|   ID = %d\n",p->idKicau);
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
}