#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* fprintf */

#include "rbst.h"
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct rbst_node rbst_node_t;
typedef enum {LEFT, RIGHT ,NUM_OF_CHILDREN} child_pos_t;
typedef int (*foreach_t)(rbst_node_t *node, int (*Action)(void *data, void *param), void *param);

/****utility functions****/
static int RBSTInserthelp(rbst_node_t *node, rbst_node_t *new_node, rbst_t *rbst, size_t height);
static void *RBSTFindhelp(rbst_node_t *node, const rbst_t *rbst, void *data);
static int rbstPreOrder(rbst_node_t *node, int (*Action)(void *data, void *param), void *param);
static int rbstPostOrder(rbst_node_t *node, int (*Action)(void *data, void *param), void *param);
static int rbstinOrder(rbst_node_t *node, int (*Action)(void *data, void *param), void *param);
static void RBSTDestroyhelp(rbst_node_t *node);
static int hasTwoChilds(rbst_node_t *node);
static void *findMinandRemove(rbst_node_t *node, rbst_node_t *parent);
static child_pos_t whichChildamI(rbst_node_t *node, rbst_node_t *parent);
static child_pos_t whichChildeIHave(rbst_node_t *node);
static child_pos_t findSide(rbst_node_t *node, void *data, int (*CmpFunc)(const void *data1, const void *data2));
static void RBSTRemovehelp(rbst_t *rbst, rbst_node_t *node, rbst_node_t *parent, void *data);
static int RBSTHeighthelp(rbst_node_t *node);
/****AVL utility functions****/
static int BalanceFactor(rbst_node_t *node);
static rbst_node_t *rightRotate(rbst_node_t *unbalancednode);
static rbst_node_t *leftRotate(rbst_node_t *unbalancednode);
static rbst_node_t *AVLbalance(rbst_node_t *node);
static int nodeHeight(rbst_node_t *node);


foreach_t Order_lut[]={rbstPreOrder, rbstinOrder, rbstPostOrder};

struct rbst_node
{
    void *data;
    rbst_node_t *children[NUM_OF_CHILDREN];
    size_t height;
}; 

struct rbst
{
  int (*CmpFunc)(const void *data1, const void *data2);
  rbst_node_t *root;
};


rbst_t *RBSTCreate (int (*CmpFunc)(const void *data1, const void *data2))
{
    rbst_t *rbst = NULL;

    rbst = (rbst_t*)malloc(sizeof(rbst_t));
    if (NULL == rbst)
    {
        fprintf(stderr, "allocation failed\n");
        return NULL;
    }

    rbst->CmpFunc = CmpFunc;
    rbst->root = NULL;

    return rbst;
}

/******************** destroy ************************/
/* void RBSTDestroy(rbst_t *rbst)
{
    rbst_t leftsubtree;
    rbst_t rightsubtree;

     if(!RBSTIsEmpty(rbst))
     {     
        leftsubtree.root = rbst->root->children[LEFT];
        rightsubtree.root = rbst->root->children[RIGHT];

        RBSTDestroy(&leftsubtree);
        RBSTDestroy(&rightsubtree);
     }
     
        free(rbst);
        rbst = NULL;

} */

void RBSTDestroy(rbst_t *rbst)
{
	
	if(!RBSTIsEmpty(rbst))
	{
 	   RBSTDestroyhelp(rbst->root);
	}

    free(rbst);
    rbst = NULL;

}

void RBSTDestroyhelp(rbst_node_t *node)
{
    if(node != NULL)
    {
        RBSTDestroyhelp(node->children[LEFT]);
        RBSTDestroyhelp(node->children[RIGHT]);
    
        free(node);
        node = NULL;
    }

}

/******************** insert ************************/

int RBSTInsert(rbst_t *rbst, void *data)
{
    rbst_node_t *new_node = NULL;

    new_node = (rbst_node_t*)malloc(sizeof(rbst_node_t));
    if (NULL == new_node)
    {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }

    new_node->data = data;
    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;
    new_node->height = 0;

    if(RBSTIsEmpty(rbst))
    {
        rbst->root = new_node;
        return 0;
    }

   return RBSTInserthelp(new_node ,rbst->root, rbst, 0);
}


