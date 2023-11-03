# Tubes-Alstrukdat-K01-H
tes change read me

## CARA PAKE WORDMACHINE KALO MAU BACA DARI TERMINAL 
### pake `ReadCommands()` untuk baca command  
mungkin pake contoh pemakaian aja ye:  
```
Word command = ReadCommands(); // nerima input misalnya "LIHAT_PROFIL 2;"
...  
if (WordStringCompare(command, "LIHAT_PROFIL")) {
    ADVWORD(false);  
    int id = wordToInt(currentWord);
    displayProfileInformation(listPengguna.contents[id]);
}
...
```
intinya untuk akses kata selanjutnya sebelum MARK, pake `ADVWORD(false)`

### pake `ReadWord()` yang udah dibikin chai
cara pakenya 
`kataYangLuMau = ReadWord()`

## CARA PAKE WORDMACHINE KALO MAU BACA DARI FILE 
### inisiasi: `STARTWORD(<filePath>, true)`
`<filePath>` -> ngasih tau kita mau nerima pita masukan dari file yang lokasinya ada di pathFile (kalo bingung filePath kek gimana bisa liat yang readConfig pengguna)  
`true` -> ngasih tau kita mau nerima masukan dari file  
### kontinu: `ADVWORD`(true)`
`true` -> ngasih tau kita mau nerima masukan dari file  

p.s. : jangan lupa `#include "boolean.h"`  
kasih tau aja kalo masih ada yang salah dari wordmachinenya mungkin aku coba selesain 👋
