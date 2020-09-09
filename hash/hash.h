#ifndef __HASH_H__ 
#define __HASH_H__

#include <stddef.h> /*size_t*/

typedef struct hash hash_t;


/* HashFunc must be suitable for inserted data. num_of _enteries is constant */
hash_t *HashCreate(int (*CmpFunc)(const void *data1, void *data2), size_t(*HashFunc)(void *value), size_t table_size);

/*  */
void HashDestroy(hash_t *hash);

/* returns success or fail. data will be enterd according to provided HashFunc */
int HashInsert(hash_t *hash, void *data);

/* returns void even when provided data does not exist in hash table. make sure to pass valid data */
void HashRemove(hash_t *hash, const void *data);

/* returns pointer to to located data according to the provided key */
void *HashFind(hash_t *hash, const void *data);

/* returns number of occupied keys */
size_t HashSize(const hash_t *hash);

/*  */
int HashIsEmpty(const hash_t *hash);

/*  */
int HashForEach(hash_t *hash, int (*ActionFunc)(void *data, void *param), void *param);

#endif