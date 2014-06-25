CFLAGS=-Wall -Wextra -Werror -Wno-unused-result -ggdb -std=gnu99

LIB=$(wildcard lib/*.c)
TESTS=$(patsubst %.c, %, $(wildcard tests/*_test.c))

tests/%_test: tests/%_test.c lib/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LIB)

all: install

.PHONY: clean tests
tests: $(TESTS)
	@./tests/run-tests.sh

main: CFLAGS+=-O3 $(LIB)
main: src/main.c
	$(CC) $(CFLAGS) -o bin/fuzzyfinder src/*.c

install:
	make main

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE) tests

clean:
	rm -rf $(TESTS) bin/*
