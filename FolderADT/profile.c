#include <stdio.h>
#include "profile.h"

void createProfile (Profile * p) {
    *p->bio = "";
    (*p).nomorHP = NULL;
    *p->weton = "";
    *p->status = "PUBLIK";
}