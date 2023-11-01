#include <stdio.h>
#include "profile.h"

void createProfile (Profile * p) {
    *p->bio = "";
    (*p).nomorHP = NULL;
    *p->weton = "";
    *p->status = "PUBLIK";
}

void displayNomorHP (Profile p) {
    if (p.nomorHP != NULL) {
        printf("0%d", p.nomorHP);
    } else {
        printf("");
    }
}

void displayStatusAKun (Profile p) {
    if (stringStringCompare(p.status, "PUBLIK")) {
        printf("PUBLIK");
    } else {
        printf("PRIVAT");
    }
}

void displayProfileInformation (Profile p) {
    printf("| Nama: ");
    displayArrayOfChar(p.username);
    putchar('\n');
    printf("| Bio Akun: ");
    displayArrayOfChar(p.bio);
    putchar('\n');
    printf("| No HP: ");
    displayNomorHP(p);
    putchar('\n');
    printf("| Weton: ");
    displayArrayOfChar(p.weton);
    putchar('\n');
}

void toLowerCase(const char original[], char lowercaseCopy[]) {
    int i;
    for (i = 0; original[i] != '\0'; i++) {
        if (original[i] >= 'A' && original[i] <= 'Z') {
            lowercaseCopy[i] = original[i] + 32;
        } else {
            lowercaseCopy[i] = original[i]; 
        }
    }
    lowercaseCopy[i] = '\0'; 
}

boolean isWetonValid (Word w) {
    int i;
    char lowercase[w.Length];
    toLowerCase(w.TabWord, lowercase);
    if (stringStringCompare(lowercase, "pahing") || stringStringCompare(lowercase, "kliwon") || stringStringCompare(lowercase, "wage") || stringStringCompare(lowercase, "pon") || stringStringCompare(lowercase, "legi")) {
        return true;
    } else {
        return false;
    }
}