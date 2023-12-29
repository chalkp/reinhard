#include "pipeline.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

Pipeline *createPipeline(const char *vertFile, const char *fragFile) {
  Pipeline *pipeline = (Pipeline*)malloc(sizeof(Pipeline));
  pipeline->vert = readFile(vertFile);
  pipeline->frag = readFile(fragFile);
  return pipeline;
}

void destroyPipeline(Pipeline *gp) {
  free(gp->vert.data);
  free(gp->frag.data);
  free(gp);
}
