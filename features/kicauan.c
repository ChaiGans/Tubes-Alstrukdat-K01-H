#include "kicauan.h"
#include <stdio.h>
#define endl printf("\n")

void printKicau(Kicauan tweet, ListPengguna ListPengguna){
    printf("| ID = %d\n", tweet.id);
    printf("| "); displayNameFromID(tweet.authorID, ListPengguna); endl;
    printf("| "); TulisDATETIME(tweet.localtime); endl;
    printf("| "); int i = 0; while(tweet.text[i] != '\0'){
        printf("%c", tweet.text[i]); i++;
    } printf("\n");
    printf("| Disukai: %d\n", tweet.like);
}

void upKicau(ListKicau *lk, ListPengguna lp, int currentUserID){
    Kicauan tweetUp; 

    // reading untuk char < 280;
    printf("Masukkan kicauan:\n");
    int curLen = 0; START(stdin, false); IgnoreBlanks(false); 
    while(currentChar != MARK){
        if (curLen < 280){
            tweetUp.text[curLen] = currentChar; curLen++;
        } ADV();
    } tweetUp.text[curLen] = '\0';

    if (tweetUp.text[0] == '\0'){
        printf("Kicauan tidak boleh hanya berisi spasi!\n"); return;
    } else {
        tweetUp.authorID = currentUserID;
        tweetUp.id = getLastIdxListKicau(*lk)+2;
        tweetUp.like = 0;
        getLocalTime(&tweetUp.localtime);
        tweetUp.balasan = NULL;
        insertLastListKicau(&*lk, tweetUp);
        
        printf("\nSelamat! kicauan telah diterbitkan!\nDetail kicauan:\n");
        printKicau(tweetUp, lp);
    }
}

void kicauanTeman(int currentUserID, ListPengguna lp, ListKicau lk, GrafPertemanan gp){
    boolean adaTeman = false;
    int i; for(i = lk.nEff-1; i>=0; i--){
        if (isTeman(gp, currentUserID, lk.buffer[i].authorID)){
            printf("\n"); printKicau(lk.buffer[i],lp);
            adaTeman = true;
        }
    } if (!adaTeman){
        printf("\nAnda belum memiliki teman atau teman anda belum memiliki kicauan, coba untuk menjalin hubungan teman terlebih dahulu atau coba untuk memakai fitur KICAU!\n");
    }
}

void debugKicau(ListKicau lk, ListPengguna lp, int debugID){
    Kicauan kc = lk.buffer[debugID-1];
    printf("AUID = %d\n", kc.authorID);
    printf("ID = %d\n", kc.id);
    printf("LIKE = %d\n", kc.like);
    TulisDATETIME(kc.localtime); endl;
    printf("ISI = %s\n", kc.text);
}

void sukaKicauan(ListKicau *lk, ListPengguna lp, int IDtweet, GrafPertemanan gp, int currentUserID){
    if (isIdxEffListKicau(*lk, IDtweet-1)){
        boolean found = true; int i = 0; boolean private = false;
        while ((lp.contents[i].index != MARK_STATIK)&&(found)){
            if (lp.contents[i].index == (*lk).buffer[IDtweet-1].authorID) found = false;
            else i++;
        } if (stringStringCompare(lp.contents[i].status, "PUBLIK")||(isTeman(gp, lp.contents[i].index, currentUserID))){
            (*lk).buffer[IDtweet-1].like++;
            printf("Selamat! Kicauan telah disukai!\nDetail kicauan:\n");
            printKicau((*lk).buffer[IDtweet-1], lp);
        } else {
            printf("Wah, kicauan tersebut dibuat oleh akun privat! Ikuti akun itu dulu ya");
        }
    } else printf("Tidak ditemukan kicauan dengan ID = %d;", IDtweet);
}

void editKicauan(int currentUserID, ListKicau *lk, ListPengguna lp, int IDtweet){
    if (isIdxEffListKicau(*lk, IDtweet-1)){
        if ((*lk).buffer[IDtweet-1].authorID == currentUserID){
            
            printf("Masukkan kicauan baru: ");

            Kicauan newTweet;

            int curLen = 0; START(stdin, false); IgnoreBlanks(false); 
            while(currentChar != MARK){
                if (curLen < 280){
                    newTweet.text[curLen] = currentChar; curLen++;
                } ADV();
            } newTweet.text[curLen] = '\0'; 

            newTweet.authorID = (*lk).buffer[IDtweet-1].authorID;
            newTweet.id = (*lk).buffer[IDtweet-1].id;
            newTweet.like = (*lk).buffer[IDtweet-1].like;
            newTweet.localtime = (*lk).buffer[IDtweet-1].localtime;

            (*lk).buffer[IDtweet-1] = newTweet;

            printf("Selamat! kicauan telah diterbitkan!\nDetil kicauan:\n");
            printKicau(newTweet, lp);

        } else printf("Kicauan dengan ID = %d bukan milikmu!", IDtweet);
    } else printf("Tidak ditemukan kicauan dengan ID = %d!", IDtweet);
}