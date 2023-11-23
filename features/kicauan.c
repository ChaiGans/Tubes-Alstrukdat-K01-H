#include "kicauan.h"
#include <stdio.h>
#define endl printf("\n")

void printKicau(Kicauan tweet, ListPengguna ListPengguna, char* tag){
    printf("| ID = %d\n", tweet.id);
    printf("| "); displayNameFromID(tweet.authorID, ListPengguna); endl;
    printf("| "); TulisDATETIME(tweet.localtime); endl;
    printf("| "); int i = 0; while(tweet.text[i] != '\0'){
        printf("%c", tweet.text[i]); i++;
    } printf("\n");
    if (tag != NULL) printf("| #%s\n", tag);
    printf("| Disukai: %d\n", tweet.like);
}

void upKicau(ListKicau *lk, ListPengguna lp, int currentUserID, DatabaseTagar *databaseTagar){
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
        // masukkan tagar
        printf("Masukkan tagar:\n");
        char tagar[30];
        curLen = 0; START(stdin, false); IgnoreBlanks(false); 
        while(currentChar != MARK){
            if (curLen < 29){
                tagar[curLen] = currentChar; curLen++;
            } ADV();
        } tagar[curLen] = '\0';
        tweetUp.authorID = currentUserID;
        tweetUp.id = getLastIdxListKicau(*lk)+2;
        tweetUp.like = 0;
        getLocalTime(&tweetUp.localtime);
        tweetUp.balasan = NULL;

        insertLastListKicau(&*lk, tweetUp);
        if (tagar[0] != '\0') insertTagar(databaseTagar, tagar, &((*lk).buffer[(*lk).nEff-1]));

        printf("\nSelamat! kicauan telah diterbitkan!\nDetail kicauan:\n");
        printKicau(tweetUp, lp, (tagar[0] == '\0' ? NULL : tagar));
    }
}

void cariKicauTagar(char tagar[], ListKicau lk, ListPengguna lp, DatabaseTagar db){
    int hash = hashTagar(tagar); printf("\n");

    char tagarlowercase[30];
    int curLen = 0;
    while((curLen < 29)&&(tagar[curLen] != '\0')){
        tagarlowercase[curLen] = makeLowerCase(tagar[curLen]); curLen++;
    } tagarlowercase[curLen] = '\0';

    while ((db.keyAndValue[hash] != NULL)&&(!stringStringCompare(db.keyAndValue[hash]->Tagar, tagarlowercase))) hash++;
    if (db.keyAndValue[hash] == NULL) printf("Tidak ditemukan kicauan dengan tagar %s\n", tagar);
    else {
        PointerAddressKicau p = db.keyAndValue[hash]->listKicauTagar;
        while (p != NULL){
            Kicauan temp = *(p->currKicau);
            printKicau(temp, lp, tagar); printf("\n");
            p = p->nextKicau;
        }
    }

}

void kicauanTeman(int currentUserID, ListPengguna lp, ListKicau lk, GrafPertemanan gp){
    boolean adaTeman = false;
    int i; for(i = lk.nEff-1; i>=0; i--){
        if (isTeman(gp, currentUserID, lk.buffer[i].authorID)){
            printf("\n"); printKicau(lk.buffer[i],lp, NULL);
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
            printf("\nSelamat! Kicauan telah disukai!\nDetail kicauan:\n");
            printKicau((*lk).buffer[IDtweet-1], lp, NULL);
        } else {
            printf("\nWah, kicauan tersebut dibuat oleh akun privat! Ikuti akun itu dulu ya\n");
        }
    } else printf("\nTidak ditemukan kicauan dengan ID = %d;\n", IDtweet);
}

void editKicauan(int currentUserID, ListKicau *lk, ListPengguna lp, int IDtweet){
    if (isIdxEffListKicau(*lk, IDtweet-1)){
        if ((*lk).buffer[IDtweet-1].authorID == currentUserID){
            
            printf("\nMasukkan kicauan baru: \n");

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

            printf("\nSelamat! kicauan telah diterbitkan!\nDetil kicauan:\n");
            printKicau(newTweet, lp, NULL);

        } else printf("\nKicauan dengan ID = %d bukan milikmu!\n", IDtweet);
    } else printf("\nTidak ditemukan kicauan dengan ID = %d!\n", IDtweet);
}