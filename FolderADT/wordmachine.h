/* File: mesinkata.h */
/* Definisi Mesin Word: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "boolean.h"
#include "charmachine.h"

#define NMax 300
#define BLANK ' '
#define NEWLINE '\n'
#define CARRIAGE '\r'

typedef struct
{
   char TabWord[NMax]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
   int Length;
} Word;

/* State Mesin Word */
extern boolean EndWord;
extern Word currentWord;
extern boolean isNewLine;

void IgnoreBlanks(boolean file);
/* Mengabaikan satu atau beberapa BLANK
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar = MARK */

void STARTWORD(FILE *input, boolean file);
/* I.S. : currentChar sembarang
   F.S. : EndWord = true, dan currentChar = MARK;
          atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */

void ADVWORD(boolean file);
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, EndWord = true.
   Proses : Akuisisi kata menggunakan procedure SalinWord */

void CopyWord();
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

void CopyLine();
/* Mengakuisisi line, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari line
   F.S. : currentWord berisi line yang sudah diakuisisi;
          currentChar = NEWLINE atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang line melebihi NMax, maka sisa line "dipotong" */

Word ReadWord();
/* Mengembalikan Word yang diberikan pengguna melalui terminal */

Word ReadCommands();
/* Mengembalikan command yang diberikan pengguna melalui terminal*/

boolean wordStringCompare(Word w, char command[]);
/* Mengembalikan true jika w sama dengan command */

int stringLength(char inputString[]);
/* Mengembalikan panjang string */

void transferWordToString(char inputString[], Word w);
/* I.S. inputString sembarang */
/* F.S. inputString berisi string yang sama dengan w */

boolean stringStringCompare(char string1[], char string2[]);
/* Mengembalikan true ketika kedua string memiliki isi yang sama */
/* false jika tidak */

void transferStringToString(char inputString[], char targetString[]);
/* I.S. inputString sembarang */
/* F.S. inputString berisi string yang sama dengan targetString */

void displayArrayOfChar(char string[]);
/* I.S. string sembarang */
/* F.S. string ditampilkan di layar */

boolean isWordNomorHP(Word w);
/* Mengembalikan true jika word hanya memuat angka */

Word removeFirstChar(Word w);
/* Menghilangkan huruf pertama pada w */

void CopyWord_FOR_LIHAT_PROFIL_ONLY();
/* Copyword khusus untuk Lihat Profil */

void ADVWORD_LIHAT_PROFIL_ONLY();
/* ADVWORD khusus untuk Lihat Profil*/

char* concatCharPtr(char* dir1, char* dir2);
#endif