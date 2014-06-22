#ifndef __FUZZY_FINDER_H
#define __FUZZY_FINDER_H

typedef struct {
    int capacity;
    int length;
    char data[];
} text_buffer;

text_buffer * text_buffer_new(int);
void text_buffer_destroy(text_buffer *);
text_buffer * text_buffer_add(text_buffer *, const char *, int);
const char * text_buffer_data(const text_buffer *);
void text_buffer_remove(text_buffer *, int);
int text_buffer_length(const text_buffer *);

#endif
