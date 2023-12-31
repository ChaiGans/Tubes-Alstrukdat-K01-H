#include "save_load.h"


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
            fprintf(file, "\n%d", j+1);
            fprintf(file, "\n%d", banyakIDBalasan);
            int k = 0; for(k = 1; k < banyakIDBalasan+1; k++){
                BinTree writeBalasan = BalasanFromID(k, lk.buffer[j].balasan);
                BinTree parent = getParent(NULL, lk.buffer[j].balasan, k);
                fprintf(file, "\n%d %d", (parent==NULL)? -1 : parent->info.id, k); // di sini masih bug, bingung cara cari id parent root
                fprintf(file, "\n%s", writeBalasan->info.text);
                fprintf(file, "\n%s", cariPenggunaID(writeBalasan->info.authorID, lp).username);
                fprintf(file, "\n%02d/%02d/%04d %02d:%02d:%02d", writeBalasan->info.time.DD, writeBalasan->info.time.MM, writeBalasan->info.time.YYYY, writeBalasan->info.time.T.HH, writeBalasan->info.time.T.MM, writeBalasan->info.time.T.SS);
            }
            i++;
        } j++;
    } fputs("\n", file); 
    fclose(file);
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
            fprintf(file, "\n%02d/%02d/%04d %02d:%02d:%02d", lk.buffer[i].localtime.DD, lk.buffer[i].localtime.MM, lk.buffer[i].localtime.YYYY, lk.buffer[i].localtime.T.HH, lk.buffer[i].localtime.T.MM, lk.buffer[i].localtime.T.SS);
        } i++;
    } fputs("\n", file); 
    fclose(file);
}

void savePengguna(char* fileName, ListPengguna lp, GrafPertemanan gp){
    FILE *file = fopen(fileName, "w");
    int i = 0; fprintf(file, "%d", ListPenggunaLength(lp));
    while(i < ListPenggunaLength(lp)){
        fprintf(file, "\n%s\n", lp.contents[i].username);
        fprintf(file, "%s\n", lp.contents[i].password);
        fprintf(file, "%s\n", lp.contents[i].bio);
        fprintf(file, "%s\n", lp.contents[i].nomorHP);
        fprintf(file, "%s\n", lp.contents[i].weton);
        fprintf(file, "%s\n", lp.contents[i].status);
        for (int j = 0; j < lp.contents[i].fotoProfil.SimbolProfil.rowEff; j++){
            for (int k = 0; k < lp.contents[i].fotoProfil.SimbolProfil.colEff; k++){
                fprintf(file, "%c ", lp.contents[i].fotoProfil.WarnaProfil.mem[j][k]);
                fprintf(file, "%c", lp.contents[i].fotoProfil.SimbolProfil.mem[j][k]);
                if (k != lp.contents[i].fotoProfil.SimbolProfil.colEff - 1) fputs(" ", file);
            } if (j != lp.contents[i].fotoProfil.SimbolProfil.rowEff - 1) fputs("\n", file);
        } i++;
    } int j, lenPermintaan = 0;
    for (i = 0; i < gp.banyakOrang; i++){
        for(j = 0; j < gp.banyakOrang; j++){
            if (j == 0) fprintf(file, "\n%c", gp.matrixPertemanan.mem[i][j]);
            else fprintf(file, " %c", gp.matrixPertemanan.mem[i][j]);
        } 
    } i = 0; infotype tumbal; PrioQueueChar pqctumbal;
    while(lp.contents[i].index != MARK_STATIK){
        if (!IsEmptyQueue(lp.contents[i].permintaanTeman)) lenPermintaan+=NBElmtQueue(lp.contents[i].permintaanTeman);
        i++;
    } fprintf(file, "\n%d", lenPermintaan);
    j = 0, i = 0; 
    while(j < lenPermintaan){
        if (!IsEmptyQueue(lp.contents[i].permintaanTeman)){
            // 0 1 0 == id 0 meminta pertemanan ke id 1, dengan 0 popularitas
            pqctumbal = lp.contents[i].permintaanTeman;
            while(!IsEmptyQueue(pqctumbal)){
                Dequeue(&pqctumbal, &tumbal);
                fprintf(file, "\n%d %d %d", tumbal.id, i, tumbal.popularity);
                j++;
            }   
        } i++;
    } fputs("\n", file);
    fclose(file);
}

void saveDraft(char* fileName, ListPengguna lp){
    FILE *file = fopen(fileName, "w");
    int i = 0, len = 0;
    while(lp.contents[i].index != MARK_STATIK){
        if (!IsEmptyStackDraf(lp.contents[i].stackdraf)) len++;
        i++;
    } fprintf(file, "%d", len); i = 0;
    while(lp.contents[i].index != MARK_STATIK){
        if (!IsEmptyStackDraf(lp.contents[i].stackdraf)){
            StackDraf temp = lp.contents[i].stackdraf; 
            ElTypeDraf tempdraf; int length = 0;
            fprintf(file, "\n%s %d", lp.contents[i].username, LengthStackDraf(temp));
            while (!IsEmptyStackDraf(temp)){
                PopStackDraf(&temp, &tempdraf);
                fprintf(file, "\n%s", tempdraf.text);
                fprintf(file, "\n%02d/%02d/%04d %02d:%02d:%02d", tempdraf.localtime.DD, tempdraf.localtime.MM, tempdraf.localtime.YYYY, tempdraf.localtime.T.HH, tempdraf.localtime.T.MM, tempdraf.localtime.T.SS);
            }
        } i++;
    } fputs("\n", file);
    fclose(file);
}

