#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../include/termbox.h"

#include "../include/text_buffer.h"
#include "../include/bit_array.h"
#include "../include/utf8_buffer.h"
#include "../include/line_buffer.h"
#include "../include/is_subsequence.h"

struct {
    utf8_buffer * query;
    bit_array * display_filter;
    line_buffer * lines;
    int selection;
    int window_start;
} state;

void state_init()
{
    state.selection = 0;
    state.lines = line_buffer_new(16);
    state.query = utf8_buffer_new(16);

    char * line = NULL;
    size_t length = 0;
    int strl, lines = 0;

    while((strl = getline(&line,&length,stdin)) > 0){
        // Remove the '\n'
        line[strl-1] = '\0';
        line_buffer_addline(state.lines,line,strl);
        lines++;
    }
    if(lines == 0){
        fprintf(stderr, "No lines in input!");
        exit(1);
    }

    state.window_start = 0;

    state.display_filter = bit_array_new(lines);
    bit_array_setall(state.display_filter);
    free(line);
}

void state_destroy()
{
    line_buffer_destroy(state.lines);
    bit_array_destroy(state.display_filter);
    utf8_buffer_destroy(state.query);
}

void state_draw_query()
{
    tb_change_cell(0, 0,'>', TB_DEFAULT, TB_DEFAULT);
    tb_change_cell(0, 1,' ', TB_DEFAULT, TB_DEFAULT);

    int col = 2, width = tb_width();
    uint32_t codepoint;

    int step = utf8_buffer_get(state.query,0,&codepoint);
    for(int offset = 0;col < width && step >= 0;){
        offset += step;
        tb_change_cell(col, 0, codepoint, TB_WHITE, TB_DEFAULT);
        col += (codepoint == '\t') ? 4 : 1;
        step = utf8_buffer_get(state.query,offset,&codepoint);
    }

    tb_set_cursor(col,0);
}

void state_draw_lines()
{
    int GREY = 0xf4;
    int printed = 0, width = tb_width(), height = tb_height();
    int line_count = line_buffer_linecount(state.lines);

    for(int i = 0; i < line_count; ++i){
        if(printed > height) break;
        if(!bit_array_get(state.display_filter,i)) continue;
        const char * line = line_buffer_getline(state.lines,i);
        utf8_iter it = utf8_iter_new(line);
        if(i == state.selection){
            bool endseen = false;
            for(int j = 0; j < width; j++){
                uint32_t next = utf8_iter_next(&it);
                endseen = endseen || !next;
                tb_change_cell(j, printed+1, endseen ? ' ' : next,
                    TB_BLACK, GREY);
            }
        }else{
            uint32_t next = utf8_iter_next(&it);
            for(int j = 0; next; j++){
                tb_change_cell(j, printed+1, next, TB_WHITE, TB_DEFAULT);
                next = utf8_iter_next(&it);
            }
        }
        printed++;
    }

}

void state_draw()
{
    tb_clear();
    tb_select_output_mode(TB_OUTPUT_256);

    state_draw_query();
    state_draw_lines();

    tb_present();
}

void state_update_buffer(char c)
{
    if(c != '\b'){
        utf8_buffer_add(state.query, &c, 1);
    }else{
        utf8_buffer_remove(state.query,1);
    }
}

int should_skip_line(int i, char c)
{
    // if we added to the buffer and we didnt match before, we cant match now
    if(c != '\b' && !bit_array_get(state.display_filter, i)) return true;
    // if we removed from the buffer and we matched before, we still match now
    if(c == '\b' && bit_array_get(state.display_filter, i)) return true;
    return false;
}

void state_update(char c)
{
    state_update_buffer(c);
    const int lines = line_buffer_linecount(state.lines);
    const char * query = utf8_buffer_data(state.query);
    int first_set = -1;
    for(int i = 0; i < lines; ++i){
        const char * line = line_buffer_getline(state.lines,i);
        if(should_skip_line(i, c)) continue;
        int issub = is_subsequence(query,line);
        if(issub){
            bit_array_set(state.display_filter, i);
            if(first_set == -1) first_set = i;
        }else{
            bit_array_clear(state.display_filter, i);
        }
    }
    const int sel = state.selection;
    if(sel == -1 || !bit_array_get(state.display_filter,sel)){
        state.selection = first_set;
    }
}

void state_update_cursor(int offset)
{
    int lines = line_buffer_linecount(state.lines);
    int pos = state.selection;
    if(pos+offset < 0 || pos+offset >= lines) return;
    for(int i = pos+offset; i >= 0 && i < lines; i += offset){
        if(bit_array_get(state.display_filter, i)){
            state.selection = i;
            return;
        }
    }
    state.selection = -1;
}

int main()
{
    state_init();

    int ret = tb_init();
    if(ret){
        fprintf(stderr, "tb_init failed with error code%d\n",ret);
        return 1;
    }

    state_draw();
    struct tb_event ev;

    const char * line = NULL;
    char append;

    while(tb_poll_event(&ev)){
        switch (ev.type) {
        case TB_EVENT_KEY:
            switch(ev.key){
            case TB_KEY_ARROW_UP:
                state_update_cursor(-1);
                break;
            case TB_KEY_ARROW_DOWN:
                state_update_cursor(1);
                break;
            case TB_KEY_ENTER:
                if(state.selection > 0){
                    line = line_buffer_getline(state.lines,state.selection);
                }
                goto done;
            case TB_KEY_ESC:
                goto done;
            case TB_KEY_BACKSPACE:
            case TB_KEY_BACKSPACE2:
                state_update('\b');
                break;
            default:
                append = ev.ch;
                if(ev.key == TB_KEY_SPACE)
                    append = ' ';
                if(ev.key == TB_KEY_TAB)
                    append = '\t';

                if(isprint(append)){
                    state_update(append);
                }
            }
        case TB_EVENT_RESIZE:
            break;
        }
        state_draw();
    }

done:
    tb_shutdown();
    if(line){
        printf("%s\n", line);
    }
    state_destroy();
    return 0;
}
