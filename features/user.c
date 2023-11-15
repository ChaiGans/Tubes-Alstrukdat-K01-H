#include <stdio.h>
#include "user.h"
#include <stdlib.h>

void daftarPengguna (ListPengguna* l, GrafPertemanan* G) {
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
        CreateEmptyStackDraf(&(*l).contents[newProfile.index].stackdraf);
        MakeEmptyQueue(&(*l).contents[newProfile.index].permintaanTeman, 20);
        
        printf("Pengguna telah berhasil terdaftar. Masuk untuk menikmati fitur-fitur BurBir.\n");
        addNewUserGrafPertemanan(G);
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
        findUsernameID(usernameMasukan, &l, &currentID, &usernameFound);
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

void gantiProfil (Profile* userProfile) {
    Word bio, nomorHP, weton;
    displayProfileInformation(*userProfile);
    printf("Masukkan bio akun:\n");
    bio = ReadWord();
    transferWordToString(userProfile->bio, bio);
    putchar('\n');
    do {
        printf("Masukkan No HP:\n");
        nomorHP = ReadWord();
        putchar('\n');
        if (!isWordNomorHP(nomorHP)) {
            printf("No HP tidak valid. Masukkan lagi yuk!\n");
        }
    } while (!isWordNomorHP(nomorHP));
    int k;
    for (k = nomorHP.Length; k > 0; k--) {
        nomorHP.TabWord[k+1] = nomorHP.TabWord[k];
    }
    nomorHP.TabWord[0] ='0';
    nomorHP.Length += 1;
    if (nomorHP.Length > 10) {
        userProfile->nomorHP = (char *) realloc (userProfile->nomorHP, nomorHP.Length * (sizeof (char)) + 1);
        (*userProfile).nomorHP[nomorHP.Length] = '\0';
    }
    transferWordToString(userProfile->nomorHP, nomorHP);

    do {
        printf("Masukkan Weton:\n");
        weton = ReadWord();
        putchar('\n');
        if (!isWetonValid(weton)) {
            printf("Weton anda tidak valid.\n");
        }
    } while (!isWetonValid(weton));
    transferWordToString(userProfile->weton, weton);
    printf("Profil anda sudah berhasil diperbarui!");
}

void aturJenisAkun (Profile* userProfile) {
    printf("Saat ini, akun Anda adalah akun ");
    displayStatusAKun(*userProfile);
    if (stringStringCompare((*userProfile).status, "PUBLIK")) {
        printf(". Ingin mengubah ke akun PRIVAT? (YA/TIDAK)");
        Word konfirmasi = ReadWord();
        if (wordStringCompare(konfirmasi, "YA")) {
            transferStringToString("PRIVAT", userProfile->status);
        }
    } else {
        printf(". Ingin mengubah ke akun PUBLIK? (YA/TIDAK)");
        Word konfirmasi = ReadWord();
        if (wordStringCompare(konfirmasi, "YA")) {
            transferStringToString("PUBLIK", userProfile->status);
        }
    }   
}

void ubahFotoProfil(Profile *userProfile) {
    printf("Foto profil Anda saat ini adalah\n");
    displayFotoProfil(userProfile->fotoProfil);
    putchar('\n');
    printf("Masukkan Foto Profil yang baru: \n");
    Word userInput = ReadWord();

    int i;
    int baris = 0;
    int kolom = 0;

    for (i = 0; i < 100; i++) {
        char karakter = userInput.TabWord[i];

        if (i % 4 == 0) {
            ELMT(WARNAPROFIL((*userProfile).fotoProfil), baris, kolom) = karakter;
        } else if (i % 4 == 2) {
            ELMT(SIMBOLPROFIL((*userProfile).fotoProfil), baris, kolom) = karakter;
        }

        if (i % 4 == 3) {
            kolom++;
            if (kolom == 5) {
                kolom = 0;
            }
        }
        if (i % 20 == 19) {
            baris++;
        }
    }
    printf("Foto profil anda sudah berhasil diganti!");
}

void lihatProfil (Word targetUser, int currentLoginID, ListPengguna listpengguna, GrafPertemanan G) {
    int targetID;
    boolean targetExisted;
    findUsernameID(targetUser, &listpengguna, &targetID, &targetExisted);
    if (!targetExisted) {
        printf("Wah, akun tersebut tidak ditemukan.\n");
    } else {
        if (!isAuthorAccountPublic(targetID, listpengguna) && !isTeman(G, currentLoginID, targetID)) {
            printf("Wah, akun ");
            displayNameFromID(targetID, listpengguna);
            printf(" diprivat nih. Ikuti dulu yuk untuk bisa melihat profil ");
            displayNameFromID(targetID, listpengguna);
            printf("!\n");
        } else {
            displayProfileInformation(listpengguna.contents[targetID]);
        }
    }
}
