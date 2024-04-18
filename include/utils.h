#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "utils/vector.h"
#include "utils/macros.h"

#define pointer_memory_allocate(PTR, TYPE, SIZE, NAME) _PTR_MEMORY_ALLOCATE(PTR, TYPE, SIZE, NAME)

typedef struct {
  char *data;
  size_t size;
  size_t capacity;
} CharVector;

typedef struct {
  char **data;
  size_t size;
  size_t capacity;
} StringArray;

CharVector create_char_vector();
void destroy_char_vector(CharVector *cv);
CharVector copy_char_vector(const CharVector *cv);

StringArray create_string_array();
void destroy_string_array(StringArray *arr);
void push_string_array(StringArray *arr, const char *str);

CharVector read_file(const char *path);
void write_file(const char *path, const CharVector *cv);

void print_error(const char *format, ...);