

#ifndef DATA_H
#define DATA_H

#include "wordmachine.h"
#include "boolean.h"
#include "fotoprofil.h"
#include "listpengguna.h"
#include "matrix.h"

// Fungsi pada data.h digunakan untuk mendapatkan data dari file pengguna.txt, kicauan.txt, balasan.txt, draf.txt, dan utas.txt
// Fungsi pada data.h juga digunakan untuk mengubah data pada file pengguna.txt, kicauan.txt, balasan.txt, draf.txt, dan utas.txt

Word blankLineCheck(Word w);
// I.S. : w sembarang
// F.S. : Jika w kosong, mengembalikan w dengan isi " "

int wordToInt(Word w);
// Mengembalikan nilai integer dari Word w.
// keknya ini bakal dipindah ke tempat lain kek wordmachine.h
// kalo ngga bikin file header baru yang full buat olah Word

void readPenggunaConfig(char *filename, ListPengguna *listPengguna);
// I.S. : Sembarang
// F.S. : Membaca file pengguna.txt dan mendefinisikan profil pengguna.

void readKicauanConfig(char *filename);
// I.S. : Sembarang
// F.S. : Membaca file kicauan.txt dan mendefinisikan kicauan.

void readBalasanConfig(char *filename);
// I.S. : Sembarang
// F.S. : Membaca file balasan.txt dan mendefinisikan balasan.

void readDrafConfig(char *filename);
// I.S. : Sembarang
// F.S. : Membaca file draf.txt dan mendefinisikan draf.

void readUtasConfig(char *filename);
// I.S. : Sembarang
// F.S. : Membaca file utas.txt dan mendefinisikan utas.

void initReadConfig(Word fileName, ListPengguna *listPengguna);
// I.S. : Sembarang
// F.S. : Membaca semua file config dan inisiasi semua data.

#endif // DATA_H
