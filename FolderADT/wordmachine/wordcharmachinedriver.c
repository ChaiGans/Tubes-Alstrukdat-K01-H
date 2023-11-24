#include "charmachine.h"
#include "wordmachine.h"
#include "../boolean.h"

int main()
{
    Word kata;
    printf("Masukkan sebuah kata: ");
    kata = ReadWord();
    printf("Kata yang dimasukkan: %s\n", kata.TabWord);

    printf("Masukkan kata 'in Harmonia Progressio': ");
    kata = ReadWord();
    if (wordStringCompare(kata, "in Harmonia Progressio"))
    {
        printf("Kata yang dimasukkan: %s\n", kata.TabWord);
    }
    else
    {
        printf("Kata yang dimasukkan bukan 'in Harmonia Progressio'\n");
    }
    return 0;
}
