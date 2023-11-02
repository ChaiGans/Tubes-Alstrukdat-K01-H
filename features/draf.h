#ifndef _DRAF_h
#define _DRAF_h

#include "../FolderADT/stackdraf.h"
#include "../FolderADT/wordmachine.h"
#include "../FolderADT/listkicau.h"
#include "../FolderADT/listpengguna.h"

void buatDraf (StackDraf* stackDraf, int currentUserID, ListKicau* listkicau, ListPengguna listpengguna);
void lihatDraf (StackDraf* stackDraf, int currentUserID, ListKicau* listkicau, ListPengguna listpengguna);

#endif