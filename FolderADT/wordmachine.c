#include <stdio.h>
#include <stdbool.h>
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
            currentWord.TabWord[currentWord.Length] = currentChar;
            currentWord.Length += 1;
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
    if (currentChar == '\n')
    { // to consume enter
        ADV();
    }
    currentWord.Length = 0;
    while (currentChar != MARK)
    {
        if (currentWord.Length < NMax)
        { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length] = currentChar;
            currentWord.Length += 1;
            ADV();
        }
        else
            break;
    }
    currentWord.TabWord[currentWord.Length] = '\0';
    return currentWord;
}

Word ReadCommands()
{
    ADVWORD(false); // membuang word terakhir setelah membaca file

    STARTWORD(stdin, false);

    return removeFirstChar(currentWord); // membuang '\n' di awal
}

boolean wordStringCompare(Word w, char command[])
{
    int i = 0;
    int lengthCommand = 0;
    while (command[lengthCommand] != '\0')
    {
        lengthCommand += 1;
    }
    if (w.Length != lengthCommand)
    {
        return false;
    }
    while (command[i] != '\0')
    {
        if (w.TabWord[i] != command[i])
        {
            return false;
        }
        i += 1;
    }
    return true;
}

int stringLength(char inputString[])
{
    int lengthString = 0;
    while (inputString[lengthString] != '\0')
    {
        lengthString += 1;
    }
    return lengthString;
}

void transferWordToString(char inputString[], Word w)
{
    int i;
    for (i = 0; i < w.Length; i++)
    {
        inputString[i] = w.TabWord[i];
    }
    inputString[w.Length] = '\0';
}

void transferStringToString(char inputString[], char targetString[])
{
    int i;
    for (i = 0; i < stringLength(inputString); i++)
    {
        targetString[i] = inputString[i];
    }
    targetString[stringLength(inputString)] = '\0';
}

boolean stringStringCompare(char string1[], char string2[])
{
    if (stringLength(string1) != stringLength(string2))
    {
        return false;
    }
    else
    {
        int i;
        for (i = 0; string1[i] != 0; i++)
        {
            if (string1[i] != string2[i])
            {
                return false;
            }
        }
    }
    return true;
}

void displayArrayOfChar(char string[])
{
    int i;
    for (i = 0; i < stringLength(string); i++)
    {
        printf("%c", string[i]);
    }
}

boolean isInteger(Word w, int *totalNumber)
{
    int i;
    int number = 0;
    for (i = 0; i < w.Length; i++)
    {
        if ((int)w.TabWord[i] < 48 || (int)w.TabWord[i] > 57)
        {
            return false;
        }
        else
        {
            number *= 10;
            number += w.TabWord[i] - '0';
        }
    }
    *totalNumber = number;
    return true;
}

Word removeFirstChar(Word w)
{
    int i;
    for (i = 1; i < w.Length; i++)
    {
        w.TabWord[i - 1] = w.TabWord[i];
    }
    w.Length -= 1;
    return w;
}