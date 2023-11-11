#include <FolderADT/data.h>
#include <stdio.h>
#include <sys/stat.h>


void saveBalasan();
void saveKicauan(char* fileName, ListKicau lk, ListPengguna lp);
void savePengguna(char* fileName, ListPengguna lp, GrafPertemanan gp);
void saveDraft(char* fileName, ListPengguna lp);
void saveUtas();
char* concatDir(char* dir1, char* dir2);
boolean isExist(char* dirName);
void saveAll(ListKicau lk, ListPengguna lp, AddressListUtas lu, GrafPertemanan gp);
void loadAll(ListPengguna *listPengguna, GrafPertemanan *pertemanan, ListKicau *listKicau, AddressListUtas *listUtas);
