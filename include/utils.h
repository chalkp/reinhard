#pragma once

#include <stddef.h>

typedef struct char_vector {
  char *data;
  size_t size;
} CharVector;

CharVector create_char_vector();
CharVector copy_char_vector(const CharVector *cv);
void destroy_char_vector(CharVector *cv);

CharVector read_file(const char *path);
void write_file(const char *path, const CharVector *cv);