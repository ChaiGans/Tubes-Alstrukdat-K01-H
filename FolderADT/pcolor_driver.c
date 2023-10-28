/**
Filename: pcolor_driver.c (driver of pcolor.h)
Description: Print character with some color in terminal
Prepared by: Asisten IF2110
Created at: 17/10/2019
Modified at: 23/10/2023
**/

#include <stdio.h>
#include "pcolor.h"

int main()
{
    // test foto profil
    FotoProfil F;
    createFotoProfil(&F);
    printFotoProfil(F);

    ubahFotoProfil(&F);
    printFotoProfil(F);
    return 0;
}
