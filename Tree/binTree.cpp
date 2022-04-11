#include "Tree.h"

SearchTree build() {
    SearchTree T = new (TreeNode);

    if(T) {
        T -> Element = 5;
        T -> right = T -> left = NULL;
        return T;
    }
    return NULL;
}

int main() {
    SearchTree T = build();
    Insert(6,T);
    Insert(4,T);
    Insert(3,T);
    Insert(8,T);
    Insert(9,T);
    Insert(1,T);
    SearchTree min = FindMax(T);
    printf("%d\n", min -> Element);
}