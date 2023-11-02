#include <stdio.h>
#include <time.h>
#include <math.h>
#include "datetime.h"

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
int GetMaxDay(int M, int Y) {
    /* Mengirimkan jumlah hari maksimum pada bulan M dan tahun Y */
    /* Prekondisi: 1 <= M <= 12*/
    /* Hint: Perhatikan Leap Year. Leap Year adalah tahun dengan 29 hari pada bulan Februari */
    /* Aturan Leap Year: */
    /* 1. Jika angka tahun itu habis dibagi 400, maka tahun itu sudah pasti tahun kabisat. 8*/
    /* 2. Jika angka tahun itu tidak habis dibagi 400 tetapi habis dibagi 100, maka tahun itu sudah pasti bukan merupakan tahun kabisat. */
    /* 3. Jika angka tahun itu tidak habis dibagi 400, tidak habis dibagi 100 akan tetapi habis dibagi 4, maka tahun itu merupakan tahun kabisat. */
    /* 4. Jika angka tahun tidak habis dibagi 400, tidak habis dibagi 100, dan tidak habis dibagi 4, maka tahun tersebut bukan merupakan tahun kabisat. */
    if (M==2) {
        if (Y % 400 == 0 || (Y % 4 == 0 && Y % 100 != 0)) {
            return 29;
        } else {
            return 28;
        }
    }
    else if (M==1 || M==3 || M==5 || M==7 || M==8 || M==10 || M==12) {
        return 31;
    }
    else {
        return 30;
    }
}

boolean IsDATETIMEValid(int D, int M, int Y, int h, int m, int s) {
    /* Mengirim true jika D,M,Y,h,m,s dapat membentuk D yang valid */
    /* dipakai untuk mentest SEBELUM membentuk sebuah DATETIME */                                 
    if ((h>=0 && h<=23) && (m>=0 && m<=59) && (s>=0 && s<=59) && (M>=1 && M<=12) && (D>=1 && D<=GetMaxDay(M,Y)) && (Y>=1900 && Y<=2030)) {
        return true;
    }
    return false;
}

/* *** Konstruktor: Membentuk sebuah DATETIME dari komponen-komponennya *** */
void CreateDATETIME(DATETIME *D, int DD, int MM, int YYYY, int hh, int mm, int ss) {
    /* Membentuk sebuah DATETIME dari komponen-komponennya yang valid */
    /* Prekondisi : DD, MM, YYYY, h, m, s valid untuk membentuk DATETIME */
    Hour(Time(*D)) = hh;
    Minute(Time(*D)) = mm;
    Second(Time(*D)) = ss;
    Day(*D) = DD;
    Month(*D) = MM;
    Year(*D) = YYYY;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaDATETIME(DATETIME *D) {
    /* I.S. : D tidak terdefinisi */
    /* F.S. : D terdefinisi dan merupakan DATETIME yang valid */
    /* Proses : mengulangi membaca komponen DD, MM, YY, h, m, s sehingga membentuk D */
    /* yang valid. Tidak mungkin menghasilkan D yang tidak valid. */
    /* Pembacaan dilakukan dengan mengetikkan komponen DD, MM, YY, h, m, s
    dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
    /* Jika DATETIME tidak valid maka diberikan pesan: "DATETIME tidak valid", dan pembacaan
        diulangi hingga didapatkan DATETIME yang valid. */
    /* Contoh:
        32 13 2023 12 34 56
        DATETIME tidak valid
        31 12 2023 12 34 56
        --> akan terbentuk DATETIME <31,12,2023,12,34,56> */
    do {
        scanf("%d %d %d %d %d %d", &Day(*D), &Month(*D), &Year(*D), &Hour(Time(*D)), &Minute(Time(*D)), &Second(Time(*D)));
        if (!IsDATETIMEValid(Day(*D), Month(*D), Year(*D), Hour(Time(*D)), Minute(Time(*D)), Second(Time(*D)))) {
            printf("DATETIME tidak valid\n");
        }
    }
    while(!IsDATETIMEValid(Day(*D), Month(*D), Year(*D), Hour(Time(*D)), Minute(Time(*D)), Second(Time(*D))));
}

void TulisDATETIME(DATETIME D) {
    /* I.S. : D sembarang */    
    /* F.S. : Nilai D ditulis dg format DD/MM/YYYY HH:MM:SS */
    /* Proses : menulis nilai setiap komponen D ke layar dalam format DD/MM/YYYY HH:MM:SS
    tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/
    printf("%d/%d/%d %d:%d:%d", Day(D), Month(D), Year(D), Hour(Time(D)), Minute(Time(D)), Second(Time(D)));
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok operasi relasional terhadap DATETIME *** */
boolean DEQ(DATETIME D1, DATETIME D2) {
    /* Mengirimkan true jika D1=D2, false jika tidak */
    return (TIMEToDetik(Time(D1))==TIMEToDetik(Time(D2))) && (Day(D1)==Day(D2)) && (Month(D1)==Month(D2)) && (Year(D1)==Year(D2));    
}

boolean DNEQ(DATETIME D1, DATETIME D2) {
    /* Mengirimkan true jika D1 tidak sama dengan D2 */
    return (!DEQ(D1,D2));
}

boolean DLT(DATETIME D1, DATETIME D2) {
    /* Mengirimkan true jika D1<D2, false jika tidak */
    if (Year(D2)>Year(D1)) {
        return true;
    }
    if (Month(D2)>Month(D1)) {
        return true;
    }
    if (Day(D2)>Day(D1)) {
        return true;
    }
    if (TIMEToDetik(Time(D2))>TIMEToDetik(Time(D1))) {
        return true;
    }
    return false;
}

unsigned long long DATETIMEToDetik (DATETIME d1){
    unsigned long long jumlahDetik = 3600 * Hour(Time(d1)) + 60 * Minute(Time(d1)) + Second(Time(d1)) + 86400 * (Day(d1)-1);
    int i;
    for (i = 1; i < Month(d1); i++) {
        jumlahDetik += (unsigned long long) (GetMaxDay(i, Year(d1))*86400);
    }
    int j;
    for (j = 1900; j < Year(d1); j++) {
        if (j % 400 == 0 || (j % 4 == 0 && j % 100 != 0)) {
            jumlahDetik += (unsigned long long) 31622400;
        } else {
            jumlahDetik += (unsigned long long) 31536000;
        }
    }
    return jumlahDetik;
}

DATETIME DetikToDATETIME(unsigned long long detik) {
    DATETIME D;
    int year = 1900;
    int i;
    int temp_day = 0;
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
        temp_day = 366;
    } else {
        temp_day = 365;
    }
    while (detik >= 86400 * temp_day) {
        detik -= temp_day * 86400;
        year+=1;
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
            temp_day = 366;
        } else {
            temp_day = 365;
        }
    }
    int month = 1;
    while (detik >= GetMaxDay(month, year) * 86400) {
        detik -= GetMaxDay(month, year) * 86400;
        month+=1;
    }
    int day = detik/86400 + 1;
    detik %= 86400;
    TIME t = DetikToTIME((long) detik);
    CreateDATETIME(&D, day, month, year, 0, 0, 0);
    Time(D) = t;
    return D; 
}