static int RBSTInserthelp(rbst_node_t *new_node, rbst_node_t *node, rbst_t *rbst, size_t height)
{
    child_pos_t side = LEFT;

    if(rbst->CmpFunc(new_node->data, node->data)>0)
    {
        side = RIGHT;
    }
    
    if(node->children[side] == NULL)
    {
        node->children[side] = new_node;
        node->height = MAX(RBSTHeighthelp(node->children[LEFT]) +1 , RBSTHeighthelp(node->children[RIGHT]) +1);
       return 0;
    }

    RBSTInserthelp( new_node, node->children[side], rbst, height +1);
/* 
    node->height =  MAX(RBSTHeighthelp(node->children[LEFT]) +1 , RBSTHeighthelp(node->children[RIGHT]) +1);   */

    node->children[side] = AVLbalance(node->children[side]);  

    node->height =  MAX(RBSTHeighthelp(node->children[LEFT]) +1 , RBSTHeighthelp(node->children[RIGHT]) +1);  

    if(node == rbst->root)
    {
        node = AVLbalance(node);  
        rbst->root = node;
    }

    return 0;
}


/******************** find ************************/
/* O(h) */
void *RBSTFind(const rbst_t *rbst, void *data)
{
    rbst_node_t *node = NULL;

    assert(rbst);

    node = rbst->root;

    return RBSTFindhelp(node, rbst, data);
}

static void *RBSTFindhelp(rbst_node_t *node, const rbst_t *rbst, void *data)
{
    child_pos_t side = LEFT;

    assert(rbst);

    if(node == NULL)
    {
        return NULL;
    }
    
    if(rbst->CmpFunc(node->data, data) < 0)
    {
        side = RIGHT;
    }
    else if(rbst->CmpFunc(node->data, data) == 0)
    {
        return node->data;
    }


    return RBSTFindhelp(node->children[side], rbst, data);
}

/******************** isempty ************************/
/* O(h) */
int RBSTIsEmpty(const rbst_t *rbst)
{
    assert(rbst);

    return rbst->root == NULL;
}



/******************** height ************************/
/* O(n) */
int RBSTHeight(const rbst_t *rbst)
{
    assert(rbst);

    if(RBSTIsEmpty(rbst))
    {
        return -1;
    }

    return RBSTHeighthelp(rbst->root);
}


static int RBSTHeighthelp(rbst_node_t *node)
{
    if(node == NULL)
    {
        return -1;
    }

    return MAX(RBSTHeighthelp(node->children[LEFT]) +1 , RBSTHeighthelp(node->children[RIGHT]) +1);
}

/* size_t RBSTHeight(const rbst_t *rbst)
{
    rbst_t leftsubtree;
    rbst_t rightsubtree;
    size_t height = 0;


    rightsubtree.root = rbst->root->children[RIGHT];
    leftsubtree.root = rbst->root->children[LEFT];

    return height = (1+ (MAX(RBSTHeight(&rightsubtree), RBSTHeight(&leftsubtree))));

}
 */

/******************** count ************************/
size_t RBSTCount(const rbst_t *rbst)
{
    rbst_t leftsubtree;
    rbst_t rightsubtree;

    assert(rbst);

    if(RBSTIsEmpty(rbst))
    {
        return 0;
    }
    leftsubtree.root = rbst->root->children[LEFT];
    rightsubtree.root = rbst->root->children[RIGHT];

    return (RBSTCount(&rightsubtree) + RBSTCount(&leftsubtree) + 1); 
}

/******************** foreach ************************/
/* O(n) */
int RBSTForEach(rbst_t *rbst, int (*Action)(void *data, void *param), void *param, order_t order)
{
    assert(rbst);

    if(RBSTIsEmpty(rbst))
    {
        return 1;
    }

    return Order_lut[order](rbst->root, Action, param);
}

