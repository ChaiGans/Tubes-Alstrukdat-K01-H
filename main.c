#include "FolderADT/charmachine.h"
#include "FolderADT/wordmachine.h"
#include "FolderADT/data.h"
#include "features/user.h"
#include <stdio.h>

Word userInput;

void printASCIIART() {
    printf("      _                     _            \n");
    printf("     | |___      _____  ___| |_ ___ _ __ \n");
    printf("     | __\\ \\ /\\ / / _ \\/ _ \\ __/ _ \\ '__|\n");
    printf("     | |_ \\ V  V /  __/  __/ ||  __/ |   \n");
    printf("      \\__| \\_/\\_/ \\___|\\___|\\__\\___|_|   \n");
    printf("                                         \n");
}

int main() {
    printASCIIART();
    printf("Selamat datang di tweeter.\n");

    Word fileName;
    int currentLoginID = -1;
    ListPengguna listPengguna;
    CreateListPengguna(&listPengguna);
    ListKicau listKicau;
    CreateListKicau(&listKicau, 10);

    printf("Masukkan nama file config: ");
    ReadWord();
    fileName = currentWord;

    initReadConfig(fileName, &listPengguna, &listKicau);

    while (true) {
        printf("\n>> ");
        Word command = ReadWord();

        if (currentLoginID == -1) {
            if (wordStringCompare(command, "MASUK")) {
                masukPengguna(&currentLoginID, listPengguna);
                displayNameFromID(currentLoginID, listPengguna);
            } else {
                printf("Silakan masuk terlebih dahulu.\n");
            }
        } else {
            if (wordStringCompare(command, "DAFTAR")) {
                daftarPengguna(&listPengguna);
            } else if (wordStringCompare(command, "UBAH_FOTO_PROFIL")) {
                ubahFotoProfil(&listPengguna.contents[currentLoginID]);
            } else if (wordStringCompare(command, "ATUR_JENIS_AKUN")) {
                aturJenisAkun(&listPengguna.contents[currentLoginID]);
            } else if (wordStringCompare(command, "GANTI_PROFIL")) {
                gantiProfil(&listPengguna.contents[currentLoginID]);
            } else if (wordStringCompare(command, "KELUAR")) {
                currentLoginID = -1;
                printf("Anda berhasil logout. Sampai jumpa di pertemuan berikutnya!\n");
            } else if (wordStringCompare(command, "TUTUP_PROGRAM")) {
                break;
            }
        }
    }
}
