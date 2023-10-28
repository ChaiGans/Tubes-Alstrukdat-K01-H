

#ifndef DATA_H
#define DATA_H

#include "wordmachine.h"
#include "charmachine.h"

// Fungsi pada data.h digunakan untuk mendapatkan data dari file pengguna.txt, kicauan.txt, balasan.txt, draf.txt, dan utas.txt
// Fungsi pada data.h juga digunakan untuk mengubah data pada file pengguna.txt, kicauan.txt, balasan.txt, draf.txt, dan utas.txt

int wordToInt(Word w);
// Mengembalikan nilai integer dari Word w.

void readPenggunaConfig(char *filename);
// I.S. : Sembarang
// F.S. : Membaca file pengguna.txt dan mendefinisikan profil pengguna.

void initReadConfig();
// I.S. : Sembarang
// F.S. : Membaca semua file config dan inisiasi semua data.

#endif // DATA_H
