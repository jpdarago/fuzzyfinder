#ifndef __BIT_ARRAY_H
#define __BIT_ARRAY_H

typedef struct {
    int length;
    unsigned int buffer[];
} bit_array;

bit_array * bit_array_new(int);
void bit_array_destroy(bit_array *);
void bit_array_set(bit_array *,int);
void bit_array_clear(bit_array *, int);
void bit_array_setall(bit_array *);
int bit_array_nextset(const bit_array *, int);
int bit_array_get(const bit_array *, int);

#endif
