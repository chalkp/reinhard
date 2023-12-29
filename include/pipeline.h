#pragma once
#include "utils.h"

typedef struct Pipeline {
  CharVector vert;
  CharVector frag;
} Pipeline;

Pipeline *createPipeline(const char *vertFile, const char *fragFile);
void destroyPipeline(Pipeline *gp);
