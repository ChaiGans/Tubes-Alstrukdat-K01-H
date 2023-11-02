#include <stdio.h>
#include "draf.h"

void buatDraf (StackDraf* stackDraf, int currentUserID, ListKicau* listkicau, ListPengguna listpengguna) {
    Draf drafBaru;
    Word konfirmasiAksi;
    createDraf(*stackDraf, &drafBaru, currentUserID);
    printf("Masukkan draf:");
    Word isiDraf = ReadWord();
    transferWordToString(stackDraf->T->text, isiDraf);
    putchar('\n');
    do {
        printf("Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini?");
        konfirmasiAksi = ReadWord();
        if (wordStringCompare(konfirmasiAksi, "HAPUS")) {
            printf("Draf telah berhasil dihapus!\n");
        } else if (wordStringCompare(konfirmasiAksi, "SIMPAN")) {
            transferWordToString(drafBaru.text, isiDraf);
            PushStackDraf(stackDraf, drafBaru);
            printf("Draf telah berhasil disimpan!\n");
        } else if (wordStringCompare(konfirmasiAksi, "TERBIT")) {
            printf("Selamat! Draf kicauan telah diterbitkan!\n");
            printf("Detil kicauan:\n");
            printf("| ID = %d", listKicauLength(*listkicau)+1);
            printf("| ");
            displayNameFromID(currentUserID, listpengguna);
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
    } while (!wordStringCompare(konfirmasiAksi, "HAPUS") && wordStringCompare(konfirmasiAksi, "SIMPAN") && !wordStringCompare(konfirmasiAksi, "TERBIT"));
}

void lihatDraf (StackDraf* stackDraf, int currentUserID, ListKicau* listkicau, ListPengguna listpengguna) {
    Draf lastDraf, deletedDraf;
    boolean found;
    searchLastDraf(*stackDraf, currentUserID, &lastDraf, &found);
    if (found) {
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
            PopStackDraf(stackDraf, &deletedDraf);
            if (wordStringCompare(konfirmasi, "HAPUS")) {
                printf("Draf telah berhasil dihapus!\n");
            } else if (wordStringCompare(konfirmasi, "UBAH")) {
                printf("Masukkan draf yang baru:\n");
                Word ubahanIsi = ReadWord();
                transferWordToString(deletedDraf.text, ubahanIsi);
                getLocalTime(&deletedDraf.localtime);
                PushStackDraf(stackDraf, deletedDraf);
            } else if (wordStringCompare(konfirmasi, "TERBIT")) {
                printf("Selamat! Draf kicauan telah diterbitkan!\n");
                printf("Detil kicauan:\n");
                printf("| ID = %d", listKicauLength(*listkicau)+1);
                printf("| ");
                displayNameFromID(currentUserID, listpengguna);
                putchar('\n');
                printf("| ");
                displayDATETIME(deletedDraf.localtime);
                putchar('\n');
                printf("| ");
                displayArrayOfChar(deletedDraf.text);
                putchar('\n');
                printf("| Disukai: 0");
                putchar('\n');
                Kicauan kicauanBaru;
                drafKicauToKicauan(deletedDraf, &kicauanBaru);
                insertLastListKicau(listkicau, kicauanBaru);
            } else if (wordStringCompare(konfirmasi, "KEMBALI")) {
                PushStackDraf(stackDraf, deletedDraf); 
            }
        } while (!wordStringCompare(konfirmasi, "KEMBALI") && !wordStringCompare(konfirmasi, "TERBIT") && !wordStringCompare(konfirmasi, "UBAH") && !wordStringCompare(konfirmasi, "HAPUS"));
    } else {
        printf("Yah, anda belum memiliki draf apapun! Buat dulu ya :D\n");
    }
}