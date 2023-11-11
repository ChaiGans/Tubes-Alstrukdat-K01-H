/* File : bintree.h */
/* ADT pohon biner */
/* Representasi Address dengan pointer */
/* Balasan adalah integer */

#ifndef POHONBINER_H
#define POHONBINER_H

#include "boolean.h"
#include "datetime.h"
#include "listpengguna.h"
#include "grafpertemanan.h"

/* Selektor */
#define ROOT(p) (p)->info
#define SIBLING(p) (p)->sibling
#define CHILDREN(p) (p)->children

typedef struct {
    int id;
    char text[280];
    int authorID;
    DATETIME time;
} Balasan;
typedef struct treeNode* Address;
typedef struct treeNode { 
   Balasan info;
   Address sibling;
   Address children;
} TreeNode;

/* Definisi PohonBiner */
/* pohon Biner kosong p = NULL */

typedef Address BinTree;

BinTree NewTree (Balasan root, BinTree left_tree, BinTree right_tree); 
/* Menghasilkan sebuah pohon biner dari root, left_tree, dan right_tree, jika alokasi berhasil 
   Menghasilkan pohon kosong (NULL) jika alokasi gagal */

void CreateTree (Balasan root, BinTree left_tree, BinTree right_tree, BinTree *p);
/* I.S. Sembarang
   F.S. Menghasilkan sebuah pohon p
   Menghasilkan sebuah pohon biner p dari akar, l, dan r, jika alokasi 
   berhasil 
   Menghasilkan pohon p yang kosong (NULL) jika alokasi gagal */

Address newTreeNode(Balasan val);
/* Alokasi sebuah address p, bernilai tidak NULL jika berhasil */
/* Mengirimkan address hasil alokasi sebuah elemen bernilai val
   Jika alokasi berhasil, maka address tidak NULL, dan misalnya 
   menghasilkan p, maka p↑.info=val, p↑.left=NULL, p↑.right=NULL 
   Jika alokasi gagal, mengirimkan NULL */

void addSiblingToRoot(Balasan Val, BinTree* targetedRoot);

void addChildrenToRoot(Balasan Val, BinTree* targetedRoot);

void addChildrenAt(int id, BinTree* treeResult, Balasan val);

int findHighestID(BinTree mainRoot);

boolean isIdBalasanDefined (int idBalasanSearch, BinTree balasan);
BinTree BalasanFromID(int idBalasanSearch, BinTree balasan);
void displayInformasiBalasan (int currentLoginID, BinTree balasan, int maxIndent, ListPengguna* listpengguna, GrafPertemanan *G);
void displayTreeOfBalasan(int currentLoginID, BinTree p, int h, int l, ListPengguna* listpengguna, GrafPertemanan *G) ;
boolean isBalasanKosong (BinTree balasan);
void deallocTreeNode (Address p);
/* I.S. p terdefinisi 
   F.S. p dikembalikan ke sistem 
   Melakukan dealokasi/pengembalian address p */

boolean isTreeEmpty (BinTree p);
/* Mengirimkan true jika p adalah pohon biner yang kosong */

boolean isOneElmt (BinTree p);
/* Mengirimkan true jika p tidak kosong dan hanya terdiri atas 1 elemen */

boolean isUnerLeft (BinTree p);
/* Mengirimkan true jika pohon biner tidak kosong, p adalah pohon unerleft: 
   hanya mempunyai subpohon kiri */

void addSiblingAt (BinTree* treeResult, Balasan Val);
boolean isUnerRight (BinTree p);
/* Mengirimkan true jika pohon biner tidak kosong, p adalah pohon unerright: 
   hanya mempunyai subpohon kanan */

boolean isBinary (BinTree p);
/* Mengirimkan true jika pohon biner tidak kosong, p adalah pohon biner: 
  mempunyai subpohon kiri dan subpohon kanan */

/* ****** Display Tree ***** */
void printPreorder(BinTree p);
/* I.S. p terdefinisi */
/* F.S. Semua simpul p sudah dicetak secara preorder: akar, pohon kiri, dan pohon kanan. 
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup (). 
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh: 
   (A()()) adalah pohon dengan 1 elemen dengan akar A
   (A(B()())(C()())) adalah pohon dengan akar A dan subpohon kiri (B()()) dan subpohon kanan (C()()) */

void printInorder(BinTree p);
/* I.S. p terdefinisi */
/* F.S. Semua simpul p sudah dicetak secara inorder: pohon kiri, akar, dan pohon kanan. 
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup (). 
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh: 
   (()A()) adalah pohon dengan 1 elemen dengan akar A
   ((()B())A(()C())) adalah pohon dengan akar A dan subpohon kiri (()B()) dan subpohon kanan (()C()) */

void printPostorder(BinTree p);
/* I.S. p terdefinisi */
/* F.S. Semua simpul p sudah dicetak secara postorder: pohon kiri, pohon kanan, dan akar. 
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup (). 
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh: 
   (()()A) adalah pohon dengan 1 elemen dengan akar A
   ((()()B)(()()C)A) adalah pohon dengan akar A dan subpohon kiri (()()B) dan subpohon kanan (()()C) */
void hapusCabangBalasan(BinTree* treeBalasan, int idTarget) ;
void printTree(BinTree p, int h);
/* I.S. p terdefinisi, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul p sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2: 
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
Note: Anda boleh membuat fungsi tambahan untuk membuat implementasi fungsi ini jika diperlukan
*/
#endif