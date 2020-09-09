#ifndef __QUEUE_H__ 
#define __QUEUE_H__

#include <stddef.h> /*size_t*/
#include <stdio.h> /*printf */

typedef struct queue queue_t; 

/*building a queue*/
queue_t *QCreate();

void QDestroy(queue_t *queue);

/*pushing to back end of the queue. returns status*/
int QEnqueue(queue_t *queue, const void *data);

/*poping from queue begining*/
void Qdequeue(queue_t *queue);

/*peeking at item at front of queue*/
void *QPeek(const queue_t *queue);

/*returns a status*/
int QIsEmpty(const queue_t *queue);

/*returns number of elements in the queue*/
size_t QCount(const queue_t *queue);

#endif 
