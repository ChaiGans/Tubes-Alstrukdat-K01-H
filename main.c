#include "FolderADT/charmachine.h"
#include "FolderADT/wordmachine.h"
#include "FolderADT/data.h"
#include "features/save_load.h"
#include "features/user.h"
#include "features/draf.h"
#include "features/balasan.h"
#include "features/kicauan.h"
#include "features/utas.h"
#include "features/teman.h"

#include <stdio.h>

Word userInput;

void printASCIIART()
{
    printf("      _                     _            \n");
    printf("     | |___      _____  ___| |_ ___ _ __ \n");
    printf("     | __\\ \\ /\\ / / _ \\/ _ \\ __/ _ \\ '__|\n");
    printf("     | |_ \\ V  V /  __/  __/ ||  __/ |   \n");
    printf("      \\__| \\_/\\_/ \\___|\\___|\\__\\___|_|   \n");
    printf("                                         \n");
}

int main()
{
    printASCIIART();
    printf("Selamat datang di BurBir.\n");
    printf("Aplikasi untuk studi kualitatif mengenai perilaku manusia dengan menggunakan metode (pengambilan data berupa) Focused Group Discussion kedua di zamannya.\n");

    int currentLoginID = -1;
    ListPengguna listPengguna;
    CreateListPengguna(&listPengguna);
    GrafPertemanan grafPertemanan;
    createGrafPertemanan(&grafPertemanan, 0);
    ListKicau listKicau;
    CreateListKicau(&listKicau, 10);
    AddressListUtas listUtas;
    CreateListUtas(&listUtas);

    printf("Masukkan nama file config: ");
    Word filename = ReadWord();
    initReadConfig(filename, &listPengguna, &grafPertemanan, &listKicau, &listUtas);
    displayGrafPertemanan(grafPertemanan);
    while (true)
    {
        // printTree(listKicau.buffer[0].balasan, 2);
        printf("\n>> ");
        ADVWORD(false); // false karena mau nerima input dari terminal
        Word command = ReadCommands();

        if (currentLoginID == -1)
        {
            if (wordStringCompare(command, "MASUK"))
            {
                masukPengguna(&currentLoginID, listPengguna);
                displayNameFromID(currentLoginID, listPengguna);
            }
            else if (wordStringCompare(command, "DAFTAR"))
            {
                daftarPengguna(&listPengguna, &grafPertemanan);
            }
            else if (wordStringCompare(command, "MUAT"))
            {
                loadAll(&listPengguna, &grafPertemanan, &listKicau, &listUtas);
            } 
            else if(wordStringCompare(command, "SIMPAN"))
            {
                saveAll(listKicau, listPengguna, listUtas, grafPertemanan);
            }
            else
            {
                printf("Silakan masuk terlebih dahulu.\n");
            }
        }
        else
        {
            if (wordStringCompare(command, "UBAH_FOTO_PROFIL"))
            {
                ubahFotoProfil(&listPengguna.contents[currentLoginID]);
            }
            else if (wordStringCompare(command, "ATUR_JENIS_AKUN"))
            {
                aturJenisAkun(&listPengguna.contents[currentLoginID]);
            }
            else if (wordStringCompare(command, "GANTI_PROFIL"))
            {
                gantiProfil(&listPengguna.contents[currentLoginID]);
            }
            else if (wordStringCompare(command, "LIHAT_PROFIL"))
            {
                ADVWORD_LIHAT_PROFIL_ONLY();
                lihatProfil(currentWord, currentLoginID, listPengguna, grafPertemanan);
            }
            else if (wordStringCompare(command, "DAFTAR_TEMAN"))
            {
                displayDaftarTeman(currentLoginID, grafPertemanan, listPengguna);
            }
            else if (wordStringCompare(command, "HAPUS_TEMAN"))
            {
                hapusTeman(currentLoginID, &grafPertemanan, listPengguna);
            }
            else if (wordStringCompare(command, "TAMBAH_TEMAN"))
            {
                kirimPermintaanTeman(currentLoginID, &grafPertemanan, &listPengguna);
            }
            else if (wordStringCompare(command, "DAFTAR_PERMINTAAN_PERTEMANAN"))
            {
                displayDaftarPermintaanTeman(currentLoginID, grafPertemanan, listPengguna);
            }
            else if (wordStringCompare(command, "SETUJUI_PERTEMANAN"))
            {
                terimaPermintaanTeman(currentLoginID, &grafPertemanan, &listPengguna);
            }
            else if (wordStringCompare(command, "BUAT_DRAF"))
            {
                buatDraf(currentLoginID, &listKicau, &listPengguna);
            }
            else if (wordStringCompare(command, "LIHAT_DRAF"))
            {
                lihatDraf(currentLoginID, &listKicau, &listPengguna);
            }
            else if (wordStringCompare(command, "KELUAR"))
            {
                currentLoginID = -1;
                printf("Anda berhasil logout. Sampai jumpa di pertemuan berikutnya!\n");
            }
            else if (wordStringCompare(command, "BALAS"))
            {
                ADVWORD(false);
                int idKicau = wordToInt(currentWord);
                ADVWORD(false);
                int idBalasan = wordToInt(currentWord);
                buatBalasan(idKicau, idBalasan, currentLoginID, &listKicau, listPengguna, grafPertemanan);
            }
            else if (wordStringCompare(command, "BALASAN"))
            {
                ADVWORD(false);
                int idKicau = wordToInt(currentWord);
                lihatBalasan(currentLoginID, idKicau, listKicau, listPengguna, &grafPertemanan);
            }
            else if (wordStringCompare(command, "HAPUS_BALASAN"))
            {
                ADVWORD(false);
                int idKicau = wordToInt(currentWord);
                ADVWORD(false);
                int idBalasan = wordToInt(currentWord);
                hapusBalasan(currentLoginID, idKicau, idBalasan, &listKicau);
            }
            else if (wordStringCompare(command, "KICAU"))
            {
                upKicau(&listKicau, listPengguna, currentLoginID);
            }
            else if (wordStringCompare(command, "KICAUAN"))
            {
                kicauanTeman(currentLoginID, listPengguna, listKicau, grafPertemanan);
            }
            else if (wordStringCompare(command, "SUKA_KICAUAN"))
            {
                ADVWORD(false);
                int idKicau = wordToInt(currentWord);
                sukaKicauan(&listKicau, listPengguna, idKicau, grafPertemanan, currentLoginID);
            }
            else if (wordStringCompare(command, "KICAUAN"))
            {
                kicauanTeman(currentLoginID, listPengguna, listKicau, grafPertemanan);
            }
            else if (wordStringCompare(command, "UBAH_KICAUAN"))
            {
                ADVWORD(false);
                int idKicau = wordToInt(currentWord);
                editKicauan(currentLoginID, &listKicau, listPengguna, idKicau);
            }
            else if (wordStringCompare(command, "UTAS"))
            {
                ADVWORD(false);
                int idKicauUtas = wordToInt(currentWord);
                buatUtas(idKicauUtas, currentLoginID, &listUtas, listKicau);
            }
            else if (wordStringCompare(command, "SAMBUNG_UTAS"))
            {
                ADVWORD(false);
                int idUtas = wordToInt(currentWord);
                ADVWORD(false);
                int index = wordToInt(currentWord);
                sambungUtas(idUtas, index, currentLoginID, &listUtas, listKicau);
            }
            else if (wordStringCompare(command, "HAPUS_UTAS"))
            {
                ADVWORD(false);
                int idUtas = wordToInt(currentWord);
                ADVWORD(false);
                int index = wordToInt(currentWord);
                hapusUtas(idUtas, index, currentLoginID, &listUtas, listKicau);
            }
            else if (wordStringCompare(command, "CETAK_UTAS"))
            {
                ADVWORD(false);
                int idUtas = wordToInt(currentWord);
                cetakUtas(idUtas, currentLoginID, &listUtas, listPengguna, listKicau, grafPertemanan);
            }
            else if(wordStringCompare(command, "SIMPAN"))
            {
                saveAll(listKicau, listPengguna, listUtas, grafPertemanan);
            }
            else if (wordStringCompare(command, "TUTUP_PROGRAM"))
            {
                break;
            }
        }
    }
}
