#include "../include/is_subsequence.h"

int is_subsequence(const char * needle, const char * haystack)
{
    if(*needle == '\0') return 1;
    for(;*haystack;haystack++){
        if(*needle == '\0'){
            break;
        }
        if(*haystack == *needle){
            needle++;
        }
    }
    return *needle == '\0';
}
