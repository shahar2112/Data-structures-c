#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "hash.h"
#include "dlist.h"

static size_t getIndex(hash_t *hash, void *data);
int isMatchWrapper(const void *data, void *param);

struct hash
{
   dlist_t **buckets;
   int (*CmpFunc)(const void *data1, void *data2);
   size_t (*HashFunc)(void *value);
   size_t table_size;
}; /*hash_t */

typedef struct Params
{
	int(*CmpFunc)(const void *data1, void *data2);
	void *data_to_find;
}params_t;



/* HashFunc must be suitable for inserted data. num_of _enteries is constant */
hash_t *HashCreate(int (*CmpFunc)(const void *, void *), size_t(*HashFunc)(void *value), size_t table_size)
{
	hash_t *hash = NULL;

	hash = (hash_t*)malloc(sizeof(hash_t));
	if (NULL == hash)
	{
		fprintf(stderr, "allocation failed\n");
		return NULL;
	}

	hash->buckets = (dlist_t**)calloc(sizeof(dlist_t*),table_size);
	if (NULL == hash->buckets)
	{
		fprintf(stderr, "allocation failed\n");
		free(hash);
		hash = NULL;
		return NULL;
	}

	hash->CmpFunc = CmpFunc;
	hash->HashFunc = HashFunc;
	hash->table_size = table_size;

	return hash;
}

/******************** destroy ************************/
void HashDestroy(hash_t *hash)
{
	size_t i = 0;

	assert(hash);

	for(i=0; i<hash->table_size; i++)
	{
		if(NULL != hash->buckets[i])
		{
			DListDestroy(hash->buckets[i]);
		}
	}
	
	free(hash->buckets);
	hash->buckets = NULL;

	free(hash);
	hash = NULL;
}

/* returns success or fail. data will be enterd according to provided HashFunc */
int HashInsert(hash_t *hash, void *data)
{
	size_t index = 0;

	assert(hash);
	
	index = getIndex(hash, data);

	if(hash->buckets[index] == NULL)
	{
		hash->buckets[index] = DListCreate();
		if(hash->buckets[index] == NULL)
		{
			fprintf(stderr, "allocation failed\n");
			return 1;
		}

	}
   
	return (DListIterIsEqual(DListEnd(hash->buckets[index]), DListPushBack(hash->buckets[index], data)));
}


/* returns void even when provided data does not exist in hash table. make sure to pass valid data */
void HashRemove(hash_t *hash, const void *data)
{
	size_t index = 0;
	iter_t iter;
	params_t param;

	assert(hash);

	index = getIndex(hash, (void *)data);
	
	param.CmpFunc = hash->CmpFunc;
	param.data_to_find = (void*)data;


	iter = DListFind(DListBegin(hash->buckets[index]), 
					DListEnd(hash->buckets[index]), 
					isMatchWrapper ,&param);

	if(!DListIterIsEqual(iter, DListEnd(hash->buckets[index])))
	{
		DListRemove(iter);
	}
}


/* returns pointer to to located data according to the provided key */
void *HashFind(hash_t *hash, const void *data)
{
	size_t index = 0;
	iter_t iter;
	params_t param;

  	assert(hash);

	index = getIndex(hash, (void *)data);
  
	param.CmpFunc = hash->CmpFunc;
	param.data_to_find = (void *)data;

	if(hash->buckets[index] != NULL)
	{
		iter = DListFind(DListBegin(hash->buckets[index]), 
						DListEnd(hash->buckets[index]), 
						isMatchWrapper ,&param);

		if(!DListIterIsEqual(iter, DListEnd(hash->buckets[index])))
		{
			return DListGetData(iter);
		}
	}
	return NULL;
}



/* returns number of occupied keys */
size_t HashSize(const hash_t *hash)
{
	size_t i = 0;
	size_t sum = 0;

  	assert(hash);

	for(i = 0; i < hash->table_size; i++)
	{
	   if(hash->buckets[i] != NULL)
	   {
		   sum += DListCount(hash->buckets[i]);
	   }
	}
	return sum;
}


int HashIsEmpty(const hash_t *hash)
{
  	assert(hash);

	return (0 == HashSize(hash));
}



int HashForEach(hash_t *hash, int (*ActionFunc)(void *data, void *param), void *param)
{
	size_t i = 0;

  	assert(hash);

	for(i = 0; i < hash->table_size; i++)
	{
		if(NULL != hash->buckets[i])
		{
			if(DListForEach(DListBegin(hash->buckets[i]), DListEnd(hash->buckets[i]), ActionFunc, param))
			{
				return 1;
			}
		}
	} 
	return 0;
}



static size_t getIndex(hash_t *hash, void *data)
{
	return ((hash->HashFunc(data))% (hash->table_size));
}


int isMatchWrapper(const void *data, void *param)
{
	params_t *params = param;

	return ((params->CmpFunc)(data, params->data_to_find) == 0);
}

