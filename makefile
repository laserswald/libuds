CC=clang
CFLAGS= -g --std=c11
tests=

mindata_test: ${tests} libuds.a
	gcc -o $@ ${tests} -L. -lmindata

all: libmindata.a test

libuds.a: vector.o dllist.o
	ar rcs libmindata.a $^

clean: 
	rm *.o
	rm *.a

test: mindata_test
	exec mindata_test
