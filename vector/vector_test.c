#include <stdio.h> /*printf */
#include <stdlib.h> /* exit() */

#include "vector.h"


int main()
{

	vector_t *vector_handle = NULL;
	int status_tester = 0;
	int index = 0;
	size_t size = 0;
	size_t element_size = sizeof(int);
	int capacity = 3;
	
	int *ptr = NULL; /* Vector to store item address */
	int int_element = 657;
	int int_element2 = 444;
	int int_element3 = 555;
	
	/*float float_element = 3.14; 
	char *string_element = "hello";*/
			
	vector_handle = VectorCreate(element_size);
	if(vector_handle == NULL)
	{
		printf("Error. Allocation was unsuccessful. \n");
		exit(1);
	}
	
	/* testing VectorPushBack */
	status_tester = VectorPushBack(vector_handle, &int_element);
	printf("\ntesting push back int:");
	printf("\ndid push succeed? (yes=0, no=1): %d\n", status_tester);
	size = VectorSize(vector_handle);
	printf("\nvector size after push is: %ld\n", size );
	
	/* testing VectorReserve */
	status_tester = VectorReserve(vector_handle, capacity);
	printf("did reserve succeed? (yes=0, no=1): %d \n", status_tester);
	
	size = VectorSize(vector_handle);
	printf("\nvector size before push is: %ld\n", size );
	
	/* testing VectorPushBack */
	status_tester = VectorPushBack(vector_handle, &int_element);
	printf("\ntesting push back int:");
	printf("\ndid reserve succeed? (yes=0, no=1): %d", status_tester);
	
	size = VectorSize(vector_handle);
	printf("\nvector size is: %ld\n", size );
	
	index = 0;
	ptr = (int*)VectorGetItem(vector_handle, index);
	printf("our element in index %d is: %d\n\n", index, *ptr );
	
	
	status_tester = VectorPushBack(vector_handle, &int_element2);
	printf("\ndid reserve succeed? (yes=0, no=1): %d", status_tester);
	
	size = VectorSize(vector_handle);
	printf("\nvector size is: %ld\n", size );
	
	index = 1;
	ptr = (int*)VectorGetItem(vector_handle, index);
	printf("our element in index %d is: %d\n\n", index, *ptr );
	
	
	status_tester = VectorPushBack(vector_handle, &int_element3);
	printf("\ndid reserve succeed? (yes=0, no=1): %d", status_tester);
	size = VectorSize(vector_handle);
	printf("\nvector size is: %ld\n", size );
	
	index = 2;
	ptr = (int*)VectorGetItem(vector_handle, index);
	printf("our element in index %d is: %d\n", index, *ptr );
		
		
	/*
	status_tester = VectorPushBack(vector_handle, &float_element);
	printf("\ntesting push back float:");
	printf("\ndid reserve succeed? (yes=0, no=1): %d", status_tester);
	
	status_tester = VectorPushBack(vector_handle, string_element);
	printf("\ntesting push back string:");
	printf("\ndid reserve succeed? (yes=0, no=1): %d \n", status_tester);*/
	
	
	/* testing VectorGetItemAddress */

	
	/*ptr = VectorGetItemAddress(vector_handle, index);
	printf("\nour element in index %d is: %f\n", index, *(float*)ptr );
	index = 2;
	ptr = VectorGetItemAddress(vector_handle, index);
	printf("\nour element in index %d is: %s\n", index, (char*)ptr );
	*/
	
	/* testing VectorSize */
	size = VectorSize(vector_handle);
	printf("\nvector size is: %ld\n", size );
	
	/* testing VectorCapacity */
	capacity =  VectorCapacity(vector_handle);
	printf("\nvector capacity is: %d\n", capacity );               
	
	status_tester = VectorPushBack(vector_handle, &int_element);
	printf("\ndid Push succeed? (yes=0, no=1): %d", status_tester);
	index = 3;
	ptr = VectorGetItem(vector_handle, index);
	printf("\nour element in index %d is: %d\n", index, *(int*)ptr );
	
	

	/* testing VectorCapacity after realloc */
	capacity =  VectorCapacity(vector_handle);
	printf("\nvector capacity is: %d\n", capacity );

	/* testing VectorSize */
	size = VectorSize(vector_handle);
	printf("\nvector size befor pop is: %ld\n", size );

	/* testing VectorPopBack */
	VectorPopBack(vector_handle);

	size = VectorSize(vector_handle);
	printf("\nvector size after pop is: %ld\n", size );
	
	
	VectorPopBack(vector_handle);
	VectorPopBack(vector_handle);

	/* testing VectorPopBack  */
	capacity =  VectorCapacity(vector_handle);
	printf("\nvector capacity after pop is: %d\n", capacity );
	size = VectorSize(vector_handle);
	printf("\nvector size after pop is: %ld\n", size );
	
	/* testing VectorDestroy  */
	VectorDestroy(vector_handle);
	
	
return 0;
}
