#include "reinhard.h"
#include <stdio.h>
#include <stdlib.h>

Reinhard *create_reinhard_instance() {
  Reinhard *reinhard = (Reinhard*)malloc(sizeof(Reinhard));
  if(reinhard == NULL) {
    fprintf(stderr, "malloc: failed to allocate memory for Reinhard\n");
    return NULL;
  }
  
  reinhard->window = create_window(800, 420, "reinhard");
  if(reinhard->window == NULL) {
    free(reinhard);
    return NULL;
  }

  reinhard->pipeline = create_pipeline("shaders/test.vert.spv", "shaders/test.frag.spv");
  if(reinhard->pipeline == NULL) {
    destroy_window(reinhard->window);
    free(reinhard);
    return NULL;
  }

  return reinhard;
}

void destroy_reinhard_instance(Reinhard *reinhard) {
  if(reinhard == NULL) {
    return;
  }

  destroy_window(reinhard->window);
  destroy_pipeline(reinhard->pipeline);
  free(reinhard);
}
