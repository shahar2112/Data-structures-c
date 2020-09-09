#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* fprintf */

#include "heap.h"

#define RED	printf("\033[1;31m")
#define BLUE printf("\033[1;36m")
#define MAGENTA printf("\033[1;35m")
#define YELLOW printf("\033[1;33m")
#define GREEN printf("\033[1;32m")
#define DEFAULT	printf("\033[0m")
/* #define TEST(real,expected) (real == expected ? printf("\033[1;35m %d, Pass\n\033[0m", expected) : printf("\033[1;31m %d, Fail\n ",expected)) */

#define TEST(real,expected) (real == expected ? printf("\033[1;32m%d, Pass\033[0m\n", expected) : printf("\033[1;31m%d, Fail\033[0m\n",expected))

static int Cmpfunc(void *data1, void *data2);
static int IsMatch(void *data, void *param);

int main()
{
    heap_t *heap = NULL;
    int num = 4;
    int arr[] = {6, 2, 1, 4, 3};
    int size = sizeof(arr)/sizeof(arr[1]);
    int i = 0;
    int *removed = NULL;

    heap = HeapCreate(Cmpfunc);
    printf("when empty size is %ld \n ", HeapSize(heap));
    TEST(0, HeapSize(heap));


    printf("Is heap empty?\n");
    TEST(HeapIsEmpty(heap), 1);

    for(i=0; i<size; i++)
    {
        BLUE;
        printf("size is %ld \n ", HeapSize(heap));
        DEFAULT;
        HeapPush(heap, &arr[i]);
        YELLOW;
        printf("after push %d (min) element is %d \n ", i+1, *(int*)HeapPeek(heap));
        DEFAULT;
    }
    BLUE;
    printf("size is %ld \n ", HeapSize(heap));
    DEFAULT;

    RED;
    printf("\nTest remove\n");
    DEFAULT;
    removed = HeapRemove(heap, IsMatch, &num);
    if(removed != NULL)
    {
        printf("removed data is %d\n", *(int*)removed);
    }
    else
    {
        printf("data not found\n");
    }

    num = 7;
    removed = HeapRemove(heap, IsMatch, &num);
    if(removed != NULL)
    {
        printf("removed data is %d\n", *(int*)removed);
    }
    else
    {
        printf("data not found\n");
    }
    
    printf("after removing 4 size is %ld\n", HeapSize(heap));
    TEST(HeapSize(heap), 4);
    printf("root is %d \n", *(int*)HeapPeek(heap));
    TEST(*(int*)HeapPeek(heap), 1);

    num = 1;
    removed = HeapRemove(heap, IsMatch, &num);
    if(removed != NULL)
    {
        printf("removed data is %d\n", *(int*)removed);
    }
    else
    {
        printf("data not found\n");
    }
    printf("after removing 1 size is %ld\n", HeapSize(heap));
    TEST(HeapSize(heap), 3);
    printf("root is %d \n", *(int*)HeapPeek(heap));
    TEST(*(int*)HeapPeek(heap), 2);


printf("\n");

    for(i=0; i<size-3; i++)
    {
        HeapPop(heap);
        printf("after pop %d (min) element is %d \n", i+1, *(int*)HeapPeek(heap));
        MAGENTA;
        printf("after pop %d size is %ld \n ", i+1, HeapSize(heap));
        DEFAULT;
    }

    HeapDestroy(heap);
    
    return 0;
}

static int Cmpfunc(void *data1, void *data2)
{
    return *(int*)data1 - *(int*)data2;
}

static int IsMatch(void *data, void *param)
{
    return *(int*)data == *(int*)param;
}