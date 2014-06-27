#include <stdio.h>
#include <assert.h>

#include "../include/is_subsequence.h"

int main(){
    assert(is_subsequence("a","ab"));
    assert(!is_subsequence("c","ab"));
    assert(is_subsequence("abc","axbxcxxxx"));
    assert(!is_subsequence("abcd","abc"));
    assert(is_subsequence("","abcd"));
    assert(is_subsequence("abcd","ABCD"));
    assert(!is_subsequence("aBcd","AbCD"));
    assert(is_subsequence("aBcd","ABCD"));
    assert(is_subsequence("olálá","olálá"));
    return 0;
}
