#ifndef __RBST_H__ 
#define __RBST_H__

#include <stddef.h> /*size_t*/

typedef struct rbst rbst_t;

/* typedef int (*cmp_func_t)(const void *data1, const void *data2);
typedef int (*action_t)(void *data, void *param); */
typedef enum {PRE_ORDER, IN_ORDER, POST_ORDER} order_t;

/* O(1) */
rbst_t *RBSTCreate (int (*CmpFunc)(const void *data1, const void *data2));

/* O(n) */
void RBSTDestroy(rbst_t *rbst);

/* O(h) */
int RBSTInsert(rbst_t *rbst, void *data);

/* O(h) */
void RBSTRemove(rbst_t *rbst, void *data);

/* O(h) */
void *RBSTFind(const rbst_t *rbst, void *data);

/* O(n) */
size_t RBSTCount(const rbst_t *rbst);

/* O(h) */
int RBSTIsEmpty(const rbst_t *rbst);

/* O(n) */
int RBSTHeight(const rbst_t *rbst);

/* O(n) */
int RBSTForEach(rbst_t *rbst, int (*Action)(void *data, void *param), void *param, order_t order);

#endif
