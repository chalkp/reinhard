#include "reinhard.h"
#include <stdio.h>

Reinhard *reinhard;

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