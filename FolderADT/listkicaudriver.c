#include "listkicau.h"
#include "stdio.h"

int main(){
    printf("=== Test Kicauan ===\n");

    ListKicau lk, lk2; CreateListKicau(&lk, 100); CreateListKicau(&lk2, 100);
    

    printf("\npanjang list kicau sekarang = %d\n", listKicauLength(lk));

    if (isEmptyListKicau(lk)) printf("\nlist kicau kosong\n");
    else printf("\nlist kicau tidak kosong\n");

    Kicauan tweet; 
    tweet.authorID = 1; 
    tweet.balasan = NULL; 
    tweet.id = 2; 
    tweet.like = 10; 
    tweet.localtime.DD = 17; tweet.localtime.MM = 8; tweet.localtime.YYYY = 1945; tweet.localtime.T.HH = 10; tweet.localtime.T.MM = 10; tweet.localtime.T.SS = 10;
    char* halo = "halo halo bandung";
    int i = 0; while(halo[i] != '\0'){
        tweet.text[i] = halo[i]; i++;
    } tweet.text[i] = '\0';

    insertLastListKicau(&lk, tweet);
    printf("\npanjang list kicau sekarang = %d\n", listKicauLength(lk));

    if (isIdxValidListKicau(lk, 10)) printf("\nidx 10 valid\n");
    else printf("\nidx 10 tidak valid\n");

    if (isIdxEffListKicau(lk, 10)) printf("\nidx 10 efektif\n");
    else printf("\nidx 10 tidak efektif\n");

    if (isFullListKicau(lk)) printf("\nlist kicau kosong\n");
    else printf("\nlist kicau tidak kosong\n");

    copyListKicau(lk, &lk2);
    Kicauan tweet2; 
    tweet2.authorID = 1; 
    tweet2.balasan = NULL; 
    tweet2.id = 2; 
    tweet2.like = 10; 
    tweet2.localtime.DD = 17; tweet2.localtime.MM = 8; tweet2.localtime.YYYY = 1945; tweet2.localtime.T.HH = 10; tweet2.localtime.T.MM = 10; tweet2.localtime.T.SS = 10;
    char* halo2 = "halo halo bandung";
    i = 0; while(halo2[i] != '\0'){
        tweet2.text[i] = halo2[i]; i++;
    } tweet2.text[i] = '\0';

    insertLastListKicau(&lk2, tweet2);
    printf("\nbefore deleted\n");
    for (i = 0; i < lk2.nEff; i++){
        printf("| ID = %d\n", lk2.buffer[i].id);
        printf("| Author ID = %d\n", lk2.buffer[i].authorID); 
        printf("| %2d/%2d/%4d %2d/%2d/%2d\n", lk2.buffer[i].localtime.DD, lk2.buffer[i].localtime.MM, lk2.buffer[i].localtime.YYYY, lk2.buffer[i].localtime.T.HH, lk2.buffer[i].localtime.T.MM, lk2.buffer[i].localtime.T.SS); 
        printf("| "); int j = 0; while(lk2.buffer[i].text[j] != '\0'){
            printf("%c", lk2.buffer[i].text[j]); j++;
        } printf("\n");
        printf("| Disukai: %d\n\n", lk2.buffer[i].like);
    }

    deleteLastListKicau(&lk2, &tweet2);
    printf("\nafter deleted\n");
    for (i = 0; i < lk2.nEff; i++){
        printf("| ID = %d\n", lk2.buffer[i].id);
        printf("| Author ID = %d\n", lk2.buffer[i].authorID); 
        printf("| %2d/%2d/%4d %2d/%2d/%2d\n", lk2.buffer[i].localtime.DD, lk2.buffer[i].localtime.MM, lk2.buffer[i].localtime.YYYY, lk2.buffer[i].localtime.T.HH, lk2.buffer[i].localtime.T.MM, lk2.buffer[i].localtime.T.SS); 
        printf("| "); int j = 0; while(lk2.buffer[i].text[j] != '\0'){
            printf("%c", lk2.buffer[i].text[j]); j++;
        } printf("\n");
        printf("| Disukai: %d\n\n", lk2.buffer[i].like);
    }
    dealocateListKicau(&lk); dealocateListKicau(&lk2);
    return 0;
}