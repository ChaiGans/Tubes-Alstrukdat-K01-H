#ifndef _BALASAN_h
#define _BALASAN_h

#include "../FolderADT/wordmachine.h"
#include "../FolderADT/listkicau.h"
#include "../FolderADT/listpengguna.h"

void buatBalasan (int IDkicau, int IDbalasan, int currentLoginID, ListKicau* listkicau, ListPengguna listpengguna);
void lihatBalasan (int idKicau, ListKicau listkicau, ListPengguna listpengguna);

#endif