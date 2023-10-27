#ifndef __TYPE_H__
#define __TYPE_H__

#include "boolean.h"
#include "matrix.h"

typedef struct {
    char* username; // Flexible size username
    char* password; // Flexible size password
    char bio[135]; // Bio max 135 karakter
    int nomorHP; 
    char weton[6]; // Pahing, Kliwon, Wage, Pon, dan Legi (case insensitive)
    char status[6]; // PUBLIC, PRIVAT, NETRAL
    Matrix fotoProfil[5][5]; // use pcolor.c
    Profil friendList[20];
    int popularitas;
    Kicauan kicauan;
} Profil;

typedef struct {
    int id;
    char text[280];
    int like;
} Kicauan;

#endif