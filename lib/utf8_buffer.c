#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "../include/text_buffer.h"
#include "../include/utf8_buffer.h"

utf8_buffer * utf8_buffer_new(int capacity)
{
    return text_buffer_new(capacity);
}

void utf8_buffer_destroy(utf8_buffer * buf)
{
    text_buffer_destroy(buf);
}

utf8_buffer * utf8_buffer_add(utf8_buffer * buf, const char * data, int length)
{
    return text_buffer_add(buf,data,length);
}

const char * utf8_buffer_data(const utf8_buffer * buf)
{
    return text_buffer_data(buf);
}

void utf8_buffer_remove(utf8_buffer * buf, int chars)
{
    const char * data = text_buffer_data(buf);
    int length = text_buffer_length(buf);

    int i = length-1;
    for(; chars > 0; chars--){
        for(;i >= 0; i--){
            if((data[i] & 0xC0) != 0x80){
                i--;
                break;
            }
        }
    }

    text_buffer_remove(buf,length - 1 - i);
}
