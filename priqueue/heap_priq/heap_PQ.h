#ifndef __HEAP_PQ_H__ 
#define __HEAP_PQ_H__

#include <stddef.h> /*size_t*/

typedef struct priority_queue pr_queue_t;

/*building a Priority Queue*/
pr_queue_t *PQCreate(int (*CmpFunc)(void *data1, void *data2));

void PQDestroy(pr_queue_t *pr_queue);

/*pushing to the Queue, accoring to the priority. returns status*/
int PQEnqueue(pr_queue_t *pr_queue, const void *data);

/*poping from front of Queue*/
void PQDequeue(pr_queue_t *pr_queue);

/*erase specific data using IsMatch function (Find & Remove)*/
void *PQErase(pr_queue_t *pr_queue, int(*IsMatch)(void *data, void *param1),void * param1);

/*peeking at item at front of Priority Queue*/
void *PQPeek(const pr_queue_t *pr_queue);

/*returns a status*/
int PQIsEmpty(const pr_queue_t *pr_queue);

/*returns number of elements in the Priority Queue*/
size_t PQCount(const pr_queue_t *pr_queue);

#endif 
