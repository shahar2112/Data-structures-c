#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */
#include <string.h> /* memcpy */

#include "cbuffer.h" /* forward declerations */ 

#define MIN(a,b) (((a)<(b))?(a):(b))

#ifndef NDEBUG
#define DEBUG_PRINT(s) fprintf(stderr, s)
#else
#define DEBUG_PRINT(s)
#endif



struct circular_buffer
{
	char *buff; /*pointer to buffer */
	size_t write; /* holds index of start of buffer */
	/* size_t read;  holds index of end */
	size_t capacity; /* size of buffer */
	size_t size; /* the size of bytes written to the buffer */
}; /* cb_t */


/**************************************************************************/
/* create a new circular buffer */
cb_t *CBCreate(size_t capacity)
{
	
	cb_t *cb = (cb_t*)malloc(sizeof(cb_t));
	if(NULL == cb)
	{
		DEBUG_PRINT("memory allocation failed\n");
		return NULL;
	}
	cb->buff = (char*)malloc(capacity);
	if(NULL == cb->buff)
	{
		DEBUG_PRINT("memory allocation failed\n");
		free(cb);
		cb = NULL;
		return NULL;
	}

	cb->write = 0;
	/*cb->read = 0;*/
	cb->capacity = capacity;
	cb->size = 0;

	return cb;
}


/**************************************************************************/
/* destory the circular buffer */
void CBDestroy(cb_t *cb)
{
	free(cb->buff);
	cb->buff = NULL;
	free(cb);
	cb = NULL;

}

/**************************************************************************/
/* write to the circular buffer, count bytes, from buff */
ssize_t CBWrite(cb_t *cb, const void *buff, size_t count)
{
	size_t ret_count = count;
	size_t len = 0;
	
	assert(cb);
	assert(buff);
	
/*

	size_t bytes_to_copy = 0;
	/*if the count is bigger than capacity 
	if(count > CBCapacity(cb))
	{
		cb->write = (cb->write + (count % CBCapacity(cb))) % CBCapacity(cb);
		buff = (char*)buff + (count - CBCapacity(cb));
		count = CBCapacity(cb);
	}
	
	bytes_to_copy =  CBCapacity(cb) - cb->write;
	
	if(count >= bytes_to_copy)
	{
		memcpy((cb->buff + cb->write) , buff, bytes_to_copy);
		cb->write = 0;
		buff = (char*)buff + bytes_to_copy;
		count -= bytes_to_copy;
	}
	*/
	/*the first memcpy is necessary 
	memcpy(cb->buff +cb->write , buff, count);
	cb->write += count;
	
	if(CBFreeSpace(cb) < ret_count)
	{
		cb->read = cb->write;
		cb->size = CBCapacity(cb);
	}
	else
	{
		cb->size += ret_count;
	}
	
	return ret_count;
	*/
	
	while(count > 0)
	{
		len = MIN((CBCapacity(cb) - cb->write), count);
		memcpy(cb->buff +cb->write , buff , len);
		count = count - len;
		buff = (char*)buff + len;
		
		cb->write = (cb->write +len) % CBCapacity(cb);
	}
	/* if you want to write more than capacity */
	if(ret_count > CBFreeSpace(cb))
	{
		/*cb->read = cb->write ; update read */
		cb->size = CBCapacity(cb);
	}
	else
	{
		cb->size += ret_count;
	}
	
	return ret_count;
}



/**************************************************************************/
/* read from the circular buffer, count bytes, to buff */
ssize_t CBRead(cb_t *cb, void *buff, size_t count)
{
	size_t bytes_to_copy = 0;
	size_t ret_count = 0;
	size_t len = 0;
	size_t read = (cb->write - cb->size + CBCapacity(cb)) % CBCapacity(cb);
	
	assert(cb);
	assert(buff);
	
	/* the first memcpy is necessary 
	if(count > (CBCapacity(cb) - CBFreeSpace(cb)))
	{
		count = CBCapacity(cb) - CBFreeSpace(cb);
	}
	
	bytes_to_copy = CBCapacity(cb)-cb->read;
	
	if(count >= bytes_to_copy)
	{
		memcpy(buff , cb->buff+cb->read, bytes_to_copy);
		cb->read = 0;
		buff = (char*)buff + bytes_to_copy;
		ret_count += bytes_to_copy;
		count -= bytes_to_copy;
		cb->size -= bytes_to_copy;
	}
*/
		/* first memcpy 
	memcpy(buff , cb->buff + cb->read , count);
	cb->read += count;
	cb->size -=count;
	ret_count += count;
	*/
	if(count > (CBCapacity(cb) - CBFreeSpace(cb)))
	{
		count = CBCapacity(cb) - CBFreeSpace(cb);
	}
	
	ret_count = count;
	
	while(count > 0)
	{
		len = MIN((CBCapacity(cb) - read), count);
		memcpy(buff , cb->buff + read , len);
		count = count - len;
		buff = (char*)buff + len;
		cb->size -= len;
		read = (read +len) % CBCapacity(cb);
	}

	
	return ret_count;
}







/**************************************************************************/
/* return the number of bytes remained in the circular buffer */
size_t CBFreeSpace(const cb_t *cb)
{
	assert(cb);
	
	return (CBCapacity(cb) - cb->size);
}



/**************************************************************************/
/* return the capacity of the circular buffer */
size_t CBCapacity(const cb_t *cb)
{
	assert(cb);
	
	return cb->capacity;

}


/**************************************************************************/
/* check if the circular buffer is empty (empty = 1; notempty = 0) */
int CBIsEmpty(const cb_t *cb)
{
	assert(cb);
	
	return (cb->size==0);
}


