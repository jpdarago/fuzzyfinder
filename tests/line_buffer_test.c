#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../include/test_macros.h"
#include "../include/text_buffer.h"
#include "../include/line_buffer.h"

void test_line_buffer_new()
{
    line_buffer * buffer = line_buffer_new(1);
    ASSERT(buffer, "expected buffer to be non-NULL");
    ASSERT(line_buffer_linecount(buffer) == 0, "unexpected number of lines");
    line_buffer_addline(buffer,"hola",4);
    const char * line = line_buffer_getline(buffer,0);
    ASSERT(!strcmp(line,"hola"),"expected first line to be hola, got %s",line);
    line_buffer_destroy(buffer);
}

void test_line_buffer_add_several()
{
    line_buffer * buffer = line_buffer_new(1);
    line_buffer_addline(buffer,"hola",4);
    line_buffer_addline(buffer,"chau",4);
    ASSERT(!strcmp(line_buffer_getline(buffer,0),"hola"),"unexpected first line");
    ASSERT(!strcmp(line_buffer_getline(buffer,1),"chau"),"unexpected second line");
    ASSERT(line_buffer_linecount(buffer) == 2, "unexpected number of lines");
    line_buffer_destroy(buffer);
}

test tests[] = {
    test_line_buffer_new,
    test_line_buffer_add_several,
    NULL,
};

int main()
{
    for(int i = 0; tests[i]; i++){
        tests[i]();
    }
    return 0;
}
