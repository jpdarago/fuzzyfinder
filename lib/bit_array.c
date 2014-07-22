#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stdio.h>

#include "../include/bit_array.h"

static const int wordsize = sizeof(int);
static const int bits_per_word = sizeof(int)* 8;

bit_array * bit_array_new(int size)
{
    assert(size > 0);
    int effective_size = (size + bits_per_word - 1)/bits_per_word;
    bit_array * ba = calloc(1,sizeof(bit_array)+effective_size*wordsize);
    assert(ba);
    ba->length = size;
    ba->setcount = 0;
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
    int prev = array->buffer[position / bits_per_word], boff = position % bits_per_word;
    if(!(prev & (1 << boff))) array->setcount++;
    array->buffer[position / bits_per_word] |= 1 << boff;
}

int bit_array_setcount(const bit_array * array)
{
    return array->setcount;
}

void bit_array_clear(bit_array * array, int position)
{
    if(position >= array->length){
        return;
    }
    int prev = array->buffer[position / bits_per_word], boff = position % bits_per_word;
    if(prev & (1 << boff)) array->setcount--;
    array->buffer[position / bits_per_word] &= ~(1 << boff);
}

void bit_array_setall(bit_array * array)
{
    int effective_size = (array->length + bits_per_word - 1)/bits_per_word;
    memset(array->buffer,UINT_MAX,effective_size * wordsize);
    array->setcount = array->length;
}

int bit_array_get(const bit_array * array, int pos)
{
    assert(pos < array->length);
    return array->buffer[pos / bits_per_word] & (1 << (pos % bits_per_word));
}

int bit_array_ithset(const bit_array * array, int ith)
{
    if(ith >= array->length) return -1;
    int effective_size = (array->length + bits_per_word -1)/bits_per_word;
    int i,index = 0, counted = 0, last = array->buffer[0];
    for(i = 0; i < effective_size; i++){
        last = array->buffer[i];
        int count = __builtin_popcount(array->buffer[i]);
        if(counted + count > ith) break;
        counted += count;
        index += bits_per_word;
    }
    if(i == effective_size) return -1;
    int seen = 0;
    for(i = 0; i < bits_per_word; i++){
        if(!(last & (1 << i))) continue;
        if(counted + seen == ith){
            return index + i;
        }
        seen++;
    }
    return -1;
}
