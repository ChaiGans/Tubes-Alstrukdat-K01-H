#include "kicauan.h"
#include <stdio.h>
#define endl printf("\n")

void printKicau(Kicauan tweet, ListPengguna ListPengguna){
    printf("| ID = %d\n", tweet.id);
    printf("| "); displayNameFromID(tweet.authorID, ListPengguna); endl;
    printf("| "); TulisDATETIME(tweet.localtime); endl;
    printf("| %c\n", tweet.text);
    printf("| Disukai: %d\n", tweet.like);
}

void upKicau(ListKicau *lk, ListPengguna lp, int currentUserID){
    Kicauan tweetUp; 

    // reading untuk char < 280;
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
        tweetUp.id = getLastIdxListKicau(*lk)+1;
        tweetUp.like = 0;
        getLocalTime(&tweetUp.localtime);

        insertLastListKicau(&*lk, tweetUp);
        
        printf("\nSelamat! kicauan telah diterbitkan!\nDetail kicauan:\n");
        printKicau(tweetUp, lp);
    }
}



void sukaKicauan(ListKicau *lk, ListPengguna lp, int IDtweet){
    if (isIdxEffListKicau(*lk, IDtweet)){
        boolean found = true; int i = 0; boolean private = false;
        while ((lp.contents[i].index != MARK_STATIK)&&(found)){
            if (lp.contents[i].index == (*lk).buffer[IDtweet-1].authorID) found = false;
            else i++;
        } if (lp.contents[i].status == "PUBLIC"){
            printf("Selamat! Kicauan telah disukai!\nDetail kicauan:\n");
            printKicau((*lk).buffer[IDtweet-1], lp);
        } else {
            printf("Wah, kicauan tersebut dibuat oleh akun privat! Ikuti akun itu dulu ya");
        }
    }else printf("Tidak ditemukan kicauan dengan ID = %d;", IDtweet);
}

void editKicauan(int currentUserID, ListKicau *lk, ListPengguna lp, int IDtweet){
    if (isIdxEffListKicau(*lk, IDtweet)){
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

            printf("Selamat! kicauan telah diterbitkan!\nDetil kicauan:");
            printKicau(newTweet, lp);

        } else printf("Kicauan dengan ID = %d bukan milikmu!", IDtweet);
    } else printf("Tidak ditemukan kicauan dengan ID = %d!", IDtweet);
}

