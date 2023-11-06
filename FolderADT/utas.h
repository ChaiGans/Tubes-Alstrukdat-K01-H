#ifndef _UTAS_h
#define _UTAS_h

#include "../FolderADT/wordmachine.h"
#include "../FolderADT/listutas.h"
#include "../FolderADT/listpengguna.h"
#include "../FolderADT/listkicau.h"

void buatUtas (int idKicau, int currentUserID, AddressListUtas *listUtas, ListPengguna listPengguna, ListKicau *listKicau);
void sambungUtas (int idKicau, int currentUserID, int index, AddressListUtas *listUtas, ListPengguna listPengguna, ListKicau *listKicau);
void hapusUtas (int idKicau, int index , int currentUserID, AddressListUtas *listUtas, ListPengguna listPengguna, ListKicau *listKicau);
void cetakUtas (int idKicau, int currentUserID, AddressListUtas *listUtas, ListPengguna listPengguna);

#endif