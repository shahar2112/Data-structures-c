#ifndef __BST_H__ 
#define __BST_H__

#include<stddef.h> /*size_t*/

typedef struct bst bst_t;
typedef struct bst_node bst_node_t;
typedef struct bst_iter
{
    bst_node_t *node;
}bst_iter_t;


/* O(1) */
bst_t *BSTCreate(int (*CmpFunc)(const void *data1, const void *data2));

/* O(n) */
void BSTDestroy(bst_t *bst);

/* O(h) */
bst_iter_t BSTInsert(bst_t *bst, void *data);

/* O(h) */
void BSTRemove(bst_iter_t iter);

/* O(h) */
bst_iter_t BSTFind(const bst_t *bst, void *data);

/* O(n) */
int BSTForEach(bst_t *bst, int (*Action)(void *data, void *param), void *param);

/* O(n) */
size_t BSTCount(const bst_t *bst);

/* O(h) */
int BSTIsEmpty(const bst_t *bst);

/* O(h) */
bst_iter_t BSTIterBegin(const bst_t *bst);

/* O(1) */
bst_iter_t BSTIterEnd(const bst_t *bst);

/* O(h) */
bst_iter_t BSTIterNext(bst_iter_t iter);

/* O(1) */
int BSTIterIsSameIter(bst_iter_t iter1, bst_iter_t iter2);

/* O(1) */
void *BSTIterGetData(bst_iter_t iter);

#endif
