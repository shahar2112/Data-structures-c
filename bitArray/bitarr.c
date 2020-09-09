#include <stdio.h> /*printf */
#include <assert.h> /*assert */
#include <limits.h> /* CHAR_BIT number of bits in a byte */

#include "bitarr.h"

#define ARR_SIZE (sizeof(size_t) * CHAR_BIT)

/* macros to generate the lookup table (at compile-time) */
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)

/* Generate a lookup table using macro  */
#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64 
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16) 
#define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 ) 
#define MIRROR R6(0), R6(2), R6(1), R6(3)

/*forward declarations */
static void reverse( char* buffer, int i);

/*lookup-table to store the number of bits set for each index
in the table. The macro COUNT_BITS generates the table. */
static unsigned char LUT_set_bits[256] = { COUNT_BITS };


/*lookup-table to store the opposit number of bits set for each index
in the table. The macro MIRROR generates the table. */
static unsigned char LUT_mirror[256] = { MIRROR };


/**************************************************************************/
bit_arr_t BitArrSetAll()
{ 					
	return ~(0); /* set all to 1 */
}


/**************************************************************************/
bit_arr_t BitArrResetAll()
{
	return 0; /* setting all to zero */
}


/**************************************************************************/
bit_arr_t BitArrSetOn(bit_arr_t bit_array, unsigned int bit_index)
{
	assert(bit_index < ARR_SIZE);

	bit_array |= (size_t)1<<bit_index;
	return bit_array;
}


/**************************************************************************/
bit_arr_t BitArrSetOff(bit_arr_t bit_array, unsigned int bit_index)
{
	assert(bit_index < ARR_SIZE);
	bit_array &= ~((size_t)1<<bit_index); /*set the index to zero with ~1 and the & */
	return bit_array;
}


/**************************************************************************/
bit_arr_t BitArrFlip(bit_arr_t bit_array, unsigned int bit_index)
{
	assert(bit_index < ARR_SIZE);
	
	bit_array ^= (size_t)1<<bit_index;
	return bit_array;
}


/**************************************************************************/
on_off_t BitArrGetBit(bit_arr_t bit_array, unsigned int bit_index)
{
	assert(bit_index < ARR_SIZE);
	return((bit_array & ((size_t)1 << bit_index)) == 0) ? OFF : ON;
} 



/**************************************************************************/
unsigned int BitArrCountOn(bit_arr_t bit_array)
{
	unsigned int count = 0;
	
	while( bit_array != 0)
	{
		count += (bit_array & 1); /* check if right bit is set ctr++ */
		bit_array >>= 1; /* move and check the next bit */
		
	}
	return count;
}


/**************************************************************************/
unsigned int BitArrCountOff(bit_arr_t bit_array)
{
	return ARR_SIZE - BitArrCountOn(bit_array);
	
	/*unsigned int ctr = 0;
	unsigned int i = 0;
	
	for(i = 0; i < ARR_SIZE; i++)
	{
		if(((bit_array >> i) & (size_t)1) == 0)
		{
			ctr++;
		}
	}
	return ctr; */
}


/**************************************************************************/
void BitArrToString(bit_arr_t bit_array, char *buffer)
{
	unsigned int i = 0;
	assert( buffer);
	
	while(i < ARR_SIZE)
	{
		if((bit_array & 1) != 0)
		{
			buffer[i] = '1';
		}
		else
		{
			buffer[i] = '0';
		}
		i++;
		bit_array >>= 1;
	}
		
	reverse(buffer, ARR_SIZE);
	/*adding '\0' to end */
	buffer[ARR_SIZE] = '\0';

}

/**************************************************************************/
static void reverse( char* buffer, int arr_size)
{
	int tmp = 0;
	unsigned int i = 0;
	unsigned int j = arr_size -1;
	
	assert( buffer);
		
	while(j > i)
	{
		tmp = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = tmp;
		i++;
		j--;
	}
	return;
}


/**************************************************************************/
bit_arr_t BitArrSetBit(bit_arr_t bit_array, unsigned int bit_index, on_off_t bit_state)
{
	assert(bit_index < ARR_SIZE);

	return bit_state==0 ?
	 BitArrSetOff(bit_array, bit_index) : BitArrSetOn(bit_array, bit_index);
	
}


/**************************************************************************/
bit_arr_t BitArrMirror(bit_arr_t bit_array)
{
	unsigned int i = 0;
	bit_arr_t mirror_array = 0;
	
	for( i = 0; i < sizeof(size_t); i++)
	{
		mirror_array <<= 8;
		mirror_array |= LUT_mirror[(bit_array >> (i*sizeof(size_t))) & 0xff];
	}
	return mirror_array;
}


/**************************************************************************/
bit_arr_t BitArrRightRotate(bit_arr_t bit_array, unsigned int n_times)
{
	bit_arr_t tmp = 0;
	unsigned int i = 0;
	for (i = 0; i < (n_times%64) ; i++)
	{
		tmp = bit_array & 1;
		bit_array >>= 1;
		tmp = tmp << (ARR_SIZE - 1);
		bit_array |= tmp;

	}
	return bit_array;
}


/**************************************************************************/
bit_arr_t BitArrLeftRotate(bit_arr_t bit_array, unsigned int n_times)
{
	bit_arr_t tmp = 0;
	unsigned int i = 0;
	for (i = 0; i < (n_times%64) ; i++)
	{
		tmp = (size_t)1 << (ARR_SIZE-1);
		tmp = bit_array & tmp;
		bit_array <<= 1;
		tmp >>= (ARR_SIZE-1);
		bit_array |= tmp;
	}
	return bit_array;
}



/**************************************************************************/
size_t BitArrCountOnLUT(bit_arr_t bit_array)
{
	unsigned int count = 0;
	unsigned int i = 0;
	
	/*Function to count number of set bits in n */
	for( i = 0; i < sizeof(size_t); i++)
	{
 		count += LUT_set_bits[(bit_array >> (i*sizeof(size_t))) & 0xff];
 	}
 	return count;
}