/* root -> left -> right */
static int rbstPreOrder(rbst_node_t *node, int (*Action)(void *data, void *param), void *param)
{
    int status = 0;

    if(node != NULL)
    {
        status = Action(node->data, param);

        if(rbstPreOrder(node->children[LEFT], Action, param))
        {
            return status;
        }
        if(rbstPreOrder(node->children[RIGHT], Action, param))
        {
            return status;
        }
    }
    return status;
}


/* left -> right -> root */
static int rbstPostOrder(rbst_node_t *node, int (*Action)(void *data, void *param), void *param)
{
    int status = 0;

     if(node != NULL)
     {     
         if(rbstPostOrder(node->children[LEFT], Action, param))
         {
             return status;
         }
         if(rbstPostOrder(node->children[RIGHT], Action, param))
         {
             return status;
         }
         status = Action(node->data, param);
     }
     return status;

}


/* left -> root -> right */
static int rbstinOrder(rbst_node_t *node, int (*Action)(void *data, void *param), void *param)
{
    int status = 0;

    if(node != NULL)
    {
        if(rbstinOrder(node->children[LEFT], Action, param))
        {
            return status;
        }
        status = Action(node->data, param);
        if(rbstinOrder(node->children[RIGHT], Action, param))
        {
            return status;
        }

    }
    return status;
}


/******************** remove ************************/
/* O(h) */
void RBSTRemove(rbst_t *rbst, void *data)
{
    assert(rbst);

    if(RBSTIsEmpty(rbst))
    {
        return;
    }

    if(RBSTCount(rbst) == 1)
    {
        free(rbst->root);
        rbst->root = NULL;
        return;
    }

    if((RBSTCount(rbst) == 2) && (rbst->CmpFunc(data, rbst->root->data)== 0))
    {
        rbst_node_t *node = rbst->root;
        rbst->root = node->children[whichChildeIHave(node)];
        free(node);
        node = NULL;
        return;
    }

    RBSTRemovehelp(rbst, rbst->root, NULL, data);
}


static void RBSTRemovehelp(rbst_t *rbst, rbst_node_t *node, rbst_node_t *parent, void *data)
{
    child_pos_t side = RIGHT;

    if(rbst->CmpFunc(node->data, data)==0)
    {
        if(hasTwoChilds(node))
        {
            node->data = findMinandRemove(node->children[RIGHT], node);
        }
        else
        {
            parent->children[whichChildamI(node,parent)] = node->children[whichChildeIHave(node)];
            free(node);
            node = NULL;
            return;
        }
    }
    else
    {
        side = findSide(node, data, rbst->CmpFunc);
        RBSTRemovehelp(rbst, node->children[side], node, data);
    }

    node->children[side] = AVLbalance(node->children[side]);  
    
    node->height =  MAX(RBSTHeighthelp(node->children[LEFT]) +1 , RBSTHeighthelp(node->children[RIGHT]) +1);  

    if(node == rbst->root)
    {
        node = AVLbalance(node);  
        rbst->root = node;
    }

    return;
    
}

/******************** morefuncs ************************/

static void *findMinandRemove(rbst_node_t *node, rbst_node_t *parent)
{
    void *data = NULL;
    if(node->children[LEFT] == NULL)
    {
        parent->children[whichChildamI(node, parent)] = node->children[RIGHT];
        data = node->data;
        free(node);
        node = NULL;
        return data;
    }

    return findMinandRemove(node->children[LEFT], node);
}


static int hasTwoChilds(rbst_node_t *node)
{
    return (node->children[RIGHT] && node->children[LEFT]);
}


static child_pos_t findSide(rbst_node_t *node, void *data, int (*CmpFunc)(const void *data1, const void *data2))
{
    child_pos_t side = RIGHT;

    if(CmpFunc(node->data , data) > 0)
    {
        side = LEFT;
    }
    return side;
}



