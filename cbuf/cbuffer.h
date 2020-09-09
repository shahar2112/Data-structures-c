#ifndef __CBUFFER_H__ 
#define __CBUFFER_H__

#include <stddef.h>
#include <sys/types.h>

typedef struct circular_buffer cb_t; 

/* create a new circular buffer */
cb_t *CBCreate(size_t capacity);

/* destory the circular buffer */
void CBDestroy(cb_t *cb);

/* write to the circular buffer, count bytes, from buff */
ssize_t CBWrite(cb_t *cb, const void *buff, size_t count);

/* read from the circular buffer, count bytes, to buff */
ssize_t CBRead(cb_t *cb, void *buff, size_t count);

/* return the number of bytes remained in the circular buffer */
size_t CBFreeSpace(const cb_t *cb);

/* return the capacity of the circular buffer */
size_t CBCapacity(const cb_t *cb);

/* check if the circular buffer is empty */
int CBIsEmpty(const cb_t *cb);

#endif /* #ifndef __CBuffer_H__ */

