CFLAGS=-Wall -Wextra -Werror -ggdb -std=gnu99

LIB=$(wildcard lib/*.c)
TESTS=$(patsubst %.c, %, $(wildcard tests/*_test.c))
BIN=src/main

DEPS=deps/lib/libtermbox.a

tests/%_test: tests/%_test.c lib/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LIB)

all: install

.PHONY: clean tests
tests: $(TESTS)
	@./tests/run-tests.sh

main: LDLIBS=$(DEPS)
main: CFLAGS+=-O3 $(LIB)
main: $(BIN)
	mv src/main bin/fuzzyfinder

install:
	./install-dependencies.sh
	make main

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE) tests

clean:
	rm -rf $(TESTS) bin/* deps/*
