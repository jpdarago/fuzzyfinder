#include <stdio.h>
#include <assert.h>

#include "../include/test_macros.h"
#include "../include/bit_array.h"

void test_new_bit_array()
{
    bit_array * ba = bit_array_new(5);
    ASSERT(ba, "expected to obtain a buffer");
    ASSERT(bit_array_nextset(ba, 0) == -1, "expected bit array to be cleared");
    bit_array_destroy(ba);
}

void test_set_bit()
{
    bit_array * ba = bit_array_new(5);
    bit_array_set(ba, 1);
    ASSERT(bit_array_get(ba,1), "expected bit 1 to be set");
    int c = bit_array_nextset(ba,0);
    ASSERT(c == 1, "expected next set bit to be 1 got %d",c);
    bit_array_destroy(ba);
}

void test_set_and_clear()
{
    bit_array * ba = bit_array_new(5);
    bit_array_set(ba, 1);
    bit_array_clear(ba,1);
    int c = bit_array_nextset(ba,0);
    ASSERT(c == -1, "expected next set bit to be -1: got %d", c);
    bit_array_destroy(ba);
}

void test_set_all()
{
    bit_array * ba = bit_array_new(5);
    bit_array_setall(ba);
    for(int i = 0; i < 4; i++){
        ASSERT(bit_array_get(ba,i), "expected bit %d to be on", i);
    }
    bit_array_destroy(ba);
}

test tests[] = {
    test_new_bit_array,
    test_set_bit,
    test_set_and_clear,
    test_set_all,
    NULL,
};

int main()
{
    for(int i = 0; tests[i]; ++i){
        tests[i]();
    }
    return 0;
}
