#include "toplev.h"

#include <cstdlib>
#include <stdio.h>
#include <stdexcept>
#include "game.h"

toplev::toplev() {}
toplev::~toplev() {}

int toplev::main(int argc, char **argv) {
  reinhard::Game game{};

  try {
    game.run();
  } catch (const std::exception &e) {
    fprintf(stderr, "%s\n", e.what());
    return 1;
  }

  return 0;
}

void toplev::finalize() {}
