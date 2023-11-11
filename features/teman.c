#include "teman.h"

void displayDaftarTeman(int currentUserID, GrafPertemanan grafPertemanan, ListPengguna listPengguna)
{
    // cari nama pengguna dari currentUserID
    Profile currentUserProfile = listPengguna.contents[currentUserID];
    printf("\n");
    displayArrayOfChar(currentUserProfile.username);
    if (getBanyakTeman(grafPertemanan, currentUserID))
    {
        printf(" memiliki %d teman.\n", getBanyakTeman(grafPertemanan, currentUserID));
        printf("Daftar teman %s:\n", currentUserProfile.username);
        int i;
        for (i = 0; i < grafPertemanan.banyakOrang; i++)
        {
            if (isTeman(grafPertemanan, currentUserID, i))
            {
                printf("| ");
                displayNameFromID(i, listPengguna);
                printf("\n");
            }
        }
    }
    else
    {
        printf(" belum memiliki teman.\n");
    }
}

void hapusTeman(int currentUserID, GrafPertemanan *grafPertemanan, ListPengguna listPengguna)
{
    // cari nama pengguna dari currentUserID
    Profile currentUserProfile = listPengguna.contents[currentUserID];

    printf("Masukkan nama pengguna yang ingin dihapus: ");
    Word namaPenggunaYangDihapus = ReadWord();
    int idPenggunaYangDihapus = findIDFromUsername(listPengguna, namaPenggunaYangDihapus);
    if (idPenggunaYangDihapus == IDX_UNDEF_STATIK)
    {
        printf("Pengguna bernama %s tidak ditemukan.\n", namaPenggunaYangDihapus);
        return;
    }
    if (!isTeman(*grafPertemanan, currentUserID, idPenggunaYangDihapus))
    {
        printf("%s bukan teman Anda.\n", namaPenggunaYangDihapus);
        return;
    }
    else
    {
        printf("Apakah anda yakin ingin menghapus %s dari daftar teman anda? (YA/TIDAK) ", namaPenggunaYangDihapus);
        Word pilihan = ReadWord();
        if (wordStringCompare(pilihan, "TIDAK"))
        {
            printf("Penghapusan teman dibatalkan.\n");
            return;
        }
        else if (wordStringCompare(pilihan, "YA"))
        {
            hapusHubunganTeman(grafPertemanan, currentUserID, idPenggunaYangDihapus);
            printf("Pengguna %s telah dihapus dari daftar teman.\n", namaPenggunaYangDihapus);
        }
    }
}

void kirimPermintaanTeman(int currentUserID, GrafPertemanan *grafPertemanan, ListPengguna listPengguna)
{
    // periksa apakah currentUserID memiliki permintaan pertemanan yang belum disetujui
    if (getBanyakPermintaanTeman(listPengguna.contents[currentUserID].permintaanTeman) != 0)
    {
        printf("Terdapat permintaan pertemanan yang belum Anda setujui. Silakan kosongkan daftar permintaan pertemanan untuk Anda terlebih dahulu.\n");
        return;
    }

    // cari nama pengguna yang akan ditambahkan
    printf("Masukkan nama pengguna yang ingin ditambahkan sebagai teman: ");
    Word namaPenggunaYangDitambahkan = ReadWord();
    int idPenerima = findIDFromUsername(listPengguna, namaPenggunaYangDitambahkan);
    if (idPenerima == IDX_UNDEF_STATIK)
    {
        printf("Pengguna bernama %s tidak ditemukan.\n", namaPenggunaYangDitambahkan);
        return;
    }
    if (isTeman(*grafPertemanan, currentUserID, idPenerima))
    {
        printf("%s sudah menjadi teman Anda.\n", namaPenggunaYangDitambahkan);
        return;
    }
    if (isMengirimPermintaan(*grafPertemanan, currentUserID, idPenerima))
    {
        printf("Anda sudah mengirim permintaan pertemanan kepada %s.\nSilahkan tunggu hingga permintaan anda disetujui.\n", namaPenggunaYangDitambahkan);
        return;
    }
    ElmtGrafPertemanan(*grafPertemanan, currentUserID, idPenerima) = '1';
    printf("Permintaan pertemanan telah dikirimkan kepada %s.\n", namaPenggunaYangDitambahkan);
}

void displayDaftarPermintaanTeman(int currentUserID, GrafPertemanan grafPertemanan, ListPengguna listPengguna)
{
    // cari nama pengguna dari currentUserID
    Profile currentUserProfile = listPengguna.contents[currentUserID];
    PrioQueueChar Q = currentUserProfile.permintaanTeman;
    if (NBElmtQueue(Q) != 0)
    {
        printf("Terdapat %d permintaan pertemanan untuk anda.\n", NBElmtQueue(Q));
        int i;
        while (!IsEmptyQueue(Q))
        {
            // printf("%d\n", NBElmtQueue(Q));
            infotype pertmintaan;
            Dequeue(&Q, &pertmintaan);
            int idPengirim = pertmintaan.id;
            int popularitas = pertmintaan.popularity;
            printf("| ");
            displayNameFromID(idPengirim, listPengguna);
            printf("\n");
            printf("| Jumlah teman: %d\n", popularitas);
            printf("\n");
        }
    }
    else
    {
        printf("Tidak ada permintaan pertemanan untuk anda.\n");
    }
}

void terimaPermintaanTeman(int currentUserID, GrafPertemanan *grafPertemanan, ListPengguna *listPengguna)
{
    // cari nama pengguna dari currentUserID
    PrioQueueChar *Q = &listPengguna->contents[currentUserID].permintaanTeman;
    // jika tidak ada permintaan pertemanan
    if (NBElmtQueue(*Q) == 0)
    {
        printf("Tidak ada permintaan pertemanan untuk anda.\n");
        return;
    }
    // jika ada permintaan, tampilkan permintaan dari yang paling populer
    infotype permintaan;
    Dequeue(Q, &permintaan);
    int idPengirim = permintaan.id;
    int popularitas = permintaan.popularity;

    printf("Permintaan pertemanan teratas dari ");
    displayNameFromID(idPengirim, *listPengguna);
    printf("\n\n| ");
    displayNameFromID(idPengirim, *listPengguna);
    printf("\n");
    printf("| Jumlah teman: %d\n", popularitas);
    printf("\n");

    printf("Apakah Anda ingin menyetujui permintaan pertemanan ini? (YA/TIDAK) ");
    Word pilihan = ReadWord();
    if (wordStringCompare(pilihan, "TIDAK"))
    {
        printf("Permintaan pertemanan dari ");
        displayNameFromID(idPengirim, *listPengguna);
        printf(" telah ditolak.\n ");
        return;
    }
    else if (wordStringCompare(pilihan, "YA"))
    {
        addTeman(grafPertemanan, currentUserID, idPengirim);
        printf("Permintaan pertemanan dari ");
        displayNameFromID(idPengirim, *listPengguna);
        printf(" telah disetujui. Selamat! Anda telah berteman dengan ");
        displayNameFromID(idPengirim, *listPengguna);
        printf(".\n");
    }
}