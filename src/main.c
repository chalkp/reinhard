#include "device.h"
#include "pipeline.h"
#include "reinhard.h"
#include <stdio.h>

Reinhard *reinhard;
Device *device;
Pipeline *pipeline;

void setup();
void run();
void finalize();

int main() {
  setup();
  run();
  finalize();
  return 0;
}

void setup() {
  device = create_device(reinhard->window);
  pipeline = create_pipeline(/*device, */"shaders/test.vert.spv", "shaders/test.frag.spv");
  reinhard = create_reinhard_instance();
  if(reinhard == NULL) {
    fprintf(stderr, "Failed to create Reinhard instance\n");
    return;
  }
}

void run() {
  while(!should_close(reinhard->window)) {
    glfwPollEvents();
  }
}

void finalize() {
  destroy_reinhard_instance(reinhard);
}
