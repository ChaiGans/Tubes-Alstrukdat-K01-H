#ifndef _USER_h
#define _USER_h

#include "../FolderADT/pengguna/listpengguna.h"
#include "../FolderADT/wordmachine/wordmachine.h"
#include "../FolderADT/pengguna/profile.h"
#include "../FolderADT/pertemanan/grafpertemanan.h"
#include "../FolderADT/queue/prioqueuechar.h"

void daftarPengguna (ListPengguna* l, GrafPertemanan* G) ;
void masukPengguna (int* currentUserID, ListPengguna l);
void gantiProfil (Profile* userProfile);
void aturJenisAkun (Profile* userProfile);
void ubahFotoProfil(Profile* userProfile);
void lihatProfil (Word targetUser, int currentLoginID, ListPengguna listpengguna, GrafPertemanan G);
/* I.S. F terdefinisi */
/* F.S. Warna dan simbol pada F terubah sesuai dengan input pengguna */
#endif