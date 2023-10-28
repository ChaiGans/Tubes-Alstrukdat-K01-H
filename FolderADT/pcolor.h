/**
Filename: pcolor.h
Description: Print character with some color in terminal
Prepared by: Asisten IF2110
Created at: 17/10/2019
Modified at: 23/10/2023
**/

/**
Details

print_xxx(c) will print c with xxx color. Import this header to use the declared functions.
We only provide 8 colors. Feel free to modify/add colors if you want to.
**/

#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"

void print_red(char c);
void print_green(char c);
void print_blue(char c);

/* ******************* Foto Profil ********************* */
#include "matrix.h"
#include "charmachine.h"
#include "wordmachine.h"

typedef struct
{
    Matrix WarnaProfil;  // Matrix warna profil
    Matrix SimbolProfil; // Matrix simbol profil
} FotoProfil;

/* *** Selektor *** */
#define WARNAPROFIL(F) (F).WarnaProfil
#define SIMBOLPROFIL(F) (F).SimbolProfil

/* *** KREATOR *** */
void createFotoProfil(FotoProfil *F);
/* Membentuk dua Matrix warnaProfil dan simbolProfil "kosong" berukuran 5 x 5 */

/* *** KELOMPOK BACA/TULIS *** */
void printFotoProfil(FotoProfil F);
/* I.S. F terdefinisi */
/* F.S. F ditampilkan di layar sesuai dengan warna dan simbolnya */

void ubahFotoProfil(FotoProfil *F);
/* I.S. F terdefinisi */
/* F.S. Warna dan simbol pada F terubah sesuai dengan input pengguna */