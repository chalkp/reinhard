#include "utils.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


CharVector create_char_vector() {
  CharVector char_vector;
  _VECTOR_INIT(&char_vector);
  _VECTOR_ALLOCATE(&char_vector, 4);
  return char_vector;
}

void destroy_char_vector(CharVector *char_vector) {
  if(char_vector->data == NULL) {
    return;
  }
  _VECTOR_FREE(char_vector);
  char_vector->data = NULL;
  char_vector->size = 0;
}

CharVector copy_char_vector(const CharVector *cv) {
  CharVector copy;
  copy.size = cv->size;

  copy.data = (char*)malloc(copy.size * sizeof(char));
  if(copy.data == NULL) {
    print_error("malloc: failed to allocate memory in copy_char_vector\n");
    return (CharVector){NULL, 0}; // return error CharVector
  }

  memcpy(copy.data, cv->data, copy.size);

  return copy;
}


StringArray create_string_array() {
  StringArray string_array;
  _VECTOR_INIT(&string_array);
  _VECTOR_ALLOCATE(&string_array, 4);
  return string_array;
}

void push_string_array(StringArray *string_array, const char *str) {
  if(string_array->size == string_array->capacity) {
    _VECTOR_ALLOCATE(string_array, ((string_array->capacity)<<1));
  }
  string_array->data[string_array->size++] = strdup(str);
}

void destroy_string_array(StringArray *arr) {
  for(size_t i=0; i<arr->size; i++) {
    free((void*)arr->data[i]);
  }
  free(arr->data);
}




CharVector read_file(const char *path) {
  FILE *file = fopen(path, "rb+");
  if(file == NULL) {
    print_error("fopen: failed to open file: %s\n", path);
    exit(1);
  }

  fseek(file, 0L, SEEK_END);
  size_t size = ftell(file);
  rewind(file);
  if(size == (size_t)-1) {
    fclose(file);
    print_error("fseek: failed to get file size: %s\n", path);
    exit(1);
  }

  char *buffer = (char*)calloc(size + 1, sizeof(char)); // size + 1: reserve space for a potential null terminator
  if(buffer == NULL) {
    fclose(file);
    print_error("calloc: failed to allocate buffer memory\n");
    exit(1);
  }
  
  size_t readed = fread(buffer, sizeof(char), size, file);
  fclose(file);
  if(readed != size) {
    free(buffer);
    return (CharVector){NULL, 0};
  }

  CharVector ret = { buffer, size };
  return ret;
}

void write_file(const char *path, const CharVector *cv) {
  FILE *file = fopen(path, "wb");
  if(file == NULL) {
    print_error("failed to open file: %s\n", path);
    exit(1);
  }

  size_t written = fwrite(cv->data, sizeof(char), cv->size, file);
  fclose(file);
  if(written != cv->size) {
    print_error("failed to write file: %s\nsize written: %ld\n", path, written);
    exit(1);
  }
}


void print_error(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  vfprintf(stderr, format, ap);
  va_end(ap);
  fputc('\n', stderr);
}