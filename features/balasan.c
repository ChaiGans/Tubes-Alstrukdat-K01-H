#include <stdio.h>
#include "balasan.h"

void buatBalasan (int IDkicau, int IDbalasan, int currentLoginID, ListKicau* listkicau, ListPengguna listpengguna, GrafPertemanan G) {
    if (!isIdKicauDefined(IDkicau, *listkicau)) {
        printf("Wah, tidak terdapat kicauan yang ingin Anda balas!\n");
    } else {
        Word masukanBalasan;
        int highestIDBalasan;
        Balasan balasanBaru;
        if (IDbalasan == -1) {
            printf("Masukkan balasan:\n");
            masukanBalasan = ReadWord();
            transferWordToString(balasanBaru.text, masukanBalasan);
            balasanBaru.authorID = currentLoginID;
            getLocalTime(&balasanBaru.time);
            if (isBalasanKosong(listkicau->buffer[IDkicau-1].balasan)) {
                balasanBaru.id = 1;
                listkicau->buffer[IDkicau-1].balasan = newTreeNode(balasanBaru);
            } else {
                highestIDBalasan = findHighestID(listkicau->buffer[IDkicau-1].balasan);
                balasanBaru.id = highestIDBalasan + 1;
                addSiblingAt(&listkicau->buffer[IDkicau-1].balasan, balasanBaru);
                // printf("%d\n", balasanBaru.id);
                // printf("%d\n", listkicau->buffer[IDkicau-1].balasan->info.id);
                // printf("%s\n", listkicau->buffer[IDkicau-1].balasan->info.text);
                // displayDATETIME(listkicau->buffer[IDkicau-1].balasan->info.time);
                // displayNameFromID(listkicau->buffer[IDkicau-1].balasan->info.authorID, listpengguna);
            }
            putchar('\n');
            printf("Selamat! balasan telah diterbitkan!\n");
            printf("Detil balasan:\n");
            printf("| ID = %d\n", balasanBaru.id);
            printf("| ");
            displayNameFromID(currentLoginID, listpengguna);
            putchar('\n');
            printf("| ");
            displayDATETIME(balasanBaru.time);
            putchar('\n');
            printf("| ");
            displayArrayOfChar(balasanBaru.text);
            putchar('\n');
        } else {
            if (!isIdBalasanDefined(IDbalasan, listkicau->buffer[IDkicau-1].balasan)) {
                    printf("Wah, tidak terdapat balasan yang ingin Anda balas!\n");
            } else {
                if (!isAuthorAccountPublic(((*listkicau).buffer[IDkicau-1].authorID), listpengguna) && !isTeman(G, currentLoginID, (*listkicau).buffer[IDkicau-1].authorID)) {
                    printf("Wah, akun tersebut merupakan akun privat dan anda belum berteman akun tersebut!\n");
                } else {
                    highestIDBalasan = findHighestID(listkicau->buffer[IDkicau-1].balasan);
                    printf("Masukkan balasan:\n");
                    masukanBalasan = ReadWord();
                    transferWordToString(balasanBaru.text, masukanBalasan);
                    balasanBaru.id = highestIDBalasan + 1;
                    balasanBaru.authorID = currentLoginID;
                    getLocalTime(&balasanBaru.time);
                    addChildrenAt(IDbalasan, &listkicau->buffer[IDkicau-1].balasan, balasanBaru);
                    putchar('\n');
                    printf("Selamat! balasan telah diterbitkan!\n");
                    printf("Detil balasan:\n");
                    printf("| ID = %d\n", balasanBaru.id);
                    printf("| ");
                    displayNameFromID(currentLoginID, listpengguna);
                    putchar('\n');
                    printf("| ");
                    displayDATETIME(balasanBaru.time);
                    putchar('\n');
                    printf("| ");
                    displayArrayOfChar(balasanBaru.text);
                    putchar('\n');
                }
            }
        }
    }
}

void lihatBalasan (int currentLoginID, int idKicau, ListKicau listkicau, ListPengguna listpengguna, GrafPertemanan G) {
    if (!isIdKicauDefined(idKicau, listkicau)) {
        printf("Tidak terdapat kicauan dengan id tersebut!\n");
    } else if (listkicau.buffer[idKicau-1].balasan == NULL) {
        printf("Belum terdapat balasan apapun pada kicauan tersebut. Yuk balas kicauan tersebut!\n");
    } else {
        if (!isAuthorAccountPublic(listkicau.buffer[idKicau-1].authorID, listpengguna) && !isTeman(G, currentLoginID, (listkicau).buffer[idKicau-1].authorID)) {
            printf("Wah, kicauan tersebut dibuat oleh pengguna dengan akun privat!\n");
        } else {
            displayTreeOfBalasan(listkicau.buffer[idKicau-1].balasan, 4, 0, &listpengguna);
        }
    }
}

void hapusBalasan (int currentLoginID, int idKicau, int idBalasan, ListKicau* listkicau) {
    if ((*listkicau).buffer[idKicau-1].authorID != currentLoginID) {
        printf("Hei, ini balasan punya siapa? Jangan dihapus ya!\n");
    } else {
        if (!isIdBalasanDefined(idBalasan, (*listkicau).buffer[idKicau-1].balasan)){ 
            printf("Balasan tidak ditemukan.\n");
        } else {
            hapusCabangBalasan(&listkicau->buffer[idKicau-1].balasan, idBalasan);
            printf("Balasan berhasil dihapus!\n");
        }
    }
}