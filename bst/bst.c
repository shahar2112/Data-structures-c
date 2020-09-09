#include "bst.h"

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* fprintf */

typedef enum {LEFT, RIGHT ,NUM_OF_CHILDREN} child_pos_t;

struct bst 
{
  bst_node_t *dummy;
  int (*CmpFunc)(const void *data1, const void *data2);
};

struct bst_node
{
    void *data;
    bst_node_t *parent;
    bst_node_t *children[NUM_OF_CHILDREN];
}; 

static bst_iter_t CreateNode(bst_iter_t curr, bst_t *bst, void *data, bst_iter_t parent);
static bst_iter_t findMin(bst_iter_t curr);
static bst_iter_t findMax(bst_iter_t curr);
static int isLeaf(bst_iter_t curr);
static child_pos_t whichSideIAm(bst_iter_t curr);
static int oneChild(bst_iter_t iter);
static child_pos_t whichSideChild(bst_iter_t curr);
static void freeIter(bst_iter_t iter);

/* O(1) */
/******************** create ************************/
bst_t *BSTCreate(int (*CmpFunc)(const void *data1, const void *data2))
{
    bst_t *bst = NULL;
    bst_node_t *first_node = NULL;

    bst = (bst_t*)malloc(sizeof(bst_t));
    if (NULL == bst)
    {
        fprintf(stderr, "allocation failed\n");
        return NULL;
    }
    
    first_node = (bst_node_t*)malloc(sizeof(bst_node_t));
    if (NULL == first_node)
    {
        fprintf(stderr, "allocation failed\n");
        free(bst);
        return NULL;
    }

    bst->dummy = first_node;
    bst->CmpFunc = CmpFunc;

    first_node->children[LEFT] = NULL;
    first_node->children[RIGHT] = NULL;
    first_node->data = NULL;
    first_node->parent = NULL;

    return bst;
}


/******************** destroy ************************/
void BSTDestroy(bst_t *bst)
{
    assert(bst);

    while(!BSTIsEmpty(bst))
    {
        BSTRemove(BSTIterBegin(bst));
    }

    free(bst->dummy);
    bst->dummy = NULL;
    free(bst);
    bst = NULL;
}

/******************** insert ************************/
bst_iter_t BSTInsert(bst_t *bst, void *data)
{
    bst_iter_t curr = BSTIterEnd(bst);
    bst_iter_t parent = BSTIterEnd(bst);
    child_pos_t side = LEFT;

    assert(bst);
    assert(data);

    /*start at root */
    parent.node = bst->dummy;
    curr.node = bst->dummy->children[LEFT];

    while(curr.node != NULL)
    {
        parent.node = curr.node;
    
         if(bst->CmpFunc(data, curr.node->data) > 0)
        {
            side = RIGHT;
        }
        else
        {
            side = LEFT;
        } 
        curr.node = curr.node->children[side];
    }    
    
    curr = CreateNode(curr, bst, data, parent);
 
    parent.node->children[side] = curr.node;

    return curr;
}

/******************** end ************************/
/* O(1) */
bst_iter_t BSTIterEnd(const bst_t *bst)
{
    bst_iter_t iter_end;

    assert(bst);

    iter_end.node = bst->dummy;

    return iter_end;
}

/******************** next ************************/
/* O(h) */
bst_iter_t BSTIterNext(bst_iter_t iter)
{
    bst_iter_t parent;

    if(iter.node->children[RIGHT])
    {
        iter.node = iter.node->children[RIGHT];
        findMin(iter);
    }
    else
    {
        parent.node = iter.node->parent;
        while(parent.node && parent.node->children[RIGHT] == iter.node)
        {
          iter.node = parent.node;
          parent.node = iter.node->parent;
        }
         iter.node = parent.node;
    }

    return iter;
}


/******************** begin ************************/
/* O(h) */
bst_iter_t BSTIterBegin(const bst_t *bst)
{
    bst_iter_t curr = BSTIterEnd(bst);

    assert(bst);

    curr.node = bst->dummy;

    return findMin(curr);
}

/******************** getdata ************************/
/* O(1) */
void *BSTIterGetData(bst_iter_t iter)
{
    /* you can't get dummy end */
     assert(iter.node->parent); 

    return iter.node->data;
}

/******************** count ************************/
/* O(n) */
size_t BSTCount(const bst_t *bst)
{
    size_t count = 0;
    bst_iter_t curr = BSTIterBegin(bst);

    assert(bst);

    for (;
        !BSTIterIsSameIter(curr, BSTIterEnd(bst));
        curr = BSTIterNext(curr))
    {
        count++;
    }
    return count;
}

