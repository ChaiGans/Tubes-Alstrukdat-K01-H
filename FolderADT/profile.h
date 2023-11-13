#ifndef __TYPE_H__
#define __TYPE_H__

#include "boolean.h"
#include "listpengguna.h"
#include "wordmachine.h"

/* pcolor */
#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"

void print_red(char c);
void print_green(char c);
void print_blue(char c);

/* ******************* Foto Profil ********************* */

#define SIZE 5 // Ukuran foto profil

/* *** KREATOR *** */
void createFotoProfil(FotoProfil *F);
/* Membentuk dua Matrix warnaProfil dan simbolProfil "kosong" berukuran 5 x 5 */

/* *** KELOMPOK BACA/TULIS *** */
void displayFotoProfil(FotoProfil F);
/* I.S. F terdefinisi */
/* F.S. F ditampilkan di layar sesuai dengan warna dan simbolnya */

// typedef struct {
//     char username[20];
//     char password[20];
//     char bio[135]; // Bio max 135 karakter
//     int nomorHP;
//     char weton[6]; // Pahing, Kliwon, Wage, Pon, dan Legi (case insensitive)
//     char status[6]; // PUBLIC, PRIVAT
//     Matrix fotoProfil[5][5]; // use pcolor.c
//     PrioQueueChar permintaanTeman; // harusnya priorqueuepermintaan (check by jumlah teman atau length of listTeman)
// } Profile;

void createProfile(Profile *p);
/* I.S. p sembarang */
/* F.S. p terdefinisi dengan nilai defaultnya */

void displayStatusAKun(Profile p);
/* I.S. p terdefinisi */
/* F.S. Status dari akun (PUBLIK atau PRIVAT) ditampilkan di layar */

void displayNomorHP(Profile p);
/* I.S. p terdefinisi */
/* F.S. nomorHP dari akun ditampilkan di layar */

void displayProfileInformation(Profile p);
/* I.S. p terdefinisi */
/* F.S. Informasi dari akun ditampilkan di layar */

void toLowerCase(const char original[], char lowercaseCopy[]);
/* I.S. original terdefinisi */
/* F.S. lowercaseCopy terdefinisi dengan lowercase dari original */

boolean isWetonValid(Word w);
/* Mengembalikan true jika weton valid, false jika tidak*/

// List Dinamis dari Kicauan
// typedef struct {
//     int id;
//     char text[280];
//     int authorID;
//     int like;
//     // Time (local time)
//     // Tree of balasan
// } Kicauan;

// typedef struct {
//     int id;
//     char text[10];
//     int authorID;
//     // TIme (local time)
// } Balasan;

// List Dinamis dari UTAS
// typedef struct {
//     Kicauan kicau;
//     ListUtas kicauansambungan; // Kicauan sambungan harus ada type : text, localtime
// } Utas;
#endif