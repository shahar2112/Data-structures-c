#include <stdio.h> /*printf */
#include <stdlib.h> /* malloc */


#include "bitarr.h"

#define ARR_SIZE 64

int main()
{
	bit_arr_t bit_array = 7;
	int bit_index = 2;
	int n_times = 8;
	char *buffer = NULL;

	buffer = (char*)malloc(ARR_SIZE +1);
	if(buffer==NULL)
	{
		printf("Error. Allocation was unsuccessful. \n");
		exit(1);
    }
	
	printf( "\nBitArrSetAll:\n ");
	BitArrToString(BitArrSetAll(), buffer);
	printf( "%s \n",  buffer);
	
	printf( "\nBitArrResetAll:\n");
	BitArrToString(BitArrResetAll(), buffer);
	printf( "%s \n",  buffer);
	
	bit_array = BitArrSetOn(bit_array, bit_index);
	printf( "\nBitArrSetOn- %lu \n",  bit_array);
	
	bit_array = BitArrSetOff(bit_array, bit_index);
	printf( "\nBitArrSetOff- %lu \n",  bit_array);
	
	bit_array = BitArrFlip(bit_array, bit_index);
	printf( "\nBitArrFlip- %lu \n",  bit_array);
	
	printf( "\nBitArrGetBit- %d \n",  BitArrGetBit(bit_array, bit_index));
	
	bit_array = 11;
	printf( "\nBitArrCountOn- %d \n", BitArrCountOn(bit_array));
	
	printf( "\nBitArrCountOnLUT- %ld \n",  BitArrCountOnLUT(bit_array));
	
	printf( "\nBitArrCountOff- %d \n",  BitArrCountOff(bit_array));
	
	printf( "\nbit is- %lu \n",  bit_array);
	BitArrToString(bit_array, buffer);
	printf( "\nbit to string is: \n");
	printf( "%s \n",  buffer);
	
	printf("bit_array after left rotation %d times is:\n ", n_times);
	BitArrLeftRotate(bit_array, n_times);
	BitArrToString(BitArrLeftRotate(bit_array, n_times), buffer);
	printf("%s \n ", buffer);
	
	BitArrToString(bit_array, buffer);
	printf( "\nbit to string is: \n");
	printf( "%s \n",  buffer);
	
	printf("bit_array after right rotation %d times is:\n ", n_times);
	BitArrRightRotate(bit_array, n_times);
	BitArrToString(BitArrRightRotate(bit_array, n_times), buffer);
	printf("%s \n ", buffer);
	
	printf("\nbit_array before mirror is:\n ");
	BitArrToString(bit_array, buffer);
	printf("%s \n ", buffer);
	printf("bit_array after mirror is:\n ");
	BitArrToString(BitArrMirror(bit_array), buffer);
	printf("%s \n ", buffer);
	
	free(buffer);
	buffer = NULL;
	
	return 0;
}

