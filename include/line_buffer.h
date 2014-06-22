#ifndef __LINE_BUFFER_H
#define __LINE_BUFFER_H

typedef struct {
    int linecount, capacity;
    // Positions to skip
    int * skip_vector;
    // Buffer with lines
    text_buffer * lines;
} line_buffer;

line_buffer * line_buffer_new(int);
void line_buffer_destroy(line_buffer * buffer);
const char * line_buffer_getline(const line_buffer *, int);
void line_buffer_addline(line_buffer *, const char *, int);
int line_buffer_linecount(const line_buffer *);

#endif
