#ifndef __TYPE_H__
#define __TYPE_H__

#include "boolean.h"
#include "listpengguna.h"
#include "wordmachine.h"

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

void createProfile (Profile * p);
void displayStatusAKun (Profile p);
void displayNomorHP (Profile p);
void displayProfileInformation (Profile p);
void toLowerCase(const char original[], char lowercaseCopy[]);
boolean isWetonValid (Word w);
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