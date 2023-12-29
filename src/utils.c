#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char *readFile(const char *path) {
  FILE *file = fopen(path, "rb");
  if(file == NULL) {
    fprintf(stderr, "failed to open file: %s\n", path);
    exit(1);
  }

  fseek(file, 0L, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char *buffer = (char*)malloc(sizeof(char)*size);
  long readed = fread(buffer, sizeof(char), size, file);
  if(readed != size) {
    fprintf(stderr, "failed to read file: %s\nsize readed: %ld", path, readed);
    exit(1);
  }
  fclose(file);

  return buffer;
}
