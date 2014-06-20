CFLAGS=-Wall -Wextra -Werror -ggdb -std=c99

LIB=$(wildcard lib/*.c)
TESTS=$(patsubst %.c, %, $(wildcard tests/*_test.c))
BIN=src/main.c

DEPS=deps/lib/libtermbox.a

tests/%_test: tests/%_test.c lib/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LIB)

.PHONY: clean tests
tests: $(TESTS)
	@./tests/run-tests.sh

main: LDLIBS=$(DEPS)
main: $(BIN)
	mv src/main bin/main

clean:
	rm -rf $(TESTS) bin/* deps/*
