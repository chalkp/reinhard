#include "pipeline.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

Pipeline *create_pipeline(const char *vert_file, const char *frag_file) {
  Pipeline *pipeline = (Pipeline*)malloc(sizeof(Pipeline));
  if(pipeline == NULL) {
    fprintf(stderr, "malloc: failed to allocate memory for Pipeline\n");
    return NULL;
  }

  pipeline->vertex_shader_code = read_file(vert_file);
  if(pipeline->vertex_shader_code.data == NULL) {
    free(pipeline);
    return NULL;
  }
  
  pipeline->fragment_shader_code = read_file(frag_file);
  if(pipeline->fragment_shader_code.data == NULL) {
    destroy_char_vector(&pipeline->vertex_shader_code);
    free(pipeline);
    return NULL;
  }
  
  return pipeline;
}

void destroy_pipeline(Pipeline *pipeline) {
  if(pipeline == NULL) {
    return;
  }

  destroy_char_vector(&pipeline->vertex_shader_code);
  destroy_char_vector(&pipeline->fragment_shader_code);
  free(pipeline);
}
