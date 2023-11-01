#ifndef _USER_h
#define _USER_h

#include "../FolderADT/listpengguna.h"
#include "../FolderADT/wordmachine.h"
#include "../FolderADT/profile.h"

void daftarPengguna (ListPengguna* l);
void masukPengguna (int* currentUserID, ListPengguna l);
void gantiProfil (Profile* userProfile);
void aturJenisAkun (Profile* userProfile);
#endif