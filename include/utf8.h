#ifndef __UTF8_H
#define __UTF8_H

#define TB_EOF -1
int tb_utf8_char_length(char c);
int tb_utf8_char_to_unicode(uint32_t *out, const char *c);
int tb_utf8_unicode_to_char(char *out, uint32_t c);

#endif
