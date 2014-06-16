#include <stdio.h>
#include <string.h>

int fuzzymatch(const char * needle, const char * haystack)
{
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