void saveUtas(char* fileName, ListPengguna listPengguna, ListKicau listKicau, AddressListUtas listUtas){
    FILE *file = fopen(fileName, "w");
    int len = ListUtaslength(listUtas);
    fprintf(file, "%d", len); 
    AddressListUtas curr = listUtas;
    int i = 0; for(i = 0; i < len; i++){
        fprintf(file, "\n%d", curr->idKicau);
        fprintf(file, "\n%d", utasLength(curr->utas->next));
        AddressUtas currU = curr->utas;
        currU = currU->next;
        while(currU != NULL){
            fprintf(file, "\n%s", currU->info.text);
            fprintf(file, "\n%s", cariPenggunaID((currU->info.idAuthor), listPengguna).username);
            fprintf(file, "\n%02d/%02d/%04d %02d:%02d:%02d", currU->info.localtime.DD, currU->info.localtime.MM, currU->info.localtime.YYYY, currU->info.localtime.T.HH, currU->info.localtime.T.MM, currU->info.localtime.T.SS);
            currU = currU->next;
        } curr = curr->next;
    } fputs("\n", file);
    fclose(file);
}

void saveAll(ListKicau lk, ListPengguna lp, AddressListUtas lu, GrafPertemanan gp){
    char* dirName = (char*)malloc(sizeof(char)*(100));
    printf("Masukkan nama folder penyimpanan\n");
    int curLen = 0; Word dirWord = ReadWord();
    while(curLen < dirWord.Length){
        dirName[curLen] = dirWord.TabWord[curLen]; curLen++;
    } dirName[curLen] = '\0';
    if (!isExist(dirName)){
        printf("belum terdapat %s. Akan dilakukan pembuatan %s terlebih dahulu.\n", dirName, dirName);
        printf("\n Mohon tunggu...");
        mkdir(dirName, 0777);
        printf("\n1...\n2...\n3...\n\n%s sudah berhasil dibuat.", dirName);
    } 
    printf("\nAnda akan melakukan penyimpanan di %s.\n", dirName);
    printf("\n Mohon tunggu...\n");
    saveBalasan(concatCharPtr(dirName, "/balasan.config"), lk, lp);
    printf("1...\n");
    saveDraft(concatCharPtr(dirName, "/draf.config"), lp);
    saveKicauan(concatCharPtr(dirName, "/kicauan.config"), lk, lp);
    printf("2...\n");
    savePengguna(concatCharPtr(dirName, "/pengguna.config"), lp, gp);
    saveUtas(concatCharPtr(dirName, "/utas.config"), lp, lk, lu);
    printf("3...\n");
    printf("\nPenyimpanan telah berhasil dilakukan!\n");
}

void loadAll(ListPengguna *listPengguna, GrafPertemanan *pertemanan, ListKicau *listKicau, AddressListUtas *listUtas, DatabaseTagar *databaseTagar){
    char* dirName = (char*)malloc(sizeof(char)*(100));
    printf("Masukkan nama folder yang hendak dimuat: ");
    int curLen = 0; Word dirWord = ReadWord();
    while(curLen < dirWord.Length){
        dirName[curLen] = dirWord.TabWord[curLen]; curLen++;
    } dirName[curLen] = '\0';
    if (!isExist(dirName)){
        printf("\nTidak ada folder yang dimaksud!\n"); return;
    } else{
        CreateListPengguna(listPengguna); createGrafPertemanan(pertemanan, 0); CreateListKicau(listKicau, 100); CreateListUtas(listUtas);
        printf("\nAnda akan melakukan pemuatan dari %s.\n", dirName);
        printf("\nMohon tunggu...\n");
        printf("1...\n");
        printf("2...\n");
        printf("3...\n");
        readPenggunaConfig(concatCharPtr(dirName, "/pengguna.config"), listPengguna, pertemanan);
        readKicauanConfig(concatCharPtr(dirName, "/kicauan.config"), listKicau, *listPengguna);
        readBalasanConfig(concatCharPtr(dirName, "/balasan.config"), listKicau, *listPengguna);
        readDrafConfig(concatCharPtr(dirName, "/draf.config"), listPengguna);
        readUtasConfig(concatCharPtr(dirName, "/utas.config"), *listPengguna, listKicau, listUtas);
        printf("\nPemuatan selesai!\n");
        createDatabaseTagar(databaseTagar);
    } 

}