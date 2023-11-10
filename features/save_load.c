#include "save_load.h"

char* concatDir(char* dir1, char* dir2){
    int i = 0, len = 0;
    while(dir1[i] != '\0'){
        i++; len++;
    } i = 0; while(dir2[i] != '\0'){
        i++; len++;
    } 
    
    char* string3 = (char*)malloc(sizeof(char)*(len+1)); 
    int j = 0; i = 0;

    while(dir1[i] != '\0'){
        string3[i] = dir1[i]; i++;
    } while(dir2[j] != '\0'){
        string3[i] = dir2[j];
        i++; j++;
    } 
    
    return string3;
}

boolean isExist(char* dirName){
    struct stat sb;
    if (stat(dirName, &sb) == 0 && S_ISDIR(sb.st_mode)) return true;
    else return false;
}

void saveBalasan(char* fileName, ListKicau lk, ListPengguna lp){
    FILE *file = fopen(fileName, "w");
    int banyakBalasan = 0, i;
    for(i = 0; i < lk.nEff; i++){
        if (lk.buffer[i].balasan != NULL) banyakBalasan++;
    } fprintf(file, "%d", banyakBalasan);
    i = 0; int j = 0;
    while(i < banyakBalasan){
        if (lk.buffer[j].balasan != NULL){
            int banyakIDBalasan = findHighestID(lk.buffer[j].balasan); 
            fprintf(file, "\n%d", banyakIDBalasan);
            int k = 0; for(k = 1; k < banyakIDBalasan+1; k++){
                BinTree writeBalasan = BalasanFromID(k, lk.buffer[j].balasan);
                fprintf(file, "\n-1 %d", k); // di sini masih bug, bingung cara cari id parent root
                fprintf(file, "\n%s", writeBalasan->info.text);
                fprintf(file, "\n%s", cariPenggunaID(writeBalasan->info.authorID, lp).username);
                fprintf(file, "\n%d/%d/%d %d:%d:%d", writeBalasan->info.time.DD, writeBalasan->info.time.MM, writeBalasan->info.time.YYYY, writeBalasan->info.time.T.HH, writeBalasan->info.time.T.MM, writeBalasan->info.time.T.SS);
            }
            i++;
        } j++;
    } fclose(file);
}

void saveKicauan(char* fileName, ListKicau lk, ListPengguna lp){
    FILE *file = fopen(fileName, "w");
    int i = 0, len = 0;
    while (i < lk.nEff){
        if (lk.buffer[i].authorID != -99) len++;
        i++;
    } fprintf(file, "%d", len);
    i = 0; while(i < lk.nEff){
        if (lk.buffer[i].authorID != -99){
            fprintf(file, "\n%d", lk.buffer[i].id);
            fprintf(file, "\n%s", lk.buffer[i].text);
            fprintf(file, "\n%d", lk.buffer[i].like);
            fprintf(file, "\n%s", cariPenggunaID(lk.buffer[i].authorID, lp).username);
            fprintf(file, "\n%d/%d/%d %d:%d:%d", lk.buffer[i].localtime.DD, lk.buffer[i].localtime.MM, lk.buffer[i].localtime.YYYY, lk.buffer[i].localtime.T.HH, lk.buffer[i].localtime.T.MM, lk.buffer[i].localtime.T.SS);
        }
    } fclose(file);
}

void savePengguna(char* fileName, ListPengguna lp){
    FILE *file = fopen(fileName, "w");
    int i = 0; fprintf(file, "%d", ListPenggunaLength(lp));
    while(i < ListPenggunaLength(lp)){
        fprintf(file, "\n%s\n", lp.contents[i].username);
        fprintf(file, "%s\n", lp.contents[i].password);
        fprintf(file, "%s\n", lp.contents[i].bio);
        fprintf(file, "%d\n", lp.contents[i].nomorHP);
        fprintf(file, "%s\n", lp.contents[i].weton);
        fprintf(file, "%s\n", lp.contents[i].status);
        for (int j = 0; j < lp.contents[i].fotoProfil.SimbolProfil.rowEff; j++){
            for (int k = 0; k < lp.contents[i].fotoProfil.SimbolProfil.colEff; k++){
                fprintf(file, "%c ", lp.contents[i].fotoProfil.WarnaProfil.mem[i][j]);
                fprintf(file, "%c", lp.contents[i].fotoProfil.WarnaProfil.mem[i][j]);
                if (k != lp.contents[i].fotoProfil.SimbolProfil.colEff - 1) fputs(" ", file);
            } if (j != lp.contents[i].fotoProfil.SimbolProfil.rowEff - 1) fputs("\n", file);
        }
    } fclose(file);
}

