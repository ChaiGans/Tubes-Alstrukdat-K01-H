#ifndef _UTAS_h
#define _UTAS_h

#include "../FolderADT/wordmachine.h"
#include "../FolderADT/listutas.h"
#include "../FolderADT/listpengguna.h"
#include "../FolderADT/listkicau.h"
#include "../FolderADT/grafpertemanan.h"

void buatUtas(int idKicau, int currentUserID, AddressListUtas *listUtas, ListKicau listKicau);
void sambungUtas(int idUtas, int index, int currentUserID, AddressListUtas *listUtas, ListKicau listKicau);
void hapusUtas(int idUtas, int index, int currentUserID, AddressListUtas *listUtas, ListKicau listKicau);
void cetakUtas(int idUtas, int currentUserID, AddressListUtas *listUtas, ListPengguna listPengguna, ListKicau listKicau, GrafPertemanan grafPertemanan);

#endif