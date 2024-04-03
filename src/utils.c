#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CharVector create_char_vector() {
  CharVector ret = {NULL, 0};
  return ret;
}

CharVector copy_char_vector(const CharVector *cv) {
  CharVector copy;
  copy.size = cv->size;

  copy.data = (char*)malloc(copy.size * sizeof(char));
  if(copy.data == NULL) {
    fprintf(stderr, "malloc: failed to allocate memory in copy_char_vector\n");
    return (CharVector){NULL, 0}; // return error CharVector
  }

  memcpy(copy.data, cv->data, copy.size);

  return copy;
}

void destroy_char_vector(CharVector *cv) {
  if(cv->data == NULL) {
    return;
  }
  free(cv->data);
  cv->data = NULL;
  cv->size = 0;  
}

CharVector read_file(const char *path) {
  FILE *file = fopen(path, "rb+");
  if(file == NULL) {
    fprintf(stderr, "fopen: failed to open file: %s\n", path);
    exit(1);
  }

  fseek(file, 0L, SEEK_END);
  size_t size = ftell(file);
  rewind(file);
  if(size == (size_t)-1) {
    fclose(file);
    fprintf(stderr, "fseek: failed to get file size: %s\n", path);
    exit(1);
  }

  char *buffer = (char*)calloc(size + 1, sizeof(char)); // size + 1: reserve space for a potential null terminator
  if(buffer == NULL) {
    fclose(file);
    fprintf(stderr, "calloc: failed to allocate buffer memory\n");
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
    fprintf(stderr, "failed to open file: %s\n", path);
    exit(1);
  }

  size_t written = fwrite(cv->data, sizeof(char), cv->size, file);
  fclose(file);
  if(written != cv->size) {
    fprintf(stderr, "failed to write file: %s\nsize written: %ld\n", path, written);
    exit(1);
  }
}



StringArray create_string_array() {
  StringArray arr;
  arr.size = 0;
  arr.capacity = 4;
  arr.data = (char**)malloc(arr.capacity*sizeof(char*));
  if(arr.data == NULL) {
    fprintf(stderr, "malloc: failed to allocate memory for string array\n");
    exit(1);
  }
  return arr;
}

void push_string_array(StringArray *arr, const char *str) {
  if(arr->size == arr->capacity) {
    arr->capacity *= 2;
    arr->data = (char**)realloc(arr->data, arr->capacity * sizeof(char*));
    if(arr->data == NULL) {
      fprintf(stderr, "realloc: failed to reallocate memory for string array\n");
      exit(1);
    }
  }
  arr->data[arr->size] = strdup(str);
  arr->size++;
}

void destroy_string_array(StringArray *arr) {
  for(size_t i=0; i<arr->size; i++) {
    free((void*)arr->data[i]);
  }
  free(arr->data);
}
