#include "../FolderADT/data.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>


void saveBalasan(char* fileName, ListKicau lk, ListPengguna lp);
void saveKicauan(char* fileName, ListKicau lk, ListPengguna lp);
void savePengguna(char* fileName, ListPengguna lp, GrafPertemanan gp);
void saveDraft(char* fileName, ListPengguna lp);
void saveUtas(char* fileName, ListPengguna listPengguna, ListKicau listKicau, AddressListUtas listUtas);
boolean isExist(char* dirName);
void saveAll(ListKicau lk, ListPengguna lp, AddressListUtas lu, GrafPertemanan gp);
void loadAll(ListPengguna *listPengguna, GrafPertemanan *pertemanan, ListKicau *listKicau, AddressListUtas *listUtas);
