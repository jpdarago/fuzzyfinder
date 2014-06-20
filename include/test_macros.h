#ifndef __TEST_MACROS_H
#define __TEST_MACROS_H

#define ASSERT(cond,msg,...)                                                \
    if(!(cond)) do{                                                         \
        fprintf(stderr,"%s:%d " msg "\n",__FILE__,__LINE__, ##__VA_ARGS__); \
        assert(0);                                                          \
    }while(0)                                                               \

#endif
