#include <stddef.h>

#ifndef __BITARR_H__
#define __BITARR_H__

typedef size_t bit_arr_t;

typedef enum { OFF, ON } on_off_t;


/* init all bits to 1 */
bit_arr_t BitArrSetAll();

/* init all bits to 0 */
bit_arr_t BitArrResetAll();


void BitArrToString(bit_arr_t bit_array, char *buffer);


bit_arr_t BitArrSetOn(bit_arr_t bit_array, unsigned int bit_index);


bit_arr_t BitArrSetOff(bit_arr_t bit_array, unsigned int bit_index);


bit_arr_t BitArrSetBit(bit_arr_t bit_array, unsigned int bit_index, on_off_t bit_state);


on_off_t BitArrGetBit(bit_arr_t bit_array, unsigned int bit_index);


bit_arr_t BitArrFlip(bit_arr_t bit_array, unsigned int bit_index);


bit_arr_t BitArrMirror(bit_arr_t bit_array);


bit_arr_t BitArrRightRotate(bit_arr_t bit_array, unsigned int n_times);


bit_arr_t BitArrLeftRotate(bit_arr_t bit_array, unsigned int n_times);


unsigned int BitArrCountOn(bit_arr_t bit_array);


unsigned int BitArrCountOff(bit_arr_t bit_array);


size_t BitArrCountOnLUT(bit_arr_t bit_array);


#endif 	/* #ifndef __BITARR_H__ */