void saveDraft(char* fileName, ListPengguna lp){
    FILE *file = fopen(fileName, "w");
    int i = 0, len = 0;
    while(lp.contents[i].index != MARK_STATIK){
        if (lp.contents[i].stackdraf.T != NULL) len++;
        i++;
    } fprintf(file, "%d", len); i = 0;
    while(lp.contents[i].index != MARK_STATIK){
        if (lp.contents[i].stackdraf.T != NULL){
            fprintf(file, "\ns", lp.contents[i].username);
            StackDraf temp = lp.contents[i].stackdraf; ElTypeDraf tempdraf;
            while (!IsEmptyStackDraf(temp)){
                PopStackDraf(&temp, &tempdraf);
                fprintf(file, "\n%s", tempdraf.text);
                fprintf(file, "\n%d/%d/%d %d:%d:%d", tempdraf.localtime.DD, tempdraf.localtime.MM, tempdraf.localtime.YYYY, tempdraf.localtime.T.HH, tempdraf.localtime.T.MM, tempdraf.localtime.T.SS);
            }
        } i++;
    } fclose(file);
}

void saveUtas(char* fileName, ListPengguna listPengguna, ListKicau listKicau, AddressListUtas listUtas){
    FILE *file = fopen(fileName, "w");
    int len = ListUtaslength(listUtas);
    fprintf(file, "%d", len); 
    AddressListUtas curr = listUtas;
    int i = 0; for(i = 0; i < len; i++){
        fprintf(file, "\n%d", curr->idKicau);
        fprintf(file, "\n%d", utaslength(curr->utas));
        AddressUtas currU = curr->utas;
        while(currU != NULL){
            fprintf(file, "\n%s", currU->info.text);
            fprintf(file, "\n%s", cariPenggunaID((currU->info.idAuthor), listPengguna).username);
            fprintf(file, "\n%d/%d/%d %d:%d:%d", currU->info.localtime.DD, currU->info.localtime.MM, currU->info.localtime.YYYY, currU->info.localtime.T.HH, currU->info.localtime.T.MM, currU->info.localtime.T.SS);
            currU = currU->next;
        } curr = curr->next;
    } fclose(file);
}

void saveAll(ListKicau lk, ListPengguna lp, AddressListUtas lu){
    char* dirName = (char*)malloc(sizeof(char)*(100));
    printf("Masukkan nama folder penyimpanan\n");
    int curLen = 0; START(stdin, false); IgnoreBlanks(false);
    while(currentChar != MARK){
        dirName[curLen] = currentChar; curLen++;
        ADV();
    } dirName[curLen] = '\0';
    if (!isExist(dirName)){
        printf("belum terdapat %s. Akan dilakukan pembuatan %s terlebih dahulu.\n", dirName, dirName);
        printf("\n Mohon tunggu...");
        mkdir(dirName);
        printf("1...\n2...\n3...\n\n%s sudah berhasil dibuat.", dirName);
    } 
    printf("\nAnda akan melakukan penyimpanan di %s.\n", dirName);
    printf("\n Mohon tunggu...\n");
    saveBalasan(concatDir(dirName, "/balasan.txt"), lk, lp);
    printf("1...\n");
    saveDraft(concatDir(dirName, "/draf.txt"), lp);
    saveKicauan(concatDir(dirName, "/kicauan.txt"), lk, lp);
    printf("2...\n");
    savePengguna(concatDir(dirName, "/pengguna.txt"), lp);
    saveUtas(concatDir(dirName, "/utas.txt"), lp, lk, lu);
    printf("3...\n");
    printf("\nPenyimpanan telah berhasil dilakukan!\n");
}

void loadAll(ListPengguna *listPengguna, GrafPertemanan *pertemanan, ListKicau *listKicau, AddressListUtas *listUtas){
    char* dirName = (char*)malloc(sizeof(char)*(100));
    printf("Masukkan nama folder yang hendak dimuat\n");
    int curLen = 0; START(stdin, false); IgnoreBlanks(false);
    while(currentChar != MARK){
        dirName[curLen] = currentChar; curLen++;
        ADV();
    } dirName[curLen] = '\0';
    if (!isExist(dirName)){
        printf("\nTidak ada folder yang dimaksud!\n"); return;
    } else{
        printf("\nAnda akan melakukan pemuatan dari %s.\n", dirName);
        printf("\n Mohon tunggu...\n");
        readPenggunaConfig(concatDir(dirName, "/pengguna.txt"), listPengguna, pertemanan);
        printf("1...\n");
        readKicauanConfig(concatDir(dirName, "/kicauan.txt"), listKicau, *listPengguna);
        readBalasanConfig(concatDir(dirName, "/balasan.txt"), listKicau, *listPengguna);
        printf("2...\n");
        // readDrafConfig(concatDir(dirName, "/draf.txt"));
        readUtasConfig(concatDir(dirName, "/utas.txt"), *listPengguna, listKicau, listUtas);
        printf("3...\n");
        printf("\nPenyimpanan telah berhasil dilakukan!\n");
    } 

}