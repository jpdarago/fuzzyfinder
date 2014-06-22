#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "../include/bit_array.h"

static const int wordsize = sizeof(int);

bit_array * bit_array_new(int size)
{
    assert(size > 0);
    int effective_size = (size + wordsize - 1)/wordsize;
    bit_array * ba = calloc(1,sizeof(bit_array)+effective_size*wordsize);
    ba->length = size;
    return ba;
}

void bit_array_destroy(bit_array * ba)
{
    free(ba);
}

void bit_array_set(bit_array * array, int position)
{
    if(position >= array->length){
        return;
    }
    array->buffer[position / wordsize] |= 1 << (position % wordsize);
}

void bit_array_clear(bit_array * array, int position)
{
    if(position >= array->length){
        return;
    }
    array->buffer[position / wordsize] &= ~(1 << (position % wordsize));
}

int bit_array_nextset(const bit_array * array, int prev)
{
    for(int i = prev; i < array->length;i++){
        int block = array->buffer[i / wordsize];
        if(block & (1 << i)) return i;
    }
    return -1;
}

void bit_array_setall(bit_array * array)
{
    memset(array->buffer,UINT_MAX,array->length);
}

int bit_array_get(const bit_array * array, int pos)
{
    assert(pos < array->length);
    return array->buffer[pos / wordsize] & (1 << (pos % wordsize));
}
