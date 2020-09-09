#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* fprintf */

#include "cbuffer.h"

#ifndef NDEBUG
#define DEBUG_PRINT(s) fprintf(stderr,(s))
#else
#define DEBUG_PRINT(s)
#endif

#define TEST(real,expected) (real == expected ? printf("pass\n") : printf("fail\n"))

void ReadAndCheck(cb_t *cb, void *buff, size_t count);

int main()
{

	cb_t *CB = NULL;
	
	char *to_write1 = "abcd";
	char *to_write2 = "efgh";
	char *to_write3 = "HelloWorld";
		
	char read_to1[20] = {0};
	char read_to2[20] = {0};
	/* Test 1 write nothing*/
/*	CB = CBCreate(5);
	
	CBWrite(CB, to_write1, 0);
	
	TEST(CBCapacity(CB),5);
	
	TEST(CBFreeSpace(CB),5);
	
	TEST(CBIsEmpty(CB),0);

	CBRead(CB, &read_to, 3);
	
	printf("read: %s\n", read_to);
	
	CBDestroy(CB);
*/

	/* Test 2 write less than capacity*/
	CB = CBCreate(5);
	
	CBWrite(CB, to_write1, 3);
	
	TEST(CBFreeSpace(CB),2);
	
	TEST(CBIsEmpty(CB),0);
	
	CBRead(CB, &read_to1, 3);
	
	printf("read: %s\n", read_to1);
	
	CBWrite(CB, to_write2, 3);
	
	TEST(CBFreeSpace(CB),2);
	
	TEST(CBIsEmpty(CB),0);

	CBRead(CB, &read_to1, 3);
	
	printf("read: %s\n", read_to1);
	
	CBDestroy(CB);
	
	/* Test 3 write capacity + read more*/
	CB = CBCreate(5);
	
	CBWrite(CB, to_write1, 5);
	
	TEST(CBFreeSpace(CB),0);
	
	TEST(CBIsEmpty(CB),0); /*no*/
	
	/*TEST(CBRead(CB, &read_to1, 6),-1)*/;

	TEST(CBRead(CB, &read_to1, 5),5);

	printf("read: %s\n", read_to1);

	CBDestroy(CB);
	
	/* Test 4 write more than capacity*/
	CB = CBCreate(5);
	
	TEST(CBWrite(CB, to_write3, 10),10);
	
	TEST(CBFreeSpace(CB),0);
	
	TEST(CBIsEmpty(CB),0);	
	
	CBRead(CB, &read_to2, 3);	

	printf("read: %s\n", read_to2);

	CBDestroy(CB);	
	
	/* Test 1 read nothing*/
	CB = CBCreate(5);
	
	CBWrite(CB, to_write1, 5);
	
	CBRead(CB, &read_to2+3, 0);
	
	printf("read: %s\n", read_to2+3);
	
	CBDestroy(CB);		

	return 0;
}


