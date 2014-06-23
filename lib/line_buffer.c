#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/text_buffer.h"
#include "../include/line_buffer.h"

static const int INITIAL_BUFSIZE = 256;

line_buffer * line_buffer_new(int capacity){
    assert(capacity > 0);
    line_buffer * buffer = calloc(1, sizeof(line_buffer));
    assert(buffer);
    buffer->capacity = capacity;
    buffer->lines = text_buffer_new(INITIAL_BUFSIZE);
    buffer->skip_vector = calloc(capacity,sizeof(int));
    return buffer;
}

void line_buffer_destroy(line_buffer * buffer)
{
    text_buffer_destroy(buffer->lines);
    free(buffer->skip_vector);
    free(buffer);
}

const char * line_buffer_getline(const line_buffer * buffer, int line)
{
    assert(buffer->linecount > line);
    return text_buffer_data(buffer->lines)+buffer->skip_vector[line];
}

void line_buffer_addline(line_buffer * buffer, const char * line, int length)
{
    assert(line[length] == '\0');
    if(buffer->capacity <= buffer->linecount){
        while(buffer->capacity <= buffer->linecount)
            buffer->capacity *= 2;
        buffer->skip_vector = realloc(buffer->skip_vector,buffer->capacity*sizeof(int));
        assert(buffer->skip_vector);
    }
    buffer->skip_vector[buffer->linecount] = text_buffer_length(buffer->lines);
    // Include '\0'
    buffer->lines = text_buffer_add(buffer->lines,line,length+1);
    buffer->linecount++;
}

int line_buffer_linecount(const line_buffer * buffer)
{
    return buffer->linecount;
}
