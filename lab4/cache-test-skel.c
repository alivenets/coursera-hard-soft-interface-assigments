/*
Coursera HW/SW Interface
Lab 4 - Mystery Caches

Mystery Cache Geometries (for you to keep notes):
mystery0:
    block size =
    cache size =
    associativity =
mystery1:
    block size =
    cache size =
    associativity =
mystery2:
    block size =
    cache size =
    associativity =
mystery3:
    block size =
    cache size =
    associativity =
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real"
 * memory addresses. You can use any convenient integer value as a
 * memory address, you should not be able to cause a segmentation
 * fault by providing a memory address out of your programs address
 * space as the argument to access_cache.
 */

#define MAX_CACHE_SIZE_BITS 24
#define MAX_CACHE_BLOCK_SIZE 1024
#define MAX_CACHE_ASSOC_BITS 24
/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  int retsize = -1;
  int i;
  flush_cache();
  access_cache(0);

  for (i = 1; i < MAX_CACHE_BLOCK_SIZE; ++i) {
    if (!access_cache(i)) {
      retsize = i;
      break;
    }
  }
  return retsize;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
  /* YOUR CODE GOES HERE */
  int retsize = -1;
  int i, j;
  for (i = 0; i < MAX_CACHE_SIZE_BITS; ++i) {
    int cache_size = (1 << i);
    flush_cache();
    
    for (j = 0; j <= cache_size / size; ++j) {
      access_cache(j*size);
    }
    
    if (!access_cache(0)) {
      retsize = cache_size;
      break;
    }
  }
  return retsize;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
  int i, j;
  int retsize = -1;

  for (i = 0; i < MAX_CACHE_ASSOC_BITS; ++i) {
    int assoc_size = (1 << i);
    flush_cache();
    for (j = 0; j <= assoc_size; ++j) {
      access_cache(j * size);
    }
    if (!access_cache(0)) {
      retsize = assoc_size;
      break;
    }
  }
  return retsize;
}

//// DO NOT CHANGE ANYTHING BELOW THIS POINT
int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.  You can
     test your geometry paramter discovery routines by calling
     cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
