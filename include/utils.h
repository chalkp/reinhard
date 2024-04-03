#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct char_vector {
  char *data;
  size_t size;
} CharVector;

CharVector create_char_vector();
CharVector copy_char_vector(const CharVector *cv);
void destroy_char_vector(CharVector *cv);

CharVector read_file(const char *path);
void write_file(const char *path, const CharVector *cv);


typedef struct string_array {
  char **data;
  size_t size;
  size_t capacity;
} StringArray;

StringArray create_string_array();
void push_string_array(StringArray *arr, const char *str);
void destroy_string_array(StringArray *arr);
