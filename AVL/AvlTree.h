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
static Position SingleRotateToLeft(Position k2);
static Position SingleRotateToRight(Position k2);
static Position DoubleRotateToLeft(Position k3);
static Position DoubleRotateToRight(Position k3);
void preOrder_Traverse(Position p);
int Max(int a, int b);
#endif
int Max(int a, int b) {
    return a > b ? a : b;
}

typedef struct AvlNode {
    ElementType Element;
    AvlTree left;
    AvlTree right;
    int Height;
} AvlNode;
//return the height of avltree
static int Height(Position p) {
    if(p == NULL)
        return -1;
    else
        return p -> Height;
}
AvlTree MakeEmpty (AvlTree T){
    if(T == NULL)
        return NULL;
    MakeEmpty(T -> left);
    MakeEmpty(T -> right);
    free(T);
}
Position Find (ElementType x, AvlTree T) {
    if(T == NULL)
        return NULL;
    if(T -> Element == x)
        return T;
    else if(T -> Element > x)
        return Find(x, T -> left);
    else if(T -> Element < x)
        return Find(x, T -> right);
}
Position FindMin(AvlTree T) {
    if(T == NULL)
        return NULL;
    while(T -> left) {
        T = T -> left;
    }
    return T;
}
Position FindMax(AvlTree T) {
    if(T == NULL)
        return NULL;
    else if(T -> right)
        return FindMax(T -> right);
    else
        return T;
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
                    T = SingleRotateToRight(T);
                else
                    T = DoubleRotateToRight(T);
        }
    } else if (x > T -> Element) {
        T -> right = Insert(x, T -> right);
        if(Height(T -> right) - Height(T -> left) == 2) {
            if(x > T -> right -> Element)
                T = SingleRotateToLeft(T);
            else
                T = DoubleRotateToLeft(T);
        }
    }
    // else x is in the tree already, do nothing
    T -> Height = Max(Height(T -> left), Height(T -> right)) + 1;
    return T;
}
AvlTree Delete(ElementType x, AvlTree T) {
    AvlTree SNode = NULL; // successor node
    AvlTree PSNode = NULL; // the parent of successor node
    AvlTree temp = NULL;

    if(T == NULL) {
        printf("not exist!\n");
        exit(0);
    } else if( x > T -> Element) {
        T -> right = Delete(x, T -> right);
        if(Height(T -> left) - Height(T ->right) > 1) {
            temp = T -> left;
            if(Height(temp -> left) >= Height(temp -> right)){
                //LL -> R
                T = SingleRotateToRight(T);
            } else {
                //LR 
                T = DoubleRotateToRight(T);
            }
        }
        T -> Height = Max(Height(T -> left), Height(T -> right)) + 1;

    } else if( x < T -> Element) {
        T -> left = Delete(x, T -> left);
        if(Height(T -> right) - Height(T -> left) > 1) {
            temp = T -> right;
            if(Height(temp -> right) >= Height(temp -> left)){
                //RR -> L
                T = SingleRotateToLeft(T);
            } else {
                //RL
                T = DoubleRotateToLeft(T);
            }
        }
        T -> Height = Max(Height(T -> left), Height(T -> right)) + 1;
    } else if(x == T -> Element) {
        if(T -> right == NULL && T -> left == NULL) {
            //if the node has no child
            free(T);
            return NULL;
        } else if(T -> right == NULL && T -> left) {
            // the node has only left child
            temp = T -> left;
            free(T);
            return temp;
        } else if(T -> right && T -> left == NULL) {
            // the node has only right child
            temp = T -> right;
            free(T);
            return temp;
        } else {
            // if the node has 2 children
            
        }
    }
}

/*LLR. This function can be called only if k2 has a left child
*  perform a rotate beeween a node(k2) and its left child
*  update heights ,then return new root.
*/
static Position SingleRotateToRight(Position k2) {
    Position k1;
    k1 = k2 -> left;
    k2 -> left = k1 -> right;
    k1 -> right = k2;

    k2 -> Height = Max(Height(k2 -> left), Height(k2 -> right)) + 1;
    k1 -> Height = Max(Height(k1 -> left), Height(k1 -> right)) + 1;
    
    return k1;  //new root
}
//RRL
static Position SingleRotateToLeft(Position k2) {
    Position k1;
    k1 = k2 -> right;
    k2 -> right = k1 -> left;
    k1 -> left = k2;

    k2 -> Height = Max(Height(k2 -> left), Height(k2 -> right)) + 1;
    k1 -> Height = Max(Height(k1 -> left), Height(k1 -> right)) + 1;
    
    return k1;  //new root
}
//RL 1.R -> RR 2. L
static Position DoubleRotateToLeft(Position k3) {
    //rotate between k1 and k2
    k3 -> right = SingleRotateToRight(k3 -> right);

    // rotate between k3 and k2
    return SingleRotateToLeft(k3);
}
// LR 1. L -> LL 2. R
static Position DoubleRotateToRight(Position k3) {
    //rotate between k1 and k2
    k3 -> left = SingleRotateToLeft(k3 -> left);

    // rotate between k2 and k3
    return SingleRotateToRight(k3);
}
void preOrder_Traverse(Position p) {
    if(p == NULL)
        return;
    printf("data = %d height = %d\n", p -> Element, p -> Height);
    preOrder_Traverse(p -> left);
    preOrder_Traverse(p -> right);
}
