#include "game.h"

namespace reinhard {
  void reinhard::Game::run() {
    while(!window.shouldClose()) {
      glfwPollEvents();
    }
  }
}
