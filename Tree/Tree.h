#ifndef _Tree_H
#define _Tree_H

#include<stdio.h>
#include<stdlib.h>
struct TreeNode;
typedef int ElementType;
typedef struct TreeNode* Position;
typedef struct TreeNode* SearchTree;

SearchTree MakeEmpty(SearchTree T);
Position Find( ElementType x, SearchTree T);
Position FindMin( SearchTree T);
Position FindMax( SearchTree T);
SearchTree Insert( ElementType x, SearchTree T);
SearchTree Delete( ElementType x, SearchTree T);
ElementType Retrieve( Position p);
#endif

struct TreeNode
{
    ElementType Element;
    Position left;
    Position right;
};

SearchTree MakeEmpty( SearchTree T) {
    if( T != NULL) {
        MakeEmpty(T -> left);
        MakeEmpty(T -> right);
        free(T);
    }
    return NULL;
}
Position Find( ElementType x, SearchTree T) {
    if(T == NULL)
        return NULL;
    if (T -> Element > x) {
        return Find(x, T -> left);
    } else {
        return Find(x, T -> right);
    }
        return T;
}
// recurisive
Position FindMin( SearchTree T) {
    if(T == NULL) {
        return NULL;
    } else if( T -> left == NULL) {
        return T;
    } else {
        return FindMin( T -> left);
    }
}
// iterarion
Position FindMax( SearchTree T) {
    //tree is not null
    if(T) {
        while (T -> right) {
            T = T -> right;
        }
    }
    return T;
}
SearchTree Insert( ElementType x, SearchTree T) {
    if(T == NULL) {
        // Create and return a one-node tree
        T = new(TreeNode);
        if(T == NULL) {
            printf("out of space\n");
            return NULL;
        } else {
            T -> Element = x;
            T -> left = T -> right = NULL;
        }
    //T is not null
    } else if (x < T -> Element) {
        T -> left = Insert(x, T -> left);
    } else if (x > T -> Element) {
        T -> right = Insert(x, T -> right);
    }// if x is in the tree, do nothing
    return T;
}
             
/* we need to reconstruct the tree
*  case 1 the node has no child
*  case 2 the node has 1 child 
*  case 3 the node has 2 children
 */ 
SearchTree Delete( ElementType x, SearchTree T) {
    Position p;
    if(T == NULL) {
        printf("Element not found!\n");
        return NULL;
    } else if (x < T -> Element) {
        T -> left = Delete(x, T -> left);
    } else if (x > T -> Element) {
        T -> right = Delete(x, T -> right);
    } else if (T -> left && T -> right) {
        // found the node in case3
        p = FindMin(T -> right);
        T -> Element = p -> Element;
        T -> right = Delete( T -> Element, T -> right);
    } else {
        //case 1 or 2
        p = T;
        if(T -> left == NULL)
            T = T -> right;
        else if( T -> right == NULL)
            T = T -> left;
        free(p);
    }
    return T;
}
