#include "AvlTree.h"

int main() {
    AvlTree T = NULL;
    T = Insert(9, T); 
    T = Insert(5, T); 
    T = Insert(10, T); 
    T = Insert(0, T); 
    T = Insert(6, T); 
    T = Insert(11, T); 
    T = Insert(-1, T); 
    T = Insert(1, T); 
    T = Insert(2, T); 
    preOrder_Traverse(T);

    T = Delete(T, 10);
    puts("\nafter delete");
    preOrder_Traverse(T);
}