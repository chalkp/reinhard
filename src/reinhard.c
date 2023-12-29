#include "reinhard.h"
#include <stdlib.h>

Reinhard *summonReinhardInstance() {
  Reinhard *reinhard = (Reinhard*)malloc(sizeof(Reinhard));
  reinhard->window = createWindow(800, 420, "reinhard");
  reinhard->pipeline = createPipeline("shaders/test.vert.spv", "shaders/test.frag.spv");
  return reinhard;
}

void destroyReinhardInstance(Reinhard *reinhard) {
  destroyWindow(reinhard->window);
  destroyPipeline(reinhard->pipeline);
  free(reinhard);
}
