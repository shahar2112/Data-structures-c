
#include <stdlib.h> /* malloc */
#include <stdio.h> /* fprintf */
#include <math.h> /* rand */

#include "rbst.h"


#define TEST(real,expected) (real == expected ? printf(" %d, \033[0;32m Pass \033[0m \n", expected) : printf(" \033[1;31m %d, Fail \033[0m\n",expected))

#define RED	printf("\033[1;31m")
#define BLUE printf("\033[1;36m")
#define MAGENTA printf("\033[1;35m")
#define YELLOW printf("\033[1;33m")
#define GREEN printf("\033[0;32m")
#define DEFAULT	printf("\033[0m")

static int CmpFunc(const void *data1, const void *data2);
static int Action(void *data, void *param);

int main()
{
    int status = 0;
    rbst_t *rbst = NULL;
     int nums[]={30, 40, 50, 75, 98, 35, 33, 45, 49, 43}; 
    
    int to_find = 33;
    int to_find2 = 35;
    size_t i = 0;
    size_t count = 0;
    void *data = NULL;
	int size = sizeof(nums)/sizeof(nums[i]);
/* 
    int *random = NULL;
    random = (int *)malloc(1000*sizeof(int));

    for(i=0; i<1000; i++)
    {
        random[i] = rand()%10;
    }

    rbst = RBSTCreate(CmpFunc);
    if(rbst == 0)
    {
        printf("failed");
    }

    for(i=0; i<1000; i++)
    {
        RBSTInsert(rbst, &random[i]);
    }

    for(i=0; i<900; i++)
    {
        RBSTRemove(rbst, &random[i]);
    }

    count = RBSTHeight(rbst);
    printf("height is %ld\n", count); */

 
    rbst = RBSTCreate(CmpFunc);
    if(rbst == 0)
    {
        printf("failed");
    }

    printf("size %d\n", size);

    for ( i = 0; i < size; i++)
    {
        status = RBSTInsert(rbst, &nums[i]);
    }

    printf("is empty?\n");

    TEST(RBSTIsEmpty(rbst), 0);

    data = RBSTFind(rbst, &to_find);
    printf("is data found? \n");
    TEST(*(int*)data, 33);


    count = RBSTCount(rbst);
    printf("count is %ld\n", count);
    TEST(RBSTCount(rbst), size); 

    count = RBSTHeight(rbst);
    printf("height is %ld\n", count);
    TEST(RBSTHeight(rbst), 3);
    RED;
     printf("PRE_ORDER\n");
    DEFAULT;
    RBSTForEach(rbst, Action, NULL, PRE_ORDER);
    RED;
    printf("POST_ORDER\n"); 
    DEFAULT;
    RBSTForEach(rbst, Action, NULL, POST_ORDER);
    RED ;
    printf("IN_ORDER\n"); 
    DEFAULT;
    RBSTForEach(rbst, Action, NULL, IN_ORDER);

    RBSTRemove(rbst, &to_find);

    RED ;
    printf("POST_ORDER AFTER REMOVING 33\n"); 
    DEFAULT;
    RBSTForEach(rbst, Action, NULL, POST_ORDER);

    RBSTRemove(rbst, &to_find2);
    RED ;
    printf("POST_ORDER AFTER REMOVING 35\n"); 
    DEFAULT;
    RBSTForEach(rbst, Action, NULL, POST_ORDER);
 
    to_find = 49;
    RBSTRemove(rbst, &to_find);
    RED ;
    printf("POST_ORDER AFTER REMOVING 49\n"); 
    DEFAULT;
    RBSTForEach(rbst, Action, NULL, POST_ORDER);

    to_find = 50;
    RBSTRemove(rbst, &to_find);
    RED ;
    printf("POST_ORDER AFTER REMOVING 50\n"); 
    DEFAULT;
    RBSTForEach(rbst, Action, NULL, POST_ORDER);

    RBSTDestroy(rbst); 
 
    return 0;
}


/******************** cmp_func ************************/
static int CmpFunc(const void *data1, const void *data2)
{
    return *(int*)data1 - *(int*)data2;
}


static int Action(void *data, void *param)
{
    param = param;

    printf("data is %d\n", *(int*)data);

    return 0;
}




