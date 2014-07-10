#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../include/test_macros.h"
#include "../include/text_buffer.h"

void test_append_data()
{
    text_buffer * buffer = text_buffer_new(6);
    ASSERT(buffer, "expected to obtain a buffer");
    ASSERT(!strcmp(text_buffer_data(buffer),""), "expected buffer content to be empty");
    ASSERT(text_buffer_length(buffer) == 0, "expected buffer length to be 0");
    buffer = text_buffer_add(buffer,"hola",4);
    ASSERT(!strcmp(text_buffer_data(buffer), "hola"), "expected buffer to contain 'hola'");
    ASSERT(text_buffer_length(buffer) == 4, "expected buffer length to be 4");
    text_buffer_destroy(buffer);
}

void test_append_lots_of_data()
{
    const char * str = "thisisareallyreallyreallyreallyreallylongstring";
    const int strlength = strlen(str);

    text_buffer * buffer = text_buffer_new(1);
    buffer = text_buffer_add(buffer,str,strlength);
    ASSERT(!strcmp(text_buffer_data(buffer),str),"unexpected buffer contents");
    text_buffer_destroy(buffer);
}

void test_append_and_remove()
{
    text_buffer * buffer = text_buffer_new(5);
    buffer = text_buffer_add(buffer,"hola",4);
    text_buffer_remove(buffer,2);
    ASSERT(!strcmp(text_buffer_data(buffer),"ho"),"unexpected buffer contents");
    text_buffer_destroy(buffer);
}

void test_append_with_spaces()
{
    const char * str = "this is a   string";
    const int strlength = strlen(str);

    text_buffer * buffer = text_buffer_new(5);
    buffer = text_buffer_add(buffer, str, strlength);
    ASSERT(!strcmp(text_buffer_data(buffer),str),"unexpected buffer contents");
    text_buffer_destroy(buffer);
}

void test_append_one_at_a_time()
{
    const char * str = "this is a really really long string with spaces and everything";
    const int strlength = strlen(str);

    text_buffer * buffer = text_buffer_new(16);
    for(int i = 0; i < strlength; i++)
        buffer = text_buffer_add(buffer, &str[i], 1);

    ASSERT(!strcmp(text_buffer_data(buffer),str),"unexpected buffer contents");
    text_buffer_destroy(buffer);
}

void test_clear_buffer()
{
    const char * str = "tuvieja";
    const int strlength = strlen(str);

    text_buffer * buffer = text_buffer_new(1);
    buffer = text_buffer_add(buffer,str,strlength);
    ASSERT(!strcmp(text_buffer_data(buffer),str),"unexpected buffer contents");

    text_buffer_clear(buffer);
    ASSERT(!strcmp(text_buffer_data(buffer),""),"unexpected buffer contents");
    ASSERT(text_buffer_length(buffer) == 0, "unexpected buffer length");
    text_buffer_destroy(buffer);
}

test tests[] = {
    test_append_data,
    test_append_lots_of_data,
    test_append_and_remove,
    test_append_with_spaces,
    test_append_one_at_a_time,
    test_clear_buffer,
    NULL,
};

int main()
{
    for(int i = 0; tests[i]; ++i){
        tests[i]();
    }
    return 0;
}
