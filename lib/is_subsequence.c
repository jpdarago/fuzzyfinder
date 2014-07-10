#include "../include/is_subsequence.h"

int is_subsequence(const char * needle, const char * haystack)
{
    for(;*haystack;haystack++){
        char s = *needle;
        if(s == '\0'){
            break;
        }
        char t = *haystack;
        // Use case insensitivity unless the search term is uppercase.
        if(t >= 'A' && t <= 'Z' && s >= 'a' && s <= 'z'){
            t = t - 'A' + 'a';
        }
        needle += (s == t);
    }
    return *needle == '\0';
}
