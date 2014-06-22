#include <stdio.h>
#include <stdlib.h>

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
        line[strl] = '\0';
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

    int col = 0, width = tb_width(), height = tb_height();
    const char * query = text_buffer_data(state.query);
    for(int i = 0; query[i]; i++){
        tb_change_cell(0, col+i, query[i], TB_DEFAULT, TB_DEFAULT);
        col++;
    }

    tb_set_cursor(0,col);

    for(int i = 0; i < line_count; ++i){
        if(i > height) break;
        if(!bit_array_get(state.display_filter,i)) continue;
        const char * line = line_buffer_getline(state.lines,i);
        if(i == state.selection){
            bool endseen = false;
            for(int j = 0; j < width; j++){
                endseen = endseen || !line[j];
                if(endseen){
                    tb_change_cell(i+1,j, ' ', TB_DEFAULT, GREY);
                }else{
                    tb_change_cell(i+1,j, line[j], TB_DEFAULT, GREY);
                }
            }
        }else{
            for(int j = 0; line[j]; j++){
                tb_change_cell(1+i, j, line[j], TB_DEFAULT, TB_DEFAULT);
            }
        }
    }

    tb_present();
}

int main()
{
    state_init();

    int ret = tb_init();
    if(ret){
        fprintf(stderr, "tb_init failed with error code%d\n",ret);
        return 1;
    }

    struct tb_event ev;
    while(tb_poll_event(&ev)){
        switch (ev.type) {
        case TB_EVENT_KEY:
            switch(ev.key){
                goto done;
                break;
            }
        case TB_EVENT_RESIZE:
            break;
        }
    }

done:
    state_destroy();
    tb_shutdown();
    return 0;
}
