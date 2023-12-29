#include "window.h"

Window *window;

void setup();
void run();
void finalize();

int main(int argc, char *argv[]) {
  setup();
  run();
  finalize();
}


void setup() {
  window = createWindow(800, 420, "reinhard");
}

void run() {
  while(!shouldClose(window)) {
    glfwPollEvents();
  }
}

void finalize() {
  destroyWindow(window);
}