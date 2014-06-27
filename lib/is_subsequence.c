#include "../include/is_subsequence.h"

int is_subsequence(const char * needle, const char * haystack)
{
    if(*needle == '\0') return 1;
    for(;*haystack;haystack++){
        if(*needle == '\0'){
            break;
        }
        char s = *needle, t = *haystack;
        // Use case insensitivity unless the search term is uppercase.
        if(t >= 'A' && t <= 'Z' && s >= 'a' && s <= 'z'){
            t = t - 'A' + 'a';
        }
        if(s == t){
            needle++;
        }
    }
    return *needle == '\0';
}
