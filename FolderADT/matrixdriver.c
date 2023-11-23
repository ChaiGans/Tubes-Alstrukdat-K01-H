#include <stdio.h>
#include "matrix.h"

void testMatrix()
{
    Matrix m1, m2, hasil;
    ElType skalar = 2;

    createMatrix(3, 3, &m1);
    createMatrix(3, 3, &m2);

    printf("Matriks 1:\n");
    readMatrix(&m1, 3, 3);
    printf("Matriks 2:\n");
    readMatrix(&m2, 3, 3);

    printf("\nMatriks 1:\n");
    displayMatrix(m1);
    printf("\nMatriks 2:\n");
    displayMatrix(m2);

    printf("\nApakah Matriks 1 matriks persegi? %s\n", isSquare(m1) ? "Ya" : "Tidak");
    printf("Apakah Matriks 2 matriks persegi? %s\n", isSquare(m2) ? "Ya" : "Tidak");

    printf("\nApakah Matriks 1 simetris? %s\n", isSymmetric(m1) ? "Ya" : "Tidak");
    printf("Apakah Matriks 2 simetris? %s\n", isSymmetric(m2) ? "Ya" : "Tidak");

    printf("\nApakah Matriks 1 matriks identitas? %s\n", isIdentity(m1) ? "Ya" : "Tidak");
    printf("Apakah Matriks 2 matriks identitas? %s\n", isIdentity(m2) ? "Ya" : "Tidak");

    printf("\nDeterminan Matriks 1: %.2f\n", determinant(m1));
    printf("Determinan Matriks 2: %.2f\n", determinant(m2));

    printf("\nTranspose Matriks 1:\n");
    hasil = transpose(m1);
    displayMatrix(hasil);

    printf("\nTranspose Matriks 2:\n");
    hasil = transpose(m2);
    displayMatrix(hasil);

    printf("\nNegasi Matriks 1:\n");
    hasil = negation(m1);
    displayMatrix(hasil);

    printf("\nNegasi Matriks 2:\n");
    hasil = negation(m2);
    displayMatrix(hasil);

    printf("\nMatriks 1 + Matriks 2:\n");
    hasil = addMatrix(m1, m2);
    displayMatrix(hasil);

    printf("\nMatriks 1 - Matriks 2:\n");
    hasil = subtractMatrix(m1, m2);
    displayMatrix(hasil);

    printf("\nMatriks 1 * Matriks 2:\n");
    hasil = multiplyMatrix(m1, m2);
    displayMatrix(hasil);

    printf("\nMatriks 1 dikalikan dengan skalar:\n");
    hasil = multiplyByConst(m1, skalar);
    displayMatrix(hasil);
}

int main()
{
    testMatrix();
    return 0;
}
