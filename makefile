CC=clang
CFLAGS= -g --std=c11 -I.

SRCS=$(wildcard *.c)
TESTS=$(wildcard test/*.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
TESTOBJ=$(patsubst %.c,%.o,$(TESTS))

all: libuds.a test

uds_test: $(TESTOBJ) libuds.a
	$(CC) -o $@ $^

libuds.a: $(OBJS)
	ar rcs $@ $^

clean: 
	rm *.o
	rm *.a

test: uds_test
	exec uds_test

.PHONY: clean test 
