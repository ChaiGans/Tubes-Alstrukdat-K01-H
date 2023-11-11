#ifndef _USER_h
#define _USER_h

#include "../FolderADT/listpengguna.h"
#include "../FolderADT/wordmachine.h"
#include "../FolderADT/profile.h"
#include "../FolderADT/grafpertemanan.h"

void daftarPengguna (ListPengguna* l);
void masukPengguna (int* currentUserID, ListPengguna l);
void gantiProfil (Profile* userProfile);
void aturJenisAkun (Profile* userProfile);
void ubahFotoProfil(Profile* userProfile);
void lihatProfil (Word targetUser, int currentLoginID, ListPengguna listpengguna, GrafPertemanan G);
/* I.S. F terdefinisi */
/* F.S. Warna dan simbol pada F terubah sesuai dengan input pengguna */
#endif