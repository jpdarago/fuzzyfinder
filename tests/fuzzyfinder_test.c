#include <stdio.h>
#include <assert.h>

#include "../include/fuzzyfinder.h"

int main(){
    assert(fuzzymatch("a","ab"));
    assert(!fuzzymatch("c","ab"));
    assert(fuzzymatch("abc","axbxcxxxx"));
    assert(!fuzzymatch("abcd","abc"));
    return 0;
}
