#ifndef KICAUAN_H
#define KICAUAN_H

#include "../FolderADT/wordmachine.h"
#include "../FolderADT/listkicau.h"
#include "../FolderADT/data.h"

void printKicau(Kicauan tweet, ListPengguna ListPengguna);
void upKicau(ListKicau *lk, ListPengguna lp, int currentUserID);
void kicauanTeman(int currentUserID, ListPengguna lp, ListKicau lk,  GrafPertemanan gp);
void sukaKicauan(ListKicau *lk, ListPengguna lp, int IDtweet, GrafPertemanan gp, int currentUserID);
void editKicauan(int currentUserID, ListKicau *lk, ListPengguna lp, int IDtweet);
void debugKicau(ListKicau lk, ListPengguna lp, int debugID);



#endif