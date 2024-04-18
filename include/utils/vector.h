#pragma once
#include <stdio.h>
#include <stdlib.h>

#define _VECTOR_INIT(vector) \
  (vector)->data = NULL; \
  (vector)->size = 0; \
  (vector)->capacity = 0;

#define _VECTOR_ALLOCATE(vector, new_capacity) \
  (vector)->data = realloc((vector)->data, (new_capacity) * sizeof(*(vector)->data)); \
  if((vector)->data == NULL) { \
    fprintf(stderr, "Memory allocation failed!\n"); \
    exit(1); \
  } \
  (vector)->capacity = (new_capacity);

#define _VECTOR_PUSH_BACK(vector, data) \
  if((vector)->size == (vector)->capacity) { \
    _VECTOR_ALLOCATE((vector), (((vector)->capacity)<<1)) \
  } \
  (vector).data[(vector).size++] = (data);

#define _VECTOR_FREE(vector) free((vector)->data);

#define _VECTOR_AT(vector, index) (vector.data[index])
