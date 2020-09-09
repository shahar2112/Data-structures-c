#include "bst.h"

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* fprintf */

#define TEST(real,expected) (real == expected ? printf("\033[1;33m%d, Pass\n\033[0m", expected) : printf("\033[1;31m %d, Fail\n\033[0m",expected));

#define RED	printf("\033[1;31m")
#define BLUE printf("\033[1;36m")
#define MAGENTA printf("\033[1;35m")
#define YELLOW printf("\033[1;33m")
#define DEFAULT	printf("\033[0m")

static int CmpFunc(const void *data1, const void *data2);
static void PrintTree(bst_t *bst,  int nums[]);
static int Action(void *data, void *param);

int main()
{
    bst_t *bst = NULL;
    int data1 = 13;
    int data2 = 8;
    int data3 = 16;
    int check = 0;
    int check2 = 15;
    int param = 2;
    int nums[]={4,6,7,8,9};
    size_t i = 0;
	int size = sizeof(nums)/sizeof(nums[i]);

    bst_iter_t it1;
    bst_iter_t it2;
    bst_iter_t it3;

    bst = BSTCreate(CmpFunc);
    if (bst == NULL)
    {
        printf("failed");
    }

    printf("Is list empty?\n");
    check = BSTIsEmpty(bst);
    TEST(check, 1);

    printf("count test\n");
    TEST(BSTCount(bst), 0);

    it1 = BSTInsert(bst, &data1);
    printf("Is list empty?\n");
    check = BSTIsEmpty(bst);
    TEST(check, 0);

    it2 = BSTInsert(bst, &data2);
    it3 = BSTInsert(bst, &data3);

    TEST(*(int*)BSTIterGetData(it1), 13)
    TEST(*(int*)BSTIterGetData(it2), 8)
    TEST(*(int*)BSTIterGetData(it3), 16)

    TEST(*(int*)BSTIterGetData(BSTIterNext(it2)), 13);
    TEST(*(int*)BSTIterGetData(BSTIterNext(it1)), 16);

    printf("count test\n");
    TEST(BSTCount(bst), 3);

    for ( i = 0; i < size; i++)
    {
        BSTInsert(bst, &nums[i]);
    }
    
    PrintTree(bst, nums);

    TEST(BSTIterIsSameIter(it1, it2), 0);

    
    TEST(*(int*)BSTIterGetData(BSTIterBegin(bst)), 4);

    BSTForEach(bst, Action, &param);
    PrintTree(bst, nums);

    check = *(int*)BSTIterGetData(BSTFind(bst, &check2));
    TEST(check, 15);

	PrintTree(bst, nums);
    check2= 18;
    check2 = *(int*)BSTIterGetData(BSTFind(bst, &check2));
    printf("the data found is %d \n", check2);
    TEST(check2, 18);

	
    BSTRemove((BSTFind(bst, &check2)));
printf("after removing %d :\n", check2);
    PrintTree(bst, nums);

    BSTDestroy(bst);

    return 0;
}

/******************** cmp_func ************************/
static int CmpFunc(const void *data1, const void *data2)
{
    return *(int*)data1 - *(int*)data2;
}

/******************** printtree ************************/
static void PrintTree(bst_t *bst, int nums[])
{
    bst_iter_t it1;
    MAGENTA;
    printf("The tree is: \n");
    DEFAULT;
     for(it1 = BSTIterBegin(bst); 
    !BSTIterIsSameIter(it1, BSTIterEnd(bst)); 
    it1 = BSTIterNext(it1))
    {
        printf(" %d \n", *(int*)BSTIterGetData(it1));
    }

}

/******************** Action ************************/
static int Action(void *data, void *param)
{
   *(int*)data = *(int*)data + *(int*)param;

    return 0;
}