/*********************same ************************/
/* O(1) */
int BSTIterIsSameIter(bst_iter_t iter1, bst_iter_t iter2)
{
    return (iter1.node == iter2.node);
}


/******************** isEmpty ************************/
/* O(h) */
int BSTIsEmpty(const bst_t *bst)
{
    assert(bst);

    return (BSTIterIsSameIter(BSTIterBegin(bst), BSTIterEnd(bst)));
}

/******************** foreach ************************/
/* O(n) */
int BSTForEach(bst_t *bst, int (*Action)(void *data, void *param), void *param)
{
    bst_iter_t curr = BSTIterEnd(bst);
    int status=0;

    assert(bst);

    for(curr = BSTIterBegin(bst);
       status==0 && !BSTIterIsSameIter(curr, BSTIterEnd(bst));
        curr = BSTIterNext(curr))
        {
            status = Action(BSTIterGetData(curr), param);
        }

    return status;
}


/******************** find ************************/
/* O(h) */
bst_iter_t BSTFind(const bst_t *bst, void *data)
{
    bst_iter_t curr = BSTIterEnd(bst);
    child_pos_t side = LEFT;
    
    assert(bst);

    curr.node = bst->dummy->children[LEFT];

    while(curr.node != NULL && curr.node->parent)
    {
        if(bst->CmpFunc(data, BSTIterGetData(curr))>0)
        {
            side = RIGHT;
        }
        else if(bst->CmpFunc(data, BSTIterGetData(curr))<0)
        {
            side = LEFT;
        }
        else
        {
            return curr;
        }   
            curr.node = curr.node->children[side];
    }

    return curr;

}


/******************** remove ************************/
/* O(h) */
void BSTRemove(bst_iter_t iter)
{
    bst_node_t *parent = NULL;
    bst_iter_t temp_iter;
    bst_iter_t scnd_temp_iter;

    child_pos_t side = LEFT;
    child_pos_t child_side = LEFT;


    while(!isLeaf(iter))
    {
     parent = iter.node->parent;
        if(oneChild(iter))
        {
            side = whichSideIAm(iter);
            child_side = whichSideChild(iter);
            parent->children[side] = iter.node->children[child_side];
            iter.node->children[child_side]->parent = parent;
           freeIter(iter);
            return;
        }
        else
        {
           bst_iter_t next_iter = BSTIterNext(iter);
           iter.node->data = BSTIterGetData(next_iter);
           iter = next_iter;
        }
    }

    
    parent = iter.node->parent;
    side = whichSideIAm(iter);
    parent->children[side] = NULL;
    freeIter(iter);
    return;

}


/******************** more funcs ************************/

/******************** createnode ************************/
static bst_iter_t CreateNode(bst_iter_t curr, bst_t *bst, void *data, bst_iter_t parent)
{
    bst_node_t *new_node = NULL;

    new_node = (bst_node_t*)malloc(sizeof(bst_node_t));
    if (NULL == new_node)
    {
        fprintf(stderr, "allocation failed\n");
        return BSTIterEnd(bst);
    }

    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;
    new_node->data = data;
    new_node->parent = parent.node;
    curr.node = new_node;

    return curr;
}

/******************** findMin ************************/
static bst_iter_t findMin(bst_iter_t curr)
{
    
    while(curr.node->children[LEFT])
    {
        curr.node = curr.node->children[LEFT];
    }

    return curr;
}

/******************** findMax ************************/
static bst_iter_t findMax(bst_iter_t curr)
{
    while(curr.node->children[RIGHT])
    {
        curr.node = curr.node->children[RIGHT];
    }
    return curr;
}

/******************** isleaf ************************/
static int isLeaf(bst_iter_t curr)
{
    return ((curr.node->children[LEFT] == NULL) &&  (curr.node->children[RIGHT] == NULL));
}

/******************** oneChild ************************/
static int oneChild(bst_iter_t iter)
{
    bst_node_t *parent = NULL;
    parent = iter.node->parent;

    return (parent->children[RIGHT] == NULL && parent->children[LEFT])
     || (parent->children[LEFT] == NULL && parent->children[RIGHT]);
}

/******************** findSide ************************/
static child_pos_t whichSideIAm(bst_iter_t curr)
{
    child_pos_t side = LEFT;

    if(curr.node->parent->children[RIGHT] == curr.node)
    {
        side = RIGHT;
    }
    return side;
}

/******************** findSide ************************/
static child_pos_t whichSideChild(bst_iter_t curr)
{
    child_pos_t side = LEFT;

    if((curr.node->children[LEFT] == NULL && curr.node->children[RIGHT]))
    {
        side = RIGHT;
    }
    return side;
}

/******************** free ************************/
static void freeIter(bst_iter_t iter)
{
    free(iter.node);
    iter.node = NULL;
}