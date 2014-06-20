#include <stdio.h>

#include "../deps/include/termbox.h"

int main()
{
    int ret = tb_init();
    if(ret){
        fprintf(stderr, "tb_init failed with error code%d\n",ret);
        return 1;
    }
    tb_clear();

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
    tb_shutdown();
    return 0;
}
