#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

CharVector readFile(const char *path) {
  FILE *file = fopen(path, "rb+");
  if(file == NULL) {
    fprintf(stderr, "failed to open file: %s\n", path);
    exit(1);
  }

  fseek(file, 0L, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char *buffer = (char*)calloc(size, sizeof(char));
  long readed = fread(buffer, sizeof(char), size, file);
  if(readed != size) {
    fprintf(stderr, "failed to read file: %s\nsize readed: %ld\n", path, readed);
    exit(1);
  }
  fclose(file);

  CharVector ret = { buffer, size };
  return ret;
}

void writeFile(const char *path, const CharVector *cv) {
  FILE *file = fopen(path, "wb");
  long written = fwrite(cv->data, sizeof(char), cv->size, file);

  if(written != cv->size) {
    fprintf(stderr, "failed to write file: %s\nsize written: %ld\n", path, written);
    exit(1);
  }
  fclose(file);
}
