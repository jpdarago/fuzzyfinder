#ifndef __UTF8_BUFFER_H
#define __UTF8_BUFFER_H

typedef text_buffer utf8_buffer;

utf8_buffer * utf8_buffer_new(int);
utf8_buffer * utf8_buffer_add(utf8_buffer *, const char *, int);
int utf8_buffer_length(const utf8_buffer *);
void utf8_buffer_destroy(utf8_buffer*);
void utf8_buffer_remove(utf8_buffer *, int);
const char * utf8_buffer_data(const utf8_buffer *);
int utf8_buffer_get(const utf8_buffer *, int, uint32_t *);

#endif
