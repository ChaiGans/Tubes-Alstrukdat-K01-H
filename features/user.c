#include <stdio.h>
#include "user.h"

void daftarPengguna (ListPengguna* l) {
    Profile newProfile;
    Word username, katasandi;
    createProfile(&newProfile);
    if (!isFullListPengguna(*l)) {
        boolean isUsernameTaken = false;
        do {
            printf("Masukkan nama:\n");
            username = ReadWord();
            if (username.Length > 20) {
                printf("Panjang maksimal nama pengguna adalah 20 karakter (termasuk spasi).\n");
                continue;
            }
            transferWordToString(newProfile.username, username);
            putchar('\n');
            if (isUsernameTaken) {
                printf("Wah, sayang sekali nama tersebut telah diambil.\n");
            }
            isUsernameTaken = isUserAlreadyExist(*l, username);
        } while (isUsernameTaken || username.Length > 20);
        do {
            printf("Masukkan kata sandi:\n");
            katasandi = ReadWord();
            transferWordToString(newProfile.password, katasandi);
            putchar('\n');
            if (katasandi.Length > 20) {
                printf("Panjang maksimal kata sandi pengguna adalah 20 karakter (termasuk spasi)\n.");
            }
        } while (katasandi.Length > 20);
        newProfile.index = ListPenggunaLength(*l);
        insertLastListPengguna(l, newProfile);
        printf("Pengguna telah berhasil terdaftar. Masuk untuk menikmati fitur-fitur BurBir.\n");
    } else {
        printf("Kapasitas pengguna sudah maksimal. Tidak bisa membuat pengguna baru lagi.\n");
    }   
}

void masukPengguna (int* currentUserID, ListPengguna l) {
    Word usernameMasukan, passwordMasukan;
    int currentID;
    boolean usernameFound = false;
    do {
        printf("Masukkan nama:\n");
        usernameMasukan = ReadWord();
        findUsernameID(usernameMasukan, l, &currentID, &usernameFound);
        putchar('\n');
        if (!usernameFound) {
            printf("Wah, nama yang Anda cari tidak ada. Masukkan nama lain!\n");
        }
    } while (!usernameFound);
    do {
        printf("Masukkan kata sandi:\n");
        passwordMasukan = ReadWord();
        if (!passwordChecker(currentID, l, passwordMasukan)) {
            printf("Wah, kata sandi yang Anda masukkan belum tepat. Periksa kembali kata sandi Anda!\n");
        }
    } while (!passwordChecker(currentID, l, passwordMasukan));
    *currentUserID = currentID;
    printf("Anda telah berhasil masuk dengan nama pengguna ");
    displayNameFromID(currentID, l);
    printf(". Mari menjelajahi BurBir bersama Ande-Ande Lumut!\n");
}

