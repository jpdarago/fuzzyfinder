CFLAGS=-Wall -Wextra -Werror -ggdb

LIB=$(wildcard lib/*.c)
TESTS=$(patsubst %.c, %, $(wildcard tests/*_test.c))

.PHONY: clean tests
tests: CFLAGS += -O0 $(LIB)
tests: $(TESTS)
	@./tests/run-tests.sh

clean:
	rm -rf $(TESTS)
