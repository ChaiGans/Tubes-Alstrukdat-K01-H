#include <stdio.h>
#include "balasan.h"

void buatBalasan (int IDkicau, int IDbalasan, int currentLoginID, ListKicau* listkicau, ListPengguna listpengguna) {
    if (!isIdKicauDefined(IDkicau, *listkicau)) {
        printf("Wah, tidak terdapat kicauan yang ingin Anda balas!\n");
    } else {
        Word masukanBalasan;
        int highestIDBalasan;
        Balasan balasanBaru;
        highestIDBalasan = findHighestID(listkicau->buffer[IDkicau].balasan);
        if (IDbalasan == -1) {
            printf("Masukkan balasan:\n");
            masukanBalasan = ReadWord();
            transferWordToString(balasanBaru.text, masukanBalasan);
            balasanBaru.id = 1;
            balasanBaru.authorID = currentLoginID;
            getLocalTime(&balasanBaru.time);
            listkicau->buffer[IDkicau].balasan = newTreeNode(balasanBaru);
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
        } else if (!isIdBalasanDefined(IDbalasan, listkicau->buffer[IDkicau].balasan)) {
            printf("Wah, tidak terdapat balasan yang ingin Anda balas!\n");
        } else {
            printf("Masukkan balasan:\n");
            masukanBalasan = ReadWord();
            transferWordToString(balasanBaru.text, masukanBalasan);
            balasanBaru.id = findHighestID(listkicau->buffer[IDkicau].balasan) + 1;
            balasanBaru.authorID = currentLoginID;
            getLocalTime(&balasanBaru.time);
            addChildrenAt(IDbalasan, &listkicau->buffer[IDkicau].balasan, balasanBaru);
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

void lihatBalasan (int idKicau, ListKicau listkicau, ListPengguna listpengguna) {
    if (!isIdKicauDefined(idKicau, listkicau)) {
        printf("Tidak terdapat kicauan dengan id tersebut!\n");
    } else if (listkicau.buffer[idKicau].balasan == NULL) {
        printf("Belum terdapat balasan apapun pada kicauan tersebut. Yuk balas kicauan tersebut!\n");
    } else {
        displayTreeOfBalasan(listkicau.buffer[idKicau].balasan, 4, 0, listpengguna);
    }
}