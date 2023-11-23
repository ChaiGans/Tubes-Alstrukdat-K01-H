/*  Nama    : Elbert Chailes */
/*  NIM     : 13522045 */
/* File: time.c */
/* Tanggal: 30 Agustus 2022 */
/* *** ABSTRACT DATA TYPE TIME *** */

#include <stdio.h>
#include "time.h"
#include <math.h>
#include <time.h>

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsTIMEValid (int H, int M, int S) {
    /* Mengirim true jika H,M,S dapat membentuk T yang valid */
    /* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
    return (H>=0 && H<24 && M>=0 && M<60 && S>=0 && S<60);
}

/* *** Konstruktor: Membentuk sebuah TIME dari komponen-komponennya *** */
void CreateTime (TIME * T, int HH, int MM, int SS) {
    /* Membentuk sebuah TIME dari komponen-komponennya yang valid */
    /* Prekondisi : HH, MM, SS valid untuk membentuk TIME */    
    Hour(*T) = HH;
    Minute(*T) = MM;
    Second(*T) = SS;
}


/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaTIME (TIME * T) {
    /* I.S. : T tidak terdefinisi */
    /* F.S. : T terdefinisi dan merupakan jam yang valid */
    /* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk T */
    /* yang valid. Tidak mungkin menghasilkan T yang tidak valid. */
    /* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
    dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
    /* Jika TIME tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
    diulangi hingga didapatkan jam yang valid. */
    /* Contoh: 
    60 3 4
    Jam tidak valid
    1 3 4
    --> akan terbentuk TIME <1,3,4> */
    int HH, MM, SS;
    scanf("%d %d %d", &HH, &MM, &SS);
    while (!IsTIMEValid(HH, MM, SS)) {
        printf("Jam tidak valid\n");
        scanf("%d %d %d", &HH, &MM, &SS);
    }
    CreateTime(T, HH, MM, SS);
}

   
void TulisTIME (TIME T) {
    /* I.S. : T sembarang */
    /* F.S. : Nilai T ditulis dg format HH:MM:SS */
    /* Proses : menulis nilai setiap komponen T ke layar dalam format HH:MM:SS
    tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 
    printf("%02d:%02d:%02d", Hour(T), Minute(T), Second(T));
}


/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long TIMEToDetik (TIME T) {
    /* Diberikan sebuah TIME, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
    /* Rumus : detik = 3600*HH + 60*MM + SS */
    /* Nilai maksimum = 3600*23+59*60+59 */
    return (3600*Hour(T) + 60*Minute(T) + Second(T));
}

TIME DetikToTIME (long N) {
    /* Mengirim  konversi detik ke TIME */
    /* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang 
    mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus: 
    N1 = N mod 86400, baru N1 dikonversi menjadi TIME */
    int hour, minute, second;
    TIME t;
    int N1 = N % 86400; 
    hour = N1 / 3600;
    minute = N1 / 60 - (hour * 60);
    second = N1 - (hour*3600) - (minute*60);
    CreateTime(&t, hour, minute, second);
    return t;
}


/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean TEQ (TIME T1, TIME T2) {
    /* Mengirimkan true jika T1=T2, false jika tidak */
    return (Hour(T1)==Hour(T2) && Minute(T1)==Minute(T2) && Second(T1)==Second(T2));
}

boolean TNEQ (TIME T1, TIME T2) {
    /* Mengirimkan true jika T1 tidak sama dengan T2 */
    return (!TEQ(T1, T2));
}

boolean TLT (TIME T1, TIME T2) {
    /* Mengirimkan true jika T1<T2, false jika tidak */
    return TIMEToDetik(T2) > TIMEToDetik(T1);
}

boolean TGT (TIME T1, TIME T2) {
    /* Mengirimkan true jika T1>T2, false jika tidak */
    return TIMEToDetik(T2) < TIMEToDetik(T1);
}

/* *** Operator aritmatika TIME *** */
TIME NextDetik (TIME T) {
    /* Mengirim 1 detik setelah T dalam bentuk TIME */
    int detik = TIMEToDetik(T);
    return DetikToTIME(detik+1);
}

TIME NextNDetik (TIME T, int N) {
    /* Mengirim N detik setelah T dalam bentuk TIME */
    int detik = TIMEToDetik(T);
    return DetikToTIME(detik+N);
}

TIME PrevDetik (TIME T) {
    /* Mengirim 1 detik sebelum T dalam bentuk TIME */
    int detik = TIMEToDetik(T);
    return DetikToTIME(detik-1+86400);
}

TIME PrevNDetik (TIME T, int N) {
    /* Mengirim N detik sebelum T dalam bentuk TIME */
    int detik = TIMEToDetik(T);
    return DetikToTIME(detik-N+86400);
}

/* *** Kelompok Operator Aritmetika *** */
long Durasi (TIME TAw, TIME TAkh) {
    /* Mengirim TAkh-TAw dlm Detik, dengan kalkulasi */
    /* Jika TAw > TAkh, maka TAkh adalah 1 hari setelah TAw */
    return (TIMEToDetik(TAkh) - TIMEToDetik(TAw) + 86400)%86400;
}

void GetLocalTime (){
    time_t rawtime;
    struct tm *local_timeinfo;

    time(&rawtime);

    local_timeinfo = localtime(&rawtime);

    int year = local_timeinfo->tm_year + 1900;
    int month = local_timeinfo->tm_mon + 1;
    int day = local_timeinfo->tm_mday;
    int hour = local_timeinfo->tm_hour;
    int minute = local_timeinfo->tm_min;
    int second = local_timeinfo->tm_sec;

    printf("%d/%d/%d %d:%d:%d\n", day,month,year,hour,minute,second);    
}