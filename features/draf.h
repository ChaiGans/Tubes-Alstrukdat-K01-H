#ifndef _DRAF_h
#define _DRAF_h

#include "../FolderADT/draf/stackdraf.h"
#include "../FolderADT/wordmachine/wordmachine.h"
#include "../FolderADT/kicauan/listkicau.h"
#include "../FolderADT/pengguna/listpengguna.h"

void buatDraf (int currentUserID, ListKicau* listkicau, ListPengguna* listpengguna);
void lihatDraf (int currentUserID, ListKicau* listkicau, ListPengguna* listpengguna);

#endif