#pragma once

#include "window.h"

namespace reinhard {
  class Game {
  public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 420;

    void run();
  private:
    Window window{WIDTH, HEIGHT, "Reinhard"};
  };
}
