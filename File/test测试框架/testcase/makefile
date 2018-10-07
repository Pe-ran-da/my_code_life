CC = gcc
CFLAGS = -std=c11 -Wall
INCLUDES = -I./include 

.PHONY: clean

libtest.a : test.o
	ar crv libtest.a test.o

test.o : src/test.c include/test.h 
	$(CC) -c $(CFLAGS) $(INCLUDES) src/test.c 

install :
	cp -a include/*  output/include
	cp -a libtest.a output/libs

clean:
	rm -rf *.o *.a ./output/libs/* ./output/include/* 
