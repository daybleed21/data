#ifndef _AvlTree_H
#define _AvlTree_H
#include <stdlib.h>
#include <stdio.h>
typedef struct AvlNode AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;
typedef int ElementType;
AvlTree MakeEmpty(AvlTree T);
Position Find(ElementType x, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType x, AvlTree T);
AvlTree Delete(AvlTree T, ElementType x);
static int Height(Position p);
static Position RR_Rotation(Position k2);
static Position LL_Rotation(Position k2);
static Position RL_Rotation(Position k3);
static Position LR_Rotation(Position k3);
void preOrder_Traverse(Position p);
int Max(int a, int b);
int getBalance(AvlTree T);
#endif
int Max(int a, int b)
{
    return a > b ? a : b;
}


typedef struct AvlNode
{
    ElementType Element;
    AvlTree left;
    AvlTree right;
    int Height;
} AvlNode;
// return the height of avltree
static int Height(Position p)
{
    if (p == NULL)
        return -1;
    else
        return p->Height;
}
int getBalance(AvlTree T)
{
    if(T == NULL)
        return 0;
    return Height(T -> left) - Height(T -> right);
}
AvlTree MakeEmpty(AvlTree T)
{
    if (T == NULL)
        return NULL;
    MakeEmpty(T->left);
    MakeEmpty(T->right);
    free(T);
}
Position Find(ElementType x, AvlTree T)
{
    if (T == NULL)
        return NULL;
    if (T->Element == x)
        return T;
    else if (T->Element > x)
        return Find(x, T->left);
    else if (T->Element < x)
        return Find(x, T->right);
}
Position FindMin(AvlTree T)
{
    if (T == NULL)
        return NULL;
    while (T->left)
    {
        T = T->left;
    }
    return T;
}
Position FindMax(AvlTree T)
{
    if (T == NULL)
        return NULL;
    else if (T->right)
        return FindMax(T->right);
    else
        return T;
}

AvlTree Insert(ElementType x, AvlTree T)
{
    if (T == NULL)
    {
        // Create and return a one-node tree
        T = (AvlTree)malloc(sizeof(AvlNode));
        if (T == NULL)
        {
            printf("out of space");
            return NULL;
        }
        else
        {
            T->Element = x;
            T->Height = 0;
            T->left = T->right = NULL;
        }
    }
    else if (x < T->Element)
    {
        T->left = Insert(x, T->left);

        if (Height(T->left) - Height(T->right) == 2)
        {
            if (x < T->left->Element)
                T = LL_Rotation(T);
            else
                T = LR_Rotation(T);
        }
    }
    else if (x > T->Element)
    {
        T->right = Insert(x, T->right);
        if (Height(T->right) - Height(T->left) == 2)
        {
            if (x > T->right->Element)
                T = RR_Rotation(T);
            else
                T = RL_Rotation(T);
        }
    }
    // else x is in the tree already, do nothing
    T->Height = Max(Height(T->left), Height(T->right)) + 1;
    return T;
}

AvlTree Delete(AvlTree T, ElementType x)
{
    if (T == NULL)
        return T;
    if (x < T->Element)
        T->left = Delete(T->left, x);
    else if (x > T->Element)
        T->right = Delete(T->right, x);
    // the node to be deleted
    else
    {
        if (T->left == NULL || T->right == NULL)
        {
            AvlTree temp = T->left ? T->left : T->right;
            // no child case
            if (temp == NULL)
            {
                free(T);
                return NULL;
            }
            else
            {
                // one child case
                free(T);
                return temp;
            }
        }
        else
        {
            // node with two children
            //  get the inorder successor
            AvlTree temp = FindMin(T->right);
            T->Element = temp->Element;
            T->right = Delete(T->right, T->Element);
        }
    }
    // update the hegiht of the current root
    T->Height = Max(Height(T->left), Height(T->right)) + 1;
    //get the balance factor of this node
    int balance = getBalance(T);
    //Left Left case
    if(balance > 1 && getBalance(T -> left) >= 0)
        return LL_Rotation(T);
    //Left Right case
    else if(balance > 1 && getBalance(T -> left) < 0)
        return LR_Rotation(T);
    //Right Right case
    else if(balance < -1 && getBalance(T -> right) >= 0)
        return RR_Rotation(T);
    //Right Left case
    else if(balance < -1 && getBalance(T -> right) < 0)
        return RL_Rotation(T);
    
    return T;
}
/*LLR. This function can be called only if k2 has a left child
 *  perform a rotate beeween a node(k2) and its left child
 *  update heights ,then return new root.
 */
static Position LL_Rotation(Position k2)
{
    Position k1;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->Height = Max(Height(k2->left), Height(k2->right)) + 1;
    k1->Height = Max(Height(k1->left), Height(k1->right)) + 1;

    return k1; // new root
}
// RRL
static Position RR_Rotation(Position k2)
{
    Position k1;
    k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    k2->Height = Max(Height(k2->left), Height(k2->right)) + 1;
    k1->Height = Max(Height(k1->left), Height(k1->right)) + 1;

    return k1; // new root
}
// RL 1.R -> RR 2. L
static Position RL_Rotation(Position k3)
{
    // rotate between k1 and k2
    k3->right = LL_Rotation(k3->right);

    // rotate between k3 and k2
    return RR_Rotation(k3);
}
// LR 1. L -> LL 2. R
static Position LR_Rotation(Position k3)
{
    // rotate between k1 and k2
    k3->left = RR_Rotation(k3->left);

    // rotate between k2 and k3
    return LL_Rotation(k3);
}
void preOrder_Traverse(Position p)
{
    if (p == NULL)
        return;
    printf("%d ", p->Element);
    preOrder_Traverse(p->left);
    preOrder_Traverse(p->right);
}
