#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../include/test_macros.h"
#include "../include/text_buffer.h"

void test_append_data()
{
    text_buffer * buffer = text_buffer_new(6);
    ASSERT(buffer, "expected to obtain a buffer");
    ASSERT(!strcmp(text_buffer_data(buffer),""), "expected buffer content to be non-empty");
    buffer = text_buffer_add(buffer,"hola",4);
    ASSERT(!strcmp(text_buffer_data(buffer), "hola"), "expected buffer to contain 'hola'");
    text_buffer_destroy(buffer);
}

void test_append_lots_of_data()
{
    const char * str = "thisisalongstring";
    const int strlength = strlen(str);

    text_buffer * buffer = text_buffer_new(4);
    buffer = text_buffer_add(buffer,str,strlength);
    ASSERT(!strcmp(text_buffer_data(buffer),str),"unexpected buffer contents");
    text_buffer_destroy(buffer);
}

void test_append_and_remove()
{
    text_buffer * buffer = text_buffer_new(4);
    buffer = text_buffer_add(buffer,"hola",4);
    text_buffer_remove(buffer,2);
    ASSERT(!strcmp(text_buffer_data(buffer),"ho"),"unexpected buffer contesnts");
}

typedef void (*test)(void);
test tests[] = {
    test_append_data,
    test_append_lots_of_data,
    test_append_and_remove,
    NULL,
};

int main()
{
    for(int i = 0; tests[i]; ++i){
        tests[i]();
    }
    return 0;
}
