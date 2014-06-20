#include <string.h>
#include <stdlib.h>

#include "../include/text_buffer.h"

text_buffer * text_buffer_new(int capacity)
{
    text_buffer * buffer = malloc(sizeof(text_buffer) + capacity);
    buffer->capacity = capacity;
    buffer->length = 0;
    buffer->data[0] = '\0';
    return buffer;
}

void text_buffer_destroy(text_buffer * buffer)
{
    free(buffer);
}

text_buffer * text_buffer_add(text_buffer * buffer,const char * text,int length)
{
    if(buffer->length + length <= buffer->capacity){
        while(buffer->capacity < length+1){
            buffer->capacity *= 2;
        }
        buffer = realloc(buffer, sizeof(text_buffer) + buffer->capacity);
    }
    memcpy(buffer->data+buffer->length,text,length);
    buffer->length += length;
    buffer->data[buffer->length] = '\0';
    return buffer;
}

const char * text_buffer_data(const text_buffer * buffer)
{
    return buffer->data;
}

void text_buffer_remove(text_buffer * buffer, int bytes)
{
    if(bytes > buffer->length){
        bytes = buffer->length;
    }
    buffer->length -= bytes;
    buffer->data[buffer->length] = '\0';
}
