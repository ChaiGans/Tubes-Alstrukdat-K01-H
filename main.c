#include "FolderADT/charmachine.h"
#include "FolderADT/wordmachine.h"
#include "FolderADT/data.h"
#include "features/user.h"
#include "features/draf.h"
#include "features/balasan.h"

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
    printf("Selamat datang di BurBir.\n");
    printf("Aplikasi untuk studi kualitatif mengenai perilaku manusia dengan menggunakan metode (pengambilan data berupa) Focused Group Discussion kedua di zamannya.\n");

    int currentLoginID = -1;
    ListPengguna listPengguna;
    CreateListPengguna(&listPengguna);
    ListKicau listKicau;
    CreateListKicau(&listKicau, 10);

    printf("Masukkan nama file config: ");
    Word filename = ReadWord();
    initReadConfig(filename, &listPengguna, &listKicau);

    while (true) {
        // printTree(listKicau.buffer[0].balasan, 2);
        printf("\n>> ");
        Word command = ReadWord();

        if (currentLoginID == -1) {
            if (wordStringCompare(command, "MASUK")) {
                masukPengguna(&currentLoginID, listPengguna);
                displayNameFromID(currentLoginID, listPengguna);
            } else if (wordStringCompare(command, "DAFTAR")) {
                daftarPengguna(&listPengguna); 
            } else {
                printf("Silakan masuk terlebih dahulu.\n");
            }
        } else {
            if (wordStringCompare(command, "UBAH_FOTO_PROFIL")) {
                ubahFotoProfil(&listPengguna.contents[currentLoginID]);
            } else if (wordStringCompare(command, "ATUR_JENIS_AKUN")) {
                aturJenisAkun(&listPengguna.contents[currentLoginID]);
            } else if (wordStringCompare(command, "GANTI_PROFIL")) {
                gantiProfil(&listPengguna.contents[currentLoginID]);
            } else if (wordStringCompare(command, "BUAT_DRAF")) {
                buatDraf(currentLoginID, &listKicau, &listPengguna);
            } else if (wordStringCompare(command, "LIHAT_DRAF")) {
                lihatDraf(currentLoginID, &listKicau, &listPengguna);
            } else if (wordStringCompare(command, "KELUAR")) {
                currentLoginID = -1;
                printf("Anda berhasil logout. Sampai jumpa di pertemuan berikutnya!\n");
            } else if (wordStringCompare(command, "TUTUP_PROGRAM")) {
                break;
            }
        }
    }
}
