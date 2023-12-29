#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char *readFile(const char *path) {
  FILE *file = fopen(path, "r");
  if(file == NULL) {
    fprintf(stderr, "failed to open file: %s\n", path);
    return NULL;
  }

  fseek(file, 0L, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char *buffer = (char*)malloc(sizeof(char)*size);
  (void)fread(buffer, 1, size, file);
  fclose(file);

  return buffer;
}
