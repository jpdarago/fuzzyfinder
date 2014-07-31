CFLAGS=-Wall -Wextra -Werror -Wno-unused-result -ggdb -std=gnu99

SRCS=$(wildcard src/*.c)
LIB=$(wildcard lib/*.c)
TESTS=$(patsubst %.c, %, $(wildcard tests/*_test.c))

tests/%_test: tests/%_test.c lib/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LIB)

all: install

.PHONY: clean tests
tests: $(TESTS)
	@./tests/run-tests.sh

bin/fuzzyfinder: CFLAGS+=-O3 $(LIB)
bin/fuzzyfinder: $(LIB) $(SRCS) 
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/fuzzyfinder src/*.c

install: bin/fuzzyfinder
	make bin/fuzzyfinder

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE) tests

clean:
	rm -rf $(TESTS) bin/*
