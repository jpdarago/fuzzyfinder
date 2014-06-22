#include <stdio.h>
#include <assert.h>

#include "../include/is_subsequence.h"

int main(){
    assert(is_subsequence("a","ab"));
    assert(!is_subsequence("c","ab"));
    assert(is_subsequence("abc","axbxcxxxx"));
    assert(!is_subsequence("abcd","abc"));
    assert(is_subsequence("","abcd"));
    return 0;
}
