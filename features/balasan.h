#ifndef _BALASAN_h
#define _BALASAN_h

#include "../FolderADT/wordmachine/wordmachine.h"
#include "../FolderADT/kicauan/listkicau.h"
#include "../FolderADT/pengguna/listpengguna.h"
#include "../FolderADT/pertemanan/grafpertemanan.h"

void buatBalasan (int IDkicau, int IDbalasan, int currentLoginID, ListKicau* listkicau, ListPengguna listpengguna, GrafPertemanan G);
void lihatBalasan (int currentLoginID, int idKicau, ListKicau listkicau, ListPengguna listpengguna, GrafPertemanan* G);
void hapusBalasan (int currentLoginID, int idKicau, int idBalasan, ListKicau* listkicau);

#endif