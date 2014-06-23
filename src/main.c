#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../deps/include/termbox.h"

#include "../include/text_buffer.h"
#include "../include/bit_array.h"
#include "../include/line_buffer.h"
#include "../include/is_subsequence.h"

struct {
    text_buffer * query;
    bit_array * display_filter;
    line_buffer * lines;
    int selection;
} state;

void state_init()
{
    state.selection = 0;
    state.lines = line_buffer_new(16);
    state.query = text_buffer_new(16);

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
    state.display_filter = bit_array_new(lines);
    bit_array_setall(state.display_filter);
    free(line);
}

void state_destroy()
{
    line_buffer_destroy(state.lines);
    bit_array_destroy(state.display_filter);
    text_buffer_destroy(state.query);
}

void state_draw()
{
    int GREY = 0xf4;
    tb_clear();
    tb_select_output_mode(TB_OUTPUT_256);
    int line_count = line_buffer_linecount(state.lines);

    tb_change_cell(0, 0,'>', TB_DEFAULT, TB_DEFAULT);
    tb_change_cell(0, 1,' ', TB_DEFAULT, TB_DEFAULT);

    int col = 2, width = tb_width(), height = tb_height();
    const char * query = text_buffer_data(state.query);
    for(int i = 0; query[i]; i++){
        tb_change_cell(col, 0, query[i], TB_WHITE, TB_DEFAULT);
        col += (query[i] == '\t') ? 4 : 1;
    }

    tb_set_cursor(col,0);
    int printed = 0;
    for(int i = 0; i < line_count; ++i){
        if(printed > height) break;
        if(!bit_array_get(state.display_filter,i)) continue;
        const char * line = line_buffer_getline(state.lines,i);
        if(i == state.selection){
            bool endseen = false;
            for(int j = 0; j < width; j++){
                endseen = endseen || !line[j];
                tb_change_cell(j, printed+1, endseen ? ' ' : line[j],
                    TB_BLACK, GREY);
            }
        }else{
            for(int j = 0; line[j]; j++){
                tb_change_cell(j, printed+1, line[j], TB_WHITE, TB_DEFAULT);
            }
        }
        printed++;
    }

    tb_present();
}

void state_update()
{
    const int lines = line_buffer_linecount(state.lines);
    const char * query = text_buffer_data(state.query);
    int first_set = -1;
    for(int i = 0; i < lines; ++i){
        const char * line = line_buffer_getline(state.lines,i);
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
                text_buffer_remove(state.query,1);
                state_update();
                break;
            default:
                append = ev.ch;
                if(ev.key == TB_KEY_SPACE)
                    append = ' ';
                if(ev.key == TB_KEY_TAB)
                    append = '\t';

                if(isprint(append)){
                    state.query = text_buffer_add(state.query,&append,1);
                    state_update();
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
