#include <stdio.h>
#include <stdlib.h>
#include "treebalasan.h"
#include "listpengguna.h"
#include "grafpertemanan.h"

int main() {
    ListPengguna listpengguna;
    GrafPertemanan graf;
    Balasan balasan1, balasan2, balasan3;
    balasan1.id = 1;
    balasan1.authorID = 1;

    balasan2.id = 2;
    balasan2.authorID = 2;

    balasan3.id = 3;
    balasan3.authorID = 3;

    BinTree root = newTreeNode(balasan1);

    addChildrenAt(1, &root, balasan2);
    addChildrenAt(2, &root, balasan3);

    printf("Tree of Balasan:\n");
    displayTreeOfBalasan(1, root, 4, 0, &listpengguna, &graf);

    int searchID = 2;
    if (isIdBalasanDefined(searchID, root)) {
        printf("Balasan with ID %d is defined.\n", searchID);
    } else {
        printf("Balasan with ID %d is not defined.\n", searchID);
    }

    int targetID = 1;
    BinTree targetBalasan = BalasanFromID(targetID, root);
    if (targetBalasan != NULL) {
        printf("Balasan with ID %d found.\n", targetID);
    } else {
        printf("Balasan with ID %d not found.\n", targetID);
    }

    int deleteID = 2;
    hapusCabangBalasan(&root, deleteID);
    printf("Tree after deleting Balasan with ID %d:\n", deleteID);
    displayTreeOfBalasan(1, root, 4, 0, &listpengguna, &graf);
    
    deallocTreeNode(root);

    return 0;
}
