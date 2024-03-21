#include "pipeline.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

Pipeline *create_pipeline(const char *vert_file, const char *frag_file) {
  Pipeline *pipeline = (Pipeline*)malloc(sizeof(Pipeline));
  pipeline->vertex_shader_code = read_file(vert_file);
  pipeline->fragment_shader_code = read_file(frag_file);
  return pipeline;
}

void destroy_pipeline(Pipeline *pipeline) {
  free(pipeline->vertex_shader_code.data);
  free(pipeline->fragment_shader_code.data);
  free(pipeline);
  pipeline = NULL;
}