boolean DGT(DATETIME D1, DATETIME D2) {
    /* Mengirimkan true jika D1>D2, false jika tidak */
    return !DLT(D1,D2) && DNEQ(D1,D2);
}
DATETIME DATETIMENextNDetik(DATETIME D, int N) {
    /* Mengirim salinan D dengan detik ditambah N */
    DATETIME dt;
    unsigned long long detik = DATETIMEToDetik(D);
    detik = detik+N ;   
    dt = DetikToDATETIME(detik); 
    return dt;
}
 
DATETIME DATETIMEPrevNDetik(DATETIME D, int N) {
    /* Mengirim salinan D dengan detik dikurang N */
    DATETIME dt;
    unsigned long long detik = DATETIMEToDetik(D);
    detik = detik-N ;   
    dt = DetikToDATETIME(detik); 
    return dt;
}

/* *** Kelompok Operator Aritmetika terhadap DATETIME *** */
long int DATETIMEDurasi(DATETIME DAw, DATETIME DAkh) {
    /* Mengirim DAkh-DAw dlm Detik, dengan kalkulasi */
    /* Prekondisi: DAkh > DAw */
   unsigned long long durasiAwal = DATETIMEToDetik(DAw);
   unsigned long long durasiAkhir = DATETIMEToDetik(DAkh);
   return (durasiAkhir - durasiAwal);
}

void getLocalTime (DATETIME* receiveTime){
    time_t rawtime;
    struct tm *local_timeinfo;

    time(&rawtime);

    local_timeinfo = localtime(&rawtime);

    Year(*receiveTime) = local_timeinfo->tm_year + 1900;
    Month(*receiveTime) = local_timeinfo->tm_mon + 1;
    Day(*receiveTime) = local_timeinfo->tm_mday;
    Hour(Time(*receiveTime)) = local_timeinfo->tm_hour;
    Minute(Time(*receiveTime))= local_timeinfo->tm_min;
    Second(Time(*receiveTime)) = local_timeinfo->tm_sec;   
}

void displayDATETIME (DATETIME receiveTime) {
    printf("%d/%d/%d %d:%d:%d\n", Day(receiveTime), Month(receiveTime), Year(receiveTime), Hour(Time(receiveTime)), Minute(Time(receiveTime)), Second(Time(receiveTime))); 
}

void DATETIMEparser(char datestring[19], DATETIME* returnedDateTime) {
    int i = 0;
    int res = 0;

    while (datestring[i] != '/') {
        res *= 10;
        res += datestring[i] - '0';
        i += 1;
    }
    returnedDateTime->DD = res;

    res = 0;
    i += 1;
    while (datestring[i] != '/') {
        res *= 10;
        res += datestring[i] - '0';
        i += 1;
    }
    returnedDateTime->MM = res;

    res = 0;
    i += 1;
    while (datestring[i] != ' ') {
        res *= 10;
        res += datestring[i] - '0';
        i += 1;
    }
    returnedDateTime->YYYY = res;

    res = 0;
    i += 1;
    while (datestring[i] != ':') {
        res *= 10;
        res += datestring[i] - '0';
        i += 1;
    }
    returnedDateTime->T.HH = res;

    res = 0;
    i += 1;
    while (datestring[i] != ':') {
        res *= 10;
        res += datestring[i] - '0';
        i += 1;
    }
    returnedDateTime->T.MM = res;

    res = 0;
    i += 1;
    while (datestring[i] != '\0') {
        res *= 10;
        res += datestring[i] - '0';
        i += 1;
    }
    returnedDateTime->T.SS = res;
}