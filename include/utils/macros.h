#pragma once

#define _PTR_MEMORY_ALLOCATION_CHECK(PTR, NAME) \
  if(PTR == NULL) { \
    fprintf(stderr, "malloc: failed to allocate memory for %s\n", NAME); \
    return NULL; \
  }

#define _PTR_MEMORY_ALLOCATE(PTR, TYPE, SIZE, NAME) \
  PTR = (TYPE*)malloc(SIZE * sizeof(TYPE)); \
  _PTR_MEMORY_ALLOCATION_CHECK(PTR, NAME)