static child_pos_t whichChildamI(rbst_node_t *node, rbst_node_t *parent)
{
    child_pos_t side = RIGHT;

    if (parent == NULL)
    {
       return NUM_OF_CHILDREN;
    }

    if (parent->children[LEFT] == node)
    {
        side = LEFT;
    }
    
    return side;
}

static child_pos_t whichChildeIHave(rbst_node_t *node)
{
    child_pos_t side = RIGHT;

    if (node->children[LEFT] != NULL)
    {
        side = LEFT;
    }
    
    return side;
}


/* static void updateHeightandBF(rbst_node_t *node, size_t height)
{
    size_t leftnodeheight = 0;
    size_t rightnodeheight = 0;

    if(node->children[LEFT] == NULL)
    {
        leftnodeheight = -1;
    } 
    else
    {
        leftnodeheight = node->children[LEFT]->height;
    }
    if(node->children[RIGHT] == NULL)
    {
        rightnodeheight = -1;
    }
    else
    {
        rightnodeheight = node->children[RIGHT]->height;
    }
} */

/******************** AVL ************************/

static int BalanceFactor(rbst_node_t *node)
{
    if(node == NULL)
    {
        return -1;
    }
    
    
    return nodeHeight(node->children[LEFT]) - nodeHeight(node->children[RIGHT]);
}


static rbst_node_t *rightRotate(rbst_node_t *unbalancednode)
{
    rbst_node_t *leftchild = unbalancednode->children[LEFT];
    rbst_node_t *grandchild = leftchild->children[RIGHT];

    /* rotate*/
    leftchild->children[RIGHT] = unbalancednode;
    unbalancednode->children[LEFT] = grandchild;

    /*update heights */
    unbalancednode->height = RBSTHeighthelp(unbalancednode);
    leftchild->height = RBSTHeighthelp(leftchild);

    /*return new root */
    return leftchild;

}

static rbst_node_t *leftRotate(rbst_node_t *unbalancednode)
{
    rbst_node_t *rightchild = unbalancednode->children[RIGHT];
    rbst_node_t *grandchild = rightchild->children[LEFT];

    /* rotate */
    rightchild->children[LEFT] = unbalancednode;
    unbalancednode->children[RIGHT] = grandchild;
    
    /* update height */
    unbalancednode->height = RBSTHeighthelp(unbalancednode);
    rightchild->height = RBSTHeighthelp(rightchild);

    return rightchild;
}


static rbst_node_t *AVLbalance(rbst_node_t *node)
{
    /*left left case */
     if((BalanceFactor(node) > 1) && (BalanceFactor(node->children[LEFT])>=0))
    {
        return rightRotate(node);
    } 
    /* right right case */
    if((BalanceFactor(node) < -1) && (BalanceFactor(node->children[RIGHT])<=0))
    {
        return leftRotate(node);
    } 
    /* left-right case */
    if((BalanceFactor(node) > 1) && (BalanceFactor(node->children[LEFT])<0) )
    {
        node->children[LEFT] = leftRotate(node->children[LEFT]);
        return rightRotate(node);
    } 
    /* right left case */
    if((BalanceFactor(node) < -1) && (BalanceFactor(node->children[RIGHT])>0))
    {
        node->children[RIGHT] = rightRotate(node->children[RIGHT]);
        return leftRotate(node);
    } 
return node;
}



static int nodeHeight(rbst_node_t *node)
{
     if(NULL == node)
    {
        return -1;
    } 
    return node->height;
}


 /*   switch(BalanceFactor(node))
    {
        case 2:
        {
            if(BalanceFactor(node->children[LEFT])>=0)
            {
                return rightRotate(node);   
            }
            else
            {                                   
                node->children[LEFT] = leftRotate(node->children[LEFT]);
                return rightRotate(node);
            }
        }
        case -2:
        {
            if(BalanceFactor(node->children[RIGHT])<=0)
            {
                return leftRotate(node); 
            }
            else
            {
                node->children[RIGHT] = rightRotate(node->children[RIGHT]);
                return leftRotate(node);  
            }
        }
    }
    return node;
} */
