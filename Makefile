CFLAGS=-Wall -Wextra -Werror -Wno-unused-result -ggdb -std=gnu99

SRCS=$(wildcard src/*.c)
LIB=$(wildcard lib/*.c)
TESTS=$(patsubst %.c, %, $(wildcard tests/*_test.c))
OBJ=bin/fuzzyfinder

tests/%_test: tests/%_test.c lib/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LIB)

all: install

.PHONY: clean tests
tests: $(TESTS)
	@./tests/run-tests.sh

$(OBJ): $(LIB) $(SRCS) 
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

install: $(OBJ)

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE) tests

clean:
	rm -rf $(TESTS) bin/*
