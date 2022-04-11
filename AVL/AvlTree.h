#ifndef _AvlTree_H
#define _AvlTree_H
#include <stdlib.h>
#include <stdio.h>
struct AvlNode;
typedef struct AvlNode* Position;
typedef struct AvlNode* AvlTree;
typedef int ElementType;
AvlTree MakeEmpty (AvlTree T);
Position Find (ElementType x, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType x, AvlTree T);
AvlTree Delete(ElementType x, AvlTree T);
static int Height(Position p);
static Position SingleRotateWithLeft(Position k2);
static Position SingleRotateWithRight(Position k2);
static Position DoubleRotateWithLeft(Position k3);
static Position DoubleRotateWithRight(Position k3);
int Max(int a, int b);
#endif
int Max(int a, int b) {
    return a > b ? a : b;
}

struct AvlNode {
    ElementType Element;
    AvlTree left;
    AvlTree right;
    int Height;
};
//return the height of avltree
static int Height(Position p) {
    if(p == NULL)
        return -1;
    else
        return p -> Height;
}

AvlTree Insert(ElementType x, AvlTree T) {
    if(T == NULL) {
        //Create and return a one-node tree
        T =(AvlTree) malloc(sizeof(struct AvlNode));
        if(T == NULL) {
            printf("out of space");
            return NULL;
        } else {
            T -> Element = x;
            T -> Height = 0;
            T -> left = T -> right = NULL;
        }
    } else if(x < T -> Element) {
        T -> left = Insert(x, T -> left);
        if(Height(T -> left) - Height(T -> right) == 2) {
            if(x < T -> left -> Element)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
        }
    } else if (x > T -> Element) {
        T -> right = Insert(x, T -> right);
        if(Height(T -> right) - Height(T -> left) == 2) {
            if(x < T -> right -> Element)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
        }
    }
    // else x is in the tree already, do nothing
    T -> Height = Max(Height(T -> left), Height(T -> right)) + 1;
    return T;
}
/* This function can be called only if k2 has a left child
*  perform a rotate beeween a node(k2) and its left child
*  update heights ,then return new root
*/
static Position SingleRotateWithLeft(Position k2) {
    Position k1;
    k1 = k2 -> left;
    k2 -> left = k1 -> right;
    k1 -> right = k2;

    k2 -> Height = Max(Height(k2 -> left), Height(k2 -> right)) + 1;
    k1 -> Height = Max(Height(k1 -> left), Height(k1 -> right)) + 1;
    
    return k1;  //new root
}
