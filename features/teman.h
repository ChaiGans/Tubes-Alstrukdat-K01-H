#ifndef TEMAN_H
#define TEMAN_H

#include "../FolderADT/data.h"

void displayDaftarTeman(int currentUserID, GrafPertemanan grafPertemanan, ListPengguna listPengguna);
// I.S. : currentUserID, grafPertemanan, dan listPengguna terdefinisi
// F.S. : Menampilkan daftar teman dari currentUserID

void hapusTeman(int currentUserID, GrafPertemanan *grafPertemanan, ListPengguna listPengguna);
// I.S. : currentUserID, grafPertemanan, dan listPengguna terdefinisi
// F.S. : Menghapus teman dari currentUserID

void kirimPermintaanTeman(int currentUserID, GrafPertemanan *grafPertemanan, ListPengguna listPengguna);
// I.S. : currentUserID, grafPertemanan, dan listPengguna terdefinisi
// F.S. : currentUserID memberikan permintaan teman ke seorang nama pengguna

void displayDaftarPermintaanTeman(int currentUserID, GrafPertemanan grafPertemanan, ListPengguna listPengguna);
// I.S. : currentUserID, grafPertemanan, dan listPengguna terdefinisi
// F.S. : Menampilkan daftar permintaan teman untuk currentUserID

void terimaPermintaanTeman(int currentUserID, GrafPertemanan *grafPertemanan, ListPengguna listPengguna);
// I.S. : currentUserID, grafPertemanan, dan listPengguna terdefinisi
// F.S. : currentUserID menerima permintaan teman dari seorang nama pengguna

#endif