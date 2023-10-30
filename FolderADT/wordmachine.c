#include <stdio.h>
#include "wordmachine.h"
#include "boolean.h"
#include "charmachine.h"

boolean EndWord;
Word currentWord;
boolean isNewLine;

void IgnoreBlanks(boolean file)
{
    /* Mengabaikan satu atau beberapa BLANK
       I.S. : currentChar sembarang
       F.S. : (currentChar ≠ BLANK dan currentChar != NEWLINE) atau currentChar = MARK */
    isNewLine = false;
    if (!file)
    {
        while (currentChar == BLANK || currentChar == NEWLINE)
        {
            if (currentChar == NEWLINE && !EOP)
            {
                isNewLine = true;
            }
            ADV();
        }
    }
    else
    {
        if (currentChar == BLANK || currentChar == NEWLINE)
        {
            if (!EOP)
            {
                isNewLine = true;
            }
            ADV();
        }
    }
}

void STARTWORD(FILE *input, boolean file)
{
    /* I.S. : currentChar sembarang
       F.S. : EndWord = true, dan currentChar = MARK;
              atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
              currentChar karakter pertama sesudah karakter terakhir kata */
    START(input, file);
    IgnoreBlanks(file);
    if (isNewLine || EOP)
    {
        EndWord = true;
    }
    else if (file)
    {
        EndWord = false;
        CopyLine();
    }
    else
    {
        EndWord = false;
        CopyWord();
    }
}

void ADVWORD(boolean file)
{
    /* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
       F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
              currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
              Jika currentChar = MARK, EndWord = true.
       Proses : Akuisisi kata menggunakan procedure CopyWord */
    IgnoreBlanks(file);
    if (EOP)
    {
        EndWord = true;
    }
    else if (file)
    {
        EndWord = false;
        CopyLine();
    }
    else
    {
        EndWord = false;
        CopyWord();
    }
}

void CopyWord()
{
    /* Mengakuisisi kata, menyimpan dalam currentWord
       I.S. : currentChar adalah karakter pertama dari kata
       F.S. : currentWord berisi kata yang sudah diakuisisi;
              currentChar = BLANK atau currentChar = MARK;
              currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
              Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
    currentWord.Length = 0;
    while (currentChar != MARK && currentChar != EOF && currentChar != BLANK)
    {
        if (currentWord.Length < NMax)
        { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length++] = currentChar;
            ADV();
        }
        else
            break;
    }
}

void CopyLine()
{
    int i = 0;
    currentWord.Length = 0;

    while (currentChar != NEWLINE && currentChar != EOF)
    {
        if (currentWord.Length < NMax)
        {
            currentWord.TabWord[i] = currentChar;
            ADV();
            i++;
        }
        else
            break;
    }
    currentWord.Length = i;
}

Word ReadWord()
{
    START(stdin, false);
    currentWord.Length = 0;
    while (currentChar != MARK)
    {
        if (currentWord.Length < NMax)
        { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length++] = currentChar;
            ADV();
        }
        else
            break;
    }
    currentWord.TabWord[currentWord.Length] = '\0';
    return currentWord;
}