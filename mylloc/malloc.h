#ifndef MYLLOC_H
#define MYLLOC_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define malloc(size) mylloc(size)
#define calloc(numitems, size) mycalloc(numitems, size)
#define realloc(ptr, size) myrealloc(ptr, size)
#define free(ptr) myfree(ptr)


void *mylloc(size_t sizes);
void *mycalloc(size_t numitems, size_t size);
void *myrealloc(void *ptr, size_t size);
void myfree(void *ptr);

#endif
