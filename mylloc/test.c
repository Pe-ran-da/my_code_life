#include "malloc.h"

#define malloc(size) mylloc(size)
#define calloc(numitems, size) mycalloc(numitems, size)
#define realloc(ptr, size) myrealloc(ptr, size)
#define free(ptr) myfree(ptr)

int main(){
  char * blah = malloc(13);
  if(blah == NULL){
    printf("Error: Malloc failed to allocate memroy.\n");
    exit(1);
  }
  strcpy(blah, "test malloc\n");
  printf(blah);
  free(blah);
  char * strd = calloc(27, 1);
  if(strd == NULL){
    printf("Error: Calloc failed to allocate memroy.\n");
    exit(2);
  }
  strcpy(strd, "This is a calloc string.\n");
  printf(strd);
  free(strd);
  return 0;
}
