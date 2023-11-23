#ifndef _UTAS_h
#define _UTAS_h

#include "../FolderADT/wordmachine/wordmachine.h"
#include "../FolderADT/utas/listutas.h"
#include "../FolderADT/pengguna/listpengguna.h"
#include "../FolderADT/kicauan/listkicau.h"
#include "../FolderADT/pertemanan/grafpertemanan.h"

void buatUtas(int idKicau, int currentUserID, AddressListUtas *listUtas, ListKicau listKicau);
void sambungUtas(int idUtas, int index, int currentUserID, AddressListUtas *listUtas, ListKicau listKicau);
void hapusUtas(int idUtas, int index, int currentUserID, AddressListUtas *listUtas, ListKicau listKicau);
void cetakUtas(int idUtas, int currentUserID, AddressListUtas *listUtas, ListPengguna listPengguna, ListKicau listKicau, GrafPertemanan grafPertemanan);

#endif