#include <stdio.h>
#include <assert.h>

#include "../include/test_macros.h"
#include "../include/bit_array.h"

void test_new_bit_array()
{
    bit_array * ba = bit_array_new(5);
    ASSERT(ba, "expected to obtain a buffer");
    bit_array_destroy(ba);
}

void test_set_bit()
{
    bit_array * ba = bit_array_new(5);
    bit_array_set(ba, 1);
    ASSERT(bit_array_get(ba,1), "expected bit 1 to be set");
    bit_array_destroy(ba);
}

void test_set_and_clear()
{
    bit_array * ba = bit_array_new(5);
    bit_array_set(ba, 1);
    bit_array_clear(ba,1);
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

void test_ith_set()
{
    bit_array * ba = bit_array_new(60);
    ASSERT(bit_array_ithset(ba,0) == -1, "expected no set bits");
    bit_array_set(ba, 0);
    ASSERT(bit_array_ithset(ba,0) == 0, "expected first bit set");
    bit_array_set(ba, 3);
    ASSERT(bit_array_ithset(ba,1) == 3, "expected third bit to be second set");
    bit_array_set(ba, 34);
    ASSERT(bit_array_ithset(ba,2) == 34, "expected thirtyfourth bit to be third set");
    bit_array_set(ba, 35);
    ASSERT(bit_array_ithset(ba,3) == 35, "expected thirtyfifth bit to be fourth set");
    ASSERT(bit_array_ithset(ba,4) == -1, "expected no fifth bit");
    bit_array_destroy(ba);
}

void test_setcount()
{
    bit_array * ba = bit_array_new(16);
    ASSERT(bit_array_setcount(ba) == 0, "expected no bits set");
    bit_array_set(ba,0);
    ASSERT(bit_array_setcount(ba) == 1, "expected 1 bit set");
    bit_array_set(ba,0);
    ASSERT(bit_array_setcount(ba) == 1, "expected 1 bit set");
    bit_array_clear(ba,0);
    ASSERT(bit_array_setcount(ba) == 0, "expected no bits set");
    bit_array_clear(ba,0);
    ASSERT(bit_array_setcount(ba) == 0, "expected no bits set");
    bit_array_setall(ba);
    ASSERT(bit_array_setcount(ba) == 16, "expected all bits set");
    bit_array_destroy(ba);
}

test tests[] = {
    test_new_bit_array,
    test_set_bit,
    test_set_and_clear,
    test_set_all,
    test_ith_set,
    test_setcount,
    NULL,
};

int main()
{
    for(int i = 0; tests[i]; ++i){
        tests[i]();
    }
    return 0;
}
