CC = gcc
CFLAGS = -I./output1/include/ -DFUNC_TEST -std=c11 -Wall -g  
OBJC = main.o is_prime.o add.o nuton.o 

.PHONY : clean

a.out : $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) output1/libs/libtest.a 

main.o : main.c
	$(CC) -c $(CFLAGS) main.c

is_prime.o : is_prime.c is_prime.h
	$(CC) -c $(CFLAGS) is_prime.c

add.o : add.h add.c
	$(CC) -c $(CFLAGS) add.c

nuton.o : nuton.c nuton.h
	$(CC) -c $(CFLAGS) nuton.c

clean :
	rm -rf *.o a.out



