#include <stdio.h>
#include <stdlib.h>

typedef int ElementType ;

typedef struct TreeNode *BinTree;
typedef BinTree Postion ;

struct TreeNode
{
    ElementType Data;
    BinTree Left ; 
    BinTree Right ;
};


