#pragma once

typedef struct CharVector {
  char *data;
  long size;
} CharVector;

CharVector readFile(const char *path);
void writeFile(const char *path, const CharVector *cv);
