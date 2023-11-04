#include <stdio.h>
#include "draf.h"

void buatDraf (int currentUserID, ListKicau* listkicau, ListPengguna* listpengguna) {
    Draf drafBaru;
    Word konfirmasiAksi;
    printf("Masukkan draf:");
    Word isiDraf = ReadWord();
    getLocalTime(&drafBaru.localtime);
    transferWordToString(drafBaru.text, isiDraf);
    putchar('\n');
    do {
        printf("Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini?");
        konfirmasiAksi = ReadWord();
        if (wordStringCompare(konfirmasiAksi, "HAPUS")) {
            printf("Draf telah berhasil dihapus!\n");
        } else if (wordStringCompare(konfirmasiAksi, "SIMPAN")) {
            transferWordToString(drafBaru.text, isiDraf);
            PushStackDraf(&(*listpengguna).contents[currentUserID].stackdraf, drafBaru);
            printf("Draf telah berhasil disimpan!\n");
        } else if (wordStringCompare(konfirmasiAksi, "TERBIT")) {
            printf("Selamat! Draf kicauan telah diterbitkan!\n");
            printf("Detil kicauan:\n");
            printf("| ID = %d", listKicauLength(*listkicau)+1);
            putchar('\n');
            printf("| ");
            displayNameFromID(currentUserID, *listpengguna);
            putchar('\n');
            printf("| ");
            displayDATETIME(drafBaru.localtime);
            putchar('\n');
            printf("| ");
            displayArrayOfChar(drafBaru.text);
            putchar('\n');
            printf("| Disukai: 0");
            putchar('\n');
            Kicauan kicauanBaru;
            drafKicauToKicauan(drafBaru, &kicauanBaru);
            insertLastListKicau(listkicau, kicauanBaru);
        } 
    } while (!wordStringCompare(konfirmasiAksi, "HAPUS") && !wordStringCompare(konfirmasiAksi, "SIMPAN") && !wordStringCompare(konfirmasiAksi, "TERBIT"));
}

void lihatDraf (int currentUserID, ListKicau* listkicau, ListPengguna* listpengguna) {
    Draf lastDraf;
    boolean found;
    if (!IsEmptyStackDraf((*listpengguna).contents[currentUserID].stackdraf)) {
        PopStackDraf(&(*listpengguna).contents[currentUserID].stackdraf, &lastDraf);
        printf("Ini draf terakhir anda:\n");
        printf("| ");
        displayDATETIME(lastDraf.localtime);
        putchar('\n');
        printf("| ");
        displayArrayOfChar(lastDraf.text);
        putchar('\n');
        Word konfirmasi;
        do {
            printf("Apakah anda ingin mengubah, menghapus, atau menerbitkan draf ini? (KEMBALI jika ingin kembali)\n");
            konfirmasi = ReadWord();
            putchar('\n');
            if (wordStringCompare(konfirmasi, "HAPUS")) {
                printf("Draf telah berhasil dihapus!\n");
            } else if (wordStringCompare(konfirmasi, "UBAH")) {
                printf("Masukkan draf yang baru:\n");
                Word ubahanIsi = ReadWord();
                transferWordToString(lastDraf.text, ubahanIsi);
                getLocalTime(&lastDraf.localtime);
                PushStackDraf(&(*listpengguna).contents[currentUserID].stackdraf, lastDraf);
            } else if (wordStringCompare(konfirmasi, "TERBIT")) {
                printf("Selamat! Draf kicauan telah diterbitkan!\n");
                printf("Detil kicauan:\n");
                printf("| ID = %d", listKicauLength(*listkicau)+1);
                putchar('\n');
                printf("| ");
                displayNameFromID(currentUserID, *listpengguna);
                putchar('\n');
                printf("| ");
                getLocalTime(&lastDraf.localtime);
                displayDATETIME(lastDraf.localtime);
                putchar('\n');
                printf("| ");
                displayArrayOfChar(lastDraf.text);
                putchar('\n');
                printf("| Disukai: 0");
                putchar('\n');
                Kicauan kicauanBaru;
                drafKicauToKicauan(lastDraf, &kicauanBaru);
                insertLastListKicau(listkicau, kicauanBaru);
            } else if (wordStringCompare(konfirmasi, "KEMBALI")) {
                PushStackDraf(&(*listpengguna).contents[currentUserID].stackdraf, lastDraf); 
            }
        } while (!wordStringCompare(konfirmasi, "KEMBALI") && !wordStringCompare(konfirmasi, "TERBIT") && !wordStringCompare(konfirmasi, "UBAH") && !wordStringCompare(konfirmasi, "HAPUS"));
    } else {
        printf("Yah, anda belum memiliki draf apapun! Buat dulu ya :D\n");
    }
}