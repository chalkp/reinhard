#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

CharVector readFile(const char *path) {
  FILE *file = fopen(path, "rb+");
  if(file == NULL) {
    fprintf(stderr, "fopen: failed to open file: %s\n", path);
    exit(1);
  }

  fseek(file, 0L, SEEK_END);
  long size = ftell(file);
  rewind(file);

  if(size == -1) {
    fclose(file);
    fprintf(stderr, "fseek: failed to get file size: %s\n", path);
    exit(1);
  }

  char *buffer = (char*)calloc(size, sizeof(char));
  long readed = fread(buffer, sizeof(char), size, file);
  fclose(file);
  if(readed != size) {
    fprintf(stderr, "failed to read file: %s\nsize readed: %ld\n", path, readed);
    exit(1);
  }

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
