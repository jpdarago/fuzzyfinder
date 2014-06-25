#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#include "../include/test_macros.h"
#include "../include/text_buffer.h"
#include "../include/utf8_buffer.h"

void test_works_as_buffer()
{
    utf8_buffer * buf = utf8_buffer_new(5);
    ASSERT(buf, "expected a buffer, got none");
    buf = utf8_buffer_add(buf, "hola", 4);
    const char * out = utf8_buffer_data(buf);
    ASSERT(!strcmp(out,"hola"),"expected 'hola', got '%s'", out);
    utf8_buffer_remove(buf,2);
    ASSERT(!strcmp(out,"ho"),"expected 'ho', got '%s'", out);
    utf8_buffer_destroy(buf);
}

void test_removes_unicode()
{
    const char * str = "a 微trin微";
    const int strlength = strlen(str);

    utf8_buffer * buf = utf8_buffer_new(32);
    buf = utf8_buffer_add(buf, str, strlength);
    const char * data = utf8_buffer_data(buf);
    utf8_buffer_remove(buf, 1);
    ASSERT(!strcmp(data, "a 微trin"), "expected 'a 微trin', got '%s'", data);
    utf8_buffer_destroy(buf);
}

test tests[] = {
    test_works_as_buffer,
    test_removes_unicode,
    NULL,
};

int main()
{
    for(int i = 0; tests[i]; i++){
        tests[i]();
    }
    return 0;
}
