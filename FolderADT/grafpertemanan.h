#ifndef GRAFPERTEMANAN_H
#define GRAFPERTEMANAN_H

#include "matrix.h"
#include "boolean.h"

typedef struct Grafpertemanan
{
    Matrix matrixPertemanan;
    int banyakOrang;
} GrafPertemanan;

#define ElmtGrafPertemanan(G, i, j) (G).matrixPertemanan.mem[i][j]

/* ** KREATOR ** */
void createGrafPertemanan(GrafPertemanan *G, int n);
/* I.S. G sembarang */
/* F.S. Terbentuk graf G kosong dengan n simpul */

/* ** SELEKTOR ** */
int getBanyakTeman(GrafPertemanan G, int i);
/* Mengembalikan banyaknya teman yang dimiliki oleh orang pada index ke i*/

/* ** FUNGSI LAIN ** */
boolean isTeman(GrafPertemanan G, int i, int j);
/* Mengembalikan true jika orang pada index ke i dan j berteman */

void hapusHubunganTeman(GrafPertemanan *G, int i, int j);
/* I.S. G terdefinisi, i dan j terdefinisi */
/* F.S. Orang pada index ke i dan j tidak berteman */

void displayGrafPertemanan(GrafPertemanan G);
/* I.S. G terdefinisi */
/* F.S. Matriks G ditampilkan pada layar */

boolean isMengirimPermintaan(GrafPertemanan G, int idPengirim, int idPenerima);
/* Mengembalikan true jika idPengirim mengirim permintaan pertemanan ke idPenerima */

int getBanyakPermintaanTeman(GrafPertemanan G, int idPenerima);
/* Mengembalikan banyaknya permintaan pertemanan yang diterima oleh idPenerima */
#endif

void addTeman(GrafPertemanan *G, int idPengirim, int idPenerima);
/* I.S. G terdefinisi, idPengirim dan idPenerima terdefinisi */
/* F.S. Orang pada index ke idPengirim dan idPenerima menjadi berteman */