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
}

void setup() {
  reinhard = summonReinhardInstance();
}

void run() {
  while(!shouldClose(reinhard->window)) {
    glfwPollEvents();
  }
}

void finalize() {
  destroyReinhardInstance(reinhard);
}
